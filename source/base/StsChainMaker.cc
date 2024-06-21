#include "StsChainMaker.hh"

#include "StsDecoder.hh"

#include "StsDst.hh"
#include "StsRunInfo.hh"
#include "StsEventInfo.hh"

#include "StsTriggerManager.hh"
#include "StsTrigger.hh"

ClassImp(StsChainMaker);

StsChainMaker* StsChainMaker::mInstance = nullptr;

StsChainMaker* StsChainMaker::GetChainMaker(int ioMode, const char* file){
  if (mInstance != nullptr)
    return mInstance;
  return new StsChainMaker(ioMode, file);
}

StsChainMaker::StsChainMaker(int ioMode, const char* file) 
: StsMaker("StsChainMaker", "StsChainMaker"), mIoMode(ioMode), mStageFlag(-999), mExpName(""), mTrigType(""), mExcuteRun(""), mRejectRun(""),
  mInputFile(file), mOutputPath(""), mOutputFile("StsDst"), mEventNum(-1), mCurrentEventID(-1)
{
    mInstance = this;
    mRunList.clear();
}

StsChainMaker::~StsChainMaker()
{
}

Int_t StsChainMaker::Init() 
{  
    if(mIoMode==kRead){
        if(!InitRead()){exit(0);}
    }
    else if(mIoMode==kWrite){
        if(!InitWrite()){exit(0);}
    }
    else if(mIoMode==kOnline){
        if(!InitOnline()){exit(0);}
    }

    InitMakers();
    Print();

    return 1;
}

Int_t StsChainMaker::Make() 
{
    if(mIoMode==kRead){
        MakeRead();
    }
    else if(mIoMode==kWrite){
        for(int run=0; run<mRunList.size(); run++){
            if(mRunList[run].second.size() == 0){
                cout << "StsChainMaker::Make() --- run: " << mRunList[run].first << " has been no files. run is skipped..." << endl;
                continue;
            }

            PrintRun(run);
            InitWriteDst(run);
            MakeWrite();
            FinishWriteDst();

            cout << "StsChainMaker::Make() --- End of Run : " << mRunList[run].first << endl;
        }
    }

    return 1;
}

Int_t StsChainMaker::Make(int event)
{
    mEventNum = event;
    if(mIoMode==kRead){
        MakeRead();
    }
    else if(mIoMode==kOnline){
        MakeOnline();
    }
    return 1;
}

Int_t StsChainMaker::Finish() 
{

    // test !!! 
    TIter iter(GetListOfTasks());
    StsMaker* maker;
    while ( (maker = dynamic_cast<StsMaker*>(iter())) ) {
        cout << "StsChainMaker::Finish() --- " << maker -> GetName() << " is Finished" << endl;
        maker -> Finish();
    }

    return 1;
}

Int_t StsChainMaker::Clear()
{
    mDst -> Clear();

    return 1;
}

StsDst* StsChainMaker::GetDst(){return mDst;}
StsRunInfo* StsChainMaker::GetRunInfo(){return mDst->GetRunInfo();}
StsEventInfo* StsChainMaker::GetEventInfo(){return mDst->GetEventInfo();}
StsTrigger* StsChainMaker::GetTrigger(){return mTrigManager->GetTrigger();}

void StsChainMaker::SetTriggerType(TString type){mTrigType = type;}
void StsChainMaker::SetExcuteRun(TString run){mExcuteRun = run;}
void StsChainMaker::SetRejectRun(TString run){mRejectRun = run;}
void StsChainMaker::SetEventNum(Int_t eventNum){mEventNum = eventNum;}
void StsChainMaker::SetInputFile(TString inputFile){mInputFile = inputFile;}
void StsChainMaker::SetOutputPath(TString outPath){mOutputPath = outPath;}

Int_t StsChainMaker::InitRun()
{
    if(mExpName == "" && mInputFile != ""){
        mRunList = GetRunList(mInputFile, mRejectRun, mStageFlag);
        return 1;
    }
    else if(mExpName != "" && mInputFile == ""){
        // mRunList = GetExpRunList(mExpName, mRejectRun, mStageFlag);
        return 1;
    }
    else if(mExpName == "" && mInputFile == "" && mExcuteRun != ""){
        mRunList = GetRunList(mExcuteRun, mRejectRun, mStageFlag);
        return 1;
    }
    else{
        cout << "StsChainMaker::InitRun() --- Warnning!!! Make sure the run setup" << endl;
        cout << "                             Your input parameters" << endl;
        cout << "                             Experiment: " << mExpName << endl;
        cout << "                             InputFile : " << mInputFile <<  endl;
        cout << "                             ExcuteRun : " <<  mExcuteRun << endl;

        int tmpNum = 0;
        vector<Int_t> Runs = GetRunsFromString(mExcuteRun);
        if(Runs.size()==0){cout <<"                             ExcuteRun : "<<endl;}
        for(int i=0; i<Runs.size(); i++){
            if(i==0){cout <<"                             ExcuteRun : ";}
            if(i!=Runs.size()-1){cout << Runs[i] << ", ";}
            if(i==Runs.size()-1){cout << Runs[i] << endl;}

            tmpNum++;
            if(tmpNum==5 && i!=Runs.size()-1){
                cout << endl;
                cout << "                                         ";
            } 
        }
        return 0;
    }

    return 0;
}

Int_t StsChainMaker::InitRead()
{
    return 1;
}

Int_t StsChainMaker::InitWrite()
{
    mStageFlag = kDaqStage;
    mTrigManager = new StsTriggerManager(mTrigType);
    mDst = new StsDst(mIoMode);
    mDst -> SetStageFlag(mStageFlag);
    mDst -> SetTrigger(GetTrigger());
    mDst -> Init();

    if(!InitRun()){return 0;}

    mDecoder = new StsDecoder();

    return 1;
}

Int_t StsChainMaker::MakeWrite()
{
    Clear();

    int tmpEventNum = 0;
    while(mDecoder->Make()){
        if(tmpEventNum == mEventNum){break;}
        PrintEvent(mDecoder->GetEventNumber());

        TIter iter(GetListOfTasks());
        StsMaker* maker;
        while ( (maker = dynamic_cast<StsMaker*>(iter())) ) {
            cout << "StsChainMaker::Make() --- " << maker -> GetName() << " is Running" << endl;
            maker -> Make();
        }

        FillDst();
        Clear();
        
        tmpEventNum++;
    }

    return 1;
}

Int_t StsChainMaker::InitOnline()
{    
    if(mInputFile == ""){
        cout << "StsChainMaker::InitOnline() --- Warning!!! There is no DAQ input path" << endl;
        return 0;
    }

    mStageFlag = kDaqStage;
    mTrigManager = new StsTriggerManager(mTrigType);
    mDst = new StsDst(mIoMode);
    mDst -> SetStageFlag(mStageFlag);
    mDst -> SetTrigger(GetTrigger());
    mDst -> Init();

    mDecoder = new StsDecoder();
    mDecoder -> Init();
    mDecoder -> SetOnlineFile(mInputFile);

    return 1;
}

Int_t StsChainMaker::MakeOnline()
{
    cout << "  StsChainMaker::MakeOnline() current event: " << mCurrentEventID << endl;

    if(mEventNum != 0 && mCurrentEventID == -1){
        while(mCurrentEventID == mEventNum){
            if(!mDecoder->Make()){
                mDecoder -> SetOnlineFile(mInputFile);
                cout << "not mKae" << endl;
            }
            mCurrentEventID = mDecoder -> GetEventNumber();
            cout << " start " << endl;
        }

        TIter iter(GetListOfTasks());
        StsMaker* maker;
        while ( (maker = dynamic_cast<StsMaker*>(iter())) ) {
            cout << "StsChainMaker::Make() --- " << maker -> GetName() << " is Running" << endl;
            maker -> Make();
        }

        return 1;
    }

    cout << " decoder make " << endl;
    if(!mDecoder->Make()){
        mDecoder -> SetOnlineFile(mInputFile);
        MakeOnline();
    }

    cout << "decoder good " << endl;
    mCurrentEventID = mDecoder -> GetEventNumber();

    TIter iter(GetListOfTasks());
    StsMaker* maker;
    while ( (maker = dynamic_cast<StsMaker*>(iter())) ) {
        cout << "StsChainMaker::Make() --- " << maker -> GetName() << " is Running" << endl;
        maker -> Make();
    }
    
    return 1;
}

Int_t StsChainMaker::InitWriteDst(int runIdx)
{
    // Output file initialization
    TString path = "";
    if(mOutputPath==""){path = AddDash(gSystem -> pwd());}
    else{path = AddDash(mOutputPath);}

    TString runID = TString::Itoa(mRunList[runIdx].first, 10);
    if(mRunList[runIdx].first == 0){runID = "000000000";}
    mOutputFile = path+"StsDst_"+runID+"_raw"+".root";

    mTFile = new TFile(Form("%s", mOutputFile.Data()), "recreate");
    if(!mTFile->IsOpen()){cout << "StsChainMaker::InitWriteDst --- Warnning!!! Make sure the ROOT File can not created :" << mOutputFile << endl;}
    
    mTree = new TTree("StsDst", "StsDst");
    mDst -> CreateDstArray(mTree);

    mDecoder -> SetRunFile(mRunList[runIdx].first, mRunList[runIdx].second);
    mDecoder -> Init();

    return 1;
}

Int_t StsChainMaker::FinishWriteDst()
{
    if(mIoMode==kWrite){
        cout << Form("StsChainMaker::Finish() --- Writing and closing file : %s", mOutputFile.Data()) << endl;
        mTFile -> cd();
        mTree -> Write();
        GetRunInfo() -> Write();
        mTFile -> Close();
    }
}

Int_t StsChainMaker::FillDst()
{
    if(mTree -> Fill()){return 1;}
    return 0;
}

void StsChainMaker::Print()
{
    TString ioMode = (mIoMode==kRead)? "READ mode" : ((mIoMode==kWrite)? "WRITE mode": "ONLINE mode");
    TString stageName = (mStageFlag==kDaqStage)? "DAQ stage" : ((mStageFlag==kRawStage)? "RAW stage": "RECO stage");

    TString totalEventNum = (mEventNum==-1)? "ALL" : TString::Itoa(mEventNum, 10);
    TString outputPath = (mOutputPath=="")? AddDash(gSystem->pwd()) : mOutputPath;


    cout << "=================================================================================" << endl;
    cout << "                                     StsChainMaker                               "<< endl;
    cout << "   --- Setup Parameter List ---                                                  "<< endl;
    cout << "   IoMode             : " << ioMode <<  endl;
    cout << "   Stage              : " << stageName << endl;
    cout << "   Experiment Type    : " << mExpName << endl;
    cout << "   Trigger Type       : " << mTrigType << endl;
    cout << "   Input File         : " << mInputFile << endl;

    int tmpNum = 0;
    vector<Int_t> Runs = GetRunsFromString(mExcuteRun);
    if(Runs.size()==0){cout <<"   Excute Run List    : "<<endl;}
    for(int i=0; i<Runs.size(); i++){
        if(i==0){cout <<"   Excute Run List    : ";}
        if(i!=Runs.size()-1){cout << Runs[i] << ", ";}
        if(i==Runs.size()-1){cout << Runs[i] << endl;}

        tmpNum++;
        if(tmpNum==5 && i!=Runs.size()-1){
            cout << endl;
            cout << "                        ";
        } 
    }

    tmpNum = 0;
    Runs = GetRunsFromString(mRejectRun);
    if(Runs.size()==0){cout <<"   Reject Run List    : "<<endl;}
    for(int i=0; i<Runs.size(); i++){
        if(i==0){cout <<"   Reject Run List    : ";}
        if(i!=Runs.size()-1){cout << Runs[i] << ", ";}
        if(i==Runs.size()-1){cout << Runs[i] << endl;}

        tmpNum++;
        if(tmpNum==5 && i!=Runs.size()-1){
            cout << endl;
            cout << "                        ";
        } 
    }

    cout << "   Total Event Number : " << totalEventNum << endl;
    cout << "   Output Path        : " << outputPath << endl;

    cout << endl;
    cout << "   --- Running Run Number List ---                                                "<< endl;

    tmpNum = 0;
    for(int i=0; i<mRunList.size(); i++){
        if(i==0){cout <<"   ";}

        if(i!=mRunList.size()-1){cout << mRunList[i].first << ", ";}
        if(i==mRunList.size()-1){cout << mRunList[i].first << endl;}
        tmpNum++;

        if(tmpNum==5 && i!=mRunList.size()-1){
            cout << endl;
            cout << "   ";
        } 
    }
    
    cout << endl;
    cout << "   --- Added Maker List ---                                                "<< endl;
    TIter iter(GetListOfTasks());
    StsMaker* maker;
    while ( (maker = dynamic_cast<StsMaker*>(iter())) ) {
        cout << "   " << maker -> GetName() << endl;
    }

    cout << endl;
    cout << "==================================================================================" << endl;
}

void StsChainMaker::PrintRun(int run)
{
    cout << "=================================================" << endl;
    cout << "  Run Number      : " << mRunList[run].first << endl;
    cout << "  Number of Files : " << mRunList[run].second.size() << endl;
    cout << "=================================================" << endl;
}

void StsChainMaker::PrintEvent(int event)
{
    cout << "=== StsChainMaker::Make() --- Event: " << event << endl; 
}
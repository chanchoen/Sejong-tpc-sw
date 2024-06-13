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
  mInputFile(file), mOutputPath(""), mOutputFile("StsDst"), mEventNum(-1), mEvent(0)
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
        cout << "StsChainMaker::Init() -- begin StsChainMaker construction for Read mode" << endl;
        if(!InitRead()){exit(0);}
    }
    else if(mIoMode==kWrite){
        cout << "StsChainMaker::Init() -- begin StsChainMaker construction for Write mode" << endl;
        if(!InitWrite()){exit(0);}
    }

    InitMakers();

    return 1;
}

Int_t StsChainMaker::Make() 
{
    cout << "StsChainMaker::Make()" << endl;

    if(mIoMode==kRead){
        MakeRead();
    }
    else if(mIoMode==kWrite){
        for(int run=0; run<mRunList.size(); run++){
            if(mRunList[run].second.size() == 0){
                cout << "StsChainMaker::Make() --- run: " << mRunList[run].first << " has been no files. run is skipped..." << endl;
                continue;
            }

            InitWriteDst(run);

            MakeWrite();

            FinishWriteDst(run);
        }

    }

    return 1;
}

Int_t StsChainMaker::Finish() 
{
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
        cout << "StsChainMaker::InitRun() --- Warnning!!! Make sure the run list setup" << endl;
        cout << "                             Your input parameters" << endl;
        cout << "                             Experiment: " << mExpName << endl;
        cout << "                             InputFile : " << mInputFile <<  endl;
        cout << "                             ExcuteRun : " <<  mExcuteRun << endl;
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
    for(int i=0; i<10; i++){
        mDecoder->Make(); // test 
    }


    // int testNum = 0;
    // while(mDecoder->Make()){
    //     if(!mDecoder->SkipEvent()){continue;}
    //     Clear();

    //     // testNum++;


    //     // TIter iter(GetListOfTasks());
    //     // StsMaker* maker;
    //     // while ( (maker = dynamic_cast<StsMaker*>(iter())) ) {
    //     //     cout << "StsChainMaker::Make() --- test " << maker -> GetName() << "." << endl;
    //     //     maker -> Make();
    //     // }

    //     // FillDst();
    // }

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
    mTree = new TTree("StsDst", "StsDst");

    mDst -> CreateDstArray(mTree);

    // Decoder initialization

    mDecoder -> SetRunFile(mRunList[runIdx].first, mRunList[runIdx].second);
    mDecoder -> Init();
}

Int_t StsChainMaker::FinishWriteDst(int runIdx)
{
    if(mIoMode==kWrite){
        cout << Form("StsChainMaker::Finish() --- Writing and closing Run: %i, %s", mRunList[runIdx].first,  mOutputFile.Data()) << endl;
        mTFile -> cd();
        mTree -> Write();
        GetRunInfo() -> Write();
        mTFile -> Close();
    }
}

Int_t StsChainMaker::FillDst()
{
    mTree -> Fill();
    return 1;
}
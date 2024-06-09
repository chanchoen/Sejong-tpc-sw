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
: StsMaker("StsChainMaker", "StsChainMaker"), mIoMode(ioMode), mStageFlag(-999), mExpName(""), mTrigType(""), mExcuteRun("ALL"), mRejectRun(""),
  mInputFile(file), mOutputPath(""), mOutputFile("StsDst"), mEventNum(-1), mEvent(0)
{
    mInstance = this;
}

StsChainMaker::~StsChainMaker()
{
}

Int_t StsChainMaker::Init() 
{  
    if(!InitChecker()){return 0;}

    if(mIoMode==kRead){
        cout << "StsChainMaker::Init() -- begin StsChainMaker construction for Read mode" << endl;
        if(InitRead() == false){return 0;}
    }
    else if(mIoMode==kWrite){
        cout << "StsChainMaker::Init() -- begin StsChainMaker construction for Write mode" << endl;
        if(InitWrite() == false){return 0;}
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
        MakeWrite();
    }

    return 1;
}

Int_t StsChainMaker::Finish() 
{
    if(mIoMode==kWrite){
        cout << Form("StsChainMaker::Finish() -- Writing and closing %s",mOutputFile.Data()) << endl;

        mTFile -> cd();
        mTree -> Write();
        GetRunInfo() -> Write();
        mTFile -> Close();
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
        // mRunList = GetRunList(mInputFile, mRejectRun);
        return 1;
    }
    else if(mExpName != "" && mInputFile == ""){
        // mRunList = GetExpRunList(mExpName, mRejectRun);
        // mRunList = GetRunList(mExcuteRun, mRejectRun);
        return 1;
    }
    return 0;
}

Int_t StsChainMaker::InitRead()
{
    return 1;
}

Int_t StsChainMaker::InitWrite()
{
    mStageFlag = kRawStage;
    mTrigManager = new StsTriggerManager(mTrigType);
    mDst = new StsDst(mIoMode);
    mDst -> SetStageFlag(mStageFlag);
    mDst -> SetTrigger(GetTrigger());
    mDst -> Init();

    // Output file initialization
    TString path = "";
    if(mOutputPath==""){path = StsUtil::AddDash(gSystem -> pwd());}
    else{path = StsUtil::AddDash(mOutputPath);}
    mOutputFile = path+mOutputFile+"_"+mTrigType+"_"+".root";

    mTFile = new TFile(Form("%s", mOutputFile.Data()), "recreate");
    mTree = new TTree("StsDst", "StsDst");

    mDst -> CreateDstArray(mTree);

    // Decoder initialization
    mDecoder = new StsDecoder(mInputFile);
    mDecoder -> Init();

    return 1;
}

Int_t StsChainMaker::MakeWrite()
{
    cout << "StsChainMaker::MakeWrite()" << endl;

    int testNum = 0;
    while(mDecoder->Make()){
        Clear();
        cout << testNum << endl;
        testNum++;


        // TIter iter(GetListOfTasks());
        // StsMaker* maker;
        // while ( (maker = dynamic_cast<StsMaker*>(iter())) ) {
        //     cout << "StsChainMaker::Make() --- test " << maker -> GetName() << "." << endl;
        //     maker -> Make();
        // }

        FillDst();
    }

    return 1;
}

Int_t StsChainMaker::FillDst()
{
    mTree -> Fill();
    return 1;
}


Int_t StsChainMaker::InitChecker()
{
    // if(mIoMode == kWrite){
    //     if(mInputFile == ""){}
    // }
    // else if(mIoMode == kRead){

    // }
    // else if(mIoMode == kOnline){

    // }

    return 1;
}
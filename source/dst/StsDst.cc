#include "StsDst.hh"
#include "StsTrigger.hh"

ClassImp(StsDst)

StsDst::StsDst(int ioMode)
: mIoMode(ioMode)
{
}

StsDst::~StsDst()
{
}

Int_t StsDst::Init()
{
    if(!mRunInfo){mRunInfo = new StsRunInfo();}
    if(!mEventInfo){mEventInfo = new StsEventInfo();}
    if(!mRawTPCPadArray && mStageFlag == kDaqStage){mRawTPCPadArray = new TClonesArray("StsRawTPCPad", mTrigger->GetTPCGeometry()->GetChannelNum());}
    if(!mRecoTPCPadArray && mStageFlag == kRecoStage){mRecoTPCPadArray = new TClonesArray("StsRecoTPCPad", mTrigger->GetTPCGeometry()->GetPadNum());}

    return 1;
}

Int_t StsDst::CreateDstArray(TTree* tree)
{
    if(mEventInfo){
        tree -> Branch("StsEventInfo", &mEventInfo);
    }
    if(mRawTPCPadArray && mStageFlag == kDaqStage){
        tree -> Branch("StsRawTPCPad", &mRawTPCPadArray);
    }
    if(mRecoTPCPadArray && mStageFlag == kRecoStage){
        tree -> Branch("StsRecoTPCPad", &mRecoTPCPadArray);
    }

    return 1;
}

Int_t StsDst::ReadDstArray(TTree* tree)
{
    if(mRawTPCPadArray && mStageFlag == kRawStage){
        tree -> SetBranchAddress("StsRawTPCPad", &mRawTPCPadArray);
    }
    if(mRecoTPCPadArray && mStageFlag == kRawStage){
        tree -> Branch("StsRecoTPCPad", &mRecoTPCPadArray);
    }
    return 1;
}

void StsDst::Clear(Option_t* option)
{
    if(mEventInfo){mEventInfo -> Clear();}
    if(mRawTPCPadArray && mStageFlag == kDaqStage){mRawTPCPadArray -> Clear("C");}
    if(mRecoTPCPadArray && mStageFlag == kRecoStage){mRecoTPCPadArray -> Clear("C");}
}

void StsDst::SetStageFlag(int stageFlag){mStageFlag = stageFlag;}
void StsDst::SetTrigger(StsTrigger* trig){mTrigger = trig;}

StsRunInfo* StsDst::GetRunInfo(){return mRunInfo;}
StsEventInfo* StsDst::GetEventInfo(){return mEventInfo;}
StsRawTPCPad* StsDst::GetRawTPCPad(int idx){return (StsRawTPCPad*)mRawTPCPadArray->ConstructedAt(idx);}
StsRecoTPCPad* StsDst::GetRecoTPCPad(int idx){return (StsRecoTPCPad*)mRecoTPCPadArray->ConstructedAt(idx);}
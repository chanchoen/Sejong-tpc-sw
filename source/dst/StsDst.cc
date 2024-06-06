#include "StsDst.hh"
#include "StsRunInfo.hh"

ClassImp(StsDst)

StsDst::StsDst()
{
    Init();
}

StsDst::~StsDst()
{
    if(mRunInfo){
        delete mRunInfo;
        mRunInfo = 0;
    }
}

Int_t StsDst::Init()
{
    if(!mRunInfo){
        mRunInfo = new StsRunInfo();
    }

    return 1;
}

void StsDst::Clear(Option_t* option)
{
    mRunInfo -> Clear();
}

StsRunInfo* StsDst::GetRunInfo(){return mRunInfo;}

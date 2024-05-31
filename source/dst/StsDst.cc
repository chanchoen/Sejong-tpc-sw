#include "StsDst.hh"

#include "StsRunInfo.hh"

// StsRunInfo* StsDst::mRunInfo = 0;

ClassImp(StsDst)

StsDst::StsDst()
{
}

StsDst::~StsDst()
{
}

void StsDst::Init()
{
    if(!mRunInfo){
        mRunInfo = new StsRunInfo();
    }
}

void StsDst::Clear()
{
    if(mRunInfo){mRunInfo = 0;}
}

// static StsRunInfo* StsDst::GetRunInfo(){return mRunInfo;}

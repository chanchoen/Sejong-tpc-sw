#include "StsTrigger_GEMTest.hh"
#include "StsTPCDrum.hh"

StsTrigger_GEMTest::StsTrigger_GEMTest()
{
    Init();
}

StsTrigger_GEMTest::~StsTrigger_GEMTest()
{
    delete mTPC;
    mTPC = 0;
}

Int_t StsTrigger_GEMTest::Init() 
{
    mTPC = new StsTPCDrum();
    mTPC -> SetGemTestForm();
    mTPC -> Init();
}

StsTPCDrum* StsTrigger_GEMTest::GetTPCGeometry(){return mTPC;}

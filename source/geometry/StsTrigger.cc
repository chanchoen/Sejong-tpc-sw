#include "StsTrigger.hh"

StsTrigger::StsTrigger()
{
}

StsTrigger::~StsTrigger()
{
}

Int_t StsTrigger::Init() 
{
    return 1;
}

StsTPCDrum* StsTrigger::GetTPCGeometry() 
{   
    StsTPCDrum* tpcDrum = new StsTPCDrum();
    return tpcDrum;
}
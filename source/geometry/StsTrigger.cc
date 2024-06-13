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

Int_t StsTrigger::GetCoBoNum(){return 0;}
Int_t StsTrigger::GetAsAdNum(){return 0;}

StsTPCDrum* StsTrigger::GetTPCGeometry() 
{   
    StsTPCDrum* tpcDrum = new StsTPCDrum();
    return tpcDrum;
}
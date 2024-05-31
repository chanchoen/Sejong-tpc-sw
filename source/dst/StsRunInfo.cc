#include "StsRunInfo.hh"

ClassImp(StsRunInfo)

StsRunInfo::StsRunInfo()
{
}

StsRunInfo::~StsRunInfo()
{
}

void StsRunInfo::Clear()
{
    test = 0;
}

void StsRunInfo::SetTest(int val)
{
    test = val;
}

Int_t StsRunInfo::GetTest()
{
    return test;
}

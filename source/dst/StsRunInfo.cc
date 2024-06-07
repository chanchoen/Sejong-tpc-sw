#include "StsRunInfo.hh"

ClassImp(StsRunInfo)

StsRunInfo::StsRunInfo()
{
}

StsRunInfo::~StsRunInfo()
{
}

void StsRunInfo::Clear(Option_t* option)
{
    TString mTrigName = "";
    TString mDate = "";
}

void StsRunInfo::SetTriggerName(TString trigName){mTrigName = trigName;}
void StsRunInfo::SetDate(TString date){mDate = date;}

TString StsRunInfo::GetTriggerName(){return mTrigName;}
TString StsRunInfo::GetDate(){mDate;}

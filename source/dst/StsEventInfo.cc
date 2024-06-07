#include "StsEventInfo.hh"

ClassImp(StsEventInfo)

StsEventInfo::StsEventInfo()
{
    Clear();
}

StsEventInfo::~StsEventInfo()
{
}

void StsEventInfo::Clear(Option_t* option)
{
    mEventNumber = 0;
    mEventTime = 0;
    mEventDiffTime = 0;
}

void StsEventInfo::SetEventNumber(UInt_t eventNum){mEventNumber = eventNum;}
void StsEventInfo::SetEventTime(UInt_t eventTime){mEventTime = eventTime;}
void StsEventInfo::SetEventDiffTime(UInt_t eventDiffTime){mEventDiffTime = eventDiffTime;}

UInt_t StsEventInfo::GetEventNumber(){return mEventNumber;}
UInt_t StsEventInfo::GetEventTime(){return mEventTime;}
UInt_t StsEventInfo::GetEventDiffTime(){return mEventDiffTime;}

#ifndef StsEventInfo_HH
#define StsEventInfo_HH

#include "TObject.h"
#include "TString.h"

using namespace std;

class StsEventInfo : public TObject
{
    public:
        StsEventInfo();
        virtual ~StsEventInfo();

        virtual void Clear(Option_t* option = "");

        void SetRunNumber(UInt_t runNum);
        void SetEventNumber(UInt_t eventNum);
        void SetEventTime(UInt_t eventTime);
        void SetEventDiffTime(UInt_t eventDiffTime);
        
        UInt_t GetRunNumber();
        UInt_t GetEventNumber();
        UInt_t GetEventTime();
        UInt_t GetEventDiffTime();

    private:
        UInt_t mRunNumber;
        UInt_t mEventNumber;
        UInt_t mEventTime;
        UInt_t mEventDiffTime;

        // trigger signal to be updated

    ClassDef(StsEventInfo, 1)
};

#endif
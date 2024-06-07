#ifndef StsTriggerManager_HH
#define StsTriggerManager_HH

#include "StsUtil.hh"

class StsTrigger;

class StsTriggerManager
{
    public:
        StsTriggerManager(TString trig = "");
        ~StsTriggerManager();

        Int_t Init();
        StsTrigger* GetTrigger();


    private:
        TString mTrigName;
        StsTrigger* mTrigger = 0;

};

#endif
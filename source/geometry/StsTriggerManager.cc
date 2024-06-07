#include "StsTriggerManager.hh"

#include "StsTrigger.hh"
#include "StsTrigger_GEMTest.hh"

StsTriggerManager::StsTriggerManager(TString trig)
: mTrigName(trig)
{
    Init();
}

StsTriggerManager::~StsTriggerManager()
{
}

Int_t StsTriggerManager::Init() 
{
    mTrigName.ToUpper();
    if(mTrigName == "GEMTEST"){
        mTrigger = new StsTrigger_GEMTest();
        return 1;
    }
    else if(mTrigName == "MAINRUN"){
        return 1;
    }
    // make the other experiment class...

    return 1;
}

StsTrigger* StsTriggerManager::GetTrigger(){return mTrigger;}
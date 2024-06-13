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

    int trigIdx = -1;
    for(int i=0; i<TRIGNUM; i++){
        TString triggerType = kTriggerType[i];
        triggerType.ToUpper();
        if(mTrigName == triggerType){
            trigIdx = i;
            break;
        }
    }
    if(trigIdx == -1){
        cout << "StsTriggerManager::Init()  --- Error: " << mTrigName << " is not correct value!! Please see the StsUtil kTriggerType." << endl;
        return 0;
    }

    if(trigIdx == 0){
        mTrigger = new StsTrigger_GEMTest();
        return 1;
    }
    else if(trigIdx == 1){
        return 1;
    }
    // make the other experiment class...

    return 1;
}

StsTrigger* StsTriggerManager::GetTrigger(){return mTrigger;}
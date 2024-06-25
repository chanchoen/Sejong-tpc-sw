#ifndef StsDst_HH
#define StsDst_HH

#include "TTree.h"
#include "TObject.h"
#include "TClonesArray.h"

#include "StsUtil.hh"
#include "StsRunInfo.hh"
#include "StsEventInfo.hh"
#include "StsRawTPCPad.hh"
#include "StsRecoTPCPad.hh"

class StsTrigger;
class StsRunInfo;


using namespace std;

class StsDst : public TObject
{
    public:
        StsDst(int ioMode=kWrite);
        virtual ~StsDst();

        virtual void Clear(Option_t* option = "");

        Int_t Init();
        Int_t CreateDstArray(TTree* tree);
        Int_t ReadDstArray(TTree* tree);

        void SetStageFlag(int stageFlag = kDaqStage);
        void SetTrigger(StsTrigger* trig);

        StsRunInfo* GetRunInfo();
        StsEventInfo* GetEventInfo();
        StsRawTPCPad* GetRawTPCPad(int idx);
        StsRecoTPCPad* GetRecoTPCPad(int idx);
    
    private:
        Int_t mIoMode;
        Bool_t mStageFlag;
        StsTrigger* mTrigger = 0;
        StsRunInfo* mRunInfo = 0;
        StsEventInfo* mEventInfo = 0;
        TClonesArray* mRawTPCPadArray = 0;
        TClonesArray* mRecoTPCPadArray = 0;
        
    ClassDef(StsDst, 1)
};

#endif
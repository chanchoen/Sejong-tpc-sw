#ifndef StsTrigger_GEMTest_HH
#define StsTrigger_GEMTest_HH

#include "StsTrigger.hh"


using namespace std;

class StsTrigger_GEMTest : public StsTrigger
{
    public:
        StsTrigger_GEMTest();
        virtual ~StsTrigger_GEMTest();

        virtual Int_t Init();
        virtual Int_t GetCoBoNum();
        virtual Int_t GetAsAdNum();
        virtual StsTPCDrum* GetTPCGeometry();
        virtual Int_t FillData(StsDst* dst, StsDAQFrame* frame);

    private:
        StsTPCDrum* mTPC = 0;
        Int_t mCoBoNum = 1;
        Int_t mAsAdNum = 1;
};

#endif


// StsTrigger_GEMTest is stemp of TPC Drum GEM test type experiment on 24/May
// *** Do not change the any setting configuration ***
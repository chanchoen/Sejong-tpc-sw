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
        virtual StsTPCDrum* GetTPCGeometry();

    private:
        StsTPCDrum* mTPC = 0;
};

#endif


// StsTrigger_GEMTest is stemp of TPC Drum GEM test type experiment on 24/May
// *** Do not change the any setting configuration ***
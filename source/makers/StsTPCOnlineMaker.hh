#ifndef StsTPCOnlineMaker_HH
#define StsTPCOnlineMaker_HH

#include "StsChainMaker.hh"
#include "StsMaker.hh"
#include "StsDst.hh"
#include "StsTrigger.hh"

#include "TCanvas.h"
#include "TH2Poly.h"

using namespace std;

class StsTPCOnlineMaker : public StsMaker
{
    public:
        StsTPCOnlineMaker();
        ~StsTPCOnlineMaker() {};

        Int_t Init();
        Int_t Make();
        Int_t Finish();

    private:
        StsDst* mDst = 0;
        StsTrigger* mTrigger = 0;
        StsTPCDrum* mTPC = 0;

        TCanvas* mCanvas = 0;
        TH2Poly* mPolyPad = 0;

    ClassDef(StsTPCOnlineMaker, 0)
};

#endif
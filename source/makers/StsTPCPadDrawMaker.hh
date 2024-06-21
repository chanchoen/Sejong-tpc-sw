#ifndef StsTPCPadDrawMaker_HH
#define StsTPCPadDrawMaker_HH

#include "StsChainMaker.hh"
#include "StsMaker.hh"
#include "StsDst.hh"
#include "StsTrigger.hh"

#include "TCanvas.h"
#include "TH2Poly.h"

using namespace std;

class StsTPCPadDrawMaker : public StsMaker
{
    public:
        StsTPCPadDrawMaker();
        ~StsTPCPadDrawMaker() {};

        Int_t Init();
        Int_t Make();
        Int_t Finish();

    private:
        StsDst* mDst = 0;
        StsTrigger* mTrigger = 0;
        StsTPCDrum* mTPC = 0;

        TCanvas* mCanvas = 0;
        TH2Poly* mPolyPad = 0;
        TH1D* mHisto = 0;

    ClassDef(StsTPCPadDrawMaker, 0)
};

#endif
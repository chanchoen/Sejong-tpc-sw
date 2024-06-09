#ifndef StsTPCPadDrawMaker_HH
#define StsTPCPadDrawMaker_HH

#include "StsMaker.hh"

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
        


    ClassDef(StsTPCPadDrawMaker, 0)
};

#endif
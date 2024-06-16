#include "StsTPCDrum.hh"
#include "TH2Poly.h"

StsTPCDrum::StsTPCDrum()
{
    mTPCForm = kMainRun;
}

Int_t StsTPCDrum::Init() 
{
    if(mTPCForm == kMainRun){ // for main pad form

    }
    else if(mTPCForm == kGemTestRun){ // for GEM test form
        mAsAdNum = 1;
        mChannelNum = 272; // including FPN
        mPadNum = 256;
        mLayerNum = 16;
        mRowNum = 16;
        mPadHeight = 0.;
        mPadWidth = 0.;
        mPadWidth2 = 0.;
        mPadGap = 0.;
    }

    return 1;
}

void StsTPCDrum::SetMainForm(){mTPCForm = kMainRun;}
void StsTPCDrum::SetGemTestForm(){mTPCForm = kGemTestRun;}

Int_t StsTPCDrum::GetAsAdNum(){return mAsAdNum;}
Int_t StsTPCDrum::GetChannelNum(){return mChannelNum;}
Int_t StsTPCDrum::GetPadNum(){return mPadNum;}
Int_t StsTPCDrum::GetLayerNum(){return mLayerNum;}
Int_t StsTPCDrum::GetRowNum(){return mRowNum;}
// Double_t StsTPCDrum::GetPadHeight(int idx);
// Double_t StsTPCDrum::GetPadWidth(int idx);
// Double_t StsTPCDrum::GetPadGap(int idx);


void StsTPCDrum::GetPolyGeometry(TH2Poly* poly)
{

}

void StsTPCDrum::InitMapping_ZAPtoGEMTest()
{

}

void StsTPCDrum::InitMapping_HyperZAPtoGEMTest()
{

}

void StsTPCDrum::InitMapping_HyperZAPtoMainRun()
{
    
}


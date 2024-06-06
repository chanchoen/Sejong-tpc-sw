#include "StsTPCDrum.hh"

StsTPCDrum::StsTPCDrum()
{
    mIsMainTest = 999;
}

Int_t StsTPCDrum::Init() 
{
    if(mIsMainTest == 1){ // for main pad form

    }
    else if(mIsMainTest == 0){ // for GEM test form
        
    }

    return 1;
}

void StsTPCDrum::SetGemTestForm(){mIsMainTest = 0;}
void StsTPCDrum::SetMainForm(){mIsMainTest = 1;}

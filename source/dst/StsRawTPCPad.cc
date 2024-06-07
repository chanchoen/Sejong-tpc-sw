#include "StsRawTPCPad.hh"

ClassImp(StsRawTPCPad)

StsRawTPCPad::StsRawTPCPad()
{
    Clear();
}

StsRawTPCPad::~StsRawTPCPad()
{
}

void StsRawTPCPad::Clear(Option_t* option)
{
    mChannel = 9999;
    std::memset(mADC, 0, sizeof(mADC));
}

void StsRawTPCPad::SetChannel(UShort_t chan){mChannel = chan;}
void StsRawTPCPad::SetADC(int tb, int adc){mADC[tb] = adc;}

void StsRawTPCPad::SetADC(UShort_t* adc)
{
    for(int i=0; i<TIMEBUCKET;){
        mADC[i] = adc[i];
    }
}

UShort_t StsRawTPCPad::GetChannel(){return mChannel;}
UShort_t StsRawTPCPad::GetADC(int tb){return mADC[tb];}
UShort_t* StsRawTPCPad::GetADC(){return mADC;}       
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
    mAget = 9999;
    mChannel = 9999;
    std::memset(mADC, 0, sizeof(mADC));
}

void StsRawTPCPad::SetAget(UShort_t aget){mAget = aget;}
void StsRawTPCPad::SetChannel(UShort_t chan){mChannel = chan;}
void StsRawTPCPad::SetADC(int tb, int adc){mADC[tb] = adc;}
void StsRawTPCPad::SetADC(uint16_t* adc){std::memcpy(mADC, adc, sizeof(mADC));}

UShort_t StsRawTPCPad::GetChannel(){return mChannel;}
UShort_t StsRawTPCPad::GetADC(int tb){return mADC[tb];}
UShort_t* StsRawTPCPad::GetADC(){return mADC;}       
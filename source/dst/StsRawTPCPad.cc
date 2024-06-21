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
    mAgetID = 9999;
    mChannelID = 9999;
    mPadID = 9999;
    std::memset(mADC, 0, sizeof(mADC));
}

void StsRawTPCPad::SetAgetID(UShort_t aget){mAgetID = aget;}
void StsRawTPCPad::SetChannelID(UShort_t chan){mChannelID = chan;}
void StsRawTPCPad::SetPadID(UShort_t pad){mPadID = pad;}
void StsRawTPCPad::SetADC(int tb, int adc){mADC[tb] = adc;}
void StsRawTPCPad::SetADC(uint16_t* adc){std::memcpy(mADC, adc, sizeof(mADC));}

UShort_t StsRawTPCPad::GetAgetID(){return mAgetID;}
UShort_t StsRawTPCPad::GetChannelID(){return mChannelID;}
UShort_t StsRawTPCPad::GetPadID(){return mPadID;}
UShort_t StsRawTPCPad::GetADC(int tb){return mADC[tb];}
UShort_t* StsRawTPCPad::GetADC(){return mADC;}       
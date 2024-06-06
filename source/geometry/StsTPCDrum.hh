#ifndef StsTPCDrum_HH
#define StsTPCDrum_HH

#include <string>
#include <iostream>

#include "StsUtil.hh"

using namespace std;

class StsTPCDrum : public StsUtil
{
    public:
        StsTPCDrum();
        virtual ~StsTPCDrum() {};

        Int_t Init();

        void SetGemTestForm();
        void SetMainForm();

        Int_t GetAsAdNum();
        Int_t GetChannelNum();

    protected:
        Int_t mIsMainTest;

        Int_t mAsAdNum;
        Int_t mChannelNum;
        Int_t mPadNum;
        Int_t mLayerNum;
        Int_t mRowNum;

    ClassDef(StsTPCDrum, 0);
};

#endif

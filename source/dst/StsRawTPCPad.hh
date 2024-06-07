#ifndef StsRawTPCPad_HH
#define StsRawTPCPad_HH

#include "TObject.h"
#include "StsUtil.hh"

using namespace std;

class StsRawTPCPad : public TObject, public StsUtil
{
    public:
        StsRawTPCPad();
        ~StsRawTPCPad();

        void Clear(Option_t* option = "");
        
        void SetChannel(UShort_t chan);
        void SetADC(int tb, int adc);
        void SetADC(UShort_t* adc);

        UShort_t GetChannel();
        UShort_t GetADC(int tb);
        UShort_t* GetADC();

        // Float_t GetX();
        // Float_t GetY();
        
    private:
        UShort_t mChannel;
        UShort_t mADC[TIMEBUCKET];

    ClassDef(StsRawTPCPad, 1)
};

#endif
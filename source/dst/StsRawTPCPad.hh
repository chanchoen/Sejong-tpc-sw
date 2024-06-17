#ifndef StsRawTPCPad_HH
#define StsRawTPCPad_HH

#include "TObject.h"
#include "StsUtil.hh"

using namespace std;

class StsRawTPCPad : public TObject
{
    public:
        StsRawTPCPad();
        virtual ~StsRawTPCPad();

        virtual void Clear(Option_t* option = "");
        
        void SetAGet(UShort_t aget);
        void SetChannel(UShort_t chan);
        void SetADC(int tb, int adc);
        void SetADC(uint16_t* adc);

        UShort_t GetChannel();
        UShort_t GetADC(int tb);
        UShort_t* GetADC();

        // Float_t GetX();
        // Float_t GetY();
        
    private:
        UShort_t mAget;
        UShort_t mChannel;
        UShort_t mADC[TIMEBUCKET];

    ClassDef(StsRawTPCPad, 1)
};

#endif
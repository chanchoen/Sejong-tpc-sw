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
        
        void SetAgetID(UShort_t aget);
        void SetChannelID(UShort_t chan);
        void SetPadID(UShort_t pad);
        void SetADC(int tb, int adc);
        void SetADC(uint16_t* adc);

        UShort_t GetAgetID();
        UShort_t GetChannelID();
        UShort_t GetPadID();
        UShort_t GetADC(int tb);
        UShort_t* GetADC();

        // Float_t GetX();
        // Float_t GetY();
        
    private:
        UShort_t mAgetID;
        UShort_t mChannelID;
        UShort_t mPadID;
        UShort_t mADC[TIMEBUCKET];

    ClassDef(StsRawTPCPad, 1)
};

#endif
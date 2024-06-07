#ifndef StsRunInfo_HH
#define StsRunInfo_HH

#include "TObject.h"
#include "TString.h"

using namespace std;

class StsRunInfo : public TObject
{
    public:
        StsRunInfo();
        ~StsRunInfo();

        void Clear(Option_t* option = "");

        void SetTriggerName(TString trigName);
        void SetDate(TString date);

        TString GetTriggerName();
        TString GetDate();

    private:
        TString mTrigName;
        TString mDate;

        // to be update some run operation
        // TString mGasType; // 
        // Int_t mGasPressure; // [Torr]
        // Int_t mGEMVolt; // [V]
        // Int_t mDynamicRange // [C]
        // etc...




    ClassDef(StsRunInfo, 1)
};

#endif
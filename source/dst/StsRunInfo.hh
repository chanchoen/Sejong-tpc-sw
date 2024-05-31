#ifndef StsRunInfo_HH
#define StsRunInfo_HH

#include "TObject.h"

using namespace std;

class StsRunInfo : public TObject
{
    public:
        StsRunInfo();
        ~StsRunInfo();

        void Clear();

        void SetTest(int val);
        Int_t GetTest();

    private:
        int test;


    ClassDef(StsRunInfo, 1)
};

#endif
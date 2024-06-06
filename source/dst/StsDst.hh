#ifndef StsDst_HH
#define StsDst_HH

#include <iostream>
#include "TObject.h"
#include "TClonesArray.h"

class StsRunInfo;

using namespace std;

class StsDst : public TObject
{
    public:
        StsDst();
        virtual ~StsDst();

        Int_t Init();
        virtual void Clear(Option_t* option = "");

        StsRunInfo* GetRunInfo();

    private:
        StsRunInfo* mRunInfo = 0;


    ClassDef(StsDst, 1)
};

#endif
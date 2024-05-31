#ifndef StsDst_HH
#define StsDst_HH

#include <iostream>
#include "TObject.h"
#include "TClonesArray.h"

class StsRunInfo;
class StsTPCRaw;

using namespace std;

class StsDst : public TObject
{
    public:
        StsDst();
        ~StsDst();

        void Init();
        void Clear();

        StsRunInfo* GetRunInfo(){return mRunInfo;}



    private:
        StsRunInfo* mRunInfo;


    ClassDef(StsDst, 1)
};

#endif
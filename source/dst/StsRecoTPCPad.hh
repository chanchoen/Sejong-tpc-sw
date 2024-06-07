#ifndef StsRecoTPCPad_HH
#define StsRecoTPCPad_HH

#include "TObject.h"

using namespace std;

class StsRecoTPCPad : public TObject
{
    public:
        StsRecoTPCPad();
        ~StsRecoTPCPad();

        void Clear(Option_t* option = "");
        
    private:

    ClassDef(StsRecoTPCPad, 1)
};

#endif
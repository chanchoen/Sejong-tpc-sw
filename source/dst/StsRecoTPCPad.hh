#ifndef StsRecoTPCPad_HH
#define StsRecoTPCPad_HH

#include "TObject.h"
#include "StsUtil.hh"

using namespace std;

class StsRecoTPCPad : public TObject
{
    public:
        StsRecoTPCPad();
        virtual ~StsRecoTPCPad();

        virtual void Clear(Option_t* option = "");
        
    private:

    ClassDef(StsRecoTPCPad, 1)
};

#endif
#ifndef StsTest2_HH
#define StsTest2_HH

#include "StsMaker.hh"
#include <string>
#include <iostream>
using namespace std;

class StsTest2 : public StsMaker
{
    public:
        StsTest2();
        ~StsTest2() {};

        Int_t Init();
        Int_t Make();
        Int_t Finish();

    ClassDef(StsTest2, 0)
};

#endif
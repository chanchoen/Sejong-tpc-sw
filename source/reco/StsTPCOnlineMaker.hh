#ifndef StsTPCOnlineMaker_HH
#define StsTPCOnlineMaker_HH

#include "StsMaker.hh"
#include <string>
#include <iostream>
using namespace std;

class StsTPCOnlineMaker : public StsMaker
{
    public:
        StsTPCOnlineMaker();
        ~StsTPCOnlineMaker() {};

        Int_t Init();
        Int_t Make();
        Int_t Finish();

    ClassDef(StsTPCOnlineMaker, 0)
};

#endif
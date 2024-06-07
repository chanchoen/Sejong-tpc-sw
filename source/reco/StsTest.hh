#ifndef StsTest_HH
#define StsTest_HH

#include "StsMaker.hh"
#include <string>
#include <iostream>
using namespace std;

class StsTest : public StsMaker
{
    public:
        StsTest();
        ~StsTest() {};

        Int_t Init();
        Int_t Make();
        Int_t Finish();

    ClassDef(StsTest, 0)
};

#endif
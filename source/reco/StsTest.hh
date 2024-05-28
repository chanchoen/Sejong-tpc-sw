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
        virtual ~StsTest() {};

        bool Init();
        bool Make();
        bool Finish();

    ClassDef(StsTest, 1)
};

#endif
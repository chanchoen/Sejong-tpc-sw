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
        virtual ~StsTest2() {};

        bool Init();
        bool Make();
        bool Finish();

    ClassDef(StsTest2, 1)
};

#endif
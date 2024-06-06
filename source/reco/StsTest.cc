#include "StsTest.hh"

#include <iostream>
using namespace std;

StsTest::StsTest()
:StsMaker("StsTest", "StsTest")
{
}

Int_t StsTest::Init() 
{
    cout << "StsTest::Init() --- testtest" << endl;
    return 1;
}

Int_t StsTest::Make() 
{
    return 1;
}


Int_t StsTest::Finish()
{
    return 1;
}
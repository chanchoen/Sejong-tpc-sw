#include "StsTest.hh"

#include <iostream>
using namespace std;

StsTest::StsTest()
:StsMaker("StsTest", "StsTest")
{
}

bool StsTest::Init() 
{
    cout << "StsTest::Init() --- testtest" << endl;
    return true;
}

bool StsTest::Make() 
{
    return true;
}


bool StsTest::Finish()
{
    return true;
}
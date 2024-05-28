#include "StsTest2.hh"

#include <iostream>
using namespace std;

StsTest2::StsTest2()
:StsMaker("StsTest2", "StsTest2")
{
}

bool StsTest2::Init() 
{
    cout << "StsTest2::Init() --- testtest" << endl;
    return true;
}

bool StsTest2::Make() 
{
    return true;
}


bool StsTest2::Finish()
{
    return true;
}
#include "StsTest2.hh"

#include <iostream>
using namespace std;

StsTest2::StsTest2()
:StsMaker("StsTest2", "StsTest2")
{
}

Int_t StsTest2::Init() 
{
    cout << "StsTest2::Init() --- testtest" << endl;
    return 1;
}

Int_t StsTest2::Make() 
{
    return 1;
}


Int_t StsTest2::Finish()
{
    return 1;
}
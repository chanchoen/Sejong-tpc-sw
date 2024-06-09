#include "StsTPCOnlineMaker.hh"

#include <iostream>
using namespace std;

StsTPCOnlineMaker::StsTPCOnlineMaker()
:StsMaker("StsTPCOnlineMaker", "StsTPCOnlineMaker")
{
}

Int_t StsTPCOnlineMaker::Init() 
{
    cout << "StsTPCOnlineMaker::Init() --- testtest" << endl;
    return 1;
}

Int_t StsTPCOnlineMaker::Make() 
{
    return 1;
}


Int_t StsTPCOnlineMaker::Finish()
{
    return 1;
}
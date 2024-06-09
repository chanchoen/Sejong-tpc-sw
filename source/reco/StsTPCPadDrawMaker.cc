#include "StsTPCPadDrawMaker.hh"

#include <iostream>
using namespace std;

StsTPCPadDrawMaker::StsTPCPadDrawMaker()
:StsMaker("StsTPCPadDrawMaker", "StsTPCPadDrawMaker")
{
}

Int_t StsTPCPadDrawMaker::Init() 
{
    cout << "StsTPCPadDrawMaker::Init() --- testtest" << endl;
    return 1;
}

Int_t StsTPCPadDrawMaker::Make() 
{
    return 1;
}


Int_t StsTPCPadDrawMaker::Finish()
{
    return 1;
}
#ifndef StsUtil_HH
#define StsUtil_HH

#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>

#include "TString.h"
#include "TMath.h"
#include "TVector3.h"

using namespace std;

class StsUtil
{
    public:
        StsUtil();
        ~StsUtil();

    protected:
        queue<TString> GetDAQFileQueue(TString inputFile = "");

    ClassDef(StsUtil, 0)
};

#endif
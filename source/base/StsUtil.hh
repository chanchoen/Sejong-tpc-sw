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

#define TIMEBUCKET 512

class StsUtil
{
    public:
        enum kStageFlag{
            kRawStage = 0,
            kRecoStage = 1
        };

        enum kIoMode{
            kRead = 0, 
            kWrite = 1, 
            kOnline = 2
        };

        // enum kTrigSignal{
            
        // };

        StsUtil();
        virtual ~StsUtil();

    protected:
        queue<TString> GetDAQFileQueue(TString inputFile = "");

};

#endif
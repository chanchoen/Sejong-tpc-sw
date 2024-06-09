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

static enum kStageFlag{
    kRawStage = 0,
    kRecoStage = 1
}kStageFlag;

static enum kIoMode{
    kRead = 0, 
    kWrite = 1, 
    kOnline = 2
}kIoMode;

#define TIMEBUCKET 512
#define TRIGNUM 2
#define EXPNUM 4

static TString kTriggerType[TRIGNUM] = {"GEMTest", "MainRun"};
static TString kExperimentType[EXPNUM] = {"HIMAC", "HIMACTPCGEMGain", "TPCDrumGEMTest", "TPCDrumMainRun"};

typedef std::vector<std::pair<TString, Int_t>> RunList;

class StsUtil
{
    public:
        StsUtil();
        virtual ~StsUtil();

        static TString AddDash(TString path);

        static RunList GetRunList(TString path, TString rejectRun);

        static vector<pair<TString, int>> GetRunPath(TString path);

        queue<tuple<int, int, TString>> GetDAQFileQueue(TString inputFile = "");

    private:
        static vector<Int_t> GetListFromString
};

#endif


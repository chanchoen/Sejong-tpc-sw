#ifndef StsUtil_HH
#define StsUtil_HH

#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>

#include "TROOT.h"
#include "TSystem.h"
#include "TSystemFile.h"
#include "TSystemDirectory.h"
#include "TString.h"
#include "TMath.h"
#include "TVector3.h"
#include "TObjArray.h"
#include "TObjString.h"

using namespace std;

static enum kStageFlag{
    kDaqStage = 0,
    kRawStage = 1,
    kRecoStage = 2
}kStageFlag;

static enum kIoMode{
    kRead = 0, 
    kWrite = 1, 
    kOnline = 2
}kIoMode;

#define TIMEBUCKET 512
#define TRIGNUM 2
#define EXPNUM 4
#define ASADNUM 4

static TString kTriggerType[TRIGNUM] = {"GEMTest", "MainRun"};
static TString kExperimentType[EXPNUM] = {"HIMAC", "HIMACTPCGEMGain", "TPCDrumGEMTest", "TPCDrumMainRun"};

static TString kDataBasePath = "/data/public_data/";
typedef vector<pair<Int_t, vector<TString>>> RunList;
typedef vector<queue<TString>> DAQList;

class StsUtil
{
    public:

        // static enum mInputType{
        //     mIsPath = 0,
        //     mIsList = 1,
        //     mIsFile = 2,
        //     mIsExpName = 3
        // };

        StsUtil();
        virtual ~StsUtil();

        static TString AddDash(TString path);
        static RunList GetRunList(TString input, TString rejectRun, int stage);
        static DAQList GetDAQList(vector<TString> fileList);

    protected:
        static Bool_t CheckRunIDFormat(TString run);
        static RunList RemovedRejectRun(RunList runList, vector<Int_t> rejectRun);

        static vector<Int_t> GetRunsFromString(TString run);
        static RunList GetLines(TString file, int stage);
        static vector<TString> GetDataBaseFile(TString run, int stage);
        static vector<TString> GetDataBaseFile(int runID, int stage);


};

#endif


#ifndef StsDecoder_HH
#define StsDecoder_HH

#include "StsUtil.hh"
#include "StsDAQFrame.hh"
#include "TClonesArray.h"

using namespace std;

class StsDst;
class StsTrigger;

class StsDecoder
{
    public:
        StsDecoder();
        ~StsDecoder();

        Int_t Init();
        Int_t Make();
        Int_t Clear();
        Int_t Finish();

        Int_t SetRunFile(int run, vector<TString> fileList);

        Bool_t SkipEvent();

    private:
        Int_t FileOpen(int asadIdx);
        Int_t ReadHeader(int asadIdx);
        Int_t ReadItem(int asadIdx);
        Int_t FillDst();

        Bool_t mEndOfEvents;

        StsDst* mDst = 0;
        StsTrigger* mTrigger = 0;

        int mAsAdNum;
        StsDAQFrame* mDAQFrame[ASADNUM];

        Int_t mRunNumber;
        DAQList mDAQList;
        std::ifstream mDAQFile[ASADNUM];

        HeaderFrame mHeader;
        ItemFrame mItem;
};

#endif
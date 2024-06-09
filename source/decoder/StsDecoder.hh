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
        StsDecoder(TString filePath = "");
        ~StsDecoder();

        Int_t Init();
        Int_t Make();
        Int_t Clear();
        Int_t Finish();

    private:
        Int_t FileOpen();
        Int_t ReadHeader();
        Int_t ReadItem();
        Int_t FillDst();

        Bool_t mEndOfEvents;

        StsDst* mDst = 0;
        StsTrigger* mTrigger = 0;
        StsDAQFrame* mDAQFrame = 0;

        TString mFilePath;
        queue<tuple<int, int, TString>> mFileQueue;
        std::ifstream mDAQFile;

        HeaderFrame mHeader;
        ItemFrame mItem;
};

#endif
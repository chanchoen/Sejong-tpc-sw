#ifndef StsDecoder_HH
#define StsDecoder_HH

#include "StsUtil.hh"

using namespace std;

class StsDst;
class StsTrigger;
class StsDAQFrame;

class StsDecoder : public StsUtil
{
    public:
        StsDecoder(TString filePath = "");
        ~StsDecoder();

        Int_t Init();
        Int_t Make();
        Int_t Clear();
        Int_t Finish();

    private:
        StsDst* mDst = 0;
        StsTrigger* mTrigger = 0;
        StsDAQFrame* mDAQFrame = 0;

        TString mFilePath;
        queue<TString> mFileQueue;

};

#endif
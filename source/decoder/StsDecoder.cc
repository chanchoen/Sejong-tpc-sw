#include "StsDecoder.hh"

#include "StsChainMaker.hh"
#include "StsDst.hh"
#include "StsTrigger.hh"
#include "StsDAQFrame.hh"

StsDecoder::StsDecoder(TString filePath) 
: mFilePath(filePath)
{

}

StsDecoder::~StsDecoder()
{
    delete mDAQFrame;
    mDAQFrame = 0;
}

Int_t StsDecoder::Init()
{
    mDst = StsChainMaker::GetChainMaker() -> GetDst();
    mTrigger = StsChainMaker::GetChainMaker() -> GetTrigger();

    if(!mTrigger){cout << " StsDecoder::Init() no mTrigger " << endl;}

    mDAQFrame = new StsDAQFrame();

    mFileQueue = GetDAQFileQueue(mFilePath);

    if(!mDst){cout << " StsDecoder::Init() no mDst " << endl;}
    // mDst->GetRunInfo();

    return 1;
}

Int_t StsDecoder::Make()
{
    // HeaderFrame headerFrame = mDAQFrame->GetHeaderFrame();
    // cout << " test " << endl;
    // cout <<  "StsDecoder::Make()" << " " << mTrigger -> GetTPCGeometry() << endl;
    // cout << " test2 " << endl;
    return 1;
}

Int_t StsDecoder::Clear()
{
    return 1;
}
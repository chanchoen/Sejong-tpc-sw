#include "StsDecoder.hh"

#include "StsChainMaker.hh"
#include "StsDst.hh"
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
    mDAQFrame = new StsDAQFrame();

    mFileQueue = GetFileQueue(mFilePath);

    return 1;
}

Int_t StsDecoder::Make()
{
    HeaderFrame headerFrame = mDAQFrame->GetHeaderFrame();

    return 1;
}

Int_t StsDecoder::Clear()
{
    return 1;
}
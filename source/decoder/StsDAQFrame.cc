#include "StsDAQFrame.hh"

StsDAQFrame::StsDAQFrame()
{
}

StsDAQFrame::~StsDAQFrame()
{
}

HeaderFrame StsDAQFrame::GetHeaderFrame(){return mHeaderFrame;}
uint32_t StsDAQFrame::GetItemFrame(){return mItemFrame;}
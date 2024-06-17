#include "StsTPCDrum.hh"
#include "TH2Poly.h"

StsTPCDrum::StsTPCDrum()
{
    mTPCForm = kMainRun;
}

Int_t StsTPCDrum::Init() 
{
    if(mTPCForm == kMainRun){ // for main pad form

    }
    else if(mTPCForm == kGemTestRun){ // for GEM test form
        InitMapping_ZAPtoGEMTest();

        mAsAdNum = 1;
        mChannelNum = 272; // including FPN
        mPadNum = 256;
        mLayerNum = 16;
        mRowNum = 16;
        mPadHeight = 0.;
        mPadWidth = 0.;
        mPadWidth2 = 0.;
        mPadGap = 0.;
    }

    return 1;
}

void StsTPCDrum::SetMainForm(){mTPCForm = kMainRun;}
void StsTPCDrum::SetGemTestForm(){mTPCForm = kGemTestRun;}

Int_t StsTPCDrum::GetAsAdNum(){return mAsAdNum;}
Int_t StsTPCDrum::GetChannelNum(){return mChannelNum;}
Int_t StsTPCDrum::GetPadNum(){return mPadNum;}
Int_t StsTPCDrum::GetLayerNum(){return mLayerNum;}
Int_t StsTPCDrum::GetRowNum(){return mRowNum;}
// Double_t StsTPCDrum::GetPadHeight(int idx);
// Double_t StsTPCDrum::GetPadWidth(int idx);
// Double_t StsTPCDrum::GetPadGap(int idx);


void StsTPCDrum::GetPolyGeometry(TH2Poly* poly)
{

}

void StsTPCDrum::InitMapping_ZAPtoGEMTest()
{
    int layerID = 0;
    int rowID = 0;
    for(int aget=0; aget<AGETNUM; aget++){
        int tmpLayer = aget*4 + 3;
        int tmpRowEven = 8;
        int tmpRowOdd = 8;

        int chanIdx = 0;
        for(int chan=0; chan<CHANNUM; chan++){
            if(StsUtil::IsFPNChannel(chan)){continue;}
            layerID = tmpLayer - int(chanIdx/16);
            
            if(chanIdx%16==0){tmpRowEven = 8; tmpRowOdd = 8;}

            if(chanIdx%2==0){
                rowID = tmpRowEven;
                tmpRowEven++;
            }
            if(chanIdx%2==1){
                tmpRowOdd--;
                rowID = tmpRowOdd;
            }

            mMapChanGEMTest.insert({make_pair(aget, chanIdx), make_pair(layerID, rowID)});
            chanIdx++;
        }
    }
}

void StsTPCDrum::InitMapping_ZAPtoMainRun()
{
    // int xId = 0;
    // int yId = 0;

    // for (int agetId = 0; agetId < 4; agetId++) {
    //     xId = 16;
    //     yId = 6 - (2 * agetId);

    //     int nChanId = 0;
    //     int padSorterIdx = 0;
    //     for (int chanId = 0; chanId < 68; chanId++) {
    //         if (chanId == 11 || chanId == 22 || chanId == 45 || chanId == 56) continue;
    //         nChanId++;
    //         int idxFPN = (nChanId - 1) / 16;
    //         if (chanId == 33 || chanId == 34 || chanId == 35) {
    //             xId = 0;
    //             if (chanId == 34) {
    //                 xId = 1;
    //                 yId++;
    //                 padSorterIdx = 14;
    //             }
    //             this->agetId_[xId][yId] = agetId;
    //             this->chanId_[xId][yId] = chanId;
    //             this->xId_[agetId][chanId] = xId;
    //             this->yId_[agetId][chanId] = yId;
    //             continue;
    //         }

    //         int sign = -1;
    //         if (nChanId % 2 == 0) {
    //             sign = 1;
    //             padSorterIdx++;
    //         } else if (chanId >= 38) {
    //             padSorterIdx -= 2;
    //         }
    //         xId = 16 + sign * (padSorterIdx);
    //         this->agetId_[xId][yId] = agetId;
    //         this->chanId_[xId][yId] = chanId;
    //         this->xId_[agetId][chanId] = xId;
    //         this->yId_[agetId][chanId] = yId;
    //     }
    // }    
}


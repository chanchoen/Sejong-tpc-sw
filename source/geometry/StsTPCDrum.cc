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
        mPadHeight = 12.0; // [mm]
        mPadWidth = 12.0; // [mm]
        mPadWidth2 = 0.; // [mm]
        mPadGap = 0.5; // [mm]
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

Int_t StsTPCDrum::GetLayerID(int padID)
{
    if(mPadMap_padID.find(padID) == mPadMap_padID.end()){return -1;}
    return mPadMap_padID[padID].first;
}

Int_t StsTPCDrum::GetLayerID(int aget, int chan)
{
    if(mPadMap.find(make_pair(aget, chan)) == mPadMap.end()){return -1;}
    return mPadMap[make_pair(aget, chan)].first;
}

Int_t StsTPCDrum::GetRowID(int padID)
{
    if(mPadMap_padID.find(padID) == mPadMap_padID.end()){return -1;}
    return mPadMap_padID[padID].second;
}

Int_t StsTPCDrum::GetRowID(int aget, int chan)
{
    if(mPadMap.find(make_pair(aget, chan)) == mPadMap.end()){return -1;}
    return mPadMap[make_pair(aget, chan)].second;
}


Double_t StsTPCDrum::GetX(int padID)
{
    double row = double(GetRowID(padID));
    return row * (GetPadWidth(padID)+GetPadGap());
}

// Double_t StsTPCDrum::GetX(int layer, int chan)
// {
//     double row = double(GetRowID(aget, chan));
//     return row * (GetPadWidth(aget, chan)+GetPadGap(padID));
// }

Double_t StsTPCDrum::GetY(int padID)
{
    double layer = double(GetLayerID(padID));
    return layer * (GetPadHeight(padID)+GetPadGap());
}

// Double_t StsTPCDrum::GetY(int layer, int row);

Double_t StsTPCDrum::GetPadHeight(int padID){return mPadHeight;}
Double_t StsTPCDrum::GetPadWidth(int padID){return mPadWidth;}
Double_t StsTPCDrum::GetPadGap(){return mPadGap;}


TH2Poly* StsTPCDrum::GetPolyGeometry()
{
    TH2Poly* polyGeo = new TH2Poly();

    double boundaryX[5];
    double boundaryY[5];
    for(int pad=0; pad<mPadNum; pad++){
        double centerX = GetX(pad);
        double centerY = GetY(pad);

        for(int i=0; i<5; i++){
            double xSign = (i<2 || i==4)? -1. : +1.;
            double ySign = (i==1 || i==2)? -1. : +1.;
            boundaryX[i] = centerX + xSign*GetPadWidth(pad)/2.;
            boundaryY[i] = centerY + ySign*GetPadHeight(pad)/2.;
        }

        polyGeo -> AddBin(5, boundaryX, boundaryY);
    }

    polyGeo -> GetZaxis()->SetRangeUser(0., 4095.);

    double padHeight = GetPadHeight(0); 
    double padWidth = GetPadWidth(0); 
    double padGap = GetPadGap();

    double boundaXLeft = 200./2. - ((double(GetRowNum())/2. - 1./2.)*padWidth + (double(GetRowNum()/2-1) + 1./2.)*padGap);
    double boundaXRight = 200./2. + ((double(GetRowNum())/2.- 1./2.)*padWidth + (double(GetRowNum()/2-1) + 1./2.)* padGap);

    double boundaYDown = 200./2. - ((double(GetLayerNum())/2.- 1./2.)*padHeight + (double(GetLayerNum()/2-1) + 1./2.)*padGap);
    double boundaYUp = 200./2. + ((double(GetLayerNum())/2.- 1./2.)*padHeight + (double(GetLayerNum()/2-1) + 1./2.)*padGap);

    polyGeo -> GetXaxis()->SetRangeUser(-1.*boundaXLeft, boundaXRight);
    polyGeo -> GetYaxis()->SetRangeUser(-1.*boundaYDown, boundaYUp);

    return polyGeo;
}

void StsTPCDrum::InitMapping_ZAPtoGEMTest()
{
    int layerID = 0;
    int rowID = 0;
    int padID = 0;
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

            mPadMap.insert({make_pair(aget, chanIdx), make_pair(layerID, rowID)});
            mPadMap_padID.insert({padID,  make_pair(layerID, rowID)});
            chanIdx++;
            padID++;
        }
    }
}
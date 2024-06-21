#ifndef StsTPCDrum_HH
#define StsTPCDrum_HH

#include "StsUtil.hh"

class TH2Poly;

using namespace std;

class StsTPCDrum
{
    enum TPCForm{
        kMainRun = 0,
        kGemTestRun = 1
    };

    public:
        StsTPCDrum();
        ~StsTPCDrum() {};

        Int_t Init();

        void SetGemTestForm();
        void SetMainForm();

        Int_t GetAsAdNum();
        Int_t GetChannelNum();
        Int_t GetPadNum();
        Int_t GetLayerNum();
        Int_t GetRowNum();

        Int_t GetLayerID(int padID);
        Int_t GetLayerID(int aget, int chan);
        Int_t GetRowID(int padID);
        Int_t GetRowID(int aget, int chan);

        Double_t GetX(int padID);
        // Double_t GetX(int aget, int chan);
        Double_t GetY(int padID);
        // Double_t GetY(int aget, int chan);

        Double_t GetPadHeight(int padID);
        Double_t GetPadWidth(int padID);
        Double_t GetPadGap();

        TH2Poly* GetPolyGeometry();

    private:
        void InitMapping_ZAPtoGEMTest();
        void InitMapping_ZAPtoMainRun();

        Bool_t mTPCForm;

        Int_t mAsAdNum;
        Int_t mChannelNum;
        Int_t mPadNum;
        Int_t mLayerNum;
        Int_t mRowNum;
        Double_t mPadHeight;
        Double_t mPadWidth;
        Double_t mPadWidth2;
        Double_t mPadGap;

        map<pair<int, int>, pair<int, int>> mPadMap; // (aget, chan<68), (layer, row)
        map<int, pair<int, int>> mPadMap_padID; // (padID<256), (layer, row)
};

#endif

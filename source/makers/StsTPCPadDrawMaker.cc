#include "StsTPCPadDrawMaker.hh"
#include "TApplication.h"

using namespace std;

StsTPCPadDrawMaker::StsTPCPadDrawMaker()
:StsMaker("StsTPCPadDrawMaker", "StsTPCPadDrawMaker")
{
}

Int_t StsTPCPadDrawMaker::Init() 
{
    mDst = StsChainMaker::GetChainMaker() -> GetDst();
    mTrigger = StsChainMaker::GetChainMaker() -> GetTrigger();
    mTPC = mTrigger -> GetTPCGeometry();
    mPolyPad = mTrigger->GetTPCGeometry()->GetPolyGeometry();
    mPolyPad -> SetStats(0);
    // mPolyPad -> GetZaxis()->SetRangeUser(0., 4000.);

    mCanvas = new TCanvas("","",600, 600);
    // mHisto = new TH1D("test","",100,0,4000);

    cout << " StsTPCPadDrawMaker::Init() " << GetName() << endl;
    return 1;
}

Int_t StsTPCPadDrawMaker::Make() 
{
    int eventID = mDst->GetEventInfo()->GetEventNumber();
    mPolyPad -> SetTitle(Form("Run %i, Event %i TPC Drum;x [mm];y [mm]", 1, eventID));
    // mPolyPad -> ClearBinContents();

    StsRawTPCPad* rawPad;
    StsRawTPCPad* rawPadFPN;

    int padID=0;
    for(int chan=0; chan<mTPC->GetChannelNum(); chan++){
        rawPad = mDst->GetRawTPCPad(chan);
        int chanID = rawPad->GetChannelID();
        if(StsUtil::IsFPNChannel(chanID)){continue;}
        // rawPadFPN = mDst->GetRawTPCPad(StsUtil::GetFPNChannelID(chanID));

        double maxADC = 0.;
        for(int tb=0; tb<512; tb++){
            double adc = rawPad->GetADC(tb);
            // double fpn = rawPadFPN -> GetADC(tb);
            // adc = adc - fpn;
            if(maxADC < adc){maxADC = adc;}
        }
        double x = mTPC->GetX(padID);
        double y = mTPC->GetY(padID);
        // if(maxADC>400){mPolyPad -> SetBinContent(padID+1, double(maxADC));}

        if(maxADC>400){mPolyPad -> Fill(x,y);}
        // if(maxADC > 400){mPolyPad -> Fill(x,y, maxADC);}
        // mHisto -> Fill(maxADC);

        padID++;
    }
    mCanvas -> cd();
    mPolyPad -> Draw("colz, text");
    // gPad -> SetLogy();
    // mHisto -> Draw();
    mCanvas -> Draw();
    // mCanvas -> SaveAs(Form("./picture/test%i.pdf", eventID));


    return 1;
}

Int_t StsTPCPadDrawMaker::Finish()
{
    mCanvas -> cd();
    mPolyPad -> Draw("colz, text");
    // gPad -> SetLogy();
    // mHisto -> Draw();
    mCanvas -> Update();
    mCanvas -> SaveAs(Form("./picture/test.pdf"));

    return 1;
}
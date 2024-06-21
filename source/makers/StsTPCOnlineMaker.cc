#include "StsTPCOnlineMaker.hh"
#include "TApplication.h"

using namespace std;

StsTPCOnlineMaker::StsTPCOnlineMaker()
:StsMaker("StsTPCOnlineMaker", "StsTPCOnlineMaker")
{
}

Int_t StsTPCOnlineMaker::Init() 
{
    mDst = StsChainMaker::GetChainMaker() -> GetDst();
    mTrigger = StsChainMaker::GetChainMaker() -> GetTrigger();
    mTPC = mTrigger -> GetTPCGeometry();
    mPolyPad = mTrigger->GetTPCGeometry()->GetPolyGeometry();
    mPolyPad -> SetStats(0);
    mCanvas = new TCanvas("","",600, 600);
    
    return 1;
}

Int_t StsTPCOnlineMaker::Make() 
{
    int eventID = mDst->GetEventInfo()->GetEventNumber();
    cout << " StsTPCOnlineMaker::make() " << eventID << endl;
    mPolyPad -> SetTitle(Form("Run %i, Event %i TPC Drum;x [mm];y [mm]", 1, eventID));
    mPolyPad -> ClearBinContents();

    StsRawTPCPad* rawPad;
    StsRawTPCPad* rawPadFPN;

    int padID=0;
    for(int chan=0; chan<mTPC->GetChannelNum(); chan++){
        rawPad = mDst->GetRawTPCPad(chan);
        int chanID = rawPad->GetChannelID();
        if(StsUtil::IsFPNChannel(chanID)){continue;}
        rawPadFPN = mDst->GetRawTPCPad(StsUtil::GetFPNChannelID(chanID));

        double maxADC = 0.;
        for(int tb=0; tb<512; tb++){
            double adc = rawPad->GetADC(tb);
            double fpn = rawPadFPN -> GetADC(tb);
            adc = adc - fpn;
            if(maxADC < adc){maxADC = adc;}
        }
        mPolyPad -> SetBinContent(padID+1, double(maxADC));
        padID++;
    }

    mCanvas -> cd();
    mPolyPad -> Draw("colz, text");
    mCanvas -> Draw();

    return 1;
}


Int_t StsTPCOnlineMaker::Finish()
{
    return 1;
}
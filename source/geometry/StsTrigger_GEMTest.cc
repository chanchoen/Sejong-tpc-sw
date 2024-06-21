#include "StsTrigger_GEMTest.hh"

StsTrigger_GEMTest::StsTrigger_GEMTest()
{
    Init();
}

StsTrigger_GEMTest::~StsTrigger_GEMTest()
{
    delete mTPC;
    mTPC = 0;
}

Int_t StsTrigger_GEMTest::Init() 
{
    mTPC = new StsTPCDrum();
    mTPC -> SetGemTestForm();
    mTPC -> Init();
}
Int_t StsTrigger_GEMTest::GetCoBoNum(){return mCoBoNum;}
Int_t StsTrigger_GEMTest::GetAsAdNum(){return mAsAdNum;}

StsTPCDrum* StsTrigger_GEMTest::GetTPCGeometry(){return mTPC;}

Int_t StsTrigger_GEMTest::FillData(StsDst* dst, StsDAQFrame* frame)
{
    StsRawTPCPad* rawPad = 0;
    for(int asadIdx=0; asadIdx<mAsAdNum; asadIdx++){
        int tmpChannelIdx = 0;
        int padID = 0;
        for(int agetIdx=0; agetIdx<nAGET; agetIdx++){
            for(int chanIdx=0; chanIdx<nCHAN; chanIdx++){
                rawPad = dst->GetRawTPCPad(tmpChannelIdx);
                rawPad -> SetAgetID(agetIdx);
                rawPad -> SetChannelID(chanIdx);

                rawPad -> SetADC(frame[asadIdx].mADC[agetIdx][chanIdx]);

                tmpChannelIdx++;

                if(StsUtil::IsFPNChannel(chanIdx)){
                    rawPad -> SetPadID(-1);
                    continue;
                }
                rawPad -> SetPadID(padID);
                padID++;
            }
        }
    }
    
    return 1;
}
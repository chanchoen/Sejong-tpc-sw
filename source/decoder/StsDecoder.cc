#include "StsDecoder.hh"

#include "StsChainMaker.hh"
#include "StsDst.hh"
#include "StsTrigger.hh"

StsDecoder::StsDecoder() 
: mEndOfEvents(false), mRunNumber(0), mAsAdNum(0)
{
}

StsDecoder::~StsDecoder()
{
    for(int i=0; i<mAsAdNum; i++){
        if(mDAQFrame[i]){
            delete mDAQFrame[i];
            mDAQFrame[i] = 0;
        }
    }
}

Int_t StsDecoder::Init()
{
    mDst = StsChainMaker::GetChainMaker() -> GetDst();
    mTrigger = StsChainMaker::GetChainMaker() -> GetTrigger();

    mAsAdNum = mTrigger->GetAsAdNum();
    for(int i=0; i<mAsAdNum; i++){
        if(!mDAQFrame[i]){mDAQFrame[i] = new StsDAQFrame();}

        if(mDAQFrame[i]){
            mDAQFrame[i] -> Clear();
            mDAQFrame[i] -> mPrevTime = 0;
        }
    }

    return 1;
}

Int_t StsDecoder::Make()
{
    for(int i=0; i<mAsAdNum; i++){
        if(!FileOpen(i)){return 0;}

        mDAQFrame[i] -> Clear();
        
        ReadHeader(i);
        ReadItem(i);

        cout << " test StsDecoder::Make() " << i << " " << mDAQFrame[i]->mEventID << " " << endl; 
    }
    if(!SkipEvent()){return 1;}


    FillDst();

    return 1;
}

Int_t StsDecoder::Clear()
{
    return 1;
}

Int_t StsDecoder::SetRunFile(int run, vector<TString> fileList)
{
    mRunNumber = run;
    mDAQList = StsUtil::GetDAQList(fileList);

}

Int_t StsDecoder::FileOpen(int asadIdx)
{
    if(!mDAQList[asadIdx].empty() && !mDAQFile[asadIdx].is_open()){
        mDAQFile[asadIdx].open(mDAQList[asadIdx].front().Data(), std::ios::binary);

        if(!mDAQFile[asadIdx].is_open()){
            cout << "StsDecoder::FileOpen() --- Error: " << mDAQList[asadIdx].front().Data() << " can not open !!!" << endl;
            cout << "StsDecoder::FileOpen() --- " << mDAQList[asadIdx].front().Data() << " to be skipped..." << endl;
            mDAQFile[asadIdx].close();
            mDAQList[asadIdx].pop();
            FileOpen(asadIdx);

            return 1;
        }
        mDAQList[asadIdx].pop();

        return 1;
    }
    if(mDAQList[asadIdx].empty() && mDAQFile[asadIdx].eof()){
        cout << "StsDecoder::FileOpen() --- End of Run: " << mRunNumber << endl;
        mDAQFile[asadIdx].close();
        return 0;
    }
    if(!mDAQList[asadIdx].empty() && mDAQFile[asadIdx].eof()){
        cout << "StsDecoder::FileOpen() --- End of File... Next to file" << endl;
        mDAQFile[asadIdx].close();
        FileOpen(asadIdx);
        return 1;
    }
    return 1;
}

Int_t StsDecoder::ReadHeader(int asadIdx)
{
    mDAQFile[asadIdx].read((char*)&(mHeader), sizeof(mHeader));

    mDAQFrame[asadIdx] -> mMetaType = (int)pow(2, (int)mHeader.metaType);
    mDAQFrame[asadIdx] -> mFrameSize = (int)((mHeader.frameSize[0] << 16) | (mHeader.frameSize[1] << 8) | (mHeader.frameSize[2]));
    mDAQFrame[asadIdx] -> mDataSource = (int)mHeader.dataSource;
    mDAQFrame[asadIdx] -> mFrameType = (int)((mHeader.frameType[0] << 8) | mHeader.frameType[1]);
    mDAQFrame[asadIdx] -> mRevision = (int)mHeader.revision;
    mDAQFrame[asadIdx] -> mHeaderSize = (int)((mHeader.headerSize[0] << 8) | mHeader.headerSize[1]) * mDAQFrame[asadIdx] -> mMetaType;
    mDAQFrame[asadIdx] -> mItemSize = (int)((mHeader.itemSize[0] << 8) | mHeader.itemSize[1]);
    mDAQFrame[asadIdx] -> mNitems = (int)((mHeader.nItems[0] << 24) | (mHeader.nItems[1] << 16) | (mHeader.nItems[2] << 8) | (mHeader.nItems[3]));
    mDAQFrame[asadIdx] -> mEventTime = (((uint64_t)mHeader.eventTime[0] << 40) | ((uint64_t)mHeader.eventTime[1] << 32) |
                             ((uint64_t)mHeader.eventTime[2] << 24) | ((uint64_t)mHeader.eventTime[3] << 16) |
                             ((uint64_t)mHeader.eventTime[4] << 8) | ((uint64_t)mHeader.eventTime[5]));

    mDAQFrame[asadIdx] -> mEventID = ((mHeader.eventId[0] << 24) | (mHeader.eventId[1] << 16) | (mHeader.eventId[2] << 8) | (mHeader.eventId[3]));
    mDAQFrame[asadIdx] -> mCoboID = (int)mHeader.coboId;
    mDAQFrame[asadIdx] -> mAsadID = (int)mHeader.asadId;
    mDAQFrame[asadIdx] -> mReadOffset = (int)((mHeader.readOffset[0] << 8) | mHeader.readOffset[1]);
    mDAQFrame[asadIdx] -> mStatus = (int)mHeader.status;

    mDAQFrame[asadIdx] -> mDiffTime = mDAQFrame[asadIdx] -> mEventTime - mDAQFrame[asadIdx] -> mPrevTime;
    if(mDAQFrame[asadIdx] -> mEventID == 0){mDAQFrame[asadIdx] -> mDiffTime = 0;}
    mDAQFrame[asadIdx] -> mPrevTime = mDAQFrame[asadIdx] -> mEventTime;

    int chanID = 0;
    for(int i=0; i<9; i++){
        for(int shift=7; shift>=0; shift--){
            if (chanID == 0) shift = 3;
            mDAQFrame[asadIdx] -> mIsHit[0][chanID] = mHeader.hitPat_0[i] & (1 << shift) ? true : false;
            mDAQFrame[asadIdx] -> mIsHit[1][chanID] = mHeader.hitPat_1[i] & (1 << shift) ? true : false;
            mDAQFrame[asadIdx] -> mIsHit[2][chanID] = mHeader.hitPat_2[i] & (1 << shift) ? true : false;
            mDAQFrame[asadIdx] -> mIsHit[3][chanID] = mHeader.hitPat_3[i] & (1 << shift) ? true : false;
            chanID++;
        }
    }

    uint8_t waste;
    for(int i=0; i<(mDAQFrame[asadIdx]->mHeaderSize - sizeof(mHeader)); i++){
        mDAQFile[asadIdx].read((char*)&waste, sizeof(uint8_t));
    }

    return 1;
}

Int_t StsDecoder::ReadItem(int asadIdx)
{
    if(mDAQFrame[asadIdx] -> mFrameType == 1){
        // Partial readout mode
        // Frame Item Format:     aacc cccc | cbbb bbbb | bb00 ssss | ssss ssss
        // Read in reverse order: ssss ssss | bb00 ssss | cbbb bbbb | aacc cccc
        // a: agetID, c: chanID, b: buckID, s: sample, 0: empty

        int agetID, chanID, buckID, sample;
        int chanIDLowerBits, chanIDUpperBits;
        int buckIDLowerBits, buckIDUpperBits;
        int sampleLowerBits, sampleUpperBits;

        for(int itemId=0; itemId < mDAQFrame[asadIdx] -> mNitems; itemId++) {
            mDAQFile[asadIdx].read((char*)&(mItem), sizeof(uint32_t));

            // Read agetID
            agetID = (mItem.items >> 6) & 0x03;

            // Read chanID
            chanIDLowerBits = (mItem.items >> 15) & 0x01;
            chanIDUpperBits = mItem.items & 0x3f;
            chanID = (chanIDUpperBits << 1) | chanIDLowerBits;

            // Read buckID
            buckIDLowerBits = (mItem.items >> 22) & 0x03;
            buckIDUpperBits = (mItem.items >> 8) & 0x7f;
            buckID = (buckIDUpperBits << 2) | buckIDLowerBits;

            // Read sample
            sampleLowerBits = (mItem.items >> 24) & 0xff;
            sampleUpperBits = (mItem.items >> 16) & 0x0f;
            sample = (sampleUpperBits << 8) | sampleLowerBits;
            mDAQFrame[asadIdx] -> mADC[agetID][chanID][buckID] = sample;
        }
    } 
    else if(mDAQFrame[asadIdx] -> mFrameType == 2){
        // Full readout mode
        // Frame Item Format:     aa00 ssss | ssss ssss | aa00 ssss | ssss ssss
        // Read in reverse order: ssss ssss | aa00 ssss | ssss ssss | aa00 ssss
        // a: agetID, s: sample, 0: empty

        int sample, sampleLowerBits, sampleUpperBits;

        for(int buckID=0; buckID<nBUCK; buckID++){
            for (int chanID=0; chanID<nCHAN; chanID += 2){
                for (int agetID=0; agetID<nAGET; agetID++){
                    mDAQFile[asadIdx].read((char *)&(mItem), sizeof(uint32_t));

                    // Read sample 1
                    sampleLowerBits = (mItem.items >> 8) & 0xff;
                    sampleUpperBits = mItem.items & 0x0f;
                    sample = (sampleUpperBits << 8) | sampleLowerBits;
                    mDAQFrame[asadIdx] -> mADC[agetID][chanID][buckID] = sample;
                    
                    // Read sample 2
                    sampleLowerBits = (mItem.items >> 24) & 0xff;
                    sampleUpperBits = (mItem.items >> 16) & 0x0f;
                    sample = (sampleUpperBits << 8) | sampleLowerBits;
                    mDAQFrame[asadIdx] -> mADC[agetID][chanID + 1][buckID] = sample;
                }
            }
        }
    }

    return 1;
}

Int_t StsDecoder::FillDst()
{
    


    return 1;
}

Bool_t StsDecoder::SkipEvent()
{
    // if(mDAQFrame -> mDiffTime < 10){return 0;}

    return 1;
}
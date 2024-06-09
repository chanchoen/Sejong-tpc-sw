#include "StsDecoder.hh"

#include "StsChainMaker.hh"
#include "StsDst.hh"
#include "StsTrigger.hh"

StsDecoder::StsDecoder(TString filePath) 
: mFilePath(filePath), mEndOfEvents(false)
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

    mDAQFrame = new StsDAQFrame();
    // mFileQueue = GetDAQFileQueue(mFilePath);

    return 1;
}

Int_t StsDecoder::Make()
{
    if(!FileOpen()){return 0;}

    mDAQFrame -> Clear();
    
    ReadHeader();
    ReadItem();

    cout << "eventID " << mDAQFrame->mEventID << " " << mDAQFrame->mEventTime << " " << mDAQFrame->mStatus << endl;;

    FillDst();

    return 1;
}

Int_t StsDecoder::Clear()
{
    return 1;
}

Int_t StsDecoder::FileOpen()
{
    // cout << "StsDecoder::FileOpen() " << endl;
    // if(!mFileQueue.empty() && !mDAQFile.is_open()){
    //     mDAQFile.open(mFileQueue.front().Data(), std::ios::binary);

    //     if(!mDAQFile.is_open()){
    //         cout << "StsDecoder::FileOpen() --- Error: " << mFileQueue.front().Data() << " can not opend!!!" << endl;
    //         cout << "StsDecoder::FileOpen() --- " << mFileQueue.front().Data() << " to be skiped..." << endl;
    //         mFileQueue.pop();
    //         FileOpen();

    //         return 1;
    //     }
    //     mFileQueue.pop();

    //     return 1;
    // }
    // if(mFileQueue.empty() && mDAQFile.eof()){
    //     cout << "StsDecoder::FileOpen() --- End of Decoding" << endl;
    //     mDAQFile.close();
    //     return 0;
    // }
    // if(!mFileQueue.empty() && mDAQFile.eof()){
    //     cout << "StsDecoder::FileOpen() --- End of File... Next to file" << endl;
    //     mDAQFile.close();
    //     FileOpen();
    //     return 1;
    // }
    // return 1;
}

Int_t StsDecoder::ReadHeader()
{
    mDAQFile.read((char*)&(mHeader), sizeof(mHeader));

    mDAQFrame -> mMetaType = (int)pow(2, (int)mHeader.metaType);
    mDAQFrame -> mFrameSize = (int)((mHeader.frameSize[0] << 16) | (mHeader.frameSize[1] << 8) | (mHeader.frameSize[2]));
    mDAQFrame -> mDataSource = (int)mHeader.dataSource;
    mDAQFrame -> mFrameType = (int)((mHeader.frameType[0] << 8) | mHeader.frameType[1]);
    mDAQFrame -> mRevision = (int)mHeader.revision;
    mDAQFrame -> mHeaderSize = (int)((mHeader.headerSize[0] << 8) | mHeader.headerSize[1]) * mDAQFrame -> mMetaType;
    mDAQFrame -> mItemSize = (int)((mHeader.itemSize[0] << 8) | mHeader.itemSize[1]);
    mDAQFrame -> mNitems = (int)((mHeader.nItems[0] << 24) | (mHeader.nItems[1] << 16) | (mHeader.nItems[2] << 8) | (mHeader.nItems[3]));
    mDAQFrame -> mEventTime = (((uint64_t)mHeader.eventTime[0] << 40) | ((uint64_t)mHeader.eventTime[1] << 32) |
                             ((uint64_t)mHeader.eventTime[2] << 24) | ((uint64_t)mHeader.eventTime[3] << 16) |
                             ((uint64_t)mHeader.eventTime[4] << 8) | ((uint64_t)mHeader.eventTime[5]));

    mDAQFrame -> mEventID = ((mHeader.eventId[0] << 24) | (mHeader.eventId[1] << 16) | (mHeader.eventId[2] << 8) | (mHeader.eventId[3]));
    mDAQFrame -> mCoboID = (int)mHeader.coboId;
    mDAQFrame -> mAsadID = (int)mHeader.asadId;
    mDAQFrame -> mReadOffset = (int)((mHeader.readOffset[0] << 8) | mHeader.readOffset[1]);
    mDAQFrame -> mStatus = (int)mHeader.status;

    int chanID = 0;
    for(int i=0; i<9; i++){
        for(int shift=7; shift>=0; shift--){
            if (chanID == 0) shift = 3;
            mDAQFrame -> mIsHit[0][chanID] = mHeader.hitPat_0[i] & (1 << shift) ? true : false;
            mDAQFrame -> mIsHit[1][chanID] = mHeader.hitPat_1[i] & (1 << shift) ? true : false;
            mDAQFrame -> mIsHit[2][chanID] = mHeader.hitPat_2[i] & (1 << shift) ? true : false;
            mDAQFrame -> mIsHit[3][chanID] = mHeader.hitPat_3[i] & (1 << shift) ? true : false;
            chanID++;
        }
    }

    uint8_t waste;
    for(int i=0; i<(mDAQFrame->mHeaderSize - sizeof(mHeader)); i++){
        mDAQFile.read((char*)&waste, sizeof(uint8_t));
    }

    return 1;
}

Int_t StsDecoder::ReadItem()
{
    if(mDAQFrame -> mFrameType == 1){
        // Partial readout mode
        // Frame Item Format:     aacc cccc | cbbb bbbb | bb00 ssss | ssss ssss
        // Read in reverse order: ssss ssss | bb00 ssss | cbbb bbbb | aacc cccc
        // a: agetID, c: chanID, b: buckID, s: sample, 0: empty

        int agetID, chanID, buckID, sample;
        int chanIDLowerBits, chanIDUpperBits;
        int buckIDLowerBits, buckIDUpperBits;
        int sampleLowerBits, sampleUpperBits;

        for(int itemId=0; itemId < mDAQFrame -> mNitems; itemId++) {
            mDAQFile.read((char*)&(mItem), sizeof(uint32_t));

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
            mDAQFrame -> mADC[agetID][chanID][buckID] = sample;
        }
    } 
    else if(mDAQFrame -> mFrameType == 2){
        // Full readout mode
        // Frame Item Format:     aa00 ssss | ssss ssss | aa00 ssss | ssss ssss
        // Read in reverse order: ssss ssss | aa00 ssss | ssss ssss | aa00 ssss
        // a: agetID, s: sample, 0: empty

        int sample, sampleLowerBits, sampleUpperBits;

        for(int buckID=0; buckID<nBUCK; buckID++){
            for (int chanID=0; chanID<nCHAN; chanID += 2){
                for (int agetID=0; agetID<nAGET; agetID++){
                    mDAQFile.read((char *)&(mItem), sizeof(uint32_t));

                    // Read sample 1
                    sampleLowerBits = (mItem.items >> 8) & 0xff;
                    sampleUpperBits = mItem.items & 0x0f;
                    sample = (sampleUpperBits << 8) | sampleLowerBits;
                    mDAQFrame -> mADC[agetID][chanID][buckID] = sample;
                    
                    // Read sample 2
                    sampleLowerBits = (mItem.items >> 24) & 0xff;
                    sampleUpperBits = (mItem.items >> 16) & 0x0f;
                    sample = (sampleUpperBits << 8) | sampleLowerBits;
                    mDAQFrame -> mADC[agetID][chanID + 1][buckID] = sample;
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
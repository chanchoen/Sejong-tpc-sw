#include "StsChainMaker.hh"

#include "StsDecoder.hh"

#include "StsDst.hh"
#include "StsRunInfo.hh"

#include "StsTrigger.hh"
#include "StsTrigger_GEMTest.hh"

StsChainMaker* StsChainMaker::mInstance = nullptr;

StsChainMaker* StsChainMaker::GetChainMaker() {
  if (mInstance != nullptr)
    return mInstance;
  return new StsChainMaker();
}

StsChainMaker::StsChainMaker(int ioMode, const char* fileName) 
: StsMaker("StsChainMaker", "StsChainMaker"), mIoMode(ioMode), mInputFileName(fileName)
{
    mFlag = true;
    mTrigDate = "";
    mDAQFile = "";
    mInputFileName = "";
    mOutputFileName = "StsDst";
    mNFiles = -1;
    mEventNum = -1;

    mStsDstArray = 0;
    mDst = 0;
    mTrigGeo = 0;
}

StsChainMaker::~StsChainMaker()
{
}

Int_t StsChainMaker::Init() 
{  
    if(mIoMode==ioRead){
        cout << "StsChainMaker::Init() -- begin StsChainMaker construction for Read mode" << endl;
        if(InitRead() == false){mFlag = false; return 0;}
    }
    else if(mIoMode==ioWrite){
        cout << "StsChainMaker::Init() -- begin StsChainMaker construction for Write mode" << endl;
        if(InitWrite() == false){mFlag = false; return 0;}
    }
    cout << "StsChainMaker::Init()  --- test " << endl;


    InitMakers();

    return 1;
}

Int_t StsChainMaker::Make() 
{
    cout << "StsChainMaker::Make()" << endl;

    if(mIoMode==ioRead){
        ReadMake();
    }
    else if(mIoMode==ioWrite){
        WriteMake();
    }



    TIter iter(GetListOfTasks());
    StsMaker* maker;
    while ( (maker = dynamic_cast<StsMaker*>(iter())) ) {
        cout << "StsChainMaker::Make() --- test " << maker -> GetName() << "." << endl;
        maker -> Make();
    }

    mEventNum++;
    return 1;
}

Int_t StsChainMaker::Finish() 
{
    if(mIoMode==ioWrite){
        cout << Form("StsChainMaker::Finish() -- Writing and closing %s",mOutputFileName.Data()) << endl;
        mTFile -> cd();
        mTree -> Write();
        mTFile -> Close();
    }

    return 1;
}

Int_t StsChainMaker::Clear()
{
    mStsDstArray -> Clear("C");
    mDst = (StsDst*)mStsDstArray -> ConstructedAt(0); // test
    mDecoder -> Clear();

    return 1;
}

StsDst* StsChainMaker::GetDst(){return mDst;}
StsTrigger* StsChainMaker::GetTrigger(){return mTrigGeo;}

void StsChainMaker::SetDAQFiles(TString file){mDAQFile = file;}
void StsChainMaker::SetTriggerDate(TString date){mTrigDate = date;}
void StsChainMaker::SetEventNum(Int_t eventNum){mEventNum = eventNum;}



// StRHICfPi0Events* StsChainMaker::getRHICfPi0Events(Int_t idx)
// {
//     if(idx >= mChain->GetEntries()){cout << "StsChainMaker::getRHICfPi0Events() -- wrong index !! " << endl;}
//     mChain -> GetEntry(idx);
//     StRHICfPi0Events* rhicfPi0Events = (StRHICfPi0Events*)mReadDataArray -> At(0);
//     return rhicfPi0Events;
// }

// Int_t StsChainMaker::getAnalEntries(){return mChain->GetEntries();}

Int_t StsChainMaker::InitRead()
{
//     mNFiles = 0;
//     if(mInputFileName.Length() == 0){
//         // No input file
//         cout << "StsChainMaker::openRead() --- Input file is not a existing ... " << endl;
//         return kStErr;
//     }
//     else{
//         if(!mChain){mChain = new TChain("StsData");}

//         std::string const dirFile = mInputFileName.Data();
//         if( dirFile.find(".list") != std::string::npos || dirFile.find(".lis") != std::string::npos ){
//             std::ifstream inputStream( dirFile.c_str() );
//             if(!inputStream) {cout << "StsChainMaker::openRead() --- ERROR: Cannot open list file " << dirFile << endl;}

//             std::string file;
//             size_t pos;
//             while(getline(inputStream, file)){
//                 pos = file.find_first_of(" ");
//                 if (pos != std::string::npos ) file.erase(pos,file.length()-pos);
//                 if(file.find("StsData") != std::string::npos) {
//                     TFile* ftmp = TFile::Open(file.c_str());
//                     if(ftmp && !ftmp->IsZombie() && ftmp->GetNkeys()) {
//                         cout << " Read in AnalRHICfPi0 file " << file << endl;
//                         mChain->Add(file.c_str());
//                         ++mNFiles;
//                     } 
//                     if (ftmp) {
//                         ftmp->Close();
//                     } 
//                 }
//             }
//             cout << " Total " << mNFiles << " files have been read in. " << endl;
//         }
//         else if(dirFile.find("AnalRHICfPi0") != std::string::npos){
//             mChain->Add(dirFile.c_str());
//             mNFiles = 1;
//             cout << " Total " << mNFiles << " files have been read in " << dirFile << endl;
//         }

//         if(mChain){
//             mReadDataArray = new TClonesArray("StRHICfPi0Events");
//             mChain -> SetBranchAddress("StRHICfPi0Events", &mReadDataArray);
//         }
//     }
//     return 1;

    return 1;
}

Int_t StsChainMaker::InitWrite()
{
    // Output file initialization
    TString currentPath = gSystem -> pwd();
    mTFile = new TFile(Form("%s/test.root", currentPath.Data()), "recreate");
    mTree = new TTree("StsDst", "StsDst");
    mStsDstArray = new TClonesArray("StsDst");
    
    mTree -> Branch("StsDst", &mStsDstArray);

    InitGeometry();

    // Decoder initialization
    mDecoder = new StsDecoder();
    mDecoder -> Init();
        

    return 1;
}

Int_t StsChainMaker::WriteMake()
{
    
    Clear();
    mDecoder->Make();


    FillDst();

    return 1;
}

Int_t StsChainMaker::InitGeometry()
{
    mTrigDate.ToUpper();
    if(mTrigDate == "GEMTEST"){
        mTrigGeo = new StsTrigger_GEMTest();
        return 1;
    }
}

Int_t StsChainMaker::FillDst()
{
    mTree -> Fill();
    return 1;
}


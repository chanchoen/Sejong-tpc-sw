#include "StsChainMaker.hh"

StsChainMaker* StsChainMaker::mInstance = nullptr;

StsChainMaker* StsChainMaker::GetChainMaker() {
  if (mInstance != nullptr)
    return mInstance;
  return new StsChainMaker();
}

StsChainMaker::StsChainMaker(int ioMode, const char* fileName) 
: StsMaker("StsChainMaker", "StsChainMaker"), mIoMode(ioMode), mInputFileName(fileName)
{
}

StsChainMaker::~StsChainMaker()
{
}

bool StsChainMaker::Init() 
{  
    // mNFiles = -1;
    // iEvent = 0;

    // if(mIoMode==ioRead){
    //     cout << "StsChainMaker::Init() -- begin StsChainMaker construction for Read mode" << endl;
    //     openRead();
    // }
    // else if(mIoMode==ioWrite){
    //     cout << "StsChainMaker::Init() -- begin StsChainMaker construction for Write mode" << endl;
    //     if(openWrite() == kStErr){return kStErr;}
    // }
    cout << "StsChainMaker::Init()  --- test " << endl;

    InitMakers();

    return 1;
}

bool StsChainMaker::Make() 
{
    cout << "StsChainMaker::Make()" << endl;


    TIter iter(GetListOfTasks());
    StsMaker* maker;
    while ( (maker = dynamic_cast<StsMaker*>(iter())) ) {
        cout << "StsChainMaker::Make() --- test " << maker -> GetName() << "." << endl;
        maker -> Make();
    }



    // // Initialize a filled data.
    // clear();

    // // =================== Fill data ===================
    // fillData();

    // iEvent++;
    return 1;
}

bool StsChainMaker::Finish() 
{
    // if(mIoMode==ioWrite){
        
    //     cout << Form("StsChainMaker::Finish() -- Writing and closing %s",mOutputFileName.Data()) << endl;
    //     mTFile -> cd();
    //     mOutTree -> Write();
    //     mTFile -> Close();
    // }

    return 1;
}

bool StsChainMaker::clear()
{
    cout << "test " << endl;
    // mOutDataArray -> Clear("C");
    // mRHICfPi0Events = (StRHICfPi0Events*)mOutDataArray -> ConstructedAt(0);
    return 1;
}

// StRHICfPi0Events* StsChainMaker::getRHICfPi0Events(Int_t idx)
// {
//     if(idx >= mChain->GetEntries()){cout << "StsChainMaker::getRHICfPi0Events() -- wrong index !! " << endl;}
//     mChain -> GetEntry(idx);
//     StRHICfPi0Events* rhicfPi0Events = (StRHICfPi0Events*)mReadDataArray -> At(0);
//     return rhicfPi0Events;
// }

// Int_t StsChainMaker::getAnalEntries(){return mChain->GetEntries();}

// Int_t StsChainMaker::openRead()
// {
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
// }

// Int_t StsChainMaker::openWrite()
// {
//     TString streamTypeName;
//     TString runNumber;
//     TString daqNumber;
//     mNFiles = 0;
//     TString rootFileName;

//     if(mInputFileName.Length() == 0){
//         // No input file
//         cout << "Input file is not a existing ... " << endl;
//         return kStErr;
//     }
//     else{
//         std::string const dirFile = mInputFileName.Data();
//         if( dirFile.find(".list") != std::string::npos || dirFile.find(".lis") != std::string::npos ){
//             std::ifstream inputStream( dirFile.c_str() );
//             if(!inputStream) {cout << "ERROR: Cannot open list file " << dirFile << endl;}

//             std::string file;
//             size_t pos;
//             while(getline(inputStream, file)){
//                 pos = file.find_first_of(" ");
//                 if (pos != std::string::npos ) file.erase(pos,file.length()-pos);
//                 if(file.find("MuDst") != std::string::npos) {
                    
//                     std::stringstream sstreamPath(file);
//                     std::string wordPath;
//                     std::vector<string> wordPaths;
//                     while(getline(sstreamPath, wordPath, '/')){
//                         wordPaths.push_back(wordPath);
//                     }
//                     int wordSize = wordPaths.size();

//                     std::stringstream sstreamWord(wordPaths[wordSize-1]);
//                     rootFileName = wordPaths[wordSize-1];
//                     std::string word;
//                     int nIdx = 0;
//                     while(getline(sstreamWord, word, '_')){
//                         // find a production stream type 
//                         if(nIdx==1){streamTypeName = word;}
//                         if(streamTypeName == "physics"){
//                             cout << "Files has not RHICf stream!!! (" << wordPaths[wordSize-1] << ")" << endl;
//                             return kStErr;
//                         }
//                         // find a runnumber 
//                         if(nIdx==2){
//                             if(word!="adc"){runNumber = word;}
//                         }
//                         if(nIdx==4){
//                             std::stringstream sstreamWord2(word);
//                             while(getline(sstreamWord2, word, '.')){
//                                 daqNumber = word;
//                                 break;
//                             }
//                         }
//                         nIdx++;
//                     }
//                     mNFiles++;
//                 } 

//             } 
//             cout << " Total " << mNFiles << " files have been read in. " << endl;
//         }
//         else if(dirFile.find("MuDst") != std::string::npos) {
//             std::stringstream sstreamPath(dirFile);
//             std::string wordPath;
//             std::vector<string> wordPaths;
//             while(getline(sstreamPath, wordPath, '/')){
//                 wordPaths.push_back(wordPath);
//             }
//             int wordSize = wordPaths.size();

//             std::stringstream sstreamWord(wordPaths[wordSize-1]);
//             rootFileName = wordPaths[wordSize-1];
//             std::string word;
//             int nIdx = 0;
//             while(getline(sstreamWord, word, '_')){
//                 // find a production stream type 
//                 if(nIdx==1){streamTypeName = word;}
//                 if(streamTypeName == "physics"){
//                     cout << "Files has not RHICf stream!!! (" << wordPaths[wordSize-1] << ")" << endl;
//                     return kStErr;
//                 }
//                 // find a runnumber 
//                 if(nIdx==2){
//                     if(word!="adc"){runNumber = word;}
//                 }
//                 if(nIdx==4){
//                     std::stringstream sstreamWord2(word);
//                     while(getline(sstreamWord2, word, '.')){
//                         daqNumber = word;
//                         break;
//                     }
//                 }
//                 nIdx++;
//             }
//             mNFiles = 1;
//         }
//     }

//     if(mNFiles == 1){
//         mOutputFileName = "st_" + streamTypeName + "_" + runNumber + "_pp500_" + daqNumber + "_AnalRHICfPi0.root";
//         cout << Form("StsChainMaker::openWrite() -- Input file name: %s", rootFileName.Data()) << endl;
//     }
//     else{
//         mOutputFileName = "st_" + streamTypeName + "_" + runNumber + "_pp500_AnalRHICfPi0.root";
//         cout << Form("StsChainMaker::openWrite() -- number of Files in .list: %i", mNFiles) << endl;
//     }
    
//     cout << Form("StsChainMaker::openWrite() -- Output file name: %s",mOutputFileName.Data()) << endl;

//     mTFile = new TFile(mOutputFileName.Data(), "recreate");
//     mOutTree = new TTree("AnalRHICfPi0","AnalRHICfPi0");

//     mOutDataArray = new TClonesArray("StRHICfPi0Events");
//     mOutTree -> Branch("StRHICfPi0Events",&mOutDataArray);

//     return 1;
// }

// Int_t StsChainMaker::getNFiles(){return mNFiles;}


// // void StsChainMaker::fillData()
// // {
// //     mOutTree -> Fill();
// // }


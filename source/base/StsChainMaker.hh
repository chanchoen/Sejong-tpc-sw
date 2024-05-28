#ifndef StsChainMaker_HH
#define StsChainMaker_HH

#include "StsMaker.hh"
#include "StsUtil.hh"

#include <iostream>
#include <TROOT.h>
#include <TString.h>
#include <TChain.h>
#include <TFile.h>
#include <TTree.h>
#include <TObjArray.h>
#include <TClonesArray.h>

// class StsData;
// class StsRunInfo;
// class StsTPCRaw;

using namespace std;
using namespace TMath;

class StsChainMaker : public StsMaker, public StsUtil
{
	public: 
		static StsChainMaker* GetChainMaker();

		StsChainMaker(int ioMode=1, const char* fileName="");
		~StsChainMaker();

		bool Init();
		bool Make();
		bool Finish();
		bool clear();

		Int_t write();
		Int_t read();


		// set parameters
		// voi

		// for read a AnalRHICfPi0 files
		// Int_t getAnalEntries();
		// Int_t getNFiles();
		// StRHICfPi0Events* getRHICfPi0Events(Int_t idx);

	private:
		static StsChainMaker *mInstance;

		// general 
		// Int_t openRead();
		// Int_t openWrite();

		// // Data writing structrue
		int mIoMode;
		// Int_t mNFiles;
		TString mInputFileName;
		// TString mOutputFileName;

		// TFile* mTFile = 0;
		// TTree* mOutTree = 0;
		// TClonesArray* mOutDataArray = 0;
		// // StsData* mData = 0;

		// // Data reading structure
		// TChain* mChain = 0;
		// TClonesArray* mReadDataArray = 0;


	protected:
		enum ioMode {ioRead, ioWrite};

	ClassDef(StsChainMaker,0);
};

#endif
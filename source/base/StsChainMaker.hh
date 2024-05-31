#ifndef StsChainMaker_HH
#define StsChainMaker_HH

#include "StsMaker.hh"
#include "StsUtil.hh"

#include <iostream>
#include "TROOT.h"
#include "TSystem.h"
#include "TString.h"
#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TObjArray.h"
#include "TClonesArray.h"

class StsDst;
class StsRunInfo;
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



		// set parameters
		// voi

		// for read a AnalRHICfPi0 files
		// Int_t getAnalEntries();
		// Int_t getNFiles();
		// StRHICfPi0Events* getRHICfPi0Events(Int_t idx);

	private:
		Int_t Read();
		Int_t Write();
		Int_t InitDst();
		Int_t FillDst();
		Int_t DstList();

		static StsChainMaker *mInstance;

		// Data writing structrue
		bool mFlag;
		int mIoMode;
		TString mInputFileName;
		TString mOutputFileName;
		Int_t mNFiles;
		Int_t mEventNum;


		TFile* mTFile;
		TTree* mTree;
		TClonesArray* mStsDstArray;
		StsDst* mDst;
		// StsRunInfo* mRunInfo;


	protected:
		enum ioMode {ioRead, ioWrite};

	ClassDef(StsChainMaker,0);
};

#endif
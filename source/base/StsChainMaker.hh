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
class StsTrigger;
class StsDecoder;

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

		Int_t Init();
		Int_t Make();
		Int_t Finish();
		Int_t Clear();
		
		StsDst* GetDst();
		StsTrigger* GetTrigger();

		void SetDAQFiles(TString file = "");
		void SetTriggerDate(TString date = "");
		void SetEventNum(Int_t eventNum = -1);

	private:
		Int_t InitRead();
		Int_t ReadMake();
		
		Int_t InitWrite();
		Int_t WriteMake();

		Int_t InitGeometry();

		Int_t InitDst();
		Int_t FillDst();
		Int_t DstList();

		static StsChainMaker *mInstance;

		// Data writing structrue
		bool mFlag;
		int mIoMode;
		TString mTrigDate;
		TString mDAQFile;
		TString mInputFileName;
		TString mOutputFileName;
		Int_t mNFiles;
		Int_t mEventNum;
		Int_t mEvent;

		TFile* mTFile = 0;
		TTree* mTree = 0;
		TClonesArray* mStsDstArray = 0;
		StsDst* mDst = 0;
		StsTrigger* mTrigGeo = 0;
		StsDecoder* mDecoder = 0;

	protected:
		enum ioMode {ioRead, ioWrite};

	ClassDef(StsChainMaker,0);
};

#endif
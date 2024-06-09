#ifndef StsChainMaker_HH
#define StsChainMaker_HH

#include "StsMaker.hh"
#include "StsUtil.hh"

#include "TROOT.h"
#include "TSystem.h"
#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TObjArray.h"
#include "TClonesArray.h"

class StsDst;
class StsRunInfo;
class StsEventInfo;
class StsTriggerManager;
class StsTrigger;
class StsDecoder;

using namespace std;
using namespace TMath;

class StsChainMaker : public StsMaker
{
	public: 
		static StsChainMaker* GetChainMaker(int ioMode=kWrite, const char* file="");

		StsChainMaker(int ioMode=kWrite, const char* file="");
		~StsChainMaker();

		Int_t Init();
		Int_t Make();
		Int_t Finish();
		Int_t Clear();
		
		StsDst* GetDst();
		StsRunInfo* GetRunInfo();
		StsEventInfo* GetEventInfo();
		StsTrigger* GetTrigger();

		void SetExperiment(TString exp = "");
		void SetTriggerType(TString type = "");
		void SetExcuteRun(TString run = "ALL");
		void SetRejectRun(TString run = "");
		void SetEventNum(Int_t eventNum = -1);
		void SetInputFile(TString inputFile = "");
		void SetOutputPath(TString outPath = "");

	private:
		Int_t InitRun();

		Int_t InitRead();
		Int_t MakeRead();
		
		Int_t InitWrite();
		Int_t MakeWrite();

		Int_t InitGeometry();

		Int_t InitDst();
		Int_t FillDst();
		Int_t DstList();
		Int_t FillRunInfo();

		Int_t InitChecker();

		Int_t Print();

		static StsChainMaker* mInstance;

		// Data writing structrue
		Int_t mStageFlag;
		Int_t mIoMode;
		
		TString mExpName;
		TString mTrigType;
		TString mExcuteRun;
		TString mRejectRun;
		TString mInputFile;
		TString mOutputPath;
		TString mOutputFile;

		RunList mRunList;
		Int_t mEventNum;
		Int_t mEvent;

		TFile* mTFile = 0;
		TTree* mTree = 0;
		StsDst* mDst = 0;
		StsTriggerManager* mTrigManager = 0;
		StsDecoder* mDecoder = 0;

	protected:


	ClassDef(StsChainMaker,0);
};

#endif
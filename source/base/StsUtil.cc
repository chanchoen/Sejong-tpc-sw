#include "StsUtil.hh"

StsUtil::StsUtil()
{
}

StsUtil::~StsUtil()
{
}

TString StsUtil::AddDash(TString path)
{
    int length = path.Sizeof();
    if(path[length-1] == '/'){return path;}
    else{
        path = path + "/";
        return path;
    }
    return path;
}

RunList StsUtil::GetRunList(TString input, TString rejectRun, int stage)
{
    RunList runList;

    if(input.Index(".list") != -1 || input.Index(".lis") != -1 || input.Index(".text") != -1 || input.Index(".txt") != -1 || input.Index(".dat") != -1){
        vector<Int_t> rejectRuns = GetRunsFromString(rejectRun);
        runList = GetLines(input, stage);
        runList = RemovedRejectRun(runList, rejectRuns);
        return runList;
    }
    else if(input.Index(".graw") != -1 || input.Index(".root") != -1){
        vector<TString> tmp;
        tmp.push_back(input);
        runList.push_back(make_pair(0, tmp));
        return runList;
    }
    else{
        vector<Int_t> excuteRuns = GetRunsFromString(input);
        vector<Int_t> rejectRuns = GetRunsFromString(rejectRun);
        for(int i=0; i<excuteRuns.size(); i++){
            int run = excuteRuns[i];
            bool isReject = false;
            for(int j=0; j<rejectRuns.size(); j++){
                if(run == rejectRuns[i]){
                    isReject = true;
                    break;
                }
            }
            if(isReject == true){continue;}

            vector<TString> fileList = GetDataBaseFile(run, stage);
            runList.push_back(make_pair(run, fileList));
        }
        return runList;
    }
    return runList;
}

DAQList StsUtil::GetDAQList(vector<TString> fileList)
{
    DAQList daqList; 
    
    vector<TString> tmpAsAdFile[ASADNUM];

    // Seperate the AsAd files
    for(int i=0; i<fileList.size(); i++){
        TString file = fileList[i];
        int asadIdx = -1;
        if(file.Index("AsAd") != -1){ // CoBo
            TString idx = file[file.Index("AsAd")+4];
            asadIdx = idx.Atoi();
        }
        if(file.Index("CoBo_") != -1){asadIdx = 0;} // rCoBo
        if(asadIdx < 0 || 4 < asadIdx){continue;}

        tmpAsAdFile[asadIdx].push_back(file);
    }

    // Sort in order the file number
    vector<TString> tmp2AsAdFile[ASADNUM];
    for(int asad=0; asad<ASADNUM; asad++){

        int findDAQNum = 0;
        while(!(findDAQNum == tmpAsAdFile[asad].size())){
            for(int i=0; i<tmpAsAdFile[asad].size(); i++){
                int numberIdx = tmpAsAdFile[asad][i].Index(".graw")-4;
                TString daqNumStr = "";
                for(int idx=0; idx<4; idx++){
                    daqNumStr += tmpAsAdFile[asad][i][numberIdx+idx];
                }
                int daqNum = daqNumStr.Atoi();

                if(findDAQNum == daqNum){
                    tmp2AsAdFile[asad].push_back(tmpAsAdFile[asad][i]);
                    findDAQNum++;
                }
            }
        }

        queue<TString> tmpQueue;
        for(int i=0; i<tmp2AsAdFile[asad].size(); i++){

            cout << " test! " << asad <<  " " << i << " " << tmp2AsAdFile[asad][i] << endl;

            tmpQueue.push(tmp2AsAdFile[asad][i]);
        }
        daqList.push_back(tmpQueue);
    }

    return daqList;
}

Bool_t StsUtil::CheckRunIDFormat(TString run)
{
    if(run.Sizeof() != 10){return false;}
    return true;
}

RunList StsUtil::RemovedRejectRun(RunList runList, vector<Int_t> rejectRun)
{
    RunList newRunList;
    if(rejectRun.size() == 0){
        newRunList = runList;
        return newRunList;
    }

    for(auto i=0; i<runList.size(); i++){
        int runNumber = runList[i].first;
        bool isReject = false;
        for(int j=0; j<rejectRun.size(); j++){
            if(runNumber == rejectRun[j]){
                isReject = true;
                break;
            }
        }
        if(isReject == true){continue;}
        newRunList.push_back(runList[i]);
    }
    return newRunList;
}


vector<Int_t> StsUtil::GetRunsFromString(TString run)
{
    vector<Int_t> list;
    if(run == ""){return list;}
    if(run.Index(",") != -1){
        run.ReplaceAll(",", " ");
    }

    TObjArray *tokens = run.Tokenize(" ");
    for(int i=0; i<tokens->GetEntries(); i++){
        TString token = ((TObjString *) tokens -> At(i)) -> GetString();
        if(!CheckRunIDFormat(token)){continue;}
        list.push_back(token.Atoi());
    }

    return list;
}

RunList StsUtil::GetLines(TString file, int stage)
{
    RunList lineList;
    vector<TString> tmpFileArr;

    std::ifstream inputFile(file.Data());
    if(inputFile.is_open()){
        string line;
        while(getline(inputFile, line)){
            TString lineTmp = line;

            if(stage == kDaqStage){ // getting .graw file in line
                if(lineTmp.Index(".graw") != -1){
                    tmpFileArr.push_back(lineTmp);
                }
            }
            if(stage == kRawStage){ // getting raw stage file in line
                if(lineTmp.Index("_raw.root") != -1){
                    tmpFileArr.push_back(lineTmp);
                }
            }
            if(stage == kRecoStage){ // getting reco stage file in line
                if(lineTmp.Index("_reco.root") != -1){
                    tmpFileArr.push_back(lineTmp);
                }
            }
            if(CheckRunIDFormat(lineTmp)){ // getting run file in line
                vector<TString> fileinRuns = GetDataBaseFile(lineTmp, stage);
                lineList.push_back(make_pair(lineTmp.Atoi(), fileinRuns));
            }
        }
        inputFile.close();
    }

    if(lineList.size() == 0 && tmpFileArr.size() != 0){
        lineList.push_back(make_pair(0, tmpFileArr));
    }
    else if(lineList.size() != 0 && tmpFileArr.size() != 0){
        lineList.clear(); // bad list file
    }

    return lineList;
}

vector<TString> StsUtil::GetDataBaseFile(TString run, int stage)
{
    vector<TString> runPathList;

    TString currentPath = gSystem->pwd();

    TString dataBase;
    if(stage == kDaqStage){dataBase = kDataBasePath+"daq";}
    if(stage == kRawStage){dataBase = kDataBasePath+"raw";}
    if(stage == kRecoStage){dataBase = kDataBasePath+"reco";}

    TSystemDirectory dir("dir", dataBase);

    TList *listOfDirs = dir.GetListOfFiles();
    TList *listOfFiles = 0;
    
    TIter next(listOfDirs);
    TObject *objDir;
    TObject *objFile;
    while((objDir = next())){
        TSystemFile* runDir = dynamic_cast<TSystemFile*>(objDir);
        if(runDir && runDir->IsDirectory()){
            
            TString runName = runDir->GetName();
            if(!CheckRunIDFormat(runName)){continue;}
            if(run != runName){continue;}

            TString runPath = dataBase+"/"+runName;
            TSystemDirectory subRunDir("", runPath);
            listOfFiles = subRunDir.GetListOfFiles();

            TIter nextFiles(listOfFiles);
            while((objFile = nextFiles())){
                TSystemFile* runFile = dynamic_cast<TSystemFile*>(objFile);
                TString fileName = runFile->GetName();
                if(!runFile){continue;}

                TString path = dataBase+"/"+runName+"/"+fileName;
                if(fileName.Index(".graw") != -1 && stage == kDaqStage){
                    runPathList.push_back(path);
                }
                else if(fileName.Index(".root") != -1 && stage != kDaqStage){
                    runPathList.push_back(path);
                }
            }
        }
    }

    return runPathList;
}

vector<TString> StsUtil::GetDataBaseFile(int runID, int stage)
{
    TString run = TString::Itoa(runID, 10);
    return GetDataBaseFile(run, stage);
}
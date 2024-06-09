#include "StsUtil.hh"

StsUtil::StsUtil()
{
}

StsUtil::~StsUtil()
{
}

TString AddDash(TString path)
{
    int length = path.Sizeof();
    if(path[length-1] == '/'){return path;}
    else{
        path = path + "/";
        return path;
    }
    return path;
}

static RunList GetRunList(TString path, TString rejectRun)
{
    vector<Int_t> rejectRunList = GetListFromString(rejectRun);
}


vector<pair<TString, int>> GetRunPath(TString path)
{
    
}

queue<tuple<int, int, TString>> StsUtil::GetDAQFileQueue(TString inputFile)
{
    queue<tuple<int, int, TString>> fileQueue;

    if(inputFile.Length() == 0){
        cout << "StsUtil::GetDAQFileQueue() --- Input file is not a existing ... " << endl;
        return fileQueue;
    }
    else{
        std::string const dirFile = inputFile.Data();
        if( dirFile.find(".list") != std::string::npos || dirFile.find(".lis") != std::string::npos || dirFile.find(".txt") != std::string::npos){
            std::ifstream inputStream( dirFile.c_str() );
            if(!inputStream) {cout << "StsUtil::GetDAQFileQueue() --- ERROR: Cannot open list file " << dirFile << endl;}

            std::string file;
            size_t pos;
            while(getline(inputStream, file)){
                pos = file.find_first_of(" ");
                if(pos != std::string::npos ){
                    file.erase(pos,file.length()-pos);
                }

                if(file.find(".graw") != std::string::npos){
                    if(file.find("AsAd") != std::string::npos){

                    }
                    fileQueue.push(file);
                } 

            }
        }
        else if(dirFile.find(".graw") != std::string::npos) {
            fileQueue.push(dirFile);
        }
        
    }
    cout << "StsUtil::GetDAQFileQueue() --- " << fileQueue.size() << " files have been queue." << endl;
    
    return fileQueue;
}
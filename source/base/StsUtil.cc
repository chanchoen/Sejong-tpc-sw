#include "StsUtil.hh"

StsUtil::StsUtil()
{
}

StsUtil::~StsUtil()
{
}

queue<TString> StsUtil::GetDAQFileQueue(TString inputFile)
{
    queue<TString> fileQueue;

    if(inputFile.Length() == 0){
        cout << "StsUtil::GetFileQueue() --- Input file is not a existing ... " << endl;
        return fileQueue;
    }
    else{
        std::string const dirFile = inputFile.Data();
        if( dirFile.find(".list") != std::string::npos || dirFile.find(".lis") != std::string::npos || dirFile.find(".txt") != std::string::npos){
            std::ifstream inputStream( dirFile.c_str() );
            if(!inputStream) {cout << "StsUtil::GetFileQueue() --- ERROR: Cannot open list file " << dirFile << endl;}

            std::string file;
            size_t pos;
            while(getline(inputStream, file)){
                pos = file.find_first_of(" ");
                if(pos != std::string::npos ){
                    file.erase(pos,file.length()-pos);
                }
                if(file.find(".graw") != std::string::npos){
                    
                    fileQueue.push(file);
                } 

            }
        }
        else if(dirFile.find(".graw") != std::string::npos) {
            fileQueue.push(dirFile);
        }
    }
    return fileQueue;
}
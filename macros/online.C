#include "StsChainMaker.hh"

#define d NextEvent()
#define a PreviousEvent()
#define s SavePicture()
#define w(event) ParticluarEvent(event)

int fEventIdx = -1;
char fKeyStats;

void NextEvent();
void PreviousEvent();
void SavePicture();
void ParticluarEvent(int event);
void Excute();

void online(TString path="/data/public_data/daq/240527001", TString triggerType="GemTest")
{
    StsChainMaker* chain = StsChainMaker::GetChainMaker(2, path);
    chain -> SetTriggerType(triggerType);
    
    StsTPCOnlineMaker* drawMaker = new StsTPCOnlineMaker();
    chain -> Add(drawMaker);
    chain -> Init();

    Excute();
    cout << endl;
    cout << "                  ------------------ online mode command gauid -----------------  " << endl;
    cout << "                 |    d : Next event                                            | " << endl;
    cout << "                 |    a : Previous event                                        | " << endl;
    cout << "                 |    s : Save the event picture                                | " << endl;
    cout << "                 |    w(int) : show the n th event. Ex) ww(150)                 | " << endl; 
    cout << "                  --------------------------------------------------------------  " << endl;
    cout << endl;
}

void Excute()
{
    if(fEventIdx < 0){fEventIdx = 0;}
    StsChainMaker::GetChainMaker() -> Make(fEventIdx);
}

void NextEvent()
{
    fEventIdx++;
    Excute();
}

void ParticluarEvent(int event)
{
    fEventIdx = event;
    Excute();
}

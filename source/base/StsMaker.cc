#include "StsMaker.hh"

#include <iostream>
using namespace std;

StsMaker::StsMaker()
:TTask()
{
}

StsMaker::StsMaker(const char* name, const char *title)
:TTask(name, title)
{
}

void StsMaker::Add(TTask *maker)
{
    TTask::Add(maker);
}

bool StsMaker::Init() 
{
    return true;
}

bool StsMaker::InitMakers()
{
    TIter iter(GetListOfTasks());
    StsMaker* maker;

    while ((maker = dynamic_cast<StsMaker*>(iter()))) {
        cout << "StsMaker::InitMakers() --- Initializing " << maker -> GetName() << "." << endl;
        if (maker -> Init() == false) {
            cout << "StsMaker::InitMakers() --- Initialization failed!" << endl;
            return false;
        }
    }

    return true;
}

bool StsMaker::Make()
{
    return true;
}

bool StsMaker::Finish()
{
    return true;
}

bool StsMaker::FinishMakers()
{
    TIter iter(GetListOfTasks());
    StsMaker* maker;

    while ( (maker = dynamic_cast<StsMaker*>(iter())) ) {
        cout << "StsMaker::FinishMakers() --- Finishing " << maker -> GetName() << "." << endl;
        if (maker -> Finish() == false) {
            cout << "StsMaker::FinishMakers() --- Finish failed!" << endl;
            return false;
        }
    }

  return true;
}
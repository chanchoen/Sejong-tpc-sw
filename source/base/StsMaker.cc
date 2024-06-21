#include "StsMaker.hh"

StsMaker::StsMaker()
:TTask()
{
}

StsMaker::StsMaker(const char* name, const char *title)
:TTask(name, title)
{
}

StsMaker::~StsMaker()
{
}

void StsMaker::Add(TTask *maker)
{
    TTask::Add(maker);
}

Int_t StsMaker::InitMakers()
{
    TIter iter(GetListOfTasks());
    StsMaker* maker;

    while ((maker = dynamic_cast<StsMaker*>(iter()))) {
        cout << "StsMaker::InitMakers() --- Initializing " << maker -> GetName() << "." << endl;
        if (maker -> Init() == false) {
            cout << "StsMaker::InitMakers() --- Initialization failed!" << endl;
            return 0;
        }
    }

    return 1;
}

Int_t StsMaker::FinishMakers()
{
    TIter iter(GetListOfTasks());
    StsMaker* maker;

    while ( (maker = dynamic_cast<StsMaker*>(iter())) ) {
        cout << "StsMaker::FinishMakers() --- Finishing " << maker -> GetName() << "." << endl;
        if (maker -> Finish() == false) {
            cout << "StsMaker::FinishMakers() --- Finish failed!" << endl;
            return 0;
        }
    }

  return 1;
}

Int_t StsMaker::Init() 
{
    return 1;
}

Int_t StsMaker::Make()
{
    return 1;
}

Int_t StsMaker::Finish()
{
    return 1;
}

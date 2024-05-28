#ifndef StsMaker_HH
#define StsMaker_HH

#include "TTask.h"
#include <string>
#include <iostream>
using namespace std;

class StsMaker : public TTask
{
    public:
        StsMaker();
        StsMaker(const char* name, const char *title);
        virtual ~StsMaker() {};

        virtual void Add(TTask *task);

        bool InitMakers();
        virtual bool Init();

        virtual bool Make();

        bool FinishMakers();
        virtual bool Finish();

    ClassDef(StsMaker, 1)
};

#endif
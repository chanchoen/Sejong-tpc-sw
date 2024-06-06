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
        virtual ~StsMaker();

        virtual void Add(TTask *task);

        Int_t InitMakers();
        Int_t FinishMakers();

        virtual Int_t Init();
        virtual Int_t Make();
        virtual Int_t Finish();


    ClassDef(StsMaker, 0)
};

#endif
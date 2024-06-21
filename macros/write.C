#include <time.h>

void write()
{
    // StsChainMaker* chain = StsChainMaker::GetChainMaker(1, "test.txt");
    StsChainMaker* chain = StsChainMaker::GetChainMaker(1);

    chain -> SetExcuteRun("240527001");
    chain -> SetTriggerType("GemTest");
    chain -> SetEventNum(10);

    time_t start, end;
    double result;

    StsTPCPadDrawMaker* drawMaker = new StsTPCPadDrawMaker();
    chain -> Add(drawMaker);
    chain -> Init();

    start = time(NULL);

    chain -> Make();

    end = time(NULL);
    result = (double)(end-start);
    cout << " running time : " << result << " s " << endl;

    chain -> Finish();

}
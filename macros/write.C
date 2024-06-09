void write()
{
    StsChainMaker* chain = StsChainMaker::GetChainMaker(1, "test.txt");

    chain -> SetTriggerType("GemTest");
    chain -> Init();

    chain -> Make();
    

    chain -> Finish();
}
void write()
{
    StsChainMaker* chain = StsChainMaker::GetChainMaker(1, "test.txt");
    // StsChainMaker* chain = StsChainMaker::GetChainMaker(1);

    // chain -> SetExcuteRun("240527001");
    chain -> SetTriggerType("GemTest");
    chain -> Init();

    chain -> Make();
    

    chain -> Finish();
}
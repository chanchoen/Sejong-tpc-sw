void test()
{
    StsChainMaker* chain = StsChainMaker::GetChainMaker();
    
    StsTest* test = new StsTest();
    StsTest2* test2 = new StsTest2();

    // chain -> Add(test2);
    // chain -> Add(test);

    chain -> Init();

    for(int i=0; i<3; i++){
        chain -> Make();
    }

    chain -> Finish();
}
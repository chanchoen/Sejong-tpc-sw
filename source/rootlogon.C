{
  TString SejongTPCswPath = "/home/shlee/workspace/Sejong-tpc-sw";
  TString libString = SejongTPCswPath + "/build/libSejongTPCsw.so";

  if (gSystem -> Load(libString) != -1)
    cout << "Sejong TPC SW Library Loaded" << endl;
  else
    cout << "Cannot Load Sejong TPC SW" << endl;
}
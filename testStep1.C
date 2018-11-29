#include "step1.cc"

void testStep1(){  
  TString path ="root://cmseos.fnal.gov//store/group/lpcljm/LJMet102x_3lepTT_2018datasets_2018_11_22_rizki/nominal/";
  
  //Choose one for test:
  TString filename ="EGamma_RunC"; //Data
//   TString filename ="DoubleMuon_RunC"; //Data


  TString inputFile=path+"/"+filename+"/"+filename+"_1.root";    	
  TString outputFile="testStep1_2018data"+filename+".root";

  gSystem->AddIncludePath("-I$CMSSW_BASE/src/");
  
  step1 t(inputFile,outputFile);
  t.Loop();
  
  std::cout<< "DONE!"<< std::endl;
  gApplication->Terminate();
}



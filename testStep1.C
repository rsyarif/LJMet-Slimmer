#include "step1.cc"

void testStep1(){  
  TString path ="root://cmseos.fnal.gov//store/group/lpcljm/LJMet94x_3lepTT_2017datasets_2018_11_7_rizki/nominal/";
  
  //Choose one for test:
//   TString filename ="TprimeTprime_M-1000_TuneCP5_13TeV-madgraph-pythia8"; //Signal
//   TString filename ="DoubleEG_RRD"; //Data
//   TString filename ="DoubleMuon_RRD"; //Data
  TString filename ="MuonEG_RRE"; //Data
//   TString filename ="TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8";  //MC bkg


  TString inputFile=path+"/"+filename+"/"+filename+"_1.root";    	
  TString outputFile="testStep1_"+filename+".root";

  gSystem->AddIncludePath("-I$CMSSW_BASE/src/");
  
  step1 t(inputFile,outputFile);
  t.Loop();
  
  std::cout<< "DONE!"<< std::endl;
  gApplication->Terminate();
}



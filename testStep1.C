#include "step1.cc"

void testStep1(){
  
  //TString inputFile="root://cmseos.fnal.gov//store/user/lpcljm/2016/LJMet80X_1lep_XCone_2018_1_18_rizki/nominal/SingleElectron_RRBCDEFGH/SingleElectron_RRBCDEFGH_99.root";
  //TString inputFile="root://cmseos.fnal.gov//store/user/lpcljm/2016/LJMet80X_1lep_XCone_2018_1_18_rizki/nominal/TprimeTprime_M-1000_TuneCUETP8M1_13TeV-madgraph-pythia8/TprimeTprime_M-1000_TuneCUETP8M1_13TeV-madgraph-pythia8_1.root";
  TString inputFile="root://cmseos.fnal.gov//store/user/lpcljm/2016/LJMet80X_1lep_XCone_2018_1_18_rizki/nominal/TprimeTprime_M-1300_TuneCUETP8M1_13TeV-madgraph-pythia8/TprimeTprime_M-1300_TuneCUETP8M1_13TeV-madgraph-pythia8_1.root";
    
  TString outputFile="test.root";
  
  gSystem->AddIncludePath("-I$CMSSW_BASE/src/");
  
  step1 t(inputFile,outputFile);
  t.Loop();
}



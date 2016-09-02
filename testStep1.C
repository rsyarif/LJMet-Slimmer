#include "step1.cc"

void testStep1(){
  
//   TString inputFile="root://cmseos.fnal.gov//store/user/lpcljm/LJMet80x_3lepTT_2016_8_24_rizki/nominal/MuonEG_PRB/MuonEG_PRB_3.root";
//   TString inputFile="root://cmseos.fnal.gov//store/user/lpcljm/LJMet80x_3lepTT_2016_8_24_rizki/nominal/DoubleEG_PRB/DoubleEG_PRB_1.root";
//   TString inputFile="root://cmseos.fnal.gov//store/user/lpcljm/LJMet80x_3lepTT_2016_8_24_rizki/nominal/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8_1.root";
  TString inputFile="root://cmseos.fnal.gov//store/user/lpcljm/LJMet80x_3lepTT_2016_8_31_rizki/nominal/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8_1.root";
//   TString inputFile="root://cmseos.fnal.gov//store/user/lpcljm/LJMet80x_3lepTT_2016_8_31_rizki/nominal/DoubleMuon_PRB/DoubleMuon_PRB_1.root";
  
  TString outputFile="test.root";
  
  gSystem->AddIncludePath("-I$CMSSW_BASE/src/");
  
  step1 t(inputFile,outputFile);
  t.Loop();
}



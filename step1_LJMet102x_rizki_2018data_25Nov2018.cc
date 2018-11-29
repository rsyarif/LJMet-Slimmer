#define step1_cxx
#include "step1.h"
#include <fstream>
#include <iostream>     // std::cout
#include <algorithm>    // std::sort
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TRandom.h>
#include <TRandom3.h>
#include <sstream>
#include <string>
#include <vector>
#include "fakerate.h" //added by rizki
#include <cmath>

using namespace std;

// ----------------------------------------------------------------------------
// DEBUG printout switches
// ----------------------------------------------------------------------------
bool DEBUG = false;
bool DEBUGleptons = false;
bool DEBUGjets = false;
bool DEBUGddbkg = false;
bool DEBUGddbkgScan = false;
bool DEBUGTriggers = true;

// ----------------------------------------------------------------------------
// Define functions
// ----------------------------------------------------------------------------

bool comparepair( const std::pair<double,int> a, const std::pair<double,int> b) { return a.first > b.first; }

TRandom3 Rand;

const double MTOP  = 173.5;
const double MW    = 80.4; 

bool step1::applySF(bool& isTagged, float tag_SF, float tag_eff){
  
  bool newTag = isTagged;
  if (tag_SF == 1) return newTag; //no correction needed 

  //throw die
  float coin = Rand.Uniform(1.);    

  if(tag_SF > 1){  // use this if SF>1

    if( !isTagged ) {

      //fraction of jets that need to be upgraded
      float mistagPercent = (1.0 - tag_SF) / (1.0 - (tag_SF/tag_eff) );

      //upgrade to tagged
      if( coin < mistagPercent ) {newTag = true;}
    }

  }else{  // use this if SF<1
      
    //downgrade tagged to untagged
    if( isTagged && coin > tag_SF ) {newTag = false;}

  }

  return newTag;
}

// ----------------------------------------------------------------------------
// MAIN EVENT LOOP
// ----------------------------------------------------------------------------

void step1::Loop() 
{

  // ----------------------------------------------------------------------------
  // Turn on input tree branches
  // ----------------------------------------------------------------------------

   if (inputTree == 0) return;
   
   inputTree->SetBranchStatus("*",0);

   //Event info

   inputTree->SetBranchStatus("event_CommonCalc",1);
   inputTree->SetBranchStatus("run_CommonCalc",1);
   inputTree->SetBranchStatus("lumi_CommonCalc",1);
   inputTree->SetBranchStatus("nPV_singleLepCalc",1);
   inputTree->SetBranchStatus("nTrueInteractions_singleLepCalc",1);
   inputTree->SetBranchStatus("MCWeight_singleLepCalc",1);
   inputTree->SetBranchStatus("LHEweightids_singleLepCalc",1);
   inputTree->SetBranchStatus("LHEweights_singleLepCalc",1);

   inputTree->SetBranchStatus("isTHBW_TpTpCalc",1);
   inputTree->SetBranchStatus("isTHTH_TpTpCalc",1);
   inputTree->SetBranchStatus("isBWBW_TpTpCalc",1);
   inputTree->SetBranchStatus("isTZBW_TpTpCalc",1);
   inputTree->SetBranchStatus("isTZTH_TpTpCalc",1);
   inputTree->SetBranchStatus("isTZTZ_TpTpCalc",1);
   inputTree->SetBranchStatus("isBHTW_TpTpCalc",1);
   inputTree->SetBranchStatus("isBHBH_TpTpCalc",1);
   inputTree->SetBranchStatus("isTWTW_TpTpCalc",1);
   inputTree->SetBranchStatus("isBZTW_TpTpCalc",1);
   inputTree->SetBranchStatus("isBZBH_TpTpCalc",1);
   inputTree->SetBranchStatus("isBZBZ_TpTpCalc",1);
   inputTree->SetBranchStatus("tPrimePt_TpTpCalc",1);
   inputTree->SetBranchStatus("NLeptonDecays_TpTpCalc",1);
   
   //triggers
   inputTree->SetBranchStatus("vsSelMCTriggersEl_singleLepCalc",1);
   inputTree->SetBranchStatus("viSelMCTriggersEl_singleLepCalc",1);
   inputTree->SetBranchStatus("vsSelMCTriggersMu_singleLepCalc",1);
   inputTree->SetBranchStatus("viSelMCTriggersMu_singleLepCalc",1);
   inputTree->SetBranchStatus("vsSelTriggersEl_singleLepCalc",1);
   inputTree->SetBranchStatus("viSelTriggersEl_singleLepCalc",1);
   inputTree->SetBranchStatus("vsSelTriggersMu_singleLepCalc",1);
   inputTree->SetBranchStatus("viSelTriggersMu_singleLepCalc",1);
   
   //electrons
   inputTree->SetBranchStatus("elPt_singleLepCalc",1);
   inputTree->SetBranchStatus("elEta_singleLepCalc",1);
   inputTree->SetBranchStatus("elPhi_singleLepCalc",1);
   inputTree->SetBranchStatus("elEnergy_singleLepCalc",1);
   inputTree->SetBranchStatus("elDxy_singleLepCalc",1);
   inputTree->SetBranchStatus("elD0_singleLepCalc",1);
   inputTree->SetBranchStatus("elDZ_singleLepCalc",1);
   inputTree->SetBranchStatus("elCharge_singleLepCalc",1);
   inputTree->SetBranchStatus("elMVAValue_singleLepCalc",1);
   inputTree->SetBranchStatus("elIsMVATight_singleLepCalc",1);
   inputTree->SetBranchStatus("elIsMVALoose_singleLepCalc",1);
   inputTree->SetBranchStatus("elMiniIso_singleLepCalc",1);
   inputTree->SetBranchStatus("elIsTightBarrel_singleLepCalc",1);
   inputTree->SetBranchStatus("elIsMediumBarrel_singleLepCalc",1);
   inputTree->SetBranchStatus("elIsLooseBarrel_singleLepCalc",1);
   inputTree->SetBranchStatus("elIsVetoBarrel_singleLepCalc",1);
   inputTree->SetBranchStatus("elIsTIghtEndCap_singleLepCalc",1);
   inputTree->SetBranchStatus("elIsMediumEndCap_singleLepCalc",1);
   inputTree->SetBranchStatus("elIsLooseEndCap_singleLepCalc",1);
   inputTree->SetBranchStatus("elIsVetoEndCap_singleLepCalc",1);

   //muons
   inputTree->SetBranchStatus("muPt_singleLepCalc",1);
   inputTree->SetBranchStatus("muEta_singleLepCalc",1);
   inputTree->SetBranchStatus("muPhi_singleLepCalc",1);
   inputTree->SetBranchStatus("muEnergy_singleLepCalc",1);
   inputTree->SetBranchStatus("muDxy_singleLepCalc",1);
   inputTree->SetBranchStatus("muDz_singleLepCalc",1);
   inputTree->SetBranchStatus("muCharge_singleLepCalc",1);
   inputTree->SetBranchStatus("muMiniIso_singleLepCalc",1);
   inputTree->SetBranchStatus("muIsTight_singleLepCalc",1);
   inputTree->SetBranchStatus("muIsMedium_singleLepCalc",1);
   inputTree->SetBranchStatus("muIsMediumPrompt_singleLepCalc",1);
   inputTree->SetBranchStatus("muIsLoose_singleLepCalc",1);

   //missing et
   inputTree->SetBranchStatus("corr_met_singleLepCalc",1);
   inputTree->SetBranchStatus("corr_met_phi_singleLepCalc",1);

   // genParticles
   inputTree->SetBranchStatus("genPt_singleLepCalc",1);
   inputTree->SetBranchStatus("genEta_singleLepCalc",1);
   inputTree->SetBranchStatus("genPhi_singleLepCalc",1);
   inputTree->SetBranchStatus("genEnergy_singleLepCalc",1);
   inputTree->SetBranchStatus("genStatus_singleLepCalc",1);
   inputTree->SetBranchStatus("genID_singleLepCalc",1);
   inputTree->SetBranchStatus("genMotherID_singleLepCalc",1);
   inputTree->SetBranchStatus("genJetPt_singleLepCalc",1);
   inputTree->SetBranchStatus("genJetEta_singleLepCalc",1);
   inputTree->SetBranchStatus("genJetPhi_singleLepCalc",1);
   inputTree->SetBranchStatus("genJetEnergy_singleLepCalc",1);

   //boosted truth
   inputTree->SetBranchStatus("HadronicVHtPt_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtEta_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtPhi_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtEnergy_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtID_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtD0Pt_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtD0Eta_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtD0Phi_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtD0E_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtD1Pt_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtD1Eta_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtD1Phi_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtD1E_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtD2Pt_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtD2Eta_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtD2Phi_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtD2E_JetSubCalc",1);

   //jets
   inputTree->SetBranchStatus("AK4JetFlav_singleLepCalc",1);
//    inputTree->SetBranchStatus("theJetPFlav_JetSubCalc",1);
   inputTree->SetBranchStatus("AK4JetPt_singleLepCalc",1);
   inputTree->SetBranchStatus("AK4JetEta_singleLepCalc",1);
   inputTree->SetBranchStatus("AK4JetPhi_singleLepCalc",1);
   inputTree->SetBranchStatus("AK4JetEnergy_singleLepCalc",1);
   inputTree->SetBranchStatus("AK4JetBDisc_singleLepCalc",1);
   inputTree->SetBranchStatus("AK4JetBDeepCSVb_singleLepCalc",1);
   inputTree->SetBranchStatus("AK4JetBDeepCSVbb_singleLepCalc",1);
   inputTree->SetBranchStatus("AK4JetBDeepCSVudsg_singleLepCalc",1);
   inputTree->SetBranchStatus("AK4JetBTag_singleLepCalc",1); // --> POSSIBLY INCORRECTLY IMPLEMENTED IN LJMET. CHECK! 9 Nov 2018 (https://github.com/jmhogan/Ljmet-Com/blob/CMSSW_9_4_X/src/singleLepCalc.cc#L1206)
   inputTree->SetBranchStatus("theJetBTag_JetSubCalc",1); // ---> USE THIS INSTEAD FOR NOW, 9 NOV 2018.
   inputTree->SetBranchStatus("AK4JetBTag_bSFup_singleLepCalc",1);
   inputTree->SetBranchStatus("AK4JetBTag_bSFdn_singleLepCalc",1);
   inputTree->SetBranchStatus("AK4JetBTag_lSFup_singleLepCalc",1);
   inputTree->SetBranchStatus("AK4JetBTag_lSFdn_singleLepCalc",1);
   
   
   //top
   inputTree->SetBranchStatus("ttbarMass_TTbarMassCalc",1);
   
   //LHE weights
   inputTree->SetBranchStatus("LHEweightids_singleLepCalc",1);
   inputTree->SetBranchStatus("LHEweights_singleLepCalc",1);

  // ----------------------------------------------------------------------------
  // Create output tree and define branches
  // ----------------------------------------------------------------------------
   
   // OUTPUT FILE
   outputFile->cd();
   TTree *outputTree = new TTree("ljmet","ljmet");

   int NJetsWtagged_0p6;
   bool isPassTrilepton;    	    
   int isEEE;
   int isEEM;
   int isEMM;
   int isMMM;
   int isTTT;
   int isTTL;
   int isTLT;
   int isLTT;
   int isTLL;
   int isLTL;
   int isLLT;
   int isLLL;
   float leadWJetPtak8;
   float topPtWeightPast400;
   float topPtWeightHighPt;
   float minDR_leadAK8otherAK8;
   std::vector<float> minDR_lepJets;
   std::vector<float> deltaR_lepBJets;
   std::vector<float> minDR_lepBJets;
   std::vector<float> deltaR_lepClosestJet;
   std::vector<float> PtRelLepClosestJet;
   
   float Mll_sameFlavorOS; //inv mass of opposite sign same flavor leps (high pt lep pairs as priority)
   std::vector<float> MllOS_allComb; // all permutation between OS trilep pairs 
   float MllOS_allComb_min; 
   float MllOS_allComb_max; 
   float Mlll; //inv mass top 3 leptons

   std::vector<float> leadWJetPtak8_shifts;
   std::vector<float> pdfWeights;
   std::vector<float> theJetAK8SoftDropMass_JetSubCalc_PtOrdered;
   std::vector<float> theJetAK8NjettinessTau3_JetSubCalc_PtOrdered;
   std::vector<float> theJetAK8MaxSubCSV_JetSubCalc_PtOrdered;

   //ID and PtOrdered
   std::vector<float> AllLeptonElPt_PtOrdered;
   std::vector<float> AllLeptonElEta_PtOrdered;
   std::vector<float> AllLeptonElPhi_PtOrdered;
   std::vector<float> AllLeptonElEnergy_PtOrdered;
   std::vector<float> AllLeptonElMiniIso_PtOrdered;
   std::vector<int> AllLeptonElFlavor_PtOrdered;
   std::vector<int> AllLeptonElIsTight_PtOrdered;
   std::vector<float> AllLeptonElDxy_PtOrdered;
   std::vector<float> AllLeptonElDz_PtOrdered;
   int AllLeptonElCount_PtOrdered;

   std::vector<float> AllLeptonMuPt_PtOrdered;
   std::vector<float> AllLeptonMuEta_PtOrdered;
   std::vector<float> AllLeptonMuPhi_PtOrdered;
   std::vector<float> AllLeptonMuEnergy_PtOrdered;
   std::vector<float> AllLeptonMuMiniIso_PtOrdered;
   std::vector<int> AllLeptonMuFlavor_PtOrdered;
   std::vector<int> AllLeptonMuIsTight_PtOrdered;
   std::vector<float> AllLeptonMuDxy_PtOrdered;
   std::vector<float> AllLeptonMuDz_PtOrdered;
   int AllLeptonMuCount_PtOrdered;

   std::vector<float> AllLeptonPt_PtOrdered;
   std::vector<float> AllLeptonEta_PtOrdered;
   std::vector<float> AllLeptonPhi_PtOrdered;
   std::vector<float> AllLeptonEnergy_PtOrdered;
   std::vector<float> AllLeptonMiniIso_PtOrdered;
   std::vector<int> AllLeptonFlavor_PtOrdered;
   std::vector<int> AllLeptonIsTight_PtOrdered;
   std::vector<int> AllLeptonCharge_PtOrdered;
   std::vector<int> AllLeptonIdx_PtOrdered;
   std::vector<float> AllLeptonDxy_PtOrdered;
   std::vector<float> AllLeptonDz_PtOrdered;
   int AllLeptonCount_PtOrdered;
   
   //PtOrderedOnly
   std::vector<float> AllLeptonElPt_PtOrderedOnly;
   std::vector<float> AllLeptonElEta_PtOrderedOnly;
   std::vector<float> AllLeptonElPhi_PtOrderedOnly;
   std::vector<float> AllLeptonElEnergy_PtOrderedOnly;
   std::vector<float> AllLeptonElMiniIso_PtOrderedOnly;
   std::vector<int> AllLeptonElFlavor_PtOrderedOnly;
   std::vector<int> AllLeptonElIsTight_PtOrderedOnly;
   std::vector<float> AllLeptonElDxy_PtOrderedOnly;
   std::vector<float> AllLeptonElDz_PtOrderedOnly;

   std::vector<float> AllLeptonMuPt_PtOrderedOnly;
   std::vector<float> AllLeptonMuEta_PtOrderedOnly;
   std::vector<float> AllLeptonMuPhi_PtOrderedOnly;
   std::vector<float> AllLeptonMuEnergy_PtOrderedOnly;
   std::vector<float> AllLeptonMuMiniIso_PtOrderedOnly;
   std::vector<int> AllLeptonMuFlavor_PtOrderedOnly;
   std::vector<int> AllLeptonMuIsTight_PtOrderedOnly;
   std::vector<float> AllLeptonMuDxy_PtOrderedOnly;
   std::vector<float> AllLeptonMuDz_PtOrderedOnly;

   std::vector<float> AllLeptonPt_PtOrderedOnly;
   std::vector<float> AllLeptonEta_PtOrderedOnly;
   std::vector<float> AllLeptonPhi_PtOrderedOnly;
   std::vector<float> AllLeptonEnergy_PtOrderedOnly;
   std::vector<float> AllLeptonMiniIso_PtOrderedOnly;
   std::vector<int> AllLeptonFlavor_PtOrderedOnly;
   std::vector<int> AllLeptonIsTight_PtOrderedOnly;
   std::vector<int> AllLeptonCharge_PtOrderedOnly;
   std::vector<int> AllLeptonIdx_PtOrderedOnly;
   std::vector<float> AllLeptonDxy_PtOrderedOnly;
   std::vector<float> AllLeptonDz_PtOrderedOnly;

   //PtOrderedOnly_top3 (of default) -> re-sorting top 3 of default ordering.
   std::vector<float> AllLeptonElPt_PtOrderedOnly_top3;
   std::vector<float> AllLeptonElEta_PtOrderedOnly_top3;
   std::vector<float> AllLeptonElPhi_PtOrderedOnly_top3;
   std::vector<float> AllLeptonElEnergy_PtOrderedOnly_top3;
   std::vector<float> AllLeptonElMiniIso_PtOrderedOnly_top3;
   std::vector<int> AllLeptonElFlavor_PtOrderedOnly_top3;
   std::vector<int> AllLeptonElIsTight_PtOrderedOnly_top3;

   std::vector<float> AllLeptonMuPt_PtOrderedOnly_top3;
   std::vector<float> AllLeptonMuEta_PtOrderedOnly_top3;
   std::vector<float> AllLeptonMuPhi_PtOrderedOnly_top3;
   std::vector<float> AllLeptonMuEnergy_PtOrderedOnly_top3;
   std::vector<float> AllLeptonMuMiniIso_PtOrderedOnly_top3;
   std::vector<int> AllLeptonMuFlavor_PtOrderedOnly_top3;
   std::vector<int> AllLeptonMuIsTight_PtOrderedOnly_top3;

   std::vector<float> AllLeptonPt_PtOrderedOnly_top3;
   std::vector<float> AllLeptonEta_PtOrderedOnly_top3;
   std::vector<float> AllLeptonPhi_PtOrderedOnly_top3;
   std::vector<float> AllLeptonEnergy_PtOrderedOnly_top3;
   std::vector<float> AllLeptonMiniIso_PtOrderedOnly_top3;
   std::vector<int> AllLeptonFlavor_PtOrderedOnly_top3;
   std::vector<int> AllLeptonIsTight_PtOrderedOnly_top3;
   std::vector<int> AllLeptonCharge_PtOrderedOnly_top3;
   std::vector<int> AllLeptonIdx_PtOrderedOnly_top3;

   std::vector<float> TightLeptonPt_PtOrdered;
   std::vector<float> TightLeptonEta_PtOrdered;
   std::vector<float> TightLeptonPhi_PtOrdered;
   std::vector<float> TightLeptonEnergy_PtOrdered;
   std::vector<float> TightLeptonMiniIso_PtOrdered;
   std::vector<int> TightLeptonFlavor_PtOrdered;
   std::vector<int> TightLeptonCharge_PtOrdered;
   std::vector<int> TightLeptonIdx_PtOrdered;
   
   std::vector<int> theJetAK8Wmatch_JetSubCalc_PtOrdered;
   std::vector<int> NJetsWtagged_0p6_shifts;
   std::vector<float> ddBkgWeights;
//    std::vector<pair<float,float> > ddBkgWeights_scan;
//    std::vector<map<float,float> > ddBkgWeights_scan;
   std::vector<float> ddBkgWeights_scan;
   std::vector<float> ddBkgWeights_scan_muFR;
   std::vector<float> ddBkgWeights_scan_elFR;
   
   int MCPastTrigger_dilep;
   int DataPastTrigger_dilep;

   outputTree->Branch("event_CommonCalc",&event_CommonCalc,"event_CommonCalc/I");
   outputTree->Branch("run_CommonCalc",&run_CommonCalc,"run_CommonCalc/I");
   outputTree->Branch("lumi_CommonCalc",&lumi_CommonCalc,"lumi_CommonCalc/I");
   outputTree->Branch("nPV_singleLepCalc",&nPV_singleLepCalc,"nPV_singleLepCalc/I");
   outputTree->Branch("nTrueInteractions_singleLepCalc",&nTrueInteractions_singleLepCalc,"nTrueInteractions_singleLepCalc/I");
   outputTree->Branch("isElectron",&isElectron,"isElectron/I");
   outputTree->Branch("isMuon",&isMuon,"isMuon/I");
   outputTree->Branch("MCPastTrigger",&MCPastTrigger,"MCPastTrigger/I");
   outputTree->Branch("DataPastTrigger",&DataPastTrigger,"DataPastTrigger/I");
   outputTree->Branch("isTHBW_TpTpCalc",&isTHBW_TpTpCalc,"isTHBW_TpTpCalc/O");
   outputTree->Branch("isTHTH_TpTpCalc",&isTHTH_TpTpCalc,"isTHTH_TpTpCalc/O");
   outputTree->Branch("isBWBW_TpTpCalc",&isBWBW_TpTpCalc,"isBWBW_TpTpCalc/O");
   outputTree->Branch("isTZBW_TpTpCalc",&isTZBW_TpTpCalc,"isTZBW_TpTpCalc/O");
   outputTree->Branch("isTZTH_TpTpCalc",&isTZTH_TpTpCalc,"isTZTH_TpTpCalc/O");
   outputTree->Branch("isTZTZ_TpTpCalc",&isTZTZ_TpTpCalc,"isTZTZ_TpTpCalc/O");
   outputTree->Branch("isBHTW_TpTpCalc",&isBHTW_TpTpCalc,"isBHTW_TpTpCalc/O");
   outputTree->Branch("isBHBH_TpTpCalc",&isBHBH_TpTpCalc,"isBHBH_TpTpCalc/O");
   outputTree->Branch("isTWTW_TpTpCalc",&isTWTW_TpTpCalc,"isTWTW_TpTpCalc/O");
   outputTree->Branch("isBZTW_TpTpCalc",&isBZTW_TpTpCalc,"isBZTW_TpTpCalc/O");
   outputTree->Branch("isBZBH_TpTpCalc",&isBZBH_TpTpCalc,"isBZBH_TpTpCalc/O");
   outputTree->Branch("isBZBZ_TpTpCalc",&isBZBZ_TpTpCalc,"isBZBZ_TpTpCalc/O");
   outputTree->Branch("tPrimePt_TpTpCalc",&tPrimePt_TpTpCalc,"tPrimePt_TpTpCalc/O");
   outputTree->Branch("NLeptonDecays_TpTpCalc",&NLeptonDecays_TpTpCalc,"NLeptonDecays_TpTpCalc/I");
   outputTree->Branch("MCWeight_singleLepCalc",&MCWeight_singleLepCalc,"MCWeight_singleLepCalc/D");
   outputTree->Branch("renormWeights",&renormWeights);
   outputTree->Branch("pdfWeights",&pdfWeights);
   outputTree->Branch("pileupWeight",&pileupWeight,"pileupWeight/F");
   outputTree->Branch("pileupWeightUp",&pileupWeightUp,"pileupWeightUp/F");
   outputTree->Branch("pileupWeightDown",&pileupWeightDown,"pileupWeightDown/F");
   outputTree->Branch("TrigEffAltWeight",&TrigEffAltWeight,"TrigEffAltWeight/F");
   outputTree->Branch("TrigEffWeight",&TrigEffWeight,"TrigEffWeight/F");
   outputTree->Branch("TrigEffWeightUncert",&TrigEffWeightUncert,"TrigEffWeightUncert/F");
   outputTree->Branch("isoSF",&isoSF,"isoSF/F");
   outputTree->Branch("lepIdSF",&lepIdSF,"lepIdSF/F");
   outputTree->Branch("EGammaGsfSF",&EGammaGsfSF,"EGammaGsfSF/F");
   outputTree->Branch("MuTrkSF",&MuTrkSF,"MuTrkSF/F");

   outputTree->Branch("isPassTrilepton",&isPassTrilepton,"isPassTrilepton/O");
   outputTree->Branch("isEEE",&isEEE,"isEEE/I");
   outputTree->Branch("isEEM",&isEEM,"isEEM/I");
   outputTree->Branch("isEMM",&isEMM,"isEMM/I");
   outputTree->Branch("isMMM",&isMMM,"isMMM/I");
   outputTree->Branch("isTTT",&isTTT,"isTTT/I");
   outputTree->Branch("isTTL",&isTTL,"isTTL/I");
   outputTree->Branch("isTLT",&isTLT,"isTLT/I");
   outputTree->Branch("isLTT",&isLTT,"isLTT/I");
   outputTree->Branch("isTLL",&isTLL,"isTLL/I");
   outputTree->Branch("isLTL",&isLTL,"isLTL/I");
   outputTree->Branch("isLLT",&isLLT,"isLLT/I");
   outputTree->Branch("isLLL",&isLLL,"isLLL/I");
   
   outputTree->Branch("MCPastTrigger",&MCPastTrigger,"MCPastTrigger/I");
   outputTree->Branch("DataPastTrigger",&DataPastTrigger,"DataPastTrigger/I");

   outputTree->Branch("MCPastTrigger_dilep",&MCPastTrigger_dilep,"MCPastTrigger_dilep/I");
   outputTree->Branch("DataPastTrigger_dilep",&DataPastTrigger_dilep,"DataPastTrigger_dilep/I");


   outputTree->Branch("ttbarMass_TTbarMassCalc",&ttbarMass_TTbarMassCalc,"ttbarMass_TTbarMassCalc/D");
   outputTree->Branch("corr_met_singleLepCalc",&corr_met_singleLepCalc,"corr_met_singleLepCalc/D");
   outputTree->Branch("corr_met_phi_singleLepCalc",&corr_met_phi_singleLepCalc,"corr_met_phi_singleLepCalc/D");
   outputTree->Branch("leptonPt_singleLepCalc",&leptonPt_singleLepCalc,"leptonPt_singleLepCalc/F");
   outputTree->Branch("leptonEta_singleLepCalc",&leptonEta_singleLepCalc,"leptonEta_singleLepCalc/F");
   outputTree->Branch("leptonPhi_singleLepCalc",&leptonPhi_singleLepCalc,"leptonPhi_singleLepCalc/F");
   outputTree->Branch("leptonEnergy_singleLepCalc",&leptonEnergy_singleLepCalc,"leptonEnergy_singleLepCalc/F");
   outputTree->Branch("leptonMiniIso_singleLepCalc",&leptonMiniIso_singleLepCalc,"leptonMiniIso_singleLepCalc/F");
   outputTree->Branch("leptonRelIso_singleLepCalc",&leptonRelIso_singleLepCalc,"leptonRelIso_singleLepCalc/F");
   outputTree->Branch("leptonDxy_singleLepCalc",&leptonDxy_singleLepCalc,"leptonDxy_singleLepCalc/F");
   outputTree->Branch("leptonDz_singleLepCalc",&leptonDz_singleLepCalc,"leptonDz_singleLepCalc/F");
   outputTree->Branch("leptonCharge_singleLepCalc",&leptonCharge_singleLepCalc,"leptonCharge_singleLepCalc/I");
   outputTree->Branch("elTrigPresel_singleLepCalc",&elTrigPresel_singleLepCalc,"elTrigPresel_singleLepCalc/I");
   outputTree->Branch("elNotConversion_singleLepCalc",&elNotConversion_singleLepCalc,"elNotConversion_singleLepCalc/I");

//electrons, ID and pt ordered
   outputTree->Branch("AllLeptonElPt_PtOrdered",&AllLeptonElPt_PtOrdered);
   outputTree->Branch("AllLeptonElEta_PtOrdered",&AllLeptonElEta_PtOrdered);
   outputTree->Branch("AllLeptonElPhi_PtOrdered",&AllLeptonElPhi_PtOrdered);
   outputTree->Branch("AllLeptonElEnergy_PtOrdered",&AllLeptonElEnergy_PtOrdered);
   outputTree->Branch("AllLeptonElMiniIso_PtOrdered",&AllLeptonElMiniIso_PtOrdered);
   outputTree->Branch("AllLeptonElFlavor_PtOrdered",&AllLeptonElFlavor_PtOrdered);
   outputTree->Branch("AllLeptonElIsTight_PtOrdered",&AllLeptonElIsTight_PtOrdered);
   outputTree->Branch("AllLeptonElCount_PtOrdered",&AllLeptonElCount_PtOrdered,"AllLeptonElCount_PtOrdered/I");
   outputTree->Branch("AllLeptonElDxy_PtOrdered",&AllLeptonElDxy_PtOrdered);
   outputTree->Branch("AllLeptonElDz_PtOrdered",&AllLeptonElDz_PtOrdered);

//electrons, pt ordered
   outputTree->Branch("AllLeptonElPt_PtOrderedOnly",&AllLeptonElPt_PtOrderedOnly);
   outputTree->Branch("AllLeptonElEta_PtOrderedOnly",&AllLeptonElEta_PtOrderedOnly);
   outputTree->Branch("AllLeptonElPhi_PtOrderedOnly",&AllLeptonElPhi_PtOrderedOnly);
   outputTree->Branch("AllLeptonElEnergy_PtOrderedOnly",&AllLeptonElEnergy_PtOrderedOnly);
   outputTree->Branch("AllLeptonElMiniIso_PtOrderedOnly",&AllLeptonElMiniIso_PtOrderedOnly);
   outputTree->Branch("AllLeptonElFlavor_PtOrderedOnly",&AllLeptonElFlavor_PtOrderedOnly);
   outputTree->Branch("AllLeptonElIsTight_PtOrderedOnly",&AllLeptonElIsTight_PtOrderedOnly);
   outputTree->Branch("AllLeptonElDxy_PtOrderedOnly",&AllLeptonElDxy_PtOrderedOnly);
   outputTree->Branch("AllLeptonElDz_PtOrderedOnly",&AllLeptonElDz_PtOrderedOnly);

//electrons, pt ordered only for top3
   outputTree->Branch("AllLeptonElPt_PtOrderedOnly_top3",&AllLeptonElPt_PtOrderedOnly_top3);
   outputTree->Branch("AllLeptonElEta_PtOrderedOnly_top3",&AllLeptonElEta_PtOrderedOnly_top3);
   outputTree->Branch("AllLeptonElPhi_PtOrderedOnly_top3",&AllLeptonElPhi_PtOrderedOnly_top3);
   outputTree->Branch("AllLeptonElEnergy_PtOrderedOnly_top3",&AllLeptonElEnergy_PtOrderedOnly_top3);
   outputTree->Branch("AllLeptonElMiniIso_PtOrderedOnly_top3",&AllLeptonElMiniIso_PtOrderedOnly_top3);
   outputTree->Branch("AllLeptonElFlavor_PtOrderedOnly_top3",&AllLeptonElFlavor_PtOrderedOnly_top3);
   outputTree->Branch("AllLeptonElIsTight_PtOrderedOnly_top3",&AllLeptonElIsTight_PtOrderedOnly_top3);

//muons, ID and pt ordered
   outputTree->Branch("AllLeptonMuPt_PtOrdered",&AllLeptonMuPt_PtOrdered);
   outputTree->Branch("AllLeptonMuEta_PtOrdered",&AllLeptonMuEta_PtOrdered);
   outputTree->Branch("AllLeptonMuPhi_PtOrdered",&AllLeptonMuPhi_PtOrdered);
   outputTree->Branch("AllLeptonMuEnergy_PtOrdered",&AllLeptonMuEnergy_PtOrdered);
   outputTree->Branch("AllLeptonMuMiniIso_PtOrdered",&AllLeptonMuMiniIso_PtOrdered);
   outputTree->Branch("AllLeptonMuFlavor_PtOrdered",&AllLeptonMuFlavor_PtOrdered);
   outputTree->Branch("AllLeptonMuIsTight_PtOrdered",&AllLeptonMuIsTight_PtOrdered);
   outputTree->Branch("AllLeptonMuCount_PtOrdered",&AllLeptonMuCount_PtOrdered,"AllLeptonMuCount_PtOrdered/I");
   outputTree->Branch("AllLeptonMuDxy_PtOrdered",&AllLeptonMuDxy_PtOrdered);
   outputTree->Branch("AllLeptonMuDz_PtOrdered",&AllLeptonMuDz_PtOrdered);

//muons, pt ordered
   outputTree->Branch("AllLeptonMuPt_PtOrderedOnly",&AllLeptonMuPt_PtOrderedOnly);
   outputTree->Branch("AllLeptonMuEta_PtOrderedOnly",&AllLeptonMuEta_PtOrderedOnly);
   outputTree->Branch("AllLeptonMuPhi_PtOrderedOnly",&AllLeptonMuPhi_PtOrderedOnly);
   outputTree->Branch("AllLeptonMuEnergy_PtOrderedOnly",&AllLeptonMuEnergy_PtOrderedOnly);
   outputTree->Branch("AllLeptonMuMiniIso_PtOrderedOnly",&AllLeptonMuMiniIso_PtOrderedOnly);
   outputTree->Branch("AllLeptonMuFlavor_PtOrderedOnly",&AllLeptonMuFlavor_PtOrderedOnly);
   outputTree->Branch("AllLeptonMuIsTight_PtOrderedOnly",&AllLeptonMuIsTight_PtOrderedOnly);
   outputTree->Branch("AllLeptonMuDxy_PtOrderedOnly",&AllLeptonMuDxy_PtOrderedOnly);
   outputTree->Branch("AllLeptonMuDz_PtOrderedOnly",&AllLeptonMuDz_PtOrderedOnly);

//muons, pt ordered only for top3
   outputTree->Branch("AllLeptonMuPt_PtOrderedOnly_top3",&AllLeptonMuPt_PtOrderedOnly_top3);
   outputTree->Branch("AllLeptonMuEta_PtOrderedOnly_top3",&AllLeptonMuEta_PtOrderedOnly_top3);
   outputTree->Branch("AllLeptonMuPhi_PtOrderedOnly_top3",&AllLeptonMuPhi_PtOrderedOnly_top3);
   outputTree->Branch("AllLeptonMuEnergy_PtOrderedOnly_top3",&AllLeptonMuEnergy_PtOrderedOnly_top3);
   outputTree->Branch("AllLeptonMuMiniIso_PtOrderedOnly_top3",&AllLeptonMuMiniIso_PtOrderedOnly_top3);
   outputTree->Branch("AllLeptonMuFlavor_PtOrderedOnly_top3",&AllLeptonMuFlavor_PtOrderedOnly_top3);
   outputTree->Branch("AllLeptonMuIsTight_PtOrderedOnly_top3",&AllLeptonMuIsTight_PtOrderedOnly_top3);

//leptons, ID and pt ordered
   outputTree->Branch("AllLeptonPt_PtOrdered",&AllLeptonPt_PtOrdered);
   outputTree->Branch("AllLeptonEta_PtOrdered",&AllLeptonEta_PtOrdered);
   outputTree->Branch("AllLeptonPhi_PtOrdered",&AllLeptonPhi_PtOrdered);
   outputTree->Branch("AllLeptonEnergy_PtOrdered",&AllLeptonEnergy_PtOrdered);
   outputTree->Branch("AllLeptonMiniIso_PtOrdered",&AllLeptonMiniIso_PtOrdered);
   outputTree->Branch("AllLeptonFlavor_PtOrdered",&AllLeptonFlavor_PtOrdered);
   outputTree->Branch("AllLeptonIsTight_PtOrdered",&AllLeptonIsTight_PtOrdered);
   outputTree->Branch("AllLeptonCharge_PtOrdered",&AllLeptonCharge_PtOrdered);
   outputTree->Branch("AllLeptonCount_PtOrdered",&AllLeptonCount_PtOrdered,"AllLeptonCount_PtOrdered/I");
   outputTree->Branch("AllLeptonDxy_PtOrdered",&AllLeptonDxy_PtOrdered);
   outputTree->Branch("AllLeptonDz_PtOrdered",&AllLeptonDz_PtOrdered);


//leptons, pt ordered
   outputTree->Branch("AllLeptonPt_PtOrderedOnly",&AllLeptonPt_PtOrderedOnly);
   outputTree->Branch("AllLeptonEta_PtOrderedOnly",&AllLeptonEta_PtOrderedOnly);
   outputTree->Branch("AllLeptonPhi_PtOrderedOnly",&AllLeptonPhi_PtOrderedOnly);
   outputTree->Branch("AllLeptonEnergy_PtOrderedOnly",&AllLeptonEnergy_PtOrderedOnly);
   outputTree->Branch("AllLeptonMiniIso_PtOrderedOnly",&AllLeptonMiniIso_PtOrderedOnly);
   outputTree->Branch("AllLeptonFlavor_PtOrderedOnly",&AllLeptonFlavor_PtOrderedOnly);
   outputTree->Branch("AllLeptonIsTight_PtOrderedOnly",&AllLeptonIsTight_PtOrderedOnly);
   outputTree->Branch("AllLeptonCharge_PtOrderedOnly",&AllLeptonCharge_PtOrderedOnly);
   outputTree->Branch("AllLeptonDxy_PtOrderedOnly",&AllLeptonDxy_PtOrderedOnly);
   outputTree->Branch("AllLeptonDz_PtOrderedOnly",&AllLeptonDz_PtOrderedOnly);

//leptons, pt ordered only for top3
   outputTree->Branch("AllLeptonPt_PtOrderedOnly_top3",&AllLeptonPt_PtOrderedOnly_top3);
   outputTree->Branch("AllLeptonEta_PtOrderedOnly_top3",&AllLeptonEta_PtOrderedOnly_top3);
   outputTree->Branch("AllLeptonPhi_PtOrderedOnly_top3",&AllLeptonPhi_PtOrderedOnly_top3);
   outputTree->Branch("AllLeptonEnergy_PtOrderedOnly_top3",&AllLeptonEnergy_PtOrderedOnly_top3);
   outputTree->Branch("AllLeptonMiniIso_PtOrderedOnly_top3",&AllLeptonMiniIso_PtOrderedOnly_top3);
   outputTree->Branch("AllLeptonFlavor_PtOrderedOnly_top3",&AllLeptonFlavor_PtOrderedOnly_top3);
   outputTree->Branch("AllLeptonIsTight_PtOrderedOnly_top3",&AllLeptonIsTight_PtOrderedOnly_top3);
   outputTree->Branch("AllLeptonCharge_PtOrderedOnly_top3",&AllLeptonCharge_PtOrderedOnly_top3);


   outputTree->Branch("TightLeptonPt_PtOrdered",&TightLeptonPt_PtOrdered);
   outputTree->Branch("TightLeptonEta_PtOrdered",&TightLeptonEta_PtOrdered);
   outputTree->Branch("TightLeptonPhi_PtOrdered",&TightLeptonPhi_PtOrdered);
   outputTree->Branch("TightLeptonEnergy_PtOrdered",&TightLeptonEnergy_PtOrdered);
   outputTree->Branch("TightLeptonMiniIso_PtOrdered",&TightLeptonMiniIso_PtOrdered);
   outputTree->Branch("TightLeptonFlavor_PtOrdered",&TightLeptonFlavor_PtOrdered);
   outputTree->Branch("TightLeptonCharge_PtOrdered",&TightLeptonCharge_PtOrdered);


   outputTree->Branch("AK4JetPt_singleLepCalc_PtOrdered",&AK4JetPt_singleLepCalc_PtOrdered);
   outputTree->Branch("AK4JetEta_singleLepCalc_PtOrdered",&AK4JetEta_singleLepCalc_PtOrdered);
   outputTree->Branch("AK4JetPhi_singleLepCalc_PtOrdered",&AK4JetPhi_singleLepCalc_PtOrdered);
   outputTree->Branch("AK4JetEnergy_singleLepCalc_PtOrdered",&AK4JetEnergy_singleLepCalc_PtOrdered);
   outputTree->Branch("AK4JetFlav_singleLepCalc_PtOrdered",&AK4JetFlav_singleLepCalc_PtOrdered);
   outputTree->Branch("AK4JetBTag_singleLepCalc_PtOrdered",&AK4JetBTag_singleLepCalc_PtOrdered); 
   outputTree->Branch("AK4JetBTag_bSFup_singleLepCalc_PtOrdered",&AK4JetBTag_bSFup_singleLepCalc_PtOrdered);
   outputTree->Branch("AK4JetBTag_bSFdn_singleLepCalc_PtOrdered",&AK4JetBTag_bSFdn_singleLepCalc_PtOrdered);
   outputTree->Branch("AK4JetBTag_lSFup_singleLepCalc_PtOrdered",&AK4JetBTag_lSFup_singleLepCalc_PtOrdered);
   outputTree->Branch("AK4JetBTag_lSFdn_singleLepCalc_PtOrdered",&AK4JetBTag_lSFdn_singleLepCalc_PtOrdered);
   outputTree->Branch("HadronicVHtID_JetSubCalc",&HadronicVHtID_JetSubCalc);
   outputTree->Branch("HadronicVHtPt_JetSubCalc",&HadronicVHtPt_JetSubCalc);
   outputTree->Branch("HadronicVHtEta_JetSubCalc",&HadronicVHtEta_JetSubCalc);
   outputTree->Branch("HadronicVHtPhi_JetSubCalc",&HadronicVHtPhi_JetSubCalc);
   outputTree->Branch("HadronicVHtEnergy_JetSubCalc",&HadronicVHtEnergy_JetSubCalc);
   outputTree->Branch("genJetPt_singleLepCalc",&genJetPt_singleLepCalc);
   outputTree->Branch("genJetEta_singleLepCalc",&genJetEta_singleLepCalc);
   outputTree->Branch("genJetPhi_singleLepCalc",&genJetPhi_singleLepCalc);
   outputTree->Branch("genJetEnergy_singleLepCalc",&genJetEnergy_singleLepCalc);
   outputTree->Branch("BJetLeadPt",&BJetLeadPt,"BJetLeadPt/F");
   outputTree->Branch("BJetLeadPt_shifts",&BJetLeadPt_shifts);
   outputTree->Branch("WJetLeadPt",&WJetLeadPt,"WJetLeadPt/F");
   outputTree->Branch("WJetLeadPt_shifts",&WJetLeadPt_shifts);
   outputTree->Branch("TJetLeadPt",&TJetLeadPt,"TJetLeadPt/F");
   outputTree->Branch("TJetLeadPt_shifts",&TJetLeadPt_shifts);
   outputTree->Branch("AK4HTpMETpLepPt",&AK4HTpMETpLepPt,"AK4HTpMETpLepPt/F");
   outputTree->Branch("AK4HT",&AK4HT,"AK4HT/F");
   
   outputTree->Branch("ddBkgWeights",&ddBkgWeights);
   outputTree->Branch("ddBkgWeights_scan",&ddBkgWeights_scan);
   outputTree->Branch("ddBkgWeights_scan_muFR",&ddBkgWeights_scan_muFR);
   outputTree->Branch("ddBkgWeights_scan_elFR",&ddBkgWeights_scan_elFR);

   outputTree->Branch("NJets_singleLepCalc",&NJets_singleLepCalc,"NJets_singleLepCalc/I");
   outputTree->Branch("NJetsAK8_JetSubCalc",&NJetsAK8_JetSubCalc,"NJetsAK8_JetSubCalc/I");
   outputTree->Branch("NJetsBTag_singleLepCalc",&NJetsBTag_singleLepCalc,"NJetsBTag_singleLepCalc/I");
   outputTree->Branch("NJetsBTagwithSF_singleLepCalc",&NJetsBTagwithSF_singleLepCalc,"NJetsBTagwithSF_singleLepCalc/I");
   outputTree->Branch("NJetsBTagwithSF_singleLepCalc_shifts",&NJetsBTagwithSF_singleLepCalc_shifts);
   outputTree->Branch("NJetsBTagwithSF_singleLepCalc_noLepCorr",&NJetsBTagwithSF_singleLepCalc_noLepCorr,"NJetsBTagwithSF_singleLepCalc_noLepCorr/I");
   outputTree->Branch("NJetsBTagwithSF_singleLepCalc_noLepCorr_shifts",&NJetsBTagwithSF_singleLepCalc_noLepCorr_shifts);
   outputTree->Branch("topPt",&topPt,"topPt/F");
   outputTree->Branch("topPtGen",&topPtGen,"topPtGen/F");
   outputTree->Branch("topMass",&topMass,"topMass/F");
   outputTree->Branch("minMleppBjet",&minMleppBjet,"minMleppBjet/F");
   outputTree->Branch("minMleppBjet_shifts",&minMleppBjet_shifts);
   outputTree->Branch("minMleppJet",&minMleppJet,"mixnMleppJet/F");
   outputTree->Branch("minMlllBjet",&minMlllBjet,"minMlllBjet/F");
   outputTree->Branch("minMlllBjet_shifts",&minMlllBjet_shifts);
   outputTree->Branch("genTopPt",&genTopPt,"genTopPt/F");
   outputTree->Branch("genAntiTopPt",&genAntiTopPt,"genAntiTopPt/F");
   outputTree->Branch("topPtWeight",&topPtWeight,"topPtWeight/F");
   outputTree->Branch("topPtWeightPast400",&topPtWeightPast400,"topPtWeightPast400/F");
   outputTree->Branch("topPtWeightHighPt",&topPtWeightHighPt,"topPtWeightHighPt/F");
   outputTree->Branch("deltaRlepJetInMinMljet",&deltaRlepJetInMinMljet,"deltaRlepJetInMinMljet/F");
   outputTree->Branch("deltaRlepbJetInMinMlb",&deltaRlepbJetInMinMlb,"deltaRlepbJetInMinMlb/F");
   outputTree->Branch("deltaRlepbJetInMinMlb_shifts",&deltaRlepbJetInMinMlb_shifts);
   outputTree->Branch("deltaPhilepJetInMinMljet",&deltaPhilepJetInMinMljet,"deltaPhilepJetInMinMljet/F");
   outputTree->Branch("deltaPhilepbJetInMinMlb",&deltaPhilepbJetInMinMlb,"deltaPhilepbJetInMinMlb/F");
   outputTree->Branch("deltaPhilepbJetInMinMlb_shifts",&deltaPhilepbJetInMinMlb_shifts);
   outputTree->Branch("deltaRtopWjet",&deltaRtopWjet,"deltaRtopWjet/F");
   outputTree->Branch("deltaRlepWjet",&deltaRlepWjet,"deltaRlepWjet/F");
   outputTree->Branch("deltaRlepTjet",&deltaRlepTjet,"deltaRlepTjet/F");
   outputTree->Branch("deltaPhitopWjet",&deltaPhitopWjet,"deltaPhitopWjet/F");
   outputTree->Branch("deltaPhilepWjet",&deltaPhilepWjet,"deltaPhilepWjet/F");
   outputTree->Branch("deltaPhilepTjet",&deltaPhilepTjet,"deltaPhilepTjet/F");
   outputTree->Branch("deltaRtopWjet_shifts",&deltaRtopWjet_shifts);
   outputTree->Branch("deltaRlepWjet_shifts",&deltaRlepWjet_shifts);
   outputTree->Branch("deltaRlepTjet_shifts",&deltaRlepTjet_shifts);
   outputTree->Branch("deltaPhitopWjet_shifts",&deltaPhitopWjet_shifts);
   outputTree->Branch("deltaPhilepWjet_shifts",&deltaPhilepWjet_shifts);
   outputTree->Branch("deltaPhilepTjet_shifts",&deltaPhilepTjet_shifts);
   outputTree->Branch("NJetsWtagged_0p6",&NJetsWtagged_0p6,"NJetsWtagged_0p6/I");
   outputTree->Branch("NJetsWtagged_0p6_shifts",&NJetsWtagged_0p6_shifts);
   outputTree->Branch("NJetsTtagged_0p81",&NJetsTtagged_0p81,"NJetsTtagged_0p81/I");
   outputTree->Branch("NJetsTtagged_0p81_shifts",&NJetsTtagged_0p81_shifts);
   outputTree->Branch("minDR_leadAK8otherAK8",&minDR_leadAK8otherAK8,"minDR_leadAK8otherAK8/F");
   outputTree->Branch("minDR_lepAK8",&minDR_lepAK8,"minDR_lepAK8/F");
   outputTree->Branch("minDR_lepJet",&minDR_lepJet,"minDR_lepJet/F");
   outputTree->Branch("minDR_lep1Jet",&minDR_lep1Jet,"minDR_lep1Jet/F");
   outputTree->Branch("minDR_lep2Jet",&minDR_lep2Jet,"minDR_lep2Jet/F");
   outputTree->Branch("minDR_lep3Jet",&minDR_lep3Jet,"minDR_lep3Jet/F");
   outputTree->Branch("minDR_lepMET",&minDR_lepMET,"minDR_lepMET/F");
   outputTree->Branch("minDR_METJet",&minDR_METJet,"minDR_METJet/F");
   outputTree->Branch("minDPhi_METJet",&minDPhi_METJet,"minDPhi_METJet/F");
   outputTree->Branch("ptRel_minDRlepJet",&ptRel_minDRlepJet,"ptRel_minDRlepJet/F");
   outputTree->Branch("ptRel_minDRlep1Jet",&ptRel_minDRlep1Jet,"ptRel_minDRlep1Jet/F");
   outputTree->Branch("ptRel_minDRlep2Jet",&ptRel_minDRlep2Jet,"ptRel_minDRlep2Jet/F");
   outputTree->Branch("ptRel_minDRlep3Jet",&ptRel_minDRlep3Jet,"ptRel_minDRlep3Jet/F");
   outputTree->Branch("MT_lepMet",&MT_lepMet,"MT_lepMet/F");
   outputTree->Branch("deltaR_lepJets",&deltaR_lepJets);
   outputTree->Branch("deltaR_lep1Jets",&deltaR_lep1Jets);
   outputTree->Branch("deltaR_lep2Jets",&deltaR_lep2Jets);
   outputTree->Branch("deltaR_lep3Jets",&deltaR_lep3Jets);
   outputTree->Branch("ptRel_lepJets",&ptRel_lepJets);
   outputTree->Branch("ptRel_lep1Jets",&ptRel_lep1Jets);
   outputTree->Branch("ptRel_lep2Jets",&ptRel_lep2Jets);
   outputTree->Branch("ptRel_lep3Jets",&ptRel_lep3Jets);
   outputTree->Branch("deltaR_lepMETs",&deltaR_lepMETs);
   outputTree->Branch("deltaR_METJets",&deltaR_METJets);
   outputTree->Branch("deltaR_lepBJets",&deltaR_lepBJets);
   outputTree->Branch("deltaR_lepBJets_bSFup",&deltaR_lepBJets_bSFup);
   outputTree->Branch("deltaR_lepBJets_bSFdn",&deltaR_lepBJets_bSFdn);
   outputTree->Branch("deltaR_lepBJets_lSFup",&deltaR_lepBJets_lSFup);
   outputTree->Branch("deltaR_lepBJets_lSFdn",&deltaR_lepBJets_lSFdn);
   outputTree->Branch("deltaR_lepAK8s",&deltaR_lepAK8s);
   outputTree->Branch("deltaPhi_lepJets",&deltaPhi_lepJets);
   outputTree->Branch("deltaPhi_lepBJets",&deltaPhi_lepBJets);
   outputTree->Branch("deltaPhi_lepBJets_bSFup",&deltaPhi_lepBJets_bSFup);
   outputTree->Branch("deltaPhi_lepBJets_bSFdn",&deltaPhi_lepBJets_bSFdn);
   outputTree->Branch("deltaPhi_lepBJets_lSFup",&deltaPhi_lepBJets_lSFup);
   outputTree->Branch("deltaPhi_lepBJets_lSFdn",&deltaPhi_lepBJets_lSFdn);
   outputTree->Branch("deltaPhi_lepAK8s",&deltaPhi_lepAK8s);
   outputTree->Branch("mass_lepJets",&mass_lepJets);
   outputTree->Branch("mass_lepBJets",&mass_lepBJets);
   outputTree->Branch("mass_lepBJets_bSFup",&mass_lepBJets_bSFup);
   outputTree->Branch("mass_lepBJets_bSFdn",&mass_lepBJets_bSFdn);
   outputTree->Branch("mass_lepBJets_lSFup",&mass_lepBJets_lSFup);
   outputTree->Branch("mass_lepBJets_lSFdn",&mass_lepBJets_lSFdn);
   outputTree->Branch("mass_lepAK8s",&mass_lepAK8s);

   outputTree->Branch("minDR_lepJets",&minDR_lepJets);
   outputTree->Branch("minDR_lepBJets",&minDR_lepBJets);

   outputTree->Branch("deltaR_lepClosestJet",&deltaR_lepClosestJet);
   outputTree->Branch("PtRelLepClosestJet",&PtRelLepClosestJet);

   outputTree->Branch("Mll_sameFlavorOS",&Mll_sameFlavorOS,"Mll_sameFlavorOS/F");
   outputTree->Branch("MllOS_allComb",&MllOS_allComb);
   outputTree->Branch("MllOS_allComb_min",&MllOS_allComb_min,"MllOS_allComb_min/F");
   outputTree->Branch("MllOS_allComb_max",&MllOS_allComb_max,"MllOS_allComb_max/F");
   outputTree->Branch("Mlll",&Mlll,"Mlll/F");


  // ----------------------------------------------------------------------------
  // Define and initialize objects / cuts / efficiencies
  // ----------------------------------------------------------------------------

   // basic cuts
   float metCut=20;
   int   njetsCut=0;
   float JetLeadPtCut=0;
   float lepPtCut=30;
   //float elEtaCut=2.1;
   float jetEtaCut=2.4;
   float ak8EtaCut=2.4;
   float jetPtCut=30;
   float elEtaCut=2.4;//2.1;//2.4;

   // counters
   int npass_trigger      = 0;
   int npass_mu500        = 0;
   int npass_met          = 0;
   int npass_njets        = 0;
   int npass_nHjets       = 0;
   int npass_JetPt    = 0;
   int npass_trilepPt     = 0;
   int npass_ElEta        = 0;
   int npass_all          = 0;
   int Nelectrons         = 0;
   int Nmuons             = 0;

   int totalLep = 0;
   
   int Neee[4]={0};
   int Neem[6]={0};
   int Nemm[6]={0};
   int Nmmm[4]={0};
   
   int EEE_count = 0;
   int EEM_count = 0;
   int EMM_count = 0;
   int MMM_count = 0;
   
   int nPassTrilepton=0;

   // Lorentz vectors
   TLorentzVector jet_lv;
   TLorentzVector bjet_lv;
   TLorentzVector wjet1_lv;
   TLorentzVector tjet1_lv;
//    TLorentzVector lepton_lv;
   std::vector<TLorentzVector> lepton_lv;
   std::vector<TLorentzVector> lepton_PtOrderedOnly_lv;
   TLorentzVector ak8_lv;
   
   // Muon Trigger & tracking efficiencies
   float avePtPOG[4][6] = {
     {35.55,44.32,53.90,73.03,145.96,254.04},
     {35.56,44.41,53.84,72.79,144.55,254.16},
     {35.36,44.38,53.83,71.70,144.44,230.07},
     {35.69,44.31,53.95,73.08,145.84,270.32},
   };
   float mueffs[4][6] = {
     {0.906,0.926,0.930,0.929,0.926,0.922},
     {0.904,0.928,0.932,0.931,0.912,0.889},
     {0.859,0.884,0.889,0.888,0.874,0.851},
     {0.786,0.817,0.820,0.823,0.774,0.675}
   };

   // Muon tracking efficiencies, https://twiki.cern.ch/twiki/bin/viewauth/CMS/MuonWorkInProgressAndPagResults#Results_on_the_full_2016_data, Feb 16 release for full data
   float tracksf[15] = {0.991237,0.994853, 0.996413,0.997157,0.997512,0.99756,0.996745,0.996996,0.99772,0.998604,0.998321,0.997682,0.995252,0.994919,0.987334};
   
   float SignalEff[11][14] = {
     {0.548356, 0.582139, 0.583056, 0.589624, 0.593879, 0.596037, 0.606139, 0.603989, 0.604075, 0.612769, 0.598276, 0.563951, 0.562433, 0.481481},
     {0.537263, 0.566472, 0.563321, 0.566097, 0.569125, 0.578216, 0.579019, 0.585555, 0.589941, 0.589891, 0.590064, 0.591820, 0.566303, 0.476440},
     {0.538521, 0.557660, 0.543946, 0.545865, 0.558151, 0.563405, 0.572813, 0.570846, 0.573461, 0.586819, 0.578804, 0.572940, 0.561443, 0.555556},
     {0.530602, 0.550354, 0.538940, 0.536638, 0.544389, 0.550410, 0.554327, 0.562982, 0.568316, 0.567526, 0.576123, 0.575019, 0.560201, 0.550186},
     {0.533944, 0.550041, 0.530723, 0.522086, 0.528805, 0.539058, 0.545445, 0.549327, 0.552455, 0.554668, 0.559353, 0.558860, 0.553680, 0.531915},
     {0.538718, 0.549315, 0.523989, 0.518197, 0.516679, 0.527819, 0.534820, 0.540149, 0.540099, 0.549270, 0.550459, 0.557293, 0.545746, 0.559468},
     {0.542657, 0.554109, 0.528772, 0.512938, 0.509910, 0.519070, 0.522395, 0.532678, 0.535456, 0.538611, 0.540082, 0.546394, 0.540544, 0.539807},
     {0.539844, 0.566326, 0.531928, 0.506292, 0.502152, 0.510498, 0.513585, 0.520557, 0.527288, 0.534014, 0.538507, 0.537015, 0.535885, 0.540658},
     {0.548628, 0.559869, 0.551592, 0.510941, 0.501727, 0.506774, 0.502805, 0.513068, 0.519535, 0.520095, 0.519365, 0.519234, 0.537919, 0.519135},
     {0.549918, 0.577604, 0.540031, 0.518584, 0.507735, 0.504109, 0.500252, 0.506397, 0.513234, 0.518664, 0.521474, 0.520294, 0.518832, 0.532468},
     {0.554463, 0.581864, 0.553090, 0.522106, 0.504654, 0.496037, 0.501408, 0.500636, 0.504387, 0.509833, 0.515884, 0.510956, 0.515713, 0.538008},
   };
   float TTbarEff[14] = {0.682439, 0.738105, 0.707007, 0.676506, 0.655480, 0.647157, 0.640495, 0.631280, 0.629425, 0.588845, 0.572383,  0.631179, 0.528302, 0.333333};
   float STEff[14] = {0.721371, 0.799146, 0.782680, 0.762160, 0.743905, 0.729174, 0.727657, 0.709333, 0.724403, 0.717466, 0.690385,  0.666667, 0.483333, 0.600000};
   float WVEff[14] = {0.712598, 0.791459, 0.756127, 0.723847, 0.705318, 0.674699, 0.718884, 0.626923, 0.662162, 0.656250, 0.564356,  0.454545, 0.285714, 0.285714};
   float TTVEff[14] = {0.605128, 0.633895, 0.614585, 0.602014, 0.588748, 0.569500, 0.557702, 0.571873, 0.539608, 0.537893, 0.540462,  0.444444, 0.189189, 0.600000};

   // Pileup distributions - from Julie 3 Feb through skype  - /jmanagan/nobackup/EffsAndNegWeights/TagEffsM17/pileupWeights.txt.
   double pileup_central[80] = {3.603e-01, 9.378e-01, 1.201e+00, 9.651e-01, 1.112e+00, 1.162e+00, 7.847e-01, 4.960e-01, 7.422e-01, 8.839e-01, 9.662e-01, 1.071e+00, 1.124e+00, 1.175e+00, 1.203e+00, 1.208e+00, 1.200e+00, 1.182e+00, 1.144e+00, 1.096e+00, 1.065e+00, 1.051e+00, 1.052e+00, 1.051e+00, 1.050e+00, 1.057e+00, 1.072e+00, 1.083e+00, 1.095e+00, 1.108e+00, 1.094e+00, 1.084e+00, 1.042e+00, 9.850e-01, 9.095e-01, 8.196e-01, 7.159e-01, 6.107e-01, 5.032e-01, 4.052e-01, 3.092e-01, 2.285e-01, 1.636e-01, 1.133e-01, 7.738e-02, 5.090e-02, 3.180e-02, 2.013e-02, 1.226e-02, 7.425e-03, 4.389e-03, 2.614e-03, 1.572e-03, 9.679e-04, 7.333e-04, 6.786e-04, 7.342e-04, 9.346e-04, 1.346e-03, 1.888e-03, 3.248e-03, 3.966e-03, 4.872e-03, 5.119e-03, 5.452e-03, 5.338e-03, 5.112e-03, 4.397e-03, 4.023e-03, 3.359e-03, 2.987e-03, 2.770e-03, 2.278e-03, 1.982e-03, 1.765e-03, 0.000e+00, 0.000e+00, 0.000e+00, 0.000e+00, 0.000e+00};

   double pileup_up[80] = {3.510e-01, 7.384e-01, 1.136e+00, 8.481e-01, 1.011e+00, 1.047e+00, 7.158e-01, 3.479e-01, 5.006e-01, 6.065e-01, 6.335e-01, 7.320e-01, 8.266e-01, 9.118e-01, 9.603e-01, 9.892e-01, 1.024e+00, 1.052e+00, 1.051e+00, 1.027e+00, 1.005e+00, 9.982e-01, 1.015e+00, 1.038e+00, 1.058e+00, 1.085e+00, 1.121e+00, 1.155e+00, 1.192e+00, 1.232e+00, 1.245e+00, 1.269e+00, 1.260e+00, 1.233e+00, 1.180e+00, 1.103e+00, 1.001e+00, 8.905e-01, 7.691e-01, 6.545e-01, 5.326e-01, 4.236e-01, 3.297e-01, 2.501e-01, 1.888e-01, 1.381e-01, 9.654e-02, 6.875e-02, 4.733e-02, 3.248e-02, 2.175e-02, 1.456e-02, 9.619e-03, 6.146e-03, 4.301e-03, 3.097e-03, 2.253e-03, 1.894e-03, 2.009e-03, 2.389e-03, 3.847e-03, 4.626e-03, 5.722e-03, 6.110e-03, 6.639e-03, 6.646e-03, 6.514e-03, 5.738e-03, 5.381e-03, 4.607e-03, 4.204e-03, 4.003e-03, 3.382e-03, 3.025e-03, 2.770e-03, 0.000e+00, 0.000e+00, 0.000e+00, 0.000e+00, 0.000e+00};

   double pileup_down[80] = {3.733e-01, 1.197e+00, 1.263e+00, 1.102e+00, 1.240e+00, 1.278e+00, 9.076e-01, 7.680e-01, 1.093e+00, 1.345e+00, 1.489e+00, 1.526e+00, 1.496e+00, 1.500e+00, 1.498e+00, 1.445e+00, 1.367e+00, 1.298e+00, 1.228e+00, 1.165e+00, 1.125e+00, 1.091e+00, 1.065e+00, 1.041e+00, 1.019e+00, 1.005e+00, 9.973e-01, 9.851e-01, 9.722e-01, 9.567e-01, 9.141e-01, 8.732e-01, 8.075e-01, 7.337e-01, 6.501e-01, 5.605e-01, 4.658e-01, 3.750e-01, 2.886e-01, 2.147e-01, 1.498e-01, 1.001e-01, 6.433e-02, 3.962e-02, 2.392e-02, 1.382e-02, 7.544e-03, 4.163e-03, 2.215e-03, 1.187e-03, 6.441e-04, 3.850e-04, 2.739e-04, 2.425e-04, 2.913e-04, 3.993e-04, 5.467e-04, 7.711e-04, 1.143e-03, 1.598e-03, 2.706e-03, 3.234e-03, 3.878e-03, 3.973e-03, 4.121e-03, 3.928e-03, 3.659e-03, 3.059e-03, 2.719e-03, 2.203e-03, 1.901e-03, 1.709e-03, 1.362e-03, 1.147e-03, 9.884e-04, 0.000e+00, 0.000e+00, 0.000e+00, 0.000e+00, 0.000e+00};
	

  // ----------------------------------------------------------------------------
  // RUN THE EVENT LOOP
  // ----------------------------------------------------------------------------

   cout << "RUN CONFIG: isMC = " << isMC << endl;
   cout << "isSig = " << isSig << ", SigMass = " << SigMass << endl;
   cout << "For W's: isTT = " << isTT << ", isST = " << isST << endl;
   cout << "Fot jets & PDF: isTOP = " << isTOP << ", isMadgraphBkg = " << isMadgraphBkg << endl;
      
   Long64_t nentries = inputTree->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = inputTree->GetEntry(jentry);   nbytes += nb;
      if (Cut(ientry) != 1) continue;
      
      //      if (ientry > 5000) continue;
      
      if(DEBUG||DEBUGleptons||DEBUGddbkg||DEBUGTriggers)std::cout << "" << std::endl;
      if(DEBUG||DEBUGleptons||DEBUGddbkg||DEBUGTriggers)std::cout << "+++++++++++++++++++++++++++++++" << std::endl;
      if(DEBUG||DEBUGleptons||DEBUGddbkg||DEBUGTriggers)std::cout<<"Event "<<event_CommonCalc<<std::endl;
      if(DEBUG||DEBUGleptons||DEBUGddbkg||DEBUGTriggers)std::cout << "+++++++++++++++++++++++++++++++" << std::endl;
      
      if(jentry % 1000 ==0) std::cout<<"Completed "<<jentry<<" out of "<<nentries<<" events"<<std::endl;

      // ----------------------------------------------------------------------------
      // Filter input file by mass or decay
      // ----------------------------------------------------------------------------

      if(isTTincMtt0to700 && ttbarMass_TTbarMassCalc >= 700.) continue;
      if(isTTincMtt0to1000 && ttbarMass_TTbarMassCalc >= 1000.) continue;
      if(isTTincMtt700to1000 && (ttbarMass_TTbarMassCalc < 700. || ttbarMass_TTbarMassCalc >= 1000.)) continue;
      if(isTTincMtt1000toInf && ttbarMass_TTbarMassCalc < 1000.) continue;
      if(outBWBW && !isBWBW_TpTpCalc) continue;
      if(outTZBW && !isTZBW_TpTpCalc) continue;
      if(outTHBW && !isTHBW_TpTpCalc) continue;
      if(outTZTH && !isTZTH_TpTpCalc) continue;
      if(outTZTZ && !isTZTZ_TpTpCalc) continue;
      if(outTHTH && !isTHTH_TpTpCalc) continue;
      if(outTWTW && !isTWTW_TpTpCalc) continue;
      if(outBZTW && !isBZTW_TpTpCalc) continue;
      if(outBHTW && !isBHTW_TpTpCalc) continue;
      if(outBZBH && !isBZBH_TpTpCalc) continue;
      if(outBZBZ && !isBZBZ_TpTpCalc) continue;
      if(outBHBH && !isBHBH_TpTpCalc) continue;

      // ----------------------------------------------------------------------------
      // Collect leptons and Assign event category and some other things
      // ----------------------------------------------------------------------------
      if(DEBUG)std::cout<<"Collect leptons and Assign event category and some other things"<<std::endl;      
      
      // ------ Rizki - start 

      if(DEBUG)std::cout<<"Rizki A - start"<<std::endl;

      std::vector<double> TightLeptonPt;
      std::vector<double> TightLeptonEta;
      std::vector<double> TightLeptonPhi;
      std::vector<double> TightLeptonEnergy;
      std::vector<double> TightLeptonMiniIso;
      std::vector<int> TightLeptonFlavor; // 0 - electron, 1 - muon
      std::vector<int> TightLeptonCharge; // 0 - electron, 1 - muon
      std::vector<int> TightLeptonIdx; // index in LJMet ntuple
      std::vector<double> TightLeptonDxy;
      std::vector<double> TightLeptonDz;
      std::vector<pair<double,int>> tightlepptindpair;      

      std::vector<double> LooseNotTightLeptonPt;
      std::vector<double> LooseNotTightLeptonEta;
      std::vector<double> LooseNotTightLeptonPhi;
      std::vector<double> LooseNotTightLeptonEnergy;
      std::vector<double> LooseNotTightLeptonMiniIso;
      std::vector<int> LooseNotTightLeptonFlavor; // 0 - electron, 1 - muon
      std::vector<int> LooseNotTightLeptonCharge; // 0 - electron, 1 - muon
      std::vector<int> LooseNotTightLeptonIdx; // index in LJMet ntuple
      std::vector<double> LooseNotTightLeptonDxy;
      std::vector<double> LooseNotTightLeptonDz;
      std::vector<pair<double,int>> loosenottightlepptindpair;      

      std::vector<double> AllLeptonPt;
      std::vector<double> AllLeptonEta;
      std::vector<double> AllLeptonPhi;
      std::vector<double> AllLeptonEnergy;
      std::vector<double> AllLeptonMiniIso;
      std::vector<int> AllLeptonFlavor; // 0 - electron, 1 - muon
      std::vector<int> AllLeptonIsTight; 
      std::vector<int> AllLeptonCharge;       
      std::vector<int> AllLeptonIdx; // index in LJMet ntuple
      std::vector<double> AllLeptonDxy;
      std::vector<double> AllLeptonDz;
      int AllLeptonCount = 0; 
      AllLeptonCount_PtOrdered = 0;
      AllLeptonElCount_PtOrdered = 0;
      AllLeptonMuCount_PtOrdered  = 0;
      std::vector<pair<double,int>> alllepptindpair;
      std::vector<pair<double,int>> alllepptindpair_top3;
      

      int tightlepindex = 0;
      int loosenottightlepindex = 0;
      int alllepindex = 0;
      int alllepindex_top3 = 0;
            
      //collect all electrons.
      if(DEBUG)std::cout<<"Collecting electrons ..."<<std::endl;      
      if(DEBUG)std::cout<<"elPt_singleLepCalc->size() = "<< elPt_singleLepCalc->size() <<std::endl;  
      for(unsigned int iel = 0; iel < elPt_singleLepCalc->size(); iel++){
      
      	if(DEBUGleptons) std::cout << "\t" << iel << std::endl;
      	if(DEBUGleptons) std::cout << "\t\t pT :" << elPt_singleLepCalc->at(iel) << std::endl;
      	if(DEBUGleptons) std::cout << "\t\t eta:" << fabs(elEta_singleLepCalc->at(iel)) << std::endl;
      	if(DEBUGleptons) std::cout << "\t\t miniIso:" << elMiniIso_singleLepCalc->at(iel) << std::endl;
      	if(DEBUGleptons) std::cout << "\t\t isMVATight:" << elIsMVATight_singleLepCalc->at(iel) << std::endl;
      	if(DEBUGleptons) std::cout << "\t\t isMVALoose:" << elIsMVALoose_singleLepCalc->at(iel) << std::endl;
      
		if(elPt_singleLepCalc->at(iel) < lepPtCut || fabs(elEta_singleLepCalc->at(iel)) > elEtaCut) continue;

		//Explicit check for Tight electrons
		bool isTightEl = false;
		if(elMiniIso_singleLepCalc->at(iel) < 0.1 && elIsMVATight_singleLepCalc->at(iel) > 0){isTightEl = true;}
		if(isTightEl){
		  TightLeptonPt.push_back(elPt_singleLepCalc->at(iel));
		  TightLeptonEta.push_back(elEta_singleLepCalc->at(iel));
		  TightLeptonPhi.push_back(elPhi_singleLepCalc->at(iel));
		  TightLeptonEnergy.push_back(elEnergy_singleLepCalc->at(iel));
		  TightLeptonMiniIso.push_back(elMiniIso_singleLepCalc->at(iel));
		  TightLeptonFlavor.push_back(0);
		  TightLeptonCharge.push_back(elCharge_singleLepCalc->at(iel));
		  TightLeptonIdx.push_back(iel);
		  TightLeptonDxy.push_back(elD0_singleLepCalc->at(iel));
		  TightLeptonDz.push_back(elDZ_singleLepCalc->at(iel));

		  tightlepptindpair.push_back(std::make_pair(elPt_singleLepCalc->at(iel),tightlepindex));
		  tightlepindex++;

		  AllLeptonPt.push_back(elPt_singleLepCalc->at(iel));
		  AllLeptonEta.push_back(elEta_singleLepCalc->at(iel));
		  AllLeptonPhi.push_back(elPhi_singleLepCalc->at(iel));
		  AllLeptonEnergy.push_back(elEnergy_singleLepCalc->at(iel));
		  AllLeptonMiniIso.push_back(elMiniIso_singleLepCalc->at(iel));
		  AllLeptonFlavor.push_back(0);
		  AllLeptonCharge.push_back(elCharge_singleLepCalc->at(iel));
		  AllLeptonIsTight.push_back(1);
		  AllLeptonIdx.push_back(iel);
		  AllLeptonDxy.push_back(elD0_singleLepCalc->at(iel));
		  AllLeptonDz.push_back(elDZ_singleLepCalc->at(iel));

		  alllepptindpair.push_back(std::make_pair(elPt_singleLepCalc->at(iel),alllepindex));
		  alllepindex++;
      	  if(DEBUGleptons) std::cout << "\t\t\t ---> Tight " << std::endl;
		}

		//Explicit check for Loose electrons 
		bool isLooseEl = false;
		if(elMiniIso_singleLepCalc->at(iel) < 0.4 && elIsMVALoose_singleLepCalc->at(iel) > 0){isLooseEl = true;}
		if(!isTightEl && isLooseEl){
		  LooseNotTightLeptonPt.push_back(elPt_singleLepCalc->at(iel));
		  LooseNotTightLeptonEta.push_back(elEta_singleLepCalc->at(iel));
		  LooseNotTightLeptonPhi.push_back(elPhi_singleLepCalc->at(iel));
		  LooseNotTightLeptonEnergy.push_back(elEnergy_singleLepCalc->at(iel));
		  LooseNotTightLeptonMiniIso.push_back(elMiniIso_singleLepCalc->at(iel));
		  LooseNotTightLeptonFlavor.push_back(0);
		  LooseNotTightLeptonCharge.push_back(elCharge_singleLepCalc->at(iel));
		  LooseNotTightLeptonIdx.push_back(iel);
		  LooseNotTightLeptonDxy.push_back(elD0_singleLepCalc->at(iel));
		  LooseNotTightLeptonDz.push_back(elDZ_singleLepCalc->at(iel));
		  
		  loosenottightlepptindpair.push_back(std::make_pair(elPt_singleLepCalc->at(iel),loosenottightlepindex));
		  loosenottightlepindex++;

		  AllLeptonPt.push_back(elPt_singleLepCalc->at(iel));
		  AllLeptonEta.push_back(elEta_singleLepCalc->at(iel));
		  AllLeptonPhi.push_back(elPhi_singleLepCalc->at(iel));
		  AllLeptonEnergy.push_back(elEnergy_singleLepCalc->at(iel));
		  AllLeptonMiniIso.push_back(elMiniIso_singleLepCalc->at(iel));
		  AllLeptonFlavor.push_back(0);
		  AllLeptonCharge.push_back(elCharge_singleLepCalc->at(iel));
		  AllLeptonIsTight.push_back(0);
		  AllLeptonIdx.push_back(iel);
		  AllLeptonDxy.push_back(elD0_singleLepCalc->at(iel));
		  AllLeptonDz.push_back(elDZ_singleLepCalc->at(iel));

		  alllepptindpair.push_back(std::make_pair(elPt_singleLepCalc->at(iel),alllepindex));
		  alllepindex++;
      	  if(DEBUGleptons) std::cout << "\t\t\t ---> Loose " << std::endl;
		}
		
      }
      
      //collect all muons. 
      if(DEBUG)std::cout<<"Collecting muons ..."<<std::endl;      
      if(DEBUG)std::cout<<"muPt_singleLepCalc->size() = "<< muPt_singleLepCalc->size() <<std::endl;  
      for(unsigned int imu = 0; imu < muPt_singleLepCalc->size(); imu++){

      	if(DEBUGleptons) std::cout << "\t" << imu << std::endl;
      	if(DEBUGleptons) std::cout << "\t\t pT :" << muPt_singleLepCalc->at(imu) << std::endl;
      	if(DEBUGleptons) std::cout << "\t\t eta:" << fabs(muEta_singleLepCalc->at(imu)) << std::endl;
      	if(DEBUGleptons) std::cout << "\t\t miniIso:" << muMiniIso_singleLepCalc->at(imu) << std::endl;
      	if(DEBUGleptons) std::cout << "\t\t isTight:" << muIsTight_singleLepCalc->at(imu) << std::endl;
      	if(DEBUGleptons) std::cout << "\t\t isLoose:" << muIsLoose_singleLepCalc->at(imu) << std::endl;

		if(muPt_singleLepCalc->at(imu) < lepPtCut || fabs(muEta_singleLepCalc->at(imu)) > 2.4) continue;
		
		//Explicit check for tight muons
		bool isTightMu = false;
		if(muMiniIso_singleLepCalc->at(imu) < 0.1 && muIsTight_singleLepCalc->at(imu) > 0) isTightMu = true;
		if(isTightMu){
		  TightLeptonPt.push_back(muPt_singleLepCalc->at(imu));
		  TightLeptonEta.push_back(muEta_singleLepCalc->at(imu));
		  TightLeptonPhi.push_back(muPhi_singleLepCalc->at(imu));
		  TightLeptonEnergy.push_back(muEnergy_singleLepCalc->at(imu));
		  TightLeptonMiniIso.push_back(muMiniIso_singleLepCalc->at(imu));
		  TightLeptonFlavor.push_back(1);
		  TightLeptonCharge.push_back(muCharge_singleLepCalc->at(imu));
		  TightLeptonIdx.push_back(imu);
		  TightLeptonDxy.push_back(muDxy_singleLepCalc->at(imu));
		  TightLeptonDz.push_back(muDz_singleLepCalc->at(imu));

		  tightlepptindpair.push_back(std::make_pair(muPt_singleLepCalc->at(imu),tightlepindex));
		  tightlepindex++;

		  AllLeptonPt.push_back(muPt_singleLepCalc->at(imu));
		  AllLeptonEta.push_back(muEta_singleLepCalc->at(imu));
		  AllLeptonPhi.push_back(muPhi_singleLepCalc->at(imu));
		  AllLeptonEnergy.push_back(muEnergy_singleLepCalc->at(imu));
		  AllLeptonMiniIso.push_back(muMiniIso_singleLepCalc->at(imu));
		  AllLeptonFlavor.push_back(1);
		  AllLeptonCharge.push_back(muCharge_singleLepCalc->at(imu));
		  AllLeptonIsTight.push_back(1);
		  AllLeptonIdx.push_back(imu);
		  AllLeptonDxy.push_back(muDxy_singleLepCalc->at(imu));
		  AllLeptonDz.push_back(muDz_singleLepCalc->at(imu));

		  alllepptindpair.push_back(std::make_pair(muPt_singleLepCalc->at(imu),alllepindex));
		  alllepindex++;
      	  if(DEBUGleptons) std::cout << "\t\t\t ---> Tight " << std::endl;
		}
		
		//Explicit check for Loose muons
		bool isLooseMu = false;
		if(muMiniIso_singleLepCalc->at(imu) < 0.4 && muIsLoose_singleLepCalc->at(imu) > 0) isLooseMu = true;
		if(!isTightMu && isLooseMu){ 
		  LooseNotTightLeptonPt.push_back(muPt_singleLepCalc->at(imu));
		  LooseNotTightLeptonEta.push_back(muEta_singleLepCalc->at(imu));
		  LooseNotTightLeptonPhi.push_back(muPhi_singleLepCalc->at(imu));
		  LooseNotTightLeptonEnergy.push_back(muEnergy_singleLepCalc->at(imu));
		  LooseNotTightLeptonMiniIso.push_back(muMiniIso_singleLepCalc->at(imu));//ATTENTION! there is mistake in new 74x LJMet ntuple muMiniIso twice filled!! hence the imu*2
		  LooseNotTightLeptonFlavor.push_back(1);
		  LooseNotTightLeptonCharge.push_back(muCharge_singleLepCalc->at(imu));
		  LooseNotTightLeptonIdx.push_back(imu);
		  LooseNotTightLeptonDxy.push_back(muDxy_singleLepCalc->at(imu));
		  LooseNotTightLeptonDz.push_back(muDz_singleLepCalc->at(imu));
		  
		  loosenottightlepptindpair.push_back(std::make_pair(muPt_singleLepCalc->at(imu),loosenottightlepindex));
		  loosenottightlepindex++;

		  AllLeptonPt.push_back(muPt_singleLepCalc->at(imu));
		  AllLeptonEta.push_back(muEta_singleLepCalc->at(imu));
		  AllLeptonPhi.push_back(muPhi_singleLepCalc->at(imu));
		  AllLeptonEnergy.push_back(muEnergy_singleLepCalc->at(imu));
		  AllLeptonMiniIso.push_back(muMiniIso_singleLepCalc->at(imu));
		  AllLeptonFlavor.push_back(1);
		  AllLeptonCharge.push_back(muCharge_singleLepCalc->at(imu));
		  AllLeptonIsTight.push_back(0);
		  AllLeptonIdx.push_back(imu);
		  AllLeptonDxy.push_back(muDxy_singleLepCalc->at(imu));
		  AllLeptonDz.push_back(muDz_singleLepCalc->at(imu));

		  alllepptindpair.push_back(std::make_pair(muPt_singleLepCalc->at(imu),alllepindex));
		  alllepindex++;
		  if(DEBUGleptons) std::cout << "\t\t\t ---> Loose " << std::endl;
		}

      }
      
      AllLeptonCount = alllepindex ;
      AllLeptonCount_PtOrdered =  AllLeptonCount;
      //std::cout << "Nleptons = " << AllLeptonCount_PtOrdered << endl;

      if(AllLeptonCount<3) continue; //skip if there is less than 3 loose leptons.
      // CHECK and UNCOMMENT BELOW if necessary!!
      if(isMC && tightlepindex<3) continue; //skip if there is less than 3 tight leptons for MC (not creating ddBKg).

      //Pt ordering
      AllLeptonPt_PtOrdered.clear();
      AllLeptonEta_PtOrdered.clear();
      AllLeptonPhi_PtOrdered.clear();
      AllLeptonEnergy_PtOrdered.clear();
      AllLeptonMiniIso_PtOrdered.clear();
      AllLeptonFlavor_PtOrdered.clear();
      AllLeptonIsTight_PtOrdered.clear();      
      AllLeptonCharge_PtOrdered.clear();      
      AllLeptonIdx_PtOrdered.clear();      
      AllLeptonDxy_PtOrdered.clear();      
      AllLeptonDz_PtOrdered.clear();      
 
      //Pt ordering - for Tight leptons - then add to All leptons list/vector
      int Nel_tight = 0;
      int Nmu_tight = 0;
      std::sort(tightlepptindpair.begin(), tightlepptindpair.end(), comparepair);
      TightLeptonPt_PtOrdered.clear();
      TightLeptonEta_PtOrdered.clear();
      TightLeptonPhi_PtOrdered.clear();
      TightLeptonEnergy_PtOrdered.clear();
      TightLeptonMiniIso_PtOrdered.clear();
      TightLeptonFlavor_PtOrdered.clear();
      TightLeptonCharge_PtOrdered.clear();
      TightLeptonIdx_PtOrdered.clear();
      for(unsigned int ilep=0; ilep < tightlepptindpair.size(); ilep++){
      	TightLeptonPt_PtOrdered.push_back(TightLeptonPt.at(tightlepptindpair[ilep].second));
      	TightLeptonEta_PtOrdered.push_back(TightLeptonEta.at(tightlepptindpair[ilep].second));
      	TightLeptonPhi_PtOrdered.push_back(TightLeptonPhi.at(tightlepptindpair[ilep].second));
      	TightLeptonEnergy_PtOrdered.push_back(TightLeptonEnergy.at(tightlepptindpair[ilep].second));
      	TightLeptonMiniIso_PtOrdered.push_back(TightLeptonMiniIso.at(tightlepptindpair[ilep].second));
      	TightLeptonFlavor_PtOrdered.push_back(TightLeptonFlavor.at(tightlepptindpair[ilep].second));
      	TightLeptonCharge_PtOrdered.push_back(TightLeptonCharge.at(tightlepptindpair[ilep].second));
      	TightLeptonIdx_PtOrdered.push_back(TightLeptonIdx.at(tightlepptindpair[ilep].second));
 
		if(TightLeptonFlavor.at(tightlepptindpair[ilep].second) == 0) Nel_tight++;
		if(TightLeptonFlavor.at(tightlepptindpair[ilep].second) == 1) Nmu_tight++;
		
		//push back for all leptons order in pt AND TIGHT
		AllLeptonPt_PtOrdered.push_back(TightLeptonPt.at(tightlepptindpair[ilep].second));
      	AllLeptonEta_PtOrdered.push_back(TightLeptonEta.at(tightlepptindpair[ilep].second));
      	AllLeptonPhi_PtOrdered.push_back(TightLeptonPhi.at(tightlepptindpair[ilep].second));
      	AllLeptonEnergy_PtOrdered.push_back(TightLeptonEnergy.at(tightlepptindpair[ilep].second));
      	AllLeptonMiniIso_PtOrdered.push_back(TightLeptonMiniIso.at(tightlepptindpair[ilep].second));
      	AllLeptonFlavor_PtOrdered.push_back(TightLeptonFlavor.at(tightlepptindpair[ilep].second));
      	AllLeptonIsTight_PtOrdered.push_back(1);
      	AllLeptonCharge_PtOrdered.push_back(TightLeptonCharge.at(tightlepptindpair[ilep].second));				
      	AllLeptonIdx_PtOrdered.push_back(TightLeptonIdx.at(tightlepptindpair[ilep].second));				
		AllLeptonDxy_PtOrdered.push_back(TightLeptonDxy.at(tightlepptindpair[ilep].second));
		AllLeptonDz_PtOrdered.push_back(TightLeptonDz.at(tightlepptindpair[ilep].second));
      	
      	if(alllepindex_top3 < 3) alllepptindpair_top3.push_back(std::make_pair(TightLeptonPt.at(tightlepptindpair[ilep].second),alllepindex_top3));
      	if(DEBUG)cout<<"appending Tight         :"<<"alllepindex_top3="<<alllepindex_top3<<", alllepptindpair_top3["<<alllepindex_top3<<"].first = "<<alllepptindpair_top3[alllepindex_top3].first<<", alllepptindpair_top3["<<alllepindex_top3<<"].second = "<<alllepptindpair_top3[alllepindex_top3].second<<endl;
      	if(alllepindex_top3 < 3) alllepindex_top3++;

      }           

      //Pt ordering - for Loose Not Tight - then append to All leptons list/vector
      std::sort(loosenottightlepptindpair.begin(), loosenottightlepptindpair.end(), comparepair);
      for(unsigned int ilep=0; ilep < loosenottightlepptindpair.size(); ilep++){
	
		//push back for all leptons order in pt AND LOOSEnotTIGHT
		AllLeptonPt_PtOrdered.push_back(LooseNotTightLeptonPt.at(loosenottightlepptindpair[ilep].second));
      	AllLeptonEta_PtOrdered.push_back(LooseNotTightLeptonEta.at(loosenottightlepptindpair[ilep].second));
      	AllLeptonPhi_PtOrdered.push_back(LooseNotTightLeptonPhi.at(loosenottightlepptindpair[ilep].second));
      	AllLeptonEnergy_PtOrdered.push_back(LooseNotTightLeptonEnergy.at(loosenottightlepptindpair[ilep].second));
      	AllLeptonMiniIso_PtOrdered.push_back(LooseNotTightLeptonMiniIso.at(loosenottightlepptindpair[ilep].second));
      	AllLeptonFlavor_PtOrdered.push_back(LooseNotTightLeptonFlavor.at(loosenottightlepptindpair[ilep].second));
      	AllLeptonIsTight_PtOrdered.push_back(0);
      	AllLeptonCharge_PtOrdered.push_back(LooseNotTightLeptonCharge.at(loosenottightlepptindpair[ilep].second));
		AllLeptonDxy_PtOrdered.push_back(LooseNotTightLeptonDxy.at(loosenottightlepptindpair[ilep].second));
		AllLeptonDz_PtOrdered.push_back(LooseNotTightLeptonDz.at(loosenottightlepptindpair[ilep].second));

      	if(alllepindex_top3 < 3) alllepptindpair_top3.push_back(std::make_pair(LooseNotTightLeptonPt.at(loosenottightlepptindpair[ilep].second),alllepindex_top3));
      	if(DEBUG)cout<<"appending LooseNotTight : alllepindex_top3="<<alllepindex_top3<<", alllepptindpair_top3["<<alllepindex_top3<<"].first = "<<alllepptindpair_top3[alllepindex_top3].first<<", alllepptindpair_top3["<<alllepindex_top3<<"].second = "<<alllepptindpair_top3[alllepindex_top3].second<<endl;
      	if(alllepindex_top3 < 3) alllepindex_top3++;
				
      }           
      
	  //DEBUG-start 
      AllLeptonElPt_PtOrdered.clear();
      AllLeptonElEta_PtOrdered.clear();
      AllLeptonElPhi_PtOrdered.clear();
      AllLeptonElEnergy_PtOrdered.clear();
      AllLeptonElMiniIso_PtOrdered.clear();
      AllLeptonElFlavor_PtOrdered.clear();
      AllLeptonElIsTight_PtOrdered.clear();      
      AllLeptonElDxy_PtOrdered.clear();
      AllLeptonElDz_PtOrdered.clear();

      AllLeptonMuPt_PtOrdered.clear();
      AllLeptonMuEta_PtOrdered.clear();
      AllLeptonMuPhi_PtOrdered.clear();
      AllLeptonMuEnergy_PtOrdered.clear();
      AllLeptonMuMiniIso_PtOrdered.clear();
      AllLeptonMuFlavor_PtOrdered.clear();
      AllLeptonMuIsTight_PtOrdered.clear();      
      AllLeptonMuDxy_PtOrdered.clear();
      AllLeptonMuDz_PtOrdered.clear();
      
      for(unsigned int ilep=0; ilep < AllLeptonPt_PtOrdered.size(); ilep++){
      	if(AllLeptonFlavor_PtOrdered.at(ilep)==0){
		  AllLeptonElPt_PtOrdered.push_back(AllLeptonPt_PtOrdered.at(ilep));
		  AllLeptonElEta_PtOrdered.push_back(AllLeptonEta_PtOrdered.at(ilep));
		  AllLeptonElPhi_PtOrdered.push_back(AllLeptonPhi_PtOrdered.at(ilep));
		  AllLeptonElEnergy_PtOrdered.push_back(AllLeptonEnergy_PtOrdered.at(ilep));
		  AllLeptonElMiniIso_PtOrdered.push_back(AllLeptonMiniIso_PtOrdered.at(ilep));
		  AllLeptonElFlavor_PtOrdered.push_back(AllLeptonFlavor_PtOrdered.at(ilep));
		  AllLeptonElIsTight_PtOrdered.push_back(AllLeptonIsTight_PtOrdered.at(ilep));            	
		  AllLeptonElDxy_PtOrdered.push_back(AllLeptonDxy_PtOrdered.at(ilep));
		  AllLeptonElDz_PtOrdered.push_back(AllLeptonDz_PtOrdered.at(ilep));
		  AllLeptonElCount_PtOrdered++;            	
      	}
      	else{
		  AllLeptonMuPt_PtOrdered.push_back(AllLeptonPt_PtOrdered.at(ilep));
		  AllLeptonMuEta_PtOrdered.push_back(AllLeptonEta_PtOrdered.at(ilep));
		  AllLeptonMuPhi_PtOrdered.push_back(AllLeptonPhi_PtOrdered.at(ilep));
		  AllLeptonMuEnergy_PtOrdered.push_back(AllLeptonEnergy_PtOrdered.at(ilep));
		  AllLeptonMuMiniIso_PtOrdered.push_back(AllLeptonMiniIso_PtOrdered.at(ilep));
		  AllLeptonMuFlavor_PtOrdered.push_back(AllLeptonFlavor_PtOrdered.at(ilep));
		  AllLeptonMuIsTight_PtOrdered.push_back(AllLeptonIsTight_PtOrdered.at(ilep));            	      	
		  AllLeptonMuDxy_PtOrdered.push_back(AllLeptonDxy_PtOrdered.at(ilep));
		  AllLeptonMuDz_PtOrdered.push_back(AllLeptonDz_PtOrdered.at(ilep));
		  AllLeptonMuCount_PtOrdered++;            	
      	}
      }
      if(DEBUGleptons)cout<< "AllLeptonCount_PtOrdered   = " << AllLeptonCount_PtOrdered << endl;
      if(DEBUGleptons)cout<< "AllLeptonElCount_PtOrdered = " << AllLeptonElCount_PtOrdered << endl;
      if(DEBUGleptons)cout<< "AllLeptonMuCount_PtOrdered = " << AllLeptonMuCount_PtOrdered << endl;
	  //DEBUG-end
	  
	  //Sorting leptons by pT only - start
      std::sort(alllepptindpair.begin(), alllepptindpair.end(), comparepair);
      AllLeptonPt_PtOrderedOnly.clear();
      AllLeptonEta_PtOrderedOnly.clear();
      AllLeptonPhi_PtOrderedOnly.clear();
      AllLeptonEnergy_PtOrderedOnly.clear();
      AllLeptonMiniIso_PtOrderedOnly.clear();
      AllLeptonFlavor_PtOrderedOnly.clear();
      AllLeptonCharge_PtOrderedOnly.clear();
      AllLeptonIsTight_PtOrderedOnly.clear();
      AllLeptonIdx_PtOrderedOnly.clear();
      AllLeptonDxy_PtOrderedOnly.clear();
      AllLeptonDz_PtOrderedOnly.clear();
      if(DEBUG)cout<<"alllepptindpair.size() = "<<alllepptindpair.size()<<endl;
      for(unsigned int ilep=0; ilep < alllepptindpair.size(); ilep++){
      	if(DEBUG)cout<<"alllepptindpair["<<ilep<<"].first = "<<alllepptindpair[ilep].first<<", alllepptindpair["<<ilep<<"].second = "<<alllepptindpair[ilep].second<<endl;
      	AllLeptonPt_PtOrderedOnly.push_back(AllLeptonPt.at(alllepptindpair[ilep].second));
      	AllLeptonEta_PtOrderedOnly.push_back(AllLeptonEta.at(alllepptindpair[ilep].second));
      	AllLeptonPhi_PtOrderedOnly.push_back(AllLeptonPhi.at(alllepptindpair[ilep].second));
      	AllLeptonEnergy_PtOrderedOnly.push_back(AllLeptonEnergy.at(alllepptindpair[ilep].second));
      	AllLeptonMiniIso_PtOrderedOnly.push_back(AllLeptonMiniIso.at(alllepptindpair[ilep].second));
      	AllLeptonFlavor_PtOrderedOnly.push_back(AllLeptonFlavor.at(alllepptindpair[ilep].second));
      	AllLeptonCharge_PtOrderedOnly.push_back(AllLeptonCharge.at(alllepptindpair[ilep].second));
      	AllLeptonIsTight_PtOrderedOnly.push_back(AllLeptonIsTight.at(alllepptindpair[ilep].second));
      	AllLeptonIdx_PtOrderedOnly.push_back(AllLeptonIdx.at(alllepptindpair[ilep].second));
      	AllLeptonDxy_PtOrderedOnly.push_back(AllLeptonDxy.at(alllepptindpair[ilep].second));
      	AllLeptonDz_PtOrderedOnly.push_back(AllLeptonDz.at(alllepptindpair[ilep].second));
      }           

      AllLeptonElPt_PtOrderedOnly.clear();
      AllLeptonElEta_PtOrderedOnly.clear();
      AllLeptonElPhi_PtOrderedOnly.clear();
      AllLeptonElEnergy_PtOrderedOnly.clear();
      AllLeptonElMiniIso_PtOrderedOnly.clear();
      AllLeptonElFlavor_PtOrderedOnly.clear();
      AllLeptonElIsTight_PtOrderedOnly.clear();      
      AllLeptonElDxy_PtOrderedOnly.clear();
      AllLeptonElDz_PtOrderedOnly.clear();

      AllLeptonMuPt_PtOrderedOnly.clear();
      AllLeptonMuEta_PtOrderedOnly.clear();
      AllLeptonMuPhi_PtOrderedOnly.clear();
      AllLeptonMuEnergy_PtOrderedOnly.clear();
      AllLeptonMuMiniIso_PtOrderedOnly.clear();
      AllLeptonMuFlavor_PtOrderedOnly.clear();
      AllLeptonMuIsTight_PtOrderedOnly.clear();      
      AllLeptonMuDxy_PtOrderedOnly.clear();
      AllLeptonMuDz_PtOrderedOnly.clear();

      for(unsigned int ilep=0; ilep < AllLeptonPt_PtOrderedOnly.size(); ilep++){
      	if(AllLeptonFlavor_PtOrderedOnly.at(ilep)==0){
		  AllLeptonElPt_PtOrderedOnly.push_back(AllLeptonPt_PtOrderedOnly.at(ilep));
		  AllLeptonElEta_PtOrderedOnly.push_back(AllLeptonEta_PtOrderedOnly.at(ilep));
		  AllLeptonElPhi_PtOrderedOnly.push_back(AllLeptonPhi_PtOrderedOnly.at(ilep));
		  AllLeptonElEnergy_PtOrderedOnly.push_back(AllLeptonEnergy_PtOrderedOnly.at(ilep));
		  AllLeptonElMiniIso_PtOrderedOnly.push_back(AllLeptonMiniIso_PtOrderedOnly.at(ilep));
		  AllLeptonElFlavor_PtOrderedOnly.push_back(AllLeptonFlavor_PtOrderedOnly.at(ilep));
		  AllLeptonElIsTight_PtOrderedOnly.push_back(AllLeptonIsTight_PtOrderedOnly.at(ilep));            	
		  AllLeptonElDxy_PtOrderedOnly.push_back(AllLeptonDxy_PtOrderedOnly.at(ilep));
		  AllLeptonElDz_PtOrderedOnly.push_back(AllLeptonDz_PtOrderedOnly.at(ilep));
      	}
      	else{
		  AllLeptonMuPt_PtOrderedOnly.push_back(AllLeptonPt_PtOrderedOnly.at(ilep));
		  AllLeptonMuEta_PtOrderedOnly.push_back(AllLeptonEta_PtOrderedOnly.at(ilep));
		  AllLeptonMuPhi_PtOrderedOnly.push_back(AllLeptonPhi_PtOrderedOnly.at(ilep));
		  AllLeptonMuEnergy_PtOrderedOnly.push_back(AllLeptonEnergy_PtOrderedOnly.at(ilep));
		  AllLeptonMuMiniIso_PtOrderedOnly.push_back(AllLeptonMiniIso_PtOrderedOnly.at(ilep));
		  AllLeptonMuFlavor_PtOrderedOnly.push_back(AllLeptonFlavor_PtOrderedOnly.at(ilep));
		  AllLeptonMuIsTight_PtOrderedOnly.push_back(AllLeptonIsTight_PtOrderedOnly.at(ilep));            	      	
		  AllLeptonMuDxy_PtOrderedOnly.push_back(AllLeptonDxy_PtOrderedOnly.at(ilep));
		  AllLeptonMuDz_PtOrderedOnly.push_back(AllLeptonDz_PtOrderedOnly.at(ilep));
      	}
      }
      if(DEBUG)cout<<"DONE sorting all leps by pt only"<<endl;

	  //Sorting leptons by pT only - end

	  //Sorting leptons by pT only - reorder TOP 3 lep in default ordering - start
      std::sort(alllepptindpair_top3.begin(), alllepptindpair_top3.end(), comparepair);
      AllLeptonPt_PtOrderedOnly_top3.clear();
      AllLeptonEta_PtOrderedOnly_top3.clear();
      AllLeptonPhi_PtOrderedOnly_top3.clear();
      AllLeptonEnergy_PtOrderedOnly_top3.clear();
      AllLeptonMiniIso_PtOrderedOnly_top3.clear();
      AllLeptonFlavor_PtOrderedOnly_top3.clear();
      AllLeptonCharge_PtOrderedOnly_top3.clear();
      AllLeptonIsTight_PtOrderedOnly_top3.clear();
      AllLeptonIdx_PtOrderedOnly_top3.clear();
      if(DEBUG)cout<<"alllepptindpair_top3.size() = "<<alllepptindpair_top3.size()<<endl;
      for(unsigned int ilep=0; ilep < alllepptindpair_top3.size(); ilep++){
      	AllLeptonPt_PtOrderedOnly_top3.push_back(AllLeptonPt_PtOrdered.at(alllepptindpair_top3[ilep].second));
      	if(DEBUG)cout<<"alllepptindpair_top3["<<ilep<<"].first = "<<alllepptindpair_top3[ilep].first<<", alllepptindpair_top3["<<ilep<<"].second = "<<alllepptindpair_top3[ilep].second<<endl;
      	AllLeptonEta_PtOrderedOnly_top3.push_back(AllLeptonEta_PtOrdered.at(alllepptindpair_top3[ilep].second));
      	AllLeptonPhi_PtOrderedOnly_top3.push_back(AllLeptonPhi_PtOrdered.at(alllepptindpair_top3[ilep].second));
      	AllLeptonEnergy_PtOrderedOnly_top3.push_back(AllLeptonEnergy_PtOrdered.at(alllepptindpair_top3[ilep].second));
      	AllLeptonMiniIso_PtOrderedOnly_top3.push_back(AllLeptonMiniIso_PtOrdered.at(alllepptindpair_top3[ilep].second));
      	AllLeptonFlavor_PtOrderedOnly_top3.push_back(AllLeptonFlavor_PtOrdered.at(alllepptindpair_top3[ilep].second));
      	AllLeptonCharge_PtOrderedOnly_top3.push_back(AllLeptonCharge_PtOrdered.at(alllepptindpair_top3[ilep].second));
      	AllLeptonIsTight_PtOrderedOnly_top3.push_back(AllLeptonIsTight_PtOrdered.at(alllepptindpair_top3[ilep].second));
//       	AllLeptonIdx_PtOrderedOnly_top3.push_back(AllLeptonIdx_PtOrdered.at(alllepptindpair_top3[ilep].second));
//       	if(DEBUG)cout<<"Check idx"<<endl;
      }           

      AllLeptonElPt_PtOrderedOnly_top3.clear();
      AllLeptonElEta_PtOrderedOnly_top3.clear();
      AllLeptonElPhi_PtOrderedOnly_top3.clear();
      AllLeptonElEnergy_PtOrderedOnly_top3.clear();
      AllLeptonElMiniIso_PtOrderedOnly_top3.clear();
      AllLeptonElFlavor_PtOrderedOnly_top3.clear();
      AllLeptonElIsTight_PtOrderedOnly_top3.clear();      

      AllLeptonMuPt_PtOrderedOnly_top3.clear();
      AllLeptonMuEta_PtOrderedOnly_top3.clear();
      AllLeptonMuPhi_PtOrderedOnly_top3.clear();
      AllLeptonMuEnergy_PtOrderedOnly_top3.clear();
      AllLeptonMuMiniIso_PtOrderedOnly_top3.clear();
      AllLeptonMuFlavor_PtOrderedOnly_top3.clear();
      AllLeptonMuIsTight_PtOrderedOnly_top3.clear();      

      for(unsigned int ilep=0; ilep < AllLeptonPt_PtOrderedOnly_top3.size(); ilep++){
      	if(AllLeptonFlavor_PtOrderedOnly_top3.at(ilep)==0){
		  AllLeptonElPt_PtOrderedOnly_top3.push_back(AllLeptonPt_PtOrderedOnly_top3.at(ilep));
		  AllLeptonElEta_PtOrderedOnly_top3.push_back(AllLeptonEta_PtOrderedOnly_top3.at(ilep));
		  AllLeptonElPhi_PtOrderedOnly_top3.push_back(AllLeptonPhi_PtOrderedOnly_top3.at(ilep));
		  AllLeptonElEnergy_PtOrderedOnly_top3.push_back(AllLeptonEnergy_PtOrderedOnly_top3.at(ilep));
		  AllLeptonElMiniIso_PtOrderedOnly_top3.push_back(AllLeptonMiniIso_PtOrderedOnly_top3.at(ilep));
		  AllLeptonElFlavor_PtOrderedOnly_top3.push_back(AllLeptonFlavor_PtOrderedOnly_top3.at(ilep));
		  AllLeptonElIsTight_PtOrderedOnly_top3.push_back(AllLeptonIsTight_PtOrderedOnly_top3.at(ilep));            	
      	}
      	else{
		  AllLeptonMuPt_PtOrderedOnly_top3.push_back(AllLeptonPt_PtOrderedOnly_top3.at(ilep));
		  AllLeptonMuEta_PtOrderedOnly_top3.push_back(AllLeptonEta_PtOrderedOnly_top3.at(ilep));
		  AllLeptonMuPhi_PtOrderedOnly_top3.push_back(AllLeptonPhi_PtOrderedOnly_top3.at(ilep));
		  AllLeptonMuEnergy_PtOrderedOnly_top3.push_back(AllLeptonEnergy_PtOrderedOnly_top3.at(ilep));
		  AllLeptonMuMiniIso_PtOrderedOnly_top3.push_back(AllLeptonMiniIso_PtOrderedOnly_top3.at(ilep));
		  AllLeptonMuFlavor_PtOrderedOnly_top3.push_back(AllLeptonFlavor_PtOrderedOnly_top3.at(ilep));
		  AllLeptonMuIsTight_PtOrderedOnly_top3.push_back(AllLeptonIsTight_PtOrderedOnly_top3.at(ilep));            	      	
      	}
      }
      if(DEBUG)cout<<"DONE sorting all leps by pt only - reorder TOP 3 lep in default ordering"<<endl;

	  //Sorting leptons by pT only - reorder TOP 3 lep in default ordering - end

      
      int Nel_top3 = 0;
      int Nmu_top3 = 0;
      int Nel_tight_top3 = 0;
      int Nmu_tight_top3 = 0;
      for(unsigned int ilep=0; ilep < AllLeptonPt_PtOrdered.size(); ilep++){
      	if(ilep < 3){
      		if(AllLeptonFlavor_PtOrdered.at(ilep)==0){ 
      			Nel_top3++;
	      		if(AllLeptonIsTight_PtOrdered.at(ilep)==1) Nel_tight_top3++;
	      	}
      		if(AllLeptonFlavor_PtOrdered.at(ilep)==1){ 
      			Nmu_top3++;
      			if(AllLeptonIsTight_PtOrdered.at(ilep)==1) Nmu_tight_top3++;
      		}
      	}
      	if(DEBUGleptons)std::cout<< "DEFAULT ordering: ilep = " << ilep << ", flavor = " << AllLeptonFlavor_PtOrdered.at(ilep) << ", charge = " << AllLeptonCharge_PtOrdered.at(ilep) << ", pT = "<< AllLeptonPt_PtOrdered.at(ilep)  << ", Eta = "<< AllLeptonEta_PtOrdered.at(ilep)  << ", isTight = " << AllLeptonIsTight_PtOrdered.at(ilep) <<", miniIso = " << AllLeptonMiniIso_PtOrdered.at(ilep) <<", Dxy = " << AllLeptonDxy_PtOrdered.at(ilep) <<", Dz = " << AllLeptonDz_PtOrdered.at(ilep) << endl; 
      }

      if(DEBUGleptons){ for(unsigned int ilep=0; ilep < AllLeptonPt_PtOrderedOnly.size(); ilep++){std::cout<< "PT ORDERED ONLY : ilep = " << ilep << ", flavor = " << AllLeptonFlavor_PtOrderedOnly.at(ilep) << ", charge = " << AllLeptonCharge_PtOrderedOnly.at(ilep) << ", pT = "<< AllLeptonPt_PtOrderedOnly.at(ilep)  << ", Eta = "<< AllLeptonEta_PtOrderedOnly.at(ilep)  << ", isTight = " << AllLeptonIsTight_PtOrderedOnly.at(ilep) <<", miniIso = " << AllLeptonMiniIso_PtOrderedOnly.at(ilep) << endl; } }
      if(DEBUGleptons){ for(unsigned int ilep=0; ilep < AllLeptonPt_PtOrderedOnly_top3.size(); ilep++){std::cout<< "ReORDER default by PT ONLY : ilep = " << ilep << ", flavor = " << AllLeptonFlavor_PtOrderedOnly_top3.at(ilep) << ", charge = " << AllLeptonCharge_PtOrderedOnly_top3.at(ilep) << ", pT = "<< AllLeptonPt_PtOrderedOnly_top3.at(ilep)  << ", Eta = "<< AllLeptonEta_PtOrderedOnly_top3.at(ilep)  << ", isTight = " << AllLeptonIsTight_PtOrderedOnly_top3.at(ilep) <<", miniIso = " << AllLeptonMiniIso_PtOrderedOnly_top3.at(ilep) << endl; } }

      
      if(DEBUGleptons)std::cout << "Nel_tight = " << Nel_tight << ",  Nmu_tight = " << Nmu_tight << endl; 
      if(DEBUGleptons)std::cout << "Nel_tight_top3 = " << Nel_tight_top3 << ",  Nmu_tight_top3 = " << Nmu_tight_top3 << endl; 
      if(DEBUGleptons)std::cout << "Nel_top3 = " << Nel_top3 << ",  Nmu_top3 = " << Nmu_top3 << endl; 

      isEEE = 0; isEEM =0; isEMM =0; isMMM= 0;
      isTTT = 0; isTTL =0; isTLT =0; isLTT= 0; isTLL= 0; isLTL= 0; isLLT= 0; isLLL= 0;
      	
      if(Nel_tight_top3 + Nmu_tight_top3 != 3 && DEBUGleptons) cout << "First 3 tight leps don't add up to 3!" << endl;
      if(Nel_top3 + Nmu_top3 != 3) cout << "First 3 All leps don't add up to 3, something's wrong" << endl;

      int tightLepCounter = 4 * AllLeptonIsTight_PtOrdered.at(0) + 2 * AllLeptonIsTight_PtOrdered.at(1) + AllLeptonIsTight_PtOrdered.at(2);
      if(Nel_top3==3){
      	isEEE = 1;
		EEE_count++;
		if(DEBUGleptons)std::cout << " -----> isEEE " << std::endl;
		Neee[Nel_tight_top3]++;
		if (tightLepCounter==7){ isTTT=1; if(DEBUGleptons)std::cout << " -----> isTTT " << std::endl;}
		if (tightLepCounter==6){ isTTL=1; if(DEBUGleptons)std::cout << " -----> isTTL " << std::endl;}
		if (tightLepCounter==5){ isTLT=1; if(DEBUGleptons)std::cout << " -----> isTLT " << std::endl;}
		if (tightLepCounter==3){ isLTT=1; if(DEBUGleptons)std::cout << " -----> isLTT " << std::endl;}
		if (tightLepCounter==4){ isTLL=1; if(DEBUGleptons)std::cout << " -----> isTLL " << std::endl;}
		if (tightLepCounter==2){ isLTL=1; if(DEBUGleptons)std::cout << " -----> isLTL " << std::endl;}
		if (tightLepCounter==1){ isLLT=1; if(DEBUGleptons)std::cout << " -----> isLLT " << std::endl;}
		if (tightLepCounter==0){ isLLL=1; if(DEBUGleptons)std::cout << " -----> isLLL " << std::endl;}
      }
      if(Nel_top3==2){
		isEEM = 1;
		EEM_count++;
		if(DEBUGleptons)std::cout << " -----> isEEM " << std::endl;
		Neem[2*Nel_tight_top3 + Nmu_tight_top3]++;
		if (tightLepCounter==7){ isTTT=1; if(DEBUGleptons)std::cout << " -----> isTTT " << std::endl;}
		if (tightLepCounter==6){ isTTL=1; if(DEBUGleptons)std::cout << " -----> isTTL " << std::endl;}
		if (tightLepCounter==5){ isTLT=1; if(DEBUGleptons)std::cout << " -----> isTLT " << std::endl;}
		if (tightLepCounter==3){ isLTT=1; if(DEBUGleptons)std::cout << " -----> isLTT " << std::endl;}
		if (tightLepCounter==4){ isTLL=1; if(DEBUGleptons)std::cout << " -----> isTLL " << std::endl;}
		if (tightLepCounter==2){ isLTL=1; if(DEBUGleptons)std::cout << " -----> isLTL " << std::endl;}
		if (tightLepCounter==1){ isLLT=1; if(DEBUGleptons)std::cout << " -----> isLLT " << std::endl;}
		if (tightLepCounter==0){ isLLL=1; if(DEBUGleptons)std::cout << " -----> isLLL " << std::endl;}
      }
      if(Nel_top3==1){
		isEMM = 1;
		EMM_count++;
		if(DEBUGleptons)std::cout << " -----> isEMM " << std::endl;
		Nemm[Nel_tight_top3 + 2*Nmu_tight_top3]++;
		if (tightLepCounter==7){ isTTT=1; if(DEBUGleptons)std::cout << " -----> isTTT " << std::endl;}
		if (tightLepCounter==6){ isTTL=1; if(DEBUGleptons)std::cout << " -----> isTTL " << std::endl;}
		if (tightLepCounter==5){ isTLT=1; if(DEBUGleptons)std::cout << " -----> isTLT " << std::endl;}
		if (tightLepCounter==3){ isLTT=1; if(DEBUGleptons)std::cout << " -----> isLTT " << std::endl;}
		if (tightLepCounter==4){ isTLL=1; if(DEBUGleptons)std::cout << " -----> isTLL " << std::endl;}
		if (tightLepCounter==2){ isLTL=1; if(DEBUGleptons)std::cout << " -----> isLTL " << std::endl;}
		if (tightLepCounter==1){ isLLT=1; if(DEBUGleptons)std::cout << " -----> isLLT " << std::endl;}
		if (tightLepCounter==0){ isLLL=1; if(DEBUGleptons)std::cout << " -----> isLLL " << std::endl;}
      }
      if(Nel_top3==0){
		isMMM = 1;
		MMM_count++;
		if(DEBUGleptons)std::cout << " -----> isMMM " << std::endl;
		Nmmm[Nmu_tight_top3]++;
		if (tightLepCounter==7){ isTTT=1; if(DEBUGleptons)std::cout << " -----> isTTT " << std::endl;}
		if (tightLepCounter==6){ isTTL=1; if(DEBUGleptons)std::cout << " -----> isTTL " << std::endl;}
		if (tightLepCounter==5){ isTLT=1; if(DEBUGleptons)std::cout << " -----> isTLT " << std::endl;}
		if (tightLepCounter==3){ isLTT=1; if(DEBUGleptons)std::cout << " -----> isLTT " << std::endl;}
		if (tightLepCounter==4){ isTLL=1; if(DEBUGleptons)std::cout << " -----> isTLL " << std::endl;}
		if (tightLepCounter==2){ isLTL=1; if(DEBUGleptons)std::cout << " -----> isLTL " << std::endl;}
		if (tightLepCounter==1){ isLLT=1; if(DEBUGleptons)std::cout << " -----> isLLT " << std::endl;}
		if (tightLepCounter==0){ isLLL=1; if(DEBUGleptons)std::cout << " -----> isLLL " << std::endl;}
      }
		
      
      isPassTrilepton = false;
      if(Nel_tight_top3 + Nmu_tight_top3 >= 3){
		nPassTrilepton++;
		isPassTrilepton = true;
		if(DEBUGleptons)std::cout << "pass trilepton cut! (3 tight leptons)" << endl;
      }
      else{
      	if(DEBUGleptons)std::cout << "fail trilepton cut! (no 3 tight leptons), must be for ddbkg?" << endl;
      }
      
	     
      //Determine bkgweights here IF processing DATA. - start
      const int nmodes = 9;
      //mode 0 = nominal. 1 = elfakerate plus, 2 = elfakerate minus, 3 = elpassrate plus, 4 = elpassrate minus, 5 = mufakerate plus, 6 = mufakerate minus, 7 = mupassrate plus, 8 = mupassrate minus
      //see feModeBehavior in fakerate.h

      double bkgweights[nmodes] = {0};
      double bkgweight = 0.;
      ddBkgWeights.clear();
      ddBkgWeights_scan.clear();

      if(!isMC){
	
			vector<double> lep1_info,lep2_info,lep3_info; //at(0): isMu, at(1): isTight, at(2): pt, at(3): eta
			lep1_info.push_back(AllLeptonFlavor_PtOrdered.at(0));lep1_info.push_back(AllLeptonIsTight_PtOrdered.at(0));lep1_info.push_back(AllLeptonPt_PtOrdered.at(0));lep1_info.push_back(AllLeptonEta_PtOrdered.at(0));
			lep2_info.push_back(AllLeptonFlavor_PtOrdered.at(1));lep2_info.push_back(AllLeptonIsTight_PtOrdered.at(1));lep2_info.push_back(AllLeptonPt_PtOrdered.at(1));lep2_info.push_back(AllLeptonEta_PtOrdered.at(1));
			lep3_info.push_back(AllLeptonFlavor_PtOrdered.at(2));lep3_info.push_back(AllLeptonIsTight_PtOrdered.at(2));lep3_info.push_back(AllLeptonPt_PtOrdered.at(2));lep3_info.push_back(AllLeptonEta_PtOrdered.at(2));
			for(int imode=0;imode<nmodes;imode++){
				if(DEBUGddbkg) cout << "" << endl;
				bkgweights[imode] = GetWeight(imode, lep1_info, lep2_info, lep3_info);
			}
			
			//ddbkgweight scan -start
			
			//add mu FR at(4) and initialize to be 0.
			lep1_info.push_back(0.);
			lep2_info.push_back(0.);
			lep3_info.push_back(0.);

			//add el FR at(5) and initialize to be 0.
			lep1_info.push_back(0.);
			lep2_info.push_back(0.);
			lep3_info.push_back(0.);
			
			float increment = 0.01;
			double initial = 0.0;
			double end = 0.5; //1.0; //0.5;
			int loop = (int) ( ( end - initial ) / increment ) + 1;
			
			double muFR = 0.; 
			double elFR = 0.; 
			
			bool scaleFR = false;
			double Zjet_ratio = 1.;
			double ttx_ratio = 1.;
			string whichRatio;
// 			whichRatio = "CR1CR2"; //To measure CR2 by fitting CR1
			whichRatio = "CR2CR1"; //To measure CR1 by fitting CR2
// 			whichRatio = "CR2SR"; //To measure SR by fitting CR2
			if(scaleFR && whichRatio=="CR1CR2") Zjet_ratio = 7.46/4.78;
			if(scaleFR && whichRatio=="CR1CR2") ttx_ratio = 72.59/77.52;
			bool CR2CR1 = false;
			if(scaleFR && whichRatio=="CR2CR1") Zjet_ratio = 4.78/7.46;
			if(scaleFR && whichRatio=="CR2CR1") ttx_ratio = 77.52/72.59;
			bool CR2SR = false;
			if(scaleFR && whichRatio=="CR2SR") Zjet_ratio = 4.78/4.84;
			if(scaleFR && whichRatio=="CR2SR") ttx_ratio = 77.52/86.55;
			if(DEBUGddbkgScan&&scaleFR) cout << "ATTENTION: scaling FR!! "<< whichRatio << " el FR by Zjet_ratio = "<< Zjet_ratio<< ", and mu FR by ttx_ratio = "<<ttx_ratio << endl;

			if(DEBUGddbkgScan) cout << "scanning ddbkg for each muFR and elFR from " << initial << " to " << end << " with increment of "<< increment <<"(" <<loop <<" loops) ." << endl;
			if(DEBUGddbkgScan) cout << "" << endl;	
			int counter = 0;
			for(float i=0; i < loop; i++){
				
				muFR = initial + i*increment;
				
				if(DEBUGddbkgScan) cout << "i = " << i << ", muFR = "<< muFR * ttx_ratio << endl;	

				lep1_info.at(4)=muFR * ttx_ratio;
				lep2_info.at(4)=muFR * ttx_ratio;
				lep3_info.at(4)=muFR * ttx_ratio;				

				for(float j=0; j < loop; j++){

					elFR = initial + j*increment;
				
					if(DEBUGddbkgScan) cout << "j = " << j << ", elFR = "<< elFR * Zjet_ratio << endl;	
			
					lep1_info.at(5)=elFR * Zjet_ratio;
					lep2_info.at(5)=elFR * Zjet_ratio;
					lep3_info.at(5)=elFR * Zjet_ratio;				
				
					if(DEBUGddbkgScan) cout << "lep1_info.at(4) = "<< lep1_info.at(4) <<", lep1_info.at(5) ="<< lep1_info.at(5) << endl;	
					if(DEBUGddbkgScan) cout << "lep2_info.at(4) = "<< lep2_info.at(4) <<", lep2_info.at(5) ="<< lep2_info.at(5)   <<endl;	
					if(DEBUGddbkgScan) cout << "lep3_info.at(4) = "<< lep3_info.at(4) <<", lep3_info.at(5) ="<< lep3_info.at(5)   <<endl;	
								
					bkgweight = GetWeight(0, lep1_info, lep2_info, lep3_info);
				
					ddBkgWeights_scan.push_back(bkgweight);
				
					ddBkgWeights_scan_muFR.push_back(muFR);
					ddBkgWeights_scan_elFR.push_back(elFR);
					if(DEBUGddbkgScan) cout << counter <<". bkgweight (muFR = "<< ddBkgWeights_scan_muFR.at(counter) << ", elFR = "<< ddBkgWeights_scan_elFR.at(counter) << ") = "<< ddBkgWeights_scan.at(counter) <<endl;	
					
					counter++;
					
					if(DEBUGddbkgScan) cout << "" << endl;	

				}
				
				double elFR = 0.; 
				
			}
			//ddbkgweight scan -end

      }//end make background weights.
            
      if(DEBUGddbkg)for(int imode=0;imode<nmodes;imode++)cout << "bkgweights["<<imode<<"] = "<< bkgweights[imode]<<endl;	

      
      for(int imode=0; imode<nmodes;imode++){ddBkgWeights.push_back(bkgweights[imode]);}
			      
      //Determine bkgweights here IF processing DATA. - end
      
      if(DEBUG)std::cout<<"Rizki A - end"<<std::endl;
      
      // ---- Rizki - end

      // ----------------------------------------------------------------------------
      // Pileup weight calculation
      // ----------------------------------------------------------------------------

      pileupWeight = 1.0;
      pileupWeightUp = 1.0;
      pileupWeightDown = 1.0;
      
      if(nTrueInteractions_singleLepCalc > 79) nTrueInteractions_singleLepCalc = 79;
      pileupWeight = pileup_central[nTrueInteractions_singleLepCalc];
      pileupWeightUp = pileup_down[nTrueInteractions_singleLepCalc];
      pileupWeightDown = pileup_up[nTrueInteractions_singleLepCalc];

      // ----------------------------------------------------------------------------
      // Assign Lepton scale factor or efficiency weights, save trigger pass/fail
      // ----------------------------------------------------------------------------

      DataPastTrigger = 0;
      MCPastTrigger = 0;
      TrigEffAltWeight = 1.0;
      TrigEffWeight = 1.0;
      TrigEffWeightUncert = 1.0;
      isoSF = 1.0;
      lepIdSF = 1.0;
      EGammaGsfSF = 1.0;
      MuTrkSF = 1.0;
            
      //Rizki - start

      if(DEBUG)std::cout<<"Rizki B - start"<<std::endl;      

      int   isPastTrig = 0;
      int   isPastTrigMC = 0;
 
      int   isPastTrig_dilep = 0;
      int   isPastTrigMC_dilep = 0;

      float TrigEffAlt = 1.0;
      float TrigEff = 1.0;
      float isosf = 1.0;
      float lepidsf = 1.0;

      if(isMC){ //MC triggers check
      
		if(DEBUGTriggers){
			for(unsigned int itrig=0; itrig < vsSelMCTriggersEl_singleLepCalc->size(); itrig++){
				if(viSelMCTriggersEl_singleLepCalc->at(itrig) > 0) std::cout << "pass El MC trigger : " << vsSelMCTriggersEl_singleLepCalc->at(itrig) << std::endl;
				}
			for(unsigned int itrig=0; itrig < vsSelMCTriggersMu_singleLepCalc->size(); itrig++){
				if(viSelMCTriggersMu_singleLepCalc->at(itrig) > 0) std::cout << "pass Mu MC trigger : " << vsSelMCTriggersMu_singleLepCalc->at(itrig) << std::endl;
				}
		}

		if(DEBUG)std::cout<<"Matching with desired MC trigger selection..."<<std::endl;  

   		if(isEEE){
		  	for(unsigned int itrig=0; itrig < vsSelMCTriggersEl_singleLepCalc->size(); itrig++){
				if( ( 
						//exclusively electron triggers
						( vsSelMCTriggersEl_singleLepCalc->at(itrig).find("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ") != std::string::npos) //||

					) &&  viSelMCTriggersEl_singleLepCalc->at(itrig) > 0 ) { 
					isPastTrigMC = 1;
					isPastTrigMC_dilep = 1;
				}
			}
	  	}
   		if(isEEM){
		  	for(unsigned int itrig=0; itrig < vsSelMCTriggersEl_singleLepCalc->size(); itrig++){
				if( ( 
						//exclusively electron triggers
						( vsSelMCTriggersEl_singleLepCalc->at(itrig).find("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ") != std::string::npos) ||

						//el&mu triggers
						( vsSelMCTriggersEl_singleLepCalc->at(itrig).find("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ") != std::string::npos) ||
						( vsSelMCTriggersEl_singleLepCalc->at(itrig).find("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ") != std::string::npos) //||
						
					) &&  viSelMCTriggersEl_singleLepCalc->at(itrig) > 0 ) { 
					isPastTrigMC = 1;
					isPastTrigMC_dilep = 1;
				}
			}
	  	}
   		if(isEMM){
		  	for(unsigned int itrig=0; itrig < vsSelMCTriggersMu_singleLepCalc->size(); itrig++){
				if( ( 
						//exclusively muon triggers
						( vsSelMCTriggersMu_singleLepCalc->at(itrig).find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8") != std::string::npos) || 	

						//el&mu triggers
						( vsSelMCTriggersMu_singleLepCalc->at(itrig).find("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ") != std::string::npos) ||
						( vsSelMCTriggersMu_singleLepCalc->at(itrig).find("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ") != std::string::npos) //||

					) &&  viSelMCTriggersMu_singleLepCalc->at(itrig) > 0 ) { 
					isPastTrigMC = 1;
					isPastTrigMC_dilep = 1;
				}
			}
	  	}
   		if(isMMM){
		  	for(unsigned int itrig=0; itrig < vsSelMCTriggersMu_singleLepCalc->size(); itrig++){
				if( ( 
						//exclusively muon triggers
						( vsSelMCTriggersMu_singleLepCalc->at(itrig).find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8") != std::string::npos) //|| 	

					) &&  viSelMCTriggersMu_singleLepCalc->at(itrig) > 0 ) { 
					isPastTrigMC = 1;
					isPastTrigMC_dilep = 1;
		  			if(DEBUGTriggers)std::cout << "vsSelMCTriggersMu_singleLepCalc->at(itrig) = " << vsSelMCTriggersMu_singleLepCalc->at(itrig) << std::endl;
					if(DEBUGTriggers)std::cout << "isPastTrigMC ="<< isPastTrigMC << ", isPastTrigMC_dilep = " << isPastTrigMC_dilep << std::endl;
				}
			}
	  	}

		if(DEBUG||DEBUGTriggers)std::cout<< "isPastTrigMC_dilep = " << isPastTrigMC_dilep <<std::endl;  

		if(DEBUG)std::cout<<"Done matching with desired MC trigger selection..."<<std::endl;  

		// APPLY SCALE FACTORS PER EVENT
		for(unsigned int ilep = 0; ilep < TightLeptonPt_PtOrdered.size(); ilep++){
		  double lepeta = TightLeptonEta_PtOrdered.at(ilep);
		  double leppt = TightLeptonPt_PtOrdered.at(ilep);

		  //////// ELECTRONS	  
		  if(TightLeptonFlavor_PtOrdered.at(ilep) == 0){

			//NEED SOME TRIGGER SF/EFFIENCIESS!!

			  // Gsf Tracking scale factor: http://fcouderc.web.cern.ch/fcouderc/EGamma/scaleFactors/Moriond17/approval/RECO/passingRECO/egammaEffi.txt_egammaPlots.pdf
			  if(lepeta < -2.45) EGammaGsfSF *= 1.318;
			  else if(lepeta < -2.4) EGammaGsfSF *= 1.114;
			  else if(lepeta < -2.3) EGammaGsfSF *= 1.025;
			  else if(lepeta < -2.2) EGammaGsfSF *= 1.014;
			  else if(lepeta < -2.0) EGammaGsfSF *= 1.007;
			  else if(lepeta < -1.8) EGammaGsfSF *= 0.995;
			  else if(lepeta < -1.65) EGammaGsfSF *= 0.995;
			  else if(lepeta < -1.566) EGammaGsfSF *= 0.992;
			  else if(lepeta < -1.4442) EGammaGsfSF *= 0.963;
			  else if(lepeta < -1.2) EGammaGsfSF *= 0.990;
			  else if(lepeta < -1.0) EGammaGsfSF *= 0.986;
			  else if(lepeta < -0.6) EGammaGsfSF *= 0.982;
			  else if(lepeta < -0.4) EGammaGsfSF *= 0.985;
			  else if(lepeta < -0.2) EGammaGsfSF *= 0.982;
			  else if(lepeta < 0.0) EGammaGsfSF *= 0.980;
			  else if(lepeta < 0.2) EGammaGsfSF *= 0.985;
			  else if(lepeta < 0.4) EGammaGsfSF *= 0.989;
			  else if(lepeta < 0.6) EGammaGsfSF *= 0.988;
			  else if(lepeta < 1.0) EGammaGsfSF *= 0.988;
			  else if(lepeta < 1.2) EGammaGsfSF *= 0.988;
			  else if(lepeta < 1.4442) EGammaGsfSF *= 0.988;
			  else if(lepeta < 1.566) EGammaGsfSF *= 0.968;
			  else if(lepeta < 1.65) EGammaGsfSF *= 0.990;
			  else if(lepeta < 1.8) EGammaGsfSF *= 0.993;
			  else if(lepeta < 2.0) EGammaGsfSF *= 0.992;
			  else if(lepeta < 2.2) EGammaGsfSF *= 0.998;
			  else if(lepeta < 2.3) EGammaGsfSF *= 1.001;
			  else if(lepeta < 2.4) EGammaGsfSF *= 0.990;
			  else if(lepeta < 2.45) EGammaGsfSF *= 0.971;
			  else EGammaGsfSF *= 0.907;
		  
/*
pT:25 bin:1
pT:30 bin:2
pT:40 bin:3
pT:50 bin:4
pT:60 bin:5
pT:100 bin:6
pT:200 bin:7
*/

/*
eta:-2.5 bin:1
eta:-2 bin:2
eta:-1.56 bin:3
eta:-1.44 bin:4
eta:-0.8 bin:5
eta:0 bin:6
eta:0.8 bin:7
eta:1.44 bin:8
eta:1.56 bin:9
eta:2 bin:10
eta:2.5 bin:11
*/
			  //miniIso < 0.1 scale factors from Julie - see email 23 Jan 2017 - https://mail.google.com/mail/u/0/#search/electron+julie/159cd256f91b7bc4
			  if(fabs(lepeta) < 0.8){
				if(leppt < 30) isoSF *= 0.998895;
				else if(leppt < 40) isoSF *= 0.99895;
				else if(leppt < 50) isoSF *= 0.998976;
				else if(leppt < 60) isoSF *= 0.99797;
				else if(leppt < 100) isoSF *= 0.998991;
				else if(leppt < 200) isoSF *= 1.00201;
				else isoSF *= 1.00101;
			  }
			  else if(fabs(lepeta) < 1.4442){
				if(leppt < 30) isoSF *= 1.00548;
				else if(leppt < 40) isoSF *= 1;
				else if(leppt < 50) isoSF *= 1;
				else if(leppt < 60) isoSF *= 1;
				else if(leppt < 100) isoSF *= 1;
				else if(leppt < 200) isoSF *= 1.00201;
				else isoSF *= 0.999;
			  }
			  else if(fabs(lepeta) < 1.566){
				if(leppt < 30) isoSF *= 1.03018;
				else if(leppt < 40) isoSF *= 1.02317;
				else if(leppt < 50) isoSF *= 1.00551;
				else if(leppt < 60) isoSF *= 1.00109;
				else if(leppt < 100) isoSF *= 1.0195;
				else if(leppt < 200) isoSF *= 1.0062;
				else isoSF *= 1.07296;
			  }
			  else if(fabs(lepeta) < 2.0){
				if(leppt < 30) isoSF *= 0.992432;
				else if(leppt < 40) isoSF *= 0.997912;
				else if(leppt < 50) isoSF *= 0.996942;
				else if(leppt < 60) isoSF *= 0.998989;
				else if(leppt < 100) isoSF *= 0.998995;
				else if(leppt < 200) isoSF *= 1;
				else isoSF *= 0.998;
			  }
			  else {
				if(leppt < 30) isoSF *= 0.978237;
				else if(leppt < 40) isoSF *= 0.987448;
				else if(leppt < 50) isoSF *= 0.99285;
				else if(leppt < 60) isoSF *= 0.997978;
				else if(leppt < 100) isoSF *= 1.00101;
				else if(leppt < 200) isoSF *= 1;
				else isoSF *= 0.997;
			  }

			  //MVA-based ID scale factors for Custom WP from Julie - see email 23 Jan 2017 - https://mail.google.com/mail/u/0/#search/electron+julie/159cd256f91b7bc4
			  if(fabs(lepeta) < 0.8){
				if(leppt < 30) lepIdSF *= 0.96468;
				else if(leppt < 40) lepIdSF *= 0.970716;
				else if(leppt < 50) lepIdSF *= 0.973262;
				else if(leppt < 60) lepIdSF *= 0.973376;
				else if(leppt < 100) lepIdSF *= 0.976571;
				else if(leppt < 200) lepIdSF *= 0.985122;
				else lepIdSF *= 0.984979;
			  }
			  else if(fabs(lepeta) < 1.4442){
				if(leppt < 30) lepIdSF *= 0.935174;
				else if(leppt < 40) lepIdSF *= 0.946512;
				else if(leppt < 50) lepIdSF *= 0.952273;
				else if(leppt < 60) lepIdSF *= 0.951302;
				else if(leppt < 100) lepIdSF *= 0.95618;
				else if(leppt < 200) lepIdSF *= 0.974157;
				else lepIdSF *= 0.941501;
			  }
			  else if(fabs(lepeta) < 1.566){
				if(leppt < 30) lepIdSF *= 0.904402;
				else if(leppt < 40) lepIdSF *= 0.929952;
				else if(leppt < 50) lepIdSF *= 0.938444;
				else if(leppt < 60) lepIdSF *= 0.943483;
				else if(leppt < 100) lepIdSF *= 0.932028;
				else if(leppt < 200) lepIdSF *= 0.982974;
				else lepIdSF *= 1.03924;
			  }
			  else if(fabs(lepeta) < 2.0){
				if(leppt < 30) lepIdSF *= 0.935412;
				else if(leppt < 40) lepIdSF *= 0.947484;
				else if(leppt < 50) lepIdSF *= 0.964516;
				else if(leppt < 60) lepIdSF *= 0.970149;
				else if(leppt < 100) lepIdSF *= 0.971368;
				else if(leppt < 200) lepIdSF *= 0.991605;
				else lepIdSF *= 1.00952;
			  }
			  else {
				if(leppt < 30) lepIdSF *= 0.947066;
				else if(leppt < 40) lepIdSF *= 0.96288;
				else if(leppt < 50) lepIdSF *= 0.970427;
				else if(leppt < 60) lepIdSF *= 0.972826;
				else if(leppt < 100) lepIdSF *= 0.978448;
				else if(leppt < 200) lepIdSF *= 1.01289;
				else lepIdSF *= 0.971398;
			  }
		
		  }

		  //////// MUONS
		  if(TightLeptonFlavor_PtOrdered.at(ilep) == 1){

			//NEED SOME TRIGGER SF/EFFIENCIESS!!

			  // Muon tracking SF -- https://twiki.cern.ch/twiki/bin/viewauth/CMS/MuonWorkInProgressAndPagResults#Results_on_the_full_2016_data, Feb 16 version for full data
			  int ebin = -1;
			  if(lepeta < -2.1) ebin = 0;
			  else if(lepeta < -1.6) ebin = 1;
			  else if(lepeta < -1.2) ebin = 2;
			  else if(lepeta < -0.9) ebin = 3;
			  else if(lepeta < -0.6) ebin = 4;
			  else if(lepeta < -0.3) ebin = 5;
			  else if(lepeta < -0.2) ebin = 6;
			  else if(lepeta <  0.2) ebin = 7;
			  else if(lepeta <  0.3) ebin = 8;
			  else if(lepeta <  0.6) ebin = 9;
			  else if(lepeta <  0.9) ebin = 10;
			  else if(lepeta <  1.2) ebin = 11;
			  else if(lepeta <  1.6) ebin = 12;
			  else if(lepeta <  2.1) ebin = 13;
			  else if(lepeta <  2.4) ebin = 14;

			  MuTrkSF *= tracksf[ebin];

			  //New MorindMC SF for MiniIso<0.1 Clint calculated on https://indico.cern.ch/event/605620/contributions/2441087/attachments/1398025/2132153/VHFMeeting_X53_01.18.17.pdf 
			  if(leppt < 40){
				if(fabs(lepeta) < 0.9) isoSF*= 1.000;
				else if(fabs(lepeta) <  1.2) isoSF*= 1.000;
				else if(fabs(lepeta) <  2.1) isoSF*= 1.000;
				else if(fabs(lepeta) <  2.4) isoSF*= 0.999;
			  }
			  else if(leppt < 50){
				if(fabs(lepeta) < 0.9) isoSF*= 0.999;
				else if(fabs(lepeta) <  1.2) isoSF*= 0.999;
				else if(fabs(lepeta) <  2.1) isoSF*= 0.999;
				else if(fabs(lepeta) <  2.4) isoSF*= 0.999;
			  }
			  else if(leppt < 60){
				if(fabs(lepeta) < 0.9) isoSF*= 0.999;
				else if(fabs(lepeta) <  1.2) isoSF*= 0.999;
				else if(fabs(lepeta) <  2.1) isoSF*= 0.999;
				else if(fabs(lepeta) <  2.4) isoSF*= 1.000;
			  }
			  else if(leppt < 100){
				if(fabs(lepeta) < 0.9) isoSF*= 1.000;
				else if(fabs(lepeta) <  1.2) isoSF*= 1.000;
				else if(fabs(lepeta) <  2.1) isoSF*= 1.000;
				else if(fabs(lepeta) <  2.4) isoSF*= 1.000;
			  }
			  else{
				if(fabs(lepeta) < 0.9) isoSF*= 1.000;
				else if(fabs(lepeta) <  1.2) isoSF*= 1.000;
				else if(fabs(lepeta) <  2.1) isoSF*= 1.000;
				else if(fabs(lepeta) <  2.4) isoSF*= 1.000;
			  }
	  
			  //Cut-based Tight scale factors from Clint's 18Jan2017 calculated on https://indico.cern.ch/event/605620/contributions/2441087/attachments/1398025/2132153/VHFMeeting_X53_01.18.17.pdf
			  if(fabs(lepeta) < 0.9){
				if(leppt < 40) lepIdSF *= 0.983;
				else if(leppt < 50) lepIdSF *= 0.983;
				else if(leppt < 60) lepIdSF *= 0.976;
				else if(leppt < 100) lepIdSF *= 0.961;
				else lepIdSF *= 0.998;
			  }
			  else if(fabs(lepeta) < 1.2){
				if(leppt < 40) lepIdSF *= 0.971;
				else if(leppt < 50) lepIdSF *= 0.972;
				else if(leppt < 60) lepIdSF *= 0.973;
				else if(leppt < 100) lepIdSF *= 0.961;
				else lepIdSF *= 0.992;
			  }
			  else if(fabs(lepeta) < 2.1){
				if(leppt < 40) lepIdSF *= 0.987;
				else if(leppt < 50) lepIdSF *= 0.987;
				else if(leppt < 60) lepIdSF *= 0.985;
				else if(leppt < 100) lepIdSF *= 0.970;
				else lepIdSF *= 1.003;
			  }
			  else {
				if(leppt < 40) lepIdSF *= 0.971;
				else if(leppt < 50) lepIdSF *= 0.972;
				else if(leppt < 60) lepIdSF *= 0.968;
				else if(leppt < 100) lepIdSF *= 0.953;
				else lepIdSF *= 0.986;
			  }
			  
		  }
		}
		
		isPastTrig = 1;
		isPastTrig_dilep = 1;
		
		if(isPastTrigMC) npass_trigger+=1;
      }
      else{ //Data triggers check

		if(DEBUGTriggers){      	
			for(unsigned int itrig=0; itrig < vsSelTriggersEl_singleLepCalc->size(); itrig++){
				if(viSelTriggersEl_singleLepCalc->at(itrig) > 0) std::cout << "pass El trigger : " << vsSelTriggersEl_singleLepCalc->at(itrig) << std::endl;
				}
			for(unsigned int itrig=0; itrig < vsSelTriggersMu_singleLepCalc->size(); itrig++){
				if(viSelTriggersMu_singleLepCalc->at(itrig) > 0) std::cout << "pass Mu trigger : " << vsSelTriggersMu_singleLepCalc->at(itrig) << std::endl;
				}
		}

		if(DEBUG)std::cout<<"Matching with desired trigger selection..."<<std::endl;  
    	
   		if(isEEE){
		  	for(unsigned int itrig=0; itrig < vsSelTriggersEl_singleLepCalc->size(); itrig++){
				if( ( 
						//exclusively electron triggers
						( vsSelTriggersEl_singleLepCalc->at(itrig).find("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ") != std::string::npos) //||

					) &&  viSelTriggersEl_singleLepCalc->at(itrig) > 0 ) { 
					isPastTrig = 1;
					isPastTrig_dilep = 1;
				}
			}
	  	}
   		if(isEEM){
		  	for(unsigned int itrig=0; itrig < vsSelTriggersEl_singleLepCalc->size(); itrig++){
				if( ( 
						//exclusively electron triggers
						( vsSelTriggersEl_singleLepCalc->at(itrig).find("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ") != std::string::npos) ||

						//el&mu triggers
						( vsSelTriggersEl_singleLepCalc->at(itrig).find("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ") != std::string::npos) ||
						( vsSelTriggersEl_singleLepCalc->at(itrig).find("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ") != std::string::npos) //||

					) &&  viSelTriggersEl_singleLepCalc->at(itrig) > 0 ) { 
					isPastTrig = 1;
					isPastTrig_dilep = 1;
				}
			}
	  	}
   		if(isEMM){
		  	for(unsigned int itrig=0; itrig < vsSelTriggersMu_singleLepCalc->size(); itrig++){
				if( ( 
						//exclusively muon triggers
						( vsSelTriggersMu_singleLepCalc->at(itrig).find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8") != std::string::npos) || 	

						//el&mu triggers
						( vsSelTriggersMu_singleLepCalc->at(itrig).find("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ") != std::string::npos) ||
						( vsSelTriggersMu_singleLepCalc->at(itrig).find("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ") != std::string::npos) //||

					) &&  viSelTriggersMu_singleLepCalc->at(itrig) > 0 ) { 
					isPastTrig = 1;
					isPastTrig_dilep = 1;
				}
			}
	  	}
   		if(isMMM){
		  	for(unsigned int itrig=0; itrig < vsSelTriggersMu_singleLepCalc->size(); itrig++){
				if( ( 
						//exclusively muon triggers
						( vsSelTriggersMu_singleLepCalc->at(itrig).find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8") != std::string::npos) //|| 	

					) &&  viSelTriggersMu_singleLepCalc->at(itrig) > 0 ) { 
					isPastTrig = 1;
					isPastTrig_dilep = 1;
		  			if(DEBUGTriggers)std::cout << "vsSelTriggersMu_singleLepCalc->at(itrig) = " << vsSelTriggersMu_singleLepCalc->at(itrig) << std::endl;
					if(DEBUGTriggers)std::cout << "isPastTrig ="<< isPastTrig << ", isPastTrig_dilep = " << isPastTrig_dilep << std::endl;
				}
			}
	  	}

		if(DEBUG||DEBUGTriggers)std::cout<< "isPastTrig_dilep = " << isPastTrig_dilep <<std::endl;  

		if(DEBUG)std::cout<<"Matching with desired MC trigger selection..."<<std::endl;  

      	isPastTrigMC = 1;
		isPastTrigMC_dilep = 1;
		
		if(isPastTrig) npass_trigger+=1;
      }
      
      
      if(DataPastTrigger) npass_trigger+=1; // --> unfinished implementation.
            
      if(DEBUG)std::cout<<"Rizki B - end"<<std::endl;      

      //Rizki - end
      

      // ----------------------------------------------------------------------------
      // Loop over AK4 jets for calculations and pt ordering pair
      // ----------------------------------------------------------------------------

      NJets_singleLepCalc = 0;
      AK4HT = 0;
      vector<pair<double,int>> jetptindpair;
      
      if(DEBUGjets)std::cout<< "AK4JetPt_singleLepCalc->size() (before jet loop) = " << AK4JetPt_singleLepCalc->size() << std::endl;

      for(unsigned int ijet=0; ijet < AK4JetPt_singleLepCalc->size(); ijet++){

		// ----------------------------------------------------------------------------
		// Basic cuts
		// ----------------------------------------------------------------------------
		if(DEBUG)std::cout<<"Basic cuts"<<std::endl;      

		if(AK4JetPt_singleLepCalc->at(ijet) < jetPtCut || fabs(AK4JetEta_singleLepCalc->at(ijet)) > jetEtaCut) continue;

		if(isMC){

		  if(DEBUGjets)std::cout<< "Jet Flavor = " << AK4JetFlav_singleLepCalc->at(ijet) << std::endl;
		  
		  // ----------------------------------------------------------------------------
		  // Counts and pt ordering pair
		  // ----------------------------------------------------------------------------

		  jetptindpair.push_back(std::make_pair(AK4JetPt_singleLepCalc->at(ijet),ijet));
		  NJets_singleLepCalc+=1;
		  AK4HT+=AK4JetPt_singleLepCalc->at(ijet);
	  
		}else{
		  jetptindpair.push_back(std::make_pair(AK4JetPt_singleLepCalc->at(ijet),ijet));
		  NJets_singleLepCalc+=1;
		  AK4HT+=AK4JetPt_singleLepCalc->at(ijet);
		}
      }

      if(DEBUGjets)std::cout<< "NJets (after jet loop) = " << NJets_singleLepCalc << std::endl;

      AK4HTpMETpLepPt = AK4HT + corr_met_singleLepCalc;
//       if(isPassTrilepton){
// 		  for(unsigned int ilep = 0; ilep < TightLeptonPt_PtOrdered.size(); ilep++){
// 			AK4HTpMETpLepPt += TightLeptonPt_PtOrdered.at(ilep);
// 		  }
//       }
//       else{ //for ddbkg (just take 3 top leps in All Lepton List.) ATTENTION: is this fine???
// 		  for(unsigned int ilep = 0; ilep < 3; ilep++){
// 			AK4HTpMETpLepPt += AllLeptonPt_PtOrdered.at(ilep);
// 		  }      
//       }
	  for(unsigned int ilep = 0; ilep < AllLeptonPt_PtOrdered.size(); ilep++){
		AK4HTpMETpLepPt += AllLeptonPt_PtOrdered.at(ilep);
	  }      
      if(DEBUG)std::cout << "AK4HTpMETpLepPt = " << AK4HTpMETpLepPt << std::endl;
	
      // ----------------------------------------------------------------------------
      // Apply pt ordering to AK4 vectors
      // ----------------------------------------------------------------------------
      if(DEBUG)std::cout<<"Apply pt ordering to AK4 vectors"<<std::endl;      

      std::sort(jetptindpair.begin(), jetptindpair.end(), comparepair);
      AK4JetPt_singleLepCalc_PtOrdered.clear();
      AK4JetEta_singleLepCalc_PtOrdered.clear();
      AK4JetPhi_singleLepCalc_PtOrdered.clear();
      AK4JetEnergy_singleLepCalc_PtOrdered.clear();
      AK4JetFlav_singleLepCalc_PtOrdered.clear();
      AK4JetBDisc_singleLepCalc_PtOrdered.clear();
      AK4JetBDeepCSVb_singleLepCalc_PtOrdered.clear();
      AK4JetBDeepCSVbb_singleLepCalc_PtOrdered.clear();
      
      AK4JetBTag_singleLepCalc_PtOrdered.clear();
      AK4JetBTag_bSFdn_singleLepCalc_PtOrdered.clear();
      AK4JetBTag_bSFup_singleLepCalc_PtOrdered.clear();
      AK4JetBTag_lSFdn_singleLepCalc_PtOrdered.clear();
      AK4JetBTag_lSFup_singleLepCalc_PtOrdered.clear();
      for(unsigned int ijet=0; ijet < jetptindpair.size(); ijet++){
      	AK4JetPt_singleLepCalc_PtOrdered.push_back(AK4JetPt_singleLepCalc->at(jetptindpair[ijet].second));
      	AK4JetEta_singleLepCalc_PtOrdered.push_back(AK4JetEta_singleLepCalc->at(jetptindpair[ijet].second));
      	AK4JetPhi_singleLepCalc_PtOrdered.push_back(AK4JetPhi_singleLepCalc->at(jetptindpair[ijet].second));
      	AK4JetEnergy_singleLepCalc_PtOrdered.push_back(AK4JetEnergy_singleLepCalc->at(jetptindpair[ijet].second));
      	AK4JetFlav_singleLepCalc_PtOrdered.push_back(AK4JetFlav_singleLepCalc->at(jetptindpair[ijet].second));
      	AK4JetBDisc_singleLepCalc_PtOrdered.push_back(AK4JetBDisc_singleLepCalc->at(jetptindpair[ijet].second));
      	AK4JetBDeepCSVb_singleLepCalc_PtOrdered.push_back(AK4JetBDeepCSVb_singleLepCalc->at(jetptindpair[ijet].second));
      	AK4JetBDeepCSVbb_singleLepCalc_PtOrdered.push_back(AK4JetBDeepCSVbb_singleLepCalc->at(jetptindpair[ijet].second));
      	AK4JetBTag_singleLepCalc_PtOrdered.push_back(theJetBTag_JetSubCalc->at(jetptindpair[ijet].second)); // ATTENTION !!!!! HACK SO THAT WE USE theJetBTag_JetSubCalc_PtOrdered instead, but keep namings. 9 Nov 2018.
      	AK4JetBTag_bSFdn_singleLepCalc_PtOrdered.push_back(AK4JetBTag_bSFdn_singleLepCalc->at(jetptindpair[ijet].second));
      	AK4JetBTag_bSFup_singleLepCalc_PtOrdered.push_back(AK4JetBTag_bSFup_singleLepCalc->at(jetptindpair[ijet].second));
      	AK4JetBTag_lSFdn_singleLepCalc_PtOrdered.push_back(AK4JetBTag_lSFdn_singleLepCalc->at(jetptindpair[ijet].second));
      	AK4JetBTag_lSFup_singleLepCalc_PtOrdered.push_back(AK4JetBTag_lSFup_singleLepCalc->at(jetptindpair[ijet].second));
      }

      // ----------------------------------------------------------------------------
      // Apply trigger cut : must pass at least one trigger
      // ----------------------------------------------------------------------------

      if(isMC){if(!isPastTrigMC)continue;} // MC trig selection
      else{if(!isPastTrig)continue;} // Data trig selection

      // ----------------------------------------------------------------------------
      // Apply kinematic cuts
      // ----------------------------------------------------------------------------
	  if(DEBUG)std::cout<<"Apply kinematic cuts"<<std::endl;      
	                
      int isPastNJetsCut = 0;
      if(NJets_singleLepCalc >= njetsCut){npass_njets+=1;isPastNJetsCut=1;}
      
      int isPastJetPtCut = 0;
      bool allJetsAboveJetPtCut = true;
      for(unsigned int ijet=0; ijet < AK4JetPt_singleLepCalc_PtOrdered.size(); ijet++){
      		if(AK4JetPt_singleLepCalc_PtOrdered[ijet] < jetPtCut){allJetsAboveJetPtCut=false;} 
      }
      if(allJetsAboveJetPtCut){npass_JetPt+=1;isPastJetPtCut=1;}

      
      int isPastMETcut = 0;
      if(corr_met_singleLepCalc > metCut){npass_met+=1;isPastMETcut=1;}

      int isPastTriLepPtCut = 0;
      if(AllLeptonPt_PtOrdered[0] > lepPtCut && AllLeptonPt_PtOrdered[1] > lepPtCut && AllLeptonPt_PtOrdered[2] > lepPtCut){npass_trilepPt+=1;isPastTriLepPtCut=1;}
      
      
      if(!(isPastMETcut && isPastNJetsCut && isPastJetPtCut && isPastTriLepPtCut)) continue;
      
      npass_all+=1;

      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /////////////// ONLY ON SELECTED EVENTS ////////////////////////////////////////////////////////////////////////////////////
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


      // ----------------------------------------------------------------------------
      // Lepton 4-vectors, calculate MT and electron trigger presel value
      // ----------------------------------------------------------------------------
      if(DEBUG)std::cout<<"Lepton 4-vectors, calculate MT and electron trigger presel value"<<std::endl;      
              
      //Rizki - start

      if(DEBUG)std::cout<<"Rizki C - start"<<std::endl;      

      // Set lepton 4-vectors - NEED TO IMPLEMENT elTrigPresel HERE!! ATTENTION: what is elTrigPresel??
      double lepM; 
      TLorentzVector lv_temp;
      lepton_lv.clear();
      TLorentzVector lv_PtOrderedOnly_temp;
      lepton_PtOrderedOnly_lv.clear();
      //if(AllLeptonPt_PtOrdered.size()<3) std::cout << "Trilepton cut fail!! will segfault when setting lepton_lv 123!!" << std::endl;
      for (unsigned int ilep=0; ilep < AllLeptonPt_PtOrdered.size() ; ilep++){
//       	std::cout << "AllLeptonPt_PtOrdered.size() : " << AllLeptonPt_PtOrdered.size() << std::endl;
//       	std::cout << "ilep : " << ilep << " AllLeptonPt_PtOrdered : " << AllLeptonPt_PtOrdered.at(ilep) << std::endl;
      	lepM = ( AllLeptonFlavor_PtOrdered[ilep]==0? 0.00051099891:0.105658367);
      	lv_temp.SetPtEtaPhiM(AllLeptonPt_PtOrdered.at(ilep),AllLeptonEta_PtOrdered.at(ilep),AllLeptonPhi_PtOrdered.at(ilep),lepM);
      	lepton_lv.push_back(lv_temp);
      	//std::cout << "lep " << ilep+1 << " , flavor :" <<  AllLeptonFlavor_PtOrdered[ilep] << " , pt : " <<AllLeptonPt_PtOrdered.at(ilep) << " ,  eta : "<<AllLeptonEta_PtOrdered.at(ilep) << " , phi : "<<AllLeptonPhi_PtOrdered.at(ilep) << " , mass : " << lepM << std::endl;

		//leptons ordered in pT only
      	lv_PtOrderedOnly_temp.SetPtEtaPhiM(AllLeptonPt_PtOrderedOnly.at(ilep),AllLeptonEta_PtOrderedOnly.at(ilep),AllLeptonPhi_PtOrderedOnly.at(ilep),lepM);
      	lepton_PtOrderedOnly_lv.push_back(lv_PtOrderedOnly_temp);

      }
	
      //calculate Mlll - start
      Mlll = -1 ;
      TLorentzVector lll_lv;
      lll_lv = lepton_lv.at(0)+lepton_lv.at(1)+lepton_lv.at(2);
      Mlll = lll_lv.M();
      //std::cout << "Mlll = " << Mlll << std::endl; 
      //calculate Mlll - end

      //calculate MllOS's - start
      Mll_sameFlavorOS = -1.;
      if(AllLeptonFlavor_PtOrdered.at(0)==AllLeptonFlavor_PtOrdered.at(1) && AllLeptonCharge_PtOrdered.at(0)*AllLeptonCharge_PtOrdered.at(1)== -1){
      	TLorentzVector temp;
      	temp = lepton_lv.at(0)+lepton_lv.at(1);
      	Mll_sameFlavorOS = temp.M();
      	//std::cout << "Mll_sameFlavorOS = " << Mll_sameFlavorOS << " (lep0+lep1)" << std::endl;
      	//std::cout << "pT1 = " << lepton_lv.at(0).Pt() << " pT2 = " << lepton_lv.at(1).Pt() << std::endl;
      	//std::cout << "eta1 = " << lepton_lv.at(0).Eta() << " eta2 = " << lepton_lv.at(1).Eta() << std::endl;
      } 
      else if(AllLeptonFlavor_PtOrdered.at(0)==AllLeptonFlavor_PtOrdered.at(2) && AllLeptonCharge_PtOrdered.at(0)*AllLeptonCharge_PtOrdered.at(2)== -1){
      	TLorentzVector temp;
      	temp = lepton_lv.at(0)+lepton_lv.at(2);
      	Mll_sameFlavorOS = temp.M();
      	//std::cout << "Mll_sameFlavorOS = " << Mll_sameFlavorOS << " (lep0+lep2)" << std::endl;
      	//std::cout << "pT1 = " << lepton_lv.at(0).Pt() << " pT2 = " << lepton_lv.at(2).Pt() << std::endl;
      	//std::cout << "eta1 = " << lepton_lv.at(0).Eta() << " eta2 = " << lepton_lv.at(2).Eta() << std::endl;
      } 
      else if(AllLeptonFlavor_PtOrdered.at(1)==AllLeptonFlavor_PtOrdered.at(2) && AllLeptonCharge_PtOrdered.at(1)*AllLeptonCharge_PtOrdered.at(2)== -1){
      	TLorentzVector temp;
      	temp = lepton_lv.at(1)+lepton_lv.at(2);
      	Mll_sameFlavorOS = temp.M();
      	//std::cout << "Mll_sameFlavorOS = " << Mll_sameFlavorOS << " (lep1+lep2)" << std::endl;
      	//std::cout << "pT2 = " << lepton_lv.at(1).Pt() << " pT3 = " << lepton_lv.at(2).Pt() << std::endl;
      	//std::cout << "eta2 = " << lepton_lv.at(1).Eta() << " eta3 = " << lepton_lv.at(2).Eta() << std::endl;
      }
      else{
      	Mll_sameFlavorOS = -1.;
      	//std::cout << "Mll_sameFlavorOS = " << Mll_sameFlavorOS << std::endl;      	
      } 

      MllOS_allComb.clear();
      unsigned int maxMllOSsize = 45;  //ATTENTION: MAXIMUM allowed leptons = 10 !!! 10C2 = 45 !
      unsigned int maxLepPermutation = ( AllLeptonPt_PtOrdered.size() * AllLeptonPt_PtOrdered.size() -1 ) / 2;
      if (maxLepPermutation > maxMllOSsize) maxMllOSsize = maxLepPermutation;
      for (unsigned int i = 0; i < maxMllOSsize ; i++){
//       for (unsigned int i = 0; i+1 < AllLeptonPt_PtOrdered.size() ; i++){
//       	for (unsigned int j = i+1; j < AllLeptonPt_PtOrdered.size() ; j++){
      		MllOS_allComb.push_back(-1);
//       	}
      }
      int MllOS_count = 0;
      for (unsigned int i = 0; i < AllLeptonPt_PtOrdered.size() ; i++){
      	for (unsigned int j = i+1; j < AllLeptonPt_PtOrdered.size() ; j++){
		  	if(AllLeptonFlavor_PtOrdered.at(i)==AllLeptonFlavor_PtOrdered.at(j) && AllLeptonCharge_PtOrdered.at(i)*AllLeptonCharge_PtOrdered.at(j)== -1){
				TLorentzVector temp;
				temp = lepton_lv.at(i)+lepton_lv.at(j);
				MllOS_allComb.at(MllOS_count)= temp.M();
		  	}
			if(DEBUG||DEBUGleptons)std::cout << "MllOS_allComb ( lep" << i <<"_lep"<< j << ") = " << MllOS_allComb.at(MllOS_count) << std::endl ;
			MllOS_count++;
		}
	  }
	  
	  vector<float>::const_iterator it, it2 ;  
	  // Find the min and max elements in the vector
	  it = std::max_element(MllOS_allComb.begin(), MllOS_allComb.end());
	  MllOS_allComb_max = *it;
	  //std::cout << "MllOS_allComb_max = " << MllOS_allComb_max << std::endl;
	  
	  //find minimum for MllOS_allComb values that are > -1
	  std::vector<float> MllOS_allComb_filled;
	  for(unsigned i=0 ; i < MllOS_allComb.size() ; i++){
	  	if(MllOS_allComb.at(i)>=0)MllOS_allComb_filled.push_back(MllOS_allComb.at(i));
	  }
	  if(MllOS_allComb_filled.size()==0)MllOS_allComb_filled.push_back(-1);
	  it2 = std::min_element(MllOS_allComb_filled.begin(), MllOS_allComb_filled.end());
	  MllOS_allComb_min = *it2;
	  //std::cout << "MllOS_allComb_min = " << MllOS_allComb_min << std::endl;
	  	  
      //calculate MllOS's - end
      
      if(DEBUG)std::cout<<"Rizki C - end"<<std::endl;      

      //Rizki - end
      

      // ----------------------------------------------------------------------------
      // 8TeV Top pT reweighting
      // ----------------------------------------------------------------------------
      if(DEBUG)std::cout<<"8TeV Top pT reweighting"<<std::endl;      


      // ----------------------------------------------------------------------------
      // AK4 Jet - lepton associations
      // ----------------------------------------------------------------------------
      if(DEBUG)std::cout<<"AK4 Jet - lepton associations"<<std::endl;      

      NJetsBTag_singleLepCalc = 0;
      NJetsBTagwithSF_singleLepCalc = 0;
      BJetLeadPt = -99;
      minMleppBjet = 1e8;
      minMleppJet = 1e8;
      minMlllBjet = 1e8;
      deltaRlepJetInMinMljet = -99;
      deltaPhilepJetInMinMljet = -99;
      deltaRlepbJetInMinMlb = -99;
      deltaPhilepbJetInMinMlb = -99;
      minDR_lepJet = 1e8;
      minDR_lep1Jet = 1e8;
      minDR_lep2Jet = 1e8;
      minDR_lep3Jet = 1e8;
      ptRel_minDRlepJet = 1e8;
      ptRel_minDRlep1Jet = 1e8;
      ptRel_minDRlep2Jet = 1e8;
      ptRel_minDRlep3Jet = 1e8;
      minDR_lepMET = 1e8;
      minDR_METJet = 1e8;
      minDPhi_METJet = 1e8;
      BJetLeadPt_shifts.clear();
      deltaR_lepJets.clear();
      deltaR_lep1Jets.clear();
      deltaR_lep2Jets.clear();
      deltaR_lep3Jets.clear();
      ptRel_lepJets.clear();
      ptRel_lep1Jets.clear();
      ptRel_lep2Jets.clear();
      ptRel_lep3Jets.clear();
      deltaR_lepMETs.clear();
      deltaR_METJets.clear();
      deltaR_lepBJets.clear();
      deltaR_lepBJets_bSFup.clear();
      deltaR_lepBJets_bSFdn.clear();
      deltaR_lepBJets_lSFup.clear();
      deltaR_lepBJets_lSFdn.clear();
      deltaPhi_lepJets.clear();
      deltaPhi_lepBJets.clear();
      deltaPhi_lepBJets_bSFup.clear();
      deltaPhi_lepBJets_bSFdn.clear();
      deltaPhi_lepBJets_lSFup.clear();
      deltaPhi_lepBJets_lSFdn.clear();
      mass_lepJets.clear();
      mass_lepBJets.clear();
      mass_lepBJets_bSFup.clear();
      mass_lepBJets_bSFdn.clear();
      mass_lepBJets_lSFup.clear();
      mass_lepBJets_lSFdn.clear();
      NJetsBTagwithSF_singleLepCalc_shifts.clear();
      minMleppBjet_shifts.clear();
      minMlllBjet_shifts.clear();
      deltaRlepbJetInMinMlb_shifts.clear();
      deltaPhilepbJetInMinMlb_shifts.clear();
      for(int i = 0; i < 4; i++){
		BJetLeadPt_shifts.push_back(-99);
		NJetsBTagwithSF_singleLepCalc_shifts.push_back(0);
		minMleppBjet_shifts.push_back(1e8);
		minMlllBjet_shifts.push_back(1e8);
		deltaRlepbJetInMinMlb_shifts.push_back(-99);
		deltaPhilepbJetInMinMlb_shifts.push_back(-99);
      }	

      for(unsigned int ijet=0; ijet < AK4JetPt_singleLepCalc_PtOrdered.size(); ijet++){
        jet_lv.SetPtEtaPhiE(AK4JetPt_singleLepCalc_PtOrdered.at(ijet),AK4JetEta_singleLepCalc_PtOrdered.at(ijet),AK4JetPhi_singleLepCalc_PtOrdered.at(ijet),AK4JetEnergy_singleLepCalc_PtOrdered.at(ijet));
        

		for(unsigned int ilep=0; ilep<lepton_PtOrderedOnly_lv.size();ilep++){
			if((lepton_PtOrderedOnly_lv.at(ilep) + jet_lv).M() < minMleppJet) {
			  minMleppJet = fabs((lepton_PtOrderedOnly_lv.at(ilep) + jet_lv).M());
			  deltaRlepJetInMinMljet = jet_lv.DeltaR(lepton_PtOrderedOnly_lv.at(ilep));
			  deltaPhilepJetInMinMljet = jet_lv.DeltaPhi(lepton_PtOrderedOnly_lv.at(ilep));
			}
		}


		//calculate dR(leps,jets) and min - start
		for (unsigned int ilep=0; ilep < lepton_PtOrderedOnly_lv.size() ; ilep++){
			deltaR_lepJets.push_back(jet_lv.DeltaR(lepton_PtOrderedOnly_lv.at(ilep)));
			ptRel_lepJets.push_back( lepton_PtOrderedOnly_lv.at(ilep).P()*(jet_lv.Vect().Cross(lepton_PtOrderedOnly_lv.at(ilep).Vect()).Mag()/jet_lv.P()/lepton_PtOrderedOnly_lv.at(ilep).P()) );
			if(ilep==0){
				deltaR_lep1Jets.push_back(jet_lv.DeltaR(lepton_PtOrderedOnly_lv.at(0)));
				ptRel_lep1Jets.push_back( lepton_PtOrderedOnly_lv.at(ilep).P()*(jet_lv.Vect().Cross(lepton_PtOrderedOnly_lv.at(ilep).Vect()).Mag()/jet_lv.P()/lepton_PtOrderedOnly_lv.at(ilep).P()) );
			}
			if(ilep==1){
				deltaR_lep2Jets.push_back(jet_lv.DeltaR(lepton_PtOrderedOnly_lv.at(1)));
				ptRel_lep2Jets.push_back( lepton_PtOrderedOnly_lv.at(ilep).P()*(jet_lv.Vect().Cross(lepton_PtOrderedOnly_lv.at(ilep).Vect()).Mag()/jet_lv.P()/lepton_PtOrderedOnly_lv.at(ilep).P()) );
			}
			if(ilep==2){
				deltaR_lep3Jets.push_back(jet_lv.DeltaR(lepton_PtOrderedOnly_lv.at(2)));
				ptRel_lep3Jets.push_back( lepton_PtOrderedOnly_lv.at(ilep).P()*(jet_lv.Vect().Cross(lepton_PtOrderedOnly_lv.at(ilep).Vect()).Mag()/jet_lv.P()/lepton_PtOrderedOnly_lv.at(ilep).P()) );
			}


			if(DEBUGjets||DEBUGleptons) std::cout << "dR(lep"<<ilep+1<<",jet"<<ijet+1<<") = "<< jet_lv.DeltaR(lepton_PtOrderedOnly_lv.at(ilep)) << "	ptRel = "<< ptRel_lepJets.at(ijet*lepton_PtOrderedOnly_lv.size() + ilep) <<  std::endl;
		}
		//find minimum 
		vector<double>::iterator minDR_lep1Jet_it;  
		minDR_lep1Jet_it = std::min_element(deltaR_lep1Jets.begin(), deltaR_lep1Jets.end());
		if(minDR_lep1Jet > *minDR_lep1Jet_it){
			minDR_lep1Jet = *minDR_lep1Jet_it;
			int min_at = std::distance(deltaR_lep1Jets.begin(), minDR_lep1Jet_it);
			ptRel_minDRlep1Jet = ptRel_lep1Jets.at(min_at); 
		}

		vector<double>::iterator minDR_lep2Jet_it;  
		minDR_lep2Jet_it = std::min_element(deltaR_lep2Jets.begin(), deltaR_lep2Jets.end());
		if(minDR_lep2Jet > *minDR_lep2Jet_it){
			minDR_lep2Jet = *minDR_lep2Jet_it;
			int min_at = std::distance(deltaR_lep2Jets.begin(), minDR_lep2Jet_it);
			ptRel_minDRlep2Jet = ptRel_lep2Jets.at(min_at); 
		}

		vector<double>::iterator minDR_lep3Jet_it;  
		minDR_lep3Jet_it = std::min_element(deltaR_lep3Jets.begin(), deltaR_lep3Jets.end());
		if(minDR_lep3Jet > *minDR_lep3Jet_it){
			minDR_lep3Jet = *minDR_lep3Jet_it;
			int min_at = std::distance(deltaR_lep3Jets.begin(), minDR_lep3Jet_it);
			ptRel_minDRlep3Jet = ptRel_lep3Jets.at(min_at); 
		}

		vector<double>::iterator minDR_lepJet_it;  
		minDR_lepJet_it = std::min_element(deltaR_lepJets.begin(), deltaR_lepJets.end());
		if(minDR_lepJet > *minDR_lepJet_it){
			minDR_lepJet = *minDR_lepJet_it;
			int min_at = std::distance(deltaR_lepJets.begin(), minDR_lepJet_it);
			ptRel_minDRlepJet = ptRel_lepJets.at(min_at); 
			
		}
		//calculate dR(leps,jets) and min - end
		
		//calculate dR(MET,jets) and min - start
		//calculate dR(MET,jets) and min - end

		//calculate minDPhi(MET,jet) - start
		if(DEBUG || DEBUGjets) cout << "MET phi = "<< corr_met_phi_singleLepCalc << ", jet ("<< ijet <<") phi = " << jet_lv.Phi()<<endl;
		double DPhi_METJet_temp = fabs(corr_met_phi_singleLepCalc - jet_lv.Phi());
		if(DPhi_METJet_temp > M_PI) DPhi_METJet_temp = fabs(DPhi_METJet_temp - 2*M_PI);
		if(DEBUG || DEBUGjets) cout << "minDPhi_METJet("<< ijet <<") = " << minDPhi_METJet;
		if(DPhi_METJet_temp < minDPhi_METJet){
			minDPhi_METJet = DPhi_METJet_temp;
			if(DEBUG || DEBUGjets) cout << " --> " << minDPhi_METJet;
			}
		if(DEBUG || DEBUGjets) cout << "" << endl;
		//calculate minDPhi(MET,jet) - end


		// Count BTag withOUT SFs
		if(AK4JetBDeepCSVbb_singleLepCalc_PtOrdered.at(ijet) + AK4JetBDeepCSVbb_singleLepCalc_PtOrdered.at(ijet) > 0.4941){ // ATTENTION !!! : HARD CODED BTAG MEDIUM VALUE for 2017data. 9 Nov 2018.
			  NJetsBTag_singleLepCalc += 1;
			}

		// Count BTag with SFs
		if(AK4JetBTag_singleLepCalc_PtOrdered.at(ijet) == 1){
		  NJetsBTagwithSF_singleLepCalc += 1;
		  if(AK4JetPt_singleLepCalc_PtOrdered.at(ijet) > BJetLeadPt) BJetLeadPt = AK4JetPt_singleLepCalc_PtOrdered.at(ijet);
		  
		  
		  if(DEBUG || DEBUGleptons) cout << "min M[lep,BJet("<<NJetsBTagwithSF_singleLepCalc<<")] = " ;
		  if(DEBUG || DEBUGleptons) cout <<  minMleppBjet ; 
		  for(unsigned int ilep=0; ilep<lepton_PtOrderedOnly_lv.size();ilep++){
			  if((lepton_PtOrderedOnly_lv.at(ilep) + jet_lv).M() < minMleppBjet) {
				minMleppBjet = fabs( (lepton_PtOrderedOnly_lv.at(ilep) + jet_lv).M() );
				deltaRlepbJetInMinMlb = jet_lv.DeltaR(lepton_PtOrderedOnly_lv.at(ilep));
				deltaPhilepbJetInMinMlb = jet_lv.DeltaPhi(lepton_PtOrderedOnly_lv.at(ilep));
				if(DEBUG || DEBUGleptons) cout << " --> "<<  minMleppBjet ;
			  }
		  }
		  if(DEBUG || DEBUGleptons) cout << "" << endl; 
		  
		  if(DEBUG || DEBUGleptons) cout << "min M[lllBJet("<<NJetsBTagwithSF_singleLepCalc<<")] = " ;
		  double minMlllBjet_temp =(lepton_PtOrderedOnly_lv.at(0)+lepton_PtOrderedOnly_lv.at(1)+lepton_PtOrderedOnly_lv.at(2) + jet_lv).M();
		  if(DEBUG || DEBUGleptons) cout <<  minMlllBjet ; 
		  if( minMlllBjet_temp < minMlllBjet) {
			minMlllBjet = fabs(minMlllBjet_temp);
			if(DEBUG || DEBUGleptons) cout << " --> "<<  minMlllBjet ; 
		  }
		  if(DEBUG || DEBUGleptons) cout << "" << endl; 

		  
		}
		if(AK4JetBTag_bSFup_singleLepCalc_PtOrdered.at(ijet) == 1){
		  NJetsBTagwithSF_singleLepCalc_shifts.at(0) += 1;
		  if(AK4JetPt_singleLepCalc_PtOrdered.at(ijet) > BJetLeadPt_shifts.at(0)) BJetLeadPt_shifts.at(0) = AK4JetPt_singleLepCalc_PtOrdered.at(ijet);
		  

		  for(unsigned int ilep=0; ilep<lepton_PtOrderedOnly_lv.size();ilep++){
			  if((lepton_PtOrderedOnly_lv.at(ilep) + jet_lv).M() < minMleppBjet) {
				minMleppBjet_shifts.at(0) = fabs( (lepton_PtOrderedOnly_lv.at(ilep) + jet_lv).M() );
				deltaRlepbJetInMinMlb_shifts.at(0) = jet_lv.DeltaR(lepton_PtOrderedOnly_lv.at(ilep));
				deltaPhilepbJetInMinMlb_shifts.at(0) = jet_lv.DeltaPhi(lepton_PtOrderedOnly_lv.at(ilep));
			  }
		  }

		  if(DEBUG || DEBUGleptons) cout << "min M[lllBJet("<<NJetsBTagwithSF_singleLepCalc<<")] (shift.at(0)) = " ;
		  double minMlllBjet_temp =(lepton_PtOrderedOnly_lv.at(0)+lepton_PtOrderedOnly_lv.at(1)+lepton_PtOrderedOnly_lv.at(2) + jet_lv).M();
		  if(DEBUG || DEBUGleptons) cout <<  minMlllBjet_shifts.at(0) ; 
		  if( minMlllBjet_temp < minMlllBjet_shifts.at(0)) {
			minMlllBjet_shifts.at(0) = fabs(minMlllBjet_temp);
			if(DEBUG || DEBUGleptons) cout << " --> "<<  minMlllBjet_shifts.at(0) ; 
		  }
		  if(DEBUG || DEBUGleptons) cout << "" << endl; 

		}
		if(AK4JetBTag_bSFdn_singleLepCalc_PtOrdered.at(ijet) == 1){
		  NJetsBTagwithSF_singleLepCalc_shifts.at(1) += 1;
		  if(AK4JetPt_singleLepCalc_PtOrdered.at(ijet) > BJetLeadPt_shifts.at(1)) BJetLeadPt_shifts.at(1) = AK4JetPt_singleLepCalc_PtOrdered.at(ijet);
		  

		  for(unsigned int ilep=0; ilep<lepton_PtOrderedOnly_lv.size();ilep++){
			  if((lepton_PtOrderedOnly_lv.at(ilep) + jet_lv).M() < minMleppBjet) {
				minMleppBjet_shifts.at(1) = fabs( (lepton_PtOrderedOnly_lv.at(ilep) + jet_lv).M() );
				deltaRlepbJetInMinMlb_shifts.at(1) = jet_lv.DeltaR(lepton_PtOrderedOnly_lv.at(ilep));
				deltaPhilepbJetInMinMlb_shifts.at(1) = jet_lv.DeltaPhi(lepton_PtOrderedOnly_lv.at(ilep));
			  }
		  }

		  if(DEBUG || DEBUGleptons) cout << "min M[lllBJet("<<NJetsBTagwithSF_singleLepCalc<<")] (shift.at(1)) = " ;
		  double minMlllBjet_temp =(lepton_PtOrderedOnly_lv.at(0)+lepton_PtOrderedOnly_lv.at(1)+lepton_PtOrderedOnly_lv.at(2) + jet_lv).M();
		  if(DEBUG || DEBUGleptons) cout <<  minMlllBjet_shifts.at(1) ; 
		  if( minMlllBjet_temp < minMlllBjet_shifts.at(1)) {
			minMlllBjet_shifts.at(1) = fabs(minMlllBjet_temp);
			if(DEBUG || DEBUGleptons) cout << " --> "<<  minMlllBjet_shifts.at(1) ; 
		  }
		  if(DEBUG || DEBUGleptons) cout << "" << endl; 


		}
		if(AK4JetBTag_lSFup_singleLepCalc_PtOrdered.at(ijet) == 1){
		  NJetsBTagwithSF_singleLepCalc_shifts.at(2) += 1;
		  if(AK4JetPt_singleLepCalc_PtOrdered.at(ijet) > BJetLeadPt_shifts.at(2)) BJetLeadPt_shifts.at(2) = AK4JetPt_singleLepCalc_PtOrdered.at(ijet);
		  

		  for(unsigned int ilep=0; ilep<lepton_PtOrderedOnly_lv.size();ilep++){
			  if((lepton_PtOrderedOnly_lv.at(ilep) + jet_lv).M() < minMleppBjet) {
				minMleppBjet_shifts.at(2) = fabs( (lepton_PtOrderedOnly_lv.at(ilep) + jet_lv).M() );
				deltaRlepbJetInMinMlb_shifts.at(2) = jet_lv.DeltaR(lepton_PtOrderedOnly_lv.at(ilep));
				deltaPhilepbJetInMinMlb_shifts.at(2) = jet_lv.DeltaPhi(lepton_PtOrderedOnly_lv.at(ilep));
			  }
		  }

		  if(DEBUG || DEBUGleptons) cout << "min M[lllBJet("<<NJetsBTagwithSF_singleLepCalc<<")] (shift.at(2)) = " ;
		  double minMlllBjet_temp =(lepton_PtOrderedOnly_lv.at(0)+lepton_PtOrderedOnly_lv.at(1)+lepton_PtOrderedOnly_lv.at(2) + jet_lv).M();
		  if(DEBUG || DEBUGleptons) cout <<  minMlllBjet_shifts.at(2) ; 
		  if( minMlllBjet_temp < minMlllBjet_shifts.at(2)) {
			minMlllBjet_shifts.at(2) = fabs(minMlllBjet_temp);
			if(DEBUG || DEBUGleptons) cout << " --> "<<  minMlllBjet_shifts.at(2) ; 
		  }
		  if(DEBUG || DEBUGleptons) cout << "" << endl; 


		}
		if(AK4JetBTag_lSFdn_singleLepCalc_PtOrdered.at(ijet) == 1){
		  NJetsBTagwithSF_singleLepCalc_shifts.at(3) += 1;
		  if(AK4JetPt_singleLepCalc_PtOrdered.at(ijet) > BJetLeadPt_shifts.at(3)) BJetLeadPt_shifts.at(3) = AK4JetPt_singleLepCalc_PtOrdered.at(ijet);


		  for(unsigned int ilep=0; ilep<lepton_PtOrderedOnly_lv.size();ilep++){
			  if((lepton_PtOrderedOnly_lv.at(ilep) + jet_lv).M() < minMleppBjet) {
				minMleppBjet_shifts.at(3) = fabs( (lepton_PtOrderedOnly_lv.at(ilep) + jet_lv).M() );
				deltaRlepbJetInMinMlb_shifts.at(3) = jet_lv.DeltaR(lepton_PtOrderedOnly_lv.at(ilep));
				deltaPhilepbJetInMinMlb_shifts.at(3) = jet_lv.DeltaPhi(lepton_PtOrderedOnly_lv.at(ilep));
			  }
		  }

		  if(DEBUG || DEBUGleptons) cout << "min M[lllBJet("<<NJetsBTagwithSF_singleLepCalc<<")] (shift.at(3)) = " ;
		  double minMlllBjet_temp =(lepton_PtOrderedOnly_lv.at(0)+lepton_PtOrderedOnly_lv.at(1)+lepton_PtOrderedOnly_lv.at(2) + jet_lv).M();
		  if(DEBUG || DEBUGleptons) cout <<  minMlllBjet_shifts.at(3) ; 
		  if( minMlllBjet_temp < minMlllBjet_shifts.at(3)) {
			minMlllBjet_shifts.at(3) = fabs(minMlllBjet_temp);
			if(DEBUG || DEBUGleptons) cout << " --> "<<  minMlllBjet_shifts.at(3) ; 
		  }
		  if(DEBUG || DEBUGleptons) cout << "" << endl; 

		}
      	
      }
      
      if(DEBUGjets||DEBUGleptons) std::cout << "min dR(lep1,jets) = "<< minDR_lep1Jet << "	ptRel = "<< ptRel_minDRlep1Jet << std::endl;
      if(DEBUGjets||DEBUGleptons) std::cout << "min dR(lep2,jets) = "<< minDR_lep2Jet << "	ptRel = "<< ptRel_minDRlep2Jet << std::endl;
      if(DEBUGjets||DEBUGleptons) std::cout << "min dR(lep3,jets) = "<< minDR_lep3Jet << "	ptRel = "<< ptRel_minDRlep3Jet << std::endl;
      if(DEBUGjets||DEBUGleptons) std::cout << "min dR(leps,jets) = "<< minDR_lepJet << "	ptRel = "<< ptRel_minDRlepJet << std::endl;
      

      // ----------------------------------------------------------------------------
      // PDF and Matrix Element energy scale weights
      // ----------------------------------------------------------------------------
      if(DEBUG)std::cout<<"PDF and Matrix Element energy scale weights"<<std::endl;      

      std::vector<double> renorm;
      std::vector<double> pdf;
      renormWeights.clear();
      pdfWeights.clear();
      if(isSig){
		// SEEMS TO APPLY TO ALL B2G MG+PYTHIA SIGNALS. LEADING ORDER 4-FLAVOR PDF
		for(unsigned int i = 0; i < LHEweightids_singleLepCalc->size(); i++){
		  if(LHEweightids_singleLepCalc->at(i) > 1 && LHEweightids_singleLepCalc->at(i) < 10){
			if(LHEweightids_singleLepCalc->at(i) == 6 || LHEweightids_singleLepCalc->at(i) == 8) continue;
			renorm.push_back(LHEweights_singleLepCalc->at(i));
			renormWeights.push_back(LHEweights_singleLepCalc->at(i));
		  }
		  if(LHEweightids_singleLepCalc->at(i) > 111 && LHEweightids_singleLepCalc->at(i) < 212){
			pdf.push_back(LHEweights_singleLepCalc->at(i));	    
			pdfWeights.push_back(LHEweights_singleLepCalc->at(i));	    
		  }
		}
      }
      else if(isMadgraphBkg){
		// SEEMS TO APPLY TO OTHER MG+PYTHIA BACKGROUNDS. LEADING ORDER 5-FLAVOR PDF
		for(unsigned int i = 0; i < LHEweightids_singleLepCalc->size(); i++){
		  if(LHEweightids_singleLepCalc->at(i) > 1 && LHEweightids_singleLepCalc->at(i) < 10){
			if(LHEweightids_singleLepCalc->at(i) == 6 || LHEweightids_singleLepCalc->at(i) == 8) continue;
			renorm.push_back(LHEweights_singleLepCalc->at(i));
			renormWeights.push_back(LHEweights_singleLepCalc->at(i));
		  }
		  if(LHEweightids_singleLepCalc->at(i) > 10 && LHEweightids_singleLepCalc->at(i) < 111){
			pdf.push_back(LHEweights_singleLepCalc->at(i));
			pdfWeights.push_back(LHEweights_singleLepCalc->at(i));
		  }
		}
      }
      else{
		// SEEMS TO APPLY TO ALL POWHEG AND MC@NLO BACKGROUNDS. NLO PDFs
		for(unsigned int i = 0; i < LHEweightids_singleLepCalc->size(); i++){
		  if(LHEweightids_singleLepCalc->at(i) > 1001 && LHEweightids_singleLepCalc->at(i) < 1010){
			if(LHEweightids_singleLepCalc->at(i) == 1006 || LHEweightids_singleLepCalc->at(i) == 1008) continue;
			renorm.push_back(LHEweights_singleLepCalc->at(i));
			renormWeights.push_back(LHEweights_singleLepCalc->at(i));
		  }
		  if(LHEweightids_singleLepCalc->at(i) > 2000 && LHEweightids_singleLepCalc->at(i) < 2101){
			pdf.push_back(LHEweights_singleLepCalc->at(i));
			pdfWeights.push_back(LHEweights_singleLepCalc->at(i));
		  }
		  if(LHEweightids_singleLepCalc->at(i) == 2101 || LHEweightids_singleLepCalc->at(i) == 2102){
			alphaSWeights.push_back(LHEweights_singleLepCalc->at(i));
		  }
		}
      }

      if(renormWeights.size() == 0){
		for(int irn = 0; irn < 6; irn++){
		  renormWeights.push_back(1.0);
		}
      }
      if(pdfWeights.size() == 0){
		for(int ipdf = 0; ipdf < 100; ipdf++){
		  pdfWeights.push_back(1.0);
		}
      }

      // ----------------------------------------------------------------------------
      // DONE!! Write the tree
      // ----------------------------------------------------------------------------
      if(DEBUG)std::cout<<"DONE!! Write the tree"<<std::endl;      

      MCPastTrigger_dilep         = (int)   isPastTrigMC_dilep;
      DataPastTrigger_dilep       = (int)   isPastTrig_dilep;
      
      if(DEBUGjets)std::cout<< "NJets (just before filling tree) = " << NJets_singleLepCalc << std::endl;
 
      outputTree->Fill();
   }

   std::cout<<""<<std::endl;
   std::cout<<"=======END STATS==========   "<<std::endl;
   std::cout<<""<<std::endl;

   //std::cout<<"Nelectrons             = "<<Nelectrons<<" / "<<nentries<<std::endl;
   //std::cout<<"Nmuons                 = "<<Nmuons<<" / "<<nentries<<std::endl;
   std::cout<<"Npassed_Trigger  = "<<npass_trigger<<" / "<<nentries<<std::endl;
   std::cout<<"Npassed_trilepPt       = "<<npass_trilepPt<<" / "<<nentries<<std::endl;
   std::cout<<"Npassed_MET            = "<<npass_met<<" / "<<nentries<<std::endl;
   std::cout<<"Npassed_nJets          = "<<npass_njets<<" / "<<nentries<<std::endl;
   std::cout<<"Npassed_JetPt          = "<<npass_JetPt<<" / "<<nentries<<std::endl;
   //std::cout<<"Npassed_ElEta          = "<<npass_ElEta<<" / "<<nentries<<std::endl;
   std::cout<<"Npassed_ALL            = "<<npass_all<<" / "<<nentries<<std::endl;

   printf("Counts of eee: LLL(%i), LLT(%i), LTT(%i), TTT(%i) : %i \n", Neee[0], Neee[1], Neee[2], Neee[3], EEE_count);
   printf("Counts of eem: LLL(%i), LLT(%i), LTL(%i), LTT(%i), TTL(%i), TTT(%i) : %i \n", Neem[0], Neem[1], Neem[2], Neem[3], Neem[4], Neem[5], EEM_count);
   printf("Counts of emm: LLL(%i), TLL(%i), LLT(%i), TLT(%i), LTT(%i), TTT(%i) : %i \n", Nemm[0], Nemm[1], Nemm[2], Nemm[3], Nemm[4], Nemm[5], EMM_count);
   printf("Counts of mmm: LLL(%i), LLT(%i), LTT(%i), TTT(%i) : %i \n", Nmmm[0], Nmmm[1], Nmmm[2], Nmmm[3], MMM_count);

   std::cout<<""<<std::endl;

   outputTree->Write();

}

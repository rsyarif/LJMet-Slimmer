
using namespace std;

void MCGamma_conversionCheck(){

	bool PrintMixedChannels = false;
	cout << "PrintMixedChannels = " << PrintMixedChannels << endl;	
	bool printSource = false;
	
	TString f_str = " root://cmseos.fnal.gov//store/user/lpcljm/LJMet80x_3lepTT_Full2016_Moriond17_extra_wGammas_2017_11_28_rizki_MCtruth_7Dec2017_ttG_step1hadds/nominal/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_hadd.root";
// 	TString f_str = "root://cmseos.fnal.gov://store/user/lpcljm/LJMet80x_3lep_Moriond17_ttbarFakeRate_saveLooseMC_2017_4_17_dR0p01_PRv9_FRv48_elMVAaltFix_rizki_step1hadds/nominal/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_hadd.root"; //fakerate was measured using LJMet80x_1orMorelep_Moriond17_ttbarFakeRate_saveLooseMC_2017_4_17_dR0p01_elMVAaltFix_rizki_step1hadds/nominal/TT_....1_hadd.root
		
	TFile *f = TFile::Open(f_str, "READ");
	
	cout << "Opening file:" << f_str << endl;

	TTree *t = (TTree*) f->Get("ljmet");
	
// 	TString saveDir = "MCGamma_conversionCheck_Dec7-2017";
// 
// 	system("mkdir -v "+saveDir);


	// FR 1 or more leptons -- ttbar
// 	float elFR = 0.35;	
// 	float elFR_isNotMatched = 0.61;	
// 	float elFR_isFromB = 0.18;	
// 	float elFR_isFromC = 0.24;	
// 	float elFR_isFromL = 0.40;	
// 	float elFR_isFromElse = 0.85;	
// 
// 	float muFR = 0.13;	
// 	float muFR_isNotMatched = 0.02;	
// 	float muFR_isFromB = 0.14;	
// 	float muFR_isFromC = 0.23;	
// 	float muFR_isFromL = 0.65;	
// 	float muFR_isFromElse = 0.79;	

	// FR 3 leptons -- ttbar
// 	float elFR = 0.24;	
// 	float elFR_isNotMatched = 0.50;	
// 	float elFR_isFromB = 0.18;	
// 	float elFR_isFromC = 0.27;	
// 	float elFR_isFromL = 0.5;	
// 	float elFR_isFromElse = 1.0;	
// 
// 	float muFR = 0.13;	
// 	float muFR_isNotMatched = 0.0;	
// 	float muFR_isFromB = 0.13;	
// 	float muFR_isFromC = 0.12;	
// 	float muFR_isFromL = 0.67;	
// 	float muFR_isFromElse = 0.81;	

	// FR 3 leptons -- DY
// 	float elFR = 0.50;	
// 	float elFR_isNotMatched = 0.51;	
// 	float elFR_isFromB = 0.24;	
// 	float elFR_isFromC = 0.30;	
// 	float elFR_isFromL = 0.85;	
// 	float elFR_isFromElse = 0.93;	
// 
// 	float muFR = 0.12;	
// 	float muFR_isNotMatched = 0.0;	
// 	float muFR_isFromB = 0.17;	
// 	float muFR_isFromC = 0.29;	
// 	float muFR_isFromL = 0.95;	
// 	float muFR_isFromElse = 0.90;	


	// FR 1 or more leptons -- ttbar -- elMVAvalueFix -- Sep18-2017
	float elFR = 0.25;	
	float elFR_isNotMatched = 0.40;	
	float elFR_isFromB = 0.15;	
	float elFR_isFromC = 0.18;	
	float elFR_isFromL = 0.27;	
	float elFR_isFromElse = 0.69;	
	float elFR_isFromPh = 1.0;	//PLACEHOLDER!

	float muFR = 0.13;	
	float muFR_isNotMatched = 0.02;	
	float muFR_isFromB = 0.14;	
	float muFR_isFromC = 0.20;	
	float muFR_isFromL = 0.77;	
	float muFR_isFromElse = 0.57;	
	float muFR_isFromPh = 1.0;	//PLACEHOLDER!


// 	TString observ = "AllLeptonPt_PtOrdered";
	TString observ = "AK4HTpMETpLepPt";

	TString trig = " && MCPastTrigger_dilep == 1";
	TString trilep = " && isPassTrilepton==1";
	TString lepPt = " && (AllLeptonPt_PtOrdered[0]>30 && AllLeptonPt_PtOrdered[1]>30 && AllLeptonPt_PtOrdered[2]>0)";
	TString exactly3Lep = " && AllLeptonCount_PtOrdered==3";

	TString njet = " && 1";
// 	TString njet = " && (NJets_singleLepCalc ==1)";
// 	TString njet = " && (NJets_singleLepCalc ==2)";
// 	TString njet = " && (NJets_singleLepCalc > 2)";

// 	TString bjet = " && 1";
	TString bjet = " && (NJetsBTagwithSF_singleLepCalc >=1)";

	//ttbar - SR cut --> CHECK!!
// 	TString SR_cut = "1 && (AllLeptonPt_PtOrdered[0] >= 30) && (AllLeptonPt_PtOrdered[1] >= 30) && (AllLeptonPt_PtOrdered[2] >= 30) && (corr_met_singleLepCalc >= 20) && (NJets_singleLepCalc >= 3) && (NJetsBTagwithSF_singleLepCalc >= 1) && MCPastTrigger_dilep == 1 && (AK4HTpMETpLepPt >= 0) && AllLeptonCount_PtOrdered == 3 && ( (MllOS_allComb[0] > 20 || MllOS_allComb[0] < 0) && (MllOS_allComb[1] > 20 || MllOS_allComb[1] < 0) && (MllOS_allComb[2] > 20 || MllOS_allComb[2] < 0) )";
	TString SR_cut = "1 && (AllLeptonPt_PtOrdered[0] >= 0) && (AllLeptonPt_PtOrdered[1] >= 0) && (AllLeptonPt_PtOrdered[2] >= 0) && (corr_met_singleLepCalc >= 20) && (NJets_singleLepCalc >= 3) && (NJetsBTagwithSF_singleLepCalc >= 1) && MCPastTrigger_dilep == 1 && isPassTrilepton == 1 && (AK4HTpMETpLepPt >= 0) && (AK4HT >= 0) && ( (MllOS_allComb[0] > 20 || MllOS_allComb[0] < 0) && (MllOS_allComb[1] > 20 || MllOS_allComb[1] < 0) && (MllOS_allComb[2] > 20 || MllOS_allComb[2] < 0) && (MllOS_allComb[3] > 20 || MllOS_allComb[3] < 0) && (MllOS_allComb[4] > 20 || MllOS_allComb[4] < 0) && (MllOS_allComb[5] > 20 || MllOS_allComb[5] < 0) && (MllOS_allComb[6] > 20 || MllOS_allComb[6] < 0) && (MllOS_allComb[7] > 20 || MllOS_allComb[7] < 0) && (MllOS_allComb[8] > 20 || MllOS_allComb[8] < 0) && (MllOS_allComb[9] > 20 || MllOS_allComb[9] < 0) && (MllOS_allComb[10] > 20 || MllOS_allComb[10] < 0) && (MllOS_allComb[11] > 20 || MllOS_allComb[11] < 0) && (MllOS_allComb[12] > 20 || MllOS_allComb[12] < 0) && (MllOS_allComb[13] > 20 || MllOS_allComb[13] < 0) && (MllOS_allComb[14] > 20 || MllOS_allComb[14] < 0) )";

	TString SFs = "( TrigEffWeight * pileupWeight * 1 * isoSF * lepIdSF * EGammaGsfSF * MuTrkSF * MCWeight_singleLepCalc/abs(MCWeight_singleLepCalc) * 0.083762754031) ";
// 	TString SFs = "2 ";


	cout << "" << endl;	
	cout << "" << endl;	
	cout << "-------SR cuts-------"<< endl;	
	cout << SR_cut << endl;	
	cout << "" << endl;	
	cout << "" << endl;	
	cout << "-------SF--------" << endl;	
	cout << SFs << endl;	
	cout << "" << endl;	
	cout << "" << endl;	
	
	TString isTTT = " && isTTT"; 
	TString isTT = " && isTT"; 
	TString isTLT = " && isTLT"; 
	TString isLTT = " && isLTT"; 

	TString isTLL = " && isTLL"; 
	TString isLLL = " && isLLL"; 
	
	TString isEEE = " && isEEE";
	TString isEEM = " && isEEM";
	TString isEMM = " && isEMM";
	TString isMMM = " && isMMM"; 

	TString isEEM_ = " && isEEM_";
	TString isEME_ = " && isEME_";
	TString isMEE_ = " && isMEE_";
	TString isEMM_ = " && isEMM_";
	TString isMEM_ = " && isMEM_";
	TString isMME_ = " && isMME_";


	TString isPPP = " && ( ( AllLeptonIsPrompt_PtOrdered[0]==1 && AllLeptonIsPrompt_PtOrdered[1]==1 && AllLeptonIsPrompt_PtOrdered[2]==1 ) )";
	
	TString isPPF = " && ( AllLeptonIsPrompt_PtOrdered[0]==1 && AllLeptonIsPrompt_PtOrdered[1]==1 && AllLeptonIsPrompt_PtOrdered[2]==0 ) ";
	TString isPFP = " && ( AllLeptonIsPrompt_PtOrdered[0]==1 && AllLeptonIsPrompt_PtOrdered[1]==0 && AllLeptonIsPrompt_PtOrdered[2]==1 ) ";
	TString isFPP = " && ( AllLeptonIsPrompt_PtOrdered[0]==0 && AllLeptonIsPrompt_PtOrdered[1]==1 && AllLeptonIsPrompt_PtOrdered[2]==1 ) ";

	TString isPFF = " && ( AllLeptonIsPrompt_PtOrdered[0]==1 && AllLeptonIsPrompt_PtOrdered[1]==0 && AllLeptonIsPrompt_PtOrdered[2]==0 ) ";
	TString isFPF = " && ( AllLeptonIsPrompt_PtOrdered[0]==0 && AllLeptonIsPrompt_PtOrdered[1]==1 && AllLeptonIsPrompt_PtOrdered[2]==0 ) ";
	TString isFFP = " && ( AllLeptonIsPrompt_PtOrdered[0]==0 && AllLeptonIsPrompt_PtOrdered[1]==0 && AllLeptonIsPrompt_PtOrdered[2]==1 ) ";

	TString isFFF = " && ( AllLeptonIsPrompt_PtOrdered[0]==0 && AllLeptonIsPrompt_PtOrdered[1]==0 && AllLeptonIsPrompt_PtOrdered[2]==0 )  ";

	//
	
	TString isTTT_ = " && ( ( AllLeptonIsTight_PtOrdered[0]==1 && AllLeptonIsTight_PtOrdered[1]==1 && AllLeptonIsTight_PtOrdered[2]==1 ) )";
	
	TString isTT_ = " && ( AllLeptonIsTight_PtOrdered[0]==1 && AllLeptonIsTight_PtOrdered[1]==1 && AllLeptonIsTight_PtOrdered[2]==0 ) ";
	TString isTLT_ = " && ( AllLeptonIsTight_PtOrdered[0]==1 && AllLeptonIsTight_PtOrdered[1]==0 && AllLeptonIsTight_PtOrdered[2]==1 ) ";
	TString isLTT_ = " && ( AllLeptonIsTight_PtOrdered[0]==0 && AllLeptonIsTight_PtOrdered[1]==1 && AllLeptonIsTight_PtOrdered[2]==1 ) ";

	TString isTLL_ = " && ( AllLeptonIsTight_PtOrdered[0]==1 && AllLeptonIsTight_PtOrdered[1]==0 && AllLeptonIsTight_PtOrdered[2]==0 ) ";
	TString isLTL_ = " && ( AllLeptonIsTight_PtOrdered[0]==0 && AllLeptonIsTight_PtOrdered[1]==1 && AllLeptonIsTight_PtOrdered[2]==0 ) ";
	TString isLLT_ = " && ( AllLeptonIsTight_PtOrdered[0]==0 && AllLeptonIsTight_PtOrdered[1]==0 && AllLeptonIsTight_PtOrdered[2]==1 ) ";

	TString isLLL_ = " && ( AllLeptonIsTight_PtOrdered[0]==0 && AllLeptonIsTight_PtOrdered[1]==0 && AllLeptonIsTight_PtOrdered[2]==0 )  ";

	//
	
	TString isPPF_isTT = " && AllLeptonIsTight_PtOrdered[0]==1 && AllLeptonIsTight_PtOrdered[1]==1 ";

	//

	TString isPPF_isNotMatched = " && ( AllLeptonIsMatched_PtOrdered[2]==0 ) ";
	TString isPFP_isNotMatched = " && ( AllLeptonIsMatched_PtOrdered[1]==0 ) " ;
	TString isFPP_isNotMatched = " && ( AllLeptonIsMatched_PtOrdered[0]==0 ) ";

	TString isPPF_isFromB = " && ( AllLeptonIsMatched_PtOrdered[2]==1 && AllLeptonIsFromB_PtOrdered[2]==1 )  ";
	TString isPFP_isFromB = " && ( AllLeptonIsMatched_PtOrdered[1]==1 && AllLeptonIsFromB_PtOrdered[1]==1 )  " ;
	TString isFPP_isFromB = " && ( AllLeptonIsMatched_PtOrdered[0]==1 && AllLeptonIsFromB_PtOrdered[0]==1 ) ";

	TString isPPF_isFromC = " && ( AllLeptonIsMatched_PtOrdered[2]==1 && AllLeptonIsFromB_PtOrdered[2]==0 && AllLeptonIsFromC_PtOrdered[2]==1 )  ";
	TString isPFP_isFromC = " && ( AllLeptonIsMatched_PtOrdered[1]==1 && AllLeptonIsFromB_PtOrdered[1]==0 && AllLeptonIsFromC_PtOrdered[1]==1 )  " ;
	TString isFPP_isFromC = " && ( AllLeptonIsMatched_PtOrdered[0]==1 && AllLeptonIsFromB_PtOrdered[0]==0 && AllLeptonIsFromC_PtOrdered[0]==1 ) ";

	TString isPPF_isFromPh = " && (  AllLeptonIsMatched_PtOrdered[2]==1 && AllLeptonIsFromB_PtOrdered[2]==0 && AllLeptonIsFromC_PtOrdered[2]==0 && AllLeptonIsFromPh_PtOrdered[2]==1 )  ";
	TString isPFP_isFromPh = " && (  AllLeptonIsMatched_PtOrdered[1]==1 && AllLeptonIsFromB_PtOrdered[1]==0 && AllLeptonIsFromC_PtOrdered[1]==0 && AllLeptonIsFromPh_PtOrdered[1]==1 )  " ;
	TString isFPP_isFromPh = " && (  AllLeptonIsMatched_PtOrdered[0]==1 && AllLeptonIsFromB_PtOrdered[0]==0 && AllLeptonIsFromC_PtOrdered[0]==0 && AllLeptonIsFromPh_PtOrdered[0]==1 ) ";

	TString isPPF_isFromL = " && ( AllLeptonIsMatched_PtOrdered[2]==1 && AllLeptonIsFromB_PtOrdered[2]==0 && AllLeptonIsFromC_PtOrdered[2]==0 && AllLeptonIsFromPh_PtOrdered[2]==0 && AllLeptonIsFromL_PtOrdered[2]==1 )  ";
	TString isPFP_isFromL = " && ( AllLeptonIsMatched_PtOrdered[1]==1 && AllLeptonIsFromB_PtOrdered[1]==0 && AllLeptonIsFromC_PtOrdered[1]==0 && AllLeptonIsFromPh_PtOrdered[1]==0 && AllLeptonIsFromL_PtOrdered[1]==1)  " ;
	TString isFPP_isFromL = " && ( AllLeptonIsMatched_PtOrdered[0]==1 && AllLeptonIsFromB_PtOrdered[0]==0 && AllLeptonIsFromC_PtOrdered[0]==0 && AllLeptonIsFromPh_PtOrdered[0]==0 && AllLeptonIsFromL_PtOrdered[0]==1) ";

	TString isPPF_isFromElse = " && (  AllLeptonIsMatched_PtOrdered[2]==1 && AllLeptonIsFromB_PtOrdered[2]==0 && AllLeptonIsFromC_PtOrdered[2]==0 && AllLeptonIsFromPh_PtOrdered[2]==0 && AllLeptonIsFromL_PtOrdered[2]==0 )  ";
	TString isPFP_isFromElse = " && (  AllLeptonIsMatched_PtOrdered[1]==1 && AllLeptonIsFromB_PtOrdered[1]==0 && AllLeptonIsFromC_PtOrdered[1]==0 && AllLeptonIsFromPh_PtOrdered[1]==0 && AllLeptonIsFromL_PtOrdered[1]==0 )  " ;
	TString isFPP_isFromElse = " && (  AllLeptonIsMatched_PtOrdered[0]==1 && AllLeptonIsFromB_PtOrdered[0]==0 && AllLeptonIsFromC_PtOrdered[0]==0 && AllLeptonIsFromPh_PtOrdered[0]==0 && AllLeptonIsFromL_PtOrdered[0]==0 ) ";
	
	
	//
	
	TH1D *h_EEE_ttt = new TH1D("h_EEE_ttt","h_EEE_ttt",21,0,2000);
	TH1D *h_EEM_ttt = new TH1D("h_EEM_ttt","h_EEM_ttt",21,0,2000);
	TH1D *h_EMM_ttt = new TH1D("h_EMM_ttt","h_EMM_ttt",21,0,2000);
	TH1D *h_MMM_ttt = new TH1D("h_MMM_ttt","h_MMM_ttt",21,0,2000);

	//===========EEE==============
	
	std::cout<<"Processing EEE ..." << std::endl;
	
	std::cout<<"Processing EEE 1 fake t/l ..." << std::endl;

	EEE_ttt_unw = t->Draw(observ+">>h_EEE_ttt",SFs+" * ( "+SR_cut+isEEE+isTTT+" )","GOFF");
	EEE_ttt = h_EEE_ttt->Integral();

	EEE_ppf_ttt = t->Draw(observ,SR_cut+isEEE+" && ( isPPF || isPFP || isFPP ) && isTTT " );
	EEE_ppf_tt  = t->Draw(observ,SR_cut+isEEE+isPPF+isPPF_isTT );

	std::cout<<"Processing EEE 1 fake t/l sources ..." << std::endl;

		//

		EEE_ppf_ttt_isNotMatched = t->Draw(observ,SR_cut+isEEE+" && ( isPPF && isTTT)"+isPPF_isNotMatched);
		EEE_pfp_ttt_isNotMatched = t->Draw(observ,SR_cut+isEEE+" && ( isPFP && isTTT)"+isPFP_isNotMatched );
		EEE_fpp_ttt_isNotMatched = t->Draw(observ,SR_cut+isEEE+" && ( isFPP && isTTT)"+isFPP_isNotMatched );

		EEE_ppf_ttt_isFromB = t->Draw(observ,SR_cut+isEEE+" && ( isPPF && isTTT)"+isPPF_isFromB);
		EEE_pfp_ttt_isFromB = t->Draw(observ,SR_cut+isEEE+" && ( isPFP && isTTT)"+isPFP_isFromB );
		EEE_fpp_ttt_isFromB = t->Draw(observ,SR_cut+isEEE+" && ( isFPP && isTTT)"+isFPP_isFromB );

		EEE_ppf_ttt_isFromC = t->Draw(observ,SR_cut+isEEE+" && ( isPPF && isTTT)"+isPPF_isFromC);
		EEE_pfp_ttt_isFromC = t->Draw(observ,SR_cut+isEEE+" && ( isPFP && isTTT)"+isPFP_isFromC );
		EEE_fpp_ttt_isFromC = t->Draw(observ,SR_cut+isEEE+" && ( isFPP && isTTT)"+isFPP_isFromC );

		EEE_ppf_ttt_isFromElse = t->Draw(observ,SR_cut+isEEE+" && ( isPPF && isTTT)"+isPPF_isFromElse);
		EEE_pfp_ttt_isFromElse = t->Draw(observ,SR_cut+isEEE+" && ( isPFP && isTTT)"+isPFP_isFromElse );
		EEE_fpp_ttt_isFromElse = t->Draw(observ,SR_cut+isEEE+" && ( isFPP && isTTT)"+isFPP_isFromElse );

		EEE_ppf_ttt_isFromPh = t->Draw(observ,SR_cut+isEEE+" && ( isPPF && isTTT)"+isPPF_isFromPh);
		EEE_pfp_ttt_isFromPh = t->Draw(observ,SR_cut+isEEE+" && ( isPFP && isTTT)"+isPFP_isFromPh );
		EEE_fpp_ttt_isFromPh = t->Draw(observ,SR_cut+isEEE+" && ( isFPP && isTTT)"+isFPP_isFromPh );

		EEE_ppf_ttt_isFromL = t->Draw(observ,SR_cut+isEEE+" && ( isPPF && isTTT)"+isPPF_isFromL);
		EEE_pfp_ttt_isFromL = t->Draw(observ,SR_cut+isEEE+" && ( isPFP && isTTT)"+isPFP_isFromL );
		EEE_fpp_ttt_isFromL = t->Draw(observ,SR_cut+isEEE+" && ( isFPP && isTTT)"+isFPP_isFromL );

	//
	cout << " ========= EEE ========= " << endl;
	cout << "       IsTTT		: " << EEE_ttt_unw << " ( weighted: "<< EEE_ttt << " ) "<<endl;
	cout << "	--1 fake /2 prompts:   "<< endl;
	cout << "       IsTTT f(T) 	: " << EEE_ppf_ttt << endl;
	if(printSource){
	cout << "               Is(not)Matched   : " << EEE_ppf_ttt_isNotMatched+EEE_pfp_ttt_isNotMatched+EEE_fpp_ttt_isNotMatched << endl;
	cout << "               IsFromB          : " << EEE_ppf_ttt_isFromB+EEE_pfp_ttt_isFromB+EEE_fpp_ttt_isFromB << endl;
	cout << "               IsFromC          : " << EEE_ppf_ttt_isFromC+EEE_pfp_ttt_isFromC+EEE_fpp_ttt_isFromC << endl;
	cout << "               IsFromPh         : " << EEE_ppf_ttt_isFromPh+EEE_pfp_ttt_isFromPh+EEE_fpp_ttt_isFromPh << endl;
	cout << "               IsFromL          : " << EEE_ppf_ttt_isFromL+EEE_pfp_ttt_isFromL+EEE_fpp_ttt_isFromL << endl;
	cout << "               IsFromElse         : " << EEE_ppf_ttt_isFromElse+EEE_pfp_ttt_isFromElse+EEE_fpp_ttt_isFromElse << endl;
	}
	float eee_fT = EEE_ppf_ttt*1.0;
	float eee_f = (EEE_ppf_tt*1.0);//+EEE_pfp_tlt+EEE_fpp_ltt )*1.0;
	cout << "       		eee ppf ttt observed  : " << endl;
	cout << "       			All sources : " << eee_fT << " +- "<< sqrt(eee_fT) << endl;;
	float EEE_fT_isNotMatched = EEE_ppf_ttt_isNotMatched+EEE_pfp_ttt_isNotMatched+EEE_fpp_ttt_isNotMatched*1.0;
	cout << "       			_isNotMatched	: " << EEE_fT_isNotMatched << " +- "<< sqrt(EEE_fT_isNotMatched) << endl;;
	float EEE_fT_isFromB = EEE_ppf_ttt_isFromB+EEE_pfp_ttt_isFromB+EEE_fpp_ttt_isFromB*1.0;
	cout << "       			_isFromB	: " << EEE_fT_isFromB << " +- "<< sqrt(EEE_fT_isFromB) << endl;;
	float EEE_fT_isFromC = EEE_ppf_ttt_isFromC+EEE_pfp_ttt_isFromC+EEE_fpp_ttt_isFromC*1.0;
	cout << "       			_isFromC	: " << EEE_fT_isFromC << " +- "<< sqrt(EEE_fT_isFromC) << endl;;
	float EEE_fT_isFromPh = EEE_ppf_ttt_isFromPh+EEE_pfp_ttt_isFromPh+EEE_fpp_ttt_isFromPh*1.0;
	cout << "       			_isFromPh	: " << EEE_fT_isFromPh << " +- "<< sqrt(EEE_fT_isFromPh) << "( " << EEE_fT_isFromPh/eee_fT *100. << "% )" << endl;;
	float EEE_fT_isFromL = EEE_ppf_ttt_isFromL+EEE_pfp_ttt_isFromL+EEE_fpp_ttt_isFromL*1.0;
	cout << "       			_isFromL	: " << EEE_fT_isFromL << " +- "<< sqrt(EEE_fT_isFromL) << endl;;
	float EEE_fT_isFromElse = EEE_ppf_ttt_isFromElse+EEE_pfp_ttt_isFromElse+EEE_fpp_ttt_isFromElse*1.0;
	cout << "       			_isFromElse	: " << EEE_fT_isFromElse << " +- "<< sqrt(EEE_fT_isFromElse) << endl;;
// if(PrintMixedChannels){
	//===========EEM==============
	std::cout<<"Processing EEM ..." << std::endl;

	EEM_ttt_unw = t->Draw(observ+">>h_EEM_ttt",SFs+" * ( "+SR_cut+isEEM+isTTT+" )","GOFF");
	EEM_ttt = h_EEM_ttt->Integral();

	//EEM - 2prompts
	std::cout<<"Processing EEM 1 fake t/l..." << std::endl;
	EEM_ppf_tt = t->Draw(observ,SR_cut+isEEM_+isPPF+isTT);

	EEM_ppf_ttt = t->Draw(observ,SR_cut+isEEM_+isPPF+isTTT);
	EEM_pfp_ttt = t->Draw(observ,SR_cut+isEEM_+isPFP+isTTT);
	EEM_fpp_ttt = t->Draw(observ,SR_cut+isEEM_+isFPP+isTTT);

	std::cout<<"Processing EEM 1 fake t/l sources..." << std::endl;
		//sources - isMatched
		EEM_ppf_tt_isNotMatched = t->Draw(observ,SR_cut+isEEM_+isPPF+isPPF_isTT+isPPF_isNotMatched);

		EEM_ppf_ttt_isNotMatched = t->Draw(observ,SR_cut+isEEM_+isPPF+isTTT+isPPF_isNotMatched);
		EEM_pfp_ttt_isNotMatched = t->Draw(observ,SR_cut+isEEM_+isPFP+isTTT+isPFP_isNotMatched);
		EEM_fpp_ttt_isNotMatched = t->Draw(observ,SR_cut+isEEM_+isFPP+isTTT+isFPP_isNotMatched);

		//sources - isFromB
		EEM_ppf_tt_isFromB = t->Draw(observ,SR_cut+isEEM_+isPPF+isPPF_isTT+isPPF_isFromB);

		EEM_ppf_ttt_isFromB = t->Draw(observ,SR_cut+isEEM_+isPPF+isTTT+isPPF_isFromB);
		EEM_pfp_ttt_isFromB = t->Draw(observ,SR_cut+isEEM_+isPFP+isTTT+isPFP_isFromB);
		EEM_fpp_ttt_isFromB = t->Draw(observ,SR_cut+isEEM_+isFPP+isTTT+isFPP_isFromB);

		//sources - isFromB
		EEM_ppf_tt_isFromB = t->Draw(observ,SR_cut+isEEM_+isPPF+isPPF_isTT+isPPF_isFromB);

		EEM_ppf_ttt_isFromB = t->Draw(observ,SR_cut+isEEM_+isPPF+isTTT+isPPF_isFromB);
		EEM_pfp_ttt_isFromB = t->Draw(observ,SR_cut+isEEM_+isPFP+isTTT+isPFP_isFromB);
		EEM_fpp_ttt_isFromB = t->Draw(observ,SR_cut+isEEM_+isFPP+isTTT+isFPP_isFromB);

		//sources - isFromC
		EEM_ppf_tt_isFromC = t->Draw(observ,SR_cut+isEEM_+isPPF+isPPF_isTT+isPPF_isFromC);

		EEM_ppf_ttt_isFromC = t->Draw(observ,SR_cut+isEEM_+isPPF+isTTT+isPPF_isFromC);
		EEM_pfp_ttt_isFromC = t->Draw(observ,SR_cut+isEEM_+isPFP+isTTT+isPFP_isFromC);
		EEM_fpp_ttt_isFromC = t->Draw(observ,SR_cut+isEEM_+isFPP+isTTT+isFPP_isFromC);

		//sources - isFromElse
		EEM_ppf_tt_isFromElse = t->Draw(observ,SR_cut+isEEM_+isPPF+isPPF_isTT+isPPF_isFromElse);

		EEM_ppf_ttt_isFromElse = t->Draw(observ,SR_cut+isEEM_+isPPF+isTTT+isPPF_isFromElse);
		EEM_pfp_ttt_isFromElse = t->Draw(observ,SR_cut+isEEM_+isPFP+isTTT+isPFP_isFromElse);
		EEM_fpp_ttt_isFromElse = t->Draw(observ,SR_cut+isEEM_+isFPP+isTTT+isFPP_isFromElse);

		//sources - isFromPh
		EEM_ppf_tt_isFromPh = t->Draw(observ,SR_cut+isEEM_+isPPF+isPPF_isTT+isPPF_isFromPh);

		EEM_ppf_ttt_isFromPh = t->Draw(observ,SR_cut+isEEM_+isPPF+isTTT+isPPF_isFromPh);
		EEM_pfp_ttt_isFromPh = t->Draw(observ,SR_cut+isEEM_+isPFP+isTTT+isPFP_isFromPh);
		EEM_fpp_ttt_isFromPh = t->Draw(observ,SR_cut+isEEM_+isFPP+isTTT+isFPP_isFromPh);

		//sources - isFromL
		EEM_ppf_tt_isFromL = t->Draw(observ,SR_cut+isEEM_+isPPF+isPPF_isTT+isPPF_isFromL);

		EEM_ppf_ttt_isFromL = t->Draw(observ,SR_cut+isEEM_+isPPF+isTTT+isPPF_isFromL);
		EEM_pfp_ttt_isFromL = t->Draw(observ,SR_cut+isEEM_+isPFP+isTTT+isPFP_isFromL);
		EEM_fpp_ttt_isFromL = t->Draw(observ,SR_cut+isEEM_+isFPP+isTTT+isFPP_isFromL);

	//EME - 2prompts
	std::cout<<"Processing EME 1 fake t/l ..." << std::endl;
	EME_ppf_tt = t->Draw(observ,SR_cut+isEME_+isPPF+isPPF_isTT);
	EME_pfp_tlt = t->Draw(observ,SR_cut+isEME_+isPFP+isTLT);
	EME_fpp_ltt = t->Draw(observ,SR_cut+isEME_+isFPP+isLTT);

	EME_ppf_ttt = t->Draw(observ,SR_cut+isEME_+isPPF+isTTT);
	EME_pfp_ttt = t->Draw(observ,SR_cut+isEME_+isPFP+isTTT);
	EME_fpp_ttt = t->Draw(observ,SR_cut+isEME_+isFPP+isTTT);

	std::cout<<"Processing EME 1 fake t/l sources ..." << std::endl;
		//sources - isMatched
		EME_ppf_tt_isNotMatched = t->Draw(observ,SR_cut+isEME_+isPPF+isPPF_isTT+isPPF_isNotMatched);

		EME_ppf_ttt_isNotMatched = t->Draw(observ,SR_cut+isEME_+isPPF+isTTT+isPPF_isNotMatched);
		EME_pfp_ttt_isNotMatched = t->Draw(observ,SR_cut+isEME_+isPFP+isTTT+isPFP_isNotMatched);
		EME_fpp_ttt_isNotMatched = t->Draw(observ,SR_cut+isEME_+isFPP+isTTT+isFPP_isNotMatched);

		//sources - isFromB
		EME_ppf_tt_isFromB = t->Draw(observ,SR_cut+isEME_+isPPF+isPPF_isTT+isPPF_isFromB);

		EME_ppf_ttt_isFromB = t->Draw(observ,SR_cut+isEME_+isPPF+isTTT+isPPF_isFromB);
		EME_pfp_ttt_isFromB = t->Draw(observ,SR_cut+isEME_+isPFP+isTTT+isPFP_isFromB);
		EME_fpp_ttt_isFromB = t->Draw(observ,SR_cut+isEME_+isFPP+isTTT+isFPP_isFromB);

		//sources - isFromC
		EME_ppf_tt_isFromC = t->Draw(observ,SR_cut+isEME_+isPPF+isPPF_isTT+isPPF_isFromC);

		EME_ppf_ttt_isFromC = t->Draw(observ,SR_cut+isEME_+isPPF+isTTT+isPPF_isFromC);
		EME_pfp_ttt_isFromC = t->Draw(observ,SR_cut+isEME_+isPFP+isTTT+isPFP_isFromC);
		EME_fpp_ttt_isFromC = t->Draw(observ,SR_cut+isEME_+isFPP+isTTT+isFPP_isFromC);

		//sources - isFromElse
		EME_ppf_tt_isFromElse = t->Draw(observ,SR_cut+isEME_+isPPF+isPPF_isTT+isPPF_isFromElse);

		EME_ppf_ttt_isFromElse = t->Draw(observ,SR_cut+isEME_+isPPF+isTTT+isPPF_isFromElse);
		EME_pfp_ttt_isFromElse = t->Draw(observ,SR_cut+isEME_+isPFP+isTTT+isPFP_isFromElse);
		EME_fpp_ttt_isFromElse = t->Draw(observ,SR_cut+isEME_+isFPP+isTTT+isFPP_isFromElse);

		//sources - isFromPh
		EME_ppf_tt_isFromPh = t->Draw(observ,SR_cut+isEME_+isPPF+isPPF_isTT+isPPF_isFromPh);

		EME_ppf_ttt_isFromPh = t->Draw(observ,SR_cut+isEME_+isPPF+isTTT+isPPF_isFromPh);
		EME_pfp_ttt_isFromPh = t->Draw(observ,SR_cut+isEME_+isPFP+isTTT+isPFP_isFromPh);
		EME_fpp_ttt_isFromPh = t->Draw(observ,SR_cut+isEME_+isFPP+isTTT+isFPP_isFromPh);

		//sources - isFromL
		EME_ppf_tt_isFromL = t->Draw(observ,SR_cut+isEME_+isPPF+isPPF_isTT+isPPF_isFromL);

		EME_ppf_ttt_isFromL = t->Draw(observ,SR_cut+isEME_+isPPF+isTTT+isPPF_isFromL);
		EME_pfp_ttt_isFromL = t->Draw(observ,SR_cut+isEME_+isPFP+isTTT+isPFP_isFromL);
		EME_fpp_ttt_isFromL = t->Draw(observ,SR_cut+isEME_+isFPP+isTTT+isFPP_isFromL);


	//MEE - 2prompts
	std::cout<<"Processing MEE 1 fake t/l ..." << std::endl;
	MEE_ppf_tt = t->Draw(observ,SR_cut+isMEE_+isPPF+isPPF_isTT);

	MEE_ppf_ttt = t->Draw(observ,SR_cut+isMEE_+isPPF+isTTT);
	MEE_pfp_ttt = t->Draw(observ,SR_cut+isMEE_+isPFP+isTTT);
	MEE_fpp_ttt = t->Draw(observ,SR_cut+isMEE_+isFPP+isTTT);

	std::cout<<"Processing MEE 1 fake t/l sources..." << std::endl;
		//source isMatched		
		MEE_ppf_tt_isNotMatched = t->Draw(observ,SR_cut+isMEE_+isPPF+isPPF_isTT+isPPF_isNotMatched);

		MEE_ppf_ttt_isNotMatched = t->Draw(observ,SR_cut+isMEE_+isPPF+isTTT+isPPF_isNotMatched);
		MEE_pfp_ttt_isNotMatched = t->Draw(observ,SR_cut+isMEE_+isPFP+isTTT+isPFP_isNotMatched);
		MEE_fpp_ttt_isNotMatched = t->Draw(observ,SR_cut+isMEE_+isFPP+isTTT+isFPP_isNotMatched);

		//source isFromB		
		MEE_ppf_tt_isFromB = t->Draw(observ,SR_cut+isMEE_+isPPF+isPPF_isTT+isPPF_isFromB);

		MEE_ppf_ttt_isFromB = t->Draw(observ,SR_cut+isMEE_+isPPF+isTTT+isPPF_isFromB);
		MEE_pfp_ttt_isFromB = t->Draw(observ,SR_cut+isMEE_+isPFP+isTTT+isPFP_isFromB);
		MEE_fpp_ttt_isFromB = t->Draw(observ,SR_cut+isMEE_+isFPP+isTTT+isFPP_isFromB);

		//source isFromC		
		MEE_ppf_tt_isFromC = t->Draw(observ,SR_cut+isMEE_+isPPF+isPPF_isTT+isPPF_isFromC);

		MEE_ppf_ttt_isFromC = t->Draw(observ,SR_cut+isMEE_+isPPF+isTTT+isPPF_isFromC);
		MEE_pfp_ttt_isFromC = t->Draw(observ,SR_cut+isMEE_+isPFP+isTTT+isPFP_isFromC);
		MEE_fpp_ttt_isFromC = t->Draw(observ,SR_cut+isMEE_+isFPP+isTTT+isFPP_isFromC);

		//source isFromElse		
		MEE_ppf_tt_isFromElse = t->Draw(observ,SR_cut+isMEE_+isPPF+isPPF_isTT+isPPF_isFromElse);

		MEE_ppf_ttt_isFromElse = t->Draw(observ,SR_cut+isMEE_+isPPF+isTTT+isPPF_isFromElse);
		MEE_pfp_ttt_isFromElse = t->Draw(observ,SR_cut+isMEE_+isPFP+isTTT+isPFP_isFromElse);
		MEE_fpp_ttt_isFromElse = t->Draw(observ,SR_cut+isMEE_+isFPP+isTTT+isFPP_isFromElse);

		//source isFromPh		
		MEE_ppf_tt_isFromPh = t->Draw(observ,SR_cut+isMEE_+isPPF+isPPF_isTT+isPPF_isFromPh);

		MEE_ppf_ttt_isFromPh = t->Draw(observ,SR_cut+isMEE_+isPPF+isTTT+isPPF_isFromPh);
		MEE_pfp_ttt_isFromPh = t->Draw(observ,SR_cut+isMEE_+isPFP+isTTT+isPFP_isFromPh);
		MEE_fpp_ttt_isFromPh = t->Draw(observ,SR_cut+isMEE_+isFPP+isTTT+isFPP_isFromPh);

		//source isFromL		
		MEE_ppf_tt_isFromL = t->Draw(observ,SR_cut+isMEE_+isPPF+isPPF_isTT+isPPF_isFromL);

		MEE_ppf_ttt_isFromL = t->Draw(observ,SR_cut+isMEE_+isPPF+isTTT+isPPF_isFromL);
		MEE_pfp_ttt_isFromL = t->Draw(observ,SR_cut+isMEE_+isPFP+isTTT+isPFP_isFromL);
		MEE_fpp_ttt_isFromL = t->Draw(observ,SR_cut+isMEE_+isFPP+isTTT+isFPP_isFromL);
	

	cout << " ========= EEM ========= " << endl;
	cout << "       TTT		: " << EEM_ttt_unw << " ( weighted: "<< EEM_ttt << " ) "<<endl;
	cout << "	--1 fake-- :  "<< endl;
	cout << "	f(T):   "<< endl;
	cout << "       EE(M) PPF TTT (fake mu) : " << EEM_ppf_ttt << endl;
	if(printSource){
	cout << "               Is(not)Matched   : " << EEM_ppf_ttt_isNotMatched << endl;
	cout << "               IsFromB          : " << EEM_ppf_ttt_isFromB << endl;
	cout << "               IsFromC          : " << EEM_ppf_ttt_isFromC << endl;
	cout << "               IsFromPh         : " << EEM_ppf_ttt_isFromPh << endl;
	cout << "               IsFromL          : " << EEM_ppf_ttt_isFromL<< endl;
	cout << "               IsFromElse         : " << EEM_ppf_ttt_isFromElse << endl;
	}
	cout << "       E(E)M PFP TTT (fake el) : " << EEM_pfp_ttt << endl;
	if(printSource){
	cout << "               Is(not)Matched   : " << EEM_pfp_ttt_isNotMatched << endl;
	cout << "               IsFromB          : " << EEM_pfp_ttt_isFromB << endl;
	cout << "               IsFromC          : " << EEM_pfp_ttt_isFromC << endl;
	cout << "               IsFromPh         : " << EEM_pfp_ttt_isFromPh << endl;
	cout << "               IsFromL          : " << EEM_pfp_ttt_isFromL<< endl;
	cout << "               IsFromElse         : " << EEM_pfp_ttt_isFromElse << endl;
	}
	cout << "       (E)EM FPP TTT (fake el) : " << EEM_fpp_ttt << endl;
	if(printSource){
	cout << "               Is(not)Matched   : " << EEM_fpp_ttt_isNotMatched << endl;
	cout << "               IsFromB          : " << EEM_fpp_ttt_isFromB << endl;
	cout << "               IsFromC          : " << EEM_fpp_ttt_isFromC << endl;
	cout << "               IsFromPh         : " << EEM_fpp_ttt_isFromPh << endl;
	cout << "               IsFromL          : " << EEM_fpp_ttt_isFromL<< endl;
	cout << "               IsFromElse         : " << EEM_fpp_ttt_isFromElse << endl;
	}
	cout << "-" << endl;
	cout << "       EM(E) PPF TTT (fake el) : " << EME_ppf_ttt << endl;
	if(printSource){
	cout << "               Is(not)Matched   : " << EME_ppf_ttt_isNotMatched << endl;
	cout << "               IsFromB          : " << EME_ppf_ttt_isFromB << endl;
	cout << "               IsFromC          : " << EME_ppf_ttt_isFromC << endl;
	cout << "               IsFromPh         : " << EME_ppf_ttt_isFromPh << endl;
	cout << "               IsFromL          : " << EME_ppf_ttt_isFromL<< endl;
	cout << "               IsFromElse         : " << EME_ppf_ttt_isFromElse << endl;
	}
	cout << "       E(M)E PFP TTT (fake mu) : " << EME_pfp_ttt << endl;
	if(printSource){
	cout << "               Is(not)Matched   : " << EME_pfp_ttt_isNotMatched << endl;
	cout << "               IsFromB          : " << EME_pfp_ttt_isFromB << endl;
	cout << "               IsFromC          : " << EME_pfp_ttt_isFromC << endl;
	cout << "               IsFromPh         : " << EME_pfp_ttt_isFromPh << endl;
	cout << "               IsFromL          : " << EME_pfp_ttt_isFromL<< endl;
	cout << "               IsFromElse         : " << EME_pfp_ttt_isFromElse << endl;
	}
	cout << "       (E)ME FPP TTT (fake el) : " << EME_fpp_ttt << endl;
	if(printSource){
	cout << "               Is(not)Matched   : " << EME_fpp_ttt_isNotMatched << endl;
	cout << "               IsFromB          : " << EME_fpp_ttt_isFromB << endl;
	cout << "               IsFromC          : " << EME_fpp_ttt_isFromC << endl;
	cout << "               IsFromPh         : " << EME_fpp_ttt_isFromPh << endl;
	cout << "               IsFromL          : " << EME_fpp_ttt_isFromL<< endl;
	cout << "               IsFromElse         : " << EME_fpp_ttt_isFromElse << endl;
	}
	cout << "-" << endl;
	cout << "       ME(E) PPF TTT (fake el) : " << MEE_ppf_ttt << endl;
	if(printSource){
	cout << "               Is(not)Matched   : " << MEE_ppf_ttt_isNotMatched << endl;
	cout << "               IsFromB          : " << MEE_ppf_ttt_isFromB << endl;
	cout << "               IsFromC          : " << MEE_ppf_ttt_isFromC << endl;
	cout << "               IsFromPh         : " << MEE_ppf_ttt_isFromPh << endl;
	cout << "               IsFromL          : " << MEE_ppf_ttt_isFromL<< endl;
	cout << "               IsFromElse         : " << MEE_ppf_ttt_isFromElse << endl;
	}
	cout << "       M(E)E PFP TTT (fake el) : " << MEE_pfp_ttt << endl;
	if(printSource){
	cout << "               Is(not)Matched   : " << MEE_pfp_ttt_isNotMatched << endl;
	cout << "               IsFromB          : " << MEE_pfp_ttt_isFromB << endl;
	cout << "               IsFromC          : " << MEE_pfp_ttt_isFromC << endl;
	cout << "               IsFromPh         : " << MEE_pfp_ttt_isFromPh << endl;
	cout << "               IsFromL          : " << MEE_pfp_ttt_isFromL<< endl;
	cout << "               IsFromElse         : " << MEE_pfp_ttt_isFromElse << endl;
	}
	cout << "       (M)EE FPP TTT (fake mu) : " << MEE_fpp_ttt << endl;
	if(printSource){
	cout << "               Is(not)Matched   : " << MEE_fpp_ttt_isNotMatched << endl;
	cout << "               IsFromB          : " << MEE_fpp_ttt_isFromB << endl;
	cout << "               IsFromC          : " << MEE_fpp_ttt_isFromC << endl;
	cout << "               IsFromPh         : " << MEE_fpp_ttt_isFromPh << endl;
	cout << "               IsFromL          : " << MEE_fpp_ttt_isFromL<< endl;
	cout << "               IsFromElse         : " << MEE_fpp_ttt_isFromElse << endl;
	}
	cout << "" << endl;
	cout << "       ---------------------  " << endl;
	float eem_e_fT = EEM_pfp_ttt+EEM_fpp_ttt+EME_ppf_ttt+EME_fpp_ttt+MEE_ppf_ttt+MEE_pfp_ttt;

		float eem_e_fT_isNotMatched = EEM_pfp_ttt_isNotMatched+EEM_fpp_ttt_isNotMatched+EME_ppf_ttt_isNotMatched+EME_fpp_ttt_isNotMatched+MEE_ppf_ttt_isNotMatched+MEE_pfp_ttt_isNotMatched;
		float eem_e_fT_isFromB = EEM_pfp_ttt_isFromB+EEM_fpp_ttt_isFromB+EME_ppf_ttt_isFromB+EME_fpp_ttt_isFromB+MEE_ppf_ttt_isFromB+MEE_pfp_ttt_isFromB;
		float eem_e_fT_isFromC = EEM_pfp_ttt_isFromC+EEM_fpp_ttt_isFromC+EME_ppf_ttt_isFromC+EME_fpp_ttt_isFromC+MEE_ppf_ttt_isFromC+MEE_pfp_ttt_isFromC;
		float eem_e_fT_isFromElse = EEM_pfp_ttt_isFromElse+EEM_fpp_ttt_isFromElse+EME_ppf_ttt_isFromElse+EME_fpp_ttt_isFromElse+MEE_ppf_ttt_isFromElse+MEE_pfp_ttt_isFromElse;
		float eem_e_fT_isFromPh = EEM_pfp_ttt_isFromPh+EEM_fpp_ttt_isFromPh+EME_ppf_ttt_isFromPh+EME_fpp_ttt_isFromPh+MEE_ppf_ttt_isFromPh+MEE_pfp_ttt_isFromPh;
		float eem_e_fT_isFromL = EEM_pfp_ttt_isFromL+EEM_fpp_ttt_isFromL+EME_ppf_ttt_isFromL+EME_fpp_ttt_isFromL+MEE_ppf_ttt_isFromL+MEE_pfp_ttt_isFromL;

	float eem_e_f = EME_ppf_tt+MEE_ppf_tt;

		float eem_e_f_isNotMatched = EME_ppf_tt_isNotMatched+MEE_ppf_tt_isNotMatched;
		float eem_e_f_isFromB = EME_ppf_tt_isFromB+MEE_ppf_tt_isFromB;
		float eem_e_f_isFromC = EME_ppf_tt_isFromC+MEE_ppf_tt_isFromC;
		float eem_e_f_isFromElse =EME_ppf_tt_isFromElse+MEE_ppf_tt_isFromElse;
		float eem_e_f_isFromPh =EME_ppf_tt_isFromPh+MEE_ppf_tt_isFromPh;
		float eem_e_f_isFromL = EME_ppf_tt_isFromL+MEE_ppf_tt_isFromL;

	cout << "       eem ppf(e) ttt observed : " <<endl;
	cout << "       		All sources		: " << eem_e_fT << " +/- " << sqrt(eem_e_fT) << endl;

	cout << "               Is(not)Matched	: " << eem_e_fT_isNotMatched << " +/- " << sqrt(eem_e_fT_isNotMatched) << endl;

	cout << "               IsFromB			: " << eem_e_fT_isFromB << " +/- " << sqrt(eem_e_fT_isFromB) << endl;

	cout << "               IsFromC			: " << eem_e_fT_isFromC << " +/- " << sqrt(eem_e_fT_isFromC) << endl;

	cout << "               IsFromPh		: " << eem_e_fT_isFromPh << " +/- " << sqrt(eem_e_fT_isFromPh) << "( " << eem_e_fT_isFromPh/eem_e_fT *100. << "% )" << endl;

	cout << "               IsFromL			: " << eem_e_fT_isFromL << " +/- " << sqrt(eem_e_fT_isFromL) << endl;

	cout << "               IsFromElse		: " << eem_e_fT_isFromElse << " +/- " << sqrt(eem_e_fT_isFromElse) << endl;


	float eem_m_fT = EEM_ppf_ttt+EME_pfp_ttt+MEE_fpp_ttt;

		float eem_m_fT_isNotMatched = EEM_ppf_ttt_isNotMatched+EME_pfp_ttt_isNotMatched+MEE_fpp_ttt_isNotMatched;
		float eem_m_fT_isFromB = EEM_ppf_ttt_isFromB+EME_pfp_ttt_isFromB+MEE_fpp_ttt_isFromB;
		float eem_m_fT_isFromC = EEM_ppf_ttt_isFromC+EME_pfp_ttt_isFromC+MEE_fpp_ttt_isFromC;
		float eem_m_fT_isFromPh = EEM_ppf_ttt_isFromPh+EME_pfp_ttt_isFromPh+MEE_fpp_ttt_isFromPh;
		float eem_m_fT_isFromElse = EEM_ppf_ttt_isFromElse+EME_pfp_ttt_isFromElse+MEE_fpp_ttt_isFromElse;
		float eem_m_fT_isFromL = EEM_ppf_ttt_isFromL+EME_pfp_ttt_isFromL+MEE_fpp_ttt_isFromL;

	float eem_m_f = EEM_ppf_tt;//+EME_pfp_tlt+MEE_fpp_ltt;

		float eem_m_f_isNotMatched = EEM_ppf_tt_isNotMatched;//+EME_pfp_tlt_isNotMatched+MEE_fpp_ltt_isNotMatched;
		float eem_m_f_isFromB = EEM_ppf_tt_isFromB;//+EME_pfp_tlt_isFromB+MEE_fpp_ltt_isFromB;
		float eem_m_f_isFromC = EEM_ppf_tt_isFromC;//+EME_pfp_tlt_isFromC+MEE_fpp_ltt_isFromC;
		float eem_m_f_isFromPh = EEM_ppf_tt_isFromPh;//+EME_pfp_tlt_isFromPh+MEE_fpp_ltt_isFromPh;
		float eem_m_f_isFromElse = EEM_ppf_tt_isFromElse;//+EME_pfp_tlt_isFromElse+MEE_fpp_ltt_isFromElse;
		float eem_m_f_isFromL = EEM_ppf_tt_isFromL;//+EME_pfp_tlt_isFromL+MEE_fpp_ltt_isFromL;

	cout << "       eem ppf(m) ttt observed : " <<endl;
	cout << "       		All sources		: " << eem_m_fT << " +/- " << sqrt(eem_m_fT) << endl;

	cout << "               Is(not)Matched	: " << eem_m_fT_isNotMatched << " +/- " << sqrt(eem_m_fT_isNotMatched) << endl;

	cout << "               IsFromB			: " << eem_m_fT_isFromB << " +/- " << sqrt(eem_m_fT_isFromB) << endl;

	cout << "               IsFromC			: " << eem_m_fT_isFromC << " +/- " << sqrt(eem_m_fT_isFromC) << endl;

	cout << "               IsFromPh		: " << eem_m_fT_isFromPh << " +/- " << sqrt(eem_m_fT_isFromPh) << "( " << eem_m_fT_isFromPh/eem_m_fT *100. << "% )" << endl;

	cout << "               IsFromL			: " << eem_m_fT_isFromL << " +/- " << sqrt(eem_m_fT_isFromL) << endl;

	cout << "               IsFromElse		: " << eem_m_fT_isFromElse << " +/- " << sqrt(eem_m_fT_isFromElse) << endl;

	cout << "       eem ppf(e+m) ttt observed : " <<endl;

	cout << "       		All sources		: " << eem_e_fT+eem_m_fT << " +/- " << sqrt(eem_e_fT+eem_m_fT) << endl;

	cout << "               Is(not)Matched	: " << eem_e_fT_isNotMatched+eem_m_fT_isNotMatched << " +/- " << sqrt(eem_e_fT_isNotMatched+eem_m_fT_isNotMatched) << endl;

	cout << "               IsFromB			: " << eem_e_fT_isFromB+eem_m_fT_isFromB << " +/- " << sqrt(eem_e_fT_isFromB+eem_m_fT_isFromB) << endl;

	cout << "               IsFromC			: " << eem_e_fT_isFromC+eem_m_fT_isFromC << " +/- " << sqrt(eem_e_fT_isFromC+eem_m_fT_isFromC) << endl;

	cout << "               IsFromPh		: " << eem_e_fT_isFromPh+eem_m_fT_isFromPh << " +/- " << sqrt(eem_e_fT_isFromPh+eem_m_fT_isFromPh)<< "( " << (eem_e_fT_isFromPh+eem_m_fT_isFromPh)/(eem_e_fT+eem_m_fT) *100. << "% )"  << endl;

	cout << "               IsFromL			: " << eem_e_fT_isFromL+eem_m_fT_isFromL << " +/- " << sqrt(eem_e_fT_isFromL+eem_m_fT_isFromL) << endl;

	cout << "               IsFromElse		: " << eem_e_fT_isFromElse+eem_m_fT_isFromElse << " +/- " << sqrt(eem_e_fT_isFromElse+eem_m_fT_isFromElse) << endl;


	//===========EMM==============	
	std::cout<<"Processing EMM ..." << std::endl;

	EMM_ttt_unw = t->Draw(observ+">>h_EMM_ttt",SFs+" * ( "+SR_cut+isEMM+isTTT+" )","GOFF");
	EMM_ttt = h_EMM_ttt->Integral();

	//1 fake / 2 prompts
	std::cout<<"Processing EMM 1 fake t/l ..." << std::endl;
	EMM_ppf_ttt = t->Draw(observ,SR_cut+isEMM_+isPPF+isTTT);
	EMM_pfp_ttt = t->Draw(observ,SR_cut+isEMM_+isPFP+isTTT);
	EMM_fpp_ttt = t->Draw(observ,SR_cut+isEMM_+isFPP+isTTT);

	EMM_ppf_tt = t->Draw(observ,SR_cut+isEMM_+isPPF+isPPF_isTT);

	std::cout<<"Processing EMM 1 fake t/l sources ..." << std::endl;
		//sources - isMatched
		EMM_ppf_ttt_isNotMatched = t->Draw(observ,SR_cut+isEMM_+isPPF+isTTT+isPPF_isNotMatched);
		EMM_pfp_ttt_isNotMatched = t->Draw(observ,SR_cut+isEMM_+isPFP+isTTT+isPFP_isNotMatched);
		EMM_fpp_ttt_isNotMatched = t->Draw(observ,SR_cut+isEMM_+isFPP+isTTT+isFPP_isNotMatched);

		EMM_ppf_tt_isNotMatched = t->Draw(observ,SR_cut+isEMM_+isPPF+isPPF_isTT+isPPF_isNotMatched);

		//sources - isFromB
		EMM_ppf_ttt_isFromB = t->Draw(observ,SR_cut+isEMM_+isPPF+isTTT+isPPF_isFromB);
		EMM_pfp_ttt_isFromB = t->Draw(observ,SR_cut+isEMM_+isPFP+isTTT+isPFP_isFromB);
		EMM_fpp_ttt_isFromB = t->Draw(observ,SR_cut+isEMM_+isFPP+isTTT+isFPP_isFromB);

		EMM_ppf_tt_isFromB = t->Draw(observ,SR_cut+isEMM_+isPPF+isPPF_isTT+isPPF_isFromB);

		//sources - isFromC
		EMM_ppf_ttt_isFromC = t->Draw(observ,SR_cut+isEMM_+isPPF+isTTT+isPPF_isFromC);
		EMM_pfp_ttt_isFromC = t->Draw(observ,SR_cut+isEMM_+isPFP+isTTT+isPFP_isFromC);
		EMM_fpp_ttt_isFromC = t->Draw(observ,SR_cut+isEMM_+isFPP+isTTT+isFPP_isFromC);

		EMM_ppf_tt_isFromC = t->Draw(observ,SR_cut+isEMM_+isPPF+isPPF_isTT+isPPF_isFromC);

		//sources - isFromPh
		EMM_ppf_ttt_isFromPh = t->Draw(observ,SR_cut+isEMM_+isPPF+isTTT+isPPF_isFromPh);
		EMM_pfp_ttt_isFromPh = t->Draw(observ,SR_cut+isEMM_+isPFP+isTTT+isPFP_isFromPh);
		EMM_fpp_ttt_isFromPh = t->Draw(observ,SR_cut+isEMM_+isFPP+isTTT+isFPP_isFromPh);

		EMM_ppf_tt_isFromPh = t->Draw(observ,SR_cut+isEMM_+isPPF+isPPF_isTT+isPPF_isFromPh);

		//sources - isFromElse
		EMM_ppf_ttt_isFromElse = t->Draw(observ,SR_cut+isEMM_+isPPF+isTTT+isPPF_isFromElse);
		EMM_pfp_ttt_isFromElse = t->Draw(observ,SR_cut+isEMM_+isPFP+isTTT+isPFP_isFromElse);
		EMM_fpp_ttt_isFromElse = t->Draw(observ,SR_cut+isEMM_+isFPP+isTTT+isFPP_isFromElse);

		EMM_ppf_tt_isFromElse = t->Draw(observ,SR_cut+isEMM_+isPPF+isPPF_isTT+isPPF_isFromElse);

		//sources - isFromL
		EMM_ppf_ttt_isFromL = t->Draw(observ,SR_cut+isEMM_+isPPF+isTTT+isPPF_isFromL);
		EMM_pfp_ttt_isFromL = t->Draw(observ,SR_cut+isEMM_+isPFP+isTTT+isPFP_isFromL);
		EMM_fpp_ttt_isFromL = t->Draw(observ,SR_cut+isEMM_+isFPP+isTTT+isFPP_isFromL);

		EMM_ppf_tt_isFromL = t->Draw(observ,SR_cut+isEMM_+isPPF+isPPF_isTT+isPPF_isFromL);

	std::cout<<"Processing MEM 1 fake t/l..." << std::endl;
	MEM_ppf_ttt = t->Draw(observ,SR_cut+isMEM_+isPPF+isTTT);
	MEM_pfp_ttt = t->Draw(observ,SR_cut+isMEM_+isPFP+isTTT);
	MEM_fpp_ttt = t->Draw(observ,SR_cut+isMEM_+isFPP+isTTT);

	MEM_ppf_tt = t->Draw(observ,SR_cut+isMEM_+isPPF+isPPF_isTT);

	std::cout<<"Processing MEM 1 fake sources..." << std::endl;
		//source - isMatched
		MEM_ppf_ttt_isNotMatched = t->Draw(observ,SR_cut+isMEM_+isPPF+isTTT+isPPF_isNotMatched);
		MEM_pfp_ttt_isNotMatched = t->Draw(observ,SR_cut+isMEM_+isPFP+isTTT+isPFP_isNotMatched);
		MEM_fpp_ttt_isNotMatched = t->Draw(observ,SR_cut+isMEM_+isFPP+isTTT+isFPP_isNotMatched);

		MEM_ppf_tt_isNotMatched = t->Draw(observ,SR_cut+isMEM_+isPPF+isPPF_isTT+isPPF_isNotMatched);

		//source - isFromB
		MEM_ppf_ttt_isFromB = t->Draw(observ,SR_cut+isMEM_+isPPF+isTTT+isPPF_isFromB);
		MEM_pfp_ttt_isFromB = t->Draw(observ,SR_cut+isMEM_+isPFP+isTTT+isPFP_isFromB);
		MEM_fpp_ttt_isFromB = t->Draw(observ,SR_cut+isMEM_+isFPP+isTTT+isFPP_isFromB);

		MEM_ppf_tt_isFromB = t->Draw(observ,SR_cut+isMEM_+isPPF+isPPF_isTT+isPPF_isFromB);

		//source - isFromC
		MEM_ppf_ttt_isFromC = t->Draw(observ,SR_cut+isMEM_+isPPF+isTTT+isPPF_isFromC);
		MEM_pfp_ttt_isFromC = t->Draw(observ,SR_cut+isMEM_+isPFP+isTTT+isPFP_isFromC);
		MEM_fpp_ttt_isFromC = t->Draw(observ,SR_cut+isMEM_+isFPP+isTTT+isFPP_isFromC);

		MEM_ppf_tt_isFromC = t->Draw(observ,SR_cut+isMEM_+isPPF+isPPF_isTT+isPPF_isFromC);

		//source - isFromPh
		MEM_ppf_ttt_isFromPh = t->Draw(observ,SR_cut+isMEM_+isPPF+isTTT+isPPF_isFromPh);
		MEM_pfp_ttt_isFromPh = t->Draw(observ,SR_cut+isMEM_+isPFP+isTTT+isPFP_isFromPh);
		MEM_fpp_ttt_isFromPh = t->Draw(observ,SR_cut+isMEM_+isFPP+isTTT+isFPP_isFromPh);

		MEM_ppf_tt_isFromPh = t->Draw(observ,SR_cut+isMEM_+isPPF+isPPF_isTT+isPPF_isFromPh);

		//source - isFromElse
		MEM_ppf_ttt_isFromElse = t->Draw(observ,SR_cut+isMEM_+isPPF+isTTT+isPPF_isFromElse);
		MEM_pfp_ttt_isFromElse = t->Draw(observ,SR_cut+isMEM_+isPFP+isTTT+isPFP_isFromElse);
		MEM_fpp_ttt_isFromElse = t->Draw(observ,SR_cut+isMEM_+isFPP+isTTT+isFPP_isFromElse);

		MEM_ppf_tt_isFromElse = t->Draw(observ,SR_cut+isMEM_+isPPF+isPPF_isTT+isPPF_isFromElse);

		//source - isFromL
		MEM_ppf_ttt_isFromL = t->Draw(observ,SR_cut+isMEM_+isPPF+isTTT+isPPF_isFromL);
		MEM_pfp_ttt_isFromL = t->Draw(observ,SR_cut+isMEM_+isPFP+isTTT+isPFP_isFromL);
		MEM_fpp_ttt_isFromL = t->Draw(observ,SR_cut+isMEM_+isFPP+isTTT+isFPP_isFromL);

		MEM_ppf_tt_isFromL = t->Draw(observ,SR_cut+isMEM_+isPPF+isPPF_isTT+isPPF_isFromL);

	std::cout<<"Processing MME 1 fake t/l..." << std::endl;
	MME_ppf_ttt = t->Draw(observ,SR_cut+isMME_+isPPF+isTTT);
	MME_pfp_ttt = t->Draw(observ,SR_cut+isMME_+isPFP+isTTT);
	MME_fpp_ttt = t->Draw(observ,SR_cut+isMME_+isFPP+isTTT);

	MME_ppf_tt = t->Draw(observ,SR_cut+isMME_+isPPF+isPPF_isTT);

	std::cout<<"Processing MME 1 fake t/l sources ..." << std::endl;
		//sources - isMatched
		MME_ppf_ttt_isNotMatched = t->Draw(observ,SR_cut+isMME_+isPPF+isTTT+isPPF_isNotMatched);
		MME_pfp_ttt_isNotMatched = t->Draw(observ,SR_cut+isMME_+isPFP+isTTT+isPFP_isNotMatched);
		MME_fpp_ttt_isNotMatched = t->Draw(observ,SR_cut+isMME_+isFPP+isTTT+isFPP_isNotMatched);

		MME_ppf_tt_isNotMatched = t->Draw(observ,SR_cut+isMME_+isPPF+isPPF_isTT+isPPF_isNotMatched);

		//sources - isFromB
		MME_ppf_ttt_isFromB = t->Draw(observ,SR_cut+isMME_+isPPF+isTTT+isPPF_isFromB);
		MME_pfp_ttt_isFromB = t->Draw(observ,SR_cut+isMME_+isPFP+isTTT+isPFP_isFromB);
		MME_fpp_ttt_isFromB = t->Draw(observ,SR_cut+isMME_+isFPP+isTTT+isFPP_isFromB);

		MME_ppf_tt_isFromB = t->Draw(observ,SR_cut+isMME_+isPPF+isPPF_isTT+isPPF_isFromB);

		//sources - isFromC
		MME_ppf_ttt_isFromC = t->Draw(observ,SR_cut+isMME_+isPPF+isTTT+isPPF_isFromC);
		MME_pfp_ttt_isFromC = t->Draw(observ,SR_cut+isMME_+isPFP+isTTT+isPFP_isFromC);
		MME_fpp_ttt_isFromC = t->Draw(observ,SR_cut+isMME_+isFPP+isTTT+isFPP_isFromC);

		MME_ppf_tt_isFromC = t->Draw(observ,SR_cut+isMME_+isPPF+isPPF_isTT+isPPF_isFromC);

		//sources - isFromPh
		MME_ppf_ttt_isFromPh = t->Draw(observ,SR_cut+isMME_+isPPF+isTTT+isPPF_isFromPh);
		MME_pfp_ttt_isFromPh = t->Draw(observ,SR_cut+isMME_+isPFP+isTTT+isPFP_isFromPh);
		MME_fpp_ttt_isFromPh = t->Draw(observ,SR_cut+isMME_+isFPP+isTTT+isFPP_isFromPh);

		MME_ppf_tt_isFromPh = t->Draw(observ,SR_cut+isMME_+isPPF+isPPF_isTT+isPPF_isFromPh);

		//sources - isFromElse
		MME_ppf_ttt_isFromElse = t->Draw(observ,SR_cut+isMME_+isPPF+isTTT+isPPF_isFromElse);
		MME_pfp_ttt_isFromElse = t->Draw(observ,SR_cut+isMME_+isPFP+isTTT+isPFP_isFromElse);
		MME_fpp_ttt_isFromElse = t->Draw(observ,SR_cut+isMME_+isFPP+isTTT+isFPP_isFromElse);

		MME_ppf_tt_isFromElse = t->Draw(observ,SR_cut+isMME_+isPPF+isPPF_isTT+isPPF_isFromElse);

		//sources - isFromL
		MME_ppf_ttt_isFromL = t->Draw(observ,SR_cut+isMME_+isPPF+isTTT+isPPF_isFromL);
		MME_pfp_ttt_isFromL = t->Draw(observ,SR_cut+isMME_+isPFP+isTTT+isPFP_isFromL);
		MME_fpp_ttt_isFromL = t->Draw(observ,SR_cut+isMME_+isFPP+isTTT+isFPP_isFromL);

		MME_ppf_tt_isFromL = t->Draw(observ,SR_cut+isMME_+isPPF+isPPF_isTT+isPPF_isFromL);


	cout << " ========= EMM ========= " << endl;
	cout << "       TTT		: " << EMM_ttt_unw << " ( weighted: "<< EMM_ttt << " ) "<<endl;
	cout << "	--1 fake-- :  "<< endl;
	cout << "	f(T):   "<< endl;
	cout << "       EM(M) PPF TTT (fake mu) : " << EMM_ppf_ttt << endl;
	if(printSource){
	cout << "               Is(not)Matched   : " << EMM_ppf_ttt_isNotMatched << endl;
	cout << "               IsFromB          : " << EMM_ppf_ttt_isFromB << endl;
	cout << "               IsFromC          : " << EMM_ppf_ttt_isFromC << endl;
	cout << "               IsFromPh         : " << EMM_ppf_ttt_isFromPh << endl;
	cout << "               IsFromL          : " << EMM_ppf_ttt_isFromL<< endl;
	cout << "               IsFromElse         : " << EMM_ppf_ttt_isFromElse << endl;
	}
	cout << "       E(M)M PFP TTT (fake mu) : " << EMM_pfp_ttt << endl;
	if(printSource){
	cout << "               Is(not)Matched   : " << EMM_pfp_ttt_isNotMatched << endl;
	cout << "               IsFromB          : " << EMM_pfp_ttt_isFromB << endl;
	cout << "               IsFromC          : " << EMM_pfp_ttt_isFromC << endl;
	cout << "               IsFromPh         : " << EMM_pfp_ttt_isFromPh << endl;
	cout << "               IsFromL          : " << EMM_pfp_ttt_isFromL<< endl;
	cout << "               IsFromElse         : " << EMM_pfp_ttt_isFromElse << endl;
	}
	cout << "       (E)MM FPP TTT (fake el) : " << EMM_fpp_ttt << endl;
	if(printSource){
	cout << "               Is(not)Matched   : " << EMM_fpp_ttt_isNotMatched << endl;
	cout << "               IsFromB          : " << EMM_fpp_ttt_isFromB << endl;
	cout << "               IsFromC          : " << EMM_fpp_ttt_isFromC << endl;
	cout << "               IsFromPh         : " << EMM_fpp_ttt_isFromPh << endl;
	cout << "               IsFromL          : " << EMM_fpp_ttt_isFromL<< endl;
	cout << "               IsFromElse         : " << EMM_fpp_ttt_isFromElse << endl;
	}
	cout << "-" << endl;
	cout << "       ME(M) PPF TTT (fake mu) : " << MEM_ppf_ttt << endl;
	if(printSource){
	cout << "               Is(not)Matched   : " << MEM_ppf_ttt_isNotMatched << endl;
	cout << "               IsFromB          : " << MEM_ppf_ttt_isFromB << endl;
	cout << "               IsFromC          : " << MEM_ppf_ttt_isFromC << endl;
	cout << "               IsFromPh         : " << MEM_ppf_ttt_isFromPh << endl;
	cout << "               IsFromL          : " << MEM_ppf_ttt_isFromL<< endl;
	cout << "               IsFromElse         : " << MEM_ppf_ttt_isFromElse << endl;
	}
	cout << "       M(E)M PFP TTT (fake el) : " << MEM_pfp_ttt << endl;
	if(printSource){
	cout << "               Is(not)Matched   : " << MEM_pfp_ttt_isNotMatched << endl;
	cout << "               IsFromB          : " << MEM_pfp_ttt_isFromB << endl;
	cout << "               IsFromC          : " << MEM_pfp_ttt_isFromC << endl;
	cout << "               IsFromPh         : " << MEM_pfp_ttt_isFromPh << endl;
	cout << "               IsFromL          : " << MEM_pfp_ttt_isFromL<< endl;
	cout << "               IsFromElse         : " << MEM_pfp_ttt_isFromElse << endl;
	}
	cout << "       (M)EM FPP TTT (fake mu) : " << MEM_fpp_ttt << endl;
	if(printSource){
	cout << "               Is(not)Matched   : " << MEM_fpp_ttt_isNotMatched << endl;
	cout << "               IsFromB          : " << MEM_fpp_ttt_isFromB << endl;
	cout << "               IsFromC          : " << MEM_fpp_ttt_isFromC << endl;
	cout << "               IsFromPh         : " << MEM_fpp_ttt_isFromPh << endl;
	cout << "               IsFromL          : " << MEM_fpp_ttt_isFromL<< endl;
	cout << "               IsFromElse         : " << MEM_fpp_ttt_isFromElse << endl;
	}
	cout << "-" << endl;
	cout << "       MM(E) PPF TTT (fake el) : " << MME_ppf_ttt << endl;
	if(printSource){
	cout << "               Is(not)Matched   : " << MME_ppf_ttt_isNotMatched << endl;
	cout << "               IsFromB          : " << MME_ppf_ttt_isFromB << endl;
	cout << "               IsFromC          : " << MME_ppf_ttt_isFromC << endl;
	cout << "               IsFromPh         : " << MME_ppf_ttt_isFromPh << endl;
	cout << "               IsFromL          : " << MME_ppf_ttt_isFromL<< endl;
	cout << "               IsFromElse         : " << MME_ppf_ttt_isFromElse << endl;
	}
	cout << "       M(M)E PFP TTT (fake mu) : " << MME_pfp_ttt << endl;
	if(printSource){
	cout << "               Is(not)Matched   : " << MME_pfp_ttt_isNotMatched << endl;
	cout << "               IsFromB          : " << MME_pfp_ttt_isFromB << endl;
	cout << "               IsFromC          : " << MME_pfp_ttt_isFromC << endl;
	cout << "               IsFromPh         : " << MME_pfp_ttt_isFromPh << endl;
	cout << "               IsFromL          : " << MME_pfp_ttt_isFromL<< endl;
	cout << "               IsFromElse         : " << MME_pfp_ttt_isFromElse << endl;
	}
	cout << "       (M)ME FPP TTT (fake mu) : " << MME_fpp_ttt << endl;
	if(printSource){
	cout << "               Is(not)Matched   : " << MME_fpp_ttt_isNotMatched << endl;
	cout << "               IsFromB          : " << MME_fpp_ttt_isFromB << endl;
	cout << "               IsFromC          : " << MME_fpp_ttt_isFromC << endl;
	cout << "               IsFromPh         : " << MME_fpp_ttt_isFromPh << endl;
	cout << "               IsFromL          : " << MME_fpp_ttt_isFromL<< endl;
	cout << "               IsFromElse         : " << MME_fpp_ttt_isFromElse << endl;
	}
	cout << "" << endl;
	cout << "       ---------------------  " << endl;

	float emm_e_fT = EMM_fpp_ttt+MEM_pfp_ttt+MME_ppf_ttt;

		float emm_e_fT_isNotMatched = EMM_fpp_ttt_isNotMatched+MEM_pfp_ttt_isNotMatched+MME_ppf_ttt_isNotMatched;
		float emm_e_fT_isFromB = EMM_fpp_ttt_isFromB+MEM_pfp_ttt_isFromB+MME_ppf_ttt_isFromB;
		float emm_e_fT_isFromC = EMM_fpp_ttt_isFromC+MEM_pfp_ttt_isFromC+MME_ppf_ttt_isFromC;
		float emm_e_fT_isFromPh = EMM_fpp_ttt_isFromPh+MEM_pfp_ttt_isFromPh+MME_ppf_ttt_isFromPh;
		float emm_e_fT_isFromElse = EMM_fpp_ttt_isFromElse+MEM_pfp_ttt_isFromElse+MME_ppf_ttt_isFromElse;
		float emm_e_fT_isFromL = EMM_fpp_ttt_isFromL+MEM_pfp_ttt_isFromL+MME_ppf_ttt_isFromL;

	float emm_e_f = MME_ppf_tt;

		float emm_e_f_isNotMatched = MME_ppf_tt_isNotMatched;
		float emm_e_f_isFromB = MME_ppf_tt_isFromB;
		float emm_e_f_isFromC = MME_ppf_tt_isFromC;
		float emm_e_f_isFromPh =MME_ppf_tt_isFromPh;
		float emm_e_f_isFromElse =MME_ppf_tt_isFromElse;
		float emm_e_f_isFromL = MME_ppf_tt_isFromL;

	cout << "       emm ppf(e) ttt observed : " <<endl;
	cout << "       		All sources		: " << emm_e_fT << " +/- " << sqrt(emm_e_fT) << endl;

	cout << "               Is(not)Matched	: " << emm_e_fT_isNotMatched << " +/- " << sqrt(emm_e_fT_isNotMatched) << endl;

	cout << "               IsFromB			: " << emm_e_fT_isFromB << " +/- " << sqrt(emm_e_fT_isFromB) << endl;

	cout << "               IsFromC			: " << emm_e_fT_isFromC << " +/- " << sqrt(emm_e_fT_isFromC) << endl;

	cout << "               IsFromPh		: " << emm_e_fT_isFromPh << " +/- " << sqrt(emm_e_fT_isFromPh) << "( " << emm_e_fT_isFromPh/emm_e_fT *100. << "% )" << endl;

	cout << "               IsFromL			: " << emm_e_fT_isFromL << " +/- " << sqrt(emm_e_fT_isFromL) << endl;

	cout << "               IsFromElse		: " << emm_e_fT_isFromElse << " +/- " << sqrt(emm_e_fT_isFromElse) << endl;

	float emm_m_fT = EMM_ppf_ttt+EMM_pfp_ttt+ MEM_ppf_ttt+ MEM_fpp_ttt+ MME_pfp_ttt+ MME_fpp_ttt;

		float emm_m_fT_isNotMatched = EMM_ppf_ttt_isNotMatched+EMM_pfp_ttt_isNotMatched+ MEM_ppf_ttt_isNotMatched+ MEM_fpp_ttt_isNotMatched+ MME_pfp_ttt_isNotMatched+ MME_fpp_ttt_isNotMatched;
		float emm_m_fT_isFromB = EMM_ppf_ttt_isFromB+EMM_pfp_ttt_isFromB+ MEM_ppf_ttt_isFromB+ MEM_fpp_ttt_isFromB+ MME_pfp_ttt_isFromB+ MME_fpp_ttt_isFromB;
		float emm_m_fT_isFromC = EMM_ppf_ttt_isFromC+EMM_pfp_ttt_isFromC+ MEM_ppf_ttt_isFromC+ MEM_fpp_ttt_isFromC+ MME_pfp_ttt_isFromC+ MME_fpp_ttt_isFromC;
		float emm_m_fT_isFromPh = EMM_ppf_ttt_isFromPh+EMM_pfp_ttt_isFromPh+ MEM_ppf_ttt_isFromPh+ MEM_fpp_ttt_isFromPh+ MME_pfp_ttt_isFromPh+ MME_fpp_ttt_isFromPh;
		float emm_m_fT_isFromElse = EMM_ppf_ttt_isFromElse+EMM_pfp_ttt_isFromElse+ MEM_ppf_ttt_isFromElse+ MEM_fpp_ttt_isFromElse+ MME_pfp_ttt_isFromElse+ MME_fpp_ttt_isFromElse;
		float emm_m_fT_isFromL = EMM_ppf_ttt_isFromL+EMM_pfp_ttt_isFromL+ MEM_ppf_ttt_isFromL+ MEM_fpp_ttt_isFromL+ MME_pfp_ttt_isFromL+ MME_fpp_ttt_isFromL;

	float emm_m_f = EMM_ppf_tt+ MEM_ppf_tt;

		float emm_m_f_isNotMatched = EMM_ppf_tt_isNotMatched+ MEM_ppf_tt_isNotMatched;
		float emm_m_f_isFromB = EMM_ppf_tt_isFromB+ MEM_ppf_tt_isFromB;
		float emm_m_f_isFromC = EMM_ppf_tt_isFromC+ MEM_ppf_tt_isFromC;
		float emm_m_f_isFromPh = EMM_ppf_tt_isFromPh+ MEM_ppf_tt_isFromPh;
		float emm_m_f_isFromElse = EMM_ppf_tt_isFromElse+ MEM_ppf_tt_isFromElse;
		float emm_m_f_isFromL = EMM_ppf_tt_isFromL+ MEM_ppf_tt_isFromL;

	cout << "       emm ppf(m) ttt observed : " <<endl;
	cout << "       		All sources		: " << emm_m_fT << " +/- " << sqrt(emm_m_fT) << endl;

	cout << "               Is(not)Matched	: " << emm_m_fT_isNotMatched << " +/- " << sqrt(emm_m_fT_isNotMatched) << endl;

	cout << "               IsFromB			: " << emm_m_fT_isFromB << " +/- " << sqrt(emm_m_fT_isFromB) << endl;

	cout << "               IsFromC			: " << emm_m_fT_isFromC << " +/- " << sqrt(emm_m_fT_isFromC) << endl;

	cout << "               IsFromPh		: " << emm_m_fT_isFromPh << " +/- " << sqrt(emm_m_fT_isFromPh)<< "( " << emm_m_fT_isFromPh/emm_m_fT *100. << "% )"  << endl;

	cout << "               IsFromL			: " << emm_m_fT_isFromL << " +/- " << sqrt(emm_m_fT_isFromL) << endl;

	cout << "               IsFromElse		: " << emm_m_fT_isFromElse << " +/- " << sqrt(emm_m_fT_isFromElse) << endl;


	cout << "       emm ppf(e+m) ttt observed : " <<endl;

	cout << "       		All sources		: " << emm_e_fT+emm_m_fT << " +/- " << sqrt(emm_e_fT+emm_m_fT) << endl;

	cout << "               Is(not)Matched	: " << emm_e_fT_isNotMatched+emm_m_fT_isNotMatched << " +/- " << sqrt(emm_e_fT_isNotMatched+emm_m_fT_isNotMatched) << endl;

	cout << "               IsFromB			: " << emm_e_fT_isFromB+emm_m_fT_isFromB << " +/- " << sqrt(emm_e_fT_isFromB+emm_m_fT_isFromB) << endl;

	cout << "               IsFromC			: " << emm_e_fT_isFromC+emm_m_fT_isFromC << " +/- " << sqrt(emm_e_fT_isFromC+emm_m_fT_isFromC) << endl;

	cout << "               IsFromPh		: " << emm_e_fT_isFromPh+emm_m_fT_isFromPh << " +/- " << sqrt(emm_e_fT_isFromPh+emm_m_fT_isFromPh)<< "( " << (emm_e_fT_isFromPh+emm_m_fT_isFromPh)/(emm_e_fT+emm_m_fT) *100. << "% )"  << endl;

	cout << "               IsFromL			: " << emm_e_fT_isFromL+emm_m_fT_isFromL << " +/- " << sqrt(emm_e_fT_isFromL+emm_m_fT_isFromL) << endl;

	cout << "               IsFromElse		: " << emm_e_fT_isFromElse+emm_m_fT_isFromElse << " +/- " << sqrt(emm_e_fT_isFromElse+emm_m_fT_isFromElse) << endl;

// }
// 	===========MMM==============
	std::cout<<"Processing MMM ..." << std::endl;

	MMM_ttt_unw = t->Draw(observ+">>h_MMM_ttt",SFs+" * ( "+SR_cut+isMMM+isTTT+" )","GOFF");
	MMM_ttt = h_MMM_ttt->Integral();

	std::cout<<"Processing MMM 1 fake t/l ..." << std::endl;
	MMM_ppf_tt = t->Draw(observ,SR_cut+isMMM+isPPF+isPPF_isTT );

	MMM_ppf_ttt = t->Draw(observ,SR_cut+isMMM+" && ( isPPF || isPFP || isFPP ) && isTTT " );

	std::cout<<"Processing MMM 1 fake t/l sources ..." << std::endl;

		//

		MMM_ppf_ttt_isNotMatched = t->Draw(observ,SR_cut+isMMM+" && ( isPPF && isTTT)"+isPPF_isNotMatched);
		MMM_pfp_ttt_isNotMatched = t->Draw(observ,SR_cut+isMMM+" && ( isPFP && isTTT)"+isPFP_isNotMatched );
		MMM_fpp_ttt_isNotMatched = t->Draw(observ,SR_cut+isMMM+" && ( isFPP && isTTT)"+isFPP_isNotMatched );

		MMM_ppf_ttt_isFromB = t->Draw(observ,SR_cut+isMMM+" && ( isPPF && isTTT)"+isPPF_isFromB);
		MMM_pfp_ttt_isFromB = t->Draw(observ,SR_cut+isMMM+" && ( isPFP && isTTT)"+isPFP_isFromB );
		MMM_fpp_ttt_isFromB = t->Draw(observ,SR_cut+isMMM+" && ( isFPP && isTTT)"+isFPP_isFromB );

		MMM_ppf_ttt_isFromC = t->Draw(observ,SR_cut+isMMM+" && ( isPPF && isTTT)"+isPPF_isFromC);
		MMM_pfp_ttt_isFromC = t->Draw(observ,SR_cut+isMMM+" && ( isPFP && isTTT)"+isPFP_isFromC );
		MMM_fpp_ttt_isFromC = t->Draw(observ,SR_cut+isMMM+" && ( isFPP && isTTT)"+isFPP_isFromC );

		MMM_ppf_ttt_isFromPh = t->Draw(observ,SR_cut+isMMM+" && ( isPPF && isTTT)"+isPPF_isFromPh);
		MMM_pfp_ttt_isFromPh = t->Draw(observ,SR_cut+isMMM+" && ( isPFP && isTTT)"+isPFP_isFromPh );
		MMM_fpp_ttt_isFromPh = t->Draw(observ,SR_cut+isMMM+" && ( isFPP && isTTT)"+isFPP_isFromPh );

		MMM_ppf_ttt_isFromElse = t->Draw(observ,SR_cut+isMMM+" && ( isPPF && isTTT)"+isPPF_isFromElse);
		MMM_pfp_ttt_isFromElse = t->Draw(observ,SR_cut+isMMM+" && ( isPFP && isTTT)"+isPFP_isFromElse );
		MMM_fpp_ttt_isFromElse = t->Draw(observ,SR_cut+isMMM+" && ( isFPP && isTTT)"+isFPP_isFromElse );

		MMM_ppf_ttt_isFromL = t->Draw(observ,SR_cut+isMMM+" && ( isPPF && isTTT)"+isPPF_isFromL);
		MMM_pfp_ttt_isFromL = t->Draw(observ,SR_cut+isMMM+" && ( isPFP && isTTT)"+isPFP_isFromL );
		MMM_fpp_ttt_isFromL = t->Draw(observ,SR_cut+isMMM+" && ( isFPP && isTTT)"+isFPP_isFromL );


	//


	cout << " ========= MMM ========= " << endl;
	cout << "       IsTTT		: " << MMM_ttt_unw << " ( weighted: "<< MMM_ttt << " ) "<<endl;
	cout << "	1 fake / 2 prompts:   "<< endl;
	cout << "       IsTTT f(T)  : " << MMM_ppf_ttt << endl;
	if(printSource){
	cout << "               Is(not)Matched   : " << MMM_ppf_ttt_isNotMatched+MMM_pfp_ttt_isNotMatched+MMM_fpp_ttt_isNotMatched << endl;
	cout << "               IsFromB          : " << MMM_ppf_ttt_isFromB+MMM_pfp_ttt_isFromB+MMM_fpp_ttt_isFromB << endl;
	cout << "               IsFromC          : " << MMM_ppf_ttt_isFromC+MMM_pfp_ttt_isFromC+MMM_fpp_ttt_isFromC << endl;
	cout << "               IsFromPh         : " << MMM_ppf_ttt_isFromPh+MMM_pfp_ttt_isFromPh+MMM_fpp_ttt_isFromPh << endl;
	cout << "               IsFromL          : " << MMM_ppf_ttt_isFromL+MMM_pfp_ttt_isFromL+MMM_fpp_ttt_isFromL << endl;
	cout << "               IsFromElse         : " << MMM_ppf_ttt_isFromElse+MMM_pfp_ttt_isFromElse+MMM_fpp_ttt_isFromElse << endl;
	}
	float mmm_fT = MMM_ppf_ttt*1.0;
	float mmm_f = (MMM_ppf_tt*1.0);//+MMM_pfp_tlt+MMM_fpp_ltt )*1.0;
	cout << "       		mmm ppf ttt observed : " << endl;
	cout << "       			All sources : " << mmm_fT << " +- "<< sqrt(mmm_fT) << endl;;
	float MMM_fT_isNotMatched = MMM_ppf_ttt_isNotMatched+MMM_pfp_ttt_isNotMatched+MMM_fpp_ttt_isNotMatched*1.0;
	cout << "       			_isNotMatched	: " << MMM_fT_isNotMatched << " +- "<< sqrt(MMM_fT_isNotMatched) << endl;;
	float MMM_fT_isFromB = MMM_ppf_ttt_isFromB+MMM_pfp_ttt_isFromB+MMM_fpp_ttt_isFromB*1.0;
	cout << "       			_isFromB	: " << MMM_fT_isFromB << " +- "<< sqrt(MMM_fT_isFromB) << endl;;
	float MMM_fT_isFromC = MMM_ppf_ttt_isFromC+MMM_pfp_ttt_isFromC+MMM_fpp_ttt_isFromC*1.0;
	cout << "       			_isFromC	: " << MMM_fT_isFromC << " +- "<< sqrt(MMM_fT_isFromC) << endl;;
	float MMM_fT_isFromPh = MMM_ppf_ttt_isFromPh+MMM_pfp_ttt_isFromPh+MMM_fpp_ttt_isFromPh*1.0;
	cout << "       			_isFromPh	: " << MMM_fT_isFromPh << " +- "<< sqrt(MMM_fT_isFromPh) << "( " << MMM_fT_isFromPh/mmm_fT *100. << "% )" << endl;;
	float MMM_fT_isFromL = MMM_ppf_ttt_isFromL+MMM_pfp_ttt_isFromL+MMM_fpp_ttt_isFromL*1.0;
	cout << "       			_isFromL	: " << MMM_fT_isFromL << " +- "<< sqrt(MMM_fT_isFromL) << endl;;
	float MMM_fT_isFromElse = MMM_ppf_ttt_isFromElse+MMM_pfp_ttt_isFromElse+MMM_fpp_ttt_isFromElse*1.0;
	cout << "       			_isFromElse	: " << MMM_fT_isFromElse << " +- "<< sqrt(MMM_fT_isFromElse) << endl;;
	

	cout<< ""<< endl;
	cout<< ""<< endl;
	cout<< "++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<< endl;
	cout<< ""<< endl;
	cout<< ""<< endl;
	cout<< "Total TTT count (unweighted)	: "<< (EEE_ttt_unw+EEM_ttt_unw+EMM_ttt_unw+MMM_ttt_unw) <<endl; 	
	cout<< "Total TTT count (weighted)		: "<< (EEE_ttt+EEM_ttt+EMM_ttt+MMM_ttt) <<endl; 	
	cout<< ""<< endl;			

	gApplication->Terminate();
	
}

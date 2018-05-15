#include <string> 
#include <vector> 

/*
void plotThings(TString sigStr,TFile *fsig, TString bkgStr, std::vector<TFile *>fbkg, std::vector<float> xs, TString var, int bin, float xmin, float xmax, TString ch="", TString cut=""){

  TTree *tsig = (TTree*) fsig->Get("ljmet");
  std::vector<TTree *> tbkg;
  for(int i=0;i<fbkg.size();i++) tbkg.push_back( (TTree*) fbkg.at(i)->Get("ljmet")) ;

  TH1D * hsig = new TH1D("hsig","hsig",bin,xmin,xmax);
  TH1D * hbkg_tot = new TH1D("hbkg_tot","hbkg_tot",bin,xmin,xmax);
  std::vector <TH1D * > hbkg;
  for(int i=0;i<tbkg.size();i++){
	std::string str = std::to_string(i);
	TString s = str;
  	hbkg.push_back( new TH1D("hbkg"+s,"hbkg"+s,bin,xmin,xmax) );
  }

  TCanvas *c = new TCanvas();

  tsig->Draw(var+">>hsig",ch+"==1");
  std::vector <int> hbkg_integral;
  for(int i=0;i<tbkg.size();i++){
	std::string str = std::to_string(i);
	TString s = str;
	hbkg_integral.push_back((int)tbkg.at(i)->Draw(var+">>hbkg"+s,""));
	//std::cout << "-----> " << hbkg.at(i)->GetName() << "integral = "<< (int)tbkg.at(i)->Draw(var+">>hbkg"+s,"") << std::endl;
  }

  hsig->Scale(1/hsig->Integral());
  hsig->SetTitle(sigStr);
  hsig->SetName(sigStr);

  for(int i=0;i<tbkg.size();i++){
  	hbkg.at(i)->Scale(1/hbkg.at(i)->Integral() * xs.at(i));
  	hbkg_tot->Add(hbkg.at(i));
  }

  hbkg_tot->Scale(1/hbkg_tot->Integral());

  hbkg_tot->SetLineColor(kRed);
  hbkg_tot->GetXaxis()->SetTitle(var);
  hbkg_tot->SetTitle(bkgStr);
  hbkg_tot->SetName(bkgStr);

  hbkg_tot->Draw();
  gPad->Update();
  auto stat = dynamic_cast<TPaveStats*>(hbkg_tot->FindObject("stats"));
  stat->SetY1NDC(0.65); stat->SetY2NDC(0.8);
  stat->Draw();

  hsig->Draw("sames");

  TLegend *l = new TLegend(.72,.59,.89,.78);
  l->AddEntry(hsig,sigStr,"l");
  l->AddEntry(hbkg_tot,bkgStr,"l");
  l->Draw();
  
  c->SetTitle(ch);

  TString folder = "plotThings/"+bkgStr+"/"+ch+"/"+sigStr;
  gSystem->Exec("mkdir -pv "+folder);
  c->SaveAs(folder+"/"+var+"_"+sigStr+"_"+ch+"_"+bkgStr+".pdf");

}
*/

void plotThings_ROC(TString sigStr,TFile *fsig, TString bkgStr, std::vector<TFile *>fbkg, std::vector<float> xs, std::vector<TString> var, std::vector<int> bin, std::vector<float> xmin, std::vector<float> xmax, TString ch="", TString cut="", TString cutName=""){

  TTree *tsig = (TTree*) fsig->Get("ljmet");
  std::vector<TTree *> tbkg;
  for(int i=0;i<fbkg.size();i++) tbkg.push_back( (TTree*) fbkg.at(i)->Get("ljmet")) ;
  
  std::vector<TH1D *> hsig;
  std::vector<TH1D *> hbkg_tot;
  
  TCanvas *cROC  = new TCanvas();
  std::vector<TGraph *> vROC;
  TMultiGraph *mgROC  = new TMultiGraph();
  TLegend *l = new TLegend(1-.89,1-.59,1-.62,1-.88);

  TString folder = "plotThings_ROC/"+bkgStr+"/"+ch+"/"+sigStr+"/"+cutName;
  gSystem->Exec("mkdir -pv "+folder);

  for(int ivar=0; ivar<var.size();ivar++){
	std::string ivarstr = std::to_string(ivar);
	//TString ivarTStr = ivarstr;
	TString ivarTStr = "_"+var.at(ivar);

	hsig.push_back( new TH1D("hsig"+ivarTStr,"hsig"+ivarTStr,bin.at(ivar),xmin.at(ivar),xmax.at(ivar)) );
	hbkg_tot.push_back( new TH1D("hbkg_tot"+ivarTStr,"hbkg_tot"+ivarTStr,bin.at(ivar),xmin.at(ivar),xmax.at(ivar)) );
	std::vector <TH1D * > hbkg;
	for(int i=0;i<tbkg.size();i++){
	std::string str = std::to_string(i);
	TString s = str;
	hbkg.push_back( new TH1D("hbkg"+s+ivarTStr,"hbkg"+s+ivarTStr,bin.at(ivar),xmin.at(ivar),xmax.at(ivar)) );
	}

	TCanvas *c = new TCanvas();
	
	TString addCut = "";
	if(cut!="")addCut = " && "+cut;
	std::cout << "cut: " << addCut << std::endl; 

	tsig->Draw(var.at(ivar)+">>hsig"+ivarTStr,ch+"==1"+addCut);
	std::vector <int> hbkg_integral;
	for(int i=0;i<tbkg.size();i++){
	std::string str = std::to_string(i);
	TString s = str;
	hbkg_integral.push_back((int)tbkg.at(i)->Draw(var.at(ivar)+">>hbkg"+s+ivarTStr,cut));
	//std::cout << "-----> " << hbkg.at(i)->GetName() << "integral = "<< (int)tbkg.at(i)->Draw(var+">>hbkg"+s,"") << std::endl;
	}
	
	std::cout <<"hsig.at(ivar)->Integral(): " << hsig.at(ivar)->Integral() << std::endl;

	hsig.at(ivar)->Scale(1/hsig.at(ivar)->Integral());
	hsig.at(ivar)->SetTitle(sigStr);
	hsig.at(ivar)->SetName(sigStr);

	for(int i=0;i<tbkg.size();i++){
	//hbkg.at(i)->Scale(1/hbkg.at(i)->Integral() * xs.at(i)); //NEED FIX AND TURN THIS ON AT SOME POINT?!
	hbkg_tot.at(ivar)->Add(hbkg.at(i));
	}

	std::cout<< "hbkg_tot.at(ivar)->Integral() : "<<hbkg_tot.at(ivar)->Integral() << std::endl;

	hbkg_tot.at(ivar)->Scale(1/hbkg_tot.at(ivar)->Integral());

	hbkg_tot.at(ivar)->SetLineColor(kRed);
	hbkg_tot.at(ivar)->GetXaxis()->SetTitle(var.at(ivar));
	hbkg_tot.at(ivar)->SetTitle(bkgStr);
	hbkg_tot.at(ivar)->SetName(bkgStr);

	hbkg_tot.at(ivar)->Draw();
	gPad->Update();
	TPaveStats* stat = (TPaveStats*)hbkg_tot.at(ivar)->FindObject("stats");
	stat->SetY1NDC(0.65); stat->SetY2NDC(0.8);
	stat->Draw();

	hsig.at(ivar)->Draw("sames");
	
	hbkg.clear();
	
	c->SetTitle(ch+" "+cutName);
	
	cROC->cd();
	cROC->SetTitle("ROC");
	vector<float> sig_eff;
	vector<float> bkg_eff;
	std::cout << "var :" << var.at(ivar) <<std::endl;	
	std::cout << "bin size:"<<bin.at(ivar)<<std::endl;	
	vROC.push_back(new TGraph(bin.at(ivar)));
// 	for(int ibin=0;ibin<bin.at(ivar)+1;ibin++){
	for(int ibin=1;ibin<bin.at(ivar)+1;ibin++){
		float sig_temp=hsig.at(ivar)->Integral(ibin,bin.at(ivar));
		float bkg_temp=hbkg_tot.at(ivar)->Integral(ibin,bin.at(ivar));
		sig_eff.push_back(sig_temp);
		bkg_eff.push_back(bkg_temp);
		//std::cout << "	bin:"<<ibin<<std::endl;	
		//std::cout << "		sig:"<<  sig_temp <<std::endl;	
		//std::cout << "		bkg:"<<  bkg_temp <<std::endl;	
		vROC.at(ivar)->SetPoint(ibin,sig_temp,1-bkg_temp);
		vROC.at(ivar)->SetLineColor((ivar+1));
		if((ivar+1)>=5){
			vROC.at(ivar)->SetLineColor((ivar+2));
			if(ivar+2>=10){
				vROC.at(ivar)->SetLineColor((ivar+3));
				//std::cout <<var.at(ivar)<< " --> color :"<<ivar+3<<std::endl;
			}
		}
	}
	mgROC->Add(vROC.at(ivar));
	
	l->AddEntry(vROC.at(ivar),var.at(ivar),"l");
	
	if( hsig.at(ivar)->Integral()==0 || hbkg_tot.at(ivar)->Integral()==0){
		std::cout << "---> either sig or bkg integral is 0 so not saving plot. !!"<< std::endl;
	}
	else{
		c->SaveAs(folder+"/"+var.at(ivar)+"_"+sigStr+"_"+ch+"_"+bkgStr+"_"+cutName+".pdf");	
	}

  }
  
  mgROC->Draw("AL");
  mgROC->SetTitle(ch);
  mgROC->GetXaxis()->SetTitle(sigStr+" efficiency");
  mgROC->GetYaxis()->SetTitle(bkgStr+" 1-efficiency");
  l->Draw();
  
  cROC->SaveAs(folder+"/"+sigStr+"_"+ch+"_"+bkgStr+"_"+cutName+"_ROC.pdf");
  
}


void plotThings(){

  //sig
  
  std::vector<TString> sigStr;
  sigStr.push_back("TT1000");
//   sigStr.push_back("TT1200");
//   sigStr.push_back("TT1400");
//   sigStr.push_back("TT1600");
  TFile *fsig;

  std::vector <TString> bkgStr;
  std::vector<std::vector<float > > bkg_xs;
  std::vector<std::vector<TFile*> > fbkg;  
  
  //ttbar

  bkgStr.push_back("ttbar");

  std::vector< float > ttbar_xs;
  ttbar_xs.push_back(832);
  bkg_xs.push_back(ttbar_xs);

  std::vector< TFile *> fbkg_ttbar;
//   fbkg_ttbar.push_back(TFile::Open("test_ttbar_1.root"));
  fbkg_ttbar.push_back(TFile::Open("test_ttbar.root"));
//   fbkg_ttbar.push_back(TFile::Open("root://cmseos.fnal.gov://store/user/lpcljm/2016/LJMet80X_1lep_XCone_2018_1_18_and_2018_1_26_and_2018_1_29_rizki_step1_v2_hadds/nominal/TT_Mtt-1000toInf_TuneCUETP8M2T4_13TeV-powheg-pythia8_hadd.root"));
//   fbkg_ttbar.push_back(TFile::Open("root://cmseos.fnal.gov://store/user/lpcljm/2016/LJMet80X_1lep_XCone_2018_1_18_and_2018_1_26_and_2018_1_29_rizki_step1_v2_hadds/nominal/TT_Mtt-700to1000_TuneCUETP8M2T4_13TeV-powheg-pythia8_hadd.root"));
//   fbkg_ttbar.push_back(TFile::Open("root://cmseos.fnal.gov://store/user/lpcljm/2016/LJMet80X_1lep_XCone_2018_1_18_and_2018_1_26_and_2018_1_29_rizki_step1_v2_hadds/nominal/TT_TuneCUETP8M2T4_backup_13TeV-powheg-pythia8_Mtt0to700_hadd.root"));
//   fbkg_ttbar.push_back(TFile::Open("root://cmseos.fnal.gov://store/user/lpcljm/2016/LJMet80X_1lep_XCone_2018_1_18_and_2018_1_26_and_2018_1_29_rizki_step1_v2_hadds/nominal/TT_TuneCUETP8M2T4_backup_13TeV-powheg-pythia8_Mtt1000toInf_hadd.root"));
//   fbkg_ttbar.push_back(TFile::Open("root://cmseos.fnal.gov://store/user/lpcljm/2016/LJMet80X_1lep_XCone_2018_1_18_and_2018_1_26_and_2018_1_29_rizki_step1_v2_hadds/nominal/TT_TuneCUETP8M2T4_backup_13TeV-powheg-pythia8_Mtt700to1000_hadd.root"));
//   fbkg_ttbar.push_back(TFile::Open("root://cmseos.fnal.gov://store/user/lpcljm/2016/LJMet80X_1lep_XCone_2018_1_18_and_2018_1_26_and_2018_1_29_rizki_step1_v2_hadds/nominal/TT_TuneCUETP8M2T4_v1_13TeV-powheg-pythia8_Mtt0to700_hadd.root"));
//   fbkg_ttbar.push_back(TFile::Open("root://cmseos.fnal.gov://store/user/lpcljm/2016/LJMet80X_1lep_XCone_2018_1_18_and_2018_1_26_and_2018_1_29_rizki_step1_v2_hadds/nominal/TT_TuneCUETP8M2T4_v1_13TeV-powheg-pythia8_Mtt1000toInf_hadd.root"));
//   fbkg_ttbar.push_back(TFile::Open("root://cmseos.fnal.gov://store/user/lpcljm/2016/LJMet80X_1lep_XCone_2018_1_18_and_2018_1_26_and_2018_1_29_rizki_step1_v2_hadds/nominal/TT_TuneCUETP8M2T4_v1_13TeV-powheg-pythia8_Mtt700to1000_hadd.root"));
  fbkg.push_back(fbkg_ttbar);

  //wjets

//   bkgStr.push_back("wjets");
// 
//   std::vector< float > wjets_xs;
//   wjets_xs.push_back(0.03216*1.21);
//   wjets_xs.push_back(1.329*1.21);
//   wjets_xs.push_back(5.501*1.21);
//   wjets_xs.push_back(12.05*1.21);
//   wjets_xs.push_back(48.91*1.21);
//   bkg_xs.push_back(wjets_xs);
// 
//   std::vector< TFile *> fbkg_wjets;
//   fbkg_wjets.push_back(TFile::Open("test_wjets2500.root"));
//   fbkg_wjets.push_back(TFile::Open("test_wjets1200.root"));
//   fbkg_wjets.push_back(TFile::Open("test_wjets800.root"));
//   fbkg_wjets.push_back(TFile::Open("test_wjets600.root"));
//   fbkg_wjets.push_back(TFile::Open("test_wjets400.root"));
//   fbkg.push_back(fbkg_wjets);

  //ewk =  wjets+ww+DY

//   bkgStr.push_back("ewk");
// 
//   std::vector< float > ewk_xs;
//   ewk_xs.push_back(0.03216*1.21);
//   ewk_xs.push_back(1.329*1.21);
//   ewk_xs.push_back(5.501*1.21);
//   ewk_xs.push_back(12.05*1.21);
//   ewk_xs.push_back(48.91*1.21);
//   ewk_xs.push_back(359.7*1.21);
//   ewk_xs.push_back(5765);
//   ewk_xs.push_back(118.7);
//   bkg_xs.push_back(ewk_xs);
// 
//   std::vector< TFile *> fbkg_ewk;
//   fbkg_ewk.push_back(TFile::Open("test_wjets2500.root"));
//   fbkg_ewk.push_back(TFile::Open("test_wjets1200.root"));
//   fbkg_ewk.push_back(TFile::Open("test_wjets800.root"));
//   fbkg_ewk.push_back(TFile::Open("test_wjets600.root"));
//   fbkg_ewk.push_back(TFile::Open("test_wjets400.root"));
//   fbkg_ewk.push_back(TFile::Open("test_wjets200.root"));
//   fbkg_ewk.push_back(TFile::Open("test_DY.root")); //--> need stats!!
//   fbkg_ewk.push_back(TFile::Open("test_ww.root")); //-- need stats!!
//   fbkg.push_back(fbkg_ewk);

  //tteek =  ttbar+wjets+ww+DY

//   bkgStr.push_back("ttewk");
// 
//   std::vector< float > ttewk_xs; //actually xs / total_event
//   ttewk_xs.push_back(0.03216*1.21);
//   ttewk_xs.push_back(1.329*1.21);
//   ttewk_xs.push_back(5.501*1.21);
//   ttewk_xs.push_back(12.05*1.21);
//   ttewk_xs.push_back(48.91*1.21);
//   ttewk_xs.push_back(359.7*1.21);
//   ttewk_xs.push_back(5765 / 96658943);
//   ttewk_xs.push_back(118.7);
//   ttewk_xs.push_back(832);
//   bkg_xs.push_back(ttewk_xs);
// 
//   std::vector< TFile *> fbkg_ttewk;
//   fbkg_ttewk.push_back(TFile::Open("test_wjets2500.root"));
//   fbkg_ttewk.push_back(TFile::Open("test_wjets1200.root"));
//   fbkg_ttewk.push_back(TFile::Open("test_wjets800.root"));
//   fbkg_ttewk.push_back(TFile::Open("test_wjets600.root"));
//   fbkg_ttewk.push_back(TFile::Open("test_wjets400.root"));
//   fbkg_ttewk.push_back(TFile::Open("test_wjets200.root"));
//   fbkg_ttewk.push_back(TFile::Open("test_DY.root")); //--> need stats!!
//   fbkg_ttewk.push_back(TFile::Open("test_ww.root")); //-- need stats!!
//   fbkg_ttewk.push_back(TFile::Open("test_ttbar.root")); //-- need stats!!
//   fbkg.push_back(fbkg_ttewk);


  std::vector<TString> ch;

  ch.push_back("isBWBW_TpTpCalc");
  ch.push_back("isTHBW_TpTpCalc");
  ch.push_back("isTZBW_TpTpCalc");
  ch.push_back("isTZTH_TpTpCalc");
  ch.push_back("isTHTH_TpTpCalc");
  ch.push_back("isTZTZ_TpTpCalc");

  std::vector<TString> cut, cutName;
  cut.push_back("(leptonPt_singleLepCalc > 60) && (corr_met_singleLepCalc > 75) && (theJetPt_JetSubCalc_PtOrdered[0] > 300) && (theJetPt_JetSubCalc_PtOrdered[1] > 150) && (theJetPt_JetSubCalc_PtOrdered[2] > 100) && (minDR_lepJet > 0.4 || ptRel_lepJet > 40) && (NJetsAK8_JetSubCalc >= 2) && (minDR_leadAK8otherAK8 > 0.8 && minDR_leadAK8otherAK8 < 3.0) && DataPastTriggerOR == 1 && NJetsH1btagged==0 && NJetsH2btagged==0 && NJetsWtagged_0p6==0 && NJets_JetSubCalc >=4 && NJetsCSVwithSF_JetSubCalc==1 && NJets_JetSubCalc>=3");
  cutName.push_back("H0W0b1");
  cut.push_back("(leptonPt_singleLepCalc > 60) && (corr_met_singleLepCalc > 75) && (theJetPt_JetSubCalc_PtOrdered[0] > 300) && (theJetPt_JetSubCalc_PtOrdered[1] > 150) && (theJetPt_JetSubCalc_PtOrdered[2] > 100) && (minDR_lepJet > 0.4 || ptRel_lepJet > 40) && (NJetsAK8_JetSubCalc >= 2) && (minDR_leadAK8otherAK8 > 0.8 && minDR_leadAK8otherAK8 < 3.0) && DataPastTriggerOR == 1 && NJetsH1btagged==0 && NJetsH2btagged==0 && NJetsWtagged_0p6==0 && NJets_JetSubCalc >=4 && NJetsCSVwithSF_JetSubCalc==2 && NJets_JetSubCalc>=3");
  cutName.push_back("H0W0b2");
  cut.push_back("(leptonPt_singleLepCalc > 60) && (corr_met_singleLepCalc > 75) && (theJetPt_JetSubCalc_PtOrdered[0] > 300) && (theJetPt_JetSubCalc_PtOrdered[1] > 150) && (theJetPt_JetSubCalc_PtOrdered[2] > 100) && (minDR_lepJet > 0.4 || ptRel_lepJet > 40) && (NJetsAK8_JetSubCalc >= 2) && (minDR_leadAK8otherAK8 > 0.8 && minDR_leadAK8otherAK8 < 3.0) && DataPastTriggerOR == 1 && NJetsH1btagged==0 && NJetsH2btagged==0 && NJetsWtagged_0p6==0 && NJets_JetSubCalc >=4 && NJetsCSVwithSF_JetSubCalc>=3 && NJets_JetSubCalc>=3");
  cutName.push_back("H0W0b3p");
  cut.push_back("(leptonPt_singleLepCalc > 60) && (corr_met_singleLepCalc > 75) && (theJetPt_JetSubCalc_PtOrdered[0] > 300) && (theJetPt_JetSubCalc_PtOrdered[1] > 150) && (theJetPt_JetSubCalc_PtOrdered[2] > 100) && (minDR_lepJet > 0.4 || ptRel_lepJet > 40) && (NJetsAK8_JetSubCalc >= 2) && (minDR_leadAK8otherAK8 > 0.8 && minDR_leadAK8otherAK8 < 3.0) && DataPastTriggerOR == 1 && NJetsH1btagged==0 && NJetsH2btagged==0 && NJetsWtagged_0p6>=1 && NJetsCSVwithSF_JetSubCalc==1 && NJets_JetSubCalc>=3");
  cutName.push_back("H0W1pb1");
  cut.push_back("(leptonPt_singleLepCalc > 60) && (corr_met_singleLepCalc > 75) && (theJetPt_JetSubCalc_PtOrdered[0] > 300) && (theJetPt_JetSubCalc_PtOrdered[1] > 150) && (theJetPt_JetSubCalc_PtOrdered[2] > 100) && (minDR_lepJet > 0.4 || ptRel_lepJet > 40) && (NJetsAK8_JetSubCalc >= 2) && (minDR_leadAK8otherAK8 > 0.8 && minDR_leadAK8otherAK8 < 3.0) && DataPastTriggerOR == 1 && NJetsH1btagged==0 && NJetsH2btagged==0 && NJetsWtagged_0p6>=1 && NJetsCSVwithSF_JetSubCalc==2 && NJets_JetSubCalc>=3");
  cutName.push_back("H0W1pb2");
  cut.push_back("(leptonPt_singleLepCalc > 60) && (corr_met_singleLepCalc > 75) && (theJetPt_JetSubCalc_PtOrdered[0] > 300) && (theJetPt_JetSubCalc_PtOrdered[1] > 150) && (theJetPt_JetSubCalc_PtOrdered[2] > 100) && (minDR_lepJet > 0.4 || ptRel_lepJet > 40) && (NJetsAK8_JetSubCalc >= 2) && (minDR_leadAK8otherAK8 > 0.8 && minDR_leadAK8otherAK8 < 3.0) && DataPastTriggerOR == 1 && NJetsH1btagged==0 && NJetsH2btagged==0 && NJetsWtagged_0p6>=1 && NJetsCSVwithSF_JetSubCalc>=3 && NJets_JetSubCalc>=3");
  cutName.push_back("H0W1pb3p");
  cut.push_back("(leptonPt_singleLepCalc > 60) && (corr_met_singleLepCalc > 75) && (theJetPt_JetSubCalc_PtOrdered[0] > 300) && (theJetPt_JetSubCalc_PtOrdered[1] > 150) && (theJetPt_JetSubCalc_PtOrdered[2] > 100) && (minDR_lepJet > 0.4 || ptRel_lepJet > 40) && (NJetsAK8_JetSubCalc >= 2) && (minDR_leadAK8otherAK8 > 0.8 && minDR_leadAK8otherAK8 < 3.0) && DataPastTriggerOR == 1 && NJetsH1btagged> 0 && NJetsH2btagged==0 && (((NJetsWtagged_0p6 > 0 || NJetsH1btagged > 0 || NJetsH2btagged > 0) && NJets_JetSubCalc >= 3) || ((NJetsWtagged_0p6 == 0 && NJetsH1btagged == 0 && NJetsH2btagged == 0) && NJets_JetSubCalc >= 4)) && NJetsCSVnotH_JetSubCalc >= 1 && NJets_JetSubCalc>=3");
  cutName.push_back("H1bW0pb1p");
  cut.push_back("(leptonPt_singleLepCalc > 60) && (corr_met_singleLepCalc > 75) && (theJetPt_JetSubCalc_PtOrdered[0] > 300) && (theJetPt_JetSubCalc_PtOrdered[1] > 150) && (theJetPt_JetSubCalc_PtOrdered[2] > 100) && (minDR_lepJet > 0.4 || ptRel_lepJet > 40) && (NJetsAK8_JetSubCalc >= 2) && (minDR_leadAK8otherAK8 > 0.8 && minDR_leadAK8otherAK8 < 3.0) && DataPastTriggerOR == 1 && NJetsH2btagged> 0 && (((NJetsWtagged_0p6 > 0 || NJetsH1btagged > 0 || NJetsH2btagged > 0) && NJets_JetSubCalc >= 3) || ((NJetsWtagged_0p6 == 0 && NJetsH1btagged == 0 && NJetsH2btagged == 0) && NJets_JetSubCalc >= 4)) && NJetsCSVnotH_JetSubCalc >= 1 && NJets_JetSubCalc>=3");
  cutName.push_back("H2bW0pb1p");

  cut.push_back("(leptonPt_singleLepCalc > 60) && (corr_met_singleLepCalc > 75) && (theJetPt_JetSubCalc_PtOrdered[0] > 300) && (theJetPt_JetSubCalc_PtOrdered[1] > 150) && (theJetPt_JetSubCalc_PtOrdered[2] > 100) && (minDR_lepJet > 0.4 || ptRel_lepJet > 40) && (NJetsAK8_JetSubCalc >= 2) && (minDR_leadAK8otherAK8 > 0.8 && minDR_leadAK8otherAK8 < 3.0) && DataPastTriggerOR == 1 && NJetsH1btagged==0 && NJetsH2btagged==0 && NJetsWtagged_0p6==0 && NJets_JetSubCalc >=4 && NJetsCSVwithSF_JetSubCalc==1 && NJets_JetSubCalc>=3 && NXConeJets>=5");
  cutName.push_back("H0W0b1X5");
  cut.push_back("(leptonPt_singleLepCalc > 60) && (corr_met_singleLepCalc > 75) && (theJetPt_JetSubCalc_PtOrdered[0] > 300) && (theJetPt_JetSubCalc_PtOrdered[1] > 150) && (theJetPt_JetSubCalc_PtOrdered[2] > 100) && (minDR_lepJet > 0.4 || ptRel_lepJet > 40) && (NJetsAK8_JetSubCalc >= 2) && (minDR_leadAK8otherAK8 > 0.8 && minDR_leadAK8otherAK8 < 3.0) && DataPastTriggerOR == 1 && NJetsH1btagged==0 && NJetsH2btagged==0 && NJetsWtagged_0p6==0 && NJets_JetSubCalc >=4 && NJetsCSVwithSF_JetSubCalc==2 && NJets_JetSubCalc>=3 && NXConeJets>=5");
  cutName.push_back("H0W0b2X5");
  cut.push_back("(leptonPt_singleLepCalc > 60) && (corr_met_singleLepCalc > 75) && (theJetPt_JetSubCalc_PtOrdered[0] > 300) && (theJetPt_JetSubCalc_PtOrdered[1] > 150) && (theJetPt_JetSubCalc_PtOrdered[2] > 100) && (minDR_lepJet > 0.4 || ptRel_lepJet > 40) && (NJetsAK8_JetSubCalc >= 2) && (minDR_leadAK8otherAK8 > 0.8 && minDR_leadAK8otherAK8 < 3.0) && DataPastTriggerOR == 1 && NJetsH1btagged==0 && NJetsH2btagged==0 && NJetsWtagged_0p6==0 && NJets_JetSubCalc >=4 && NJetsCSVwithSF_JetSubCalc>=3 && NJets_JetSubCalc>=3 && NXConeJets>=5");
  cutName.push_back("H0W0b3pX5");
  cut.push_back("(leptonPt_singleLepCalc > 60) && (corr_met_singleLepCalc > 75) && (theJetPt_JetSubCalc_PtOrdered[0] > 300) && (theJetPt_JetSubCalc_PtOrdered[1] > 150) && (theJetPt_JetSubCalc_PtOrdered[2] > 100) && (minDR_lepJet > 0.4 || ptRel_lepJet > 40) && (NJetsAK8_JetSubCalc >= 2) && (minDR_leadAK8otherAK8 > 0.8 && minDR_leadAK8otherAK8 < 3.0) && DataPastTriggerOR == 1 && NJetsH1btagged==0 && NJetsH2btagged==0 && NJetsWtagged_0p6>=1 && NJetsCSVwithSF_JetSubCalc==1 && NJets_JetSubCalc>=3 && NXConeJets>=5");
  cutName.push_back("H0W1pb1X5");
  cut.push_back("(leptonPt_singleLepCalc > 60) && (corr_met_singleLepCalc > 75) && (theJetPt_JetSubCalc_PtOrdered[0] > 300) && (theJetPt_JetSubCalc_PtOrdered[1] > 150) && (theJetPt_JetSubCalc_PtOrdered[2] > 100) && (minDR_lepJet > 0.4 || ptRel_lepJet > 40) && (NJetsAK8_JetSubCalc >= 2) && (minDR_leadAK8otherAK8 > 0.8 && minDR_leadAK8otherAK8 < 3.0) && DataPastTriggerOR == 1 && NJetsH1btagged==0 && NJetsH2btagged==0 && NJetsWtagged_0p6>=1 && NJetsCSVwithSF_JetSubCalc==2 && NJets_JetSubCalc>=3 && NXConeJets>=5");
  cutName.push_back("H0W1pb2X5");
  cut.push_back("(leptonPt_singleLepCalc > 60) && (corr_met_singleLepCalc > 75) && (theJetPt_JetSubCalc_PtOrdered[0] > 300) && (theJetPt_JetSubCalc_PtOrdered[1] > 150) && (theJetPt_JetSubCalc_PtOrdered[2] > 100) && (minDR_lepJet > 0.4 || ptRel_lepJet > 40) && (NJetsAK8_JetSubCalc >= 2) && (minDR_leadAK8otherAK8 > 0.8 && minDR_leadAK8otherAK8 < 3.0) && DataPastTriggerOR == 1 && NJetsH1btagged==0 && NJetsH2btagged==0 && NJetsWtagged_0p6>=1 && NJetsCSVwithSF_JetSubCalc>=3 && NJets_JetSubCalc>=3 && NXConeJets>=5");
  cutName.push_back("H0W1pb3pX5");
  cut.push_back("(leptonPt_singleLepCalc > 60) && (corr_met_singleLepCalc > 75) && (theJetPt_JetSubCalc_PtOrdered[0] > 300) && (theJetPt_JetSubCalc_PtOrdered[1] > 150) && (theJetPt_JetSubCalc_PtOrdered[2] > 100) && (minDR_lepJet > 0.4 || ptRel_lepJet > 40) && (NJetsAK8_JetSubCalc >= 2) && (minDR_leadAK8otherAK8 > 0.8 && minDR_leadAK8otherAK8 < 3.0) && DataPastTriggerOR == 1 && NJetsH1btagged> 0 && NJetsH2btagged==0 && (((NJetsWtagged_0p6 > 0 || NJetsH1btagged > 0 || NJetsH2btagged > 0) && NJets_JetSubCalc >= 3) || ((NJetsWtagged_0p6 == 0 && NJetsH1btagged == 0 && NJetsH2btagged == 0) && NJets_JetSubCalc >= 4)) && NJetsCSVnotH_JetSubCalc >= 1 && NJets_JetSubCalc>=3 && NXConeJets>=5");
  cutName.push_back("H1bW0pb1pX5");
  cut.push_back("(leptonPt_singleLepCalc > 60) && (corr_met_singleLepCalc > 75) && (theJetPt_JetSubCalc_PtOrdered[0] > 300) && (theJetPt_JetSubCalc_PtOrdered[1] > 150) && (theJetPt_JetSubCalc_PtOrdered[2] > 100) && (minDR_lepJet > 0.4 || ptRel_lepJet > 40) && (NJetsAK8_JetSubCalc >= 2) && (minDR_leadAK8otherAK8 > 0.8 && minDR_leadAK8otherAK8 < 3.0) && DataPastTriggerOR == 1 && NJetsH2btagged> 0 && (((NJetsWtagged_0p6 > 0 || NJetsH1btagged > 0 || NJetsH2btagged > 0) && NJets_JetSubCalc >= 3) || ((NJetsWtagged_0p6 == 0 && NJetsH1btagged == 0 && NJetsH2btagged == 0) && NJets_JetSubCalc >= 4)) && NJetsCSVnotH_JetSubCalc >= 1 && NJets_JetSubCalc>=3 && NXConeJets>=5");
  cutName.push_back("H2bW0pb1pX5");

  cut.push_back("");
  cutName.push_back("NoCut");
  
  std::vector<TString> vvar;
  std::vector<int> vbin;
  std::vector<float> vxmin;
  std::vector<float> vxmax;
  vvar.push_back("NJets_JetSubCalc");
  vbin.push_back(15);
  vxmin.push_back(-0.5);
  vxmax.push_back(14.5);
  vvar.push_back("NXConeJets");
  vbin.push_back(15);
  vxmin.push_back(-0.5);
  vxmax.push_back(14.5);
  vvar.push_back("AK4HTpMETpLepPt");
  vbin.push_back(50);
  vxmin.push_back(0);
  vxmax.push_back(5000);
  vvar.push_back("minMleppBjet");
  vbin.push_back(50);
  vxmin.push_back(0);
  vxmax.push_back(1000);
  vvar.push_back("maxMlep3XConeJets");
  vbin.push_back(50);
  vxmin.push_back(0);
  vxmax.push_back(5000);
//   vvar.push_back("Mlep3closeXConeJets");
//   vbin.push_back(50);
//   vxmin.push_back(0);
//   vxmax.push_back(2000);
//   vvar.push_back("TcandAveMass0");
//   vbin.push_back(50);
//   vxmin.push_back(0);
//   vxmax.push_back(2000);
//   vvar.push_back("TcandAveMass1");
//   vbin.push_back(50);
//   vxmin.push_back(0);
//   vxmax.push_back(2000);
//   vvar.push_back("TcandAveMass2");
//   vbin.push_back(50);
//   vxmin.push_back(0);
//   vxmax.push_back(2000);
//   vvar.push_back("Tcand1Mass0");
//   vbin.push_back(50);
//   vxmin.push_back(0);
//   vxmax.push_back(2000);
//   vvar.push_back("Tcand1Mass1");
//   vbin.push_back(50);
//   vxmin.push_back(0);
//   vxmax.push_back(2000);
//   vvar.push_back("Tcand1Mass2");
//   vbin.push_back(50);
//   vxmin.push_back(0);
//   vxmax.push_back(2000);
//   vvar.push_back("Tcand2Mass0");
//   vbin.push_back(50);
//   vxmin.push_back(0);
//   vxmax.push_back(2000);
//   vvar.push_back("Tcand2Mass1");
//   vbin.push_back(50);
//   vxmin.push_back(0);
//   vxmax.push_back(2000);
//   vvar.push_back("Tcand2Mass2");
//   vbin.push_back(50);
//   vxmin.push_back(0);
//   vxmax.push_back(2000);
  vvar.push_back("MassWcand1BTagXCone");
  vbin.push_back(50);
  vxmin.push_back(0);
  vxmax.push_back(2000);
  vvar.push_back("MassWcand2BTagXCone");
  vbin.push_back(50);
  vxmin.push_back(0);
  vxmax.push_back(2000);
  vvar.push_back("Mass1XCone123");
  vbin.push_back(50);
  vxmin.push_back(0);
  vxmax.push_back(2000);
  vvar.push_back("Mass2XCone123");
  vbin.push_back(50);
  vxmin.push_back(0);
  vxmax.push_back(2000);
  vvar.push_back("M_WcandBTagXCone_XCone123");
  vbin.push_back(50);
  vxmin.push_back(0);
  vxmax.push_back(5000);

  
  for(int sig=0; sig<sigStr.size();sig++){
  	fsig = TFile::Open("test_"+sigStr.at(sig)+".root");
//   	fsig = TFile::Open("test_"+sigStr.at(sig)+"_1.root");
  	for(int bkg=0; bkg<bkgStr.size();bkg++){
  		for(int i=0; i<ch.size();i++){

// 		  plotThings(sigStr.at(sig),fsig,bkgStr.at(bkg),fbkg.at(bkg),bkg_xs.at(bkg),"deltaR_lepXConeJets[0]",50,-1,6,ch.at(i));
// 		  plotThings(sigStr.at(sig),fsig,bkgStr.at(bkg),fbkg.at(bkg),bkg_xs.at(bkg),"deltaR_lepXConeJets[1]",50,-1,6,ch.at(i));
// 		  plotThings(sigStr.at(sig),fsig,bkgStr.at(bkg),fbkg.at(bkg),bkg_xs.at(bkg),"deltaR_lepXConeJets[2]",50,-1,6,ch.at(i));
// 		  plotThings(sigStr.at(sig),fsig,bkgStr.at(bkg),fbkg.at(bkg),bkg_xs.at(bkg),"deltaR_lepXConeJets[3]",50,-1,6,ch.at(i));
// 		  plotThings(sigStr.at(sig),fsig,bkgStr.at(bkg),fbkg.at(bkg),bkg_xs.at(bkg),"AK4HTpMETpLepPt",50,0,5000,ch.at(i));
// 		  plotThings(sigStr.at(sig),fsig,bkgStr.at(bkg),fbkg.at(bkg),bkg_xs.at(bkg),"maxMlep3XConeJets",50,0,5000,ch.at(i));
// 		  plotThings(sigStr.at(sig),fsig,bkgStr.at(bkg),fbkg.at(bkg),bkg_xs.at(bkg),"Mlep3closeXConeJets",50,0,2000,ch.at(i));
// 		  plotThings(sigStr.at(sig),fsig,bkgStr.at(bkg),fbkg.at(bkg),bkg_xs.at(bkg),"minMleppBjet",50,0,1000,ch.at(i));
// 		  plotThings(sigStr.at(sig),fsig,bkgStr.at(bkg),fbkg.at(bkg),bkg_xs.at(bkg),"NXConeJets",15,-0.5,14.5,ch.at(i));

  			for(int icut=0; icut<cut.size();icut++){  		
  				plotThings_ROC(sigStr.at(sig),fsig,bkgStr.at(bkg),fbkg.at(bkg),bkg_xs.at(bkg),vvar,vbin,vxmin,vxmax,ch.at(i),cut.at(icut),cutName.at(icut));
   			}		  
  		}
  	}
  }
  
gApplication->Terminate();

}

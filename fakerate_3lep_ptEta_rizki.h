#ifndef _FAKERATE_H
#define _FAKERATE_H
#include <TRandom2.h>
#include "Math/Random.h"
#include <iostream>
// #include "CMSStyle.C"

#include "TStyle.h"
#include "TColor.h"
#include "TFile.h"
#include <TH1F.h>
#include <TH2.h>
#include "TCanvas.h"

using namespace std;

bool DEBUGfakerate_h = false;

float Pr(int mode,std::vector<double> lep_info);
inline float uPr(std::vector<double> lep_info);
float Fr(int mode,std::vector<double> lep_info);
inline float uFr(std::vector<double> lep_info);

inline float uQe();

inline double epsilon(double f);//these are guearenteed to be small numbers
inline double eta(double p);//these are guearenteed to be small numbers

inline int frModeBehavior(int mode,int flavour);
inline int prModeBehavior(int mode,int flavour);
inline int qeModeBehavior(int mode);


std::vector<double> SF3Lepbkg(double f, double p, int N_t0, int N_t1, int N_t2, int N_t3);
	//output: {0:N_ppp, 1:N_fpp, 2:N_ffp, 3:N_fff, 4:N_signal, 5:N_1fake, 6:N_2fakes, 7:N_3fakes, 8:N_bkg}
double SF3Lepbkg_simple(double f, double p, int N_t0, int N_t1, int N_t2, int N_t3);

// double ChiSquared(int k); //what are these for??
// int ThrowPoissonFromMeasurement(TRandom2* r, int n); //what are these for??


/////////////////// Tripple electron ////////////////////////
double GetWeight(int mode, std::vector<double> lep1_info, std::vector<double> lep2_info, std::vector<double> lep3_info);

double W_ttt(int mode, std::vector<double> lep1_info, std::vector<double> lep2_info, std::vector<double> lep3_info );
double W_ttl(int mode, std::vector<double> lep1_info, std::vector<double> lep2_info, std::vector<double> lep3_info );
double W_tlt(int mode, std::vector<double> lep1_info, std::vector<double> lep2_info, std::vector<double> lep3_info );
double W_ltt(int mode, std::vector<double> lep1_info, std::vector<double> lep2_info, std::vector<double> lep3_info );
double W_tll(int mode, std::vector<double> lep1_info, std::vector<double> lep2_info, std::vector<double> lep3_info );
double W_ltl(int mode, std::vector<double> lep1_info, std::vector<double> lep2_info, std::vector<double> lep3_info );
double W_llt(int mode, std::vector<double> lep1_info, std::vector<double> lep2_info, std::vector<double> lep3_info );
double W_lll(int mode, std::vector<double> lep1_info, std::vector<double> lep2_info, std::vector<double> lep3_info );

/////////////////////////////
// 
// // TFile* file_el = TFile::Open("/uscms_data/d3/rsyarif/Spring2016/TprimeFakeRateReproduce/FromJulie/CMSSW_7_4_14/src/LJMet/macros/step1/FakeRatePlots/FakeRate_Data_subtr_El_PtEta.root");
// // TFile* file_mu = TFile::Open("/uscms_data/d3/rsyarif/Spring2016/TprimeFakeRateReproduce/FromJulie/CMSSW_7_4_14/src/LJMet/macros/step1/FakeRatePlots/FakeRate_Data_subtr_Mu_PtEta.root");
// 
// TFile* file_el = TFile::Open("/uscms_data/d3/rsyarif/Spring2016/TprimeFakeRateReproduce/FromJulie/CMSSW_7_4_14/src/LJMet/macros/step1/FakeRateFiles/withWJetsIncl_subtrDenom/FakeRate_Data_subtr_El_PtEta.root");
// TFile* file_mu = TFile::Open("/uscms_data/d3/rsyarif/Spring2016/TprimeFakeRateReproduce/FromJulie/CMSSW_7_4_14/src/LJMet/macros/step1/FakeRateFiles/withWJetsIncl_subtrDenom/FakeRate_Data_subtr_Mu_PtEta.root");
// 
// // TFile* file_el = TFile::Open("/uscms_data/d3/rsyarif/Spring2016/TprimeFakeRateReproduce/FromJulie/CMSSW_7_4_14/src/LJMet/macros/step1/FakeRateFiles/withWJetsIncl_subtrDenom/FakeRate_Data_subtr_El_Pt_1bin.root");
// // TFile* file_mu = TFile::Open("/uscms_data/d3/rsyarif/Spring2016/TprimeFakeRateReproduce/FromJulie/CMSSW_7_4_14/src/LJMet/macros/step1/FakeRateFiles/withWJetsIncl_subtrDenom/FakeRate_Data_subtr_Mu_Pt_1bin.root");
// 
// 
// TCanvas* c_el = (TCanvas*) file_el->Get("c1");
// TCanvas* c_mu = (TCanvas*) file_mu->Get("c1");
// TH2D *h_el = (TH2D*) c_el->GetPrimitive("newratioEl");
// TH2D *h_mu = (TH2D*) c_mu->GetPrimitive("newratioMu");


float Pr(int mode, std::vector<double> lep_info){
	if(lep_info.at(0)==0){
		//ele prompt rate
		double pt_el = lep_info.at(2);
		double eta_el = lep_info.at(3);
		double weight = 0.0;

		//PRv5test, PRv7test, PRvElPRtest - to see how el fr affects things.
// 		weight = 1.0;
// 		return weight;

		//PRv6, PRv8test - from Clint https://mail.google.com/mail/u/0/#search/clint/159dc97c5d3fb221
		/* as given by Clint
		[1]
		30 < pt < 40 = 0.881
		40 < pt < 50 = 0.918
		50 < pt < 60 = 0.931
		60 < pt < 70 = 0.940
		70 < pt         = 0.950
		*/
// 		if(pt_el>=30. && pt_el < 40.) weight = 0.881;
//         else if(pt_el<50) weight = 0.918;
//         else if(pt_el<60) weight = 0.931;
//         else if(pt_el<70)weight = 0.940;
//         else weight = 0.950;
// 		//if(DEBUGfakerate_h)std::cout << "elPR used (mode:"<<mode<<") = " << weight << " + " << "("<<prModeBehavior(mode)<<")"<<uPr(lep_info)<< std::endl;
// 		if(DEBUGfakerate_h)std::cout << "Ele PR -- Mode: " << mode << ", " << weight <<" + "<< prModeBehavior(mode,lep_info.at(0)) <<  " * " << uPr(lep_info)<< endl;
// 		return weight + uPr(lep_info)*prModeBehavior(mode,lep_info.at(0));

		//PRvMuPRtest,PRv9 from http://cms.cern.ch/iCMS/jsp/db_notes/noteInfo.jsp?cmsnoteid=CMS%20AN-2016/242 v16
		if(pt_el>=30. && pt_el < 40.) weight = 0.904;
        else if(pt_el<50) weight = 0.928;
        else if(pt_el<60) weight = 0.934;
        else if(pt_el<70) weight = 0.942;
        else if(pt_el<80) weight = 0.947;
        else if(pt_el<90) weight = 0.953;
        else if(pt_el<100) weight = 0.955;
        else if(pt_el<125) weight = 0.948;
        else if(pt_el<150) weight = 0.951;
        else if(pt_el<200) weight = 0.946;
        else if(pt_el<300) weight = 0.935;
        else if(pt_el<400) weight = 0.920;
        else if(pt_el<500) weight = 0.902;
        else weight = 0.800;
		//if(DEBUGfakerate_h)std::cout << "elPR used (mode:"<<mode<<") = " << weight << " + " << "("<<prModeBehavior(mode)<<")"<<uPr(lep_info)<< std::endl;
		if(DEBUGfakerate_h)std::cout << "Ele PR -- Mode: " << mode << ", " << weight <<" + "<< prModeBehavior(mode,lep_info.at(0)) <<  " * " << uPr(lep_info)<< endl;
		return weight + uPr(lep_info)*prModeBehavior(mode,lep_info.at(0));

		//PRv10 from http://home.fnal.gov/~souvik/Work/VLQ/IFTABLE_VLQ_PromptRate_ee_OS.c , https://mail.google.com/mail/u/0/#sent/15c957c688a0ff96
// 		double error=0.0;
// 		if (eta_el<-2.4) eta_el=-2.4;
// 		if (eta_el>2.4) eta_el=2.4;
// 		if (pt_el<20) pt_el=20;
// 		if (pt_el>200) pt_el=200;
// 		if (-2.4<=eta_el && eta_el<=-2.1)
// 		{
// 			if (30<=pt_el && pt_el<=35) {error=0.0158699; weight = 0.674312;}
// 			if (35<=pt_el && pt_el<=40) {error=0.0151333; weight = 0.725287;}
// 			if (40<=pt_el && pt_el<=45) {error=0.0158157; weight = 0.744737;}
// 			if (45<=pt_el && pt_el<=50) {error=0.0165737; weight = 0.795608;}
// 			if (50<=pt_el && pt_el<=60) {error=0.0144782; weight = 0.817416;}
// 			if (60<=pt_el && pt_el<=70) {error=0.0204946; weight = 0.815642;}
// 			if (70<=pt_el && pt_el<=80) {error=0.0289686; weight = 0.806452;}
// 			if (80<=pt_el && pt_el<=100) {error=0.0195342; weight = 0.929825;}
// 			if (100<=pt_el && pt_el<=120) {error=0.0407486; weight = 0.876923;}
// 			if (120<=pt_el && pt_el<=200) {error=0.0608155; weight = 0.782609;}
// 		}
// 		if (-2.1<=eta_el && eta_el<=-1.4442)
// 		{
// 			if (30<=pt_el && pt_el<=35) {error=0.00782644; weight = 0.75438;}
// 			if (35<=pt_el && pt_el<=40) {error=0.00752914; weight = 0.784827;}
// 			if (40<=pt_el && pt_el<=45) {error=0.00715891; weight = 0.816781;}
// 			if (45<=pt_el && pt_el<=50) {error=0.00783679; weight = 0.818973;}
// 			if (50<=pt_el && pt_el<=60) {error=0.006606; weight = 0.831671;}
// 			if (60<=pt_el && pt_el<=70) {error=0.00741374; weight = 0.883547;}
// 			if (70<=pt_el && pt_el<=80) {error=0.00904045; weight = 0.899099;}
// 			if (80<=pt_el && pt_el<=100) {error=0.00934107; weight = 0.897533;}
// 			if (100<=pt_el && pt_el<=120) {error=0.0140611; weight = 0.909091;}
// 			if (120<=pt_el && pt_el<=200) {error=0.0149635; weight = 0.914286;}
// 		}
// 		if (-1.4442<=eta_el && eta_el<=-0.8)
// 		{
// 			if (30<=pt_el && pt_el<=35) {error=0.00596045; weight = 0.746759;}
// 			if (35<=pt_el && pt_el<=40) {error=0.00555519; weight = 0.784242;}
// 			if (40<=pt_el && pt_el<=45) {error=0.00543; weight = 0.79522;}
// 			if (45<=pt_el && pt_el<=50) {error=0.00586282; weight = 0.806565;}
// 			if (50<=pt_el && pt_el<=60) {error=0.00453821; weight = 0.838322;}
// 			if (60<=pt_el && pt_el<=70) {error=0.00529979; weight = 0.864904;}
// 			if (70<=pt_el && pt_el<=80) {error=0.00606678; weight = 0.87346;}
// 			if (80<=pt_el && pt_el<=100) {error=0.00592697; weight = 0.871779;}
// 			if (100<=pt_el && pt_el<=120) {error=0.00822386; weight = 0.895728;}
// 			if (120<=pt_el && pt_el<=200) {error=0.00995513; weight = 0.868284;}
// 		}
// 		if (-0.8<=eta_el && eta_el<=-0.4)
// 		{
// 			if (30<=pt_el && pt_el<=35) {error=0.00684374; weight = 0.746535;}
// 			if (35<=pt_el && pt_el<=40) {error=0.00637733; weight = 0.775777;}
// 			if (40<=pt_el && pt_el<=45) {error=0.00605954; weight = 0.81032;}
// 			if (45<=pt_el && pt_el<=50) {error=0.00645753; weight = 0.827254;}
// 			if (50<=pt_el && pt_el<=60) {error=0.00510029; weight = 0.840178;}
// 			if (60<=pt_el && pt_el<=70) {error=0.005332; weight = 0.882289;}
// 			if (70<=pt_el && pt_el<=80) {error=0.0062641; weight = 0.890953;}
// 			if (80<=pt_el && pt_el<=100) {error=0.00588061; weight = 0.890265;}
// 			if (100<=pt_el && pt_el<=120) {error=0.0081943; weight = 0.907348;}
// 			if (120<=pt_el && pt_el<=200) {error=0.00742501; weight = 0.929412;}
// 		}
// 		if (-0.4<=eta_el && eta_el<=0)
// 		{
// 			if (30<=pt_el && pt_el<=35) {error=0.00657291; weight = 0.736315;}
// 			if (35<=pt_el && pt_el<=40) {error=0.00625086; weight = 0.775409;}
// 			if (40<=pt_el && pt_el<=45) {error=0.00626275; weight = 0.779936;}
// 			if (45<=pt_el && pt_el<=50) {error=0.00655557; weight = 0.800862;}
// 			if (50<=pt_el && pt_el<=60) {error=0.00508275; weight = 0.830459;}
// 			if (60<=pt_el && pt_el<=70) {error=0.00599551; weight = 0.842262;}
// 			if (70<=pt_el && pt_el<=80) {error=0.00674729; weight = 0.868044;}
// 			if (80<=pt_el && pt_el<=100) {error=0.00595107; weight = 0.880688;}
// 			if (100<=pt_el && pt_el<=120) {error=0.0090709; weight = 0.846641;}
// 			if (120<=pt_el && pt_el<=200) {error=0.00795598; weight = 0.881356;}
// 		}
// 		if (0<=eta_el && eta_el<=0.4)
// 		{
// 			if (30<=pt_el && pt_el<=35) {error=0.00645803; weight = 0.74441;}
// 			if (35<=pt_el && pt_el<=40) {error=0.00611116; weight = 0.774194;}
// 			if (40<=pt_el && pt_el<=45) {error=0.00615234; weight = 0.790714;}
// 			if (45<=pt_el && pt_el<=50) {error=0.00641464; weight = 0.811007;}
// 			if (50<=pt_el && pt_el<=60) {error=0.00500111; weight = 0.834086;}
// 			if (60<=pt_el && pt_el<=70) {error=0.00558322; weight = 0.860104;}
// 			if (70<=pt_el && pt_el<=80) {error=0.00653965; weight = 0.874513;}
// 			if (80<=pt_el && pt_el<=100) {error=0.00574122; weight = 0.880075;}
// 			if (100<=pt_el && pt_el<=120) {error=0.00880419; weight = 0.871369;}
// 			if (120<=pt_el && pt_el<=200) {error=0.0076547; weight = 0.891859;}
// 		}
// 		if (0.4<=eta_el && eta_el<=0.8)
// 		{
// 			if (30<=pt_el && pt_el<=35) {error=0.00638429; weight = 0.764666;}
// 			if (35<=pt_el && pt_el<=40) {error=0.00626432; weight = 0.774186;}
// 			if (40<=pt_el && pt_el<=45) {error=0.00608344; weight = 0.79798;}
// 			if (45<=pt_el && pt_el<=50) {error=0.0061428; weight = 0.835068;}
// 			if (50<=pt_el && pt_el<=60) {error=0.00491389; weight = 0.852828;}
// 			if (60<=pt_el && pt_el<=70) {error=0.00558009; weight = 0.871524;}
// 			if (70<=pt_el && pt_el<=80) {error=0.00634108; weight = 0.8904;}
// 			if (80<=pt_el && pt_el<=100) {error=0.00571277; weight = 0.895434;}
// 			if (100<=pt_el && pt_el<=120) {error=0.00831442; weight = 0.901716;}
// 			if (120<=pt_el && pt_el<=200) {error=0.00793872; weight = 0.909579;}
// 		}
// 		if (0.8<=eta_el && eta_el<=1.4442)
// 		{
// 			if (30<=pt_el && pt_el<=35) {error=0.00600562; weight = 0.740109;}
// 			if (35<=pt_el && pt_el<=40) {error=0.005689; weight = 0.760483;}
// 			if (40<=pt_el && pt_el<=45) {error=0.00559439; weight = 0.774749;}
// 			if (45<=pt_el && pt_el<=50) {error=0.00592529; weight = 0.798429;}
// 			if (50<=pt_el && pt_el<=60) {error=0.00468873; weight = 0.8213;}
// 			if (60<=pt_el && pt_el<=70) {error=0.0052283; weight = 0.855438;}
// 			if (70<=pt_el && pt_el<=80) {error=0.00662805; weight = 0.847435;}
// 			if (80<=pt_el && pt_el<=100) {error=0.00596986; weight = 0.866052;}
// 			if (100<=pt_el && pt_el<=120) {error=0.00888821; weight = 0.87156;}
// 			if (120<=pt_el && pt_el<=200) {error=0.0102119; weight = 0.862676;}
// 		}
// 		if (1.4442<=eta_el && eta_el<=2.1)
// 		{
// 			if (30<=pt_el && pt_el<=35) {error=0.00783831; weight = 0.744509;}
// 			if (35<=pt_el && pt_el<=40) {error=0.00769034; weight = 0.757157;}
// 			if (40<=pt_el && pt_el<=45) {error=0.00756508; weight = 0.785205;}
// 			if (45<=pt_el && pt_el<=50) {error=0.00776335; weight = 0.823651;}
// 			if (50<=pt_el && pt_el<=60) {error=0.00630027; weight = 0.852718;}
// 			if (60<=pt_el && pt_el<=70) {error=0.00784083; weight = 0.865121;}
// 			if (70<=pt_el && pt_el<=80) {error=0.00964751; weight = 0.880071;}
// 			if (80<=pt_el && pt_el<=100) {error=0.00897936; weight = 0.899821;}
// 			if (100<=pt_el && pt_el<=120) {error=0.0149408; weight = 0.89781;}
// 			if (120<=pt_el && pt_el<=200) {error=0.0176413; weight = 0.891026;}
// 		}
// 		if (2.1<=eta_el && eta_el<=2.4)
// 		{
// 			if (30<=pt_el && pt_el<=35) {error=0.0154749; weight = 0.686318;}
// 			if (35<=pt_el && pt_el<=40) {error=0.0148938; weight = 0.742459;}
// 			if (40<=pt_el && pt_el<=45) {error=0.0149299; weight = 0.798064;}
// 			if (45<=pt_el && pt_el<=50) {error=0.0168101; weight = 0.804309;}
// 			if (50<=pt_el && pt_el<=60) {error=0.0151095; weight = 0.802594;}
// 			if (60<=pt_el && pt_el<=70) {error=0.0204407; weight = 0.832335;}
// 			if (70<=pt_el && pt_el<=80) {error=0.0232132; weight = 0.884211;}
// 			if (80<=pt_el && pt_el<=100) {error=0.0242022; weight = 0.862069;}
// 			if (100<=pt_el && pt_el<=120) {error=0.0438854; weight = 0.866667;}
// 			if (120<=pt_el && pt_el<=200) {error=0.0591528; weight = 0.842105;}
// 		}
// 		if(DEBUGfakerate_h)std::cout << "elFR : " << weight << "	error : " << error << std::endl;
// 		return weight + error*prModeBehavior(mode,lep_info.at(0));

	}
	else{
		//muon prompt rate
		double pt_mu = lep_info.at(2);
		double eta_mu = lep_info.at(3);
		double weight = 0.0;

		// PRv6, PRv7test, PRvElPRtest, PRv9 - From Clint, https://indico.cern.ch/event/605620/contributions/2441087/attachments/1398025/2132153/VHFMeeting_X53_01.18.17.pdf http://cms.cern.ch/iCMS/jsp/db_notes/noteInfo.jsp?cmsnoteid=CMS%20AN-2016/242 v16
		weight = 0.943;
		//if(DEBUGfakerate_h)std::cout << "muPR used (mode:"<<mode<<") = " << weight << " + " << "("<<prModeBehavior(mode)<<")"<<uPr(lep_info)<< std::endl;
 		if(DEBUGfakerate_h)std::cout << "Mu  PR -- Mode: " << mode << ", " << weight <<" + "<<  prModeBehavior(mode,lep_info.at(0)) << " * " << uPr(lep_info)<< endl;
		return weight + uPr(lep_info)*prModeBehavior(mode,lep_info.at(0));

		//PRvMuPRtest,PRv8test - to see how mu fr affects things.
// 		weight = 1.0;
// 		return weight;

		//PRv10 from http://home.fnal.gov/~souvik/Work/VLQ/IFTABLE_VLQ_PromptRate_mm_OS.c , https://mail.google.com/mail/u/0/#sent/15c957c688a0ff96
// 		double error=0.0;
// 		if (eta_mu<-2.4) eta_mu=-2.4;
// 		if (eta_mu>2.4) eta_mu=2.4;
// 		if (pt_mu<20) pt_mu=20;
// 		if (pt_mu>200) pt_mu=200;
// 		if (-2.4<=eta_mu && eta_mu<=-2.1)
// 		{
// 			if (30<=pt_mu && pt_mu<=35) {error=0.00696436; weight = 0.892137;}
// 			if (35<=pt_mu && pt_mu<=40) {error=0.00693992; weight = 0.898835;}
// 			if (40<=pt_mu && pt_mu<=45) {error=0.00706841; weight = 0.900334;}
// 			if (45<=pt_mu && pt_mu<=50) {error=0.00706971; weight = 0.917826;}
// 			if (50<=pt_mu && pt_mu<=60) {error=0.00574953; weight = 0.914552;}
// 			if (60<=pt_mu && pt_mu<=70) {error=0.00681109; weight = 0.923329;}
// 			if (70<=pt_mu && pt_mu<=80) {error=0.00856267; weight = 0.920683;}
// 			if (80<=pt_mu && pt_mu<=100) {error=0.00751544; weight = 0.931677;}
// 			if (100<=pt_mu && pt_mu<=120) {error=0.012473; weight = 0.92094;}
// 			if (120<=pt_mu && pt_mu<=200) {error=0.0128986; weight = 0.919282;}
// 		}
// 		if (-2.1<=eta_mu && eta_mu<=-1.4442)
// 		{
// 			if (30<=pt_mu && pt_mu<=35) {error=0.00423302; weight = 0.882312;}
// 			if (35<=pt_mu && pt_mu<=40) {error=0.00389967; weight = 0.901786;}
// 			if (40<=pt_mu && pt_mu<=45) {error=0.00359675; weight = 0.918554;}
// 			if (45<=pt_mu && pt_mu<=50) {error=0.00358602; weight = 0.93014;}
// 			if (50<=pt_mu && pt_mu<=60) {error=0.00279378; weight = 0.936759;}
// 			if (60<=pt_mu && pt_mu<=70) {error=0.00317277; weight = 0.945398;}
// 			if (70<=pt_mu && pt_mu<=80) {error=0.00377638; weight = 0.949013;}
// 			if (80<=pt_mu && pt_mu<=100) {error=0.0035186; weight = 0.949844;}
// 			if (100<=pt_mu && pt_mu<=120) {error=0.00500679; weight = 0.954155;}
// 			if (120<=pt_mu && pt_mu<=200) {error=0.0048202; weight = 0.953968;}
// 		}
// 		if (-1.4442<=eta_mu && eta_mu<=-0.8)
// 		{
// 			if (30<=pt_mu && pt_mu<=35) {error=0.00401537; weight = 0.856636;}
// 			if (35<=pt_mu && pt_mu<=40) {error=0.00371574; weight = 0.873392;}
// 			if (40<=pt_mu && pt_mu<=45) {error=0.0034907; weight = 0.894574;}
// 			if (45<=pt_mu && pt_mu<=50) {error=0.00372436; weight = 0.899417;}
// 			if (50<=pt_mu && pt_mu<=60) {error=0.00270208; weight = 0.920543;}
// 			if (60<=pt_mu && pt_mu<=70) {error=0.00297884; weight = 0.93547;}
// 			if (70<=pt_mu && pt_mu<=80) {error=0.00336079; weight = 0.942488;}
// 			if (80<=pt_mu && pt_mu<=100) {error=0.0031307; weight = 0.943244;}
// 			if (100<=pt_mu && pt_mu<=120) {error=0.00462734; weight = 0.941797;}
// 			if (120<=pt_mu && pt_mu<=200) {error=0.00452172; weight = 0.936981;}
// 		}
// 		if (-0.8<=eta_mu && eta_mu<=-0.4)
// 		{
// 			if (30<=pt_mu && pt_mu<=35) {error=0.00470619; weight = 0.850811;}
// 			if (35<=pt_mu && pt_mu<=40) {error=0.00446924; weight = 0.866701;}
// 			if (40<=pt_mu && pt_mu<=45) {error=0.00407411; weight = 0.899049;}
// 			if (45<=pt_mu && pt_mu<=50) {error=0.00434482; weight = 0.902554;}
// 			if (50<=pt_mu && pt_mu<=60) {error=0.00305025; weight = 0.929025;}
// 			if (60<=pt_mu && pt_mu<=70) {error=0.00316887; weight = 0.948449;}
// 			if (70<=pt_mu && pt_mu<=80) {error=0.00365533; weight = 0.952325;}
// 			if (80<=pt_mu && pt_mu<=100) {error=0.0033826; weight = 0.95379;}
// 			if (100<=pt_mu && pt_mu<=120) {error=0.00467305; weight = 0.96039;}
// 			if (120<=pt_mu && pt_mu<=200) {error=0.00394609; weight = 0.968686;}
// 		}
// 		if (-0.4<=eta_mu && eta_mu<=0)
// 		{
// 			if (30<=pt_mu && pt_mu<=35) {error=0.00494403; weight = 0.824304;}
// 			if (35<=pt_mu && pt_mu<=40) {error=0.0045926; weight = 0.851982;}
// 			if (40<=pt_mu && pt_mu<=45) {error=0.00461813; weight = 0.859745;}
// 			if (45<=pt_mu && pt_mu<=50) {error=0.0046739; weight = 0.884287;}
// 			if (50<=pt_mu && pt_mu<=60) {error=0.0034217; weight = 0.909817;}
// 			if (60<=pt_mu && pt_mu<=70) {error=0.00371799; weight = 0.927039;}
// 			if (70<=pt_mu && pt_mu<=80) {error=0.00421646; weight = 0.938287;}
// 			if (80<=pt_mu && pt_mu<=100) {error=0.00361364; weight = 0.949281;}
// 			if (100<=pt_mu && pt_mu<=120) {error=0.00549009; weight = 0.944064;}
// 			if (120<=pt_mu && pt_mu<=200) {error=0.00542912; weight = 0.939144;}
// 		}
// 		if (0<=eta_mu && eta_mu<=0.4)
// 		{
// 			if (30<=pt_mu && pt_mu<=35) {error=0.0049536; weight = 0.826683;}
// 			if (35<=pt_mu && pt_mu<=40) {error=0.00465082; weight = 0.850017;}
// 			if (40<=pt_mu && pt_mu<=45) {error=0.00452705; weight = 0.872309;}
// 			if (45<=pt_mu && pt_mu<=50) {error=0.00466499; weight = 0.885782;}
// 			if (50<=pt_mu && pt_mu<=60) {error=0.00361182; weight = 0.900685;}
// 			if (60<=pt_mu && pt_mu<=70) {error=0.00373889; weight = 0.925866;}
// 			if (70<=pt_mu && pt_mu<=80) {error=0.00411751; weight = 0.941033;}
// 			if (80<=pt_mu && pt_mu<=100) {error=0.00371454; weight = 0.94599;}
// 			if (100<=pt_mu && pt_mu<=120) {error=0.00572901; weight = 0.937958;}
// 			if (120<=pt_mu && pt_mu<=200) {error=0.00540456; weight = 0.940229;}
// 		}
// 		if (0.4<=eta_mu && eta_mu<=0.8)
// 		{
// 			if (30<=pt_mu && pt_mu<=35) {error=0.00481413; weight = 0.843734;}
// 			if (35<=pt_mu && pt_mu<=40) {error=0.00426876; weight = 0.881247;}
// 			if (40<=pt_mu && pt_mu<=45) {error=0.00397586; weight = 0.902571;}
// 			if (45<=pt_mu && pt_mu<=50) {error=0.00431111; weight = 0.907126;}
// 			if (50<=pt_mu && pt_mu<=60) {error=0.00314211; weight = 0.922949;}
// 			if (60<=pt_mu && pt_mu<=70) {error=0.00332086; weight = 0.94214;}
// 			if (70<=pt_mu && pt_mu<=80) {error=0.00359692; weight = 0.954156;}
// 			if (80<=pt_mu && pt_mu<=100) {error=0.0031486; weight = 0.96106;}
// 			if (100<=pt_mu && pt_mu<=120) {error=0.00465931; weight = 0.958791;}
// 			if (120<=pt_mu && pt_mu<=200) {error=0.00414826; weight = 0.964921;}
// 		}
// 		if (0.8<=eta_mu && eta_mu<=1.4442)
// 		{
// 			if (30<=pt_mu && pt_mu<=35) {error=0.00406441; weight = 0.850052;}
// 			if (35<=pt_mu && pt_mu<=40) {error=0.00379344; weight = 0.870671;}
// 			if (40<=pt_mu && pt_mu<=45) {error=0.0037034; weight = 0.880694;}
// 			if (45<=pt_mu && pt_mu<=50) {error=0.00368503; weight = 0.896516;}
// 			if (50<=pt_mu && pt_mu<=60) {error=0.00267093; weight = 0.921551;}
// 			if (60<=pt_mu && pt_mu<=70) {error=0.00309357; weight = 0.928499;}
// 			if (70<=pt_mu && pt_mu<=80) {error=0.00362711; weight = 0.933039;}
// 			if (80<=pt_mu && pt_mu<=100) {error=0.00307613; weight = 0.945103;}
// 			if (100<=pt_mu && pt_mu<=120) {error=0.00457282; weight = 0.943507;}
// 			if (120<=pt_mu && pt_mu<=200) {error=0.00427907; weight = 0.946121;}
// 		}
// 		if (1.4442<=eta_mu && eta_mu<=2.1)
// 		{
// 			if (30<=pt_mu && pt_mu<=35) {error=0.00415463; weight = 0.888309;}
// 			if (35<=pt_mu && pt_mu<=40) {error=0.00392593; weight = 0.899812;}
// 			if (40<=pt_mu && pt_mu<=45) {error=0.00365288; weight = 0.917223;}
// 			if (45<=pt_mu && pt_mu<=50) {error=0.00383761; weight = 0.921881;}
// 			if (50<=pt_mu && pt_mu<=60) {error=0.00284717; weight = 0.936629;}
// 			if (60<=pt_mu && pt_mu<=70) {error=0.00308697; weight = 0.949307;}
// 			if (70<=pt_mu && pt_mu<=80) {error=0.00375119; weight = 0.949212;}
// 			if (80<=pt_mu && pt_mu<=100) {error=0.00337869; weight = 0.953185;}
// 			if (100<=pt_mu && pt_mu<=120) {error=0.00484937; weight = 0.955915;}
// 			if (120<=pt_mu && pt_mu<=200) {error=0.00491175; weight = 0.953628;}
// 		}
// 		if (2.1<=eta_mu && eta_mu<=2.4)
// 		{
// 			if (30<=pt_mu && pt_mu<=35) {error=0.00686689; weight = 0.901919;}
// 			if (35<=pt_mu && pt_mu<=40) {error=0.00672348; weight = 0.901631;}
// 			if (40<=pt_mu && pt_mu<=45) {error=0.00641161; weight = 0.920067;}
// 			if (45<=pt_mu && pt_mu<=50) {error=0.00653247; weight = 0.929928;}
// 			if (50<=pt_mu && pt_mu<=60) {error=0.00558035; weight = 0.924554;}
// 			if (60<=pt_mu && pt_mu<=70) {error=0.00637618; weight = 0.933684;}
// 			if (70<=pt_mu && pt_mu<=80) {error=0.00794699; weight = 0.934224;}
// 			if (80<=pt_mu && pt_mu<=100) {error=0.00770646; weight = 0.929873;}
// 			if (100<=pt_mu && pt_mu<=120) {error=0.0109881; weight = 0.935743;}
// 			if (120<=pt_mu && pt_mu<=200) {error=0.0131449; weight = 0.916479;}
// 		}
// 		if(DEBUGfakerate_h)std::cout << "muFR : " << weight << "	error : " << error << std::endl;
// 		return weight + error*prModeBehavior(mode,lep_info.at(0));

	}
}

float Fr(int mode, std::vector<double> lep_info){
	if(lep_info.at(0)==0){
		//ele fake rate
		double pt_el = lep_info.at(2);
		double eta_el = lep_info.at(3);
		double weight = 0.0;

		if(lep_info.size()==4){ //before scan size is 4

			//FRv18b,18bSys - CR2 letPt PRv6 2 1bjet leppt>30 GeV, FRv19test
// 			weight = 0.25 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));

			//FRv20b - CR2 letPt PRv6 2 1bjet leppt>30 GeV, fixedLumi, newMllOS
// 			weight = 0.24 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));

			//FRv21test - applying zjets ttx SR/CR2 ratio
// 			weight = 0.186 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));

			//FRv22 - CR2 letPt PRv6 latestLJMEtFeb242017
// 			weight = 0.22 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));

			//FRv24 - CR2 letPt PRv6 latestLJMEtFeb242017_newMuTrkSF
// 			weight = 0.23 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));

			//FRv25ttbar
// 			weight = 0.0 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));

			//FRv26ttbar
// 			weight = 0.5 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));

			//FRv27
// 			weight = 0.26 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));

			//FRv28ttbar
// 			weight = 0.01 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));

			//FRv29CR1
// 			weight = 0.29 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));

			//FRv30CR2 - CR2 letPt PRv9 latestLJMEtMar312017_newRunH, FRvMuEtatest
// 			weight = 0.23 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));

			//FRv31CR1 - CR1 letPt PRv9 latestLJMEtMar312017_newRunH
// 			weight = 0.29 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));

			//FRv32CR1CR2 - CR1CR2 letPt PRv9 latestLJMEtMar312017_newRunH
// 			weight = 0.26 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));

			//FRv33 - experimenting
// 			weight = 0.31 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));

			//FRv34 - experimenting
// 			weight = 0.346 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));

			//FRv35 ttbar pt dependence - experimenting ttbar FR 3orMoreLeptons, FRv35a, FRv35b
// 			if(pt_el>=30. && pt_el < 50.) weight = 0.19 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));
// 			else if(pt_el<100) weight = 0.30 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));
// 			else if(pt_el<150) weight = 0.48 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));
// 			else if(pt_el<200) weight = 0.80 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));
// 			else if(pt_el<500) weight = 0.83 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));
// 			else weight = 0.83 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));

			//FRv36 ttbar pt dependence - Clints AN2016-242 El fake rate from b source.
// 			if(pt_el>=30. && pt_el < 50.) weight = 0.12 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));
// 			else if(pt_el<100) weight = 0.19 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));
// 			else if(pt_el<150) weight = 0.30 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));
// 			else if(pt_el<200) weight = 0.37 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));
// 			else if(pt_el<500) weight = 0.48 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));
// 			else weight = 0.48 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));

			//FRv37 ddbkg ttbar June2-2017
// 			if(pt_el>=30. && pt_el < 100.) weight = 0.20 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));
// 			else weight = 0.30 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));

			//FRv38 ddbkg ttbar June5-2017
// 			if(pt_el>=30. && pt_el < 60.) weight = 0.19 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));
// 			else if(pt_el<100) weight = 0.22 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));
// 			else if(pt_el<140) weight = 0.26 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));
// 			else if(pt_el<180) weight = 0.31 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));
// 			else if(pt_el<500) weight = 0.42 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));
// 			else weight = 0.42 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));

			//FRv39 based ttbar pt dependence but translated based on FRv30CR2
// 			if(pt_el>=30. && pt_el < 50.) weight = 0.19 + 0.02 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));
// 			else if(pt_el<100) weight = 0.30 + 0.02 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));
// 			else if(pt_el<150) weight = 0.48 + 0.02 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));
// 			else if(pt_el<200) weight = 0.80 + 0.02 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));
// 			else if(pt_el<500) weight = 0.83 + 0.02 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));
// 			else weight = 0.83 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));

			//FRv40 pt dependence - based on Clints AN2016-242 El fake rate from b source, but translated
// 			if(pt_el>=30. && pt_el < 50.) weight = 0.12 + 0.1 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));
// 			else if(pt_el<100) weight = 0.19 + 0.1 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));
// 			else if(pt_el<150) weight = 0.30 + 0.1 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));
// 			else if(pt_el<200) weight = 0.37 + 0.1 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));
// 			else if(pt_el<500) weight = 0.48 + 0.1 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));
// 			else weight = 0.48 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));

			//FRv41 SRST1000low, FRv41lessSys, FRv43 SRHT600low
// 			weight = 0.38 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));

			//FRv42CR2 - PRv10
// 			weight = 0.24 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));

			//FRv44 FRSRmlllb400
// 			weight = 0.34 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));

			//FRv45 FRSRHT400low
			/* weight = 0.36 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));  */

			//FRv46 FRSRHT400low2D
// 			weight = 0.50 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));

			//FRv47 FRSRHT400low2Dext
// 			weight = 0.52 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));

			//FRv48 FRSRHT400low elMVAValueFix
// 			weight = 0.25 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));

			//FRv49 FRCR2 elMVAValueFix
			weight = 0.20 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));

			//FRv50 FRCR1 elMVAValueFix
// 			weight = 0.23 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));

		}
		else{
			weight = lep_info.at(5);
		}

// 		if(DEBUGfakerate_h)std::cout << "elFR used = " << weight << std::endl;
		if(DEBUGfakerate_h)std::cout << "Ele FR -- Mode: " << mode << ", " << frModeBehavior(mode,lep_info.at(0)) << " * " << uFr(lep_info)<<  endl;

		return weight;


	}
	else{
		//muon fake rate
		double pt_mu = lep_info.at(2);
		double eta_mu = lep_info.at(3);
		double weight = 0.0;

		if(lep_info.size()==4) {  //before scan size is 4

			//FRv18b,18bSys - CR2 LepPt PRv6 1bjet lepPt>30 GeV
// 			weight = 0.11 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));

			//FRv19test - model after Clints eta dependence
// 			weight = ( 0.1203392 - 3.849218e-18*eta_mu + 0.0257206*(eta_mu*eta_mu) ) + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));

			//FRv20b - CR2 letPt PRv6 2 1bjet leppt>30 GeV, fixedLumi, newMllOS
// 			weight = 0.11 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));

			//FRv21test - applying zjets ttx SR/CR2 ratio
// 			weight = 0.125 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));

			//FRv22 - CR2 letPt PRv6 latestLJMEtFeb242017, FRv24 - _newMuTrkSF
// 			weight = 0.15 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));

			//FRv26ttbar,FRv25ttbar
// 			weight = 0.5 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));

			//FRv27
// 			weight = 0.13 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));

			//FRv28ttbar
// 			weight = 0.42 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));

			//FRv29CR1
// 			weight = 0.13 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));

			//FRvMuEtatest - model after Clints eta dependence
// 			weight = ( 0.15 - 3.849218e-18*eta_mu + 0.0257206*(eta_mu*eta_mu) ) + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));

			//FRv30CR2,FRv31CR1 - lepPt PRv9 latestLJMEtMar312017 _newRunH, FRv33, FRv35b, FRv39, FRv40, FRv42, FRv45
			/* weight = 0.16 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));  */

			//FRvMuEtatest - model after Clints eta dependence - central=FRv30CR2
// 			weight = ( 0.16 - 3.849218e-18*eta_mu + 0.0257206*(eta_mu*eta_mu) ) + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));

			//FRv34 - experimenting ttbar FR 1orMoreLeptons
// 			weight = 0.131 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));

			//FRv35 - experimenting ttbar FR 3orMoreLeptons (average sort of), FRv36
// 			weight = 0.13 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));

			//FRv37 ddbkg ttbar June2-2017
// 			if(pt_mu>=30. && pt_mu < 100.) weight = 0.14 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));
// 			else weight = 0.15 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));

			//FRv38 ddbkg ttbar June5-2017 - averaging based on the pt dependance results, FRv35a ddbkg pt independent
// 			weight = 0.14 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));

			//FRv41, , FRv41lessSys, FRv44
// 			weight = 0.17 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));

			//FRv43 FRSRHT600low, FRv48 FRSRHT400low elMVAValueFix
// 			weight = 0.18 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));

			//FRv46 FRSRHT400low2D
// 			weight = 0.36 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));

			//FRv47 FRSRHT400low2Dext
// 			weight = 0.35 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));

			//FRv49 FRCR2 elMVAValueFix
// 			weight = 0.14 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));

			//FRv48MuEtatest - model after Clints eta dependence - central=FRv48
// 			weight = ( 0.18 - 3.849218e-18*eta_mu + 0.0257206*(eta_mu*eta_mu) ) + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));

			//FRv49MuEtatest - model after Clints eta dependence - central=FRv48
			weight = ( 0.14 - 3.849218e-18*eta_mu + 0.0257206*(eta_mu*eta_mu) ) + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));

			//FRv50 FRCR1 elMVAValueFix
// 			weight = 0.15 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));

		}
		else{
			weight = lep_info.at(4);
		}

// 		if(DEBUGfakerate_h)std::cout << "muFR used = " << weight << std::endl;
		if(DEBUGfakerate_h)std::cout << "Mu  FR -- Mode: " << mode << ", " << frModeBehavior(mode,lep_info.at(0)) << " * " << uFr(lep_info)<<  endl;

		return weight;

	}
}

inline float uPr(std::vector<double> lep_info){

	if(lep_info.at(0)==0){
		//ele prompt rate unc

		//PRv5test,PRv7test,PRvElPRtest
// 		return 0.0;

		//PRv6,PRv8test,PRv9,PRvMuPRtest
		return 0.001;

		//PRv10 but it doesn really matter since its defined in PR
// 		return 1.0;

	}
	else{
		//mu prompt rate unc

		return 0.001; // PRv3, PRv4, PRv5test, PRv6,PRv7test,PRv9,PRvElPRtest

		//PRv8test, PRvMuPRtest
// 		return 0.0;

		//PRv10 but it doesn really matter since its defined in PR
// 		return 1.0;

	}
}

inline float uFr(std::vector<double> lep_info){
	if(lep_info.at(0)==0){
		//ele fake rate unc
		double pt_el = lep_info.at(2);
		double eta_el = lep_info.at(3);

		//FRv18bSys	taking into account systematics from closure test: sqrt(stat^2 +sys^2), FRv19test
// 		return sqrt(0.04*0.04 + 0.05*0.05);

	 	//FRv20b, FRv21test
// 		return sqrt(0.03*0.03 + 0.06*0.06);

	 	//FRv22, FRv24, FRvMuEtatest
// 		return sqrt(0.03*0.03 + 0.06*0.06);

		//FRv26ttbar,FRv25ttbar,FRv28ttbar --> arbitraty/dummmy approx.
// 		return sqrt(0.05*0.05);

		//FRv27
// 		return sqrt(0.03*0.03);

		//FRv29CR1
// 		return sqrt(0.06*0.06);

	 	//FRv30CR2, FRvMuEtatest, FRv35b, FRv39, FRv40, FRv41, FRv42
// 		return sqrt(0.02*0.02 + 0.06*0.06);

	 	//FRv31CR1
// 		return sqrt(0.01*0.01 + 0.06*0.06);

	 	//FRv30CR2extSys - see first ARC meeting, FRv33
// 		return 0.08;

	 	//FRv30CR2statOnly
// 		return 0.02;

	 	//FRv30CR2Sys2Only - see email https://mail.google.com/mail/u/0/?zx=aem6qf27p3l3#inbox/15bee84ec2989632 May10th2017
// 		return 0.06;

	 	//FRv30CR2Sys4Only - see email https://mail.google.com/mail/u/0/?zx=aem6qf27p3l3#inbox/15bee84ec2989632 May10th2017
// 		return 0.03;

	 	//FRv30CR2Sys5Only - see email https://mail.google.com/mail/u/0/?zx=aem6qf27p3l3#inbox/15bee84ec2989632 May10th2017
// 		return 0.06;

	 	//FRv34
// 		return 0.0014;

	 	//FRv35 - experimenting ttbar FR 3orMoreLeptons, FRv36 as proxy, FRv35a
// 	 	double weight;
// 		if(pt_el>=30. && pt_el < 50.) weight = 0.01;
// 		else if(pt_el<100) weight = 0.01;
// 		else if(pt_el<150) weight = 0.05;
// 		else if(pt_el<200) weight = 0.10;
// 		else if(pt_el<500) weight = 0.09;
// 		else weight = 0.09;
// 		return weight;

		//FRv37 ddbkg ttbar June2-2017 - proxy values
// 	 	double weight;
// 		if(pt_el>=30. && pt_el < 50.) weight = 0.01;
// 		else weight = 0.05;
// 		return weight;

		//FRv38 ddbkg ttbar June5-2017 - not based on anything, errors estimation just out of thin air for proxy.
// 	 	double weight;
// 		if(pt_el>=30. && pt_el < 60.) weight = 0.01;
// 		else if(pt_el<100) weight = 0.01;
// 		else if(pt_el<140) weight = 0.05;
// 		else if(pt_el<180) weight = 0.10;
// 		else if(pt_el<500) weight = 0.09;
// 		else weight = 0.09;
// 		return weight;

	 	//FRv41lessSys
// 		return sqrt(0.02*0.02);

	 	//FRv43
// 		return sqrt(0.024*0.024);

	 	//FRv44
// 		return sqrt(0.027*0.027);

	 	//FRv45
//		return sqrt(0.026*0.026);

	 	//FRv46
// 		return sqrt(0.03*0.03);

	 	//FRv47
// 		return sqrt(0.07*0.07);

	 	//FRv48
// 		return sqrt(0.028*0.028);

	 	//FRv49
// 		return sqrt(0.018*0.018);

	 	//FRv48sys - adding ttbar∆(SRHT400low-SRHT400)
// 		return sqrt(0.028*0.028 + 0.12*0.12);

	 	//FRv49sys - adding ttbar∆(CR2-SR)
		return sqrt(0.018*0.018 + 0.04*0.04);

	 	//FRv50
// 		return sqrt(0.017*0.017);

	 	//FRv50sys - based on FRv49sys - adding ttbar∆(CR2-SR)
// 		return sqrt(0.017*0.017 + 0.04*0.04);


	}
	else{
		//mu fake rate unc
		double pt_mu = lep_info.at(2);
		double eta_mu = lep_info.at(3);

		//FRv18bSys	taking into account systematics from closure test sqrt(stat^2 +sys^2), FRv19test
// 		return sqrt(0.03*0.03 + 0.04*0.04);

		 //FRv20b, FRv21test
// 		return sqrt(0.02*0.02 + 0.03*0.03);

	 	//FRv22, FRv24, FRvMuEtatest
// 		return sqrt(0.03*0.03 + 0.02*0.02);

		//FRv26ttbar,FRv25ttbar,FRv28ttbar --> arbitraty/dummmy approx.
// 		return sqrt(0.05*0.05);

		//FRv27
// 		return sqrt(0.02*0.02);

		//FRv29CR1
// 		return sqrt(0.02*0.02);

	 	//FRv30CR2, FRv31CR2, FRvMuEtatest, FRv33, FRv35b, FRv39, FRv40, FRv41, FRv42
// 		return sqrt(0.02*0.02 + 0.0*0.0);

	 	//FRv30CR2extSys - see first ARC meeting.
// 		return 0.024;

	 	//FRv30CR2statOnly
// 		return 0.02;

	 	//FRv30CR2Sys2Only - see email https://mail.google.com/mail/u/0/?zx=aem6qf27p3l3#inbox/15bee84ec2989632 May10th2017
// 		return 0.00;

	 	//FRv30CR2Sys4Only - see email https://mail.google.com/mail/u/0/?zx=aem6qf27p3l3#inbox/15bee84ec2989632 May10th2017
// 		return 0.014;

	 	//FRv30CR2Sys5Only - see email https://mail.google.com/mail/u/0/?zx=aem6qf27p3l3#inbox/15bee84ec2989632 May10th2017
// 		return 0.00;

	 	//FRv34
// 		return 0.001;

	 	//FRv35 - experimenting ttbar FR 3orMoreLeptons (average sort of), FRv36, FRv38
// 		return 0.01;

		//FRv37 ddbkg ttbar June2-2017 - proxy values
// 	 	double weight;
// 		if(pt_mu>=30. && pt_mu < 50.) weight = 0.01;
// 		else weight = 0.05;
// 		return weight;

	 	//FRv41lessSys
// 		return sqrt(0.03*0.03);

	 	//FRv43
// 		return sqrt(0.029*0.029);

	 	//FRv44
// 		return sqrt(0.028*0.028);

	 	//FRv45
		//return sqrt(0.029*0.029);

	 	//FRv46
// 		return sqrt(0.03*0.03);

	 	//FRv47
// 		return sqrt(0.1*0.1);

	 	//FRv48
// 		return sqrt(0.027*0.027);

	 	//FRv49
// 		return sqrt(0.014*0.014);

	 	//FRv48sys - adding ttbar∆(SRHT400low-SRHT400)
// 		return sqrt(0.027*0.027 + 0.01*0.01);

	 	//FRv49sys - adding ttbar∆(CR2-SR)
		return sqrt(0.014*0.014 + 0.0*0.0);

	 	//FRv50, FR50vsys based on FRv49sys
// 		return sqrt(0.019*0.019);


	}
}


inline float uQe(){return 0.30;}//percent

inline double epsilon(double f){return f/(1.0-f);}
inline double eta(double p){return (1.0-p)/p;}


//    ____
//   |___ \
//     __) |
//    |__ <
//    ___) |
//   |____/
//
//


std::vector<double> SF3Lepbkg(double f, double p, int N_t0, int N_t1, int N_t2, int N_t3){
	//Calculates all prompt and fake bkg info for Same Flavor trilepton events
	//output: {0:N_ppp, 1:N_fpp, 2:N_ffp, 3:N_fff, 4:N_signal, 5:N_1fake, 6:N_2fakes, 7:N_3fakes, 8:N_bkg}
	//This is taken from AN-10-261_v1 Section 4
	//N_t0 is #events with all 3 loose leptons failing tight
	//N_t1 is #events with one loose leptons failing tight and the other 2 passing tight
	//N_t2 is #events with two  loose leptons failing tight and the other one passing tight
	//N_t3 is #events with all 3 loose leptons passing tight
	//p is the probability ratio of a true lepton passes tight / a true lepton passing loose
	//f is the probability ratio of a fake lepton passes tight / a true lepton passing loose
	//N_fff is the loose leptons from three non-prompt fakes.
	//N_ffp is the loose leptons with one real lepton and two fakes.
	//N_fpp is the loose leptons with two real lepton and one fakes.
	//N_ppp is the number of true tri-lepton events passing loose
	//N_signal is the number of true tri-leptons all passing tight
	//N_1fake  is the number of events passing tight-tight with one fake lepton
	//N_2fake  is the number of events passing tight-tight with two fake lepton
	//N_3fake  is the number of events passing tight-tight with all three leptons fake
	//N_bkg = N_1fake + N_2fake + N_3fakes is the number of events passing tight that are not from two real leptons.
	double div = 1.0/pow(p-f,3);
	double omf = 1.0-f;
	double omp = 1.0-p;
	std::vector<double> out;
	out.push_back(div*(omf*omf*omf*N_t0 - f*omf*omf*N_t2 + f*f*omf*N_t1 - f*f*f*N_t0)); //N_ppp 0
	out.push_back(div*( 3.0*p*f*f*N_t0 - (f*f*omp + 2.0*p*f*omf)*N_t1 + (2.0*f*omp*omf + p*omf*omf)*N_t2 - 3.0*omp*omf*omf*N_t3) );//N_fpp 1
	out.push_back(div*(-3.0*p*p*f*N_t0 + (2.0*p*f*omp + p*p*omf)*N_t1 - (f*omp*omp + 2.0*p*omp*omf)*N_t2 + 2.0*omp*omp*omf*N_t3) );//N_ffp 2
	out.push_back(div*(p*p*p*N_t0 - p*p*omp*N_t1 + p*omp*omp*N_t2 - omp*omp*omp*N_t3));// N_fff 3
	out.push_back(p*p*p*out[0]); //4
	out.push_back(p*p*f*out[1]); //5
	out.push_back(p*f*f*out[2]); //6
	out.push_back(f*f*f*out[3]); //7
	out.push_back(out[5] + out[6] + out[7]);
	return out;
}
double SF3Lepbkg_simple(double f, double p, int N_t0, int N_t1, int N_t2, int N_t3){
	//returns  the number of tight tri-lepton events with at least one fake object (N_bkg from SF3Lepbkg)
	//This is taken from AN-10-261_v1 Section 4
	//N_t0 is #events with all 3 loose leptons failing tight
	//N_t1 is #events with one loose leptons failing tight and the other 2 passing tight
	//N_t2 is #events with two  loose leptons failing tight and the other one passing tight
	//N_t3 is #events with all 3 loose leptons passing tight
	//p is the probability ratio of a true lepton passes tight / a true lepton passing loose
	//f is the probability ratio of a fake lepton passes tight / a true lepton passing loose
	double div = 1.0/pow(p-f,3);
	double omf = 1.0-f;
	double omp = 1.0-p;
	double N_fpp = div*( 3.0*p*f*f*N_t0 - (f*f*omp + 2.0*p*f*omf)*N_t1 + (2.0*f*omp*omf + p*omf*omf)*N_t2 - 3.0*omp*omf*omf*N_t3);
	double N_ffp = div*(-3.0*p*p*f*N_t0 + (2.0*p*f*omp + p*p*omf)*N_t1 - (f*omp*omp + 2.0*p*omp*omf)*N_t2 + 2.0*omp*omp*omf*N_t3);
	double N_fff = div*(p*p*p*N_t0 - p*p*omp*N_t1 + p*omp*omp*N_t2 - omp*omp*omp*N_t3);
	return p*p*f*N_fpp + p*f*f*N_ffp + f*f*f*N_fff;
}

/////////////////////////////////////////////////////////////

/* //what is this for???
int ThrowPoissonFromMeasurement(TRandom2* r, int n){//wad
	if(n>100) return (int) r->Gaus(n, sqrt((float)n));
	//figure out what the distribution of poisson parameters are.
	return r->Poisson( 0.5*ChiSquared(2*(n+1) ) );
} //what is this for???
double ChiSquared(int k){//wad
	ROOT::Math::Random<ROOT::Math::GSLRngMT> r;
	return r.ChiSquare(k);
} //what is this for???
*/

/////////////////////// FUNCTIONS FOR WEIGHTS /////////////////////
///////////////////////coifs for SS emu////////////////////////////
//mode 0 = nominal. 1 = elfakerate plus, 2 = elfakerate minus, 3 = elpassrate plus, 4 = elpassrate minus, 5 = mufakerate plus, 6 = mufakerate minus, 7 = mupassrate plus, 8 = mupassrate minus
inline int frModeBehavior(int mode,int flavour){
	int temp = 0;
	if(flavour==0){
		if(mode==1) temp = 1;
		if(mode==2) temp = -1;
	}
	if(flavour==1){
		if(mode==5) temp = 1;
		if(mode==6) temp = -1;
	}
	return temp	;
} //if electron:+1,-1 for 1,2 ; if muon:+1,-1 for 5,6, else 0
inline int prModeBehavior(int mode,int flavour){
	int temp = 0;
	if(flavour==0){
		if(mode==3) temp = 1;
		if(mode==4) temp = -1;
	}
	if(flavour==1){
		if(mode==7) temp = 1;
		if(mode==8) temp = -1;
	}
	return temp	;
} //if electron:+1,-1 for 3,4 ; if muon:+1,-1 for 7,8, else 0


inline double Det_em(double fe, double pe, double fm, double pm, double q){ return -(1.0 - 2.0* q)*(pe - fe)*(pm - fm); } //det is always negative.


/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////Tripple Lepton /////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
double GetWeight(int mode, std::vector<double> lep1_info, std::vector<double> lep2_info, std::vector<double> lep3_info){
	//std::cout << "GetWeight: "<<" mode = "<<mode<<", lep1_info.at(1) = "<<lep1_info.at(1)<<", lep2_info.at(1) = "<<lep2_info.at(1)<<", lep3_info.at(1) = "<<lep3_info.at(1) << std::endl;
    if(		lep1_info.at(1)==1 && lep2_info.at(1)==1 && lep3_info.at(1)==1){return W_ttt(mode, lep1_info, lep2_info, lep3_info);}
    else if(lep1_info.at(1)==1 && lep2_info.at(1)==1 && lep3_info.at(1)==0){return W_ttl(mode, lep1_info, lep2_info, lep3_info);}
    else if(lep1_info.at(1)==1 && lep2_info.at(1)==0 && lep3_info.at(1)==1){return W_tlt(mode, lep1_info, lep2_info, lep3_info);}
    else if(lep1_info.at(1)==0 && lep2_info.at(1)==1 && lep3_info.at(1)==1){return W_ltt(mode, lep1_info, lep2_info, lep3_info);}
    else if(lep1_info.at(1)==1 && lep2_info.at(1)==0 && lep3_info.at(1)==0){return W_tll(mode, lep1_info, lep2_info, lep3_info);}
    else if(lep1_info.at(1)==0 && lep2_info.at(1)==1 && lep3_info.at(1)==0){return W_ltl(mode, lep1_info, lep2_info, lep3_info);}
    else if(lep1_info.at(1)==0 && lep2_info.at(1)==0 && lep3_info.at(1)==1){return W_llt(mode, lep1_info, lep2_info, lep3_info);}
    else if(lep1_info.at(1)==0 && lep2_info.at(1)==0 && lep3_info.at(1)==0){return W_lll(mode, lep1_info, lep2_info, lep3_info);}
    else return 0.0;
    }

/* Calculation by anthony:

(-(f1*f2*f3*p1*p2*p3*(n_lll))

- f1*f2*(-1 + f3)*p1*p2*p3*(n_llt)

+ f1*f3*p1*p2*p3*(n_ltl)
- f1*f2*f3*p1*p2*p3*(n_ltl)

+ f2*f3*p1*p2*p3*(n_tll)
- f1*f2*f3*p1*p2*p3*(n_tll)

- f1*p1*p2*p3*(n_ltt)
+ f1*f2*p1*p2*p3*(n_ltt)
+ f1*f3*p1*p2*p3*(n_ltt)
- f1*f2*f3*p1*p2*p3*(n_ltt)

-  f2*p1*p2*p3*(n_tlt)
+ f1*f2*p1*p2*p3*(n_tlt)
+ f2*f3*p1*p2*p3*(n_tlt)
- f1*f2*f3*p1*p2*p3*(n_tlt)

- f3*p1*p2*p3*(n_ttl)
+    f1*f3*p1*p2*p3*(n_ttl)
+ f2*f3*p1*p2*p3*(n_ttl)
- f1*f2*f3*p1*p2*p3*(n_ttl)

+  (f3*(f1 - p1)*(f2 - p2) + (f2*(-f1 + p1) + (f1 - (f1 + f2 - f1*f2 + (-1 + f1)*(-1 + f2)*f3)*p1)*p2)*p3)*(n_ttt))

/((f1 - p1)*(f2 - p2)*(f3 - p3))

*/

///Tri-lep
double W_lll(int mode, std::vector<double> lep1_info, std::vector<double> lep2_info, std::vector<double> lep3_info){
	double f1 = Fr(mode, lep1_info);
	double p1 = Pr(mode, lep1_info);
	double f2 = Fr(mode, lep2_info);
	double p2 = Pr(mode, lep2_info);
	double f3 = Fr(mode, lep3_info);
	double p3 = Pr(mode, lep3_info);
	//std::cout << "W_lll: f1 = "<<f1<<", p1 = "<<p1<<", f2 = "<<f2<<", p2 = "<<p2<<", f3 = "<<f3<<", p3 = "<<p3 << std::endl;
	double div = ((f1 - p1)*(f2 - p2)*(f3 - p3));
	return -f1*f2*f3*p1*p2*p3/div;
}
double W_ltt(int mode, std::vector<double> lep1_info, std::vector<double> lep2_info, std::vector<double> lep3_info){
	double f1 = Fr(mode, lep1_info);
	double p1 = Pr(mode, lep1_info);
	double f2 = Fr(mode, lep2_info);
	double p2 = Pr(mode, lep2_info);
	double f3 = Fr(mode, lep3_info);
	double p3 = Pr(mode, lep3_info);
	//std::cout << "W_ltt: f1 = "<<f1<<", p1 = "<<p1<<", f2 = "<<f2<<", p2 = "<<p2<<", f3 = "<<f3<<", p3 = "<<p3 << std::endl;
	double div = ((f1 - p1)*(f2 - p2)*(f3 - p3));
	return (-f1*p1*p2*p3 + f1*f2*p1*p2*p3 + f1*f3*p1*p2*p3 - f1*f2*f3*p1*p2*p3 )/div;
}
double W_tlt(int mode, std::vector<double> lep1_info, std::vector<double> lep2_info, std::vector<double> lep3_info){
	double f1 = Fr(mode, lep1_info);
	double p1 = Pr(mode, lep1_info);
	double f2 = Fr(mode, lep2_info);
	double p2 = Pr(mode, lep2_info);
	double f3 = Fr(mode, lep3_info);
	double p3 = Pr(mode, lep3_info);
	//std::cout << "W_tlt: f1 = "<<f1<<", p1 = "<<p1<<", f2 = "<<f2<<", p2 = "<<p2<<", f3 = "<<f3<<", p3 = "<<p3 << std::endl;
	double div = ((f1 - p1)*(f2 - p2)*(f3 - p3));
	return ( -f2*p1*p2*p3 + f1*f2*p1*p2*p3 + f2*f3*p1*p2*p3 - f1*f2*f3*p1*p2*p3 )/div;
}
double W_ttl(int mode, std::vector<double> lep1_info, std::vector<double> lep2_info, std::vector<double> lep3_info){
	double f1 = Fr(mode, lep1_info);
	double p1 = Pr(mode, lep1_info);
	double f2 = Fr(mode, lep2_info);
	double p2 = Pr(mode, lep2_info);
	double f3 = Fr(mode, lep3_info);
	double p3 = Pr(mode, lep3_info);
	//std::cout << "W_ttl: f1 = "<<f1<<", p1 = "<<p1<<", f2 = "<<f2<<", p2 = "<<p2<<", f3 = "<<f3<<", p3 = "<<p3 << std::endl;
	double div = ((f1 - p1)*(f2 - p2)*(f3 - p3));
	return ( - f3*p1*p2*p3 + f1*f3*p1*p2*p3 + f2*f3*p1*p2*p3 - f1*f2*f3*p1*p2*p3 )/div;
}
double W_llt(int mode, std::vector<double> lep1_info, std::vector<double> lep2_info, std::vector<double> lep3_info){
	double f1 = Fr(mode, lep1_info);
	double p1 = Pr(mode, lep1_info);
	double f2 = Fr(mode, lep2_info);
	double p2 = Pr(mode, lep2_info);
	double f3 = Fr(mode, lep3_info);
	double p3 = Pr(mode, lep3_info);
	//std::cout << "W_llt: f1 = "<<f1<<", p1 = "<<p1<<", f2 = "<<f2<<", p2 = "<<p2<<", f3 = "<<f3<<", p3 = "<<p3 << std::endl;
	double div = ((f1 - p1)*(f2 - p2)*(f3 - p3));
	return (-f1*f2*(-1 + f3)*p1*p2*p3 )/div;
}
double W_ltl(int mode, std::vector<double> lep1_info, std::vector<double> lep2_info, std::vector<double> lep3_info){
	double f1 = Fr(mode, lep1_info);
	double p1 = Pr(mode, lep1_info);
	double f2 = Fr(mode, lep2_info);
	double p2 = Pr(mode, lep2_info);
	double f3 = Fr(mode, lep3_info);
	double p3 = Pr(mode, lep3_info);
	//std::cout << "W_ltl: f1 = "<<f1<<", p1 = "<<p1<<", f2 = "<<f2<<", p2 = "<<p2<<", f3 = "<<f3<<", p3 = "<<p3 << std::endl;
	double div = ((f1 - p1)*(f2 - p2)*(f3 - p3));
	return ( f1*f3*p1*p2*p3 - f1*f2*f3*p1*p2*p3 )/div;
}
double W_tll(int mode, std::vector<double> lep1_info, std::vector<double> lep2_info, std::vector<double> lep3_info){
	double f1 = Fr(mode, lep1_info);
	double p1 = Pr(mode, lep1_info);
	double f2 = Fr(mode, lep2_info);
	double p2 = Pr(mode, lep2_info);
	double f3 = Fr(mode, lep3_info);
	double p3 = Pr(mode, lep3_info);
	//std::cout << "W_tll: f1 = "<<f1<<", p1 = "<<p1<<", f2 = "<<f2<<", p2 = "<<p2<<", f3 = "<<f3<<", p3 = "<<p3 << std::endl;
	double div = ((f1 - p1)*(f2 - p2)*(f3 - p3));
	return ( f2*f3*p1*p2*p3 - f1*f2*f3*p1*p2*p3 )/div;
}
double W_ttt(int mode, std::vector<double> lep1_info, std::vector<double> lep2_info, std::vector<double> lep3_info){
	double f1 = Fr(mode, lep1_info);
	double p1 = Pr(mode, lep1_info);
	double f2 = Fr(mode, lep2_info);
	double p2 = Pr(mode, lep2_info);
	double f3 = Fr(mode, lep3_info);
	double p3 = Pr(mode, lep3_info);
	//std::cout << "W_ttt: f1 = "<<f1<<", p1 = "<<p1<<", f2 = "<<f2<<", p2 = "<<p2<<", f3 = "<<f3<<", p3 = "<<p3 << std::endl;
	double div = ((f1 - p1)*(f2 - p2)*(f3 - p3));
	return (  (f3*(f1 - p1)*(f2 - p2) + (f2*(-f1 + p1) + (f1 - (f1 + f2 - f1*f2 + (-1 + f1)*(-1 + f2)*f3)*p1)*p2)*p3)  )/div;
}


#endif

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

float Pr(int mode,std::vector<double> lep_info);
inline float uPr(std::vector<double> lep_info);
float Fr(int mode,std::vector<double> lep_info);
inline float uFr(std::vector<double> lep_info);

inline float uQe();

inline double epsilon(double f);//these are guearenteed to be small numbers
inline double eta(double p);//these are guearenteed to be small numbers

inline int frModeBehavior(int mode);
inline int prModeBehavior(int mode);
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

// TFile* file_el = TFile::Open("/uscms_data/d3/rsyarif/Spring2016/TprimeFakeRateReproduce/FromJulie/CMSSW_7_4_14/src/LJMet/macros/step1/FakeRatePlots/FakeRate_Data_subtr_El_PtEta.root");
// TFile* file_mu = TFile::Open("/uscms_data/d3/rsyarif/Spring2016/TprimeFakeRateReproduce/FromJulie/CMSSW_7_4_14/src/LJMet/macros/step1/FakeRatePlots/FakeRate_Data_subtr_Mu_PtEta.root");

TFile* file_el = TFile::Open("/uscms_data/d3/rsyarif/Spring2016/TprimeFakeRateReproduce/FromJulie/CMSSW_7_4_14/src/LJMet/macros/step1/FakeRateFiles/withWJetsIncl_subtrDenom/FakeRate_Data_subtr_El_PtEta.root");
TFile* file_mu = TFile::Open("/uscms_data/d3/rsyarif/Spring2016/TprimeFakeRateReproduce/FromJulie/CMSSW_7_4_14/src/LJMet/macros/step1/FakeRateFiles/withWJetsIncl_subtrDenom/FakeRate_Data_subtr_Mu_PtEta.root");

// TFile* file_el = TFile::Open("/uscms_data/d3/rsyarif/Spring2016/TprimeFakeRateReproduce/FromJulie/CMSSW_7_4_14/src/LJMet/macros/step1/FakeRateFiles/withWJetsIncl_subtrDenom/FakeRate_Data_subtr_El_Pt_1bin.root");
// TFile* file_mu = TFile::Open("/uscms_data/d3/rsyarif/Spring2016/TprimeFakeRateReproduce/FromJulie/CMSSW_7_4_14/src/LJMet/macros/step1/FakeRateFiles/withWJetsIncl_subtrDenom/FakeRate_Data_subtr_Mu_Pt_1bin.root");


TCanvas* c_el = (TCanvas*) file_el->Get("c1");
TCanvas* c_mu = (TCanvas*) file_mu->Get("c1");
TH2D *h_el = (TH2D*) c_el->GetPrimitive("newratioEl");
TH2D *h_mu = (TH2D*) c_mu->GetPrimitive("newratioMu");


float Pr(int mode, std::vector<double> lep_info){
	if(lep_info.at(0)==0){
		//ele prompt rate
		double pt_el = lep_info.at(2);
		double eta_el = lep_info.at(3);
		double weight = 0.0;
			
		//PRv4 - anthony's numbers based on clints 'new' 74X/76X el MVA measurement (https://indico.cern.ch/event/605620/contributions/2441087/attachments/1398025/2132153/VHFMeeting_X53_01.18.17.pdf)
		/* as given by anthony
			if(Pt>20. && Pt < 70.) ret = -7e-5*Pt*Pt + 0.0101*Pt + 0.4807;
        	else if(Pt<80) ret = 0.863;
        	else if(Pt<90) ret = 0.867;
        	else if(Pt>=90) ret = 0.875;
			float proj = -7e-5*Pt*Pt + 0.0101*Pt + 0.4807;
        	if(Pt<30) return 0.75-proj;
        	else if(Pt<70) return 0.01;
        	else if(Pt<90) return 0.004;
        	else return 0.0156;
		*/
		if(pt_el>20. && pt_el < 70.) weight = -7e-5*pt_el*pt_el + 0.0101*pt_el + 0.4807;
        else if(pt_el<80) weight = 0.863;
        else if(pt_el<90) weight = 0.867;
        else if(pt_el>=90)weight = 0.875;
		//std::cout << "elPR used (mode:"<<mode<<") = " << weight << " + " << "("<<prModeBehavior(mode)<<")"<<uPr(lep_info)<< std::endl;
		//std::cout << "Ele -- Mode: " << mode << ", pt: " << pt_el << ", eta: " << eta_el << ", weight: " << weight << ", prModeBehavior(mode): " << frModeBehavior(mode) << ", uFr: " << uFr(lep_info)<< ", weight + uFr(lep_info)*frModeBehavior(mode): " << weight + uFr(lep_info)*prModeBehavior(mode) << endl;
		return weight + uPr(lep_info)*prModeBehavior(mode);

	}
	else{
		//muon prompt rate
		double pt_mu = lep_info.at(2);
		double eta_mu = lep_info.at(3);
		double weight = 0.0;

		// PRv3, PRv4 - Clints AN2016_242_v9 values for MiniIso < 0.1 - http://cms.cern.ch/iCMS/jsp/openfile.jsp?tp=draft&files=AN2016_242_v9.pdf
		weight = 0.932; 
		//std::cout << "muPR used (mode:"<<mode<<") = " << weight << " + " << "("<<prModeBehavior(mode)<<")"<<uPr(lep_info)<< std::endl;
 		//std::cout << "Mu: Mode: " << mode << ", " << prModeBehavior(mode) << " * uPr: " << uPr(lep_info)<< endl;
		return weight + uPr(lep_info)*prModeBehavior(mode); 

	}
}
	
float Fr(int mode, std::vector<double> lep_info){
	if(lep_info.at(0)==0){
		//ele fake rate
		double pt_el = lep_info.at(2);
		double eta_el = lep_info.at(3);
		double weight = 0.0;
		
		if(lep_info.size()==4){ //before scan size is 4

			//FRv14, FRv14a - My 2D ddbkg fit measurement using PRv2 no btag fixed ST looseLepJetlean Full2016 HLTupdate Mu MiniIso < 0.1 !
			weight = 0.21 + uFr(lep_info)*frModeBehavior(mode); 

		}
		else{
			weight = lep_info.at(5);
		}

// 		std::cout << "elFR used = " << weight << std::endl;
// 		std::cout << "Ele -- Mode: " << mode << ", pt: " << pt_el << ", eta: " << eta_el << ", weight: " << weight << ", frModeBehavior(mode): " << frModeBehavior(mode) << ", uFr: " << uFr(lep_info)<< ", weight + uFr(lep_info)*frModeBehavior(mode): " << weight + uFr(lep_info)*frModeBehavior(mode) << endl;
				
		return weight; 


	}
	else{
		//muon fake rate
		double pt_mu = lep_info.at(2);
		double eta_mu = lep_info.at(3);
		double weight = 0.0;

		if(lep_info.size()==4) {  //before scan size is 4

			weight = 0.12 + uFr(lep_info)*frModeBehavior(mode); //My 2D ddbkg fit measurement using PRv2 no btag fixed ST looseLepJetlean Full2016 HLTupdate Mu MiniIso < 0.1 ! - I label this FRv14, FRv14a
		} 
		else{
			weight = lep_info.at(4);
		}
		
// 		std::cout << "muFR used = " << weight << std::endl;
// 		std::cout << "Mu -- " << " pt: " << pt_mu << ", eta: " << eta_mu << ", weight = " << weight << ", Mode: " << mode << ", frModeBehavior(mode): " << frModeBehavior(mode) << ", uFr: " << uFr(lep_info) << ", weight + uFr(lep_info)*frModeBehavior(mode): " << weight + uFr(lep_info)*frModeBehavior(mode) << endl;

		return weight;

	}
}

inline float uPr(std::vector<double> lep_info){

	if(lep_info.at(0)==0){
		//ele prompt rate unc

		//PRv4 
		double pt_el = lep_info.at(2);
		double eta_el = lep_info.at(3);
		float proj = -7e-5*pt_el*pt_el + 0.0101*pt_el + 0.4807;
        if(pt_el<30) return 0.75-proj;
        else if(pt_el<70) return 0.01;
        else if(pt_el<90) return 0.004;
        else return 0.0156;
	}
	else{
		//mu prompt rate unc

		return 0.001; // PRv3, PRv4
	}
}

inline float uFr(std::vector<double> lep_info){
	if(lep_info.at(0)==0){
		//ele fake rate unc
		return 0.01; //FRv14a more precise unc
	}
	else{
		//mu fake rate unc
		return 0.03; //FRv14, FRv14a
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
//mode 0 = nominal. 1 = fakerate plus, 2 = fakerate minus, 3 = passrate plus, 4 = passrate minus, 5 = q plus, 6 = q minus
inline int frModeBehavior(int mode){ return mode==1?1:(mode==2?-1:0); } //+1,-1 for 1,2, else 0
inline int prModeBehavior(int mode){ return mode==3?1:(mode==4?-1:0); } //+1,-1 for 3,4, else 0


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
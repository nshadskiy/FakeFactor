#ifndef __TNTUPLEANALYZER__
#define __TNTUPLEANALYZER__

#include "ViennaTool/NtupleClass.h"
#include "TLorentzVector.h"
#include "TChain.h"
//#include "TFile.h"
#include "TTree.h"
//#include "TH1D.h"
#include "TRandom3.h"
#include <vector>

#include "ViennaTool/Globals.h"

class TNtupleAnalyzer{
 public:
  TNtupleAnalyzer();
  ~TNtupleAnalyzer();

  void loadFile(TString filename, TString chain);
  void closeFile();
  void select(const TString preselectionFile, const Int_t mode);
  Int_t setTreeValues(const TString preselectionFile, const Int_t mode, const Int_t whichTau=1);
  Int_t findPos(const Double_t val, const std::vector<Double_t> *v_val);
  Int_t fitsGenCategory(const Int_t mode);
  Double_t calcDR(const Double_t eta1, const Double_t phi1, const Double_t eta2, const Double_t phi2);
  void initOutfileTree(TTree* tree);
  
  
 private:
  TString curr_sample;

  NtupleClass *event;

  TChain* tchain;
  // fields variables of SignalClass
  //    double mtll,mMuMu, dRMu, bpt_1, weight, sf, weight_sf, mu2_iso;//,mu1_eta, mu1_phi, mu2_eta, mu2_phi;
  double mt_leplep,m_leplep, lep_dR, bpt_1, weight, sf, weight_sf, mu2_iso;//,mu1_eta, mu1_phi, mu2_eta, mu2_phi;
  int passes3LVeto, passesDLVeto,njets,nbtag;
  double mjj,jdeta,njetingap20;
  double mvamet; double met;
  double otherLep_pt,otherLep_eta,otherLep_phi,otherLep_m,otherLep_iso;
  int    otherLep_q;
  double lep_pt,lep_eta,lep_phi,lep_m,lep_iso;
  double lep_vloose,lep_loose,lep_medium;
  int    lep_q, lep_gen_match;
  int n_iso_lep, n_iso_otherLep;
  int tau_iso_ind;

  std::vector<Double_t> *alltau_pt;
  std::vector<Double_t> *alltau_eta;
  std::vector<Double_t> *alltau_phi;
  std::vector<Double_t> *alltau_q;
  std::vector<Int_t> *alltau_decay;
  std::vector<Double_t> *alltau_beta;
  //    std::vector<Int_t> *alltau_looseBeta;
  std::vector<Int_t> *alltau_mediumBeta;
  //    std::vector<Int_t> *alltau_tightBeta;
  std::vector<Int_t> *alltau_vlooseMVA;
  std::vector<Int_t> *alltau_looseMVA;
  std::vector<Int_t> *alltau_mediumMVA;
  std::vector<Int_t> *alltau_tightMVA;
  std::vector<Int_t> *alltau_vtightMVA;

  std::vector<Int_t> *alltau_lepVeto;
  std::vector<Int_t> *alltau_gen_match;
  std::vector<Double_t> *alltau_dRToB;
  std::vector<Double_t> *alltau_dRToLep;
  std::vector<Double_t> *alltau_dRToOtherLep;
  std::vector<Double_t> *alltau_mvis;
  std::vector<Double_t> *alltau_mt;
  std::vector<Double_t> *alltau_mt2;
  std::vector<Double_t> *alltau_svfit;
  std::vector<Double_t> *alltau_Zpt;
  //    Int_t bin,gen_match_1,gen_match_2,mediumBeta,nAdditionalMu,passes3LVeto, passesDLVeto;
  //    Float_t q_2;
  //    Int_t gen_match_1,nAdditionalMu,passes3LVeto, passesDLVeto;

  // variables used in whole class
  Double_t* pt_cuts_Wjets,*pt_cuts_DY,*pt_cuts_TT,*pt_cuts_QCD,*pt_cuts_QCD_AI;
  Double_t* eta_cuts_Wjets,*eta_cuts_DY,*eta_cuts_TT,*eta_cuts_QCD;
  Int_t* decay_cuts_Wjets,*decay_cuts_DY,*decay_cuts_TT,*decay_cuts_QCD;
  Double_t* mt_cuts_Wjets,*mt_cuts_DY,*mt_cuts_TT,*mt_cuts_QCD;
  Int_t n_p_Wjets,n_p_DY,n_p_TT,n_p_QCD,n_p_QCD_AI;
  Int_t n_t_Wjets,n_t_DY,n_t_TT,n_t_QCD;
  Int_t n_e_Wjets,n_e_DY,n_e_TT,n_e_QCD;
  Int_t n_m_Wjets,n_m_DY,n_m_TT,n_m_QCD;

  //use for mtll correction
  Double_t corr_array[nFIT_BINS];
  //    Int_t corr_array_nbin;

  Double_t corr_d[NB_MTCORR], corr_k[NB_MTCORR];
  Double_t corr_d_err[NB_MTCORR], corr_k_err[NB_MTCORR], corr_SSxxOverN[NB_MTCORR], corr_avg_x[NB_MTCORR];
  Double_t sys_corr_d[NB_MTCORR], sys_corr_k[NB_MTCORR];

  TRandom3 r3;  
};



#endif

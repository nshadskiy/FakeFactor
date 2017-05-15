#ifndef __GLOBALCLASS__
#define __GLOBALCLASS__

#include "ViennaTool/SignalClass.h"
#include "ViennaTool/Globals.h"
#include "TLorentzVector.h"
#include "TChain.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TLegend.h"
#include "THStack.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TLatex.h"
#include "TChain.h"
#include "TStyle.h"
#include "TRandom3.h"
#include "TGraphAsymmErrors.h"

#include <vector>

class GlobalClass{
 public:
  GlobalClass();
  ~GlobalClass();

  void loadFile(TString filename, TString chain);
  void closeFile();
  void init();
  Int_t passesCuts(const Int_t cuts, const Int_t ind);
  Int_t isLoose(const Int_t mode=0, const Int_t ind=0);
  Int_t isTight_alt(const Int_t mode=0, const Int_t ind=0);
  Int_t isTight(const Int_t mode=0, const Int_t ind=0);
  Int_t isInSR(const Int_t mode, const Int_t ind=0);
  Int_t isInCR(const Int_t mode, const Int_t ind=0);
  Int_t isInAll(const Int_t mode, const Int_t ind=0);
  Int_t getWeightIndex_mt(const Double_t mt);
  Int_t getWeightIndex_pt(const Double_t pt);
  Int_t getWeightIndex_mttot(const Double_t mttot);
  Int_t getWeightIndex_mvis(const Double_t mvis);
  Int_t getWeightIndex_lepPt(const Double_t lepPt);
  Int_t getWeightIndex_muiso(const Double_t muiso);
  Int_t getWeightIndex_dm(const Int_t dm);
  Int_t getWeightBin(const Double_t pt, Int_t dm);
  Int_t getWeightBin(const Int_t ind=0);
  Int_t nBins(Int_t mode);
  Int_t getBin(const Int_t mode, const Int_t ind=0);
  Double_t getFittedBinContent( const Int_t mode, std::vector<TGraphAsymmErrors*> fittedFFs, const Int_t ind=0 );
  Int_t getTrackIndex(const Int_t mode, const Int_t ind=0);
  Int_t getPtIndex(const Int_t mode, const Int_t ind=0);
  Int_t getNjetIndex(const Int_t mode, const Int_t ind=0);
  Int_t getEtaIndex(const Int_t mode, const Int_t ind=0);
  Int_t getMtIndex(const Int_t mode, const Int_t ind=0);
  Int_t getIndex(const Double_t* a, const Int_t a_size, const Double_t val);
  Double_t selVal(const Int_t mode, const Int_t ind=0);
  Int_t getPInd( Int_t dm );
  Int_t fulfillCategory(Int_t categoryMode=0, Int_t ind=0);
  TString getCatString_noSel(Int_t categoryMode=0);
  TString getFracString(Int_t categoryMode=0);
  TString getChannelString(Int_t categoryMode=0);

  Int_t getNpts(const Int_t mode, const Int_t ind=0);
  Int_t getNtracks(const Int_t mode, const Int_t ind=0);
  Int_t getNjets(const Int_t mode, const Int_t ind=0);
  
  
  
 protected:
  TString curr_sample;
  SignalClass *event_s;
  TChain* tchain;

  // variables used in whole class
  //Double_t* pt_cuts_Wjets,*pt_cuts_DY,*pt_cuts_TT,*pt_cuts_QCD,*pt_cuts_QCD_AI;
  Double_t* pt_cuts_Wjets,*pt_cuts_DY,*pt_cuts_TT_SR,*pt_cuts_TT_CR,*pt_cuts_QCD,*pt_cuts_QCD_AI;
  Double_t* eta_cuts_Wjets,*eta_cuts_DY,*eta_cuts_TT,*eta_cuts_QCD;
  Int_t* decay_cuts_Wjets,*decay_cuts_DY,*decay_cuts_TT,*decay_cuts_QCD;
  Double_t* mt_cuts_Wjets,*mt_cuts_DY,*mt_cuts_TT,*mt_cuts_QCD;
  Int_t* njet_cuts_Wjets,*njet_cuts_DY,*njet_cuts_TT_SR,*njet_cuts_TT_CR,*njet_cuts_QCD;
  //Int_t* njet_cuts_Wjets,*njet_cuts_DY,*njet_cuts_TT,*njet_cuts_QCD;
  //Int_t n_p_Wjets,n_p_DY,n_p_TT,n_p_QCD,n_p_QCD_AI;
  Int_t n_p_Wjets,n_p_DY,n_p_TT_SR,n_p_TT_CR,n_p_QCD,n_p_QCD_AI;
  Int_t n_t_Wjets,n_t_DY,n_t_TT,n_t_QCD;
  Int_t n_e_Wjets,n_e_DY,n_e_TT,n_e_QCD;
  Int_t n_m_Wjets,n_m_DY,n_m_TT,n_m_QCD;
  //Int_t n_j_Wjets,n_j_DY,n_j_TT,n_j_QCD;
  Int_t n_j_Wjets,n_j_DY,n_j_TT_SR,n_j_TT_CR,n_j_QCD;

  //use for mtll correction
  Double_t corr_array[nFIT_BINS];
  //    Int_t corr_array_nbin;

  Double_t corr_d[NB_MTCORR], corr_k[NB_MTCORR];
  Double_t corr_d_err[NB_MTCORR], corr_k_err[NB_MTCORR], corr_SSxxOverN[NB_MTCORR], corr_avg_x[NB_MTCORR];
  Double_t sys_corr_d[NB_MTCORR], sys_corr_k[NB_MTCORR];

  
};



#endif

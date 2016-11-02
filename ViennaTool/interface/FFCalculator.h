#ifndef __FFCALCULATOR__
#define __FFCALCULATOR__

#include "HTTutilities/Jet2TauFakes/interface/WrapperTGraph.h"
#include "HTTutilities/Jet2TauFakes/interface/WrapperTH2F.h"
#include "HTTutilities/Jet2TauFakes/interface/WrapperTH3D.h"
#include "HTTutilities/Jet2TauFakes/interface/WrapperTFormula.h"
#include "HTTutilities/Jet2TauFakes/interface/IFunctionWrapper.h"
#include "HTTutilities/Jet2TauFakes/interface/FakeFactor.h"


#include "ViennaTool/interface/GlobalClass.h"
#include "ViennaTool/interface/PlotterClass.h"
#include "ViennaTool/interface/GaussianKernelSmoother.h"
#include "ViennaTool/src/GaussianKernelSmoother.cc"
#include "TFractionFitter.h"
#include "TH3D.h"
#include "TFormula.h"
#include "TF1.h"


class FFCalculator : public GlobalClass, public PlotterClass{
 public:
  FFCalculator();
  FFCalculator(//Int_t N_p_Wjets,Int_t N_p_DY,Int_t N_p_TT,Int_t N_p_QCD,Int_t N_p_QCD_AI,
               Int_t N_p_Wjets,Int_t N_p_DY,Int_t N_p_TT_SR,Int_t N_p_TT_CR,Int_t N_p_QCD,Int_t N_p_QCD_AI,
               Int_t N_eta_Wjets,Int_t N_eta_DY,Int_t N_eta_TT,Int_t N_eta_QCD,
               Int_t N_t_Wjets,Int_t N_t_DY,Int_t N_t_TT,Int_t N_t_QCD,
               Int_t N_m_Wjets,Int_t N_m_DY,Int_t N_m_TT,Int_t N_m_QCD,
               //Int_t N_j_Wjets,Int_t N_j_DY,Int_t N_j_TT,Int_t N_j_QCD,
               Int_t N_j_Wjets,Int_t N_j_DY,Int_t N_j_TT_SR,Int_t N_j_TT_CR,Int_t N_j_QCD,
               const Double_t Pt_cuts_Wjets[], const Double_t Pt_cuts_DY[], const Double_t Pt_cuts_TT_SR[], const Double_t Pt_cuts_TT_CR[], const Double_t Pt_cuts_QCD[], const Double_t Pt_cuts_QCD_AI[],
               const Double_t Eta_cuts_Wjets[],const Double_t Eta_cuts_DY[],const Double_t Eta_cuts_TT[],const Double_t Eta_cuts_QCD[],
               const Int_t Decay_cuts_Wjets[],const Int_t Decay_cuts_DY[],const Int_t Decay_cuts_TT[],const Int_t Decay_cuts_QCD[],
               const Double_t Mt_cuts_Wjets[],const Double_t Mt_cuts_DY[],const Double_t Mt_cuts_TT[],const Double_t Mt_cuts_QCD[],
               const Int_t Njet_cuts_Wjets[], const Int_t Njet_cuts_DY[], const Int_t Njet_cuts_TT_SR[], const Int_t Njets_cuts_TT_CR[], const Int_t Njet_cuts_QCD[]
               
                  );
  ~FFCalculator();

  void calcWeightFromFit(const TString fname, const TString m_path_img, const TString m_path_w, const TString isolation, Int_t mode=0);
  Int_t doTemplateFit(const TH1D *data, const std::vector<TH1D*> templates, const TString output_path, std::vector<TH1D*> &res, TH1D* &res_data, const Int_t mode);
  void calcFFCorr(const Int_t mode, const TString pre_main, const std::vector<TString> pre_sub, const TString FF_file, const TString weight_file="", const Int_t cuts=0);
  void calcBgEstFF(const std::vector<Int_t> mode, const std::vector<Int_t> nbins, const std::vector<Double_t> hist_min, const std::vector<Double_t> hist_max, const TString FFfile, const std::vector<TString> bg_est_file, const std::vector<TString> syst_file, const Int_t cuts=0, const TString corr_file="");
  void calcBgEstFF(const Int_t mode, const Int_t nbins, const Double_t hist_min, const Double_t hist_max, const TString FFfile, const TString bg_est_file, const std::vector<TString> syst_file,  const Int_t cuts=0, const TString corr_file="");
  TH1D* setCorrValue(const TString fname, const TString hname);
  Double_t getCorrValueFitErr(Double_t m_mt=-999, Int_t ind=-1);
  Double_t getCorrValueFit(Double_t m_corr_d=-999, const Double_t m_corr_k=-999, Int_t ind=0);
  double getCorrValue(const double value, const int err, TH1D* h_corr);
  TH1D* calcToyError(const std::vector<TH1D*> bg_est[NERR+1], const int ind );
  TH1D* calcToyError( TH1D* bg_est[NERR+1] );
  void createSystRatio(const TString fin1, const TString fin2, const TString fout, const int mode=0, const TString plotfile="", const int ratio=0, const int incl_stat_err=0);
  void createFitSystRatio(const TString FF1, const TString FF2, const TString pname1, const TString pname2, const int ind);
  void initCorrFit(const TString filename[NB_MTCORR], const TString plotfilename[NB_MTCORR], const TString formfilename="");
  void doCorrFit(const TString filename, const TString plotfilename, Double_t &m_corr_d, Double_t &m_corr_k, Double_t &m_corr_d_err, Double_t &m_corr_k_err, Double_t &m_corr_SSxxOverN, Double_t &m_corr_avg_x);
  
  void calcFFweights(const TString data_file, const std::vector<TString> weight_files, const std::vector<TString> presel_files, const TString m_path_img, const TString m_path_w="", const TString template_file="", Int_t mode=0);

  void applyFF(TString outfile, const std::vector<Int_t> mode, const Int_t categoryMode, TString fname=FF_inputFile, const Int_t cuts=0 );
  void applyFF_tt_raw(TString outfile, const std::vector<Int_t> mode, const Int_t categoryMode, TString fname=FF_inputFile, const Int_t cuts=0 );
  void applyFF_wUncertainties(TString outfile, const std::vector<Int_t> mode, const Int_t categoryMode, TString fname=FF_inputFile, const Int_t cuts=0, const Int_t tau_ind=0 );
  void getInputs(std::vector<double>&inputs, Int_t ind);
  void getSystUncertainties(const Int_t mode, TString ffname, const std::vector<TString> syst_file, TString outfile);

  void subtractBackground(TH1D* fakefactor_histo, TString fname, const Int_t mode, const Int_t categoryMode, Int_t cuts=0, Int_t tau_ind=0);

  void calc_nonclosure(const Int_t mode, const TString raw_ff, const TString compare_file, const TString ff_output, const Int_t doPlot=1, const Int_t subtractMC=1, const Int_t tau_ind=0 );
  void calc_muisocorr(const Int_t mode, const TString raw_ff, const TString CR_file, const TString nonclosure_corr, const TString ff_output, const Int_t doPlot=1, const Int_t subtractMC=1, const Int_t tau_ind=0 );
  void calc_mtcorr(const Int_t mode, const TString raw_ff, const TString CR_file, const TString nonclosure_corr, const TString ff_output, const Int_t tau_ind=0 );
  void calc_OSSScorr(const Int_t mode, const TString raw_ff, const TString SR_file_AI, const TString nonclosure_corr, const TString ff_output, const Int_t doPlot=1, const Int_t subtractMC=1, const Int_t tau_ind=0 );

  Double_t return_yvalue(Double_t xvalue, TGraphAsymmErrors* g);

};

#endif

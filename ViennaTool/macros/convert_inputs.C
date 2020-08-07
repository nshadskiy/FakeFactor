#include "TFile.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TGraphAsymmErrors.h"
#include "TString.h"
#include "ViennaTool/Globals.h"
#include "ViennaTool/interface/GaussianKernelSmoother.h"
#include <sstream>

void conv_th1_to_th2( const TString fn , const TString hn , const TString hnout , const TString fout_n , const int opt );
void conv_th1_to_th3( const TString fn , const TString hn, const TString hnout, const TString fout_n , const Int_t njetbinned=1 );
//void conv_th1_to_th2( const TString fn , const TString hn , const TString fout_n , const Int_t N_D1, const Int_t N_D2, const Double_t V1[], const Int_t V2[], const int ntoys=0 );
void make_frac_sys( const TString fn , const std::vector<TString> fn_other , const TString hn , const TString hnout , const std::vector<TString> hn_other , const TString fout_n , const int opt );
void make_frac_sys( const TString fn , const std::vector<TString> fn_other , const TString hn , const TString hnout , const std::vector<TString> hn_other , const TString fout_n , const Int_t N_D1, const Int_t N_D2, const Double_t V1[], const Int_t V2[], const int ntoys=0 );
void make_3Dhisto( TString fn , const TString hn , const TString hnout , const TString fout_n , Int_t N_D1, const Int_t N_D2, const Int_t N_D3, const Double_t V1[], const Double_t V2[], const Int_t V3[], Int_t njetbinned=1 );
void copy_th1( const TString fn , const TString hn , const TString fout_n );
void smooth_th1( const TString fn , const TString hn , const TString fout_n , const int useBinErrors=0 );
TH1D* extract_binerr_histo( TString fn , TString hn );
TString getCatString(Int_t categoryMode=0);

void convert_corrections( TString fn, TString gn, TString fout, TString gout, const TString tight_cat="");
void combineQCDSystematics( TString fQCD_nonclosure, TString sys_nonclosure, TString fQCD_muiso, TString fQCD_OSSS, TString sys_OSSS, TString sys_muiso, TString fout, TString tout, const TString tight_cat="");
void combineQCDSystematics_morphed( TString fQCD_nonclosure, TString sys_nonclosure, TString fQCD_muiso, TString fQCD_OSSS, TString sys_OSSS, TString sys_muiso, TString fout, TString tout, const TString tight_cat="");

void combineWSystematics( TString fW_nonclosure, TString sys_nonclosure, TString fW_mtcorr, TString sys_mtcorr, TString fout, TString tout, const TString tight_cat="");
void combineWSystematics_morphed( TString fW_nonclosure, TString sys_nonclosure, TString fW_mtcorr, TString sys_mtcorr, TString fout, TString tout, const TString tight_cat="");

void combineTTSystematics( TString fTT_nonclosure, TString sys_nonclosure, TString fout, TString tout, const TString tight_cat="");
void combineTTSystematics_morphed( TString fTT_nonclosure, TString sys_nonclosure, TString fout, TString tout, const TString tight_cat="");

void convert_inputs(Int_t inclusive=1, Int_t categoryMode=0){

  TString fn;
  TString fn3d;
  TString hn;
  TString hnout;
  TString hnout3d;
  TString fnD, fnW, fnT, fnQ;
  TString fout_n;
  TString fout_n3d;
  TString fout_nD, fout_nW, fout_nT, fout_nQ;

  TString catString=getCatString(categoryMode);
  cout << "------------------------------------------------------------------" << endl;
  cout << "------------------------------------------------------------------" << endl;
  cout << "------------------------------------------------------------------" << endl;
  cout << catString << endl;

  TString SSstring="";
  TString AIstring="";
  TString vtightString="";
  if(CALC_SS_SR) SSstring+="_SS_SR";
  if(CALC_SS_SR) AIstring+="_AI";

  TString data = (!DOMC) ? "data_" : "mc_";
  TString QCD = (DOMC && !DOQCD) ? "woQCD_" : "";
  TString MC = (DOMC) ? "_MC" : ""; 
  
  const TString d="ViennaTool/fakefactor/"+data+QCD+s_chan[CHAN]+"/";
  const TString o="ViennaTool/ff_2d/"+s_chan[CHAN]+MC+"/"+catString+"/";
  catString.ReplaceAll("incl","");
  

  if(inclusive){
    fn="FF_corr_Wjets_MCsum_noGen"+SSstring+".root";
    fn3d="FF_corr_Wjets_MCsum_noGen"+SSstring+".root";
    hn="c_t";
    hnout="FakeFactors_Data_HighMT_2D_Iso_Medium_InvertIso_Medium_tau_pt_vs_decayMode";
    hnout3d="FakeFactors_Data_HighMT_3D_Iso_Medium_InvertIso_Medium_tau_pt_vs_decayMode";
    fout_n="FakeFactors_Data_W_2D.root";
    fout_n3d="FakeFactors_Data_W_3D.root";
    //conv_th1_to_th2( d+fn , hn , hnout , o+fout_n , 0 );

    if(CHAN!=kTAU)conv_th1_to_th3( d+fn3d , hn , hnout3d , o+fout_n3d );
    fn="FF_corr_DY_MCsum_noGen.root";
    hn="c_t";
    hnout="c_t_2d";
    fout_n="ff_dy.root";
    //if(CHAN!=kTAU)conv_th1_to_th2( d+fn , hn , o+fout_n , hnout , 0 );
    
    //fn="FF_corr_TT_MCsum_noGen.root";
    fn="FF_TT_J_only_SR.root";
    hn="c_t";
    fout_n="FakeFactors_Data_TT_2D.root";
    fout_n3d="FakeFactors_Data_TT_3D.root";
    hnout="FakeFactors_Data_TT_anyb_addLep_InvertIso_tau_pt_vs_decayMode";
    hnout3d="FakeFactors_Data_TT_anyb_addLep_InvertIso_tau_pt_vs_decayMode";
    //conv_th1_to_th2( d+fn , hn , o+fout_n , hnout , 0 );
    if(CHAN!=kTAU)conv_th1_to_th3( d+fn , hn , hnout3d, o+fout_n3d );
    fn="FF_corr_QCD_MCsum_noGen"+AIstring+vtightString+".root";
    fn3d="FF_corr_QCD_MCsum_noGen"+AIstring+vtightString+".root";
    hn="c_t";
    hnout="FakeFactors_Data_QCDSS_2D_SS_Iso_Medium_SS_InvertIso_Medium_tau_pt_vs_decayMode";
    hnout3d="FakeFactors_Data_QCDSS_3D_SS_Iso_Medium_SS_InvertIso_Medium_tau_pt_vs_decayMode";
    fout_n="FakeFactors_Data_QCD_2D.root";
    fout_n3d="FakeFactors_Data_QCD_3D.root";
    //conv_th1_to_th2( d+fn , hn , hnout , o+fout_n , 0 );
    conv_th1_to_th3( d+fn3d , hn , hnout3d , o+fout_n3d ); 
    if(!DOMC){
      if(!CALC_SS_SR){
        if(CHAN==kTAU) {
          convert_corrections( d+"FF_corr_QCD_MCsum_noGen_nonclosure_lepPt.root", "nonclosure_QCD", o+"Correction_Data_QCD_PT.root", "QCD_SS_MuMedium_Data_FFSSMuMediumData_PT_correction");
          if( doNJetBinning ){
            convert_corrections( d+"FF_corr_QCD_MCsum_noGen_nonclosure_lepPt_0jet.root", "nonclosure_QCD", o+"Correction_Data_QCD_PT_0jet.root", "QCD_SS_MuMedium_Data_FFSSMuMediumData_PT_correction");
            convert_corrections( d+"FF_corr_QCD_MCsum_noGen_nonclosure_lepPt_1jet.root", "nonclosure_QCD", o+"Correction_Data_QCD_PT_1jet.root", "QCD_SS_MuMedium_Data_FFSSMuMediumData_PT_correction");
          }
        }

        convert_corrections( d+FF_corr_QCD_MCsum_noGen_nonclosure,      "nonclosure_QCD", o+"Correction_Data_QCD_MVis.root",      "QCD_SS_MuMedium_Data_FFSSMuMediumData_mvis_correction");
        if( doNJetBinning ){
          convert_corrections( d+FF_corr_QCD_MCsum_noGen_nonclosure_0jet, "nonclosure_QCD", o+"Correction_Data_QCD_MVis_0jet.root", "QCD_SS_MuMedium_Data_FFSSMuMediumData_mvis_correction");
          convert_corrections( d+FF_corr_QCD_MCsum_noGen_nonclosure_1jet, "nonclosure_QCD", o+"Correction_Data_QCD_MVis_1jet.root", "QCD_SS_MuMedium_Data_FFSSMuMediumData_mvis_correction");
        }
        convert_corrections( d+FF_corr_QCD_MCsum_noGen_OSSScorr,        "OSSS_corr_QCD",  o+"Correction_Data_QCD_OSSS.root", "QCD_SS_Data_FFSSMuMediumData_OSSS_correction");
          if( doNJetBinning ){
        convert_corrections( d+FF_corr_QCD_MCsum_noGen_OSSScorr_0jet,        "OSSS_corr_QCD",  o+"Correction_Data_QCD_OSSS_0jet.root", "QCD_SS_Data_FFSSMuMediumData_OSSS_correction");
        convert_corrections( d+FF_corr_QCD_MCsum_noGen_OSSScorr_1jet,        "OSSS_corr_QCD",  o+"Correction_Data_QCD_OSSS_1jet.root", "QCD_SS_Data_FFSSMuMediumData_OSSS_correction");
          }
        if(CHAN!=kTAU){
          convert_corrections( d+FF_corr_QCD_MCsum_noGen_muisocorr,         "muiso_QCD",        o+"Correction_Data_QCD_MuIso.root",      "QCD_SS_Data_FFSSMuMediumData_isomu_correction");
          if( doNJetBinning ){
            convert_corrections( d+FF_corr_QCD_MCsum_noGen_muisocorr_0jet,    "muiso_QCD",        o+"Correction_Data_QCD_MuIso_0jet.root", "QCD_SS_Data_FFSSMuMediumData_isomu_correction");
            convert_corrections( d+FF_corr_QCD_MCsum_noGen_muisocorr_1jet,    "muiso_QCD",        o+"Correction_Data_QCD_MuIso_1jet.root", "QCD_SS_Data_FFSSMuMediumData_isomu_correction");
          }
 
          //convert_corrections( d+FF_corr_Wjets_MCsum_noGen_nonclosure,      "nonclosure_Wjets", o+"Correction_Data_W_MVis.root",         "W_OS_Data_FFOSData_mvis_correction");
          convert_corrections( d+FF_corr_Wjets_MCsum_noGen_nonclosure,      "nonclosure_Wjets", o+"Correction_Data_W_lepPt.root",         "W_OS_Data_FFOSData_lepPt_correction");
          if( doNJetBinning ){
            convert_corrections( d+FF_corr_Wjets_MCsum_noGen_nonclosure_0jet, "nonclosure_Wjets", o+"Correction_Data_W_MVis_0jet.root",    "W_OS_Data_FFOSData_mvis_correction");
            convert_corrections( d+FF_corr_Wjets_MCsum_noGen_nonclosure_1jet, "nonclosure_Wjets", o+"Correction_Data_W_MVis_1jet.root",    "W_OS_Data_FFOSData_mvis_correction");
          }
          convert_corrections( d+FF_corr_Wjets_MC_noGen_mtcorr,             "mt_corr_Wjets",    o+"Correction_MC_W_MT.root",             "W_OS_MC_FFOSMC_mt_correction");
          if( doNJetBinning ){
            convert_corrections( d+FF_corr_Wjets_MC_noGen_mtcorr_0jet,        "mt_corr_Wjets",    o+"Correction_MC_W_MT_0jet.root",        "W_OS_MC_FFOSMC_mt_correction");
            convert_corrections( d+FF_corr_Wjets_MC_noGen_mtcorr_1jet,        "mt_corr_Wjets",    o+"Correction_MC_W_MT_1jet.root",        "W_OS_MC_FFOSMC_mt_correction");
          }
          convert_corrections( d+FF_corr_TT_MC_noGen_nonclosure,            "nonclosure_TT_MC", o+"Correction_MC_TT_MVis.root",     "TT_OS_MC_mvis_correction");
        }
      }
      else{
        convert_corrections( d+FF_corr_QCD_MCsum_noGen_nonclosure_AI,         "nonclosure_QCD",      o+"Correction_Data_QCD_MVis.root",    "QCD_SS_MuMedium_Data_FFSSMuMediumData_mvis_correction");
        convert_corrections( d+FF_corr_QCD_MCsum_noGen_muisocorr_AI,          "muiso_QCD",           o+"Correction_Data_QCD_MuIso.root",   "QCD_SS_Data_FFSSMuMediumData_isomu_correction");
        convert_corrections( d+FF_corr_Wjets_MCsum_noGen_nonclosure_SS_SR,    "nonclosure_Wjets",    o+"Correction_Data_W_MVis.root",      "W_OS_Data_FFOSData_mvis_correction");
        convert_corrections( d+FF_corr_Wjets_MC_noGen_mtcorr_SS_SR,           "mt_corr_Wjets",       o+"Correction_MC_W_MT.root",          "W_OS_MC_FFOSMC_mt_correction");
      }
      
      if(!CALC_SS_SR){
        if(CHAN==kTAU){
          combineQCDSystematics( d+FF_corr_QCD_MCsum_noGen_nonclosure,        "nonclosure_QCD_up",    d+"FF_corr_QCD_MCsum_noGen_nonclosure_lepPt.root", "nonclosure_QCD_up",   d+FF_corr_QCD_MCsum_noGen_OSSScorr, "OSSS_corr_QCD_up",  o+"uncertainties_QCD_W.root", "uncertainties_QCD_MVis_Iso_SS2OS_up");
          combineQCDSystematics( d+FF_corr_QCD_MCsum_noGen_nonclosure,        "nonclosure_QCD_down",  d+"FF_corr_QCD_MCsum_noGen_nonclosure_lepPt.root", "nonclosure_QCD_down", d+FF_corr_QCD_MCsum_noGen_OSSScorr, "OSSS_corr_QCD_down", o+"uncertainties_QCD_W.root", "uncertainties_QCD_MVis_Iso_SS2OS_down");
          combineQCDSystematics_morphed( d+FF_corr_QCD_MCsum_noGen_nonclosure,        "nonclosure_QCD",  d+"FF_corr_QCD_MCsum_noGen_nonclosure_lepPt.root", "nonclosure_QCD", d+FF_corr_QCD_MCsum_noGen_OSSScorr, "OSSS_corr_QCD", o+"uncertainties_QCD_W.root", "uncertainties_QCD_MVis_Iso_SS2OS");
          combineQCDSystematics_morphed( d+FF_corr_QCD_MCsum_noGen_nonclosure_0jet,        "nonclosure_QCD",  d+"FF_corr_QCD_MCsum_noGen_nonclosure_lepPt_0jet.root", "nonclosure_QCD", d+FF_corr_QCD_MCsum_noGen_OSSScorr_0jet, "OSSS_corr_QCD", o+"uncertainties_QCD_W_0jet.root", "uncertainties_QCD_MVis_Iso_SS2OS");
          combineQCDSystematics_morphed( d+FF_corr_QCD_MCsum_noGen_nonclosure_1jet,        "nonclosure_QCD",  d+"FF_corr_QCD_MCsum_noGen_nonclosure_lepPt_1jet.root", "nonclosure_QCD", d+FF_corr_QCD_MCsum_noGen_OSSScorr_1jet, "OSSS_corr_QCD", o+"uncertainties_QCD_W_1jet.root", "uncertainties_QCD_MVis_Iso_SS2OS");

          combineQCDSystematics( d+FF_corr_QCD_MCsum_noGen_nonclosure,        "nonclosure_mcup_QCD",    d+"FF_corr_QCD_MCsum_noGen_nonclosure_lepPt.root", "nonclosure_mcup_QCD",   d+FF_corr_QCD_MCsum_noGen_OSSScorr, "OSSS_corr_QCD_up",  o+"uncertainties_QCD_W.root", "uncertainties_QCD_MVis_Iso_SS2OS_mcup");
          combineQCDSystematics( d+FF_corr_QCD_MCsum_noGen_nonclosure,        "nonclosure_mcdown_QCD",  d+"FF_corr_QCD_MCsum_noGen_nonclosure_lepPt.root", "nonclosure_mcdown_QCD", d+FF_corr_QCD_MCsum_noGen_OSSScorr, "OSSS_corr_QCD_down", o+"uncertainties_QCD_W.root", "uncertainties_QCD_MVis_Iso_SS2OS_mcdown");
        }else{
          combineQCDSystematics( d+FF_corr_QCD_MCsum_noGen_nonclosure,        "nonclosure_QCD_up",    d+FF_corr_QCD_MCsum_noGen_muisocorr, "muiso_corr_QCD_up",   d+FF_corr_QCD_MCsum_noGen_OSSScorr, "OSSS_corr_QCD_up",  o+"uncertainties_QCD_W.root", "uncertainties_QCD_MVis_Iso_SS2OS_up");
          combineQCDSystematics( d+FF_corr_QCD_MCsum_noGen_nonclosure,        "nonclosure_QCD_down",  d+FF_corr_QCD_MCsum_noGen_muisocorr, "muiso_corr_QCD_down", d+FF_corr_QCD_MCsum_noGen_OSSScorr, "OSSS_corr_QCD_down", o+"uncertainties_QCD_W.root",  "uncertainties_QCD_MVis_Iso_SS2OS_down");
          combineQCDSystematics_morphed( d+FF_corr_QCD_MCsum_noGen_nonclosure,        "nonclosure_QCD",    d+FF_corr_QCD_MCsum_noGen_muisocorr, "muiso_corr_QCD",   d+FF_corr_QCD_MCsum_noGen_OSSScorr, "OSSS_corr_QCD",  o+"uncertainties_QCD_W.root", "uncertainties_QCD_MVis_Iso_SS2OS_morphed");
          combineQCDSystematics( d+FF_corr_QCD_MCsum_noGen_nonclosure,        "nonclosure_mcup_QCD",    d+FF_corr_QCD_MCsum_noGen_muisocorr, "muiso_mcup_QCD",   d+FF_corr_QCD_MCsum_noGen_OSSScorr, "OSSS_corr_QCD_up",  o+"uncertainties_QCD_W.root", "uncertainties_QCD_MVis_Iso_SS2OS_mcup");
          combineQCDSystematics( d+FF_corr_QCD_MCsum_noGen_nonclosure,        "nonclosure_mcdown_QCD",  d+FF_corr_QCD_MCsum_noGen_muisocorr, "muiso_mcdown_QCD", d+FF_corr_QCD_MCsum_noGen_OSSScorr, "OSSS_corr_QCD_down", o+"uncertainties_QCD_W.root",  "uncertainties_QCD_MVis_Iso_SS2OS_mcdown");
        }
        if(CHAN!=kTAU){

          combineWSystematics( d+FF_corr_Wjets_MCsum_noGen_nonclosure, "nonclosure_Wjets_up",   d+FF_corr_Wjets_MC_noGen_mtcorr, "mt_corr_Wjets_up",   o+"uncertainties_QCD_W.root", "uncertainties_W_MVis_MT_up" );
          combineWSystematics( d+FF_corr_Wjets_MCsum_noGen_nonclosure, "nonclosure_Wjets_down", d+FF_corr_Wjets_MC_noGen_mtcorr, "mt_corr_Wjets_down", o+"uncertainties_QCD_W.root", "uncertainties_W_MVis_MT_down" );
          combineWSystematics_morphed( d+FF_corr_Wjets_MCsum_noGen_nonclosure, "nonclosure_Wjets",   d+FF_corr_Wjets_MC_noGen_mtcorr, "mt_corr_Wjets",   o+"uncertainties_QCD_W.root", "uncertainties_W_MVis_MT_morphed" );
          combineWSystematics( d+FF_corr_Wjets_MCsum_noGen_nonclosure, "nonclosure_mcup_Wjets",   d+FF_corr_Wjets_MC_noGen_mtcorr, "mt_corr_Wjets_up",   o+"uncertainties_QCD_W.root", "uncertainties_W_MVis_MT_mcup" );
          combineWSystematics( d+FF_corr_Wjets_MCsum_noGen_nonclosure, "nonclosure_mcdown_Wjets", d+FF_corr_Wjets_MC_noGen_mtcorr, "mt_corr_Wjets_down", o+"uncertainties_QCD_W.root", "uncertainties_W_MVis_MT_mcdown" );
          combineTTSystematics( d+FF_corr_TT_MC_noGen_nonclosure, "nonclosure_TT_MC_up",   o+"uncertainties_TT.root", "uncertainties_TT_MVis_up" );
          combineTTSystematics( d+FF_corr_TT_MC_noGen_nonclosure, "nonclosure_TT_MC_down", o+"uncertainties_TT.root", "uncertainties_TT_MVis_down" );
          combineTTSystematics_morphed( d+FF_corr_TT_MC_noGen_nonclosure, "nonclosure_TT_MC", o+"uncertainties_TT.root", "uncertainties_TT_MVis" );

        }
      }
      else{
        combineQCDSystematics( d+FF_corr_QCD_MCsum_noGen_nonclosure_AI,    "nonclosure_QCD_up",     d+FF_corr_QCD_MCsum_noGen_muisocorr_AI, "muiso_corr_QCD_up",   d+FF_corr_QCD_MCsum_noGen_OSSScorr, "OSSS_corr_QCD_up",o+"uncertainties_QCD_W.root", "uncertainties_QCD_MVis_Iso_SS2OS_up");
        combineQCDSystematics( d+FF_corr_QCD_MCsum_noGen_nonclosure_AI,    "nonclosure_QCD_down",   d+FF_corr_QCD_MCsum_noGen_muisocorr_AI, "muiso_corr_QCD_down", d+FF_corr_QCD_MCsum_noGen_OSSScorr, "OSSS_corr_QCD_up", o+"uncertainties_QCD_W.root", "uncertainties_QCD_MVis_Iso_SS2OS_down");
        
        combineWSystematics( d+FF_corr_Wjets_MCsum_noGen_nonclosure_SS_SR, "nonclosure_Wjets_up",   d+FF_corr_Wjets_MC_noGen_mtcorr_SS_SR, "mt_corr_Wjets_up",     o+"uncertainties_QCD_W.root",       "uncertainties_W_MVis_MT_up" );
        combineWSystematics( d+FF_corr_Wjets_MCsum_noGen_nonclosure_SS_SR, "nonclosure_Wjets_down", d+FF_corr_Wjets_MC_noGen_mtcorr_SS_SR, "mt_corr_Wjets_down",   o+"uncertainties_QCD_W.root",       "uncertainties_W_MVis_MT_down" );
      }
    }
  }
    
  // fnW="weight_Wjets"+catString+SSstring+".root";
  // hn="h_w";
  // fout_nW="frac_wjets.root";

  // fnD="weight_DY_J"+catString+SSstring+".root";
  // hn="h_w";
  // fout_nD="frac_dy.root";

  // fnT="weight_TT_J"+catString+SSstring+".root";
  // hn="h_w";
  // fout_nT="frac_tt.root";

  // fnQ="weight_QCD"+catString+SSstring+".root";
  // hn="h_w";
  // fout_nQ="frac_qcd.root";

  // hnout="h_w_2d";

  // //stat. unc. of fractions
  // std::vector<TString> fn_other_w; fn_other_w.push_back( d+fnD ); fn_other_w.push_back( d+fnT ); fn_other_w.push_back( d+fnQ );
  // std::vector<TString> fn_other_d; fn_other_d.push_back( d+fnW ); fn_other_d.push_back( d+fnT ); fn_other_d.push_back( d+fnQ );
  // std::vector<TString> fn_other_t; fn_other_t.push_back( d+fnW ); fn_other_t.push_back( d+fnD ); fn_other_t.push_back( d+fnQ );
  // std::vector<TString> fn_other_q; fn_other_q.push_back( d+fnW ); fn_other_q.push_back( d+fnD ); fn_other_q.push_back( d+fnT );

  // std::vector<TString> hn_other_w; hn_other_w.push_back( hn+"D"); hn_other_w.push_back( hn+"T"); hn_other_w.push_back( hn+"Q");
  // std::vector<TString> hn_other_d; hn_other_d.push_back( hn+"W"); hn_other_d.push_back( hn+"T"); hn_other_d.push_back( hn+"Q");
  // std::vector<TString> hn_other_t; hn_other_t.push_back( hn+"W"); hn_other_t.push_back( hn+"D"); hn_other_t.push_back( hn+"Q");
  // std::vector<TString> hn_other_q; hn_other_q.push_back( hn+"W"); hn_other_q.push_back( hn+"D"); hn_other_q.push_back( hn+"T");

  // make_frac_sys( d+fnW , fn_other_w , hn , hnout , hn_other_w , o+fout_nW , 1 );
  // make_frac_sys( d+fnD , fn_other_d , hn , hnout , hn_other_d , o+fout_nD , 1 );
  // make_frac_sys( d+fnT , fn_other_t , hn , hnout , hn_other_t , o+fout_nT , 1 );
  // make_frac_sys( d+fnQ , fn_other_q , hn , hnout , hn_other_q , o+fout_nQ , 1 );


}

void conv_th1_to_th2( const TString fn , const TString hn , const TString hnout , const TString fout_n , const int opt ){

  std::vector<TString> dummy(0);
  make_frac_sys( fn , dummy , hn , hnout , dummy , fout_n , opt );

}

void conv_th1_to_th3( const TString fn , const TString hn, const TString hnout, const TString fout_n, const Int_t njetbinned ){
  if(fn.Contains("_Wjets")) make_3Dhisto( fn, hn, hnout, fout_n, N_p_Wjets, N_dR_Wjets, N_j_Wjets, Pt_cuts_Wjets, dRTauLep_cuts_Wjets, Njet_cuts_Wjets, njetbinned );
  else if(fn.Contains("_QCD")) make_3Dhisto( fn, hn, hnout, fout_n, N_p_QCD, N_t_QCD, N_j_QCD, Pt_cuts_QCD, dRTauLep_cuts_QCD, Njet_cuts_QCD, njetbinned );
  else if(fn.Contains("_TT")) make_3Dhisto( fn, hn, hnout, fout_n, N_dR_TT_SR, N_t_TT, N_j_TT_SR, Pt_cuts_TT_SR, dRTauLep_cuts_TT_SR, Njet_cuts_TT_SR, njetbinned );
  else make_3Dhisto( fn, hn, hnout, fout_n, N_p_Wjets, N_dR_Wjets, N_j_Wjets, Pt_cuts_Wjets, dRTauLep_cuts_Wjets, Njet_cuts_Wjets, njetbinned );
  
}

void make_3Dhisto( TString fn , const TString hn , const TString hnout , const TString fout_n , Int_t N_D1, const Int_t N_D2, const Int_t N_D3, const Double_t V1[], const Double_t V2[], const Int_t V3[] , Int_t njetbinned ){

  cout << "make_3D_histo \t" << fn << "\t" << hn << "\t" << fout_n << "\t" << endl;

  ///////////////////////////////////////////////////////////////////////////////////////////////////////
  //Getting TT scalefactors from CR
  vector<Double_t> scale_factors;
  if(CHAN==kTAU || DOMC){
    scale_factors.push_back(1.); scale_factors.push_back(1.);
  }
  else{
    TString tight_cat="";
    const TString d="ViennaTool/fakefactor/data_"+s_chan[CHAN]+"/";
    TFile *f_data_CR=new TFile(d+"FF_corr_TT_MCsum_noGen.root");
    cout << "f_data_CR: " << d+"FF_corr_TT_MCsum_noGen.root" << endl;
    cout << "f_MC_CR: " << d+"FF_TT_J_only.root" << endl;
    cout << "CR Histogram: " << hn << endl;
    TH1D *h_data_CR= (TH1D*)f_data_CR->Get(hn);
    TFile *f_MC_CR=new TFile(d+"FF_TT_J_only.root");
    TH1D *h_MC_CR= (TH1D*)f_MC_CR->Get(hn);
    //for(int i=1; i<=h_data_CR->GetNbinsX(); i++){
    for(int i=1; i<=2; i++){
      if( sizeof(Decay_cuts_Wjets)/sizeof(Decay_cuts_Wjets[0]) > 1 ){
        if(fn.Contains("TT")) scale_factors.push_back( abs(h_data_CR->GetBinContent(i)/h_MC_CR->GetBinContent(i) ) );  
        else scale_factors.push_back(1.);
      }else{
        if(fn.Contains("TT")) scale_factors.push_back( abs(h_data_CR->GetBinContent(1)/h_MC_CR->GetBinContent(1) ) );  //if decay mode is not considered -> only use 1 bin
        else scale_factors.push_back(1.);
      }
      cout << "Scale factor " << i-1 << " :" << scale_factors.at(i-1) << endl;
    }
  }
  ////////////////////////////////////////////////////////////////////////////////////////////////////////

  if(fit_pT_bins) N_D1=fitBins;
  Double_t d1[N_D1+1];
  Double_t d2[N_D2+1];
  Double_t d3[N_D3+1];

  if(fit_pT_bins){
    N_D1=fitBins;
    for (int i=0; i<=N_D1; i++){
      d1[i]=fitMin+i*(fitMax-fitMin)/fitMax;
    }
  }
  else{
    for (int i=0; i<N_D1; i++){
      d1[i]=V1[i];
    }
    d1[N_D1]=250;
  }
  for (int i=0; i<N_D2; i++){
    d2[i]=V2[i];
  }
  d2[N_D2]=15;

  for (int i=0; i<N_D3; i++){
    d3[i]=V3[i];
  }
  d3[N_D3]=10;
  if(fit_pT_bins) fn.ReplaceAll(".root","_fitted.root");
  TFile *f=new TFile( fn );
  cout << "HistoNames: "<< hnout << endl;
  TH3D *hout                      = new TH3D( hnout,                             "",  N_D1 , d1,  N_D2 ,  d2 , N_D3 , d3 );
  TH3D *hout_err_low              = new TH3D( hnout+"_error_low",                "",  N_D1 , d1,  N_D2 ,  d2 , N_D3 , d3 );
  TH3D *hout_err_dr0_njet0_low    = new TH3D( hnout+"_error_dr0_njet0_low",      "",  N_D1 , d1,  N_D2 ,  d2 , N_D3 , d3 );
  TH3D *hout_err_dr0_njet1_low    = new TH3D( hnout+"_error_dr0_njet1_low",      "",  N_D1 , d1,  N_D2 ,  d2 , N_D3 , d3 );
  TH3D *hout_err_dr0_njet2_low    = new TH3D( hnout+"_error_dr0_njet2_low",      "",  N_D1 , d1,  N_D2 ,  d2 , N_D3 , d3 );
  TH3D *hout_err_dr1_njet0_low    = new TH3D( hnout+"_error_dr1_njet0_low",      "",  N_D1 , d1,  N_D2 ,  d2 , N_D3 , d3 );
  TH3D *hout_err_dr1_njet1_low    = new TH3D( hnout+"_error_dr1_njet1_low",      "",  N_D1 , d1,  N_D2 ,  d2 , N_D3 , d3 );
  TH3D *hout_err_dr1_njet2_low    = new TH3D( hnout+"_error_dr1_njet2_low",      "",  N_D1 , d1,  N_D2 ,  d2 , N_D3 , d3 );

  TH3D *hout_err_high             = new TH3D( hnout+"_error_high",               "",  N_D1 , d1,  N_D2 ,  d2 , N_D3 , d3 );
  TH3D *hout_err_dr0_njet0_high   = new TH3D( hnout+"_error_dr0_njet0_high",     "",  N_D1 , d1,  N_D2 ,  d2 , N_D3 , d3 );
  TH3D *hout_err_dr0_njet1_high   = new TH3D( hnout+"_error_dr0_njet1_high",     "",  N_D1 , d1,  N_D2 ,  d2 , N_D3 , d3 );
  TH3D *hout_err_dr0_njet2_high   = new TH3D( hnout+"_error_dr0_njet2_high",     "",  N_D1 , d1,  N_D2 ,  d2 , N_D3 , d3 );
  TH3D *hout_err_dr1_njet0_high   = new TH3D( hnout+"_error_dr1_njet0_high",     "",  N_D1 , d1,  N_D2 ,  d2 , N_D3 , d3 );
  TH3D *hout_err_dr1_njet1_high   = new TH3D( hnout+"_error_dr1_njet1_high",     "",  N_D1 , d1,  N_D2 ,  d2 , N_D3 , d3 );
  TH3D *hout_err_dr1_njet2_high   = new TH3D( hnout+"_error_dr1_njet2_high",     "",  N_D1 , d1,  N_D2 ,  d2 , N_D3 , d3 );

  TH3D *hout_err_mc_low    = new TH3D( hnout+"_error_mc_low",      "",  N_D1 , d1,  N_D2 ,  d2 , N_D3 , d3 );
  TH3D *hout_err_mc_high   = new TH3D( hnout+"_error_mc_high",     "",  N_D1 , d1,  N_D2 ,  d2 , N_D3 , d3 );

  TH3D *hout_err_dr0_njet0_morphed_low    = new TH3D( hnout+"_error_dr0_njet0_morphed_low",      "",  N_D1 , d1,  N_D2 ,  d2 , N_D3 , d3 );
  TH3D *hout_err_dr0_njet0_morphed_high    = new TH3D( hnout+"_error_dr0_njet0_morphed_high",      "",  N_D1 , d1,  N_D2 ,  d2 , N_D3 , d3 );
  TH3D *hout_err_dr0_njet1_morphed_low    = new TH3D( hnout+"_error_dr0_njet1_morphed_low",      "",  N_D1 , d1,  N_D2 ,  d2 , N_D3 , d3 );
  TH3D *hout_err_dr0_njet1_morphed_high    = new TH3D( hnout+"_error_dr0_njet1_morphed_high",      "",  N_D1 , d1,  N_D2 ,  d2 , N_D3 , d3 );
  TH3D *hout_err_dr0_njet2_morphed_low    = new TH3D( hnout+"_error_dr0_njet2_morphed_low",      "",  N_D1 , d1,  N_D2 ,  d2 , N_D3 , d3 );
  TH3D *hout_err_dr0_njet2_morphed_high    = new TH3D( hnout+"_error_dr0_njet2_morphed_high",      "",  N_D1 , d1,  N_D2 ,  d2 , N_D3 , d3 );

  TH3D *hout_err_dr1_njet0_morphed_low    = new TH3D( hnout+"_error_dr1_njet0_morphed_low",      "",  N_D1 , d1,  N_D2 ,  d2 , N_D3 , d3 );
  TH3D *hout_err_dr1_njet0_morphed_high    = new TH3D( hnout+"_error_dr1_njet0_morphed_high",      "",  N_D1 , d1,  N_D2 ,  d2 , N_D3 , d3 );
  TH3D *hout_err_dr1_njet1_morphed_low    = new TH3D( hnout+"_error_dr1_njet1_morphed_low",      "",  N_D1 , d1,  N_D2 ,  d2 , N_D3 , d3 );
  TH3D *hout_err_dr1_njet1_morphed_high    = new TH3D( hnout+"_error_dr1_njet1_morphed_high",      "",  N_D1 , d1,  N_D2 ,  d2 , N_D3 , d3 );
  TH3D *hout_err_dr1_njet2_morphed_low    = new TH3D( hnout+"_error_dr1_njet2_morphed_low",      "",  N_D1 , d1,  N_D2 ,  d2 , N_D3 , d3 );
  TH3D *hout_err_dr1_njet2_morphed_high    = new TH3D( hnout+"_error_dr1_njet2_morphed_high",      "",  N_D1 , d1,  N_D2 ,  d2 , N_D3 , d3 );




  TString replaceString=hnout;
  replaceString.ReplaceAll("_3d","");
  

  if(fit_pT_bins){
    Double_t err_dr0njet0=0;
    Double_t err_dr0njet1=0;
    Double_t err_dr0njet2=0;

    Double_t err_dr1njet0=0;
    Double_t err_dr1njet1=0;
    Double_t err_dr1njet2=0;

    if(useExtraFitUncertainties){
      if( CHAN==kMU){
        if(fn.Contains("_QCD")){
          err_dr0njet0=QCD_fitErr_dm0njet0_mt; 
          err_dr0njet1=QCD_fitErr_dm0njet1_mt; 
          err_dr0njet2=QCD_fitErr_dm0njet1_mt; 
        } else if(fn.Contains("_Wjets")){
          err_dr0njet0=W_fitErr_dm0njet0_mt; 
          err_dr0njet1=W_fitErr_dm0njet1_mt; 
          err_dr1njet0=W_fitErr_dm0njet0_mt; 
          err_dr1njet1=W_fitErr_dm0njet1_mt; 
          err_dr0njet2=W_fitErr_dm0njet1_mt; 
          err_dr1njet2=W_fitErr_dm0njet1_mt; 
        }
      }
      else if( CHAN==kEL ){
        if(fn.Contains("_QCD")){
          err_dr0njet0=QCD_fitErr_dm0njet0_et; 
          err_dr0njet1=QCD_fitErr_dm0njet1_et; 
          err_dr0njet2=QCD_fitErr_dm0njet1_et; 
        } else if(fn.Contains("_Wjets")){
          err_dr0njet0=W_fitErr_dm0njet0_et; 
          err_dr0njet1=W_fitErr_dm0njet1_et; 
          err_dr1njet0=W_fitErr_dm0njet0_et; 
          err_dr1njet1=W_fitErr_dm0njet1_et; 
          err_dr0njet2=W_fitErr_dm0njet1_et; 
          err_dr1njet2=W_fitErr_dm0njet1_et; 
        }
      }
      else if( CHAN==kTAU ){
        if(fn.Contains("_QCD")){
          err_dr0njet0=QCD_fitErr_dm0njet0_tt; 
          err_dr0njet1=QCD_fitErr_dm0njet1_tt; 
          err_dr0njet2=QCD_fitErr_dm0njet1_tt; 

        }
      }
    }
    
    std::cout << "fn: " << fn << std::endl;
    for (int idr=0; idr<N_D2; idr++){
      for (int ijet=0; ijet<N_D3; ijet++){
        stringstream fitted_histo; fitted_histo << "dm0" << "_njet" << ijet << "dR" << idr ;
        stringstream func_name; func_name << "f_dm0" << "_njet" << ijet << "dR" << idr ;
        stringstream fitted_histo_mcup; fitted_histo_mcup << "dm0" << "_njet" << ijet << "dR" << idr << "_mcup";
        stringstream fitted_histo_mcdown; fitted_histo_mcdown << "dm0" << "_njet" << ijet << "dR" << idr <<  "_mcdown";
        std::cout << fitted_histo.str().c_str() << std::endl;
        std::cout << fitted_histo_mcup.str().c_str() << std::endl;
        std::cout << fitted_histo_mcdown.str().c_str() << std::endl;
    
        TGraphAsymmErrors *h=(TGraphAsymmErrors*) f->Get(fitted_histo.str().c_str());
        TGraphAsymmErrors *h_mcup=(TGraphAsymmErrors*) f->Get(fitted_histo_mcup.str().c_str());
        TGraphAsymmErrors *h_mcdown=(TGraphAsymmErrors*) f->Get(fitted_histo_mcdown.str().c_str());

        TF1 *f_fit = (TF1*) f->Get(func_name.str().c_str());
        double err1 = f_fit->GetParError(0);
        double err2 = f_fit->GetParError(1);
        double x=0; double cont=0;  double cont_mcup=0;  double cont_mcdown=0;
        double y_value = 0;
        double param1 = f_fit->GetParameter(0);
        double param2 = f_fit->GetParameter(1);
        double pthist_max = 0.0;
        if(fn.Contains("TT")) pthist_max = 200.;
        else pthist_max =  80.;

          double crossing1; double crossing2;
          double startpoint1; double startpoint2;

          if(fn.Contains("TT")) {
          crossing1 = 60.;
          crossing2 = 120.;
          }
          else {
          crossing1 = 40.;
          crossing2 = 60.;
          }
          startpoint1 = param1 - err2*crossing1;
          startpoint2 = param1 - 0.5*err2*crossing2;
          double lepPt_max = 120.0;
          Int_t n_morph_pt = 0; Int_t i_morph_pt = 0;
          for (int ipt=0; h->GetX()[ipt]<lepPt_max; ipt++){
            n_morph_pt += 1;
            i_morph_pt = ipt;
            }
          std::cout << i_morph_pt << std::endl;
        for (int ipt=0; ipt<fitBins; ipt++){
          h->GetPoint( ipt + 1,x,cont );
          h_mcup->GetPoint( ipt + 1,x,cont_mcup );
          h_mcdown->GetPoint( ipt + 1,x,cont_mcdown );

          // cont = cont*scale_factors.at(idr);
          y_value = x*(param2+err2)+param1;
          double err_low=h->GetErrorYlow(ipt+1);
          double err_high=h->GetErrorYhigh(ipt+1);
          if(ipt+1==fitBins) {err_low=h->GetErrorYlow(ipt); err_high=h->GetErrorYhigh(ipt);}
          hout->SetBinContent(       ipt+1 , idr+1 , ijet+1 , cont );
          //if(fn.Contains("Wjets") && idr==0 && ijet==0)cout << ipt << " " << hout->GetBinContent(ipt+1,idr+1,ijet+1) << endl;
          hout->SetBinError(         ipt+1 , idr+1 , ijet+1 , (err_low+err_high)/2 );
          hout_err_low->SetBinContent(       ipt+1 , idr+1 , ijet+1 , err_low/cont );
          hout_err_low->SetBinError(       ipt+1 , idr+1 , ijet+1 , err_low );
          hout_err_mc_low->SetBinContent(       ipt+1 , idr+1 , ijet+1 , (cont-cont_mcup)/cont );
          hout_err_mc_low->SetBinError(       ipt+1 , idr+1 , ijet+1 , 0 );
          hout_err_high->SetBinContent(       ipt+1 , idr+1 , ijet+1 , err_high/cont );
          hout_err_high->SetBinError(       ipt+1 , idr+1 , ijet+1 , err_high );
          hout_err_mc_high->SetBinContent(       ipt+1 , idr+1 , ijet+1 , (cont-cont_mcdown)/cont );
          hout_err_mc_high->SetBinError(       ipt+1 , idr+1 , ijet+1 , 0 );
          double param1_error; double param2_error;

          param1_error = err1;
          if (x<pthist_max) {
            param2_error = cont - (x*(param2-err2)+param1);
          }
          else {
            param2_error =  cont - (pthist_max*(param2-err2)+param1);
          }
          double morphed_high; double morphed_low;
          double morphed_high_constant; double morphed_low_constant;
          double cmb_low; double cmb_high;
          cmb_low = TMath::Sqrt( TMath::Power(err_low/cont,2) + TMath::Power(err_dr0njet0,2) );
          cmb_high = TMath::Sqrt( TMath::Power(err_high/cont,2) + TMath::Power(err_dr0njet0,2) );
          morphed_high =  ((-cmb_low)* float(n_morph_pt-ipt-1)/(n_morph_pt-1) + (cmb_high)* float(ipt)/(n_morph_pt-1));
          morphed_low =  ((cmb_high)* float(n_morph_pt-ipt-1)/(n_morph_pt-1) + (-cmb_low)* float(ipt)/(n_morph_pt-1));
          if(ipt==i_morph_pt) {
            morphed_high_constant = morphed_high;
            morphed_low_constant = morphed_low;
          }
          if (ipt>i_morph_pt){
            morphed_high = morphed_high_constant;
            morphed_low = morphed_low_constant;
            }
          if(idr==0 && ijet==0){
            hout_err_dr0_njet0_low->SetBinContent(       ipt+1 , idr+1 , ijet+1 , TMath::Sqrt( TMath::Power(err_low/cont,2) + TMath::Power(err_dr0njet0,2) ) );
            hout_err_dr0_njet1_low->SetBinContent(       ipt+1 , idr+1 , ijet+1 , 0        );
            hout_err_dr1_njet0_low->SetBinContent(       ipt+1 , idr+1 , ijet+1 , 0        );
            hout_err_dr1_njet1_low->SetBinContent(       ipt+1 , idr+1 , ijet+1 , 0        );


            hout_err_dr0_njet0_morphed_low->SetBinContent(ipt+1 , idr+1 , ijet+1 , morphed_low );
            hout_err_dr0_njet1_morphed_low->SetBinContent(ipt+1 , idr+1 , ijet+1 , 0 );
            hout_err_dr1_njet0_morphed_low->SetBinContent(ipt+1 , idr+1 , ijet+1 , 0 );
            hout_err_dr1_njet1_morphed_low->SetBinContent(ipt+1 , idr+1 , ijet+1 , 0 );
          }
          if(idr==0 && ijet==1){
            hout_err_dr0_njet0_low->SetBinContent(       ipt+1 , idr+1 , ijet+1 , 0        );
            hout_err_dr0_njet1_low->SetBinContent(       ipt+1 , idr+1 , ijet+1 , TMath::Sqrt( TMath::Power(err_low/cont,2) + TMath::Power(err_dr0njet1,2) ) );
            hout_err_dr1_njet0_low->SetBinContent(       ipt+1 , idr+1 , ijet+1 , 0        );
            hout_err_dr1_njet1_low->SetBinContent(       ipt+1 , idr+1 , ijet+1 , 0        );



            hout_err_dr0_njet0_morphed_low->SetBinContent(ipt+1 , idr+1 , ijet+1 , 0 );
            hout_err_dr0_njet1_morphed_low->SetBinContent(ipt+1 , idr+1 , ijet+1 , morphed_low );
            hout_err_dr1_njet0_morphed_low->SetBinContent(ipt+1 , idr+1 , ijet+1 , 0 );
            hout_err_dr1_njet1_morphed_low->SetBinContent(ipt+1 , idr+1 , ijet+1 , 0 );
          }
          if(idr==1 && ijet==0){
            hout_err_dr0_njet0_low->SetBinContent(       ipt+1 , idr+1 , ijet+1 , 0        );
            hout_err_dr0_njet1_low->SetBinContent(       ipt+1 , idr+1 , ijet+1 , 0        );
            hout_err_dr1_njet0_low->SetBinContent(       ipt+1 , idr+1 , ijet+1 , TMath::Sqrt( TMath::Power(err_low/cont,2) + TMath::Power(err_dr1njet0,2) ) );
            hout_err_dr1_njet1_low->SetBinContent(       ipt+1 , idr+1 , ijet+1 , 0        );


            hout_err_dr0_njet0_morphed_low->SetBinContent(ipt+1 , idr+1 , ijet+1 , 0 );
            hout_err_dr0_njet1_morphed_low->SetBinContent(ipt+1 , idr+1 , ijet+1 , 0 );
            hout_err_dr1_njet0_morphed_low->SetBinContent(ipt+1 , idr+1 , ijet+1 , morphed_low );
            hout_err_dr1_njet1_morphed_low->SetBinContent(ipt+1 , idr+1 , ijet+1 , 0 );    
          }
          if(idr==1 && ijet==1){
            hout_err_dr0_njet0_low->SetBinContent(       ipt+1 , idr+1 , ijet+1 , 0        );
            hout_err_dr0_njet1_low->SetBinContent(       ipt+1 , idr+1 , ijet+1 , 0        );
            hout_err_dr1_njet0_low->SetBinContent(       ipt+1 , idr+1 , ijet+1 , 0        );
            hout_err_dr1_njet1_low->SetBinContent(       ipt+1 , idr+1 , ijet+1 , TMath::Sqrt( TMath::Power(err_low/cont,2) + TMath::Power(err_dr1njet1,2) ) );


            hout_err_dr0_njet0_morphed_low->SetBinContent(ipt+1 , idr+1 , ijet+1 , 0 );
            hout_err_dr0_njet1_morphed_low->SetBinContent(ipt+1 , idr+1 , ijet+1 , 0 );
            hout_err_dr1_njet0_morphed_low->SetBinContent(ipt+1 , idr+1 , ijet+1 , 0 );
            hout_err_dr1_njet1_morphed_low->SetBinContent(ipt+1 , idr+1 , ijet+1 , morphed_low );
          }

          if(idr==0 && ijet==0){
            hout_err_dr0_njet0_high->SetBinContent(       ipt+1 , idr+1 , ijet+1 , TMath::Sqrt( TMath::Power(err_high/cont,2) + TMath::Power(err_dr0njet0,2) ) );
            hout_err_dr0_njet1_high->SetBinContent(       ipt+1 , idr+1 , ijet+1 , 0        );
            hout_err_dr1_njet0_high->SetBinContent(       ipt+1 , idr+1 , ijet+1 , 0        );
            hout_err_dr1_njet1_high->SetBinContent(       ipt+1 , idr+1 , ijet+1 , 0        );


            hout_err_dr0_njet0_morphed_high->SetBinContent(ipt+1 , idr+1 , ijet+1 , morphed_high );
            hout_err_dr0_njet1_morphed_high->SetBinContent(ipt+1 , idr+1 , ijet+1 , 0 );
            hout_err_dr1_njet0_morphed_high->SetBinContent(ipt+1 , idr+1 , ijet+1 , 0 );
            hout_err_dr1_njet1_morphed_high->SetBinContent(ipt+1 , idr+1 , ijet+1 , 0 ); 
           
          }
          if(idr==0 && ijet==1){
            hout_err_dr0_njet0_high->SetBinContent(       ipt+1 , idr+1 , ijet+1 , 0        );
            hout_err_dr0_njet1_high->SetBinContent(       ipt+1 , idr+1 , ijet+1 , TMath::Sqrt( TMath::Power(err_high/cont,2) + TMath::Power(err_dr0njet1,2) ) );
            hout_err_dr1_njet0_high->SetBinContent(       ipt+1 , idr+1 , ijet+1 , 0        );
            hout_err_dr1_njet1_high->SetBinContent(       ipt+1 , idr+1 , ijet+1 , 0        );



            hout_err_dr0_njet0_morphed_high->SetBinContent(ipt+1 , idr+1 , ijet+1 , 0 );
            hout_err_dr0_njet1_morphed_high->SetBinContent(ipt+1 , idr+1 , ijet+1 , morphed_high );
            hout_err_dr1_njet0_morphed_high->SetBinContent(ipt+1 , idr+1 , ijet+1 , 0 );
            hout_err_dr1_njet1_morphed_high->SetBinContent(ipt+1 , idr+1 , ijet+1 , 0 );
          }


          if(idr==0 && ijet==2){
            hout_err_dr0_njet0_high->SetBinContent(       ipt+1 , idr+1 , ijet+1 , 0        );
            hout_err_dr0_njet1_high->SetBinContent(       ipt+1 , idr+1 , ijet+1 , 0        );
            hout_err_dr1_njet0_high->SetBinContent(       ipt+1 , idr+1 , ijet+1 , 0        );
            hout_err_dr1_njet1_high->SetBinContent(       ipt+1 , idr+1 , ijet+1 , 0        );


            hout_err_dr0_njet0_morphed_high->SetBinContent(ipt+1 , idr+1 , ijet+1 , 0 );
            hout_err_dr0_njet1_morphed_high->SetBinContent(ipt+1 , idr+1 , ijet+1 , 0 );
            hout_err_dr1_njet0_morphed_high->SetBinContent(ipt+1 , idr+1 , ijet+1 , 0 );
            hout_err_dr1_njet1_morphed_high->SetBinContent(ipt+1 , idr+1 , ijet+1 , 0 );

            hout_err_dr0_njet2_morphed_high->SetBinContent(ipt+1 , idr+1 , ijet+1 , morphed_high );
            hout_err_dr0_njet2_high->SetBinContent(       ipt+1 , idr+1 , ijet+1 , TMath::Sqrt( TMath::Power(err_high/cont,2) + TMath::Power(err_dr0njet2,2) ) );
            hout_err_dr1_njet2_morphed_high->SetBinContent(ipt+1 , idr+1 , ijet+1 , 0 );
            hout_err_dr1_njet2_high->SetBinContent(       ipt+1 , idr+1 , ijet+1 , 0 );

            hout_err_dr0_njet0_low->SetBinContent(       ipt+1 , idr+1 , ijet+1 , 0        );
            hout_err_dr0_njet1_low->SetBinContent(       ipt+1 , idr+1 , ijet+1 , 0        );
            hout_err_dr1_njet0_low->SetBinContent(       ipt+1 , idr+1 , ijet+1 , 0        );
            hout_err_dr1_njet1_low->SetBinContent(       ipt+1 , idr+1 , ijet+1 , 0        );


            hout_err_dr0_njet0_morphed_low->SetBinContent(ipt+1 , idr+1 , ijet+1 , 0 );
            hout_err_dr0_njet1_morphed_low->SetBinContent(ipt+1 , idr+1 , ijet+1 , 0 );
            hout_err_dr1_njet0_morphed_low->SetBinContent(ipt+1 , idr+1 , ijet+1 , 0 );
            hout_err_dr1_njet1_morphed_low->SetBinContent(ipt+1 , idr+1 , ijet+1 , 0 );

            hout_err_dr0_njet2_morphed_low->SetBinContent(ipt+1 , idr+1 , ijet+1 , morphed_low );
            hout_err_dr0_njet2_low->SetBinContent(       ipt+1 , idr+1 , ijet+1 , TMath::Sqrt( TMath::Power(err_high/cont,2) + TMath::Power(err_dr0njet2,2) ) );
            hout_err_dr1_njet2_morphed_low->SetBinContent(ipt+1 , idr+1 , ijet+1 , 0 );
            hout_err_dr1_njet2_low->SetBinContent(       ipt+1 , idr+1 , ijet+1 , 0 );

          }

          if(idr==1 && ijet==0){
            hout_err_dr0_njet0_high->SetBinContent(       ipt+1 , idr+1 , ijet+1 , 0        );
            hout_err_dr0_njet1_high->SetBinContent(       ipt+1 , idr+1 , ijet+1 , 0        );
            hout_err_dr1_njet0_high->SetBinContent(       ipt+1 , idr+1 , ijet+1 , TMath::Sqrt( TMath::Power(err_high/cont,2) + TMath::Power(err_dr1njet0,2) ) );
            hout_err_dr1_njet1_high->SetBinContent(       ipt+1 , idr+1 , ijet+1 , 0        );

            hout_err_dr0_njet0_morphed_high->SetBinContent(ipt+1 , idr+1 , ijet+1 , 0 );
            hout_err_dr0_njet1_morphed_high->SetBinContent(ipt+1 , idr+1 , ijet+1 , 0 );
            hout_err_dr1_njet0_morphed_high->SetBinContent(ipt+1 , idr+1 , ijet+1 , morphed_high );
            hout_err_dr1_njet1_morphed_high->SetBinContent(ipt+1 , idr+1 , ijet+1 , 0 );
          }
          if(idr==1 && ijet==1){
            hout_err_dr0_njet0_high->SetBinContent(       ipt+1 , idr+1 , ijet+1 , 0        );
            hout_err_dr0_njet1_high->SetBinContent(       ipt+1 , idr+1 , ijet+1 , 0        );
            hout_err_dr1_njet0_high->SetBinContent(       ipt+1 , idr+1 , ijet+1 , 0        );
            hout_err_dr1_njet1_high->SetBinContent(       ipt+1 , idr+1 , ijet+1 , TMath::Sqrt( TMath::Power(err_high/cont,2) + TMath::Power(err_dr1njet1,2) ) );



            hout_err_dr0_njet0_morphed_high->SetBinContent(ipt+1 , idr+1 , ijet+1 , 0 );
            hout_err_dr0_njet1_morphed_high->SetBinContent(ipt+1 , idr+1 , ijet+1 , 0 );
            hout_err_dr1_njet0_morphed_high->SetBinContent(ipt+1 , idr+1 , ijet+1 , 0 );
            hout_err_dr1_njet1_morphed_high->SetBinContent(ipt+1 , idr+1 , ijet+1 , morphed_high );
        
          }
          if(idr==1 && ijet==2){
            hout_err_dr0_njet0_high->SetBinContent(       ipt+1 , idr+1 , ijet+1 , 0        );
            hout_err_dr0_njet1_high->SetBinContent(       ipt+1 , idr+1 , ijet+1 , 0        );
            hout_err_dr1_njet0_high->SetBinContent(       ipt+1 , idr+1 , ijet+1 , 0        );
            hout_err_dr1_njet1_high->SetBinContent(       ipt+1 , idr+1 , ijet+1 , 0        );


            hout_err_dr0_njet0_morphed_high->SetBinContent(ipt+1 , idr+1 , ijet+1 , 0 );
            hout_err_dr0_njet1_morphed_high->SetBinContent(ipt+1 , idr+1 , ijet+1 , 0 );
            hout_err_dr1_njet0_morphed_high->SetBinContent(ipt+1 , idr+1 , ijet+1 , 0 );
            hout_err_dr1_njet1_morphed_high->SetBinContent(ipt+1 , idr+1 , ijet+1 , 0 );

            hout_err_dr0_njet2_morphed_high->SetBinContent(ipt+1 , idr+1 , ijet+1 , 0 );
            hout_err_dr0_njet2_high->SetBinContent(       ipt+1 , idr+1 , ijet+1 , 0 );
            hout_err_dr1_njet2_morphed_high->SetBinContent(ipt+1 , idr+1 , ijet+1 , morphed_high );
            hout_err_dr1_njet2_high->SetBinContent(       ipt+1 , idr+1 , ijet+1 , TMath::Sqrt( TMath::Power(err_high/cont,2) + TMath::Power(err_dr0njet2,2) ) );

            hout_err_dr0_njet0_low->SetBinContent(       ipt+1 , idr+1 , ijet+1 , 0        );
            hout_err_dr0_njet1_low->SetBinContent(       ipt+1 , idr+1 , ijet+1 , 0        );
            hout_err_dr1_njet0_low->SetBinContent(       ipt+1 , idr+1 , ijet+1 , 0        );
            hout_err_dr1_njet1_low->SetBinContent(       ipt+1 , idr+1 , ijet+1 , 0        );


            hout_err_dr0_njet0_morphed_low->SetBinContent(ipt+1 , idr+1 , ijet+1 , 0 );
            hout_err_dr0_njet1_morphed_low->SetBinContent(ipt+1 , idr+1 , ijet+1 , 0 );
            hout_err_dr1_njet0_morphed_low->SetBinContent(ipt+1 , idr+1 , ijet+1 , 0 );
            hout_err_dr1_njet1_morphed_low->SetBinContent(ipt+1 , idr+1 , ijet+1 , 0 );

            hout_err_dr0_njet2_morphed_low->SetBinContent(ipt+1 , idr+1 , ijet+1 , 0 );
            hout_err_dr0_njet2_low->SetBinContent(       ipt+1 , idr+1 , ijet+1 , 0 );
            hout_err_dr1_njet2_morphed_low->SetBinContent(ipt+1 , idr+1 , ijet+1 , morphed_low );
            hout_err_dr1_njet2_low->SetBinContent(       ipt+1 , idr+1 , ijet+1 , TMath::Sqrt( TMath::Power(err_high/cont,2) + TMath::Power(err_dr0njet2,2)) );
        
          }
        }
      }
    }
  }
  else if(njetbinned){
    TH1D *h=(TH1D*) f->Get(hn);
    for (int i=0; i<N_D1; i++){
      for (int j=0; j<N_D2; j++){
        for (int k=0; k<N_D3; k++){
          double cont=h->GetBinContent( i+N_D1*j + (N_D1*N_D2)*k + 1 );
          cont = cont*scale_factors.at(j);
          cout << i+N_D1*j + (N_D1*N_D2)*k + 1 << ": " << cont << endl;
          double err =h->GetBinError( i+N_D1*j + (N_D1*N_D2)*k + 1 );
          hout->SetBinContent(       i+1 , j+1 , k+1 , cont );
          hout->SetBinError(         i+1 , j+1 , k+1 , err );
          hout_err_low->SetBinContent(       i+1 , j+1 , k+1 , err/cont );
          hout_err_low->SetBinError(       i+1 , j+1 , k+1 , err );
          hout_err_high->SetBinContent(       i+1 , j+1 , k+1 , err/cont );
          hout_err_high->SetBinError(       i+1 , j+1 , k+1 , err );
        }
      }
    }
    delete h;
  }
  else{
    cout << fn << " fake factors have no njet binning! Is this intended?" << endl;
    return;
  }
  
  cout << "OutputFile: " << fout_n << endl;
  TFile *fout=new TFile ( fout_n , "RECREATE" );
  hout->Write();
  hout_err_low->Write();
  hout_err_high->Write();
  hout_err_mc_low->Write();
  hout_err_mc_high->Write();
  if(fit_pT_bins){
    hout_err_dr0_njet0_low->Write();
    hout_err_dr0_njet1_low->Write();
    hout_err_dr0_njet2_low->Write();

    hout_err_dr1_njet0_low->Write();
    hout_err_dr1_njet1_low->Write();
    hout_err_dr1_njet2_low->Write();

    hout_err_dr0_njet0_high->Write();
    hout_err_dr0_njet1_high->Write();
    hout_err_dr0_njet2_high->Write();

    hout_err_dr1_njet0_high->Write();
    hout_err_dr1_njet1_high->Write();
    hout_err_dr1_njet2_high->Write();

    hout_err_dr0_njet0_morphed_low->Write();
    hout_err_dr0_njet1_morphed_low->Write();
    hout_err_dr0_njet2_morphed_low->Write();
    hout_err_dr1_njet0_morphed_low->Write();
    hout_err_dr1_njet1_morphed_low->Write();
    hout_err_dr1_njet2_morphed_low->Write();

    hout_err_dr0_njet0_morphed_high->Write();
    hout_err_dr0_njet1_morphed_high->Write();
    hout_err_dr0_njet2_morphed_high->Write();

    hout_err_dr1_njet0_morphed_high->Write();
    hout_err_dr1_njet1_morphed_high->Write();
    hout_err_dr1_njet2_morphed_high->Write();

  }
  fout->Close();

  f->Close();

}

void make_frac_sys( const TString fn , const std::vector<TString> fn_other , const TString hn , const TString hnout , const std::vector<TString> hn_other , const TString fout_n , const int opt ){

  if ( opt==0 ) make_frac_sys( fn , fn_other , hn , hnout, hn_other , fout_n , N_p_Wjets , N_t_Wjets , Pt_cuts_Wjets , Decay_cuts_Wjets );
  if ( opt==1 && CHAN != kTAU ) make_frac_sys( fn , fn_other , hn , hnout, hn_other , fout_n , w_pt_n    , N_t_Wjets , w_pt_v        , Decay_cuts_Wjets );
  if ( opt==1 && CHAN == kTAU ) make_frac_sys( fn , fn_other , hn , hnout, hn_other , fout_n , w_mttot_n    , N_t_Wjets , w_mttot_v        , Decay_cuts_Wjets );

}

void smooth_th1( const TString fn , const TString hn , const TString fout_n , const int useBinErrors ){

  cout << "smooth_th1 \t" << fn << "\t" << hn << "\t" << fout_n << endl;

  GaussianKernelSmoother gsk;

  if ( useBinErrors ){
    TH1D *h_binerr=extract_binerr_histo( fn , hn );
    int ret=gsk.setInputHisto( h_binerr );
    if ( ret != 0 ) return;
    gsk.setWidth( 2* h_binerr->GetBinWidth(1) );
    delete h_binerr;
  } else{
    int ret=gsk.setInputHisto( fn, hn );
    if ( ret != 0 ) return;
    TH1D *h=gsk.returnInputHisto();
    gsk.setWidth( 1* h->GetBinWidth(1) );
  }


  gsk.getSmoothHisto();

  TH1D *h2=gsk.returnSmoothedHisto();


  TFile *fout=new TFile ( fout_n , "RECREATE" );
  h2->Write();
  fout->Close();

  //  f->Close();
}

void copy_th1( const TString fn , const TString hn , const TString fout_n ){

  cout << "copy_th1 \t" << fn << "\t" << hn << "\t" << fout_n << endl;

  TFile *f=new TFile( fn );
  TH1D *h=(TH1D*) f->Get(hn);

  TFile *fout=new TFile ( fout_n , "RECREATE" );
  h->Write();
  fout->Close();

  f->Close();

}

void make_frac_sys( const TString fn , const std::vector<TString> fn_other , const TString hn , const TString hnout , const std::vector<TString> hn_other , const TString fout_n , const Int_t N_D1, const Int_t N_D2, const Double_t V1[], const Int_t V2[], const int ntoys ){

  cout << "make_frac_sys \t" << fn << "\t" << hn << "\t" << fout_n << "\t" << ntoys << endl;

  Double_t d1[N_D1+1];
  Double_t d2[N_D2+1];

  for (int i=0; i<N_D1; i++){
    d1[i]=V1[i];
  }
  if(CHAN !=kTAU) d1[N_D1]=250;
  else d1[N_D1]=1000;

  for (int i=0; i<N_D2; i++){
    d2[i]=V2[i];
  }
  d2[N_D2]=15;

  const int n_other=fn_other.size();

  TFile *f=new TFile( fn );
  TH1D *h=(TH1D*) f->Get(hn);

  TH2D *hout      = new TH2D( hnout,      "",  N_D1 , d1,  N_D2 ,  d2 );
  TString replaceString=hnout;
  replaceString.ReplaceAll("_2d","");
  TH2D *hout_low  = new TH2D( replaceString+"_low_2d",  "",  N_D1 , d1,  N_D2 ,  d2 );
  TH2D *hout_high = new TH2D( replaceString+"_high_2d", "",  N_D1 , d1,  N_D2 ,  d2 );

  std::vector<TFile*>  f_other(n_other);
  std::vector<TH1D*>   h_other(n_other);
  std::vector<TH2D*>   h_low_other(n_other);
  std::vector<TH2D*>   h_high_other(n_other);
  std::vector<double>  v_other(n_other);
  for (unsigned jf=0; jf<n_other; jf++){
    f_other.at(jf) = new TFile( fn_other.at(jf) );
    h_other.at(jf) = (TH1D*) f_other.at(jf)->Get(hn);
    h_low_other.at(jf)=new TH2D(  hn_other.at(jf)+"_low_2d"  ,  "", N_D1 , d1,  N_D2 ,  d2 );
    h_high_other.at(jf)=new TH2D( hn_other.at(jf)+"_high_2d" ,  "", N_D1 , d1,  N_D2 ,  d2 );
  }



  for (int i=0; i<N_D1; i++){
    for (int j=0; j<N_D2; j++){
      double cont=h->GetBinContent( i+N_D1*j +1 );
      double err =h->GetBinError( i+N_D1*j +1 );
      hout->SetBinContent(       i+1 , j+1 , cont );
      hout->SetBinError(         i+1 , j+1 , err );
      //THESE ERRORS ARE ONLY FOR TAUTAU CHANNEL
      if(cont != 0) err = err/(2*cont);
      else err = 0;
      //cout << (1-err) << endl;
      hout_low->SetBinContent(  i+1 , j+1 , (1-err) );
      hout_high->SetBinContent( i+1 , j+1 , (1+err) );

      double s_other=0;
      for (unsigned jf=0; jf<n_other; jf++){
        v_other.at(jf)=h_other.at(jf)->GetBinContent( i+N_D1*j +1 );
        s_other+=v_other.at(jf);
              
      }
      for (unsigned jf=0; jf<n_other; jf++){
        double shift = err * v_other.at(jf)/s_other;
        //cout << "B " << h_low_other.at(0)->GetBinContent(  5, 1 ) << "\t" << i+1 << "\t" << j+1 << "\t" << jf << endl;
        h_low_other.at(jf)->SetBinContent(  i+1 , j+1 , v_other.at(jf) + shift );
        h_high_other.at(jf)->SetBinContent( i+1 , j+1 , v_other.at(jf) - shift );
               
      }
    }
  }

  TFile *fout=new TFile ( fout_n , "RECREATE" );
  hout->Write();
  if ( n_other>0 ){
    hout_low->Write();
    hout_high->Write();
  }
  for (unsigned jf=0; jf<n_other; jf++){
    h_low_other.at(jf)->Write();
    h_high_other.at(jf)->Write();
  }
  //  cout << h_low_other.at(0)->GetBinContent(  5, 1 ) << endl;
  fout->Close();

  f->Close();

}

TH1D* extract_binerr_histo( TString fn , TString hn ){

  TFile *f=new TFile( fn );
  TH1D *h=(TH1D*) f->Get(hn);

  TH1D *h_ret=(TH1D*)h->Clone();

  for (int ib=1; ib<=h_ret->GetNbinsX(); ib++){
    if ( fabs(h_ret->GetBinContent( ib ))>1e-8 )h_ret->SetBinContent( ib , h_ret->GetBinError( ib ) / h_ret->GetBinContent( ib ) );
    else h_ret->SetBinContent( ib , 0 );
    h_ret->SetBinError(   ib , 0 );
  }

  return h_ret;
}

TString getCatString(Int_t categoryMode){

  if ( categoryMode & _DUMMYCAT )           return categories[0];
  
  
  return "incl";
  
}

void convert_corrections( TString fn, TString gn, TString fout, TString gout, const TString tight_cat){
  cout << "In Convert_Corrections: " << fn << " " << gn << " " << fout << " " << gout << " " << tight_cat << endl;
  TFile *f=new TFile(fn.ReplaceAll(".root",tight_cat+".root"));
  TGraphAsymmErrors *t=(TGraphAsymmErrors*)f->Get(gn);
  TFile *fout_h=new TFile(fout.ReplaceAll(".root",tight_cat+".root"),"RECREATE");
  TGraphAsymmErrors *gout_h=(TGraphAsymmErrors*)t->Clone(gout);
  gout_h->SetTitle(gout);
  fout_h->cd();
  gout_h->Write();
  f->Close();fout_h->Close();
  
}

void combineQCDSystematics( TString fQCD_nonclosure, TString sys_nonclosure, TString fQCD_otherLep, TString sys_otherLep, TString fQCD_OSSS, TString sys_OSSS, TString fout, TString tout, const TString tight_cat){
  std::cout << "combineQCDSystematics " << fQCD_nonclosure << " " << sys_nonclosure << std::endl;
  std::cout << "fQCD_nonclosure " << fQCD_nonclosure << std::endl;
  std::cout << "sys_nonclosure " << sys_nonclosure << std::endl;
  std::cout << "fQCD_otherLep " << fQCD_otherLep << std::endl;
  std::cout << "sys_otherLep " << sys_otherLep << std::endl;
  std::cout << "fQCD_OSSS " << fQCD_OSSS << std::endl;
  std::cout << "sys_OSSS " << sys_OSSS << std::endl;
  std::cout << "fout " << fout << std::endl;
  std::cout << "tout " << tout  << std::endl;
  std::cout << "tight_cat " << tight_cat<< std::endl;
  
  Float_t addUncertainty=0;
  if(useExtraOSSSuncertainty){
    if( CHAN==kMU )       addUncertainty=OSSSuncertainty_mt;
    else if( CHAN==kEL)   addUncertainty=OSSSuncertainty_et;
    else if( CHAN==kTAU)  addUncertainty=OSSSuncertainty_tt;
  }
  if(CHAN!=kTAU){
    TFile *f_nonclosure=new TFile(fQCD_nonclosure.ReplaceAll(".root",tight_cat+".root"));
    TGraphAsymmErrors *sys_nonclosure_t=(TGraphAsymmErrors*)f_nonclosure->Get(sys_nonclosure);
    TFile *f_otherLep=new TFile(fQCD_otherLep.ReplaceAll(".root",tight_cat+".root"));
    TGraphAsymmErrors *sys_otherLep_t=(TGraphAsymmErrors*)f_otherLep->Get(sys_otherLep);
    TFile *f_OSSS=new TFile(fQCD_OSSS.ReplaceAll(".root",tight_cat+".root"));
    TGraphAsymmErrors *sys_OSSS_t=(TGraphAsymmErrors*)f_OSSS->Get(sys_OSSS);

    TH2D *out_t = new TH2D(tout, tout, sys_nonclosure_t->GetN(), sys_nonclosure_t->GetX()[0], sys_nonclosure_t->GetX()[sys_nonclosure_t->GetN()-1], sys_otherLep_t->GetN(), sys_otherLep_t->GetX()[0], sys_otherLep_t->GetX()[sys_otherLep_t->GetN()-1]);
    for(Int_t i=0; i<=sys_nonclosure_t->GetN(); i++){
      for(Int_t j=0; j<=sys_otherLep_t->GetN(); j++){
        //if(!CALC_SS_SR) out_t->SetBinContent(i,j,TMath::Sqrt( TMath::Power(sys_nonclosure_t->GetY()[i],2) ) );
        if(!CALC_SS_SR){
          Float_t binContent = TMath::Sqrt( TMath::Power(sys_nonclosure_t->GetY()[i],2) + TMath::Power(sys_otherLep_t->GetY()[j],2) + TMath::Power(sys_OSSS_t->GetY()[i],2) + TMath::Power(addUncertainty,2) );
          if(binContent>1) binContent=1;
          out_t->SetBinContent(i,j,binContent );
        }
        else out_t->SetBinContent(i,j,TMath::Sqrt( TMath::Power(sys_nonclosure_t->GetY()[i],2) + TMath::Power(sys_otherLep_t->GetY()[j],2) ) );
      }
    }
    TFile *fout_f=new TFile(fout.ReplaceAll(".root",tight_cat+".root"),"UPDATE");
    fout_f->cd();
    out_t->Write();
    fout_f->Close();
  }

  else{
    TFile *f_nonclosure=new TFile(fQCD_nonclosure);
    TGraphAsymmErrors *sys_nonclosure_t=(TGraphAsymmErrors*)f_nonclosure->Get(sys_nonclosure);
    TFile *f_otherLep=new TFile(fQCD_otherLep);
    
    TGraphAsymmErrors *sys_otherLep_t=(TGraphAsymmErrors*)f_otherLep->Get(sys_otherLep);
    TFile *f_OSSS=new TFile(fQCD_OSSS);
    TGraphAsymmErrors *sys_OSSS_t=(TGraphAsymmErrors*)f_OSSS->Get(sys_OSSS);
    
    TH2D *out_t = new TH2D(tout, tout, sys_nonclosure_t->GetN(), sys_nonclosure_t->GetX()[0], sys_nonclosure_t->GetX()[sys_nonclosure_t->GetN()-1], sys_otherLep_t->GetN(), sys_otherLep_t->GetX()[0], sys_otherLep_t->GetX()[sys_otherLep_t->GetN()-1]);
    
    for(Int_t i=0; i<=sys_nonclosure_t->GetN(); i++){
      for(Int_t j=0; j<=sys_otherLep_t->GetN(); j++){
        //if(!CALC_SS_SR) out_t->SetBinContent(i,j,TMath::Sqrt( TMath::Power(sys_nonclosure_t->GetY()[i],2) ) );
        if(!CALC_SS_SR){
          Float_t binContent=TMath::Sqrt( TMath::Power(sys_nonclosure_t->GetY()[i],2) + TMath::Power(sys_otherLep_t->GetY()[j],2) + TMath::Power(sys_OSSS_t->GetY()[i],2) + TMath::Power(addUncertainty,2) );
          if(binContent>1)binContent=1;
          out_t->SetBinContent(i,j,binContent);
        }
        else out_t->SetBinContent(i,j,TMath::Sqrt( TMath::Power(sys_nonclosure_t->GetY()[i],2) + TMath::Power(sys_otherLep_t->GetY()[j],2) ) );
      }
    }
    TFile *fout_f=new TFile(fout.ReplaceAll(".root",tight_cat+".root"),"UPDATE");
    fout_f->cd();
    out_t->Write();
    fout_f->Close();
  }
  
}

void combineQCDSystematics_morphed( TString fQCD_nonclosure, TString sys_nonclosure, TString fQCD_otherLep, TString sys_otherLep, TString fQCD_OSSS, TString sys_OSSS, TString fout, TString tout, const TString tight_cat){
  std::cout << "combineQCDSystematics morphed " << fQCD_nonclosure << " " << sys_nonclosure << std::endl;
  
  
  // std::cout << "fQCD_nonclosure " << fQCD_nonclosure << std::endl; 
  // std::cout << "sys_nonclosure " << sys_nonclosure << std::endl; 
  // std::cout << "fQCD_otherLep " << fQCD_otherLep << std::endl; 
  // std::cout << "sys_otherLep " << sys_otherLep << std::endl; 
  // std::cout << "fQCD_OSSS " << fQCD_OSSS << std::endl; 
  // std::cout << "sys_OSSS " << sys_OSSS << std::endl; 
  // std::cout << "fout " << fout << std::endl; 
  // std::cout << "tout " << tout << std::endl;  
  // std::cout << "tight_cat " << tight_cat << std::endl;
  
  
  TFile *f_nonclosure=new TFile(fQCD_nonclosure.ReplaceAll(".root",tight_cat+".root"));
  TGraphAsymmErrors *sys_nonclosure_t_up=(TGraphAsymmErrors*)f_nonclosure->Get(sys_nonclosure+"_up");
  TGraphAsymmErrors *sys_nonclosure_t_down=(TGraphAsymmErrors*)f_nonclosure->Get(sys_nonclosure+"_down");
  
  TFile *f_otherLep=new TFile(fQCD_otherLep.ReplaceAll(".root",tight_cat+".root"));
  TGraphAsymmErrors *sys_otherLep_t_up=(TGraphAsymmErrors*)f_otherLep->Get(sys_otherLep+"_up");
  TGraphAsymmErrors *sys_otherLep_t_down=(TGraphAsymmErrors*)f_otherLep->Get(sys_otherLep+"_down");

  TFile *f_OSSS=new TFile(fQCD_OSSS.ReplaceAll(".root",tight_cat+".root"));
  TGraphAsymmErrors *sys_OSSS_t_up=(TGraphAsymmErrors*)f_OSSS->Get(sys_OSSS+"_up");
  TGraphAsymmErrors *sys_OSSS_t_down=(TGraphAsymmErrors*)f_OSSS->Get(sys_OSSS+"_down");

  Float_t addUncertainty=0;
  if(useExtraOSSSuncertainty){
    if( CHAN==kMU )       addUncertainty=OSSSuncertainty_mt;
    else if( CHAN==kEL)   addUncertainty=OSSSuncertainty_et;
    else if( CHAN==kTAU)  addUncertainty=OSSSuncertainty_tt;
  }
  TH1D *out_t_mvis_up = new TH1D(tout+"_mvis_up", tout+"_mvis_up", sys_nonclosure_t_up->GetN(), sys_nonclosure_t_up->GetX()[0], sys_nonclosure_t_up->GetX()[sys_nonclosure_t_up->GetN()-1]);
  TH1D *out_t_mvis_down = new TH1D(tout+"_mvis_down", tout+"_mvis_down", sys_nonclosure_t_down->GetN(), sys_nonclosure_t_down->GetX()[0], sys_nonclosure_t_down->GetX()[sys_nonclosure_t_down->GetN()-1]);

  TH1D *out_t_mvis_osss_up = new TH1D(tout+"_mvis_osss_up", tout+"_mvis_osss_up", sys_OSSS_t_up->GetN(), sys_OSSS_t_up->GetX()[0], sys_OSSS_t_up->GetX()[sys_OSSS_t_up->GetN()-1]);
  TH1D *out_t_mvis_osss_down = new TH1D(tout+"_mvis_osss_down", tout+"_mvis_osss_down", sys_OSSS_t_down->GetN(), sys_OSSS_t_down->GetX()[0], sys_OSSS_t_down->GetX()[sys_OSSS_t_down->GetN()-1]);
  

  TH1D *out_t_pt_up = new TH1D(tout+"_pt_up", tout+"_pt_up", sys_otherLep_t_up->GetN(), sys_otherLep_t_up->GetX()[0], sys_otherLep_t_up->GetX()[sys_otherLep_t_up->GetN()-1]);
  TH1D *out_t_pt_down = new TH1D(tout+"_pt_down", tout+"_pt_down", sys_otherLep_t_down->GetN(), sys_otherLep_t_down->GetX()[0], sys_otherLep_t_down->GetX()[sys_otherLep_t_down->GetN()-1]);
  
  double morphed_high; double morphed_low;
  double mvis_max = 250.0;
  Int_t n_morph_mvis = 0; Int_t i_morph_mvis = 0;
  Int_t n_morph_mvis_osss = 0; Int_t i_morph_mvis_osss = 0;

  for(Int_t i=0; sys_nonclosure_t_up->GetX()[i] < mvis_max; i++){
    n_morph_mvis += 1;
    i_morph_mvis = i;
  }
  for(Int_t i=0; sys_OSSS_t_up->GetX()[i] < mvis_max; i++){
    n_morph_mvis_osss += 1;
    i_morph_mvis_osss = i;
  }
  double pt_max = 9999.0;
  if( CHAN!=kTAU) {
      pt_max = 0.15;
  }
  else {
      pt_max = 119.9;
  }
  Int_t n_morph_pt = 0; Int_t i_morph_pt = 0;
  for(Int_t i=0; sys_otherLep_t_down->GetX()[i] < pt_max; i++){
    n_morph_pt += 1;
    i_morph_pt = i;
  }
  std::cout << i_morph_pt << std::endl;
  std::cout << sys_otherLep_t_down->GetX()[i_morph_pt] << std::endl;
  for(Int_t i=0; i<=sys_nonclosure_t_down->GetN(); i++){
    morphed_high = (-sys_nonclosure_t_down->GetY()[i])*float( n_morph_mvis-i-1)/(n_morph_mvis-1) + (sys_nonclosure_t_up->GetY()[i])*float(i)/(n_morph_mvis-1);
    morphed_low = (sys_nonclosure_t_up->GetY()[i])*float( n_morph_mvis-i-1)/(n_morph_mvis-1) + (-sys_nonclosure_t_down->GetY()[i])*float(i)/(n_morph_mvis-1);
    if (i>i_morph_mvis){
      morphed_high = (-sys_nonclosure_t_down->GetY()[i_morph_mvis])*float( n_morph_mvis-i_morph_mvis-1)/(n_morph_mvis-1) + (sys_nonclosure_t_up->GetY()[i_morph_mvis])*float(i_morph_mvis)/(n_morph_mvis-1);
      morphed_low = (sys_nonclosure_t_up->GetY()[i_morph_mvis])*float( n_morph_mvis-i_morph_mvis-1)/(n_morph_mvis-1) + (-sys_nonclosure_t_down->GetY()[i_morph_mvis])*float(i_morph_mvis)/(n_morph_mvis-1);
    }
    out_t_mvis_up->SetBinContent(i,morphed_high);
    out_t_mvis_down->SetBinContent(i,morphed_low);
  }
  for(Int_t i=0; i<=sys_OSSS_t_down->GetN(); i++){
    morphed_high = (-sys_OSSS_t_down->GetY()[i])*float( n_morph_mvis_osss-i-1)/(n_morph_mvis_osss-1) + (sys_OSSS_t_up->GetY()[i])*float(i)/(n_morph_mvis_osss-1);
    morphed_low = (sys_OSSS_t_up->GetY()[i])*float( n_morph_mvis_osss-i-1)/(n_morph_mvis_osss-1) + (-sys_OSSS_t_down->GetY()[i])*float(i)/(n_morph_mvis_osss-1);
    if (i>i_morph_mvis_osss){
      morphed_high = (-sys_OSSS_t_down->GetY()[i_morph_mvis_osss])*float( n_morph_mvis_osss-i_morph_mvis_osss-1)/(n_morph_mvis_osss-1) + (sys_OSSS_t_up->GetY()[i_morph_mvis_osss])*float(i_morph_mvis_osss)/(n_morph_mvis_osss-1);
      morphed_low = (sys_OSSS_t_up->GetY()[i_morph_mvis_osss])*float( n_morph_mvis_osss-i_morph_mvis_osss-1)/(n_morph_mvis_osss-1) + (-sys_OSSS_t_down->GetY()[i_morph_mvis_osss])*float(i_morph_mvis_osss)/(n_morph_mvis_osss-1);
    }
    out_t_mvis_osss_up->SetBinContent(i,morphed_high);
    out_t_mvis_osss_down->SetBinContent(i,morphed_low);
  }
  for(Int_t i=0; i<=sys_otherLep_t_up->GetN(); i++){
    morphed_high = (-sys_otherLep_t_down->GetY()[i])*float( n_morph_pt-i-1)/(n_morph_pt-1) + (sys_otherLep_t_up->GetY()[i])*float(i)/(n_morph_pt-1);
    morphed_low = (sys_otherLep_t_up->GetY()[i])*float( n_morph_pt-i-1)/(n_morph_pt-1) + (-sys_otherLep_t_down->GetY()[i])*float(i)/(n_morph_pt-1);
    if (i>i_morph_pt){
      morphed_high = (-sys_otherLep_t_down->GetY()[i_morph_pt])*float( n_morph_pt-i_morph_pt-1)/(n_morph_pt-1) + (sys_otherLep_t_up->GetY()[i_morph_pt])*float(i_morph_pt)/(n_morph_pt-1);
      morphed_low = (sys_otherLep_t_up->GetY()[i_morph_pt])*float( n_morph_pt-i_morph_pt-1)/(n_morph_pt-1) + (-sys_otherLep_t_down->GetY()[i_morph_pt])*float(i_morph_pt)/(n_morph_pt-1);
    }
    out_t_pt_up->SetBinContent(i,morphed_high);
    out_t_pt_down->SetBinContent(i,morphed_low);
  }
  TFile *fout_f=new TFile(fout.ReplaceAll(".root",tight_cat+".root"),"UPDATE");
  fout_f->cd();
  out_t_mvis_up->Write();
  out_t_mvis_down->Write();
  out_t_mvis_osss_up->Write();
  out_t_mvis_osss_down->Write();
  out_t_pt_up->Write();
  out_t_pt_down->Write();

  fout_f->Close();
}

void combineWSystematics( TString fW_nonclosure, TString sys_nonclosure, TString fW_mtcorr, TString sys_mtcorr, TString fout, TString tout, const TString tight_cat){

  TFile *f_nonclosure=new TFile(fW_nonclosure.ReplaceAll(".root",tight_cat+".root"));
  TGraphAsymmErrors *sys_nonclosure_t=(TGraphAsymmErrors*)f_nonclosure->Get(sys_nonclosure);
  TFile *f_mtcorr=new TFile(fW_mtcorr.ReplaceAll(".root",tight_cat+".root"));
  TGraphAsymmErrors *sys_mtcorr_t=(TGraphAsymmErrors*)f_mtcorr->Get(sys_mtcorr);
  TString tout_morphed = tout+"_morphed";
  Double_t additionalDYuncertainty=0;
  if(useWToDYUncertainty){
    if(CHAN==kMU)      additionalDYuncertainty=WToDYUncertainty_mt;
    else if(CHAN==kEL) additionalDYuncertainty=WToDYUncertainty_et;
  }
  TH2D *out_t = new TH2D(tout, tout, sys_nonclosure_t->GetN(), sys_nonclosure_t->GetX()[0], sys_nonclosure_t->GetX()[sys_nonclosure_t->GetN()-1], sys_mtcorr_t->GetN(), sys_mtcorr_t->GetX()[0], sys_mtcorr_t->GetX()[sys_mtcorr_t->GetN()-1]);
  // cout << "i-Bins: " << sys_nonclosure_t->GetN() << " , j-Bins: " << sys_mtcorr_t->GetN() << endl;
  for(Int_t i=0; i<=sys_nonclosure_t->GetN(); i++){
    for(Int_t j=0; j<=sys_mtcorr_t->GetN(); j++){
      //out_t->SetBinContent(i,j,TMath::Sqrt( TMath::Power(sys_mtcorr_t->GetY()[j],2) ) );
      // cout << i << "," << j << ": " << TMath::Sqrt( TMath::Power(sys_nonclosure_t->GetY()[i],2) << " " << TMath::Power(sys_mtcorr_t->GetY()[j],2) << " "<<  TMath::Power(additionalDYuncertainty,2) )<<endl;
      // cout << "Bincontent " << i << "," << j << ": " << TMath::Sqrt( TMath::Power(sys_nonclosure_t->GetY()[i],2) + TMath::Power(sys_mtcorr_t->GetY()[j],2) + TMath::Power(additionalDYuncertainty,2) )<<endl;
      out_t->SetBinContent(i,j,TMath::Sqrt( TMath::Power(sys_nonclosure_t->GetY()[i],2) + TMath::Power(sys_mtcorr_t->GetY()[j],2) + TMath::Power(additionalDYuncertainty,2) ) );    
      //overwriting overflow bin (otherwise: inf error):
      if( j == 2000) out_t->SetBinContent(i,j, out_t->GetBinContent(i,j-1));
      if( i == 2000) out_t->SetBinContent(i,j, out_t->GetBinContent(i-1,j));
      if( out_t->GetBinContent(i,j) > 1){
        cout << i << " " << j << " " << out_t->GetBinContent(i,j) << endl;
      } 
    }
  }
  out_t->SetBinContent(2000,2000, out_t->GetBinContent(2000,1999) );
  TFile *fout_f=new TFile(fout.ReplaceAll(".root",tight_cat+".root"),"UPDATE");
  fout_f->cd();
  out_t->Write();
  fout_f->Close();

}

void combineWSystematics_morphed( TString fW_nonclosure, TString sys_nonclosure, TString fW_mtcorr, TString sys_mtcorr, TString fout, TString tout, const TString tight_cat){

  TFile *f_nonclosure=new TFile(fW_nonclosure.ReplaceAll(".root",tight_cat+".root"));
  TGraphAsymmErrors *sys_nonclosure_t_up=(TGraphAsymmErrors*)f_nonclosure->Get(sys_nonclosure+"_up");
  TGraphAsymmErrors *sys_nonclosure_t_down=(TGraphAsymmErrors*)f_nonclosure->Get(sys_nonclosure+"_down");
  TFile *f_mtcorr=new TFile(fW_mtcorr.ReplaceAll(".root",tight_cat+".root"));
  TGraphAsymmErrors *sys_mtcorr_t_up=(TGraphAsymmErrors*)f_mtcorr->Get(sys_mtcorr+"_up");
  TGraphAsymmErrors *sys_mtcorr_t_down=(TGraphAsymmErrors*)f_mtcorr->Get(sys_mtcorr+"_down");

  Double_t additionalDYuncertainty=0;
  if(useWToDYUncertainty){
    if(CHAN==kMU)      additionalDYuncertainty=WToDYUncertainty_mt;
    else if(CHAN==kEL) additionalDYuncertainty=WToDYUncertainty_et;
  }
  TH1D *out_t_lepPt_up = new TH1D(tout+"_lepPt_up", tout+"_lepPt_up", sys_nonclosure_t_up->GetN(), sys_nonclosure_t_up->GetX()[0], sys_nonclosure_t_up->GetX()[sys_nonclosure_t_up->GetN()-1]);
  TH1D *out_t_lepPt_down = new TH1D(tout+"_lepPt_down", tout+"_lepPt_down", sys_nonclosure_t_down->GetN(), sys_nonclosure_t_down->GetX()[0], sys_nonclosure_t_down->GetX()[sys_nonclosure_t_down->GetN()-1]);

  TH1D *out_t_mt_up = new TH1D(tout+"_mt_up", tout+"_mt_up", sys_mtcorr_t_up->GetN(), sys_mtcorr_t_up->GetX()[0], sys_mtcorr_t_up->GetX()[sys_mtcorr_t_up->GetN()-1]);
  TH1D *out_t_mt_down = new TH1D(tout+"_mt_down", tout+"_mt_down", sys_mtcorr_t_down->GetN(), sys_mtcorr_t_down->GetX()[0], sys_mtcorr_t_down->GetX()[sys_mtcorr_t_down->GetN()-1]);
  double lepPt_max = 120.0;
  Int_t n_morph_lepPt = 0; Int_t i_morph_lepPt = 0;
  for(Int_t i=0; sys_nonclosure_t_up->GetX()[i] < lepPt_max; i++){
    n_morph_lepPt += 1;
    i_morph_lepPt = i;
  }
  double mt_max = 160.0;
  Int_t n_morph_mt = 0; Int_t i_morph_mt = 0;
  for(Int_t i=0; sys_mtcorr_t_up->GetX()[i] < mt_max; i++){
    n_morph_mt += 1;
    i_morph_mt = i;
  }
  double morphed_high; double morphed_low; 
  // cout << "i-Bins: " << sys_nonclosure_t->GetN() << " , j-Bins: " << sys_mtcorr_t->GetN() << endl;
  for(Int_t i=0; i<=sys_nonclosure_t_up->GetN(); i++){
    morphed_high = (-sys_nonclosure_t_down->GetY()[i])*float( n_morph_lepPt-i-1)/(n_morph_lepPt-1) + (sys_nonclosure_t_up->GetY()[i])*float(i)/(n_morph_lepPt-1);
    morphed_low = (sys_nonclosure_t_up->GetY()[i])*float( n_morph_lepPt-i-1)/(n_morph_lepPt-1) + (-sys_nonclosure_t_down->GetY()[i])*float(i)/(n_morph_lepPt-1);
    if (i>i_morph_lepPt){
      morphed_high = (-sys_nonclosure_t_down->GetY()[i_morph_lepPt])*float( n_morph_lepPt-i_morph_lepPt-1)/(n_morph_lepPt-1) + (sys_nonclosure_t_up->GetY()[i_morph_lepPt])*float(i_morph_lepPt)/(n_morph_lepPt-1);
      morphed_low = (sys_nonclosure_t_up->GetY()[i_morph_lepPt])*float( n_morph_lepPt-i_morph_lepPt-1)/(n_morph_lepPt-1) + (-sys_nonclosure_t_down->GetY()[i_morph_lepPt])*float(i_morph_lepPt)/(n_morph_lepPt-1);
    }
    out_t_lepPt_up->SetBinContent(i,morphed_high);
    out_t_lepPt_down->SetBinContent(i,morphed_low);
  }
  for(Int_t i=0; i<=sys_mtcorr_t_up->GetN(); i++){
    morphed_high = (-sys_mtcorr_t_down->GetY()[i])*float( n_morph_mt-i-1)/(n_morph_mt-1) + (sys_mtcorr_t_up->GetY()[i])*float(i)/(n_morph_mt-1);
    morphed_low = (sys_mtcorr_t_up->GetY()[i])*float( n_morph_mt-i-1)/(n_morph_mt-1) + (-sys_mtcorr_t_down->GetY()[i])*float(i)/(n_morph_mt-1);
    if (i>i_morph_mt){
      morphed_high = (-sys_mtcorr_t_down->GetY()[i_morph_mt])*float( n_morph_mt-i_morph_mt-1)/(n_morph_mt-1) + (sys_mtcorr_t_up->GetY()[i_morph_mt])*float(i_morph_mt)/(n_morph_mt-1);
      morphed_low = (sys_mtcorr_t_up->GetY()[i_morph_mt])*float( n_morph_mt-i_morph_mt-1)/(n_morph_mt-1) + (-sys_mtcorr_t_down->GetY()[i_morph_mt])*float(i_morph_mt)/(n_morph_mt-1);
    }
    out_t_mt_up->SetBinContent(i,morphed_high );
    out_t_mt_down->SetBinContent(i,morphed_low );
    //overwriting overflow bin (otherwise: inf error)
    }

  TFile *fout_f=new TFile(fout.ReplaceAll(".root",tight_cat+".root"),"UPDATE");
  fout_f->cd();
  out_t_lepPt_up->Write();
  out_t_lepPt_down->Write();
  out_t_mt_up->Write();
  out_t_mt_down->Write();
  fout_f->Close();

}


void combineTTSystematics( TString fTT_nonclosure, TString sys_nonclosure, TString fout, TString tout, const TString tight_cat){

  const TString d="ViennaTool/fakefactor/data_"+s_chan[CHAN]+"/";
  
  TFile *f_nonclosure=new TFile(fTT_nonclosure.ReplaceAll(".root",tight_cat+".root"));
  TGraphAsymmErrors *sys_nonclosure_t=(TGraphAsymmErrors*)f_nonclosure->Get(sys_nonclosure);

  TFile *f_data_CR=new TFile(d+"FF_corr_TT_MCsum_noGen.root");
  TH1D *h_data_CR= (TH1D*)f_data_CR->Get("c_t"+tight_cat);
  TFile *f_MC_CR=new TFile(d+"FF_TT_J_only.root");
  TH1D *h_MC_CR= (TH1D*)f_MC_CR->Get("c_t"+tight_cat);

  Double_t scale_factors[2];
  scale_factors[0] = abs(h_data_CR->GetBinContent(1)-h_MC_CR->GetBinContent(1))/h_MC_CR->GetBinContent(1); 
  scale_factors[1] = abs(h_data_CR->GetBinContent(1)-h_MC_CR->GetBinContent(1))/h_MC_CR->GetBinContent(1);
  
  //Double_t scale_factors[]={0.37,0.09};
  //Double_t scale_factors[]={0.23,0.06};
  cout << "///////////////////////////////////////////////////////" << endl;
  cout << "TT data/MC scale factors:" << endl;
  cout << "Data: " << h_data_CR->GetBinContent(1) << " and MC: " << h_MC_CR->GetBinContent(1) << " -> " << scale_factors[0] << endl;

  TH1D *out_t = new TH1D(tout, tout, sys_nonclosure_t->GetN(), sys_nonclosure_t->GetX()[0], sys_nonclosure_t->GetX()[sys_nonclosure_t->GetN()-1]);
  for(Int_t i=0; i<=sys_nonclosure_t->GetN(); i++){
    out_t->SetBinContent(i,TMath::Sqrt( TMath::Power(sys_nonclosure_t->GetY()[i],2)+TMath::Power(scale_factors[0],2) ));    
  }
  // cout << "TT-Outputfile: " << fout.ReplaceAll(".root",tight_cat+".root") << endl;
  TFile *fout_f=new TFile(fout.ReplaceAll(".root",tight_cat+".root"),"UPDATE");
  fout_f->cd();
  out_t->Write();
  fout_f->Close();
  f_data_CR->Close();
  f_MC_CR->Close();

}

void combineTTSystematics_morphed( TString fTT_nonclosure, TString sys_nonclosure, TString fout, TString tout, const TString tight_cat){

  const TString d="ViennaTool/fakefactor/data_"+s_chan[CHAN]+"/";
  
  TFile *f_nonclosure=new TFile(fTT_nonclosure.ReplaceAll(".root",tight_cat+".root"));
  TGraphAsymmErrors *sys_nonclosure_t_up=(TGraphAsymmErrors*)f_nonclosure->Get(sys_nonclosure+"_up");
  TGraphAsymmErrors *sys_nonclosure_t_down=(TGraphAsymmErrors*)f_nonclosure->Get(sys_nonclosure+"_down");

  TFile *f_data_CR=new TFile(d+"FF_corr_TT_MCsum_noGen.root");
  TH1D *h_data_CR= (TH1D*)f_data_CR->Get("c_t"+tight_cat);
  TFile *f_MC_CR=new TFile(d+"FF_TT_J_only.root");
  TH1D *h_MC_CR= (TH1D*)f_MC_CR->Get("c_t"+tight_cat);

  Double_t scale_factors[2];
  scale_factors[0] = abs(h_data_CR->GetBinContent(1)-h_MC_CR->GetBinContent(1))/h_MC_CR->GetBinContent(1); 
  scale_factors[1] = abs(h_data_CR->GetBinContent(1)-h_MC_CR->GetBinContent(1))/h_MC_CR->GetBinContent(1);
  
  //Double_t scale_factors[]={0.37,0.09};
  //Double_t scale_factors[]={0.23,0.06};
  cout << "///////////////////////////////////////////////////////" << endl;
  cout << "TT data/MC scale factors:" << endl;
  cout << "Data: " << h_data_CR->GetBinContent(1) << " and MC: " << h_MC_CR->GetBinContent(1) << " -> " << scale_factors[0] << endl;

  TH1D *out_t_up = new TH1D(tout+"_morphed_up", tout+"_morphed_up", sys_nonclosure_t_up->GetN(), sys_nonclosure_t_up->GetX()[0], sys_nonclosure_t_up->GetX()[sys_nonclosure_t_up->GetN()-1]);
  TH1D *out_t_down = new TH1D(tout+"_morphed_down", tout+"_morphed_down", sys_nonclosure_t_down->GetN(), sys_nonclosure_t_down->GetX()[0], sys_nonclosure_t_down->GetX()[sys_nonclosure_t_down->GetN()-1]);
  TH1D *out_t_sf = new TH1D(tout+"_sf", tout+"_sf", sys_nonclosure_t_down->GetN(), sys_nonclosure_t_down->GetX()[0], sys_nonclosure_t_down->GetX()[sys_nonclosure_t_down->GetN()-1]);
  double morphed_high; double morphed_low;
  // double mvis_max = 250.0;
  // Int_t n_morph_mvis = 0; Int_t i_morph_mvis = 0;
  // for(Int_t i=0; sys_nonclosure_t_up->GetX()[i] < mvis_max; i++){
  //   n_morph_mvis += 1;
  //   i_morph_mvis = i;
  // }

  for(Int_t i=0; i<=sys_nonclosure_t_down->GetN(); i++){
    morphed_high = (-sys_nonclosure_t_down->GetY()[i])*float( sys_nonclosure_t_down->GetN()-i-1)/(sys_nonclosure_t_down->GetN()-1) + (sys_nonclosure_t_up->GetY()[i])*float(i)/(sys_nonclosure_t_down->GetN()-1);
    morphed_low = (sys_nonclosure_t_up->GetY()[i])*float( sys_nonclosure_t_down->GetN()-i-1)/(sys_nonclosure_t_down->GetN()-1) + (-sys_nonclosure_t_down->GetY()[i])*float(i)/(sys_nonclosure_t_down->GetN()-1);
    // if (i>i_morph_mvis){
    //   morphed_high = (-sys_nonclosure_t_down->GetY()[i_morph_mvis])*float( n_morph_mvis-i_morph_mvis-1)/(n_morph_mvis-1) + (sys_nonclosure_t_up->GetY()[i_morph_mvis])*float(i_morph_mvis)/(n_morph_mvis-1);
    //   morphed_low = (sys_nonclosure_t_up->GetY()[i_morph_mvis])*float( n_morph_mvis-i_morph_mvis-1)/(n_morph_mvis-1) + (-sys_nonclosure_t_down->GetY()[i_morph_mvis])*float(i_morph_mvis)/(n_morph_mvis-1);
    // }
    out_t_sf->SetBinContent(i,scale_factors[0]);
    out_t_up->SetBinContent(i, morphed_high);  
    out_t_down->SetBinContent(i, morphed_low);    
  
  }
  out_t_up->SetBinContent(sys_nonclosure_t_up->GetN(),out_t_up->GetBinContent(sys_nonclosure_t_up->GetN()-1));
  out_t_down->SetBinContent(sys_nonclosure_t_down->GetN(),out_t_down->GetBinContent(sys_nonclosure_t_down->GetN()-1));

  // cout << "TT-Outputfile: " << fout.ReplaceAll(".root",tight_cat+".root") << endl;
  TFile *fout_f=new TFile(fout.ReplaceAll(".root",tight_cat+".root"),"UPDATE");
  fout_f->cd();
  out_t_sf->Write();
  out_t_up->Write();
  out_t_down->Write();

  fout_f->Close();
  f_data_CR->Close();
  f_MC_CR->Close();

}
  

#ifndef __CINT__
int main(int argc, char* argv[]) {
  if(inclusive_selection) convert_inputs();
  if(exclusive_selection){
    for(Int_t icat=0; icat<nCAT; icat++){
      if(CHAN==kTAU && icat >= 2) continue;
      cout << icat << endl;
      convert_inputs(0,catMode[icat]);
    }
  }
  else convert_inputs();
}
#endif

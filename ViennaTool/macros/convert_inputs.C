#include "TFile.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TGraphAsymmErrors.h"
#include "TString.h"
#include "ViennaTool/Globals.h"
#include "ViennaTool/interface/GaussianKernelSmoother.h"

void conv_th1_to_th2( const TString fn , const TString hn , const TString hnout , const TString fout_n , const int opt );
void conv_th1_to_th3( const TString fn , const TString hn, const TString hnout, const TString fout_n , const Int_t njetbinned=1 );
//void conv_th1_to_th2( const TString fn , const TString hn , const TString fout_n , const Int_t N_D1, const Int_t N_D2, const Double_t V1[], const Int_t V2[], const int ntoys=0 );
void make_frac_sys( const TString fn , const std::vector<TString> fn_other , const TString hn , const TString hnout , const std::vector<TString> hn_other , const TString fout_n , const int opt );
void make_frac_sys( const TString fn , const std::vector<TString> fn_other , const TString hn , const TString hnout , const std::vector<TString> hn_other , const TString fout_n , const Int_t N_D1, const Int_t N_D2, const Double_t V1[], const Int_t V2[], const int ntoys=0 );
void make_3Dhisto( const TString fn , const TString hn , const TString hnout , const TString fout_n , const Int_t N_D1, const Int_t N_D2, const Int_t N_D3, const Double_t V1[], const Int_t V2[], const Int_t V3[], Int_t njetbinned=1 );
void copy_th1( const TString fn , const TString hn , const TString fout_n );
void smooth_th1( const TString fn , const TString hn , const TString fout_n , const int useBinErrors=0 );
TH1D* extract_binerr_histo( TString fn , TString hn );
TString getCatString(Int_t categoryMode=0);

void convert_corrections( const TString fn, const TString gn, const TString fout, const TString gout);
void combineQCDSystematics( const TString fQCD_nonclosure, const TString sys_nonclosure, const TString fQCD_muiso, const TString fQCD_OSSS, const TString sys_OSSS, const TString sys_muiso, const TString fout, const TString tout);
void combineWSystematics( const TString fW_nonclosure, const TString sys_nonclosure, const TString fW_mtcorr, const TString sys_mtcorr, const TString fout, const TString tout);
void combineTTSystematics( const TString fTT_nonclosure, const TString sys_nonclosure, const TString fout, const TString tout);

void convert_inputs(Int_t categoryMode=0){

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
  if(calcVTightFF) vtightString+="_VTight";

  const TString d="ViennaTool/fakefactor/data_"+s_chan[CHAN]+"/";
  const TString o="ViennaTool/ff_2d/"+s_chan[CHAN]+"/"+catString+"/";
  catString.ReplaceAll("incl","");
  
  //catString="SS_incl";
  //const TString d="fakefactor/data_"+s_chan[CHAN]+"/";
  //const TString o="ff_2d/"+s_chan[CHAN]+"/"+catString+"/";
  //catString.ReplaceAll("SS_incl","");

  //const TString d="fakefactor/mc_"+s_chan[CHAN]+"/";
  //const TString o="ff_2d/"+s_chan[CHAN]+"/mc_incl/";
  //catString.ReplaceAll("incl","");

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
  conv_th1_to_th2( d+fn , hn , o+fout_n , hnout , 0 );

  fn="FF_corr_TT_MCsum_noGen.root";
  hn="c_t";
  fout_n="FakeFactors_Data_TT_2D.root";
  fout_n3d="FakeFactors_Data_TT_3D.root";
  hnout="FakeFactors_Data_TT_anyb_addLep_InvertIso_tau_pt_vs_decayMode";
  hnout3d="FakeFactors_Data_TT_anyb_addLep_InvertIso_tau_pt_vs_decayMode";
  //conv_th1_to_th2( d+fn , hn , o+fout_n , hnout , 0 );
  if(CHAN!=kTAU)conv_th1_to_th3( d+fn , hn , hnout3d, o+fout_n3d , 0 );

  fn="FF_corr_QCD_MCsum_noGen"+AIstring+vtightString+".root";
  fn3d="FF_corr_QCD_MCsum_noGen"+AIstring+vtightString+".root";
  hn="c_t";
  hnout="FakeFactors_Data_QCDSS_2D_SS_Iso_Medium_SS_InvertIso_Medium_tau_pt_vs_decayMode";
  hnout3d="FakeFactors_Data_QCDSS_3D_SS_Iso_Medium_SS_InvertIso_Medium_tau_pt_vs_decayMode";
  fout_n="FakeFactors_Data_QCD_2D.root";
  fout_n3d="FakeFactors_Data_QCD_3D.root";
  //conv_th1_to_th2( d+fn , hn , hnout , o+fout_n , 0 );
  conv_th1_to_th3( d+fn3d , hn , hnout3d , o+fout_n3d );

  if(!CALC_SS_SR){
    convert_corrections( d+FF_corr_QCD_MCsum_noGen_nonclosure, "nonclosure_QCD", o+"Correction_Data_QCD_MVis.root", "QCD_SS_MuMedium_Data_FFSSMuMediumData_mvis_correction");
    if(CHAN!=kTAU){      
      convert_corrections( d+FF_corr_QCD_MCsum_noGen_muisocorr, "muiso_QCD", o+"Correction_Data_QCD_MuIso.root", "QCD_SS_Data_FFSSMuMediumData_isomu_correction");
      convert_corrections( d+FF_corr_QCD_MCsum_noGen_OSSScorr, "OSSS_corr_QCD", o+"Correction_Data_QCD_OSSS.root", "QCD_SS_Data_FFSSMuMediumData_OSSS_correction");
      //convert_corrections( d+"FF_corr_QCD_only_noGen_nonclosure.root", "nonclosure_QCD_MC", o+"Correction_Data_QCD_MVis.root", "QCD_SS_MuMedium_Data_FFSSMuMediumData_mvis_correction");
      //convert_corrections( d+"FF_corr_QCD_only_noGen_muisocorr.root", "muiso_QCD", o+"Correction_Data_QCD_MuIso.root", "QCD_SS_Data_FFSSMuMediumData_isomu_correction");
      //convert_corrections( d+"FF_corr_QCD_only_noGen_OSSS.root", "OSSS_corr_QCD", o+"Correction_Data_QCD_OSSS.root", "QCD_SS_Data_FFSSMuMediumData_OSSS_correction");
      convert_corrections( d+FF_corr_Wjets_MCsum_noGen_nonclosure, "nonclosure_Wjets", o+"Correction_Data_W_MVis.root", "W_OS_Data_FFOSData_mvis_correction");
      //convert_corrections( d+"FF_corr_Wjets_MC_noGen_nonclosure.root", "nonclosure_Wjets_MC", o+"Correction_Data_W_MVis.root", "W_OS_Data_FFOSData_mvis_correction");
      convert_corrections( d+FF_corr_Wjets_MC_noGen_mtcorr, "mt_corr_Wjets", o+"Correction_MC_W_MT.root", "W_OS_MC_FFOSMC_mt_correction");
      convert_corrections( d+FF_corr_TT_MC_noGen_nonclosure, "nonclosure_TT_MC", o+"Correction_MC_TT_MVis.root", "TT_OS_MC_mvis_correction");
    }
  }
  else{
    convert_corrections( d+FF_corr_QCD_MCsum_noGen_nonclosure_AI, "nonclosure_QCD", o+"Correction_Data_QCD_MVis.root", "QCD_SS_MuMedium_Data_FFSSMuMediumData_mvis_correction");
    convert_corrections( d+FF_corr_QCD_MCsum_noGen_muisocorr_AI, "muiso_QCD", o+"Correction_Data_QCD_MuIso.root", "QCD_SS_Data_FFSSMuMediumData_isomu_correction");
    convert_corrections( d+FF_corr_Wjets_MCsum_noGen_nonclosure_SS_SR, "nonclosure_Wjets", o+"Correction_Data_W_MVis.root", "W_OS_Data_FFOSData_mvis_correction");
    convert_corrections( d+FF_corr_Wjets_MC_noGen_mtcorr_SS_SR, "mt_corr_Wjets", o+"Correction_MC_W_MT.root", "W_OS_MC_FFOSMC_mt_correction");
  }
  //convert_corrections( d+"FF_corr_Wjets_MC_noGen_mtcorr_SS_SR.root", "mt_corr_Wjets", o+"Correction_MC_W_MT.root", "W_OS_MC_FFOSMC_mt_correction");

  if(!CALC_SS_SR){
    combineQCDSystematics( d+FF_corr_QCD_MCsum_noGen_nonclosure, "nonclosure_QCD_up", d+FF_corr_QCD_MCsum_noGen_muisocorr, "muiso_corr_QCD_up", d+FF_corr_QCD_MCsum_noGen_OSSScorr, "OSSS_corr_QCD_up",o+"uncertainties_QCD_W.root", "uncertainties_QCD_MVis_Iso_SS2OS_up");
    combineQCDSystematics( d+FF_corr_QCD_MCsum_noGen_nonclosure, "nonclosure_QCD_down", d+FF_corr_QCD_MCsum_noGen_muisocorr, "muiso_corr_QCD_down", d+FF_corr_QCD_MCsum_noGen_OSSScorr, "OSSS_corr_QCD_up", o+"uncertainties_QCD_W.root", "uncertainties_QCD_MVis_Iso_SS2OS_down");
    if(CHAN!=kTAU){
      
      combineWSystematics( d+FF_corr_Wjets_MCsum_noGen_nonclosure, "nonclosure_Wjets_up", d+FF_corr_Wjets_MC_noGen_mtcorr, "mt_corr_Wjets_up", o+"uncertainties_QCD_W.root", "uncertainties_W_MVis_MT_up" );
      combineWSystematics( d+FF_corr_Wjets_MCsum_noGen_nonclosure, "nonclosure_Wjets_down", d+FF_corr_Wjets_MC_noGen_mtcorr, "mt_corr_Wjets_down", o+"uncertainties_QCD_W.root", "uncertainties_W_MVis_MT_down" );
      if(CHAN==kMU)combineTTSystematics( d+FF_corr_TT_MC_noGen_nonclosure, "nonclosure_TT_MC_up", o+"uncertainties_TT.root", "uncertainties_TT_MVis_up" );
      if(CHAN==kMU)combineTTSystematics( d+FF_corr_TT_MC_noGen_nonclosure, "nonclosure_TT_MC_down", o+"uncertainties_TT.root", "uncertainties_TT_MVis_down" );
      //combineQCDSystematics( d+"FF_corr_QCD_only_noGen_nonclosure.root", "nonclosure_QCD_MC_up", d+"FF_corr_QCD_only_noGen_muisocorr.root", "muiso_corr_QCD_up", d+"FF_corr_QCD_only_noGen_OSSS.root", "OSSS_corr_QCD_up",o+"uncertainties_QCD_W.root", "uncertainties_QCD_MVis_Iso_SS2OS_up");
      //combineQCDSystematics( d+"FF_corr_QCD_only_noGen_nonclosure.root", "nonclosure_QCD_MC_down", d+"FF_corr_QCD_only_noGen_muisocorr.root", "muiso_corr_QCD_down", d+"FF_corr_QCD_only_noGen_OSSS.root", "OSSS_corr_QCD_up", o+"uncertainties_QCD_W.root", "uncertainties_QCD_MVis_Iso_SS2OS_down");
      
      //combineWSystematics( d+"FF_corr_Wjets_MC_noGen_nonclosure.root", "nonclosure_Wjets_MC_up", d+FF_corr_Wjets_MC_noGen_mtcorr, "mt_corr_Wjets_up", o+"uncertainties_QCD_W.root", "uncertainties_W_MVis_MT_up" );
      //combineWSystematics( d+"FF_corr_Wjets_MC_noGen_nonclosure.root", "nonclosure_Wjets_MC_down", d+FF_corr_Wjets_MC_noGen_mtcorr, "mt_corr_Wjets_down", o+"uncertainties_QCD_W.root", "uncertainties_W_MVis_MT_down" );
    }
  }
  else{
    combineQCDSystematics( d+FF_corr_QCD_MCsum_noGen_nonclosure_AI, "nonclosure_QCD_up", d+FF_corr_QCD_MCsum_noGen_muisocorr_AI, "muiso_corr_QCD_up", d+FF_corr_QCD_MCsum_noGen_OSSScorr, "OSSS_corr_QCD_up",o+"uncertainties_QCD_W.root", "uncertainties_QCD_MVis_Iso_SS2OS_up");
    combineQCDSystematics( d+FF_corr_QCD_MCsum_noGen_nonclosure_AI, "nonclosure_QCD_down", d+FF_corr_QCD_MCsum_noGen_muisocorr_AI, "muiso_corr_QCD_down", d+FF_corr_QCD_MCsum_noGen_OSSScorr, "OSSS_corr_QCD_up", o+"uncertainties_QCD_W.root", "uncertainties_QCD_MVis_Iso_SS2OS_down");
    
    combineWSystematics( d+FF_corr_Wjets_MCsum_noGen_nonclosure_SS_SR, "nonclosure_Wjets_up", d+FF_corr_Wjets_MC_noGen_mtcorr_SS_SR, "mt_corr_Wjets_up", o+"uncertainties_QCD_W.root", "uncertainties_W_MVis_MT_up" );
    combineWSystematics( d+FF_corr_Wjets_MCsum_noGen_nonclosure_SS_SR, "nonclosure_Wjets_down", d+FF_corr_Wjets_MC_noGen_mtcorr_SS_SR, "mt_corr_Wjets_down", o+"uncertainties_QCD_W.root", "uncertainties_W_MVis_MT_down" );
  }

  //stat. unc. of fractions
  /*std::vector<TString> fn_other_w; fn_other_w.push_back( d+fnD ); fn_other_w.push_back( d+fnT ); fn_other_w.push_back( d+fnQ );
  std::vector<TString> fn_other_d; fn_other_d.push_back( d+fnW ); fn_other_d.push_back( d+fnT ); fn_other_d.push_back( d+fnQ );
  std::vector<TString> fn_other_t; fn_other_t.push_back( d+fnW ); fn_other_t.push_back( d+fnD ); fn_other_t.push_back( d+fnQ );
  std::vector<TString> fn_other_q; fn_other_q.push_back( d+fnW ); fn_other_q.push_back( d+fnD ); fn_other_q.push_back( d+fnT );

  std::vector<TString> hn_other_w; hn_other_w.push_back( hn+"D"); hn_other_w.push_back( hn+"T"); hn_other_w.push_back( hn+"Q");
  std::vector<TString> hn_other_d; hn_other_d.push_back( hn+"W"); hn_other_d.push_back( hn+"T"); hn_other_d.push_back( hn+"Q");
  std::vector<TString> hn_other_t; hn_other_t.push_back( hn+"W"); hn_other_t.push_back( hn+"D"); hn_other_t.push_back( hn+"Q");
  std::vector<TString> hn_other_q; hn_other_q.push_back( hn+"W"); hn_other_q.push_back( hn+"D"); hn_other_q.push_back( hn+"T");

  make_frac_sys( d+fnW , fn_other_w , hn , hnout , hn_other_w , o+fout_nW , 1 );
  make_frac_sys( d+fnD , fn_other_d , hn , hnout , hn_other_d , o+fout_nD , 1 );
  make_frac_sys( d+fnT , fn_other_t , hn , hnout , hn_other_t , o+fout_nT , 1 );
  make_frac_sys( d+fnQ , fn_other_q , hn , hnout , hn_other_q , o+fout_nQ , 1 );*/

  /*
   *   fn="sys_TT_J_nonclosure_mvis.root";
     hn="sys";
       fout_n="sys_tt_nonclosure_mvis.root";
       copy_th1( d+fn , hn , o+fout_n );
       fn="corr_TT_J_nonclosure_mvis.root";
       hn="corr";
       fout_n="corr_tt_mvis.root";
       copy_th1( d+fn , hn , o+fout_n );
  */

}

void conv_th1_to_th2( const TString fn , const TString hn , const TString hnout , const TString fout_n , const int opt ){

  std::vector<TString> dummy(0);
  //  if ( opt==0 ) conv_th1_to_th2( fn , hn , fout_n , N_p_Wjets , N_t_Wjets , Pt_cuts_Wjets , Decay_cuts_Wjets , 100 );
  //  if ( opt==1 ) conv_th1_to_th2( fn , hn , fout_n , w_mt_n    , N_t_Wjets , w_mt_v        , Decay_cuts_Wjets );
  make_frac_sys( fn , dummy , hn , hnout , dummy , fout_n , opt );

}

void conv_th1_to_th3( const TString fn , const TString hn, const TString hnout, const TString fout_n, const Int_t njetbinned ){

  make_3Dhisto( fn, hn, hnout, fout_n, N_p_Wjets, N_t_Wjets, N_j_Wjets, Pt_cuts_Wjets, Decay_cuts_Wjets, Njet_cuts_Wjets, njetbinned );
  
}

void make_3Dhisto( const TString fn , const TString hn , const TString hnout , const TString fout_n , const Int_t N_D1, const Int_t N_D2, const Int_t N_D3, const Double_t V1[], const Int_t V2[], const Int_t V3[] , Int_t njetbinned ){

  cout << "make_3D_histo \t" << fn << "\t" << hn << "\t" << fout_n << "\t" << endl;

  Double_t d1[N_D1+1];
  Double_t d2[N_D2+1];
  Double_t d3[N_D3+1];

  for (int i=0; i<N_D1; i++){
    d1[i]=V1[i];
  }
  d1[N_D1]=250;

  for (int i=0; i<N_D2; i++){
    d2[i]=V2[i];
  }
  d2[N_D2]=15;

  for (int i=0; i<N_D3; i++){
    d3[i]=V3[i];
  }
  d3[N_D3]=10;

  TFile *f=new TFile( fn );
  TH1D *h=(TH1D*) f->Get(hn);

  TH3D *hout      = new TH3D( hnout,            "",  N_D1 , d1,  N_D2 ,  d2 , N_D3 , d3 );
  TH3D *hout_err  = new TH3D( hnout+"_error",      "",  N_D1 , d1,  N_D2 ,  d2 , N_D3 , d3 );
  TString replaceString=hnout;
  replaceString.ReplaceAll("_3d","");

  if(njetbinned){
    for (int i=0; i<N_D1; i++){
      for (int j=0; j<N_D2; j++){
        for (int k=0; k<N_D3; k++){
          double cont=h->GetBinContent( i+N_D1*j + (N_D1*N_D2)*k + 1 );
          /*cout << "i: " << i << endl;
          cout << "j: " << j << endl;
          cout << "k: " << k << endl;
          cout << i+N_D1*j + (N_D1*N_D2)*k + 1 << ": " << h->GetBinContent( i+N_D1*j + (N_D1*N_D2)*k + 1 ) << endl;*/
          double err =h->GetBinError( i+N_D1*j + (N_D1*N_D2)*k + 1 );
          hout->SetBinContent(       i+1 , j+1 , k+1 , cont );
          hout->SetBinError(         i+1 , j+1 , k+1 , err );
          hout_err->SetBinContent(       i+1 , j+1 , k+1 , err/cont );
          cout << cont << " " << err << " " << err/cont << endl;
          hout_err->SetBinError(       i+1 , j+1 , k+1 , err );
        }
      }
    }
  }
  else{
    for (int i=0; i<N_D1; i++){
      for (int j=0; j<N_D2; j++){
        for (int k=0; k<N_D3; k++){
          double cont=h->GetBinContent( i+N_D1*j + 1 );
          /*cout << "i: " << i << endl;
          cout << "j: " << j << endl;
          cout << "k: " << k << endl;
          cout << i+N_D1*j + 1 << ": " << h->GetBinContent( i+N_D1*j + 1 ) << endl;*/
          double err =h->GetBinError( i+N_D1*j + 1 );
          hout->SetBinContent(       i+1 , j+1 , k+1 , cont );
          hout->SetBinError(         i+1 , j+1 , k+1 , err );
          hout_err->SetBinContent(       i+1 , j+1 , k+1 , err );
          hout_err->SetBinError(       i+1 , j+1 , k+1 , err/cont );
        }
      }
    }
  }
  
    
  TFile *fout=new TFile ( fout_n , "RECREATE" );
  hout->Write();
  hout_err->Write();
  fout->Close();

  f->Close();

}

void make_frac_sys( const TString fn , const std::vector<TString> fn_other , const TString hn , const TString hnout , const std::vector<TString> hn_other , const TString fout_n , const int opt ){

  if ( opt==0 ) make_frac_sys( fn , fn_other , hn , hnout, hn_other , fout_n , N_p_Wjets , N_t_Wjets , Pt_cuts_Wjets , Decay_cuts_Wjets );
  if ( opt==1 ) make_frac_sys( fn , fn_other , hn , hnout, hn_other , fout_n , w_mt_n    , N_t_Wjets , w_mt_v        , Decay_cuts_Wjets );

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
  d1[N_D1]=250;

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
      hout_low->SetBinContent(  i+1 , j+1 , cont-err );
      hout_high->SetBinContent( i+1 , j+1 , cont+err );

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
        //if ( (i+1)==5 && (j+1)==1 ) std::cout << hn_other.at(jf) << "\t" << v_other.at(jf) << "\t" << shift << "\t" << v_other.at(jf) - shift  << " == " << h_low_other.at(jf)->GetBinContent(  i+1 , j+1 )  << endl;
        //cout << "A " << h_low_other.at(0)->GetBinContent(  5, 1 ) << "\t" << i+1 << "\t" << j+1 << "\t" << jf << endl;
              
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

  if ( categoryMode & _0JET ) return categories[0];
  if ( categoryMode & _1JET ) return categories[1];
  if ( categoryMode & _1JETZ050 ) return categories[2];
  if ( categoryMode & _1JETZ50100 ) return categories[3];
  if ( categoryMode & _1JETZ100 ) return categories[4];
  if ( categoryMode & _2JET ) return categories[5];
  if ( categoryMode & _2JETVBF ) return categories[6];
  if ( categoryMode & _ANYB ) return categories[7];

  return "incl";
  
}

void convert_corrections( const TString fn, const TString gn, const TString fout, const TString gout){

  TFile *f=new TFile(fn);
  TGraphAsymmErrors *t=(TGraphAsymmErrors*)f->Get(gn);
  TFile *fout_h=new TFile(fout,"RECREATE");
  TGraphAsymmErrors *gout_h=(TGraphAsymmErrors*)t->Clone(gout);
  gout_h->SetTitle(gout);
  fout_h->cd();
  gout_h->Write();
  f->Close();fout_h->Close();
  
}

void combineQCDSystematics( const TString fQCD_nonclosure, const TString sys_nonclosure, const TString fQCD_muiso, const TString sys_muiso, const TString fQCD_OSSS, const TString sys_OSSS, const TString fout, const TString tout){

  if(CHAN!=kTAU){
    TFile *f_nonclosure=new TFile(fQCD_nonclosure);
    TGraphAsymmErrors *sys_nonclosure_t=(TGraphAsymmErrors*)f_nonclosure->Get(sys_nonclosure);
    TFile *f_muiso=new TFile(fQCD_muiso);
    TGraphAsymmErrors *sys_muiso_t=(TGraphAsymmErrors*)f_muiso->Get(sys_muiso);
    TFile *f_OSSS=new TFile(fQCD_OSSS);
    TGraphAsymmErrors *sys_OSSS_t=(TGraphAsymmErrors*)f_OSSS->Get(sys_OSSS);
    
    TH2D *out_t = new TH2D(tout, tout, sys_nonclosure_t->GetN(), sys_nonclosure_t->GetX()[0], sys_nonclosure_t->GetX()[sys_nonclosure_t->GetN()-1], sys_muiso_t->GetN(), sys_muiso_t->GetX()[0], sys_muiso_t->GetX()[sys_muiso_t->GetN()-1]);
    for(Int_t i=0; i<sys_nonclosure_t->GetN(); i++){
      for(Int_t j=0; j<sys_muiso_t->GetN(); j++){
        //if(!CALC_SS_SR) out_t->SetBinContent(i,j,TMath::Sqrt( TMath::Power(sys_nonclosure_t->GetY()[i],2) ) );
        if(!CALC_SS_SR)out_t->SetBinContent(i,j,TMath::Sqrt( TMath::Power(sys_nonclosure_t->GetY()[i],2) + TMath::Power(sys_muiso_t->GetY()[j],2) ) + TMath::Power(sys_OSSS_t->GetY()[i],2) );
        else out_t->SetBinContent(i,j,TMath::Sqrt( TMath::Power(sys_nonclosure_t->GetY()[i],2) + TMath::Power(sys_muiso_t->GetY()[j],2) ) );
      }
    }
    TFile *fout_f=new TFile(fout,"UPDATE");
    fout_f->cd();
    out_t->Write();
    fout_f->Close();
  }

  else{
    TFile *f_nonclosure=new TFile(fQCD_nonclosure);
    TGraphAsymmErrors *sys_nonclosure_t=(TGraphAsymmErrors*)f_nonclosure->Get(sys_nonclosure);
    
    TH1D *out_t = new TH1D(tout, tout, sys_nonclosure_t->GetN(), sys_nonclosure_t->GetX()[0], sys_nonclosure_t->GetX()[sys_nonclosure_t->GetN()-1]);
    for(Int_t i=0; i<sys_nonclosure_t->GetN(); i++){
      out_t->SetBinContent(i,TMath::Sqrt( TMath::Power(sys_nonclosure_t->GetY()[i],2) + TMath::Power(0.05,2) ) );
    }
    TFile *fout_f=new TFile(fout,"UPDATE");
    fout_f->cd();
    out_t->Write();
    fout_f->Close();
    
  }
}

void combineWSystematics( const TString fW_nonclosure, const TString sys_nonclosure, const TString fW_mtcorr, const TString sys_mtcorr, const TString fout, const TString tout){

  TFile *f_nonclosure=new TFile(fW_nonclosure);
  TGraphAsymmErrors *sys_nonclosure_t=(TGraphAsymmErrors*)f_nonclosure->Get(sys_nonclosure);
  TFile *f_mtcorr=new TFile(fW_mtcorr);
  TGraphAsymmErrors *sys_mtcorr_t=(TGraphAsymmErrors*)f_mtcorr->Get(sys_mtcorr);

  TH2D *out_t = new TH2D(tout, tout, sys_nonclosure_t->GetN(), sys_nonclosure_t->GetX()[0], sys_nonclosure_t->GetX()[sys_nonclosure_t->GetN()-1], sys_mtcorr_t->GetN(), sys_mtcorr_t->GetX()[0], sys_mtcorr_t->GetX()[sys_mtcorr_t->GetN()-1]);
  for(Int_t i=0; i<sys_nonclosure_t->GetN(); i++){
    for(Int_t j=0; j<sys_mtcorr_t->GetN(); j++){
      //out_t->SetBinContent(i,j,TMath::Sqrt( TMath::Power(sys_mtcorr_t->GetY()[j],2) ) );
      out_t->SetBinContent(i,j,TMath::Sqrt( TMath::Power(sys_nonclosure_t->GetY()[i],2) + TMath::Power(sys_mtcorr_t->GetY()[j],2) ) );
    }
  }
  TFile *fout_f=new TFile(fout,"UPDATE");
  fout_f->cd();
  out_t->Write();
  fout_f->Close();

}

void combineTTSystematics( const TString fTT_nonclosure, const TString sys_nonclosure, const TString fout, const TString tout){

  TFile *f_nonclosure=new TFile(fTT_nonclosure);
  TGraphAsymmErrors *sys_nonclosure_t=(TGraphAsymmErrors*)f_nonclosure->Get(sys_nonclosure);

  TH1D *out_t = new TH1D(tout, tout, sys_nonclosure_t->GetN(), sys_nonclosure_t->GetX()[0], sys_nonclosure_t->GetX()[sys_nonclosure_t->GetN()-1]);
  for(Int_t i=0; i<sys_nonclosure_t->GetN(); i++){
    out_t->SetBinContent(i,TMath::Sqrt( TMath::Power(sys_nonclosure_t->GetY()[i],2) ));
  }
  TFile *fout_f=new TFile(fout,"UPDATE");
  fout_f->cd();
  out_t->Write();
  fout_f->Close();

}
  
#ifndef __CINT__
int main(int argc, char* argv[]) {
  if(!inclusive_selection){
    for(Int_t icat=0; icat<nCAT; icat++){
      cout << icat << endl;
      convert_inputs(catMode[icat]);
    }
  }
  else convert_inputs();
}
#endif

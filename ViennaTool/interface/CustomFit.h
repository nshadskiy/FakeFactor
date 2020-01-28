#ifndef __CustomFit__
#define __CustomFit__

//#include <algorithm>
#include <stdlib.h>
#include<math.h>
#include<iostream>

#include "TMath.h"
#include "TH1D.h"
#include "TGraphAsymmErrors.h"
#include "TGraphErrors.h"
#include "TString.h"
#include "TRandom3.h"
#include "TF1.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TSpline.h"

//#include "Math/Minimizer.h"

using namespace std;

static const int NTOYS = 200;

class CustomFit
{

 public:
  CustomFit();
  //  ~CustomFit();

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  int setInputHisto(TString fname , TString hname ){ 
    TFile *f=new TFile( fname );
    this->h_in=(TH1D*) f->Get( hname );
    if ( this->h_in ) return 0;
    else{ cerr << "ERROR: " << hname << " not found in file " << fname << endl; return 1; }
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  TH1D* returnInputHisto() { 
    return this->h_in; 
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    int setInputHisto( TH1D* m_h ){  // overloaded method - so far never seen being used
    this->h_in=(TH1D*) m_h->Clone();
    if ( this->h_in ) return 0;
    else{ cerr << "ERROR: Could not assign histogram with address " << m_h << endl; return 1; }
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  void set_chi2 (float m_chi2) {
    this->chi2_nominal_fit = m_chi2;    
  }
  void set_Ndof (int m_Ndof) {
    this->N_dof = m_Ndof;    
  }
  
  float get_chi2 () {
    return this->chi2_nominal_fit;    
  }
  int get_Ndof () {
    return this->N_dof;    
  }

  void set_fitFunc( TString m_fitFunc ){ 
    this->fitFunc = m_fitFunc;
    if (this->errFunc == "") this->errFunc = m_fitFunc;
  }
  void set_errFunc( TString m_errFunc ){ 
    this->errFunc = m_errFunc; 
  }
  void set_bin_centers( std::vector<double> m_bin_centers ){
    this->bin_centers = m_bin_centers; 
  }
  void set_bin_centers(TString fname , TString hname , int nbins){
    TFile *f=new TFile( fname );
    TH1D *b=(TH1D*) f->Get( hname );
    if ( ! b ){ std::cerr << "ERROR: " << hname << " not found in file " << fname << std::endl; return;}
    std::vector<double> m_bin_centers;
    for (int i=0; i<nbins; i++){
      std::cout << "bin center " << i << " : " << b->GetBinContent(i+this->fitFromBin) << std::endl;
      m_bin_centers.push_back( b->GetBinContent(i+this->fitFromBin) );
    }
    this->bin_centers = m_bin_centers;
  }
  void set_fitFromBin( int m_fitFromBin ){ 
    this->fitFromBin = m_fitFromBin;
  }
  void set_fitMin( float m_fitMin ){ 
    this->fitMin = m_fitMin;
  }
  void set_fitMax( float m_fitMax ){ 
    this->fitMax = m_fitMax;
  }
  void set_autoCorr( int m_autoCorr ){ //try to automatically cut off and smoothen functions if they go below 0
    this->autoCorr = m_autoCorr;       //only effective if histMaxFrac is not set!
  }
  void set_histMaxFrac( float m_histMaxFrac ){ //flat fit after this fractions of bins
    this->histMaxFrac = m_histMaxFrac;
  }
  float get_histMaxFrac( ){
    return this->histMaxFrac;
  }
  void set_maxFracErrorFactor( float m_maxFracErrorFactor ){
    this->maxFracErrorFactor = m_maxFracErrorFactor;
  }
  void set_smoothFrac( float m_smoothFrac ){ //smooth transition starting from this fraction of bins to histMaxFrac
    this->smoothFrac = m_smoothFrac;
  }
  void set_smoothMode( TString m_smoothMode ){ //simple, or spline3
    this->smoothMode = m_smoothMode;
  }
  void set_err_scale( float m_err_scale ){ 
    this->err_scale = m_err_scale;
  }
  void set_err_cl( int m_err_cl ){ 
    this->err_cl = m_err_cl;
  }
  void set_histo_bins( int m_histo_bins ){ 
    this->histo_bins = m_histo_bins;
  }
  
  void fitHisto();

  TGraphAsymmErrors* returnFitInputGraph(){ return this->g_fit_input; }
  TH1D* returnFitHisto(int i=0){ 
    if (i==0)      return this->h_fit; 
    else if (i>0)  return this->h_fit_hi;
    else           return this->h_fit_lo;
  }

  TGraphAsymmErrors* returnFitGraph(){ return this->g_fit; }
  TGraphErrors* returnConfInterval(){ return this->grint; }
  TF1* returnFitForm(){ return this->f_fit; }
  TF1* returnErrFits(int i){ return this->f_fit_err[i]; }

  
  TGraphAsymmErrors* fluctuateGraph();

  private:
  TGraphAsymmErrors* makeFitGraph(TH1D* h_in);
  double std_dev( const std::vector<double> v );
  double std_dev( std::vector<double> v, double& err_lo, double& err_hi , double central_value=0);
  double std_dev( TF1* f[] , const unsigned fsize , const double val , double& err_lo, double& err_hi, const int cl=0);
  TF1* getFitErr();
  
  TH1D *h_in; //input histo
  TH1D *h_fit; //fit result, binned to a histo (output)
  TH1D *h_fit_lo; //fit result, binned to a histo (output), lower uncertainty band
  TH1D *h_fit_hi; //fit result, binned to a histo (output), higher uncertainty band
  TGraphAsymmErrors* g_fit; //fit result, as a TGraph with asym errors

  TF1 *f_fit;
  TF1 *f_fit_err[NTOYS];
  TGraphAsymmErrors* g_fit_input; //input histo, converted to a TGraph
  TGraphErrors* grint;

  TString fitFunc;
  TString errFunc;
  std::vector<double> bin_centers;
  int fitFromBin;
  float histMaxFrac;
  float maxFracErrorFactor;
  float smoothFrac;
  TString smoothMode;
  float smoothParam;
  float smoothExp;
  int autoCorr;

  int N_dof;
  float chi2_nominal_fit;
  
  float fitMin;
  float fitMax;
  float err_scale;
  int err_cl;
  int histo_bins;
  int save_err_fits;
  TRandom3 rand;

  
};

#endif


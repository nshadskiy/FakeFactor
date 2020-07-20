#include "ViennaTool/interface/GaussianKernelSmoother.h"

//ClassImp(GaussianKernelSmoother)

GaussianKernelSmoother::GaussianKernelSmoother(){
  std::cout << "Gaussian kernal smoother initialized" << std::endl;
  this->doIgnoreZeroBins=1.;
  this->doWidthInBins=0.;
  this->widthInBins_sf=0.5;
  this->width=1.;
  this->doErrors=0;
  this->doWeights=0;
  this->kernelDistance="lin";
  this->lastBinFrom=-1;
  this->doLastBinFrom=0;
  this->fixFirstBin=0;
}

TH1D* GaussianKernelSmoother::fluctuateHisto(){
  TH1D *h = (TH1D*)this->h_in->Clone((TString)this->h_in->GetName()+"_toy");
  Int_t nbins = this->h_in->GetNbinsX();

  for (int ib=1; ib<=nbins; ib++){
    double val = this->h_in->GetBinContent(ib);
    double err = this->h_in->GetBinError(ib);
    double newval = this->rand.Gaus(val,err);
    h->SetBinContent(ib,newval);
  }
  return h;
}

double GaussianKernelSmoother::getBinWidthForGaussianWindow(TH1D* m_h) {
  Int_t nbins = m_h->GetNbinsX();
  double bin_width=0;
  for (int ib=1; ib<=nbins; ib++) { // find maximal bin width
    if ( bin_width < m_h->GetBinWidth(ib) ) {
      bin_width=m_h->GetBinWidth(ib);  
    }

  }
  bin_width *= this->widthInBins_sf; // scale the maximal bin width found with widthInBins_sf (= 1.115);
  std::cout << "Bin width for gaussian window: " << bin_width << std::endl;

  return bin_width;
}

double GaussianKernelSmoother::getSmoothedValue( TH1D* m_h , const double x) {
  return 1.1;
}

double GaussianKernelSmoother::getSmoothedValue(TH1D* m_h , const double m_x, const double bin_width){

  double x;
  if ( doLastBinFrom && m_x > lastBinFrom ) x=lastBinFrom; // obsolete doLastBinFrom=0
  else x=m_x;

  double sumw = 0.;
  double sumwy = 0. ;
  Int_t nbins = m_h->GetNbinsX();

  double m_width=this->width;

  if ( this->doWidthInBins ){ // is set to 1 

  
    m_width=0;
    double wsum=0;
    for (int ib=1; ib<=nbins; ib++){
      double w=TMath::Gaus( fabs( x-m_h->GetBinCenter(ib) )/(bin_width) );
      m_width += m_h->GetBinWidth(ib)* w;
      wsum += w;
    }
    m_width /= wsum;
    m_width *= this->width;
  }
  // std::cout << "m_width: " << m_width << std::endl;
      
 
  for (int ib=1; ib<=nbins; ib++){
    double yi = m_h->GetBinContent(ib);
    double ei = m_h->GetBinError(ib);
    if ( fabs(yi)<1e-8 && ei<1e-8 ) {
      // std::cout << "Found low bin content and low uncertainty" << std::endl;
      continue;
    }
    double xi = m_h->GetBinCenter(ib);
    double dx = ( this->rescaling(x) - this->rescaling(xi) ) / m_width;

    double wi = TMath::Gaus(dx);
    if (this->doWeights) wi *= this->h_w->GetBinContent(ib);
    
    sumw += wi;
    sumwy += wi*yi;
  }
   
  double val = 0.;
  if (sumw>0.) val = sumwy/sumw;
    
  return val;
}

void GaussianKernelSmoother::getSmoothHisto(){

  if ( ! this->h_in ) std::cerr << "ERROR: GaussianKernelSmoother::getSmoothHisto: input histo does not exist." << std::endl;

  this->h_out = (TH1D*)this->h_in->Clone(this->h_in->GetName()+(TString)"_smoothed");
  this->h_out->SetDirectory(0);

  Int_t nbins = this->h_out->GetNbinsX();


  double binWidthforGaussianWindow = this->getBinWidthForGaussianWindow(this->h_in);

  for (int ib=1; ib<=nbins; ib++){
    double x = this->h_out->GetBinCenter(ib);
    std::cout << "Bin center at " << x << std::endl;
    double smooth_val = this->getSmoothedValue(this->h_in , x, binWidthforGaussianWindow);
    this->h_out->SetBinContent(ib,smooth_val);
    // exit(0);
  }
}

double GaussianKernelSmoother::rescaling( double val ){

  
  if ( kernelDistance == "lin" ) return val;
  else if ( kernelDistance == "log" ) return log(val);
  else if ( kernelDistance == "err" ) return this->g_rescaling->Eval(val);
  else return val;
}

double GaussianKernelSmoother::invertRescaling( double val ){

  //  if ( doLastBinFrom && lastBinFrom > 0 ) return this->g_inv_rescaling->Eval(val);

  if ( kernelDistance == "lin" ) return val;
  if ( kernelDistance == "log" ) return exp(val);
  if ( kernelDistance == "err" ) return this->g_inv_rescaling->Eval(val);
  else return val;
}

void GaussianKernelSmoother::getContSmoothHisto(){

  if ( ! this->h_in ) std::cerr << "ERROR: GaussianKernelSmoother::getSmoothHisto: input histo does not exist." << std::endl;

  double mini = this->h_in->GetXaxis()->GetBinLowEdge(1);
  double maxi = this->h_in->GetXaxis()->GetBinUpEdge(this->h_in->GetNbinsX());

  std::cout << "mini " << mini << std::endl;
  std::cout << "maxi " << maxi << std::endl;
  

  if ( fabs(mini)<1e-8 ) mini = this->h_in->GetXaxis()->GetBinUpEdge(1)/10.;

  std::cout << "mini " << mini << std::endl;
  std::cout << "maxi " << maxi << std::endl;

  const int nbins = 2000;
  double bins[nbins+1]={0};
  double xs[nbins]={0};
  double ys[nbins]={0};

  double dx = (this->rescaling(maxi) - this->rescaling(mini))/nbins;

  for (int i=0; i<=nbins; i++){
    bins[i] = this->invertRescaling(  this->rescaling(mini) + i*dx  );
  }
  
  double binWidthforGaussianWindow = this->getBinWidthForGaussianWindow(this->h_in);
  for (int i=0; i<nbins; i++){
    xs[i] = ( bins[i]+bins[i+1] )/2;
    if (this->fixFirstBin) {
      if (xs[i]<h_in->GetXaxis()->GetBinUpEdge(1)) {
        ys[i] = this->h_in->GetBinContent(1);
      }
      else {
        ys[i] = this->getSmoothedValue( this->h_in , xs[i], binWidthforGaussianWindow );
      }
    }
    //if (this->fixSecondBin) {
     // if (xs[i]>h_in->GetXaxis()->GetBinUpEdge(1) && xs[i]<h_in->GetXaxis()->GetBinUpEdge(2)) {
      //  ys[i] = this->h_in->GetBinContent(2);
     // }
     // else {
     //   ys[i] = this->getSmoothedValue( this->h_in , xs[i], binWidthforGaussianWindow );
     // }
    //}
    else {
      ys[i] = this->getSmoothedValue( this->h_in , xs[i], binWidthforGaussianWindow );
    }
  } 
  if ( this->doErrors ) {
    const int NTOYS=100;
    double ys_rnd[nbins]={0};
    double ys_err[nbins]={0};
    

    std::vector<double> toys[nbins];
    
    for (int it=0; it<NTOYS; it++){
      TH1D *h_rnd=this->fluctuateHisto();
      for (int ib=0; ib<nbins; ib++){
        ys_rnd[ib]=this->getSmoothedValue( h_rnd , xs[ib], binWidthforGaussianWindow );
        toys[ib].push_back( ys_rnd[ib] );
      }
      delete h_rnd;
    }
    
    for (int i=0; i<nbins; i++){
      ys_err[i]  = this->std_dev( toys[i] );
    }

    g_out=new TGraphAsymmErrors( nbins , xs , ys , 0 , 0 , ys_err , ys_err );
    g_out->SetLineColor(38);
    g_out->SetMarkerColor(kRed);
    g_out->SetMarkerStyle(20);
    g_out->SetMarkerSize(0.5);
    g_out_err=new TGraphAsymmErrors( nbins , xs , ys_err );
  } 
  else { // never happens
    g_out = new TGraphAsymmErrors( nbins , xs , ys , 0 , 0 , 0 , 0 );
    g_out_err=new TGraphAsymmErrors( nbins , xs , 0 );
  }
  

}

TH1D* GaussianKernelSmoother::makeWeights( TH1D* h ){

  TH1D *h_w = (TH1D*)h->Clone( (TString)h->GetName()+"_weights" );
  h_w->SetDirectory(0);

  double sum_weights=0;

  for (int ib=1; ib<=h->GetNbinsX(); ib++){
    double weight = 0.;
    if ( fabs( h->GetBinError(ib) ) > 1e-8 ){
      weight = 1./( pow(h->GetBinError(ib),2) );
    }
    h_w->SetBinContent( ib , weight );
    h_w->SetBinError(   ib , 0      );
    sum_weights+=weight;
  }

  h_w->Scale( 1/sum_weights );

  return h_w;
}


void GaussianKernelSmoother::createGraphKDE( TH1D* m_h ){

  int nbins=m_h->GetNbinsX();

  double *x=new double[nbins];
  double *y=new double[nbins];
 
  double cumsum_y=0;
  for (int ib=1; ib<=nbins; ib++){
    x[ib-1]=m_h->GetBinCenter(ib);
    if ( m_h->GetBinError(ib)>0 ) cumsum_y+=1/sqrt( m_h->GetBinError(ib) );
    y[ib-1]=cumsum_y;
  }
  for (int ib=1; ib<=nbins; ib++){ y[ib-1]/=cumsum_y; }//normalize function

  this->g_rescaling=new TGraph(nbins,x,y);
  this->g_inv_rescaling=new TGraph(nbins,y,x);
}


double GaussianKernelSmoother::std_dev( std::vector<double> v ){
  unsigned size=v.size();

  double mean=0;
  for (unsigned i=0; i<size; i++) mean+=v.at(i)/size;

  double std_dev=0;
  for (unsigned i=0; i<size; i++){
    double diff = v.at(i) - mean;
    std_dev+=diff*diff;
  }
  std_dev/=(size-1.);
  std_dev=sqrt(std_dev);
 
  return std_dev;
}

void GaussianKernelSmoother::createTestHisto(){

  TF1 *p1 = new TF1("p1","[0]+x*[1]+x*x*[2]");
  p1->SetParameters(5., 10., 0.);

  //  std::cout << p1->Eval(-5) << "\t" << p1->Eval(0) << "\t" << p1->Eval(5) << std::endl;

  this->h_in = new TH1D("h_in","",100,1,11);
  this->h_in->FillRandom("p1",1000);
  this->h_in->SetMarkerColor(kBlack);
  this->h_in->SetLineColor(kBlack);

}


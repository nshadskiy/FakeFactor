#include "ViennaTool/interface/CustomFit.h"
#include "TFitResult.h"
#include "TVirtualFitter.h"
#include <math.h>       /* pow */


CustomFit::CustomFit(){ // FIXME: is this initialization in the constructor really needed for all of the variables?
  this->fitFunc="";
  this->errFunc="";
  this->fitFromBin=-1;
  this->histo_bins=100;
  this->err_scale=2;
  this->err_cl=1;
  this->histMaxFrac=99;
  this->maxFracErrorFactor=4;
  this->smoothFrac=-1;
  this->smoothMode="spline3"; //spline3 or simple
  this->smoothParam=2;
  this->smoothExp=0.7;
  this->autoCorr=1;
  this->chi2_nominal_fit=0;
  this->N_dof = -1;
}

void CustomFit::fitHisto(){

  if ( ! this->h_in ) std::cerr << "ERROR: CustomFit::fitHisto: input histo does not exist." << std::endl;

  this->g_fit_input=this->makeFitGraph( h_in ); // TGraphAsymmErrors translation of TH1D h_in

  this->f_fit = new TF1("f1",this->fitFunc,fitMin,fitMax); // 1-Dim function 
  // f_fit->SetParLimits(0,0,1);
  // f_fit->SetParLimits(1,-0.01,0.01);
  // f_fit->ExcludeBin(1);
  // f_fit->ExcludeBin(2);
  
  
  TFitResultPtr r = g_fit_input->Fit(f_fit,"SN"); // "N"-option : Do not store the graphics function, do not draw
                                                  // “S”-option : The result of the fit is returned in the TFitResultPtr
                                                  // ToDo what is "Q"-option?


  
  std::cout << "I am here" << std::endl;
  this->grint = new TGraphErrors(this->histo_bins);
  float k = pow(this->fitMax/this->fitMin, 1./(this->histo_bins -1));
  
  for (int i=0; i<this->histo_bins; i++) {
  
      grint->SetPoint(i, this->fitMin*pow(k,i),  0);
  }
  /*Compute the confidence intervals at the x points of the created graph*/
  (TVirtualFitter::GetFitter())->GetConfidenceIntervals(grint,0.68);
  
  
  this->N_dof = f_fit->GetNDF();
  set_chi2(r->Chi2());
  std::cout << "The Fit's chi2 value is: " << r->Chi2() << std::endl;
  std::cout << "The Fit's no of deg of freedom: " << f_fit->GetNDF() << std::endl;

  r->Print();
  // TMatrixDSym cov = r->GetCovarianceMatrix();


  


  for (int i=0; i<NTOYS; i++){
    this->f_fit_err[i]=this->getFitErr();
  }
  
  
  //  this->h_fit = new TH1D("h_fit","",this->histo_bins,this->fitMin,this->fitMax);
  //  int nbins=this->histo_bins*this->histMaxFrac;  
  int nbins=this->histo_bins; 

  


  this->h_fit = new TH1D("h_fit","",nbins,this->fitMin,this->fitMax);
  this->h_fit_lo = new TH1D("h_fit_lo","",nbins,this->fitMin,this->fitMax);
  this->h_fit_hi = new TH1D("h_fit_hi","",nbins,this->fitMin,this->fitMax);

  

  double *x=new double[nbins]; double *y=new double[nbins];
  double *ey_lo=new double[nbins]; double *ey_hi=new double[nbins];

  //autoCorr: cut-off and smoothing
  if ( this->autoCorr && this->histMaxFrac>1 ){
    for (int i=1; i<=nbins; i++){
      double xv=h_fit->GetBinCenter(i);
      if ( f_fit->Eval( xv ) <= 0 ){
	std::cout << "Auto-correcting negative value at " << xv << std::endl;
	this->histMaxFrac=xv/this->fitMax*0.8;
	this->smoothFrac=this->histMaxFrac*0.8;
	this->smoothMode="spline3";
	break;
      }
    }
  }

  //info used for spline
  const int np=4;
  double xx[np]={0}; xx[0]=-1;
  double yy[np]={0};
  TSpline3 *spline3;

  //create spline object if set
  if (this->smoothMode=="spline3" && this->smoothFrac>0){
    for (int i=1; i<=nbins; i++){
      double xv=h_fit->GetBinCenter(i);

      if( xv>this->fitMax*this->smoothFrac && xv <= this->fitMax*this->histMaxFrac ){
	if ( xx[0]<0 ){
	  xx[0]=h_fit->GetBinCenter(i-2); yy[0]=f_fit->Eval( xx[0] );
	  xx[1]=xv; yy[1]=f_fit->Eval( xv );
	}
	xx[np-2]=xv; yy[np-2]=f_fit->Eval( xv );
	xx[np-1]=h_fit->GetBinCenter(i+2); yy[np-1]=yy[np-2];
      }

    }
    spline3=new TSpline3("sp3",xx,yy,np);
  }

  //  for (int i=1; i<=this->histo_bins; i++){
  float smooth_term=0;
  int flatten_from=-1;
  double nflattened_bins=-1; //(1-this->histMaxFrac)*nbins;
  
  
  
  for (int i=1; i<=nbins; i++){

    // std::cout << "error y-axis lower: " << ey_lo[i-1] << std::endl;
    
    double xv=h_fit->GetBinCenter(i);
    double spline_val=-1;
    //to just continue after a certain value:
    if ( xv > this->fitMax*this->histMaxFrac ){
      // std::cout << "flattening...." << std::endl;
      if (flatten_from<0){
        flatten_from=i; //bin after which flattening starts
        nflattened_bins=nbins-i+1;
      }
      double val=this->h_fit->GetBinContent(i-1);
      this->h_fit->SetBinContent( i , val );
      if (nflattened_bins <= 0) std::cout << "Warning: nflattend_bins in CustomFit.cc is zero or negative!" << std::endl;
      double infl=( (i-flatten_from)/nflattened_bins ) * (this->maxFracErrorFactor-1); //total err at end will be (factor) times the value at beginning of flattening
      x[i-1]=xv;
      y[i-1]=y[flatten_from-2];
     
      // infl = 0.;// set inflation to zero

      ey_lo[i-1]=ey_lo[flatten_from-2]*(1+infl);   ey_hi[i-1]=ey_hi[flatten_from-2]*(1+infl);
      this->h_fit->SetBinError( i , this->h_fit->GetBinError(i-1) );
      this->h_fit_lo->SetBinContent( i , val-ey_lo[i-1] );
      this->h_fit_hi->SetBinContent( i , val+ey_hi[i-1] );
      // std::cout << "error y-axis lower: " << ey_lo[i-1] << std::endl << "------------------------" << std::endl;
      continue;
    } 
    else if( this->smoothFrac>0 && xv>this->fitMax*this->smoothFrac ){
      // std::cout << "smoothing...." << std::endl;

      if( this->smoothMode=="simple" ){
        float a=this->fitMax*this->smoothFrac;
        float b=this->fitMax*this->histMaxFrac;

        const float s_s=f_fit->Eval( b ) - f_fit->Eval( a );
        float s_d=fabs( (xv-a)/(b-a) -0.5 ) -0.5;
        float sign_sd=(s_d > 0) - (s_d < 0);
        
        smooth_term=-s_s/this->smoothParam*pow(fabs(s_d),this->smoothExp)*sign_sd;
      } 
      else if ( this->smoothMode=="spline3" ){
	      spline_val=spline3->Eval( xv );
      }
    }
    // std::cout << "error y-axis lower: " << ey_lo[i-1] << std::endl;

    double val=f_fit->Eval( xv ) + smooth_term;
    // std::cout << "error y-axis lower: " << ey_lo[i-1] << std::endl;
    if ( spline_val>0 ){
      val=spline_val;
    }
    // std::cout << "error y-axis lower: " << ey_lo[i-1] << std::endl;
    this->h_fit->SetBinContent( i , val );
    // std::cout << "error y-axis lower: " << ey_lo[i-1] << std::endl;
    double err = this->err_scale*this->std_dev( this->f_fit_err , NTOYS , xv , ey_lo[i-1], ey_hi[i-1], this->err_cl );
    //    double err = this->err_scale*this->std_dev( this->f_fit_err , NTOYS , xv , ey_lo[i-1], ey_hi[i-1], 1 ); //CL - 16% / 84% value
    //double err = this->err_scale*this->std_dev( this->f_fit_err , NTOYS , xv , ey_lo[i-1], ey_hi[i-1]); //std dev
    // std::cout << "error y-axis lower: " << ey_lo[i-1] << std::endl << "------------------------" << std::endl;
    ey_lo[i-1]*=this->err_scale;
    ey_hi[i-1]*=this->err_scale;
    x[i-1]=xv;
    y[i-1]=val;
    if ( err>val ) err=val;
    this->h_fit->SetBinError( i , err );
    this->h_fit_lo->SetBinContent( i , val-ey_lo[i-1] );
    this->h_fit_hi->SetBinContent( i , val+ey_hi[i-1] );


  } //end loop over x bins

  /*
  if (this->smoothMode=="spline3"){
    TCanvas *tc=new TCanvas();
    spline3->Draw();
    gPad->SaveAs("x.png");
  }
  */
  

  this->g_fit = new TGraphAsymmErrors( nbins , x , y , 0 , 0 , ey_lo , ey_hi );
  
}

TF1* CustomFit::getFitErr() {
  TF1* f;

  TGraphAsymmErrors *g_toys = this->fluctuateGraph();
  
  f = new TF1("this->f_fit_err",this->errFunc,fitMin,fitMax);
  int fit_status = g_toys->Fit(f,"NQ"); // “Q” Quiet mode (minimum printing)
                                        // “N” Do not store the graphics function, do not draw
  if (fit_status != 0) {
    std::cout << "Fit Error! exiting FF production" << std::endl;
    exit(0);
  }
  
  return f;
  //     The fitStatus is 0 if the fit is OK (i.e no error occurred).
  //     The value of the fit status code is negative in case of an error not connected with the
  //     minimization procedure, for example  when a wrong function is used.
  //     Otherwise the return value is the one returned from the minimization procedure.
  //     When TMinuit (default case) or Minuit2 are used as minimizer the status returned is :
  //     fitStatus =  migradResult + 10*minosResult + 100*hesseResult + 1000*improveResult.
  //     TMinuit will return 0 (for migrad, minos, hesse or improve) in case of success and 4 in
  //     case of error (see the documentation of TMinuit::mnexcm). So for example, for an error
  //     only in Minos but not in Migrad a fitStatus of 40 will be returned.
  //     Minuit2 will return also 0 in case of success and different values in migrad minos or
  //     hesse depending on the error. See in this case the documentation of
  //     Minuit2Minimizer::Minimize for the migradResult, Minuit2Minimizer::GetMinosError for the
  //     minosResult and Minuit2Minimizer::Hesse for the hesseResult.
  //     If other minimizers are used see their specific documentation for the status code returned.
  //     For example in the case of Fumili, for the status returned see TFumili::Minimize.
}

TGraphAsymmErrors* CustomFit::fluctuateGraph(){
  TGraphAsymmErrors *g = (TGraphAsymmErrors*)this->g_fit_input->Clone((TString)this->g_fit_input->GetName()+"_toy");

  Int_t nbins = g->GetN();

  double x,y;
  double el,eh,err;
  for (int ib=0; ib<nbins; ib++){
    g->GetPoint(ib,x,y);
    el=g->GetErrorYlow(ib);
    eh=g->GetErrorYhigh(ib);
    err=(el+eh)/2.;
    double newval = this->rand.Gaus(y,err);
    g->SetPoint(ib,x,newval);
  }
  return g;
}


TGraphAsymmErrors* CustomFit::makeFitGraph(TH1D* h_in){
  /*
  This function takes the histogram h_in and return a TGraph with asymmetric errors corresponding
  in y-direction to the bin errors of the histogram. The error in x-direction is set to zero. 
  */
  if (this->fitFromBin < 0){
    std::cout << "ERROR: fitFromBin has not been set!" << std::endl;
    return 0;
  }

  TGraphAsymmErrors* g;
  int nbins=bin_centers.size();  

  double *x=new double[nbins];
  double *y=new double[nbins];
  double *ey_u=new double[nbins];
  double *ey_d=new double[nbins];
  
  for (int i=0; i<nbins; i++){
    x[i]=bin_centers.at(i);
    y[i]=h_in->GetBinContent( this->fitFromBin+i );
    if (y[i]<=0 || i == nbins-1) { //exclude the last bin from the fit (it is the overflow bin with some weird behavior)
      ey_u[i]=0.;
      ey_d[i]=0.;
    }
    else {
      ey_u[i]=h_in->GetBinErrorUp( this->fitFromBin+i );
      ey_d[i]=h_in->GetBinErrorLow( this->fitFromBin+i );
    }

  }

  g=new TGraphAsymmErrors( bin_centers.size() , x , y , 0 , 0 , ey_d , ey_u );

  return g;
}

//standard deviation
double CustomFit::std_dev( const std::vector<double> v ){
  unsigned size=v.size();

  double mean=0;
  for (unsigned i=0; i<size; i++) mean+=v.at(i)/size;

  double std_dev=0;
  for (unsigned i=0; i<size; i++){
    double diff = v.at(i) - mean;
    std_dev+=diff*diff;
  }
  std_dev/= (size-1);
  std_dev=sqrt(std_dev);
 
  return std_dev;
}

//instead of calculating std dev, return the 16% / 84% quantile
double CustomFit::std_dev( std::vector<double> v, double& err_lo, double& err_hi , double central_value){
  std::sort(v.begin(),v.end());
  int i_lo=(int)(0.16*v.size());
  int i_hi=(int)(0.84*v.size());
  float val_lo=v.at(i_lo);
  float val_hi=v.at(i_hi);

  err_lo=central_value-val_lo;
  err_hi=val_hi-central_value;

 if (err_lo<err_hi/10.) err_lo=err_hi/10.;
 if (err_hi<err_lo/10.) err_hi=err_lo/10.;

  std::cout << "DEBUG : std_dev CL " << i_lo << " " << i_hi << " " << val_lo << " " << val_hi << " " << err_lo << " " << err_hi << std::endl;
  return fabs(val_lo-val_hi)/2; //symm. error
}

//double CustomFit::std_dev( TF1* f[] , const unsigned fsize ,  const double val , const double binc ){
double CustomFit::std_dev( TF1* f[] , const unsigned fsize ,  const double val , double& err_lo, double& err_hi, const int cl){
  std::vector<double> v;
  for (unsigned i=0; i<fsize; i++){
    double y=f[i]->Eval(val);
    //    if ( !cl && y<0 ) y=0;
    if ( y<0 ) y=0;
    //    if (y>2*binc) y=2*binc;
    v.push_back( y  );
  }

  double ret;
  // std::cout << "cl: " << cl << std::endl;
  if ( cl ) {
    ret=this->std_dev( v , err_lo , err_hi , this->f_fit->Eval(val) );
  }
  else{ ret=this->std_dev( v ); err_lo=ret; err_hi=ret; }

  // std::cout << "ret: " << ret << std::endl;
  return ret;
}


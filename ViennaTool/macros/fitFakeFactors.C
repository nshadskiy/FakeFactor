#include "TFile.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TLine.h"
#include "ViennaTool/interface/CustomFit.h"
#include "ViennaTool/interface/GlobalClass.h"

#include "sstream"
#include <iostream>
using namespace std;


CustomFit SetCustomFit(CustomFit cf, Int_t mode_i, Int_t idm, Int_t ijet) {

  if (CHAN == kMU && mode_i & _W_JETS && ijet == 0) {
    cf.set_fitFunc( "pol1(0)" );
    if( idm == 1) cf.set_fitFunc( "pol1(0)" );
    cf.set_histMaxFrac( 80.0/500.0 );
    cf.set_smoothFrac(60.0/500.0);
    if( idm == 1 && mode_i ){ cf.set_histMaxFrac( 80.0/500.0 ); cf.set_smoothFrac(60.0/500.0);}
    cf.set_err_scale( 1.0 );
    cf.set_err_cl( 0 );
    cf.set_smoothMode("spline3");              
  }
  else if (CHAN == kMU && mode_i & _W_JETS) {
    cf.set_fitFunc( "pol1(0)" );
    if( idm == 1) cf.set_fitFunc( "pol1(0)" );
    cf.set_err_scale( 1.0 );
    cf.set_err_cl( 0 );
    cf.set_histMaxFrac( 100.0/500.0 );
    cf.set_smoothFrac(60.0/500.0);
    cf.set_smoothMode("spline3");              
  }
  else if (CHAN == kMU && mode_i & _QCD && mode_i & _AI && ijet == 1) {
    cf.set_fitFunc( "pol1(0)" );
    cf.set_err_scale( 1.0 );
    cf.set_err_cl( 0 );
    cf.set_histMaxFrac( 80.0/500.0 );
    cf.set_smoothFrac(60.0/500.0);
    cf.set_smoothMode("spline3");              
  }
  else if (CHAN == kMU && mode_i & _QCD && mode_i & _AI && ijet == 0) {
    cf.set_fitFunc( "pol2(0)" );
    cf.set_err_scale( 1.0 );
    cf.set_err_cl( 0 );
    cf.set_histMaxFrac( 80./500.0 );
    cf.set_smoothFrac( 60./500.0);
    cf.set_smoothMode("spline3");              
  }          
  else if (CHAN == kMU && mode_i & _QCD) {
    cf.set_fitFunc( "pol1(0)" );
    if( ijet == 0 && idm == 0) cf.set_fitFunc( "pol1(0)" );
    cf.set_err_scale( 1.0 );
    cf.set_err_cl( 0 );
    if (idm == 0) cf.set_histMaxFrac( 80.0/500.0 );
    else  cf.set_histMaxFrac( 80.0/500.0 );
    cf.set_smoothFrac(60.0/500.0);
    cf.set_smoothMode("spline3");
  }
  else if (CHAN == kMU && mode_i & _TT) {
    cf.set_fitFunc( "pol1(0)" );
    if( idm == 1) cf.set_fitFunc( "pol1(0)" );
    cf.set_err_scale( 1.0 );
    cf.set_err_cl( 0 );
    if (idm == 0) cf.set_histMaxFrac( 200.0/500.0 );
    else cf.set_histMaxFrac( 200.0/500.0 );
    cf.set_smoothFrac(120.0/500.0);
    cf.set_smoothMode("spline3");
  }
  ////////////////////////////////////////////////////  
  // settings for the etau channel
  ////////////////////////////////////////////////////  
  else if( CHAN==kEL && (mode_i & _QCD) ) { // QCD FFs
    cf.set_fitFunc( "pol1(0)" );
    cf.set_err_scale( 1.0 );
    cf.set_histMaxFrac( 80.0/500.0 );  
    cf.set_smoothFrac(60.0/500.0);
    cf.set_err_cl( 0 ); 
    cf.set_smoothMode("spline3");
    // cf.set_Ndof(2);
  }
  else if( CHAN==kEL && mode_i & _TT ){
    cf.set_fitFunc( "pol1(0)" );
    cf.set_err_scale( 1.0 );
    cf.set_err_cl( 0 );
    cf.set_histMaxFrac( 200.0/500.0 );
    cf.set_smoothFrac(120.0/500.0);
    cf.set_smoothMode("spline3");              
  }
  else if( CHAN==kEL && mode_i & _W_JETS ){
    cf.set_fitFunc( "pol1(0)" );
    cf.set_err_scale( 1.0 );
    cf.set_err_cl( 0 );
    cf.set_histMaxFrac( 80.0/500.0 );
    cf.set_smoothFrac(60.0/500.0);
    cf.set_smoothMode("spline3");              
  }
  //////////////////////////////////////////////
  else if( CHAN==kTAU ){ //use default p0 for 1p0j, only //THIS IS USED FOR "TIGHT WP"  #&& !(ijet == 0 && idm == 0) 
    //	  else if( CHAN==kTAU && ijet == 1 ){ //use default p0 for 1p1j/3p1j //THIS IS USED FOR "VERY TIGHT WP"
    cf.set_fitFunc( "pol3(0)" );
    cf.set_err_scale( 3.0 );
    
    if(mode_i & _AI) cf.set_histMaxFrac( 80.0/500.0 ); 
    else{
      if( ijet == 0) cf.set_histMaxFrac( 80.0/500.0 ); 
      else cf.set_histMaxFrac( 80.0/500.0 ); 
    } 
    if( idm == 1 ) cf.set_histMaxFrac( 80.0/500.0 ); 
    if( idm == 1 && ijet == 0) cf.set_histMaxFrac( 80.0/500.0 ); 
    cf.set_smoothFrac(60.0/500.0);
      
    cf.set_smoothMode("spline3");              
  }
  else if( false ){ //use default p0 for 3p0j, but inflate errors! //THIS IS USED FOR "TIGHT WP"
    //	  else if( CHAN==kTAU && ijet == 0 && idm==1){ //use default p0 for 3p0j, but inflate errors! //THIS IS USED FOR "VERY TIGHT WP"
    cf.set_fitFunc( "pol1(0)" );
    cf.set_err_scale( 9.0 );
    cf.set_err_cl( 0 );
  }
  else{
    //current default
    cf.set_fitFunc( "pol1(0)" );
    cf.set_err_scale( 1.0 );
    cf.set_err_cl( 0 );
    
  }
  return cf;

}


void fitFakeFactors(){

  std::cout << std::endl << "*******************************************************" << std::endl;
  std::cout << "*Fitting pT bins of fake factors                      *" << std::endl;
  std::cout << "*******************************************************" << std::endl << std::endl;

  
  
  TString pi=path_img_data;       
  TString p=path_ff_data;       
  TString m_preselection_data=preselection_data;        
  TString m_SR_data=SR_data;        
  TString m_label="data"; 
  

 

  vector<Int_t> modes; modes.push_back(_QCD); modes.push_back(_QCD|_AI); if(CHAN!=kTAU){modes.push_back(_W_JETS); modes.push_back(_W_JETS); modes.push_back(_TT);}
  vector<TString> fake_histos; fake_histos.push_back(p+FF_corr_QCD_MCsum_noGen); fake_histos.push_back(p+FF_corr_QCD_MCsum_noGen_AI); if(CHAN!=kTAU){fake_histos.push_back(p+FF_corr_Wjets_MCsum_noGen);  fake_histos.push_back(p+FF_corr_Wjets_MC_noGen); fake_histos.push_back(p+FF_TT_J_only_SR);}
  vector<Int_t> dm_bins; dm_bins.push_back(N_t_QCD); dm_bins.push_back(N_t_QCD); if(CHAN!=kTAU){dm_bins.push_back(N_t_Wjets); dm_bins.push_back(N_t_Wjets); dm_bins.push_back(N_t_TT);}
  vector<Int_t> jet_bins; jet_bins.push_back(N_j_QCD); jet_bins.push_back(N_j_QCD); if(CHAN!=kTAU){jet_bins.push_back(N_j_Wjets); jet_bins.push_back(N_j_Wjets); jet_bins.push_back(N_j_TT_SR);}
  vector<Int_t> pt_bins; pt_bins.push_back(N_p_QCD); pt_bins.push_back(N_p_QCD_AI); if(CHAN!=kTAU){pt_bins.push_back(N_p_Wjets); pt_bins.push_back(N_p_Wjets); pt_bins.push_back(N_p_TT_SR);}

  for(Int_t imode=0;imode<modes.size();imode++){ // loop over modes ~ i.e. different background processes
    
    TString ff_fitted_name = fake_histos.at(imode); 
    ff_fitted_name.ReplaceAll(".root","_fitted.root");
    TFile ff_fitted(ff_fitted_name,"RECREATE");
    std::cout << "Creating " << ff_fitted_name << std::endl;
    for (Int_t i_uncmode=0; i_uncmode<3; i_uncmode++) {
    for(Int_t idm=0; idm<dm_bins.at(imode); idm++){ // loop over decay modes 
      for(Int_t ijet=0; ijet<jet_bins.at(imode); ijet++){ // loop over jet categories
      
        CustomFit cf;
        TString histname = "c_t";
        if(i_uncmode==1) {
          histname = "c_t_mcup";
        }
        else if(i_uncmode==2) {
          histname = "c_t_mcdown";
        }
        std::cout << "i_uncmode " << i_uncmode << std::endl;
        std::cout << "histname " << histname << std::endl;

        int ret = cf.setInputHisto( fake_histos.at(imode) , histname );
        if ( ret != 0 ) return; // error appeared
        TH1D *h = cf.returnInputHisto(); // h is the histogram of the FF measurement in the different jet categories
        
        const int nbins = pt_bins.at(imode); // number of tau pt bins
        double a_bins[nbins] = {}; // filling a_bins with the pt boundary values which is bkg process dependent
        if(modes.at(imode) & _QCD && !(modes.at(imode) & _AI) ) for(int ibin=0; ibin<nbins; ibin++){a_bins[ibin]=Pt_cuts_QCD[ibin];}
        else if(modes.at(imode) & _QCD && (modes.at(imode) & _AI) ) for(int ibin=0; ibin<nbins; ibin++){a_bins[ibin]=Pt_cuts_QCD_AI[ibin];}
        else if(modes.at(imode) & _W_JETS) for(int ibin=0; ibin<nbins; ibin++){a_bins[ibin]=Pt_cuts_Wjets[ibin];}
        else if(modes.at(imode) & _TT) for(int ibin=0; ibin<nbins; ibin++){a_bins[ibin]=Pt_cuts_TT_SR[ibin];}
        
        cf = SetCustomFit(cf, modes.at(imode), idm, ijet); // settings for the fit are set
 
        Int_t cat = idm+dm_bins.at(imode)*ijet; // category = DecayMode + N_decayModes * JetCategoryBin

        std::cout << "idm: " << idm << std::endl;
        std::cout << "dm_bins.at(imode): " << dm_bins.at(imode) << std::endl;
        std::cout << "ijet: " << ijet << std::endl;
        std::cout << "cat: " << cat << std::endl;
        std::cout << "no of pt bins: " << nbins << std::endl;
        

        cf.set_fitMin( fitMin ); //defined in Settings.h channel denpedent
        cf.set_fitMax( fitMax ); //defined in Settings.h 
        
        cf.set_histo_bins( fitBins*2 ); //this is only done to get nicer plots -> reverted before saving the FFs

        cf.set_fitFromBin( 1+cat*nbins );
        cf.set_bin_centers( fake_histos.at(imode) , "bins_weighted", nbins ); //Fill the vector this->bin_centers of CostumFit (cf) with the bin center values 

        cf.fitHisto();

        TGraphAsymmErrors *g_fit_input=cf.returnFitInputGraph(); //the input to the fit: data points in the range given
        TF1 *f_fit=cf.returnFitForm();                //the fit result (function)
        std::cout << "TF1 printout " << std::endl;
        f_fit->Print();
        std::cout << f_fit->GetParameter(0) << std::endl;
        std::cout << f_fit->GetParameter(1) << std::endl;
        std::cout << f_fit->GetParError(0) << std::endl;
        std::cout << f_fit->GetParError(1) << std::endl;
        std::cout << "TF1 printout done " << std::endl;
        TGraphAsymmErrors *g_fit=cf.returnFitGraph();              //the fit result binned (histo)
        TGraphAsymmErrors *g_fit2=new TGraphAsymmErrors( *g_fit );

        double ymax = 0.5; 
        double ymin = 0.001;
        
        for(int i=0; i<g_fit->GetN(); i++) {
          Double_t x; Double_t y;
          g_fit->GetPoint(i,x,y);
          if( y-g_fit->GetErrorYlow(i) <=0.01) g_fit->SetPointEYlow( i,y-0.01 );
          if(y+g_fit->GetErrorYhigh(i)>=ymax-0.01) {
            g_fit->SetPointEYhigh( i,ymax-0.01-y );
          }
        }

        for( int i=0; i<g_fit_input->GetN()-1; i++) {
          Double_t x; Double_t y;
          g_fit_input->GetPoint( i,x,y );
          g_fit_input->SetPointEXlow ( i, abs(a_bins[i]-x) );
          g_fit_input->SetPointEXhigh( i, abs(x-a_bins[i+1]) );
          
        }
        

        TCanvas *c2=new TCanvas("new","FFfit",800,800);
        c2->cd();
        c2->SetLogx();
        gStyle->SetOptStat(0);
        gPad->SetBottomMargin(0.15);
        gPad->SetLeftMargin(0.15);
        
        g_fit->SetTitle("");
        g_fit->Draw(); // error band
        
        
        
        
        g_fit->GetXaxis()->SetRangeUser(fitMin-0.1,fitMax+7);
        g_fit->GetXaxis()->SetTitle("p_{T}(#tau_{h}) (GeV)");
        g_fit->GetXaxis()->SetTitleSize(0.06);
        g_fit->GetXaxis()->SetTitleFont(42);
        g_fit->GetXaxis()->SetTitleOffset(1.06);
        g_fit->GetXaxis()->SetLabelSize(0.04);
        
        g_fit->GetYaxis()->SetRangeUser(ymin,ymax);
        if(modes.at(imode) & _QCD) g_fit->GetYaxis()->SetTitle("FF_{QCD}");
        else if(modes.at(imode) & _W_JETS) g_fit->GetYaxis()->SetTitle("FF_{W+jets}");
        else if(modes.at(imode) & _TT) g_fit->GetYaxis()->SetTitle("FF_{t#bar{t}}");
        g_fit->GetYaxis()->SetTitleFont(42);
        g_fit->GetYaxis()->SetTitleSize(0.06);
        g_fit->GetYaxis()->SetTitleOffset(1.16);
        g_fit->GetYaxis()->SetLabelSize(0.04);
        g_fit->GetXaxis()->SetNdivisions(50005);
        g_fit->GetXaxis()->SetMoreLogLabels();
        g_fit->GetXaxis()->SetNoExponent();
        
        
        f_fit->SetLineColor(kBlack);
        f_fit->SetLineWidth(3);

        g_fit->SetLineWidth(5.);
        g_fit->SetLineColor(kOrange-2);

        gStyle->SetEndErrorSize(0);
        // g_fit->Draw("Ez same");
        g_fit2->SetLineColor(kBlack);
        g_fit2->SetLineWidth(3);
        g_fit2->Draw("CPX same"); // nominal line 
        /*
        "C"	A smooth Curve is drawn
        "P"	The current marker is plotted at each point
        "X+"	The X-axis is drawn on the top side of the plot
        */

        TGraphErrors* grint = cf.returnConfInterval();

        grint->SetLineColor(kRed);
        // std::cout << grint << std::endl;
        grint->SetLineColorAlpha(kRed, 0.1);
        grint->SetLineWidth(2.);
        grint->Draw("E0 same");
        // TGraphErrors* grint_line = cf.returnConfInterval();
        // grint_line->SetLineColor(kRed);
        // grint_line->SetMarkerColor(kRed);
        // grint_line->SetMarkerSize(2.);
        // grint_line->SetLineColorAlpha(kRed, 0.);
        // grint_line->SetLineWidth(0.);
        // grint_line->Draw("same");

        TGraph* legendGraph2 = new TGraph();
        legendGraph2->SetLineColor(kRed);
        legendGraph2->SetLineWidth(4);
        legendGraph2->SetLineColorAlpha(kRed, 0.05);
        legendGraph2->SetFillColor(kRed);

        g_fit_input->SetLineWidth(2.);
        g_fit_input->SetMarkerSize(1.6);
        g_fit_input->SetMarkerStyle(20);
        g_fit_input->Draw("E P SAME"); // "P"	Draw current marker at each bin except empty bins.

        TGraph* legendGraph = new TGraph();
        legendGraph->SetLineColor(kBlack);
        legendGraph->SetLineWidth(4);
        legendGraph->SetFillColor(kOrange-2);
        
        
        TLegend* leg = new TLegend(0.60,0.66,0.9,0.895);
        leg->SetShadowColor(10);
        leg->SetLineColor(10);
        leg->SetTextFont(42);
        leg->SetTextSize(0.027);
        leg->AddEntry(g_fit_input,"Measured","EP");
        TString fit_text = "#splitline{Analytic fit (68\% CL)}";
        fit_text.Append("{#chi^{2} / N_{dof} = ").Append(std::to_string(cf.get_chi2()).substr(0, std::to_string(cf.get_chi2()).find(".") + 3)).Append(" / ").Append(std::to_string(cf.get_Ndof())).Append("}");

        // TString ss = std::to_string(luminosity).substr(0, std::to_string(luminosity).find(".") + 3).append(" fb^{-1} (").append(ERA).append(", 13 TeV)");

        TString customFit_text = "#splitline{Resampling method}{high-p_{T}(#tau) flattening}";
        leg->AddEntry(legendGraph, customFit_text, "lf");
        leg->AddEntry(legendGraph2, fit_text, "lf");
        leg->Draw();
        
        gPad->RedrawAxis();
        gPad->Update();
        TLine line;
        line.DrawLine(fitMax+7, ymin, fitMax+7, ymax);
        
        TLatex ChannelJetcat;
        ChannelJetcat.SetTextSize(0.038);
        ChannelJetcat.SetNDC();
        ChannelJetcat.SetTextFont(42);
        
        // TString jetMode=""; { if(modes.at(imode) & _TT ) jetMode+="#geq 0jet"; else if(ijet==0) jetMode+="0jet"; else if(ijet==1) jetMode+="1jet"; else jetMode+="#geq2jet";}
        TString jetMode=""; { if(ijet==0) jetMode+="0jet"; else if(ijet==1) jetMode+="1jet"; else jetMode+="#geq2jet";}
        TString channel=""; { if(CHAN == kMU) channel+="#mu^{}#tau_{h}"; else if(CHAN == kEL) channel+="e#tau_{h}"; else channel+="#tau_{h}#tau_{h}";}
        
        ChannelJetcat.DrawLatex(0.16,0.915,"channel: "+channel+", jet cat: "+jetMode);
        
        
        TLatex cms1 = TLatex( 0.19, 0.838, "CMS" );
        TString preliminary; 
        TString paper; 
        Double_t yvalue = 0.78;          
        
        if( modes.at(imode) & _TT ) {paper="#splitline{Simulation}{Preliminary}"; yvalue=0.765;}
        else paper="Preliminary";
        if( modes.at(imode) & _TT ) {preliminary="#splitline{Simulation}{Preliminary}"; yvalue=0.765;}
        else preliminary="Preliminary";
        TLatex cms2 = TLatex( 0.19, yvalue, paper );
        TLatex cms3 = TLatex( 0.19, yvalue, preliminary );
        
        cms1.SetNDC();
        cms1.SetTextSize(0.06);
        cms1.SetTextFont(62);
        
        cms2.SetNDC();
        cms2.SetTextFont(12);
        cms2.SetTextSize(0.05);
        cms2.SetTextFont(52);
        
        cms3.SetNDC();
        cms3.SetTextFont(12);
        cms3.SetTextSize(0.05);
        cms3.SetTextFont(52);
        

        TString ss = std::to_string(luminosity).substr(0, std::to_string(luminosity).find(".") + 3).append(" fb^{-1} (").append(ERA).append(", 13 TeV)");
        TLatex infoRight = TLatex( 0.595, 0.915, ss );
        infoRight.SetNDC();
        infoRight.SetTextFont(42);
        infoRight.SetTextSize(0.03);
        if( !(modes.at(imode) & _TT) ) {
          infoRight.Draw();
        }
 
        



        cms1.Draw();
        cms2.Draw();
        // cms3.Draw();
        
        
        TString ending=""; stringstream convert; stringstream f_convert;
        if(modes.at(imode) & _QCD) ending=ending+"QCD_"; if(modes.at(imode) & _W_JETS) ending=ending+"Wjets_"; if(modes.at(imode) & _TT) ending=ending+"TT_";
        if( modes.at(imode) & _QCD && ff_fitted_name.Contains("AI") ) ending += "AI_";
        if( modes.at(imode) & _W_JETS && ff_fitted_name.Contains("_MC_") ) ending += "MC_";
        if(i_uncmode==0) {
        convert << "dm" << idm << "_" << "njet" << ijet;
        f_convert << "f_dm" << idm << "_" << "njet" << ijet;
         }
        else if(i_uncmode==1) {
          convert << "dm" << idm << "_" << "njet" << ijet << "_mcup";
          f_convert << "f_dm" << idm << "_" << "njet" << ijet << "_mcup";   
          }
        else if(i_uncmode==2) {
          convert << "dm" << idm << "_" << "njet" << ijet << "_mcdown";
          f_convert << "f_dm" << idm << "_" << "njet" << ijet << "_mcdown";   
          }
        stringstream convertChannel;
        if(CHAN==kMU) convertChannel<<"_mt"; if(CHAN==kEL) convertChannel<<"_et"; if(CHAN==kTAU) convertChannel<<"_tt"; 
        ending=ending+convert.str()+convertChannel.str();
        gPad->RedrawAxis();

        if(ALLPLOTS) c2->SaveAs(pi+"ff_"+ending+".png");
        c2->SaveAs(pi+"ff_"+ending+".pdf");
        c2->SaveAs(pi+"ff_"+ending+".C");

        c2->cd();
        cf.set_fitFromBin( 1+cat*nbins );
        cf.set_fitMin( fitMin );
        cf.set_fitMax( fitMax );
        cf.set_histo_bins( fitBins );                     
        cf.set_bin_centers( fake_histos.at(imode) , "bins_weighted", nbins ); //fitFromBin  needs to be set BEFORE          
        cf.fitHisto();
        g_fit=cf.returnFitGraph();

        for(int i=0; i<g_fit->GetN(); i++){
          Double_t x; Double_t y;
          g_fit->GetPoint(i,x,y);
          if(y-g_fit->GetErrorYlow(i)<0) g_fit->SetPointEYlow( i,y );
          if(y+g_fit->GetErrorYhigh(i)>=1.) g_fit->SetPointEYhigh( i,0.99-y );

        }
        f_fit->SetName(f_convert.str().c_str());
        g_fit->SetName(convert.str().c_str());
        g_fit->GetYaxis()->SetRangeUser(0.,1.);
        // g_fit->GetXaxis()->SetRangeUser(fitMin-0.1,fitMax+7); //TODO
        
        gPad->RedrawAxis();
        
        ff_fitted.cd();
        g_fit->Write();
        f_fit->Write();
        delete g_fit_input,f_fit;
        delete c2;
      
      
      }
    }
    }
    ff_fitted.Close();
    // exit(0);
  }
  
}


#ifndef __CINT__
int main(int argc, char* argv[]) {
  fitFakeFactors();    
}
#endif

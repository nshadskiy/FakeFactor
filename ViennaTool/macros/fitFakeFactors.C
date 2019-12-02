#include "TFile.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TLine.h"
#include "ViennaTool/interface/CustomFit.h"
#include "ViennaTool/interface/GlobalClass.h"

#include "sstream"
#include <iostream>
using namespace std;

void fitFakeFactors(){

  std::cout << std::endl << "*******************************************************" << std::endl;
  std::cout << "*Fitting pT bins of fake factors                      *" << std::endl;
  std::cout << "*******************************************************" << std::endl << std::endl;

  
  TString p, pi;
  TString m_preselection_data;
  TString m_SR_data;
  TString m_label;
  if      ( DOMC  &&  DOQCD                 ){ pi=path_img_mc;         p=path_ff_mc;         m_preselection_data=preselection_MCsum;       m_SR_data=SR_MCsum;       m_label="sim";  }
  else if ( !DOMC                           ){ pi=path_img_data;       p=path_ff_data;       m_preselection_data=preselection_data;        m_SR_data=SR_data;        m_label="data"; }
  else if ( DOMC  && ( !DOQCD || CHAN!=kMU) ){ pi=path_img_mc_woQCD;   p=path_ff_mc_woQCD;   m_preselection_data=preselection_MCsum_woQCD; m_SR_data=SR_MCsum_woQCD; m_label="sim";  }

  TString pmc=path_ff_mc;             if ( ( !DOQCD && DOMC ) || CHAN!=kMU ) pmc=path_ff_mc_woQCD;
  TString psmc=preselection_MCsum;    if ( ( !DOQCD && DOMC ) || CHAN!=kMU ) psmc=preselection_MCsum_woQCD;

  vector<TString> tight_cats; tight_cats.push_back("c_t"); 
  
  // tight_cats.push_back("c_t_alt");
  vector<Int_t> modes; modes.push_back(_QCD); modes.push_back(_QCD|_AI); if(CHAN!=kTAU){modes.push_back(_W_JETS); modes.push_back(_W_JETS); modes.push_back(_TT);}
  vector<TString> fake_histos; fake_histos.push_back(p+FF_corr_QCD_MCsum_noGen); fake_histos.push_back(p+FF_corr_QCD_MCsum_noGen_AI); if(CHAN!=kTAU){fake_histos.push_back(p+FF_corr_Wjets_MCsum_noGen);  fake_histos.push_back(p+FF_corr_Wjets_MC_noGen); fake_histos.push_back(p+FF_TT_J_only_SR);}
  vector<Int_t> dm_bins; dm_bins.push_back(N_t_QCD); dm_bins.push_back(N_t_QCD); if(CHAN!=kTAU){dm_bins.push_back(N_t_Wjets); dm_bins.push_back(N_t_Wjets); dm_bins.push_back(N_t_TT);}
  vector<Int_t> jet_bins; jet_bins.push_back(N_j_QCD); jet_bins.push_back(N_j_QCD); if(CHAN!=kTAU){jet_bins.push_back(N_j_Wjets); jet_bins.push_back(N_j_Wjets); jet_bins.push_back(N_j_TT_SR);}
  vector<Int_t> pt_bins; pt_bins.push_back(N_p_QCD); pt_bins.push_back(N_p_QCD_AI); if(CHAN!=kTAU){pt_bins.push_back(N_p_Wjets); pt_bins.push_back(N_p_Wjets); pt_bins.push_back(N_p_TT_SR);}

  for(Int_t imode=0;imode<modes.size();imode++){
    std::cout << "Mode: "<<modes[imode]<<endl;
    TString ff_fitted_name = fake_histos.at(imode); ff_fitted_name.ReplaceAll(".root","_fitted.root");
    std::cout << ff_fitted_name << std::endl;
    TFile ff_fitted(ff_fitted_name,"RECREATE");
    std::cout << "Creating " << ff_fitted_name << std::endl;
    for(Int_t itight=0;itight<tight_cats.size();itight++){
      for(Int_t idm=0; idm<dm_bins.at(imode); idm++){
        for(Int_t ijet=0; ijet<jet_bins.at(imode); ijet++){
        
          CustomFit cf;
          
          int ret=cf.setInputHisto( fake_histos.at(imode) , tight_cats.at(itight) );
          if ( ret != 0 ) return;
          TH1D *h=cf.returnInputHisto();
                
          //w+jets
          const int nbins=pt_bins.at(imode);
          cout << "NBINS: " << nbins << endl;
          double a_bins[nbins] = {};
          if(modes.at(imode) & _QCD && !(modes.at(imode) & _AI) ) for(int ibin=0; ibin<nbins; ibin++){a_bins[ibin]=Pt_cuts_QCD[ibin];}
          if(modes.at(imode) & _QCD && (modes.at(imode) & _AI) ) for(int ibin=0; ibin<nbins; ibin++){a_bins[ibin]=Pt_cuts_QCD_AI[ibin];}
          if(modes.at(imode) & _W_JETS) for(int ibin=0; ibin<nbins; ibin++){a_bins[ibin]=Pt_cuts_Wjets[ibin];}
          if(modes.at(imode) & _TT) for(int ibin=0; ibin<nbins; ibin++){a_bins[ibin]=Pt_cuts_TT_SR[ibin];}
          
          
          /* if( CHAN==kMU && ( modes.at(imode) & _W_JETS && idm == 0 && ijet == 1 ) )
            {
	      cf.set_fitFunc( "pol1(0)" );
	      cf.set_err_scale( 1.2 );
            }
            
	 else */ 
          if (CHAN == kMU && modes.at(imode) & _W_JETS && ijet == 0) {
                  cf.set_fitFunc( "pol1(0)" );
                  if( idm == 1) cf.set_fitFunc( "pol1(0)" );
                  cf.set_histMaxFrac( 80.0/500.0 );
                  cf.set_smoothFrac(60.0/500.0);
                  if( idm == 1 && modes.at(imode) ){ cf.set_histMaxFrac( 80.0/500.0 ); cf.set_smoothFrac(60.0/500.0);}
                  cf.set_err_scale( 3.0 );
                  cf.set_err_cl( 0 );
                  cf.set_smoothMode("spline3");              
                  }
          else if (CHAN == kMU && modes.at(imode) & _W_JETS) {
                  cf.set_fitFunc( "pol1(0)" );
                  if( idm == 1) cf.set_fitFunc( "pol1(0)" );
                  cf.set_err_scale( 3.0 );
                  cf.set_err_cl( 0 );
                  cf.set_histMaxFrac( 100.0/500.0 );
                  cf.set_smoothFrac(60.0/500.0);
                  cf.set_smoothMode("spline3");              
                  }
          
          else if (CHAN == kMU && modes.at(imode) & _QCD && modes.at(imode) & _AI && ijet == 1) {
                  cf.set_fitFunc( "pol1(0)" );
                  cf.set_err_scale( 3.0 );
                  cf.set_err_cl( 0 );
                  cf.set_histMaxFrac( 80.0/500.0 );
                  cf.set_smoothFrac(60.0/500.0);
                  cf.set_smoothMode("spline3");              
                  }
          else if (CHAN == kMU && modes.at(imode) & _QCD && modes.at(imode) & _AI && ijet == 0) {
                  cf.set_fitFunc( "pol2(0)" );
                  cf.set_err_scale( 3.0 );
                  cf.set_err_cl( 0 );
                  cf.set_histMaxFrac( 80./500.0 );
                  cf.set_smoothFrac( 60./500.0);
                  cf.set_smoothMode("spline3");              
                  }          
          else if (CHAN == kMU && modes.at(imode) & _QCD) {
                cf.set_fitFunc( "pol1(0)" );
                if( ijet == 0 && idm == 0) cf.set_fitFunc( "pol1(0)" );
                  cf.set_err_scale( 3.0 );
                  cf.set_err_cl( 0 );
                  if (idm == 0) cf.set_histMaxFrac( 80.0/500.0 );
                  else  cf.set_histMaxFrac( 80.0/500.0 );
                  cf.set_smoothFrac(60.0/500.0);
                  cf.set_smoothMode("spline3");
                  }
          else if (CHAN == kMU && modes.at(imode) & _TT) {
                cf.set_fitFunc( "pol1(0)" );
                if( idm == 1) cf.set_fitFunc( "pol1(0)" );
                  cf.set_err_scale( 3.0 );
                  cf.set_err_cl( 0 );
                  if (idm == 0) cf.set_histMaxFrac( 200.0/500.0 );
                  else cf.set_histMaxFrac( 200.0/500.0 );
                  cf.set_smoothFrac(120.0/500.0);
                  cf.set_smoothMode("spline3");
                  }
        ////////////////////////////////////////////////////  
        else if( CHAN==kEL && (modes.at(imode) & _QCD) && modes.at(imode) & _AI  ) {
                if( ijet == 0 )cf.set_fitFunc( "pol1(0)" );
                else     	     cf.set_fitFunc( "pol1(0)" );
                cf.set_err_scale( 3.0 );
                if( ijet == 0 ) {cf.set_histMaxFrac( 80.0/500.0 );  cf.set_smoothFrac(60.0/500.0);}
                else            {cf.set_histMaxFrac( 80.0/500.0 );  cf.set_smoothFrac(60.0/500.0);}
                if( idm == 1 && ijet == 0){ cf.set_histMaxFrac( 80.0/500.0 ); cf.set_smoothFrac(60.0/500.0);}
                if( idm == 1 && ijet == 1){ cf.set_histMaxFrac( 80.0/500.0 ); cf.set_smoothFrac(60.0/500.0);}
                cf.set_err_cl( 0 );          
                cf.set_smoothMode("spline3");
            }              
            else if( CHAN==kEL && (modes.at(imode) & _QCD) ) {
                cf.set_fitFunc( "pol1(0)" );
                if( ijet == 0 && idm == 0) cf.set_fitFunc( "pol1(0)" );  
                cf.set_err_scale( 3.0 );
                cf.set_err_cl( 0 );         
                if( ijet == 0 ) {cf.set_histMaxFrac( 80.0/500.0 );  cf.set_smoothFrac(60.0/500.0);}
                else            {cf.set_histMaxFrac( 80.0/500.0 );  cf.set_smoothFrac(60.0/500.0);}
                if( ijet == 0 && idm == 0) cf.set_histMaxFrac( 80.0/500.0 );  cf.set_smoothFrac(60.0/500.0);
                cf.set_smoothMode("spline3");     
            }
          else if( CHAN==kEL && modes.at(imode) & _TT ){
              cf.set_fitFunc( "pol1(0)" );
              cf.set_err_scale( 3.0 );
              cf.set_err_cl( 0 );
                    cf.set_histMaxFrac( 200.0/500.0 );
                    cf.set_smoothFrac(120.0/500.0);
                    cf.set_smoothMode("spline3");              
                }
          else if( CHAN==kEL && modes.at(imode) & _W_JETS && modes.at(imode) & _AI ){
              cf.set_fitFunc( "pol1(0)" );
              cf.set_err_scale( 3.0 );
              cf.set_err_cl( 0 );
                    cf.set_histMaxFrac( 80.0/500.0 );
                    cf.set_smoothFrac(60.0/500.0);
                    cf.set_smoothMode("spline3");              
                }
          else if( CHAN==kEL && modes.at(imode) & _W_JETS && ijet == 0){
              cf.set_fitFunc( "pol1(0)" );  
              cf.set_err_scale( 3.0 );
              cf.set_err_cl( 0 );
                    cf.set_histMaxFrac( 80.0/500.0 );
                    cf.set_smoothFrac(60.0/500.0);
                    cf.set_smoothMode("spline3");              
                }
          else if( CHAN==kEL && modes.at(imode) & _W_JETS ){
              cf.set_fitFunc( "pol1(0)" );
              cf.set_err_scale( 3.0 );
              cf.set_err_cl( 0 );
                    cf.set_histMaxFrac( 80.0/500.0 );
                    cf.set_smoothFrac(60.0/500.0);
                    cf.set_smoothMode("spline3");              
                }
            //////////////////////////////////////////////
            else if( CHAN==kTAU ){ //use default p0 for 1p0j, only //THIS IS USED FOR "TIGHT WP"  #&& !(ijet == 0 && idm == 0) 
              //	  else if( CHAN==kTAU && ijet == 1 ){ //use default p0 for 1p1j/3p1j //THIS IS USED FOR "VERY TIGHT WP"
              cf.set_fitFunc( "pol1(0)" );
              cf.set_err_scale( 1.2 );
              // //change "cut-off" for alternative (otherwise take default)
              // if      (ijet == 0 && idm == 1) cf.set_histMaxFrac( 0.35 );
              // else if (ijet == 1 && idm == 1) cf.set_histMaxFrac( 0.35 );
              // if ( modes.at(imode) & _AI  ) 
              if(modes.at(imode) & _AI) cf.set_histMaxFrac( 80.0/500.0 ); 
              else{
                if( ijet == 0) cf.set_histMaxFrac( 80.0/500.0 ); 
                else cf.set_histMaxFrac( 80.0/500.0 ); 
              } 
              if( idm == 1 ) cf.set_histMaxFrac( 80.0/500.0 ); 
              if( idm == 1 && ijet == 0) cf.set_histMaxFrac( 80.0/500.0 ); 
              cf.set_smoothFrac(60.0/500.0);
              // else if ( ijet == 0) {cf.set_histMaxFrac( 0.26 );  cf.set_smoothFrac(0.2);}
              // else if ( ijet == 1) {cf.set_histMaxFrac( 0.2 );  cf.set_smoothFrac(0.18);}
              
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
                cf.set_err_scale( 3.0 );
                cf.set_err_cl( 0 );
                //alternative
                //	    cf.set_fitFunc( "pol1(0)" );
                //	    cf.set_err_scale( 1.2 );
              }

              Int_t cat=idm+dm_bins.at(imode)*ijet;
              cf.set_fitFromBin( 1+cat*nbins );
              cf.set_fitMin( fitMin );
              cf.set_fitMax( fitMax );
              cf.set_histo_bins( fitBins*10 ); //this is only done to get nicer plots -> reverted before saving the FFs
              
              std::vector<double> bins;
              cf.set_bin_centers( fake_histos.at(imode) , "bins_weighted", nbins ); //fitFromBin  needs to be set BEFORE
              
              cf.fitHisto();
              
              TGraphAsymmErrors *g_fit_input=cf.returnFitInputGraph(); //the input to the fit: data points in the range given
              TF1 *f_fit=cf.returnFitForm();                //the fit result (function)
              TGraphAsymmErrors *g_fit=cf.returnFitGraph();              //the fit result binned (histo)
              TGraphAsymmErrors *g_fit2=new TGraphAsymmErrors( *g_fit );

              double ymax = 0.7; double ymin = 0.001;
          //          if(CHAN==kTAU){ymax = 1.0; ymin = 0.301;}

              for(int i=0; i<g_fit->GetN(); i++){
                Double_t x; Double_t y;
                g_fit->GetPoint(i,x,y);
                if( y-g_fit->GetErrorYlow(i) <=0.01) g_fit->SetPointEYlow( i,y-0.01 );
                if(y+g_fit->GetErrorYhigh(i)>=ymax-0.01){
                  g_fit->SetPointEYhigh( i,ymax-0.01-y );
                }
              }

              for( int i=0; i<g_fit_input->GetN()-1; i++){
                Double_t x; Double_t y;
                g_fit_input->GetPoint( i,x,y );
                // cout << x << " " << y << endl;
                // cout << a_bins[i] << " " << a_bins[i+1] << endl;
                // cout << "errorbars x " << abs(x-a_bins[i+1]) << " " << abs(a_bins[i]-x) << endl;
                g_fit_input->SetPointEXlow ( i, abs(a_bins[i]-x) );
                g_fit_input->SetPointEXhigh( i, abs(x-a_bins[i+1]) );
                
              }

          TCanvas *c2=new TCanvas("new","FFfit",800,800);
          c2->cd();
          c2->SetLogx();
          gStyle->SetOptStat(0);
          gPad->SetBottomMargin(0.15);
          gPad->SetLeftMargin(0.15);
          //  h->Draw("E");     //to set the axis
          
          g_fit->GetYaxis()->SetRangeUser(ymin,ymax);
          g_fit->GetXaxis()->SetRangeUser(fitMin-0.1,fitMax+7);
          //  g_fit->SetMarkerStyle(21);
          g_fit->SetTitle("");
          g_fit->Draw();
          g_fit->GetXaxis()->SetTitle("p_{T}(tau) (GeV)");
          g_fit->GetXaxis()->SetTitleSize(0.06);
          g_fit->GetXaxis()->SetTitleFont(42);
          g_fit->GetXaxis()->SetTitleOffset(1.06);
          g_fit->GetXaxis()->SetLabelSize(0.04);
          if(modes.at(imode) & _QCD) g_fit->GetYaxis()->SetTitle("FF_{QCD}");
          if(modes.at(imode) & _W_JETS) g_fit->GetYaxis()->SetTitle("FF_{W+jets}");
          if(modes.at(imode) & _TT) g_fit->GetYaxis()->SetTitle("FF_{t#bar{t}}");
          g_fit->GetYaxis()->SetTitleFont(42);
          g_fit->GetYaxis()->SetTitleSize(0.06);
          g_fit->GetYaxis()->SetTitleOffset(1.06);
          g_fit->GetYaxis()->SetLabelSize(0.04);
          g_fit->GetXaxis()->SetNdivisions(50005);
          g_fit->GetXaxis()->SetMoreLogLabels();
          g_fit->GetXaxis()->SetNoExponent();
          
          
          f_fit->SetLineColor(kBlack);
          f_fit->SetLineWidth(3);
          g_fit->SetLineWidth(5.);
          g_fit->SetLineColor(kOrange-2);

          gStyle->SetEndErrorSize(0);
          g_fit->Draw("Ez same");
          g_fit2->SetLineColor(kBlack);
          g_fit2->SetLineWidth(3);
          g_fit2->Draw("XCP same");
          //f_fit->Draw("axis same");
          g_fit_input->SetLineWidth(2.);
          g_fit_input->SetMarkerSize(1.6);
          g_fit_input->SetMarkerStyle(20);
          g_fit_input->Draw("E P SAME");

          TGraph* legendGraph = new TGraph();
          legendGraph->SetLineColor(kBlack);
          legendGraph->SetLineWidth(4);
          legendGraph->SetFillColor(kOrange-2);
          
          
          TLegend* leg = new TLegend(0.62,0.76,0.9,0.895);
          leg->SetShadowColor(10);
          leg->SetLineColor(10);
          leg->SetTextFont(42);
          leg->SetTextSize(0.038);
          leg->AddEntry(g_fit_input,"Measured","EP");
          //leg->AddEntry(g_fit,"Best fit value","lf");
          leg->AddEntry(legendGraph,"Best fit value","lf");
          //leg->AddEntry(g_fit,"Best fit value","brNDC");
          leg->Draw();
          
          gPad->RedrawAxis();
          gPad->Update();
          TLine line;
          line.DrawLine(fitMax+7, ymin, fitMax+7, ymax);
          
          TLatex l,l1,l2;
          l.SetTextSize(0.048);l1.SetTextSize(0.038);l2.SetTextSize(0.048);
          l.SetNDC();l1.SetNDC();l2.SetNDC();
          l.SetTextFont(42);l1.SetTextFont(42);l2.SetTextFont(42);
          //l.SetTextFont(102);
          TString bkg=""; {if(modes.at(imode) & _QCD) bkg+="QCD"; else if(modes.at(imode) & _W_JETS) bkg+="W+jets"; else if(modes.at(imode) & _TT) bkg+="TT";} 
          TString jetMode=""; { if(modes.at(imode) & _TT ) jetMode+="#geq 0jet"; else if(ijet==0) jetMode+="0jet"; else jetMode+="#geq1jet";}
          TString channel=""; { if(CHAN == kMU) channel+="#mu^{}#tau_{h}"; else if(CHAN == kEL) channel+="e#tau_{h}"; else channel+="#tau_{h}#tau_{h}";}
          //{if(modes.at(imode) & _QCD) channel+=" QCD multijet"; else if(modes.at(imode) & _W_JETS) channel+=" W+jets"; else if(modes.at(imode) & _TT) channel+=" t#bar{t}";}
          //if(idm==0) l.DrawLatex(0.52,0.8,"FFs "+bkg);
          //else l.DrawLatex(0.52,0.8,"FFs "+bkg);
          if(idm==0) l1.DrawLatex(0.19,0.915,channel+" "+jetMode);
          else l1.DrawLatex(0.19,0.915,channel+" "+jetMode);
          //l2.DrawLatex(0.16,0.85,channel);

          TLatex cms1 = TLatex( 0.19, 0.838, "CMS" );
          TString preliminary; TString paper; Double_t yvalue = 0.78;          
          if( modes.at(imode) & _TT ) {paper="#splitline{Simulation}{Supplementary}"; yvalue=0.765;}
          else paper="Supplementary";
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
          
          TLatex infoRight = TLatex( 0.665, 0.915, "35.9 fb^{-1} (13 TeV)" );
          infoRight.SetNDC();
          infoRight.SetTextFont(42);
          infoRight.SetTextSize(0.03);

          cms1.Draw();
          //if( modes.at(imode) & _TT ) cms2.Draw();
          if( !(modes.at(imode) & _TT) ) infoRight.Draw();
          
          TString ending=""; stringstream convert;
          if(modes.at(imode) & _QCD) ending=ending+"QCD_"; if(modes.at(imode) & _W_JETS) ending=ending+"Wjets_"; if(modes.at(imode) & _TT) ending=ending+"TT_";
          if( modes.at(imode) & _QCD && ff_fitted_name.Contains("AI") ) ending += "AI_";
          if( modes.at(imode) & _W_JETS && ff_fitted_name.Contains("_MC_") ) ending += "MC_";
          convert << "dm" << idm << "_" << "njet" << ijet;
          if(itight==1) convert << "_alt";
          stringstream convertChannel;
          if(CHAN==kMU) convertChannel<<"_mt"; if(CHAN==kEL) convertChannel<<"_et"; if(CHAN==kTAU) convertChannel<<"_tt"; 
          ending=ending+convert.str()+convertChannel.str();
          gPad->RedrawAxis();

          cms2.Draw();
          //              cms3.Draw();
          if(ALLPLOTS) c2->SaveAs(pi+"ff_"+ending+".png");
          c2->SaveAs(pi+"ff_"+ending+".pdf");

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
          
          g_fit->SetName(convert.str().c_str());
          g_fit->GetYaxis()->SetRangeUser(0.,1.);
          g_fit->GetXaxis()->SetRangeUser(fitMin-0.1,fitMax+7); //TODO

          gPad->RedrawAxis();
          
          ff_fitted.cd();
          g_fit->Write();
          
          delete g_fit_input,f_fit;
          delete c2;
        
        
        }
      }
    }
    ff_fitted.Close();
  }
  
}


#ifndef __CINT__
int main(int argc, char* argv[]) {
  fitFakeFactors();    
}
#endif

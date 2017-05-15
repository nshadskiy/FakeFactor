#include "TFile.h"
#include "TH1D.h"
#include "TCanvas.h"
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

  vector<TString> tight_cats; tight_cats.push_back("c_t"); tight_cats.push_back("c_t_alt");
  vector<Int_t> modes; modes.push_back(_QCD); modes.push_back(_QCD|_AI); if(CHAN!=kTAU){modes.push_back(_W_JETS); modes.push_back(_W_JETS); modes.push_back(_TT);}
  vector<TString> fake_histos; fake_histos.push_back(p+FF_corr_QCD_MCsum_noGen); fake_histos.push_back(p+FF_corr_QCD_MCsum_noGen_AI); if(CHAN!=kTAU){fake_histos.push_back(p+FF_corr_Wjets_MCsum_noGen);  fake_histos.push_back(p+FF_corr_Wjets_MC_noGen); fake_histos.push_back(p+FF_TT_J_only_SR);}
  vector<Int_t> dm_bins; dm_bins.push_back(N_t_QCD); dm_bins.push_back(N_t_QCD); if(CHAN!=kTAU){dm_bins.push_back(N_t_Wjets); dm_bins.push_back(N_t_Wjets); dm_bins.push_back(N_t_TT);}
  vector<Int_t> jet_bins; jet_bins.push_back(N_j_QCD); jet_bins.push_back(N_j_QCD); if(CHAN!=kTAU){jet_bins.push_back(N_j_Wjets); jet_bins.push_back(N_j_Wjets); jet_bins.push_back(N_j_TT_SR);}
  vector<Int_t> pt_bins; pt_bins.push_back(N_p_QCD); pt_bins.push_back(N_p_QCD_AI); if(CHAN!=kTAU){pt_bins.push_back(N_p_Wjets); pt_bins.push_back(N_p_Wjets); pt_bins.push_back(N_p_TT_SR);}

  for(Int_t imode=0;imode<modes.size();imode++){
    TString ff_fitted_name = fake_histos.at(imode); ff_fitted_name.ReplaceAll(".root","_fitted.root");
    TFile ff_fitted(ff_fitted_name,"RECREATE");
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
          if(modes.at(imode) & _QCD && !modes.at(imode) & _AI ) for(int ibin=0; ibin<nbins; ibin++){a_bins[ibin]=Pt_cuts_QCD[ibin];}
          if(modes.at(imode) & _QCD && modes.at(imode) & _AI ) for(int ibin=0; ibin<nbins; ibin++){a_bins[ibin]=Pt_cuts_QCD_AI[ibin];}
          if(modes.at(imode) & _W_JETS) for(int ibin=0; ibin<nbins; ibin++){a_bins[ibin]=Pt_cuts_Wjets[ibin];}
          if(modes.at(imode) & _TT) for(int ibin=0; ibin<nbins; ibin++){a_bins[ibin]=Pt_cuts_TT_SR[ibin];}
          
          
          if( CHAN==kMU && ( ( modes.at(imode) & _QCD ) )
              || ( modes.at(imode) & _W_JETS && idm == 1 )
              || ( modes.at(imode) & _W_JETS && idm == 0 && ijet == 0 )
              || ( modes.at(imode) & _TT )
              ) 
            {
              cf.set_fitFunc( "landau(0)+pol0(2)" );
              cf.set_err_scale( 3.0 ); //opt 1
              cf.set_err_cl( 0 );
            }
          /*else if( CHAN==kEL && (  (modes.at(imode) & _QCD) && ijet == 0 ) ){
            cf.set_fitFunc( "landau(0)+pol0(2)" );
            cf.set_err_scale( 3.0 ); //opt 1
            cf.set_err_cl( 0 );
            }*/
          else if( CHAN==kEL ){
            cf.set_fitFunc( "landau(0)+pol0(2)" );
            cf.set_err_scale( 3.0 ); //opt 1
            cf.set_err_cl( 0 );
            if( modes.at(imode) & _QCD && ijet == 0 && idm == 1 ){
              cf.set_histMaxFrac( 0.4 );
              cf.set_smoothFrac(0.15);
              cf.set_smoothMode("spline3");              
            }
          }
          else if( CHAN==kEL && (  (modes.at(imode) & _QCD) && (modes.at(imode) & _AI) && ijet == 1 && idm == 0 ) ){
            cf.set_fitFunc( "landau(0)+pol1(2)" );
            cf.set_histMaxFrac( 0.2 );
            cf.set_smoothFrac(0.1);
            cf.set_smoothMode("spline3");              
          }
          else if( CHAN==kEL && (  (modes.at(imode) & _QCD) && ijet == 1 && idm == 0 ) ){
            cf.set_fitFunc( "landau(0)+pol1(2)" );
            /*cf.set_histMaxFrac( 0.6 );
            cf.set_smoothFrac(0.4);
            cf.set_smoothMode("spline3");*/              
          }
          else if( CHAN==kTAU && idm==0 ){
            cf.set_fitFunc( "landau(0)+pol0(2)" );
            cf.set_err_scale( 3.0 );
            cf.set_err_cl( 0 );
          }
          else{
            cf.set_fitFunc( "landau(0)+pol1(2)" );
            cf.set_err_scale( 1.2 );
            if( CHAN==kTAU && modes.at(imode) & _AI && ijet == 0 ){
              cf.set_histMaxFrac( 0.4 );
              cf.set_smoothFrac(0.2);
              cf.set_smoothMode("spline3");              
            }
            else if( CHAN==kTAU && ijet == 0 ){
              cf.set_histMaxFrac( 0.25 );
              cf.set_smoothFrac(0.10);
              //cf.set_histMaxFrac( 0.55 );
              //cf.set_smoothFrac(0.3);
              cf.set_smoothMode("spline3");
            }
            else if( CHAN==kTAU && ijet == 1 ){
              cf.set_histMaxFrac( 0.4 );
              cf.set_smoothFrac(0.2);
              cf.set_smoothMode("spline3");
            //if(CHAN==kMU && modes.at(imode) & _QCD && idm==0 && ijet==1) cf.set_histMaxFrac( 0.75 );
            //if(CHAN==kEL && modes.at(imode) & _W_JETS && idm==1) cf.set_histMaxFrac( 0.65 );
            }
          }
          Int_t cat=idm+dm_bins.at(imode)*ijet;
          cf.set_fitFromBin( 1+cat*nbins );
          cf.set_fitMin( fitMin );
          cf.set_fitMax( fitMax );
          cf.set_histo_bins( fitBins );
          
          std::vector<double> bins;
          cf.set_bin_centers( fake_histos.at(imode) , "bins_weighted", nbins ); //fitFromBin  needs to be set BEFORE
          
          cf.fitHisto();
          
          TGraph *g_fit_input=cf.returnFitInputGraph(); //the input to the fit: data points in the range given
          TF1 *f_fit=cf.returnFitForm();                //the fit result (function)
          TGraphAsymmErrors *g_fit=cf.returnFitGraph();              //the fit result binned (histo)
          TGraphAsymmErrors *g_fit2=new TGraphAsymmErrors( *g_fit );
          
          for(int i=0; i<g_fit->GetN(); i++){
            Double_t x; Double_t y;
            g_fit->GetPoint(i,x,y);
            /*if( i<=1 && g_fit->GetErrorYlow(i) > 1.4*g_fit->GetErrorYlow(i+1) )   g_fit->SetPointEYlow( i, g_fit->GetErrorYlow(i+1) );
            if( i<=1 && g_fit->GetErrorYhigh(i) > 1.4*g_fit->GetErrorYhigh(i+1) ) g_fit->SetPointEYhigh( i, g_fit->GetErrorYhigh(i+1) );
            if( i>1 && g_fit->GetErrorYlow(i) > 1.4*g_fit->GetErrorYlow(i-1) )   g_fit->SetPointEYlow( i, g_fit->GetErrorYlow(i-1) );
            if( i>1 && g_fit->GetErrorYhigh(i) > 1.4*g_fit->GetErrorYhigh(i-1) ) g_fit->SetPointEYhigh( i, g_fit->GetErrorYhigh(i-1) );*/
            if(y-g_fit->GetErrorYlow(i)<0) g_fit->SetPointEYlow( i,y );
            if(y+g_fit->GetErrorYhigh(i)>=1.) g_fit->SetPointEYhigh( i,0.99-y );
          }
          
          TCanvas *c2=new TCanvas();
          c2->cd();
          c2->SetLogx();
          gStyle->SetOptStat(0);
          gPad->SetBottomMargin(0.15);
          gPad->SetLeftMargin(0.15);
          //  h->Draw("E");     //to set the axis
          double ymax = TMath::MaxElement(g_fit->GetN(),g_fit->GetY() );
          cout << "ymax: " << ymax << endl;
          double h_fit_max=0;
          //f_fit->GetYaxis()->SetRangeUser(0.,ymax+0.05);
          g_fit->GetYaxis()->SetRangeUser(0.,1.);
          g_fit->GetXaxis()->SetRangeUser(fitMin-0.1,fitMax+7);
          //  g_fit->SetMarkerStyle(21);
          g_fit->SetTitle("");
          g_fit->Draw();
          g_fit->GetXaxis()->SetTitle("p_{T} [GeV]");
          g_fit->GetXaxis()->SetTitleSize(0.08);
          g_fit->GetXaxis()->SetTitleFont(62);
          g_fit->GetXaxis()->SetTitleOffset(0.75);
          g_fit->GetXaxis()->SetLabelSize(0.05);
          g_fit->GetYaxis()->SetTitle("F_{F}");
          g_fit->GetYaxis()->SetTitleFont(62);
          g_fit->GetYaxis()->SetTitleSize(0.08);
          g_fit->GetYaxis()->SetTitleOffset(0.75);
          g_fit->GetYaxis()->SetLabelSize(0.05);
          f_fit->SetMinimum(0);
          f_fit->SetLineColor(kRed);
          f_fit->SetLineWidth(3);
          g_fit->SetLineWidth(5.);
          g_fit->SetLineColor(kOrange-2);
          //h_fit->SetLineColor(602);
          //h_fit->Draw("E same");
          g_fit->Draw("Ez same");
          g_fit2->SetLineColor(kRed);
          g_fit2->SetLineWidth(3);
          g_fit2->Draw("XCP same");
          //f_fit->Draw("axis same");
          g_fit_input->SetLineWidth(3.);
          g_fit_input->SetMarkerStyle(20);
          g_fit_input->Draw("P same");

          
          gPad->RedrawAxis();
          
          TLatex l,l1;
          l.SetTextSize(0.05);l1.SetTextSize(0.05);
          l.SetNDC();l1.SetNDC();
          //l.SetTextFont(102);
          TString bkg=""; {if(modes.at(imode) & _QCD) bkg+="QCD"; else if(modes.at(imode) & _W_JETS) bkg+="W+jets"; else if(modes.at(imode) & _TT) bkg+="TT";}
          TString decayMode=""; {if(idm==0) decayMode+="1-prong"; else decayMode+="3-prong";}
          TString jetMode=""; { if(modes.at(imode) & _TT ) jetMode+="#geq0jet"; else if(ijet==0) jetMode+="0jet"; else jetMode+="#geq1jet";}
          /*if(idm==0) l.DrawLatex(0.52,0.8,"FFs "+bkg);
          else l.DrawLatex(0.52,0.8,"FFs "+bkg);
          if(idm==0) l1.DrawLatex(0.52,0.7,decayMode+", "+jetMode);
          else l1.DrawLatex(0.52,0.7,decayMode+", "+jetMode);*/
          if(idm==0) l1.DrawLatex(0.22,0.85,decayMode+", "+jetMode);
          else l1.DrawLatex(0.22,0.85,decayMode+", "+jetMode);

          TLatex cms1 = TLatex( 0.15, 0.915, "CMS" );
          TLatex cms2 = TLatex( 0.243, 0.915, "Preliminary" );
          cms1.SetNDC();
          cms1.SetTextSize(0.06);
          cms2.SetNDC();
          cms2.SetTextFont(12);
          cms2.SetTextSize(0.06);
          
          TLatex infoRight = TLatex( 0.725, 0.915, "35.9 fb^{-1} (13 TeV)" );
          infoRight.SetNDC();
          infoRight.SetTextSize(0.035);

          cms1.Draw();
          cms2.Draw();
          infoRight.Draw();
          
          TString ending=""; stringstream convert; 
          if(modes.at(imode) & _QCD) ending=ending+"QCD_"; if(modes.at(imode) & _W_JETS) ending=ending+"Wjets_"; if(modes.at(imode) & _TT) ending=ending+"TT_";
          if( modes.at(imode) & _QCD && ff_fitted_name.Contains("AI") ) ending += "AI_";
          if( modes.at(imode) & _W_JETS && ff_fitted_name.Contains("_MC_") ) ending += "MC_";
          convert << "dm" << idm << "_" << "njet" << ijet;
          if(itight==1) convert << "_alt";
          ending=ending+convert.str();
          gPad->RedrawAxis();
          c2->SaveAs(pi+"pTfit"+ending+".png");
          if(ALLPLOTS) c2->SaveAs(pi+"pTfit"+ending+".pdf");
          g_fit->SetName(convert.str().c_str());
          ff_fitted.cd();
          g_fit->Write();
          
          delete g_fit_input,f_fit;
        
        
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

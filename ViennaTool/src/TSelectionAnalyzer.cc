#include "ViennaTool/interface/TSelectionAnalyzer.h"

#include <iostream>
#include <sstream>


using namespace std;

TSelectionAnalyzer::TSelectionAnalyzer()
{
}

TSelectionAnalyzer::~TSelectionAnalyzer()
{
}

void TSelectionAnalyzer::calcBgEstSim(const TString preselection,const Int_t mode,const Int_t categoryMode,const TString output, const Int_t cuts)
{
  TH1D *tightSR,*looseSR;//,*allSR;
  TString suff=""; 
  if (mode & _SS ) suff=" (SS) ";

  if (mode & MT) {
    tightSR =     new TH1D("hh_t_mt","Tight events in SR"+suff,w_mt_n,w_mt_v);
    looseSR =     new TH1D("hh_l_mt","Loose events in SR"+suff,w_mt_n,w_mt_v);
  }
  else if (mode & MVIS && mode & _AI) {
    tightSR = new TH1D("hh_t_mvis","Tight events in SR"+suff,w_mvis_n,w_mvis_v);
    looseSR = new TH1D("hh_l_mvis","Loose events in SR"+suff,w_mvis_n,w_mvis_v);
  }
  else if (mode & MVIS) {
    tightSR = new TH1D("hh_t_mvis","Tight events in SR"+suff,nbins_mvis,hist_min_mvis,hist_max_mvis);
    looseSR = new TH1D("hh_l_mvis","Loose events in SR"+suff,nbins_mvis,hist_min_mvis,hist_max_mvis);
  }
  else if (mode & PT) {
    tightSR = new TH1D("hh_t_pt","Tight events in SR"+suff,nbins_pt,hist_min_pt,hist_max_pt);
    looseSR = new TH1D("hh_l_pt","Loose events in SR"+suff,nbins_pt,hist_min_pt,hist_max_pt);
  }
  else if (mode & ETA2) {
    tightSR = new TH1D("hh_t_eta","Tight events in SR"+suff,nbins_eta,hist_min_eta,hist_max_eta);
    looseSR = new TH1D("hh_l_eta","Loose events in SR"+suff,nbins_eta,hist_min_eta,hist_max_eta);
  }
  else if (mode & SVFIT) {                                      
    tightSR = new TH1D("hh_t_svfit","Tight events in SR"+suff,nbins_svfit,hist_min_svfit,hist_max_svfit);
    looseSR = new TH1D("hh_l_svfit","Loose events in SR"+suff,nbins_svfit,hist_min_svfit,hist_max_svfit);
  }
  else if (mode & LEPPT) {                                      
    tightSR = new TH1D("hh_t_lepPt","Tight events in SR"+suff,w_lepPt_n,w_lepPt_v);
    looseSR = new TH1D("hh_l_lepPt","Loose events in SR"+suff,w_lepPt_n,w_lepPt_v);
  }
  
  else {
    std::cout<<"ERROR: no valid mode given. Exiting TNtupleAnalyzer::calcBgEstSim..."<<std::endl;
    return;
  }

  loadFile(preselection,"Events");

  
  TString cutstring = this->getSRCutString(mode, categoryMode);
  
  if ( DEBUG ) std::cout << "SR CUT STRING: " << cutstring << endl;

  TString s_selval, s_histoname = "";
  if (mode & MVIS) {      s_selval = "alltau_mvis[tau_iso_ind]"; s_histoname = "mvis";  }
  else if (mode & PT)   { s_selval = "alltau_pt[tau_iso_ind]";   s_histoname = "pt";    }
  else if (mode & MT) {   s_selval = "alltau_mt[tau_iso_ind]";   s_histoname = "mt";    }
  else if (mode & ETA2) {   s_selval = "alltau_eta[tau_iso_ind]";   s_histoname = "eta";    }
  else if (mode & LEPPT) {s_selval = "lep_pt";         s_histoname = "lepPt"; }
  else if (mode & SVFIT) {s_selval = "alltau_svfit[tau_iso_ind]"; s_histoname = "svfit"; }


  event_s->fChain->Draw(s_selval + ">>hh_t_"+s_histoname+"", "weight_sf * "+cutstring + "*" + this->getWPCutString("tight"), "goff");
   if ( DEBUG ) {
     cout << "hh_t_"<<s_histoname << " DONE " << endl;
     cout << "full cut string tight region : "<<"weight_sf * " << cutstring  <<  "*"  <<  this->getWPCutString("tight") <<endl; 
   }
  event_s->fChain->Draw(s_selval + ">>hh_l_"+s_histoname+"", "weight_sf * "+cutstring + "*" + this->getWPCutString("loose"), "goff");
   if ( DEBUG ) {
     cout << "hh_l_"<<s_histoname << " DONE " << endl;
     cout << "full cut string loose region : " <<"weight_sf * " <<cutstring  << "*"  << this->getWPCutString("loose") <<endl; 
 
    }
  
  
  TFile f(output,"recreate");


  if (DEBUG) {
    std::cout<<"output: "<<output<<std::endl;

    std::cout << "***************** SR HISTO STATS ********************" << std::endl;
    std::cout << "No of events passing tight criteria: " << tightSR->GetEntries() << std::endl;
    std::cout << "No of events passing loose criteria: " << looseSR->GetEntries() << std::endl;
  }

  tightSR->Write();
  looseSR->Write();
  f.Close();

  delete tightSR;delete looseSR;
  delete tchain;delete event_s;
}



void TSelectionAnalyzer::getCRHisto(TString preselection,Int_t mode,TString output)
{
  loadFile(preselection,"Events");

  TH1D* tightCR,*looseCR;
  
  if (mode & MT) {
    tightCR = new TH1D("hh_t_mt","",w_mt_n,w_mt_v);
    looseCR = new TH1D("hh_l_mt","",w_mt_n,w_mt_v);
  }
  else if (mode & MVIS) {
    tightCR = new TH1D("hh_t_mvis","",w_mvis_n,w_mvis_v);
    looseCR = new TH1D("hh_l_mvis","",w_mvis_n,w_mvis_v);
  }
  else if (mode & PT) {
    tightCR = new TH1D("hh_t_pt","",nbins_pt,hist_min_pt,hist_max_pt);
    looseCR = new TH1D("hh_l_pt","",nbins_pt,hist_min_pt,hist_max_pt);
  }
  else if (mode & ETA2) {
    tightCR = new TH1D("hh_t_eta","",nbins_eta,hist_min_eta,hist_max_eta);
    looseCR = new TH1D("hh_l_eta","",nbins_eta,hist_min_eta,hist_max_eta);
  }
  else if (mode & MUISO) {
    tightCR = new TH1D("hh_t_muiso","",w_muiso_n,w_muiso_v);
    looseCR = new TH1D("hh_l_muiso","",w_muiso_n,w_muiso_v);
  }
  else if (mode & LEPPT) {
    tightCR = new TH1D("hh_t_lepPt","",w_lepPt_n,w_lepPt_v);
    looseCR = new TH1D("hh_l_lepPt","",w_lepPt_n,w_lepPt_v);
  }
  else {
    std::cout<<"ERROR: no valid mode given. Exiting TNtupleAnalyzer::getCRHisto..."<<std::endl;
    return;
  }

  TString cutstring = this->getCRCutString(mode);
  
  if ( DEBUG ) std::cout << "CR CUT STRING: " << cutstring << endl;

  TString s_selval, s_histoname = "";
  if (mode & MVIS) {      s_selval = "alltau_mvis[0]"; s_histoname = "mvis";  }
  else if (mode & MUISO) {s_selval = "lep_iso";        s_histoname = "muiso"; }
  else if (mode & PT)   { s_selval = "alltau_pt[0]";   s_histoname = "pt";    }
  else if (mode & MT) {   s_selval = "alltau_mt[0]";   s_histoname = "mt";    }
  else if (mode & ETA2) {   s_selval = "alltau_eta[0]";   s_histoname = "eta";    }
  else if (mode & LEPPT) {s_selval = "lep_pt";         s_histoname = "lepPt"; }


  
  event_s->fChain->Draw(s_selval + ">>hh_t_"+s_histoname+"", "weight_sf * "+cutstring + "*" + this->getWPCutString("tight"), "goff");
   if ( DEBUG ) cout << "hh_t_"<<s_histoname << " DONE " << endl;
  event_s->fChain->Draw(s_selval + ">>hh_l_"+s_histoname+"", "weight_sf * "+cutstring + "*" + this->getWPCutString("loose"), "goff");
   if ( DEBUG ) cout << "hh_l_"<<s_histoname << " DONE " << endl;
  
  if (DEBUG) {
    std::cout << "***************** CR HISTO STATS ********************" << std::endl;
    std::cout << "No of events passing tight criteria: " << tightCR->GetEntries() << std::endl;
    std::cout << "No of events passing loose criteria: " << looseCR->GetEntries() << std::endl;
  }


  TFile f1(output,"recreate");
  tightCR->Write();
  looseCR->Write();
  if (DEBUG) {std::cout<<"WRITING output: " << output << std::endl;}
  f1.Close();

  delete tightCR;delete looseCR;
  delete event_s;delete tchain;
}





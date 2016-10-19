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

/*void TSelectionAnalyzer::loadFile(TString filename, TString chain)
{
  tchain = new TChain(chain);
  tchain->Add(filename);

  if       (filename==datafile) this->curr_sample="data";
  else if  (filename==DYfile || filename==DY_NJfile) this->curr_sample="DY";
  else if  (filename==TTfile) this->curr_sample="TT";
  else if  (filename==Wjetsfile) this->curr_sample="Wjets";
  else if  (filename==QCDfile) this->curr_sample="QCD";
  else if  (filename==VVfile) this->curr_sample="VV";
  else this->curr_sample="unknown";
  
  int nev=0;
  if (chain=="Events"){  event_s = new SignalClass(tchain); if (DEBUG) nev=event_s->fChain->GetEntries(); }
  else std::cout << "unknown chain!" << std::endl;
  if (DEBUG) std::cout<<"File: "<<filename<<" loaded" << ", #events: "<< nev << std::endl;
}

void TSelectionAnalyzer::closeFile()
{
  delete event_s;
  delete tchain;
  }*/

void TSelectionAnalyzer::calcBgEstSim(const TString preselection,const Int_t mode,const Int_t categoryMode,const TString output, const Int_t cuts)
{
  TH1D *tightSR,*looseSR,*looseSR_tt,*allSR;
  TString suff=""; if (mode & _SS ) suff=" (SS) ";
  if (mode & M2T) {                                      
    tightSR = new TH1D("hh_t_mt2","Tight events in SR"+suff,nbins_mt2,hist_min_mt2,hist_max_mt2);
    looseSR = new TH1D("hh_l_mt2","Loose events in SR"+suff,nbins_mt2,hist_min_mt2,hist_max_mt2);
    looseSR_tt = new TH1D("hh_ltt_mt2","Loose events in tt SR"+suff,nbins_mt2,hist_min_mt2,hist_max_mt2);
    allSR   = new TH1D("hh_a_mt2",  "All events in SR"+suff,nbins_mt2,hist_min_mt2,hist_max_mt2);
  }
  else if (mode & MT) {
    tightSR = new TH1D("hh_t_mt","Tight events in SR"+suff,nbins_mt,hist_min_mt,hist_max_mt);
    looseSR = new TH1D("hh_l_mt","Loose events in SR"+suff,nbins_mt,hist_min_mt,hist_max_mt);
    looseSR_tt = new TH1D("hh_ltt_mt","Loose events in tt SR"+suff,nbins_mt,hist_min_mt,hist_max_mt);
    allSR   = new TH1D("hh_a_mt",  "All events in SR"+suff,nbins_mt,hist_min_mt,hist_max_mt);
  }
  else if (mode & MVIS && mode & _AI) {
    tightSR = new TH1D("hh_t_mvis","Tight events in SR"+suff,w_mvis_n,w_mvis_v);
    looseSR = new TH1D("hh_l_mvis","Loose events in SR"+suff,w_mvis_n,w_mvis_v);
    looseSR_tt = new TH1D("hh_ltt_mvis","Loose events in tt SR"+suff,w_mvis_n,w_mvis_v);
    allSR   = new TH1D("hh_a_mvis",  "All events in SR"+suff,w_mvis_n,w_mvis_v);
  }
  /*else if (mode & MVIS) {
    tightSR = new TH1D("hh_t_mvis","Tight events in SR"+suff,w_mvis_n,w_mvis_v);
    looseSR = new TH1D("hh_l_mvis","Loose events in SR"+suff,w_mvis_n,w_mvis_v);
    looseSR_tt = new TH1D("hh_ltt_mvis","Loose events in tt SR"+suff,w_mvis_n,w_mvis_v);
    allSR   = new TH1D("hh_a_mvis",  "All events in SR"+suff,w_mvis_n,w_mvis_v);
    }*/
  else if (mode & MVIS) {
    tightSR = new TH1D("hh_t_mvis","Tight events in SR"+suff,nbins_mvis,hist_min_mvis,hist_max_mvis);
    looseSR = new TH1D("hh_l_mvis","Loose events in SR"+suff,nbins_mvis,hist_min_mvis,hist_max_mvis);
    looseSR_tt = new TH1D("hh_ltt_mvis","Loose events in tt SR"+suff,nbins_mvis,hist_min_mvis,hist_max_mvis);
    allSR   = new TH1D("hh_a_mvis",  "All events in SR"+suff,nbins_mvis,hist_min_mvis,hist_max_mvis);
  }
  else if (mode & PT) {
    tightSR = new TH1D("hh_t_pt","Tight events in SR"+suff,nbins_pt,hist_min_pt,hist_max_pt);
    looseSR = new TH1D("hh_l_pt","Loose events in SR"+suff,nbins_pt,hist_min_pt,hist_max_pt);
    looseSR_tt = new TH1D("hh_ltt_pt","Loose events in tt SR"+suff,nbins_pt,hist_min_pt,hist_max_pt);
    allSR   = new TH1D("hh_a_pt",  "All events in SR"+suff,nbins_pt,hist_min_pt,hist_max_pt);
  }
  else if (mode & SVFIT) {                                      
    tightSR = new TH1D("hh_t_svfit","Tight events in SR"+suff,nbins_svfit,hist_min_svfit,hist_max_svfit);
    looseSR = new TH1D("hh_l_svfit","Loose events in SR"+suff,nbins_svfit,hist_min_svfit,hist_max_svfit);
    looseSR_tt = new TH1D("hh_ltt_svfit","Loose events in tt SR"+suff,nbins_svfit,hist_min_svfit,hist_max_svfit);
    allSR   = new TH1D("hh_a_svfit",  "All events in SR"+suff,nbins_svfit,hist_min_svfit,hist_max_svfit);
  }
  else if (mode & LEPPT) {                                      
    tightSR = new TH1D("hh_t_lepPt","Tight events in SR"+suff,nbins_lepPt,hist_min_lepPt,hist_max_lepPt);
    looseSR = new TH1D("hh_l_lepPt","Loose events in SR"+suff,nbins_lepPt,hist_min_lepPt,hist_max_lepPt);
    looseSR_tt = new TH1D("hh_ltt_lepPt","Loose events in tt SR"+suff,nbins_lepPt,hist_min_lepPt,hist_max_lepPt);
    allSR   = new TH1D("hh_a_lepPt",  "All events in SR"+suff,nbins_lepPt,hist_min_lepPt,hist_max_lepPt);
  }
  else if (mode & MVAMET) {                                      
    tightSR = new TH1D("hh_t_mvamet","Tight events in SR"+suff,nbins_mvamet,hist_min_mvamet,hist_max_mvamet);
    looseSR = new TH1D("hh_l_mvamet","Loose events in SR"+suff,nbins_mvamet,hist_min_mvamet,hist_max_mvamet);
    looseSR_tt = new TH1D("hh_ltt_mvamet","Loose events in tt SR"+suff,nbins_mvamet,hist_min_mvamet,hist_max_mvamet);
    allSR   = new TH1D("hh_a_mvamet",  "All events in SR"+suff,nbins_mvamet,hist_min_mvamet,hist_max_mvamet);
  }
  else if (mode & ETA) {                                      
    tightSR = new TH1D("hh_t_eta","Tight events in SR"+suff,nbins_eta,hist_min_eta,hist_max_eta);
    looseSR = new TH1D("hh_l_eta","Loose events in SR"+suff,nbins_eta,hist_min_eta,hist_max_eta);
    looseSR_tt = new TH1D("hh_ltt_eta","Loose events in tt SR"+suff,nbins_eta,hist_min_eta,hist_max_eta);
    allSR   = new TH1D("hh_a_eta",  "All events in SR"+suff,nbins_eta,hist_min_eta,hist_max_eta);
  }
  else if (mode & MMTOT) {                                      
    tightSR = new TH1D("hh_t_mttot","Tight events in SR"+suff,nbins_mttot,hist_min_mttot,hist_max_mttot);
    looseSR = new TH1D("hh_l_mttot","Loose events in SR"+suff,nbins_mttot,hist_min_mttot,hist_max_mttot);
    looseSR_tt = new TH1D("hh_ltt_mttot","Loose events in tt SR"+suff,nbins_mttot,hist_min_mttot,hist_max_mttot);
    allSR   = new TH1D("hh_a_mttot",  "All events in SR"+suff,nbins_mttot,hist_min_mttot,hist_max_mttot);
  }
  
  else {
    std::cout<<"ERROR: no valid mode given. Exiting TNtupleAnalyzer::calcBgEstSim..."<<std::endl;
    return;
  }


  loadFile(preselection,"Events");
  Int_t nentries = Int_t(event_s->fChain->GetEntries());
  std::cout<<"calcBgEstSim: Input " << preselection << ", output " << output << ". Processing "<<nentries<<" events."<<flush;
  Double_t fillVal=0;
  Int_t tau_ind=0;
  for (Int_t jentry=0; jentry<nentries;jentry++) {
    event_s->GetEntry(jentry);
    if (APPLY_TO_ISOTAU){
      tau_ind=event_s->tau_iso_ind;
      if ( tau_ind<0 ) continue;
    }

    if ( !fulfillCategory(categoryMode) ) continue;
    if ( isInSR(mode,tau_ind) && ( !cuts || this->passesCuts(cuts,tau_ind) )  ){
      fillVal=this->selVal(mode,tau_ind);
      Double_t DMscaling=1;
      Double_t XSscaling=1;
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      //tau id scaling
      if( preselection.Contains("DY_TT") || preselection.Contains("TT_T") || preselection.Contains("VV_T") ){
        if(event_s->alltau_decay->at(0)<5) DMscaling=1.;
        else DMscaling=1.;
      }
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      //tau XS scaling
      /*if( preselection.Contains("DY_TT") || preselection.Contains("DY_L") || preselection.Contains("DY_J") ){
        XSscaling=0.95;
        }*/ // this is now already done in the preprocessing
      allSR->Fill(fillVal,event_s->weight_sf*DMscaling*XSscaling);
      if ( this->isTight(0,tau_ind) ) tightSR->Fill(fillVal,event_s->weight_sf*DMscaling*XSscaling);
      if ( this->isLoose(0,tau_ind) ) looseSR->Fill(fillVal,event_s->weight_sf*DMscaling*XSscaling);
      if ( this->isLoose_tt(0,tau_ind) ) looseSR_tt->Fill(fillVal,event_s->weight_sf*DMscaling*XSscaling);
    }
  }
  std::cout << " in tightSR: " << tightSR->Integral(-1,-1) << std::endl;

  TFile f(output,"recreate");
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //tau id scaling errors
  if( preselection.Contains("DY_TT") || preselection.Contains("TT_T") || preselection.Contains("VV_T") ){
    for(int i=1; i<tightSR->GetNbinsX();i++){
      if(tightSR->GetBinContent(i) > 1){
        Double_t err1=tightSR->GetBinError(i)/tightSR->GetBinContent(i);
        Double_t err2=0.06;
        tightSR->SetBinError( i,TMath::Sqrt(TMath::Power(err1,2)+TMath::Power(err2,2))*tightSR->GetBinContent(i) );
      }
    }
    for(int i=1; i<looseSR->GetNbinsX();i++){
      if(looseSR->GetBinContent(i) > 1){
        Double_t err1=looseSR->GetBinError(i)/looseSR->GetBinContent(i);
        Double_t err2=0.06;
        looseSR->SetBinError( i,TMath::Sqrt(TMath::Power(err1,2)+TMath::Power(err2,2))*looseSR->GetBinContent(i) );
      }
    }
    for(int i=1; i<looseSR_tt->GetNbinsX();i++){
      if(looseSR_tt->GetBinContent(i) > 1){
        Double_t err1=looseSR_tt->GetBinError(i)/looseSR_tt->GetBinContent(i);
        Double_t err2=0.06;
        looseSR_tt->SetBinError( i,TMath::Sqrt(TMath::Power(err1,2)+TMath::Power(err2,2))*looseSR_tt->GetBinContent(i) );
      }
    }    
  }
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //DY XS error
  if( preselection.Contains("DY_TT") || preselection.Contains("DY_L") || preselection.Contains("DY_J") ){
    for(int i=1; i<tightSR->GetNbinsX();i++){
      if(tightSR->GetBinContent(i) > 1){
        Double_t err1=tightSR->GetBinError(i)/tightSR->GetBinContent(i);
        Double_t err2=0.02;
        tightSR->SetBinError( i,TMath::Sqrt(TMath::Power(err1,2)+TMath::Power(err2,2))*tightSR->GetBinContent(i) );
      }
    }
    for(int i=1; i<looseSR->GetNbinsX();i++){
      if(looseSR->GetBinContent(i) > 1){
        Double_t err1=looseSR->GetBinError(i)/looseSR->GetBinContent(i);
        Double_t err2=0.02;
        looseSR->SetBinError( i,TMath::Sqrt(TMath::Power(err1,2)+TMath::Power(err2,2))*looseSR->GetBinContent(i) );
      }
    }
    for(int i=1; i<looseSR_tt->GetNbinsX();i++){
      if(looseSR_tt->GetBinContent(i) > 1){
        Double_t err1=looseSR_tt->GetBinError(i)/looseSR_tt->GetBinContent(i);
        Double_t err2=0.02;
        looseSR_tt->SetBinError( i,TMath::Sqrt(TMath::Power(err1,2)+TMath::Power(err2,2))*looseSR_tt->GetBinContent(i) );
      }
    }    
  }
  tightSR->Write();
  looseSR->Write();
  looseSR_tt->Write();
  allSR->Write();
  f.Close();

  delete tightSR;delete looseSR;delete looseSR_tt;delete allSR;
  delete tchain;delete event_s;
}

void TSelectionAnalyzer::getCRHisto(TString preselection,Int_t mode,TString output)
{
  loadFile(preselection,"Events");

  std::cout << "In TSelectionanalyzer::getCRHisto , producing " << output << std::endl;

  const Int_t FI=1;
  TH1D* tightCR,*looseCR,*looseCR_tt,*allCR;
  if (mode & MT) {
    tightCR = new TH1D("hh_t_mt","",FI*nbins_mt,hist_min_mt,hist_max_mt);
    looseCR = new TH1D("hh_l_mt","",FI*nbins_mt,hist_min_mt,hist_max_mt);
    looseCR_tt = new TH1D("hh_ltt_mt","",FI*nbins_mt,hist_min_mt,hist_max_mt);
    allCR   = new TH1D("hh_a_mt","",FI*nbins_mt,hist_min_mt,hist_max_mt);
  }
  else if (mode & MVIS) {
    tightCR = new TH1D("hh_t_mvis","",w_mvis_n,w_mvis_v);
    looseCR = new TH1D("hh_l_mvis","",w_mvis_n,w_mvis_v);
    looseCR_tt = new TH1D("hh_ltt_mvis","",w_mvis_n,w_mvis_v);
    allCR   = new TH1D("hh_a_mvis","",w_mvis_n,w_mvis_v);
  }
  else if (mode & PT) {
    tightCR = new TH1D("hh_t_pt","",FI*nbins_pt,hist_min_pt,hist_max_pt);
    looseCR = new TH1D("hh_l_pt","",FI*nbins_pt,hist_min_pt,hist_max_pt);
    looseCR_tt = new TH1D("hh_ltt_pt","",FI*nbins_pt,hist_min_pt,hist_max_pt);
    allCR   = new TH1D("hh_a_pt","",FI*nbins_pt,hist_min_pt,hist_max_pt);
  }
  else if (mode & MUISO) {
    tightCR = new TH1D("hh_t_muiso","",w_muiso_n,w_muiso_v);
    looseCR = new TH1D("hh_l_muiso","",w_muiso_n,w_muiso_v);
    looseCR_tt = new TH1D("hh_ltt_muiso","",w_muiso_n,w_muiso_v);
    allCR   = new TH1D("hh_a_muiso","",w_muiso_n,w_muiso_v);
  }
  else if (mode & ZPT) {
    tightCR = new TH1D("hh_t_zpt","",w_zpt_n,w_zpt_v);
    looseCR = new TH1D("hh_l_zpt","",w_zpt_n,w_zpt_v);
    looseCR_tt = new TH1D("hh_ltt_zpt","",w_zpt_n,w_zpt_v);
    allCR   = new TH1D("hh_a_zpt","",w_zpt_n,w_zpt_v);
  }
  else {
    std::cout<<"ERROR: no valid mode given. Exiting TNtupleAnalyzer::getCRHisto..."<<std::endl;
    return;
  }
  Int_t ct=0,cl=0,cltt=0;
  Int_t nentries = Int_t(event_s->fChain->GetEntries());
  if (DEBUG) std::cout<<"The input chain contains: "<<nentries<<" events."<<std::endl;
  Double_t fillVal;
  for (Int_t jentry=0; jentry<nentries;jentry++) {
    if (DEBUG){ if (jentry%1000000==0 && jentry>0) std::cout<<jentry<<std::endl; }
    event_s->GetEntry(jentry);
    fillVal=this->selVal(mode);
    if (isInCR(mode)) {
      allCR->Fill(fillVal,event_s->weight_sf);
      if (this->isTight()) {
	ct++;
	tightCR->Fill(fillVal,event_s->weight_sf); 
      }
      else if (this->isLoose()) {
	cl++;
	looseCR->Fill(fillVal,event_s->weight_sf); 
      }
      if (this->isLoose_tt()) {
	cltt++;
	looseCR_tt->Fill(fillVal,event_s->weight_sf); 
      }
    }
  }
  if (DEBUG) std::cout<<cl<<" loose"<<std::endl;
  if (DEBUG) std::cout<<ct<<" tight"<<std::endl;
  if (DEBUG) std::cout<<cltt<<" loose tt"<<std::endl;

  TFile f1(output,"recreate");
  tightCR->Write();
  looseCR->Write();
  looseCR_tt->Write();
  allCR->Write();
  f1.Close();

  delete tightCR;delete looseCR;delete looseCR_tt;delete allCR;
  //  delete event_s;delete tchain;
}





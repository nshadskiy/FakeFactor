#include "ViennaTool/interface/TSelectionAnalyzer.h"

#include <iostream>
#include <string>
#include "TStyle.h"
#include <thread>

using namespace std;

// void CallCRHisto_creation (TSelectionAnalyzer* Analyzer ) {
void CallCRHisto_creation (TSelectionAnalyzer* Analyzer, int variable_bitcode, int CR_bitcode, TString control_region, TString variable_name) {
  int nSA = nSAMPLES;
  const TString *ssa=vsuff;
  TString presel_file;
  TString current_sample;

  TString CF = COINFLIP==1 ? "" : "_DC"; // coinflip is =1 for mutau and etau channels. It is =0 for tautau
  

  for (unsigned int is=0; is<=nSA; is++){ //loop over samples
      
    presel_file = path_presel+s_preselection+"_"+ssa[is]+CF+".root";
    current_sample = ssa[is];
    
    //if emb mode is used switch to the correct preselection file
    if((EMB==1 && ( presel_file.Contains("DY_J") || presel_file.Contains("DY_L") || presel_file.Contains("TT_J")  || presel_file.Contains("TT_L") || presel_file.Contains("VV_J") || presel_file.Contains("VV_L") )) ){
      presel_file = presel_file.ReplaceAll(".root", "_EMB.root");
    }
    if (is == nSA) {
      presel_file = preselection_data;
      current_sample = "data";
    }
    if(DEBUG) {std::cout<<"using preselection file: "<<presel_file<<std::endl;}

    
    Analyzer->getCRHisto(presel_file, variable_bitcode|CR_bitcode , path_sim+s_CR+"_"+control_region+"_"+variable_name+"_"+current_sample+".root"  );

    if( doNJetBinning ){
      Analyzer->getCRHisto(presel_file, variable_bitcode|CR_bitcode|JET0 , path_sim+s_CR+"_"+control_region+"_"+variable_name+"_0jet_"+current_sample+".root"  );
      Analyzer->getCRHisto(presel_file, variable_bitcode|CR_bitcode|JET1 , path_sim+s_CR+"_"+control_region+"_"+variable_name+"_1jet_"+current_sample+".root"  );
    }
    
  }

}


void ProduceMCsubtractedHistos (TString control_region, TString variable_name, TString AI_extension, TString Njet_extension, int variable_mask, int sub_all ) {
  TString modes[] = {"l","t"};
  Int_t nmodes = 2;
  const TString *ssa=vsuff;
  int nSA = nSAMPLES;

  TString input_filename  = path_sim+s_CR+"_"+control_region+"_"+variable_name+AI_extension+Njet_extension+"_data.root";
  TString output_filename = path_sim+s_CR+"_"+control_region+"_"+variable_name+AI_extension+Njet_extension+"_data_MCsubtracted.root";

  if (DEBUG) {std::cout << "loading: " << input_filename << " and creating file: " << output_filename << std::endl; }


  TFile outfile ( output_filename,"RECREATE"  );
  TFile infile( input_filename );
  
  for(int imode=0; imode<nmodes; imode++) {
    TH1D* inhist = (TH1D*)infile.Get("hh_"+modes[imode]+"_"+variable_name);
    TH1D* outhist = (TH1D*)inhist->Clone("hh_"+modes[imode]+"_"+variable_name+"_MCsubtracted"); 
    outhist->Add(inhist,-1);
    TH1D* dataminusMC = (TH1D*)inhist->Clone("hh_"+modes[imode]+"_"+variable_name+"_dataminusMC"); 

    for (int is=0; is<nSA; is++){ //loop over samples
      if((!sub_all) && (control_region == ssa[is])) continue;
      TFile tmp(path_sim+s_CR+"_"+control_region+"_"+variable_name+AI_extension+Njet_extension+"_"+ssa[is]+".root"  );
      TH1D *tmphist = (TH1D*)tmp.Get("hh_"+modes[imode]+"_"+variable_name);

      if(variable_mask & MUISO){
        for(int i=1; i<tmphist->GetNbinsX();i++){
          if( tmphist->GetBinContent(i) > inhist->GetBinContent(i) ){
            tmphist->SetBinContent(i,0);
            tmphist->SetBinError(i,0);
          }
          if(tmphist->GetBinContent(i) > 3){
            Double_t err1=tmphist->GetBinError(i)/tmphist->GetBinContent(i);
            Double_t err2=0.25;
            tmphist->SetBinError( i,TMath::Sqrt(TMath::Power(err1,2)+TMath::Power(err2,2))*tmphist->GetBinContent(i) );
          }
        }
      }

      outhist->Add(tmphist);
      dataminusMC->Add(tmphist,-1);

      tmp.Close();
    }
    for (int nBin=0;nBin<=dataminusMC->GetNbinsX();++nBin) {
      if (dataminusMC->GetBinContent(nBin)<0.0){ dataminusMC->SetBinContent(nBin, 0.0);}
    }

    outfile.cd();
    inhist->Write();
    outhist->Write();
    dataminusMC->Write();
  }
  infile.Close();
  outfile.Close();
}

void CRHisto(int doCalc, int nCR, int nQU) {
  std::cout << std::endl << "***************************************" << std::endl;
  std::cout << "*             CRHisto                 *" << std::endl;
  std::cout << "***************************************" << std::endl << std::endl;


  std::cout << "doCalc: " << doCalc << std::endl;
  std::cout << "nCR: " << nCR << std::endl;
  std::cout << "nQU: " << nQU << std::endl;
  

  TSelectionAnalyzer* Analyzer = new TSelectionAnalyzer();
  Analyzer->init();

  TString m_preselection_data=preselection_data;
  TString m_path_img=path_img_data;

  const int nVARused = nVARCR; //mt,mvis,pt,muiso
  const int ivar[4]={MT|NO_SR,MVIS,PT,MUISO};

  const int icr[nCR]=        {_W_JETS , _DY  , _TT  , _QCD};
  const TString scr[nCR]=    {s_Wjets, s_DY , s_TT , s_QCD};
  
  
  std::vector<TString> sjet; 
  if( doNJetBinning ) {
    sjet.push_back(""); 
    sjet.push_back("_0jet"); 
    sjet.push_back("_1jet");
  }
  else {
    sjet.push_back("");
  }

  int nSA = nSAMPLES;
  const TString *ssa=vsuff;

  const TString squ[nQU]=    {s_loose, s_tight};

  TString CF = COINFLIP==1 ? "" : "_DC"; // coinflip is =1 for mutau and etau channels. It is =0 for tautau

  TString presel_file = "";
  
  for (int ic=0; ic<nCR; ic++){ //loop over CRs - Wjets, DY, TT, QCD 
    for (int iv=0; iv<nVARused; iv++){ //loop over mt, mvis, pt, muiso
      CallCRHisto_creation (Analyzer, ivar[iv], icr[ic], scr[ic], tvarCR[iv]);  
    }
  }



  CallCRHisto_creation(Analyzer, 0, _W_JETS|MVIS|NO_SR, s_Wjets, "mvis_nosr" );

  //pick only QCD control region - produces ViennaTool/sim/channel/CR_QCD_lepPt_*.root but not the MCsubtracted one
  CallCRHisto_creation(Analyzer, 0, _QCD|LEPPT, s_QCD, "lepPt" );
  CallCRHisto_creation(Analyzer, 0, _W_JETS|LEPPT, s_Wjets, "lepPt" );

  
  //get AI CR histogramms for QCD mvis nonclosure
  CallCRHisto_creation(Analyzer, MVIS, _QCD|_AI, s_QCD, s_mvis+"_AI" );
  
  if(CHAN==kTAU){
    CallCRHisto_creation(Analyzer, 0, LEPPT|_QCD|_AI|JET0, s_QCD, "lepPt_AI" );
  }
  
  //get SS Wjet histogramms for SS mvis Wjets closure
  CallCRHisto_creation(Analyzer, MVIS, _W_JETS|_AI, s_Wjets, s_mvis+"_SS" );
  
  CallCRHisto_creation(Analyzer, LEPPT, _W_JETS|_AI, s_Wjets, "lepPt_SS" );
  
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //get Wjet SS histos for corrections
  Analyzer->getCRHisto(preselection_Wjets, MVIS|_W_JETS|_SS , path_sim+s_CR+"_Wjets_mvis_Wjets_SS_SR.root"  );
  Analyzer->getCRHisto(preselection_Wjets, MT|NO_SR|_W_JETS|_SS , path_sim+s_CR+"_Wjets_mt_Wjets_SS_SR.root"  );
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// void CallCRHisto_creation (TSelectionAnalyzer* Analyzer, int variable_bitcode, int CR_bitcode, TString control_region, TString variable_name) {
  // for (int ic=0; ic<nCR; ic++){ //loop over CRs
  //   for (int iv=0; iv<nVARused; iv++){ //loop over mt, mvis, pt, muiso
  //       for (int is=0; is<nSA; is++){ 
  //         Analyzer->getCRHisto(presel_file, ivar[iv]|icr[ic] , path_sim+s_CR+"_"+scr[ic]+"_"+tvarCR[iv]+"_"+ssa[is]+".root"  );
  //         Analyzer->getCRHisto(presel_file, icr[ic]|LEPPT    , path_sim+s_CR+"_"+scr[ic]+"_lepPt_"         +ssa[is]+".root"  );
  //         Analyzer->getCRHisto(presel_file, ivar[iv]|icr[ic]|_AI , path_sim+s_CR+"_"+scr[ic]+"_"+tvarCR[iv]+"_AI_"+ssa[is]+".root"  );
  //         Analyzer->getCRHisto(presel_file, LEPPT|icr[ic]|_AI , path_sim+s_CR+"_"+scr[ic]+"_lepPt_AI_"+ssa[is]+".root"  );
  //         Analyzer->getCRHisto(presel_file, ivar[iv]|icr[ic]|_AI , path_sim+s_CR+"_"+scr[ic]+"_"+tvarCR[iv]+"_SS_"+ssa[is]+".root"  );
  //     }
  //   }
  // }        
  // const int ivar[4]={MT|NO_SR,MVIS,PT,MUISO};
  // const int icr[nCR]=        {_W_JETS , _DY  , _TT  , _QCD};
  // const TString scr[nCR]=    {s_Wjets, s_DY , s_TT , s_QCD};
  // const TString tvarCR[nVARCR]={s_mt,s_mvis,s_pt,s_muiso}; defined in globals.h
  
  TString modes[] = {"l","t"};
  Int_t nmodes = 2;
  
  for (int ij=0; ij<=2*(doNJetBinning); ij++){ //loop over inclusive, 0jet, 1jet //Check if Njet binning is implemented
    ProduceMCsubtractedHistos(s_QCD  ,"lepPt",""   ,sjet[ij],0,0); //get QCD      lepPT MC subtracted CRs
    ProduceMCsubtractedHistos(s_Wjets  ,"lepPt",""   ,sjet[ij],0,0); //get QCD      lepPT MC subtracted CRs
    ProduceMCsubtractedHistos(s_QCD  ,s_mvis ,"_AI",sjet[ij],0,0); //get QCD   AI mvis  MC subtracted CRs
    ProduceMCsubtractedHistos(s_Wjets,s_mvis ,"_SS",sjet[ij],0,0); //get Wjets SS mvis  MC subtracted CRs
    ProduceMCsubtractedHistos(s_Wjets,"lepPt" ,"_SS",sjet[ij],0,1); //get Wjets SS mvis  MC subtracted CRs

  }
  
  for (int ic=0; ic<nCR; ic++){ //loop over CRs - Wjets, DY, TT and QCD
    for (int iv=0; iv<nVARused; iv++){ //loop over mt, mvis, pt, muiso
      for (int ij=0; ij<=2*(doNJetBinning); ij++){ //loop over inclusive, 0jet, 1jet
        ProduceMCsubtractedHistos(scr[ic],tvarCR[iv],"",sjet[ij],ivar[iv],0);
      }
    }
  }
  

  if(DEBUG) {std::cout << "Producing CR plots ..." << std::endl;}

  
  std::vector<TString> ty; 
  for (int it=0; it<nSA; it++) {
    ty.push_back(vsuff[it]);
  }

  for (int ic=0; ic<nCR; ic++){ //loop over CRs
    for (int iv=0; iv<nVARused; iv++){ //loop over mt, mvis, pt, muiso
      for (int iq=0; iq<nQU; iq++){ //loop over loose/tight
        std::vector<TString> cr; 
        for (int is=0; is<nSA; is++){ cr.push_back(path_sim+s_CR+"_"+scr[ic]+"_"+tvarCR[iv]+"_"+ssa[is]+".root"); }
        if(DEBUG) {
          cout << path_sim+s_CR+"_"+scr[ic]+"_"+tvarCR[iv]+"_data.root" << " " << squ[iq] << " " <<  scr[ic] << " " << m_path_img+s_CR+"_"+scr[ic]+"_"+squ[iq]+"_"+tvarCR[iv] << " " << tvarCR_l[iv]  << endl;
        }
        Analyzer->plotCR(cr, ty, path_sim+s_CR+"_"+scr[ic]+"_"+tvarCR[iv]+"_data.root", squ[iq], scr[ic]    , m_path_img+s_CR+"_"+scr[ic]+"_"+squ[iq]+"_"+tvarCR[iv], tvarCR_l[iv] ); 
      }
    }
  }

  // Plot AI CR:

  std::vector<TString> cr; 
  for (int is=0; is<nSA; is++){ cr.push_back(path_sim+s_CR+"_QCD_mvis_AI_"+ssa[is]+".root"); if(DEBUG){cout << "FNAME: "<< path_sim+s_CR+"_QCD_mvis_AI_"+ssa[is]+".root" << endl;} }
  for (int iq=0; iq<nQU; iq++){ //loop over loose/tight
    Analyzer->plotCR(cr, ty, path_sim+s_CR+"_QCD_mvis_AI_data.root", squ[iq], "QCD", m_path_img+s_CR+"_QCD_AI_"+squ[iq]+"_mvis", tvarCR_l[1] ); 
  }
  cr.clear();
 
  for (int is=0; is<nSA; is++){ cr.push_back(path_sim+s_CR+"_Wjets_mvis_SS_"+ssa[is]+".root"); if(DEBUG){cout << "FNAME: "<< path_sim+s_CR+"_Wjets_mvis_SS_"+ssa[is]+".root" << endl;} }
  for (int iq=0; iq<nQU; iq++){ //loop over loose/tight
    Analyzer->plotCR(cr, ty, path_sim+s_CR+"_Wjets_mvis_SS_data.root", squ[iq], "Wjets", m_path_img+s_CR+"_Wjets_SS_"+squ[iq]+"_mvis", tvarCR_l[1] ); 
  }
  cr.clear();
 
  
  for (int is=0; is<nSA; is++){ cr.push_back(path_sim+s_CR+"_QCD_lepPt_"+ssa[is]+".root"); if(DEBUG){ cout << "FNAME: "<< path_sim+s_CR+"_QCD_lepPt_"+ssa[is]+".root" << endl;} }
  for (int iq=0; iq<nQU; iq++){ //loop over loose/tight
    Analyzer->plotCR(cr, ty, path_sim+s_CR+"_QCD_lepPt_data.root", squ[iq], "QCD", m_path_img+s_CR+"_QCD_lepPt_"+squ[iq], tvar_l[3] ); 
  }
  cr.clear();
  
  if(CHAN == kTAU){
    for (int is=0; is<nSA; is++){ cr.push_back(path_sim+s_CR+"_QCD_lepPt_AI_"+ssa[is]+".root"); if(DEBUG){cout << "FNAME: "<< path_sim+s_CR+"_QCD_lepPt_AI_"+ssa[is]+".root" << endl;} }
    for (int iq=0; iq<nQU; iq++){ //loop over loose/tight
      Analyzer->plotCR(cr, ty, path_sim+s_CR+"_QCD_lepPt_AI_data.root", squ[iq], "QCD", m_path_img+s_CR+"_QCD_lepPt_AI_"+squ[iq], tvar_l[3] ); 
    }
  }
  cr.clear();
  
  //end of plots
  
  delete Analyzer;

  
}
  
#ifndef __CINT__
int main(int argc, char* argv[]) {
  int doCalc = argc > 1 ? atoi(argv[1]) : 1;
  int nCR = argc > 2 ? atoi(argv[2]) : 4;
  int nQU = argc > 3 ? atoi(argv[3]) : 3;
  CRHisto(doCalc,nCR,nQU);    
}
#endif

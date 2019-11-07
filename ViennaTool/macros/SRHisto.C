#include "ViennaTool/interface/TSelectionAnalyzer.h"

#include <iostream>
#include <string>
#include <tuple>

using namespace std;

std::tuple<std::vector<TString>,std::vector<TString>> FillPaths(std::vector<TString> ps, std::vector<TString> fl) {
  
  if( EMB==1 ){
    ps.push_back(preselection_data);
    ps.push_back(preselection_Wjets); 
    ps.push_back(preselection_EMB); 
    ps.push_back(preselection_TT_J_EMB); 
    ps.push_back(preselection_TT_L_EMB);
    ps.push_back(preselection_VV_J_EMB); 
    ps.push_back(preselection_VV_L_EMB);
    ps.push_back(preselection_DY_J_EMB); 
    ps.push_back(preselection_DY_L_EMB); 
    
    fl.push_back(SR_data_mt); 
    fl.push_back(SR_Wjets_mt_sim); 
    fl.push_back(SR_EMB_mt_sim); 
    fl.push_back(SR_TT_J_mt_sim); 
    fl.push_back(SR_TT_L_mt_sim);
    fl.push_back(SR_VV_J_mt_sim); 
    fl.push_back(SR_VV_L_mt_sim);
    fl.push_back(SR_DY_J_mt_sim); 
    fl.push_back(SR_DY_L_mt_sim); 
  }else{
    ps.push_back(preselection_data);
    ps.push_back(preselection_Wjets); 
    ps.push_back(preselection_TT_T); 
    ps.push_back(preselection_TT_J); 
    ps.push_back(preselection_TT_L);
    ps.push_back(preselection_VV_T); 
    ps.push_back(preselection_VV_J); 
    ps.push_back(preselection_VV_L);
    ps.push_back(preselection_DY_TT); 
    ps.push_back(preselection_DY_J); 
    ps.push_back(preselection_DY_L); 
    
    fl.push_back(SR_data_mt); 
    fl.push_back(SR_Wjets_mt_sim); 
    fl.push_back(SR_TT_T_mt_sim);
    fl.push_back(SR_TT_J_mt_sim); 
    fl.push_back(SR_TT_L_mt_sim);
    fl.push_back(SR_VV_T_mt_sim); 
    fl.push_back(SR_VV_J_mt_sim); 
    fl.push_back(SR_VV_L_mt_sim);
    fl.push_back(SR_DY_TT_mt_sim); 
    fl.push_back(SR_DY_J_mt_sim); 
    fl.push_back(SR_DY_L_mt_sim); 
  }
  return std::make_tuple(ps,fl);

}

int ProduceMCsubtracted (TString variable_name, TString extension) {
  TString modes[] = {"l","t"}; // the 2 modes are l(oose) and t(ight) where FF is defined via t / l&!t
  Int_t nmodes = sizeof(modes) / sizeof(*modes);

  int nSA = nSAMPLES; // depends on EMB or nonEMB
  const TString *ssa=vsuff;

  TString outfile_name = path_sim+s_SR+"_data"+variable_name+extension+"_MCsubtracted.root";
  TString infile_name  = path_sim+s_SR+"_data"+variable_name+extension+".root";

  TFile outfile ( outfile_name,"RECREATE"  );
  if (DEBUG) {
    cout << "WRITING: " << outfile_name << " from input file:" << endl;
    cout << infile_name << endl;
  }

  TFile infile( infile_name  );
  //check if infile exists
  if(infile.IsZombie() ){ 
    std::cout << "\033[1;36m INFO: \033[0m" << infile_name << " not available - breaking now" << std::endl; 
    return 0;
  }
  
  for(int imode=0; imode<nmodes; imode++){ // loop over tight and loose selection modi
    TH1D* inhist = (TH1D*)infile.Get("hh_"+modes[imode]+variable_name);
    TH1D* outhist = (TH1D*)inhist->Clone("hh_"+modes[imode]+variable_name+"_MCsubtracted"); 
    TH1D* outhist2 = (TH1D*)inhist->Clone("hh_"+modes[imode]+variable_name+"_dataminusMC"); 
    
    // trick to get correct binning
    outhist->Add(inhist,-1);
    outhist2->Add(inhist,-1);
    outhist2->Add(inhist);
    
    for (int is=0; is<nSA; is++){ //loop over samples
      cout << "WRITING: " << path_sim+s_SR+"_"+ssa[is]+variable_name+extension+".root" << endl;
      TFile tmp(path_sim+s_SR+"_"+ssa[is]+variable_name+extension+".root"  );
      if(tmp.IsZombie() ){
        cout << path_sim+s_SR+"_"+ssa[is]+variable_name+extension+".root" << " not available"<<  endl; 
        continue;
      }
      TH1D *tmphist = (TH1D*)tmp.Get("hh_"+modes[imode]+variable_name);
      
      outhist->Add(tmphist);
      outhist2->Add(tmphist,-1);
      tmp.Close();
    }
    outfile.cd();
    inhist->Write();
    outhist->Write();
    outhist2->Write();
  }
  infile.Close();
  outfile.Close();
  return 1;
}


void SRHisto() {

  std::cout << std::endl << "***************************************" << std::endl;
  std::cout << "*             SRHisto                 *" << std::endl;
  std::cout << "***************************************" << std::endl << std::endl;

  
  TSelectionAnalyzer *Analyzer = new TSelectionAnalyzer();
  
  Analyzer->init();

  std::vector<TString> ps; // preselection path
  std::vector<TString> fl; // path to SR histos - to be found out more
  std::tie(ps,fl) = FillPaths(ps,fl);
  
  
  Int_t nVARused = nVAR-1; //nVAR = 5 (Globals.h) no muiso is needed here
  
  const TString r1[nVARused]={"_pt","_mt","_mvis"}; //
  const TString r2[nVARused]={ "_mt", "_mvis", "_pt"}; //"_mt2","_lepPt","_mvamet","_met","_eta", "_mttot","_mjj"};
  const TString discrim_var[nVAR] = {"_mt", "_mvis", "_pt","_eta"};
  Int_t n_discrim_var = sizeof(discrim_var) / sizeof(*discrim_var);

  TString tmp,tmp2;
  for (unsigned i=0; i<ps.size(); i++){ // loop over all preselection paths to root files
    
    tmp=fl.at(i); //avoid editing fl
    Int_t categoryMode=0;

    if (DEBUG) {std::cout << "Loading preselection file: " << ps.at(i) << std::endl;}
    
    Analyzer->calcBgEstSim( ps.at(i), MT|NO_SR, categoryMode, tmp.ReplaceAll(r1[0], r2[0]) ); // MT|NO_SR =   
    Analyzer->calcBgEstSim( ps.at(i), MVIS, categoryMode, tmp.ReplaceAll(r1[1],r2[1]) );
    Analyzer->calcBgEstSim( ps.at(i), PT, categoryMode, tmp.ReplaceAll(r1[2],r2[2]) );
    
    tmp=fl.at(i); 
    Analyzer->calcBgEstSim( ps.at(i), MVIS|_AI, categoryMode, tmp.ReplaceAll(r2[0], "_mvis_AI") );
    
    if(use_svfit){
      tmp=fl.at(i); 
      Analyzer->calcBgEstSim( ps.at(i), SVFIT, categoryMode, tmp.ReplaceAll(r2[0], "_svfit"));
    }
    
    
  }
  delete Analyzer;

  //Get all histos with MC subtracted
  for (unsigned int ivar=0; ivar < n_discrim_var; ivar++) {
    ProduceMCsubtracted(discrim_var[ivar],"");
    if (discrim_var[ivar] == "_mvis") { // Get AI mvis histos with MC subtracted
      ProduceMCsubtracted(discrim_var[ivar],"_AI");
    }
  }
  
}
  
#ifndef __CINT__
int main(int argc, char* argv[]) {
  SRHisto();    
}
#endif

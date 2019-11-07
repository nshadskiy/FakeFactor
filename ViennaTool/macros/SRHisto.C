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

void SRHisto() {

  std::cout << std::endl << "***************************************" << std::endl;
  std::cout << "*             SRHisto                 *" << std::endl;
  std::cout << "***************************************" << std::endl << std::endl;

  const Int_t DOCUTS = doCuts;
  std::cout << "doCuts: " << doCuts << std::endl;
  std::cout << "inclusive_selection: " << inclusive_selection << std::endl;
  std::cout << "DOQCD: " << DOQCD << std::endl;
  
  
 
  
  TSelectionAnalyzer *Analyzer = new TSelectionAnalyzer();
  
  Analyzer->init();

  std::vector<TString> ps; // preselection path
  std::vector<TString> fl; // path to SR histos - to be found out more
  std::tie(ps,fl) = FillPaths(ps,fl);
  
  
  Int_t nVARused = nVAR-1; //nVAR = 5 (Globals.h) no muiso is needed here
  
  const TString r1[nVARused]={"_pt","_mt","_mvis"}; //
  const TString r2[nVARused]={ "_mt", "_mvis", "_pt"}; //"_mt2","_lepPt","_mvamet","_met","_eta", "_mttot","_mjj"};
  const TString discrim_var[nVAR] = {"_mt", "_mvis", "_pt","_eta"};

  TString tmp,tmp2;
  for (unsigned i=0; i<ps.size(); i++){ // loop over all preselection paths to root files
    
    tmp=fl.at(i); //avoid editing fl
    Int_t categoryMode=0;

    std::cout << "preselection file: " << ps.at(i) << std::endl;
    
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
  
   
  TString modes[] = {"l","t"};
  Int_t nmodes = sizeof(modes) / sizeof(*modes);
  Int_t n_discrim_var = sizeof(discrim_var) / sizeof(*discrim_var);
  
  
  int nSA; // number of samples
  nSA=nSAMPLES; // depends on EMB or nonEMB
  const TString *ssa=vsuff;
  
  //////////////////////////////////////////////////////////////////////////////////////////////////////
  //Get AI mvis histos with MC subtracted for the moment they are only computed for mvis
  for (int iv=0; iv<n_discrim_var; iv++){ //loop over the discriminating variables
    if (iv != 1) { // select only mvis for the moment
      continue;
    }

    TFile outfile ( path_sim+s_SR+"_data"+discrim_var[iv]+"_AI_MCsubtracted.root","RECREATE"  );
    cout << "WRITING: " << path_sim+s_SR+"_data"+discrim_var[iv]+"_AI_MCsubtracted.root" << " from input file:" << endl;
    cout << path_sim+s_SR+"_data"+discrim_var[iv]+"_AI.root" << endl;
    TFile infile( path_sim+s_SR+"_data"+discrim_var[iv]+"_AI.root"  );
    
    if(infile.IsZombie() ){
      cout << "\033[1;36m INFO: \033[0m"+path_sim+s_SR+"_data"+discrim_var[iv]+"_AI.root" << " not available" << endl; 
      break;
    }
    
    for(int imode=0; imode<nmodes; imode++){
      TH1D* inhist = (TH1D*)infile.Get("hh_"+modes[imode]+"_mvis");
      TH1D* outhist = (TH1D*)inhist->Clone("hh_"+modes[imode]+"_mvis_MCsubtracted"); outhist->Add(inhist,-1);
      for (int is=0; is<nSA; is++){ //loop over samples
        if(ssa[is]=="QCD") continue;
        cout << "WRITING: " << path_sim+s_SR+"_"+ssa[is]+discrim_var[iv]+"_AI.root" << endl;
        TFile tmp(path_sim+s_SR+"_"+ssa[is]+discrim_var[iv]+"_AI.root"  );
        if(tmp.IsZombie() ){cout << path_sim+s_SR+"_"+ssa[is]+discrim_var[iv]+"_AI.root" << " not available"<<  endl; continue;}
        TH1D *tmphist = (TH1D*)tmp.Get("hh_"+modes[imode]+discrim_var[iv]);
        
        outhist->Add(tmphist);
        tmp.Close();
      }
      outfile.cd();
      inhist->Write();
      outhist->Write();
    }
    infile.Close();outfile.Close();
    
  }
  
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////
  //Get all histos with MC subtracted
  nVARused=3;
  for (int iv=0; iv<nVARused; iv++){ //loop over mt, mvis, pt
    std::cout<<r2[iv]<<std::endl;
    TFile outfile ( path_sim+s_SR+"_data"+r2[iv]+"_MCsubtracted.root","RECREATE"  );
    TFile infile( path_sim+s_SR+"_data"+r2[iv]+".root"  );
    if(infile.IsZombie() ){cout << path_sim+s_SR+"_data"+r2[iv]+".root" << " not available" << endl; break;}
    for(int imode=0; imode<nmodes; imode++){
      TH1D* inhist = (TH1D*)infile.Get("hh_"+modes[imode]+r2[iv]);
      TH1D* outhist = (TH1D*)inhist->Clone("hh_"+modes[imode]+"_"+r2[iv]+"MCsubtracted"); outhist->Add(inhist,-1);
      for (int is=0; is<nSA; is++){ //loop over samples
        if(ssa[is]=="QCD") continue;
        TFile tmp(path_sim+s_SR+"_"+ssa[is]+r2[iv]+".root"  );
        if(tmp.IsZombie() ){cout << path_sim+s_SR+"_"+ssa[is]+r2[iv]+".root" << " not available"<<  endl; continue;}
        TH1D *tmphist = (TH1D*)tmp.Get("hh_"+modes[imode]+r2[iv]);
        outhist->Add(tmphist);
        tmp.Close();
      }
      outfile.cd();
      inhist->Write();
      outhist->Write();
    }
    infile.Close();outfile.Close();
  }
  
    
    
  
      
  


  
}
  
#ifndef __CINT__
int main(int argc, char* argv[]) {
  SRHisto();    
}
#endif

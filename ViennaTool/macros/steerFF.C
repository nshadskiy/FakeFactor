#include "ViennaTool/interface/FFCalculator.h"
#include "ViennaTool/src/FFCalculator.cc"

#include <iostream>
#include <string>

using namespace std;

void CalcFF() {

  std::cout << std::endl << "***************************************" << std::endl;
  std::cout << "*             Calculate Fakefactor    *" << std::endl;
  std::cout << "***************************************" << std::endl << std::endl;

  
  TString pi=path_img_data;       
  TString p=path_ff_data;       
  TString m_preselection_data=preselection_data;        
  TString m_SR_data=SR_data;        
  TString m_label="data"; 

  TString pmc=path_ff_mc;             
  TString psmc=preselection_MCsum; 

  if ( CHAN!=kMU ) {
    pmc=path_ff_mc_woQCD;
    psmc=preselection_MCsum_woQCD;
  }

  int m_gen_match=0;
  

  
  
  FFCalculator* Analyzer = new FFCalculator(N_p_Wjets,N_p_DY,N_p_TT_SR,N_p_TT_CR,N_p_QCD,N_p_QCD_AI,
                                            N_e_Wjets,N_e_DY,N_e_TT,N_e_QCD,
                                            N_t_Wjets,N_t_DY,N_t_TT,N_t_QCD,
                                            N_m_Wjets,N_m_DY,N_m_TT,N_m_QCD,
                                            N_j_Wjets,N_j_DY,N_j_TT_SR,N_j_TT_CR,N_j_QCD,
                                            Pt_cuts_Wjets,Pt_cuts_DY,Pt_cuts_TT_SR,Pt_cuts_TT_CR,Pt_cuts_QCD,Pt_cuts_QCD_AI,
                                            Eta_cuts_Wjets,Eta_cuts_DY,Eta_cuts_TT,Eta_cuts_QCD,
                                            Decay_cuts_Wjets,Decay_cuts_DY,Decay_cuts_TT,Decay_cuts_QCD,
                                            Mt_cuts_Wjets,Mt_cuts_DY,Mt_cuts_TT,Mt_cuts_QCD,
                                            Njet_cuts_Wjets,Njet_cuts_DY,Njet_cuts_TT_SR,Njet_cuts_TT_CR,Njet_cuts_QCD
                                            );
  
  Analyzer->init();
  
  std::vector<TString> wf; 
  wf.push_back(p+a_weight[0]); wf.push_back(p+a_weight[1]); wf.push_back(p+a_weight[2]); // This is old code where fractions were computed directly inside the FF framework
  
  
  // Fill the vector ps with the paths to the different preselection files
  std::vector<TString> ps; 
  ps.push_back(preselection_Wjets); ps.push_back(preselection_DY_J); ps.push_back(preselection_TT_J_EMB); 
  ps.push_back(preselection_DY_TT); ps.push_back(preselection_DY_L); ps.push_back(preselection_TT_T); ps.push_back(preselection_TT_L);
  ps.push_back(preselection_VV_T); ps.push_back(preselection_VV_L);


  std::vector<TString> pre_sub_wj;
  std::vector<TString> pre_sub_tt; 
  std::vector<TString> pre_sub_qcd;
  
  //definition of backgrounds to be subtracted:
  pre_sub_wj.push_back(preselection_DY); pre_sub_wj.push_back(preselection_TT); pre_sub_wj.push_back(preselection_VV);
  pre_sub_tt.push_back(preselection_DY); pre_sub_tt.push_back(preselection_Wjets); pre_sub_tt.push_back(preselection_TT_T); pre_sub_tt.push_back(preselection_TT_L); pre_sub_tt.push_back(preselection_VV);
  pre_sub_qcd.push_back(preselection_DY); pre_sub_qcd.push_back(preselection_Wjets); pre_sub_qcd.push_back(preselection_TT); pre_sub_qcd.push_back(preselection_VV);

  
  
  if( EMB ){
      //EMBEDDING
      pre_sub_wj.clear(); 
      pre_sub_wj.push_back(preselection_EMB); pre_sub_wj.push_back(preselection_DY_J_EMB); pre_sub_wj.push_back(preselection_DY_L_EMB); pre_sub_wj.push_back(preselection_TT_J_EMB); pre_sub_wj.push_back(preselection_TT_L_EMB); pre_sub_wj.push_back(preselection_VV_J_EMB); pre_sub_wj.push_back(preselection_VV_L_EMB);

      pre_sub_tt.clear();
      pre_sub_tt.push_back(preselection_EMB); pre_sub_tt.push_back(preselection_Wjets); pre_sub_tt.push_back(preselection_DY_J_EMB); pre_sub_tt.push_back(preselection_DY_L_EMB); pre_sub_tt.push_back(preselection_TT_L_EMB); pre_sub_tt.push_back(preselection_VV_J_EMB); pre_sub_tt.push_back(preselection_VV_L_EMB);
      
      pre_sub_qcd.clear();
      pre_sub_qcd.push_back(preselection_EMB); pre_sub_qcd.push_back(preselection_Wjets); pre_sub_qcd.push_back(preselection_DY_J_EMB); pre_sub_qcd.push_back(preselection_DY_L_EMB); pre_sub_qcd.push_back(preselection_TT_J_EMB); pre_sub_qcd.push_back(preselection_TT_L_EMB); pre_sub_qcd.push_back(preselection_VV_J_EMB); pre_sub_qcd.push_back(preselection_VV_L_EMB);
  }
  if (CHAN!=kTAU){
    cout << endl << "################### Calculating FFs         ###############" << endl << endl;
    
    cout << "Calculating TT FFs" << endl; 
    Analyzer->calcFFCorr(_TT|m_gen_match,                        m_preselection_data,   pre_sub_tt,          p+FF_corr_TT_MCsum_noGen,     p+weight_TT_J);   
    Analyzer->calcFFCorr(_TT|m_gen_match,                        preselection_TT_J_EMB,     empty_vec_tstring,   p+FF_TT_J_only,               p+weight_TT_J);
    Analyzer->calcFFCorr(_TT|m_gen_match|SR,                     preselection_TT_J_EMB,     empty_vec_tstring,   p+FF_TT_J_only_SR,            p+weight_TT_J);

    
    cout << "Calculating W+Jets FFs" << endl;
    Analyzer->calcFFCorr(_W_JETS|m_gen_match,                    m_preselection_data,   pre_sub_wj,          p+FF_corr_Wjets_MCsum_noGen,  p+weight_Wjets);
    Analyzer->calcFFCorr(_W_JETS|m_gen_match,                    preselection_Wjets,    empty_vec_tstring,   p+FF_corr_Wjets_MC_noGen,     p+weight_Wjets);
  
    cout << "Calculating QCD FFs" << endl;
    Analyzer->calcFFCorr(_QCD|m_gen_match,                       m_preselection_data,   pre_sub_qcd,         p+FF_corr_QCD_MCsum_noGen,    p+weight_QCD);
    if( EMB ){
      pre_sub_qcd.clear();
      pre_sub_qcd.push_back(preselection_DY_EMB); pre_sub_qcd.push_back(preselection_Wjets); pre_sub_qcd.push_back(preselection_TT_T_EMB); pre_sub_qcd.push_back(preselection_TT_J_EMB); pre_sub_qcd.push_back(preselection_TT_L_EMB); pre_sub_qcd.push_back(preselection_VV_T_EMB); pre_sub_qcd.push_back(preselection_VV_L_EMB); pre_sub_qcd.push_back(preselection_VV_J_EMB);
      
    }
    Analyzer->calcFFCorr(_QCD|m_gen_match|_AI,                   m_preselection_data,   pre_sub_qcd,         p+FF_corr_QCD_MCsum_noGen_AI, p+weight_QCD);
  }
  else { // in the tt channel there are only QCD fake factors
    Analyzer->calcFFCorr(_QCD|m_gen_match,                       m_preselection_data,   pre_sub_qcd,         p+FF_corr_QCD_MCsum_noGen,    p+weight_QCD);
    if( EMB ){
      pre_sub_qcd.clear();
      pre_sub_qcd.push_back(preselection_DY_EMB); pre_sub_qcd.push_back(preselection_Wjets); pre_sub_qcd.push_back(preselection_TT_T_EMB); pre_sub_qcd.push_back(preselection_TT_J_EMB); pre_sub_qcd.push_back(preselection_TT_L_EMB); pre_sub_qcd.push_back(preselection_VV_T_EMB); pre_sub_qcd.push_back(preselection_VV_L_EMB); pre_sub_qcd.push_back(preselection_VV_J_EMB);
      
    }
    Analyzer->calcFFCorr(_QCD|m_gen_match|_AI,                   m_preselection_data,   pre_sub_qcd,         p+"FF_corr_QCD_MCsum_noGen_AI.root", p+weight_QCD);
  }
  
  

  if(CHAN==kMU){
    Analyzer->plotFF(p+FF_corr_TT_MCsum_noGen,    p+FF_TT_J_only,    _TT, pi+"ff_TT_CR_data_vs_MC"   ,"FF in TT CR(data #mu#tau)", "FF in TT CR(sim #mu#tau)");
  }
  if(CHAN==kEL){
    Analyzer->plotFF(p+FF_corr_TT_MCsum_noGen,    p+FF_TT_J_only,    _TT, pi+"ff_TT_CR_data_vs_MC"   ,"FF in TT CR(data e#tau)", "FF in TT CR(sim e#tau)");
  }

  
  delete Analyzer;

  
}
  
#ifndef __CINT__
int main(int argc, char* argv[]) {
  CalcFF();    
}
#endif



// some print statements:
  // std::cout << "N_p_Wjets: " << N_p_Wjets << std::endl;
  // std::cout << "sizeof(Pt_cuts_Wjets): " << sizeof(Pt_cuts_Wjets) << std::endl;
  // std::cout << "sizeof(Double_t): " << sizeof(Double_t) << std::endl; 


  // std::cout << "N_p_Wjets: " << N_p_Wjets << std::endl;
  // std::cout << "N_p_DY: " << N_p_DY << std::endl;
  // std::cout << "N_p_TT_SR: " << N_p_TT_SR << std::endl;
  // std::cout << "N_p_TT_CR: " << N_p_TT_CR << std::endl;
  // std::cout << "N_p_QCD: " << N_p_QCD << std::endl;
  // std::cout << "N_p_QCD_AI: " << N_p_QCD_AI << std::endl;

  // std::cout << "N_e_Wjets: " << N_e_Wjets << std::endl;
  // std::cout << "N_e_DY: " << N_e_DY << std::endl;
  // std::cout << "N_e_TT: " << N_e_TT << std::endl;
  // std::cout << "N_e_QCD: " << N_e_QCD << std::endl;

  // std::cout << "N_t_Wjets: " << N_t_Wjets << std::endl;
  // std::cout << "N_t_DY: " << N_t_DY << std::endl;
  // std::cout << "N_t_TT: " << N_t_TT << std::endl;
  // std::cout << "N_t_QCD: " << N_t_QCD << std::endl;

  // std::cout << "N_m_Wjets: " << N_m_Wjets << std::endl;
  // std::cout << "N_m_DY: " << N_m_DY << std::endl;
  // std::cout << "N_m_TT: " << N_m_TT << std::endl;
  // std::cout << "N_m_QCD: " << N_m_QCD << std::endl;

  // std::cout << "N_j_Wjets: " << N_j_Wjets << std::endl;
  // std::cout << "N_j_DY: " << N_j_DY << std::endl;
  // std::cout << "N_j_TT_SR: " << N_j_TT_SR << std::endl;
  // std::cout << "N_j_TT_CR: " << N_j_TT_CR << std::endl;
  // std::cout << "N_j_QCD: " << N_j_QCD << std::endl;

  // std::cout << "Pt_cuts_Wjets: " << Pt_cuts_Wjets << std::endl;
  // std::cout << "Pt_cuts_DY: " << Pt_cuts_DY << std::endl;
  // std::cout << "Pt_cuts_TT_SR: " << Pt_cuts_TT_SR << std::endl;
  // std::cout << "Pt_cuts_TT_CR: " << Pt_cuts_TT_CR << std::endl;
  // std::cout << "Pt_cuts_QCD: " << Pt_cuts_QCD << std::endl;
  // std::cout << "Pt_cuts_QCD_AI: " << Pt_cuts_QCD_AI << std::endl;

  // std::cout << "Eta_cuts_Wjets: " << Eta_cuts_Wjets << std::endl;
  // std::cout << "Eta_cuts_DY: " << Eta_cuts_DY << std::endl;
  // std::cout << "Eta_cuts_TT: " << Eta_cuts_TT << std::endl;
  // std::cout << "Eta_cuts_QCD: " << Eta_cuts_QCD << std::endl;

  // std::cout << "Decay_cuts_Wjets: " << Decay_cuts_Wjets << std::endl;
  // std::cout << "Decay_cuts_DY: " << Decay_cuts_DY << std::endl;
  // std::cout << "Decay_cuts_TT: " << Decay_cuts_TT << std::endl;
  // std::cout << "Decay_cuts_QCD: " << Decay_cuts_QCD << std::endl;

  // std::cout << "Mt_cuts_Wjets: " << Mt_cuts_Wjets << std::endl;
  // std::cout << "Mt_cuts_DY: " << Mt_cuts_DY << std::endl;
  // std::cout << "Mt_cuts_TT: " << Mt_cuts_TT << std::endl;
  // std::cout << "Mt_cuts_QCD: " << Mt_cuts_QCD << std::endl;

  // std::cout << "Njet_cuts_Wjets: " << Njet_cuts_Wjets << std::endl;
  // std::cout << "Njet_cuts_DY: " << Njet_cuts_DY << std::endl;
  // std::cout << "Njet_cuts_TT_SR: " << Njet_cuts_TT_SR << std::endl;
  // std::cout << "Njet_cuts_TT_CR: " << Njet_cuts_TT_CR << std::endl;
  // std::cout << "Njet_cuts_QCD: " << Njet_cuts_QCD << std::endl;

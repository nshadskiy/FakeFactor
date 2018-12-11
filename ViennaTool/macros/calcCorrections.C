#include "ViennaTool/interface/FFCalculator.h"
#include "ViennaTool/src/FFCalculator.cc"

#include <iostream>
#include <string>

using namespace std;

void calcCorrections() {

  std::cout << std::endl << "***************************************" << std::endl;
  std::cout << "*     Calculating Corrections         *" << std::endl;
  std::cout << "***************************************" << std::endl << std::endl;

  
  TString p, pi;
  TString m_preselection_data;
  TString m_SR_data;
  TString m_label;
  if      ( DOMC  &&  DOQCD                 ){ pi=path_img_mc;         p=path_ff_mc;         m_preselection_data=preselection_MCsum;       m_SR_data=SR_MCsum;       m_label="sim";  }
  else if ( !DOMC                           ){ pi=path_img_data;       p=path_ff_data;       m_preselection_data=preselection_data;        m_SR_data=SR_data;        m_label="data"; }
  else if ( DOMC  && ( !DOQCD || CHAN!=kMU) ){ pi=path_img_mc_woQCD;   p=path_ff_mc_woQCD;   m_preselection_data=preselection_MCsum_woQCD; m_SR_data=SR_MCsum_woQCD; m_label="sim";  }

  TString pmc=path_ff_mc;             if ( ( !DOQCD && DOMC ) || CHAN!=kMU ) pmc=path_ff_mc_woQCD;
  TString psmc=preselection_MCsum;    if ( ( !DOQCD && DOMC ) || CHAN!=kMU ) psmc=preselection_MCsum_woQCD;

  int m_gen_match=0;
  if (requireGenMatch_whenCalcFF) m_gen_match=GEN_MATCH;



  
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

  cout << "Calculating QCD and W+jets corrections" << endl;
  if(!DOMC && CHAN!=kTAU){
    Analyzer->loadFile(m_preselection_data,"Events");
    Analyzer->calc_nonclosure(_QCD,                               p+FF_corr_QCD_MCsum_noGen_fitted,      CR_QCD_mvis_data_MCsubtracted, p+FF_corr_QCD_MCsum_noGen_nonclosure,"",0);
    //Analyzer->calc_nonclosure(_QCD,                               p+FF_corr_QCD_MCsum_noGen_fitted,      CR_QCD_mvis_data_MCsubtracted, p+FF_corr_QCD_MCsum_noGen_nonclosure,"_alt",0);

    cout << "Analysizer->calc_nonclosure( " << _W_JETS << " " << p+FF_corr_Wjets_MCsum_noGen_fitted << " " << CR_Wjets_mvis_data_MCsubtracted << " " << p+FF_corr_Wjets_MCsum_noGen_nonclosure << " 0" << endl;
    Analyzer->calc_nonclosure(_W_JETS,                            p+FF_corr_Wjets_MCsum_noGen_fitted,    CR_Wjets_mvis_data_MCsubtracted, p+FF_corr_Wjets_MCsum_noGen_nonclosure,"",0);
    //Analyzer->calc_nonclosure(_W_JETS,                            p+FF_corr_Wjets_MCsum_noGen_fitted,    CR_Wjets_mvis_data_MCsubtracted, p+FF_corr_Wjets_MCsum_noGen_nonclosure,"_alt",0);
    Analyzer->calc_muisocorr(_QCD|MUISO,                          p+FF_corr_QCD_MCsum_noGen_fitted,      CR_QCD_muiso_data_MCsubtracted, p+FF_corr_QCD_MCsum_noGen_nonclosure, p+FF_corr_QCD_MCsum_noGen_muisocorr,"",0);
    //Analyzer->calc_muisocorr(_QCD|MUISO,                          p+FF_corr_QCD_MCsum_noGen_fitted,      CR_QCD_muiso_data_MCsubtracted, p+FF_corr_QCD_MCsum_noGen_nonclosure, p+FF_corr_QCD_MCsum_noGen_muisocorr,"_alt",0);
    Analyzer->calc_nonclosure(_QCD|_AI,                           p+FF_corr_QCD_MCsum_noGen_AI_fitted,   CR_QCD_mvis_AI_data_MCsubtracted, p+FF_corr_QCD_MCsum_noGen_nonclosure_AI, "",0);
    //Analyzer->calc_nonclosure(_QCD|_AI,                           p+FF_corr_QCD_MCsum_noGen_AI_fitted,   CR_QCD_mvis_AI_data_MCsubtracted, p+FF_corr_QCD_MCsum_noGen_nonclosure_AI, "_alt",0);
    Analyzer->calc_OSSScorr(_QCD|_AI,                             p+FF_corr_QCD_MCsum_noGen_AI_fitted,   SR_data_mvis_AI_MCsubtracted, p+FF_corr_QCD_MCsum_noGen_nonclosure_AI, p+FF_corr_QCD_MCsum_noGen_OSSScorr,"",0);
    //Analyzer->calc_OSSScorr(_QCD|_AI,                             p+FF_corr_QCD_MCsum_noGen_AI_fitted,   SR_data_mvis_AI_MCsubtracted, p+FF_corr_QCD_MCsum_noGen_nonclosure_AI, p+FF_corr_QCD_MCsum_noGen_OSSScorr, "_alt",0);
    
    Analyzer->loadFile(preselection_Wjets,"Events");
    Analyzer->calc_nonclosure(_W_JETS,                           p+FF_corr_Wjets_MC_noGen_fitted,        CR_Wjets_mvis_Wjets, p+FF_corr_Wjets_MC_noGen_nonclosure, "", 0, 0);
    //Analyzer->calc_nonclosure(_W_JETS,                           p+FF_corr_Wjets_MC_noGen_fitted,        CR_Wjets_mvis_Wjets, p+FF_corr_Wjets_MC_noGen_nonclosure, "_alt", 0, 0);
    Analyzer->loadFile(preselection_Wjets,"Events");
    Analyzer->calc_mtcorr(_W_JETS|NO_SR,                         p+FF_corr_Wjets_MC_noGen_fitted,        CR_Wjets_mt_Wjets, p+FF_corr_Wjets_MC_noGen_nonclosure, p+FF_corr_Wjets_MC_noGen_mtcorr,"",0);
    //Analyzer->calc_mtcorr(_W_JETS|NO_SR,                         p+FF_corr_Wjets_MC_noGen_fitted,        CR_Wjets_mt_Wjets, p+FF_corr_Wjets_MC_noGen_nonclosure, p+FF_corr_Wjets_MC_noGen_mtcorr, "_alt",0);
    
  }
  else cout << "FIXME: Reasonable corrections for MC closure if enough statistics" << endl;
  if(CHAN!=kTAU){
    cout << "Calculating TT corrections" << endl;
    Analyzer->loadFile(preselection_TT_J,"Events");
    Analyzer->calc_nonclosure(_TT|SR,                            p+FF_TT_J_only_SR_fitted,               SR_TT_J_mvis_sim, p+FF_corr_TT_MC_noGen_nonclosure, "", 0, 0);
    //Analyzer->calc_nonclosure(_TT|SR,                            p+FF_TT_J_only_SR_fitted,               SR_TT_J_mvis_sim, p+FF_corr_TT_MC_noGen_nonclosure, "_alt", 0, 0);
    //...done
  }

  if(CHAN==kTAU){
    Analyzer->loadFile(preselection_data,"Events");
    Analyzer->calc_nonclosure(_QCD,                             p+FF_corr_QCD_MCsum_noGen_fitted,        CR_QCD_mvis_data_MCsubtracted,    p+FF_corr_QCD_MCsum_noGen_nonclosure,"",0);
    Analyzer->calc_nonclosure(_QCD|_AI,                         p+FF_corr_QCD_MCsum_noGen_AI_fitted,     CR_QCD_mvis_AI_data_MCsubtracted, p+FF_corr_QCD_MCsum_noGen_nonclosure_AI,"",0);
    Analyzer->calc_OSSScorr(_QCD|_AI,                           p+FF_corr_QCD_MCsum_noGen_AI_fitted,     SR_data_mvis_AI_MCsubtracted,     p+FF_corr_QCD_MCsum_noGen_nonclosure_AI, p+FF_corr_QCD_MCsum_noGen_OSSScorr,"",0);
    Analyzer->calc_nonclosure_lepPt(_QCD,                       p+FF_corr_QCD_MCsum_noGen_fitted,        CR_QCD_lepPt_data_MCsubtracted,   p+FF_corr_QCD_MCsum_noGen_nonclosure,    p+FF_corr_QCD_MCsum_noGen_nonclosure_lepPt,"",0);
    //Analyzer->calc_nonclosure(_QCD,                             p+FF_corr_QCD_MCsum_noGen_fitted,        CR_QCD_mvis_data_MCsubtracted,    p+FF_corr_QCD_MCsum_noGen_nonclosure,"_alt",0);
    //Analyzer->calc_nonclosure(_QCD|_AI,                         p+FF_corr_QCD_MCsum_noGen_AI_fitted,     CR_QCD_mvis_AI_data_MCsubtracted, p+FF_corr_QCD_MCsum_noGen_nonclosure_AI,"_alt", 0);
    //Analyzer->calc_OSSScorr(_QCD|_AI,                           p+FF_corr_QCD_MCsum_noGen_AI_fitted,     SR_data_mvis_AI_MCsubtracted,     p+FF_corr_QCD_MCsum_noGen_nonclosure_AI, p+FF_corr_QCD_MCsum_noGen_OSSScorr,"_alt",0);
    //Analyzer->calc_nonclosure_lepPt(_QCD,                       p+FF_corr_QCD_MCsum_noGen_fitted,        CR_QCD_lepPt_data_MCsubtracted,   p+FF_corr_QCD_MCsum_noGen_nonclosure,    p+FF_corr_QCD_MCsum_noGen_nonclosure_lepPt,"_alt",0);
  }
        
  
}
  
#ifndef __CINT__
int main(int argc, char* argv[]) {
  calcCorrections();    
}
#endif

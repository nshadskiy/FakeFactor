#include "ViennaTool/interface/FFCalculator.h"
#include "ViennaTool/src/FFCalculator.cc"

#include <iostream>
#include <string>

using namespace std;

void CalcFF() {

  std::cout << std::endl << "***************************************" << std::endl;
  std::cout << "*             Calculate Fakefactor    *" << std::endl;
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

  std::vector<TString> wf; wf.push_back(p+a_weight[0]); wf.push_back(p+a_weight[1]); wf.push_back(p+a_weight[2]); if (DOQCD) wf.push_back(p+a_weight[3]);
  std::vector<TString> ps; ps.push_back(preselection_Wjets); ps.push_back(preselection_DY_J); ps.push_back(preselection_TT_J_EMB); //if (DOQCD) ps.push_back(preselection_QCD);
  ps.push_back(preselection_DY_TT); ps.push_back(preselection_DY_L); ps.push_back(preselection_TT_T); ps.push_back(preselection_TT_L);
  if(useVV) {ps.push_back(preselection_VV_T); ps.push_back(preselection_VV_L);}

  std::vector<TString> pre_sub_wj;
  std::vector<TString> pre_sub_dy; 
  std::vector<TString> pre_sub_tt; 
  std::vector<TString> pre_sub_qcd;
  //definition of backgrounds to be subtracted:
  pre_sub_wj.push_back(preselection_DY); pre_sub_wj.push_back(preselection_TT); pre_sub_wj.push_back(preselection_VV);
  pre_sub_dy.push_back(preselection_Wjets); pre_sub_dy.push_back(preselection_TT); pre_sub_dy.push_back(preselection_DY_TT); pre_sub_dy.push_back(preselection_DY_L); pre_sub_dy.push_back(preselection_VV);
  pre_sub_tt.push_back(preselection_DY); pre_sub_tt.push_back(preselection_Wjets); pre_sub_tt.push_back(preselection_TT_T); pre_sub_tt.push_back(preselection_TT_L); pre_sub_tt.push_back(preselection_VV);
  pre_sub_qcd.push_back(preselection_DY); pre_sub_qcd.push_back(preselection_Wjets); pre_sub_qcd.push_back(preselection_TT); pre_sub_qcd.push_back(preselection_VV);

  // Float_t yields[5];
  // Float_t combinedYields[20];
  // if(doCalcWeights && !CALC_SS_SR){
  //   cout << endl << "################### Calculating FF weights  ###############" << endl << endl;
  //   if(inclusive_selection) Analyzer->calcFFweights(m_preselection_data,wf, ps, yields, pi, p, p+template_file_name);
  //   if(exclusive_selection){
  //     for(Int_t icat=0;icat<nCAT;icat++){
  //       if(CHAN==kTAU && icat>2) continue;
        
  //       TString m_preselection_data_tmp=m_preselection_data; //m_preselection_data_tmp.ReplaceAll( ".root",categories[icat]+".root" );
  //       std::vector<TString> wf; wf.push_back(p+a_weight[0]); wf.push_back(p+a_weight[1]); wf.push_back(p+a_weight[2]); if (DOQCD) wf.push_back(p+a_weight[3]);
  //       //for(Int_t iwf; iwf<wf.size();iwf++) wf.at(iwf).ReplaceAll( ".root",categories[icat]+".root" );
  //       TString template_file_name_tmp=p+template_file_name; template_file_name_tmp.ReplaceAll( ".root",categories[icat]+".root" );
  //       std::vector<TString> ps; ps.push_back(preselection_Wjets); ps.push_back(preselection_DY_J); ps.push_back(preselection_TT_J_EMB); //if (DOQCD) ps.push_back(preselection_QCD);
  //       ps.push_back(preselection_DY_TT); ps.push_back(preselection_DY_L); ps.push_back(preselection_TT_T); ps.push_back(preselection_TT_L);
  //       if(useVV) {ps.push_back(preselection_VV_T); ps.push_back(preselection_VV_L);}
  //       //for(Int_t ips=0; ips<ps.size();ips++) ps.at(ips).ReplaceAll( ".root",categories[icat]+".root" );
  //       Analyzer->calcFFweights(m_preselection_data_tmp,wf, ps, yields, pi, p, template_file_name_tmp, 0, catMode[icat]);
  //       /*
  //       //This was used for MSSM frac plots
  //       if(CHAN!=kTAU){
  //         if( catMode[icat] & _BTAG_TIGHT ){
  //           for(int i=0;i<5;i++) combinedYields[i] = yields[i];
  //         }
  //         if( catMode[icat] & _BTAG_LOOSEMT ){
  //           for(int i=0;i<5;i++) combinedYields[i+5] = yields[i];
  //         }
  //         if( catMode[icat] & _NOBTAG_TIGHT ){
  //           for(int i=0;i<5;i++) combinedYields[i+10] = yields[i];
  //         }
  //         if( catMode[icat] & _NOBTAG_LOOSEMT ){
  //           for(int i=0;i<5;i++) combinedYields[i+15] = yields[i];
  //         }
  //       }
  //       else if(CHAN==kTAU){
  //         if( catMode[icat] & _BTAG ){
  //           for(int i=0;i<5;i++) combinedYields[i] = yields[i];
  //         }
  //         if( catMode[icat] & _NOBTAG ){
  //           for(int i=0;i<5;i++) combinedYields[i+10] = yields[i];
  //         }
  //       }
  //       */
  //     }
  //   }
  // }

  // if( doCalcWeights && makePieCharts ){
  //   if(CHAN==kMU){
  //     Analyzer->plotPieFractions_mutau_etau( "mt", "ViennaTool/Images/data_mt/fractions_mt", 1, combinedYields);
  //     Analyzer->plotPieFractions_mutau_etau( "mt", "ViennaTool/Images/data_mt/fractions_mt", 0, combinedYields);
  //   }
  //   if(CHAN==kEL){
  //     Analyzer->plotPieFractions_mutau_etau( "et", "ViennaTool/Images/data_et/fractions_et", 1, combinedYields);
  //     Analyzer->plotPieFractions_mutau_etau( "et", "ViennaTool/Images/data_et/fractions_et", 0, combinedYields);
  //   }
  //   if(CHAN==kTAU){
  //     Analyzer->plotPieFractions_tautau( "tt", "ViennaTool/Images/data_tt/fractions_tt", 1, combinedYields);
  //     Analyzer->plotPieFractions_tautau( "tt", "ViennaTool/Images/data_tt/fractions_tt", 0, combinedYields);
  //   }
  // }
  
  // if(doCalcWeights && CALC_SS_SR){
  //   cout << endl << "################### Calculating SS FF weights  ###############" << endl << endl;
  //   TString template_file_name_tmp=template_file_name; template_file_name_tmp.ReplaceAll( ".root","_SS_SR.root" );
  //   Analyzer->calcFFweights(m_preselection_data,wf,ps,yields,pi,p,p+template_file_name_tmp);
    
  // }
  
  if (inclusive_selection){
    if( EMB ){
        //EMBEDDING
        pre_sub_wj.clear(); 
        pre_sub_wj.push_back(preselection_EMB); pre_sub_wj.push_back(preselection_DY_J_EMB); pre_sub_wj.push_back(preselection_DY_L_EMB); pre_sub_wj.push_back(preselection_TT_J_EMB); pre_sub_wj.push_back(preselection_TT_L_EMB); pre_sub_wj.push_back(preselection_VV_J_EMB); pre_sub_wj.push_back(preselection_VV_L_EMB);

        pre_sub_dy.clear();
        pre_sub_dy.push_back(preselection_EMB); pre_sub_dy.push_back(preselection_Wjets); pre_sub_dy.push_back(preselection_TT_J_EMB); pre_sub_dy.push_back(preselection_TT_L_EMB); pre_sub_dy.push_back(preselection_DY_L_EMB); pre_sub_dy.push_back(preselection_VV_J_EMB); pre_sub_dy.push_back(preselection_VV_L_EMB);

        pre_sub_tt.clear();
        pre_sub_tt.push_back(preselection_EMB); pre_sub_tt.push_back(preselection_Wjets); pre_sub_tt.push_back(preselection_DY_J_EMB); pre_sub_tt.push_back(preselection_DY_L_EMB); pre_sub_tt.push_back(preselection_TT_L_EMB); pre_sub_tt.push_back(preselection_VV_J_EMB); pre_sub_tt.push_back(preselection_VV_L_EMB);
        
        pre_sub_qcd.clear();
        pre_sub_qcd.push_back(preselection_EMB); pre_sub_qcd.push_back(preselection_Wjets); pre_sub_qcd.push_back(preselection_DY_J_EMB); pre_sub_qcd.push_back(preselection_DY_L_EMB); pre_sub_qcd.push_back(preselection_TT_J_EMB); pre_sub_qcd.push_back(preselection_TT_L_EMB); pre_sub_qcd.push_back(preselection_VV_J_EMB); pre_sub_qcd.push_back(preselection_VV_L_EMB);
    }
    if (doCalc==1 && CHAN!=kTAU){

      ///////////////////////////////////////////////////////////////////////////////////////
      /////////////2. Calc FF
      ///////////////////////////////////////////////////////////////////////////////////////
      cout << endl << "################### Calculating FFs         ###############" << endl << endl;
      
      cout << "Presel-files for subtraction: " << endl; 
      for (int i = 0; i < pre_sub_wj.size(); i ++){
        cout << i << " " << pre_sub_wj[i] << endl;
      }
      
      //TT FFs are calculated from NTuples without EMB
      cout << "Calculating TT FFs" << endl;
      if (useDYFF_forTT) Analyzer->calcFFCorr(_DY|m_gen_match,     m_preselection_data,   pre_sub_dy,          p+FF_corr_TT_MCsum_noGen,     p+weight_TT_J);
      else               Analyzer->calcFFCorr(_TT|m_gen_match,     m_preselection_data,   pre_sub_tt,          p+FF_corr_TT_MCsum_noGen,     p+weight_TT_J);
      Analyzer->calcFFCorr(_TT|m_gen_match,                        preselection_TT_J_EMB,     empty_vec_tstring,   p+FF_TT_J_only,               p+weight_TT_J);
      Analyzer->calcFFCorr(_TT|m_gen_match|SR,                     preselection_TT_J_EMB,     empty_vec_tstring,   p+FF_TT_J_only_SR,            p+weight_TT_J);

      
      cout << "Calculating W+Jets FFs" << endl;
      Analyzer->calcFFCorr(_W_JETS|m_gen_match,                    m_preselection_data,   pre_sub_wj,          p+FF_corr_Wjets_MCsum_noGen,  p+weight_Wjets);
      Analyzer->calcFFCorr(_W_JETS|m_gen_match,                    preselection_Wjets,    empty_vec_tstring,   p+FF_corr_Wjets_MC_noGen,     p+weight_Wjets);
      

      cout << "Calculating QCD FFs" << endl;
      Analyzer->calcFFCorr(_QCD|m_gen_match,                       m_preselection_data,   pre_sub_qcd,         p+FF_corr_QCD_MCsum_noGen,    p+weight_QCD);
      Analyzer->calcFFCorr(_QCD|m_gen_match|_AI,                   m_preselection_data,   pre_sub_qcd,         p+FF_corr_QCD_MCsum_noGen_AI, p+weight_QCD);
    }

    if(doCalc && CHAN==kTAU){
      Analyzer->calcFFCorr(_QCD|m_gen_match,                       m_preselection_data,   pre_sub_qcd,         p+FF_corr_QCD_MCsum_noGen,    p+weight_QCD);
      Analyzer->calcFFCorr(_QCD|m_gen_match|_AI,                   m_preselection_data,   pre_sub_qcd,         p+"FF_corr_QCD_MCsum_noGen_AI.root", p+weight_QCD);
    }
    
  }  

  if(inclusive_selection && doCalc){
    if(CHAN==kMU){
      Analyzer->plotFF(p+FF_corr_TT_MCsum_noGen,    p+FF_TT_J_only,    _TT, pi+"ff_TT_CR_data_vs_MC"   ,"FF in TT CR(data #mu#tau)", "FF in TT CR(sim #mu#tau)");
      Analyzer->plotFF(p+FF_corr_TT_MCsum_noGen,    p+FF_TT_J_only,    _TT, pi+"ff_TT_CR_data_vs_MC"   ,"FF in TT CR(data #mu#tau)", "FF in TT CR(sim #mu#tau)", "_alt");
    }
    if(CHAN==kEL){
      Analyzer->plotFF(p+FF_corr_TT_MCsum_noGen,    p+FF_TT_J_only,    _TT, pi+"ff_TT_CR_data_vs_MC"   ,"FF in TT CR(data e#tau)", "FF in TT CR(sim e#tau)");
      Analyzer->plotFF(p+FF_corr_TT_MCsum_noGen,    p+FF_TT_J_only,    _TT, pi+"ff_TT_CR_data_vs_MC"   ,"FF in TT CR(data e#tau)", "FF in TT CR(sim e#tau)", "_alt");
    }
  }
  
  delete Analyzer;

  
}
  
#ifndef __CINT__
int main(int argc, char* argv[]) {
  CalcFF();    
}
#endif

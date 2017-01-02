#include "ViennaTool/interface/FFCalculator.h"
#include "ViennaTool/src/FFCalculator.cc"

#include <iostream>
#include <string>

using namespace std;

void ApplyFF() {

  std::cout << std::endl << "*******************************************************" << std::endl;
  std::cout << "*Applying Fakefactor and calculating uncertainties    *" << std::endl;
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
    
  ///////////////////////////////////////////////////////////////////////////////////////
  /////////////Calc Bkg estimates + toys for stat uncertainties
  ///////////////////////////////////////////////////////////////////////////////////////
  if (doBgEst){
    cout << endl << "################### Background estimates    ###############" << endl << endl;

    for(Int_t icat=0; icat<nCAT; icat++){
    //for(Int_t icat=2; icat<5; icat++){
      if(inclusive_selection && icat>0) continue;
      Int_t categoryMode=0;
      if(inclusive_frac_mt) categoryMode=_INCLFRAC_MT;
      if(inclusive_frac_et) categoryMode=_INCLFRAC_ET;
      if(inclusive_frac_tt) categoryMode=_INCLFRAC_TT;
      if(!inclusive_selection) {
        if(inclusive_frac_mt) categoryMode=catMode[icat]|_INCLFRAC_MT;
        if(inclusive_frac_et) categoryMode=catMode[icat]|_INCLFRAC_ET;
        if(inclusive_frac_tt) categoryMode=catMode[icat]|_INCLFRAC_TT;
        if(cat_frac_mt) categoryMode=catMode[icat]|_CATFRAC_MT;
        if(cat_frac_et) categoryMode=catMode[icat]|_CATFRAC_ET;
        if(cat_frac_tt) categoryMode=catMode[icat]|_CATFRAC_TT;
        
      }
      Analyzer->loadFile(m_preselection_data,"Events");
      if(CHAN==kTAU){
        //FIXME: this has to be adapted like the ELSE function
        vector<Int_t> mode_q; mode_q.push_back(_QCD|NO_SR|MT); mode_q.push_back(_QCD|MVIS); mode_q.push_back(_QCD|NO_SR|PT);
        vector<Int_t> mode_w; mode_w.push_back(_W_JETS|NO_SR|MT); mode_w.push_back(_W_JETS|MVIS); mode_w.push_back(_W_JETS|NO_SR|PT);
        vector<Int_t> mode_d; mode_d.push_back(_DY|NO_SR|MT); mode_d.push_back(_DY|MVIS); mode_d.push_back(_DY|NO_SR|PT);
        vector<Int_t> mode_t; mode_t.push_back(_TT|NO_SR|MT); mode_t.push_back(_TT|MVIS); mode_t.push_back(_TT|NO_SR|PT);
        vector<Int_t> mode_comb; mode_comb.push_back(NO_SR|MT); mode_comb.push_back(MVIS); mode_comb.push_back(NO_SR|PT);
        Analyzer->applyFF_tt_raw(p+"FFestimate_QCD", mode_q, categoryMode);
        Analyzer->applyFF_tt_raw(p+"FFestimate_Wjets", mode_w, categoryMode);
        Analyzer->applyFF_tt_raw(p+"FFestimate_DY_J", mode_t, categoryMode);
        Analyzer->applyFF_tt_raw(p+"FFestimate_tt_J", mode_d, categoryMode);
        Analyzer->applyFF_tt_raw(p+"FFestimate", mode_comb, categoryMode);
      }
      else{
        vector<Int_t> mode_t; mode_t.push_back(_TT|NO_SR|MT); mode_t.push_back(_TT|MVIS); mode_t.push_back(_TT|NO_SR|PT); if(use_svfit){mode_t.push_back(_TT|SVFIT);}
        vector<Int_t> mode_q; mode_q.push_back(_QCD|NO_SR|MT); mode_q.push_back(_QCD|MVIS); mode_q.push_back(_QCD|NO_SR|PT); if(use_svfit){mode_q.push_back(_QCD|SVFIT);}
        vector<Int_t> mode_w; mode_w.push_back(_W_JETS|NO_SR|MT); mode_w.push_back(_W_JETS|MVIS); mode_w.push_back(_W_JETS|NO_SR|PT); if(use_svfit){mode_w.push_back(_W_JETS|SVFIT);}
        vector<Int_t> mode_d; mode_d.push_back(_DY|NO_SR|MT); mode_d.push_back(_DY|MVIS); mode_d.push_back(_DY|NO_SR|PT); if(use_svfit){mode_d.push_back(_DY|SVFIT);}
        vector<Int_t> mode_comb;
        //mode_comb.push_back(PT);
        //mode_comb.push_back(LEPPT);
        mode_comb.push_back(MET|NO_SR);
        //mode_comb.push_back(NO_SR|PT); if(use_svfit){mode_comb.push_back(_TT|SVFIT);}
        /*Analyzer->applyFF(p+"FFestimate_QCD", mode_q, categoryMode);
        Analyzer->applyFF(p+"FFestimate_Wjets", mode_w, categoryMode);
        Analyzer->applyFF(p+"FFestimate_tt_J", mode_t, categoryMode);
        Analyzer->applyFF(p+"FFestimate_DY_J", mode_d, categoryMode);*/
        if(!doCuts)Analyzer->applyFF(p+"FFestimate", mode_comb, categoryMode);

        if(doCuts) for (unsigned l=0; l<NC; l++){ Analyzer->applyFF( p+"FFestimate_cuts_"+c_text[l], mode_comb, categoryMode, c_cuts[l]  ); }       
        
        //vector<Int_t> mode_t; mode_t.push_back(_TT_J|NO_SR|MT); mode_t.push_back(_TT_J|MVIS); mode_t.push_back(_TT_J|NO_SR|PT);
        //vector<Int_t> mode_q; mode_q.push_back(_QCD|NO_SR|MT); mode_q.push_back(_QCD|MVIS); mode_q.push_back(_QCD|NO_SR|PT);
        //vector<Int_t> mode_w; mode_w.push_back(_W_JETS|NO_SR|MT); mode_w.push_back(_W_JETS|MVIS); mode_w.push_back(_W_JETS|NO_SR|PT);
        //vector<Int_t> mode_d; mode_d.push_back(_DY_J|NO_SR|MT); mode_d.push_back(_DY_J|MVIS); mode_d.push_back(_DY_J|NO_SR|PT);
        //vector<Int_t> mode_comb; mode_comb.push_back(NO_SR|MT); mode_comb.push_back(MVIS); mode_comb.push_back(NO_SR|PT);
        //Analyzer->applyFF(p+"FFestimate_QCD_SS_SR", mode_q, categoryMode);
        //Analyzer->applyFF(p+"FFestimate_Wjets_SS_SR", mode_w, categoryMode);
        //Analyzer->applyFF(p+"FFestimate_tt_J_SS_SR", mode_t, categoryMode);
        //Analyzer->applyFF(p+"FFestimate_DY_J_SS_SR", mode_d, categoryMode);
        //Analyzer->applyFF(p+"FFestimate_SS_SR", mode_comb, categoryMode);
      }

    }
  }

  ///////////////////////////////////////////////////////////////////////////////////////
  ///////////////4. Plotting
  ///////////////////////////////////////////////////////////////////////////////////////
  if (doPlots){
    Analyzer->loadFile(preselection_data,"Events");

    std::vector<TString> vlabel_all;
    std::vector<TString> vlabel_bkg;
    std::vector<TString> vlabel_ff;
    std::vector<TString> vlabel_bkg_ff;
    std::vector<TString> vname_ff;
    std::vector<TString> vsuff_ff;
    for (unsigned il=0; il< (sizeof(vlabel) / sizeof(vlabel[0]) ); il++){
      vlabel_all.push_back(vlabel[il]);
      if ( !vlabel[il].Contains("ZTT") ) vlabel_bkg.push_back(vlabel[il]);
    }
    for (unsigned il=0; il< (sizeof(vlabel_w_ff) / sizeof(vlabel_w_ff[0]) ); il++){
      vlabel_bkg_ff.push_back(vlabel_w_ff[il]);
    }
    for (unsigned i=0; i<n_ff; i++){
      vlabel_ff.push_back(vlabel[ vlabel_i_ff[i] ]);
      vname_ff.push_back(vname[ vlabel_i_ff[i] ]);
      vsuff_ff.push_back(vsuff[ vlabel_i_ff[i] ]);
    }
    
    std::vector<TString> proc_list_mt;
    proc_list_mt.push_back(p+"FFestimate_Wjets_mt.root");
    proc_list_mt.push_back(p+"FFestimate_tt_J_mt.root");
    proc_list_mt.push_back(SR_TT_T_mt_sim);
    proc_list_mt.push_back(SR_TT_L_mt_sim);
    proc_list_mt.push_back(p+"FFestimate_DY_J_mt.root");
    proc_list_mt.push_back(SR_DY_TT_mt_sim);
    proc_list_mt.push_back(SR_DY_L_mt_sim);
    if (DOQCD)   proc_list_mt.push_back(p+"FFestimate_QCD_mt.root");
    
    std::vector<TString> proc_list_mt_ff;
    proc_list_mt_ff.push_back(SR_TT_T_mt_sim);
    proc_list_mt_ff.push_back(SR_TT_L_mt_sim);
    proc_list_mt_ff.push_back(SR_DY_TT_mt_sim);
    proc_list_mt_ff.push_back(SR_DY_L_mt_sim);
    proc_list_mt_ff.push_back(p+"FFestimate_mt.root");
    
    std::vector<TString> proc_list_mvis(proc_list_mt);
    std::vector<TString> proc_list_pt(proc_list_mt);
    for (unsigned iv=0; iv<proc_list_mt.size(); iv++){
      proc_list_mvis.at(iv).ReplaceAll("mt.","mvis.");
      proc_list_pt.at(iv).ReplaceAll(s_mt,s_pt);
    }
    
    std::vector<TString> proc_list_mvis_ff(proc_list_mt_ff);
    for (unsigned iv=0; iv<proc_list_mt_ff.size(); iv++){
      cout << proc_list_mvis_ff.at(iv) << endl;
      proc_list_mvis_ff.at(iv).ReplaceAll("mt.","mvis.");
      cout << proc_list_mvis_ff.at(iv) << endl;
    }
    
    std::vector<TString> proc_list_bkg_mt;
    for (unsigned iv=0; iv<proc_list_mt.size(); iv++){ if ( !proc_list_mt.at(iv).Contains("DY_TT") ) proc_list_bkg_mt.push_back( proc_list_mt.at(iv) ); }
    
    std::vector<TString> proc_list_bkg_mvis(proc_list_bkg_mt);
    std::vector<TString> proc_list_bkg_pt(proc_list_bkg_mt);
    for (unsigned iv=0; iv<proc_list_bkg_mt.size(); iv++){
      proc_list_bkg_mvis.at(iv).ReplaceAll("mt.","mvis.");
      proc_list_bkg_pt.at(iv).ReplaceAll(s_mt,s_pt);
    }
    
    //plot bkg sum estimate a la run 1 vs FF
    if ( !DOMC ){
      TString bsum=SR_MCsum_mt; bsum.ReplaceAll( "SR_MCsum", "SR_Bkgsum_run1" ); //bsum.ReplaceAll( "_"+s_mt , "_"+tvar[0] );
      Analyzer->plotBgStackedAgainstData(bsum,"Bkg a la run 1",proc_list_bkg_mt,  vlabel_bkg,pi+"run1_vs_ff_"+tvar[0],"Bkg sum run 1 vs FF",tvar_l[0],_COLOR_RUN1);
      
      TString data=SR_data_mt;
      Analyzer->plotBgStackedAgainstData(data,"data",proc_list_mt_ff,  vlabel_bkg_ff,pi+"bkg_ff_"+tvar[0],"Bkg estimation with FF",tvar_l[0],_COLOR_FF);
      
      
      bsum=SR_MCsum_mvis; bsum.ReplaceAll( "SR_MCsum", "SR_Bkgsum_run1" ); //bsum.ReplaceAll( "_"+s_mvis , "_"+tvar[1] );
      Analyzer->plotBgStackedAgainstData(bsum,"Bkg a la run 1",proc_list_bkg_mvis,  vlabel_bkg,pi+"run1_vs_ff_"+tvar[1],"Bkg sum run 1 vs FF",tvar_l[1],_COLOR_RUN1);
      
      data=SR_data_mvis;
      Analyzer->plotBgStackedAgainstData(data,"data",proc_list_mvis_ff,  vlabel_bkg_ff,pi+"bkg_ff_"+tvar[1],"Bkg estimation with FF",tvar_l[1],_COLOR_FF);
    }
  }


  
  delete Analyzer;

  
}
  
#ifndef __CINT__
int main(int argc, char* argv[]) {
  ApplyFF();    
}
#endif

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



  
  FFCalculator* Analyzer = new FFCalculator(N_p_Wjets,N_p_DY,N_p_TT,N_p_QCD,
                                            N_e_Wjets,N_e_DY,N_e_TT,N_e_QCD,
                                            N_t_Wjets,N_t_DY,N_t_TT,N_t_QCD,
                                            N_m_Wjets,N_m_DY,N_m_TT,N_m_QCD,
                                            N_j_Wjets,N_j_DY,N_j_TT,N_j_QCD,
                                            Pt_cuts_Wjets,Pt_cuts_DY,Pt_cuts_TT,Pt_cuts_QCD,
                                            Eta_cuts_Wjets,Eta_cuts_DY,Eta_cuts_TT,Eta_cuts_QCD,
                                            Decay_cuts_Wjets,Decay_cuts_DY,Decay_cuts_TT,Decay_cuts_QCD,
                                            Mt_cuts_Wjets,Mt_cuts_DY,Mt_cuts_TT,Mt_cuts_QCD,
                                            Njet_cuts_Wjets,Njet_cuts_DY,Njet_cuts_TT,Njet_cuts_QCD
                                            );

  Analyzer->init();

  std::vector<TString> wf; wf.push_back(p+a_weight[0]); wf.push_back(p+a_weight[1]); wf.push_back(p+a_weight[2]); if (DOQCD) wf.push_back(p+a_weight[3]);
  std::vector<TString> ps; ps.push_back(preselection_Wjets); ps.push_back(preselection_DY_J); ps.push_back(preselection_TT_J); //if (DOQCD) ps.push_back(preselection_QCD);
  ps.push_back(preselection_DY_TT); ps.push_back(preselection_DY_L); ps.push_back(preselection_TT_T); ps.push_back(preselection_TT_L);
  if(useVV) {ps.push_back(preselection_VV_T); ps.push_back(preselection_VV_L);}

  std::vector<TString> pre_sub_wj; pre_sub_wj.push_back(preselection_DY); pre_sub_wj.push_back(preselection_TT); //decide if VV is needed here
  if (DOQCD) pre_sub_wj.push_back(preselection_QCD);

  std::vector<TString> pre_sub_dy; pre_sub_dy.push_back(preselection_Wjets); pre_sub_dy.push_back(preselection_TT); pre_sub_dy.push_back(preselection_DY_TT); pre_sub_dy.push_back(preselection_DY_L); //decide if VV is needed here
  if (DOQCD) pre_sub_dy.push_back(preselection_QCD);

  std::vector<TString> pre_sub_tt; pre_sub_tt.push_back(preselection_DY); pre_sub_tt.push_back(preselection_Wjets); pre_sub_tt.push_back(preselection_TT_T); pre_sub_tt.push_back(preselection_TT_L); //decide if VV is needed here
  if (DOQCD) pre_sub_tt.push_back(preselection_QCD);

  std::vector<TString> pre_sub_qcd;
  pre_sub_qcd.push_back(preselection_DY); pre_sub_qcd.push_back(preselection_Wjets); pre_sub_qcd.push_back(preselection_TT); //decide if VV is needed here

  if(doCalcWeights && !CALC_SS_SR){
    cout << endl << "################### Calculating FF weights  ###############" << endl << endl;
    if(inclusive_selection) Analyzer->calcFFweights(m_preselection_data,wf, ps, pi, p, p+template_file_name);
    else{
      for(Int_t icat=0;icat<nCAT;icat++){
      //for(Int_t icat=3;icat<4;icat++){
        TString m_preselection_data_tmp=m_preselection_data; //m_preselection_data_tmp.ReplaceAll( ".root",categories[icat]+".root" );
        std::vector<TString> wf; wf.push_back(p+a_weight[0]); wf.push_back(p+a_weight[1]); wf.push_back(p+a_weight[2]); if (DOQCD) wf.push_back(p+a_weight[3]);
        //for(Int_t iwf; iwf<wf.size();iwf++) wf.at(iwf).ReplaceAll( ".root",categories[icat]+".root" );
        TString template_file_name_tmp=p+template_file_name; template_file_name_tmp.ReplaceAll( ".root",categories[icat]+".root" );
        std::vector<TString> ps; ps.push_back(preselection_Wjets); ps.push_back(preselection_DY_J); ps.push_back(preselection_TT_J); //if (DOQCD) ps.push_back(preselection_QCD);
        ps.push_back(preselection_DY_TT); ps.push_back(preselection_DY_L); ps.push_back(preselection_TT_T); ps.push_back(preselection_TT_L);
        //for(Int_t ips=0; ips<ps.size();ips++) ps.at(ips).ReplaceAll( ".root",categories[icat]+".root" );
        Analyzer->calcFFweights(m_preselection_data_tmp,wf, ps, pi, p, template_file_name_tmp, catMode[icat]);
      }
    }
  }

  if(doCalcWeights && CALC_SS_SR){
    cout << endl << "################### Calculating SS FF weights  ###############" << endl << endl;
    TString template_file_name_tmp=template_file_name; template_file_name_tmp.ReplaceAll( ".root","_SS_SR.root" );
    Analyzer->calcFFweights(m_preselection_data,wf,ps,pi,p,p+template_file_name_tmp);
    
  }

  Int_t m_corr=0, m_ttcorr=0; if (applyFF_fromCR){ m_corr=_WCORR; m_ttcorr=_TTCORR;}
  
  if (inclusive_selection){

    if (doCalc==1){

      ///////////////////////////////////////////////////////////////////////////////////////
      /////////////2. Calc FF
      ///////////////////////////////////////////////////////////////////////////////////////
      cout << endl << "################### Calculating FFs         ###############" << endl << endl;
      Analyzer->calcFFCorr(_W_JETS|m_gen_match,                    m_preselection_data,   pre_sub_wj,    p+FF_corr_Wjets_MCsum_noGen,  p+weight_Wjets);

      if (useWJFF_forDY) Analyzer->calcFFCorr(_W_JETS|m_gen_match, m_preselection_data,   pre_sub_wj,    p+FF_corr_DY_MCsum_noGen,     p+weight_DY_J);
      else               Analyzer->calcFFCorr(_DY|m_gen_match ,    m_preselection_data,   pre_sub_dy,    p+FF_corr_DY_MCsum_noGen,     p+weight_DY_J); //DY_J using FF from DY->mumu CR

      //Analyzer->calcFFCorr(_DY|m_gen_match,                        m_preselection_data,   pre_sub_dy,    p+FF_corr_DY_MCsum_noGen,     p+weight_DY_J);
      //DY_J using FF from  W+jets CR
      //Analyzer->calcFFCorr(_W_JETS|m_gen_match,                          m_preselection_data,   pre_sub_wj,    p+FF_corr_DY_MCsum_noGen,     p+weight_DY_J);

      cout << "Calculating TT FFs" << endl;
      if (useDYFF_forTT) Analyzer->calcFFCorr(_DY|m_gen_match,     m_preselection_data,   pre_sub_dy,    p+FF_corr_TT_MCsum_noGen,  p+weight_TT_J);
      else               Analyzer->calcFFCorr( _TT|m_gen_match,    m_preselection_data,   pre_sub_tt,    p+FF_corr_TT_MCsum_noGen,  p+weight_TT_J);

      if (DOQCD){
        cout << "Calculating QCD FFs" << endl;
        Analyzer->calcFFCorr(_QCD|m_gen_match,                     m_preselection_data,   pre_sub_qcd,   p+FF_corr_QCD_MCsum_noGen,    p+weight_QCD);
        Analyzer->calcFFCorr(_QCD|m_gen_match|_AI,                     m_preselection_data,   pre_sub_qcd,   p+FF_corr_QCD_MCsum_noGen_AI,    p+weight_QCD);
        //Analyzer->calc_nonclosure(_QCD,                            p+FF_corr_QCD_MCsum_noGen,  p+weight_QCD,  CR_QCD_mvis_data,  p+FF_corr_QCD_MCsum_noGen_closure, p+FF_corr_QCD_MCsum_noGen_nonclosure);
        //if(CHAN==kTAU) Analyzer->calcFFCorr(_QCD|m_gen_match|SR,   m_preselection_data,   pre_sub_qcd,   p+FF_corr_QCD_MCsum_noGen_OS, p+weight_QCD);
        Analyzer->calcFFCorr(_QCDISO|m_gen_match,                  m_preselection_data,   pre_sub_qcd,   p+FF_corr_QCDISO_MCsum_noGen, p+weight_QCD);
      }
    }

    if (doCalcCorrections==1){
      cout << "Calculating QCD and W+jets corrections" << endl;
      if(!DOMC){
        Analyzer->loadFile(m_preselection_data,"Events");
        Analyzer->calc_nonclosure(_QCD,                            p+FF_corr_QCD_MCsum_noGen,  CR_QCD_mvis_data_MCsubtracted, p+FF_corr_QCD_MCsum_noGen_nonclosure);
        Analyzer->calc_nonclosure(_W_JETS,                            p+FF_corr_Wjets_MCsum_noGen,  CR_Wjets_mvis_data_MCsubtracted, p+FF_corr_Wjets_MCsum_noGen_nonclosure);
        Analyzer->calc_muisocorr(_QCD|MUISO,                       p+FF_corr_QCD_MCsum_noGen,  CR_QCD_muiso_data_MCsubtracted, p+FF_corr_QCD_MCsum_noGen_nonclosure, p+FF_corr_QCD_MCsum_noGen_muisocorr);
        Analyzer->calc_nonclosure(_QCD|_AI,                            p+FF_corr_QCD_MCsum_noGen_AI,  CR_QCD_mvis_AI_data_MCsubtracted, p+FF_corr_QCD_MCsum_noGen_nonclosure_AI, 0);
        Analyzer->calc_OSSScorr(_QCD|_AI,                       p+FF_corr_QCD_MCsum_noGen_AI,  SR_data_mvis_AI_MCsubtracted, p+FF_corr_QCD_MCsum_noGen_nonclosure_AI, p+FF_corr_QCD_MCsum_noGen_OSSScorr);
        
        Analyzer->calcFFCorr(_W_JETS|m_gen_match,                    preselection_Wjets,   empty_vec_tstring,    p+FF_corr_Wjets_MC_noGen,  p+weight_Wjets);
        Analyzer->loadFile(preselection_Wjets,"Events");
        Analyzer->calc_nonclosure(_W_JETS,                            p+FF_corr_Wjets_MC_noGen,  CR_Wjets_mvis_Wjets, p+FF_corr_Wjets_MC_noGen_nonclosure, 0, 0);
        Analyzer->calc_mtcorr(_W_JETS|NO_SR,                            p+FF_corr_Wjets_MC_noGen,  CR_Wjets_mt_Wjets, p+FF_corr_Wjets_MC_noGen_nonclosure, p+FF_corr_Wjets_MC_noGen_mtcorr);
        
      }
      else cout << "FIXME: Reasonable corrections for MC closure if enough statistics" << endl;
      

      //These are the setting for tt
      //if(CHAN==kTAU) Analyzer->calcFFCorr(_QCD|m_gen_match,   m_preselection_data,   pre_sub_qcd,   p+FF_corr_QCD_MCsum_noGen, p+weight_QCD);
      //Analyzer->plotFF(p+"FF_corr_QCD_MCsum_noGen_VTight.root",    p+"FF_corr_QCD_MCsum_noGen_VTight.root",    _QCD, pi+"ff_QCD_njetBinned"   ,"QCD m_{T}(#tau#tau) !vtightMVA", "QCD m_{T}(#mu#tau) vlooseMVA && !vtightMVA",PTDMJET_BINS,nPTDMJET_BINS+1);
      
      //Analyzer->calcFFCorr(_QCD|m_gen_match|_AI,   m_preselection_data,   pre_sub_qcd,   p+"FF_corr_QCD_MCsum_noGen_AI.root", p+weight_QCD);
      //Analyzer->loadFile(preselection_data,"Events");
      //Analyzer->calc_nonclosure(_QCD,                            p+"FF_corr_QCD_MCsum_noGen_VTight.root",  "sim/tt/CR_QCD_mvis_data_MCsubtracted.root", p+"FF_corr_QCD_MCsum_noGen_nonclosure.root");
      //Analyzer->calc_nonclosure(_QCD|_AI,                            p+"FF_corr_QCD_MCsum_noGen_AI_VTight.root",  "sim/tt/CR_QCD_mvis_AI_data_MCsubtracted.root", p+"FF_corr_QCD_MCsum_noGen_nonclosure_AI.root", 0);
      //Analyzer->calc_OSSScorr(_QCD|_AI,                       p+"FF_corr_QCD_MCsum_noGen_AI_VTight.root",  "sim/"+s_chan[CHAN]+"/SR_data_mvis_AI_MCsubtracted.root", p+"FF_corr_QCD_MCsum_noGen_nonclosure_AI.root", p+FF_corr_QCD_MCsum_noGen_OSSScorr);
      
      //mvis correction for TT
      if(CHAN==kMU){
        cout << "Calculating TT corrections" << endl;
        Analyzer->loadFile(preselection_TT_J,"Events");
        Analyzer->calcFFCorr(_TT|m_gen_match,                    preselection_TT_J,   empty_vec_tstring,    pmc+FF_TT_J_only,  p+weight_TT_J);
        Analyzer->calc_nonclosure(_TT|SR,                            pmc+FF_TT_J_only,  SR_TT_J_mvis_sim, p+FF_corr_TT_MC_noGen_nonclosure, 1, 0);
        //...done
      }

      if(CHAN==kMU){
        /*Analyzer->plotFF(p+"FF_corr_QCD_MCsum_noGen.root",    "fakefactor/mc_mt/FF_corr_QCD_MCsum_noGen.root",    _QCD, pi+"ff_QCD_data_vs_MC"   ,"FF in QCD (data #mu#tau)", "FF in QCD (sim #mu#tau)");
        Analyzer->plotFF(p+"FF_corr_Wjets_MCsum_noGen.root",    "fakefactor/mc_mt/FF_corr_Wjets_MCsum_noGen.root",    _W_JETS, pi+"ff_Wjets_data_vs_MC"   ,"FF in Wjets (data #mu#tau)", "FF in Wjets (sim #mu#tau)");
        Analyzer->plotFF(p+"FF_corr_DY_MCsum_noGen.root",    "fakefactor/mc_mt/FF_corr_DY_MCsum_noGen.root",    _DY, pi+"ff_DY_J_data_vs_MC"   ,"FF in DY (data #mu#tau)", "FF in DY (sim #mu#tau)");
        Analyzer->plotFF(p+"FF_corr_TT_MCsum_noGen.root",    "fakefactor/mc_mt/FF_corr_TT_MCsum_noGen.root",    _TT, pi+"ff_TT_data_vs_MC"   ,"FF in TT (data #mu#tau)", "FF in TT (sim #mu#tau)");
        
        Analyzer->plotFF(p+"FF_corr_QCD_MCsum_noGen.root",    "fakefactor/data_et/FF_corr_QCD_MCsum_noGen.root",    _QCD, pi+"ff_QCD_data_mt_vs_et"   ,"FF in QCD (data #mu#tau)", "FF in QCD (data e#tau)");
        Analyzer->plotFF(p+"FF_corr_Wjets_MCsum_noGen.root",    "fakefactor/data_et/FF_corr_Wjets_MCsum_noGen.root",    _W_JETS, pi+"ff_Wjets_data_mt_vs_et"   ,"FF in Wjets (data #mu#tau)", "FF in Wjets (data e#tau)");
        Analyzer->plotFF(p+"FF_corr_DY_MCsum_noGen.root",    "fakefactor/data_et/FF_corr_DY_MCsum_noGen.root",    _DY, pi+"ff_DY_J_data_mt_vs_et"   ,"FF in DY (data #mu#tau)", "FF in DY (data e#tau)");
        Analyzer->plotFF(p+"FF_corr_TT_MCsum_noGen.root",    "fakefactor/data_et/FF_corr_TT_MCsum_noGen.root",    _TT, pi+"ff_TT_data_mt_vs_et"   ,"FF in TT (data #mu#tau)", "FF in TT (data e#tau)");

        Analyzer->plotFF(p+"FF_corr_QCD_MCsum_noGen.root",    "../../../CMSSW_7_6_3/src/ViennaTool/fakefactor/data_mt/FF_corr_QCD_MCsum_noGen.root",    _QCD, pi+"ff_QCD_data2016_vs_data2015"   ,"FF in QCD (2016 #mu#tau)", "FF in QCD (2015 #mu#tau)");
        Analyzer->plotFF(p+"FF_corr_Wjets_MCsum_noGen.root",    "../../../CMSSW_7_6_3/src/ViennaTool/fakefactor/data_mt/FF_corr_Wjets_MCsum_noGen.root",    _W_JETS, pi+"ff_Wjets_data2016_vs_data2015"   ,"FF in Wjets (2016 #mu#tau)", "FF in Wjets (2015 #mu#tau)");
        Analyzer->plotFF(p+"FF_corr_TT_MCsum_noGen.root",    "../../../CMSSW_7_6_3/src/ViennaTool/fakefactor/data_mt/FF_corr_TT_MCsum_noGen.root",    _TT, pi+"ff_TT_data2016_vs_data2015"   ,"FF in TT (2016 #mu#tau)", "FF in TT (2015 #mu#tau)");*/
      }
      
      
      ///////////////////////////////////////////////////////////////////////////////////////
      /////////////2b. Calc some FF for debugging (e.g. in SR)
      ///////////////////////////////////////////////////////////////////////////////////////

      if (doDebugPlots==2){
        cout << endl << "################### Calculating FFs (debug) ###############" << endl << endl;
        //Analyzer->calcFFCorr(MUISO|VSVAR|DOALL|_QCD|m_gen_match,m_preselection_data,pre_sub_qcd,                p+FF_corr_QCD_MCsum_muiso);
        Analyzer->calcFFCorr(MUISO|VSVAR|_QCD|m_gen_match,m_preselection_data,pre_sub_qcd,                      p+FF_corr_QCD_MCsum_muiso_CR);
        //Analyzer->calcFFCorr(MUISO|VSVAR|SR|_QCD|m_gen_match,m_preselection_data,pre_sub_qcd,                   p+FF_corr_QCD_MCsum_muiso_SR);
        Analyzer->calcFFCorr(NB   |VSVAR|_QCD|m_gen_match,m_preselection_data,pre_sub_qcd,                      p+FF_corr_QCD_MCsum_nb_CR);
        Analyzer->calcFFCorr(NB   |VSVAR|_TT |m_gen_match,m_preselection_data,pre_sub_tt,                       p+FF_corr_TT_J_MCsum_nb_CR);
        Analyzer->calcFFCorr(DRB  |VSVAR|_QCD|m_gen_match,m_preselection_data,pre_sub_qcd,                      p+FF_corr_QCD_MCsum_drb_CR);
        Analyzer->calcFFCorr(DRB  |VSVAR|_TT |m_gen_match,m_preselection_data,pre_sub_tt,                       p+FF_corr_TT_J_MCsum_drb_CR);
      }

      if (doDebugPlots && DOMC){
        //Specific sample, vs nb

        if (doDebugPlots==2){
          Analyzer->calcFFCorr(NB|VSVAR|_QCD|m_gen_match,preselection_QCD,empty_vec_tstring,                      p+FF_QCD_only_nb_CR);
          Analyzer->calcFFCorr(NB|VSVAR|SR|_QCD|m_gen_match,preselection_QCD,empty_vec_tstring,                   p+FF_QCD_only_nb_SR);
          Analyzer->calcFFCorr(NB|VSVAR|_TT|m_gen_match,preselection_TT_J,empty_vec_tstring,                      p+FF_TT_J_only_nb_CR);
          Analyzer->calcFFCorr(NB|VSVAR|SR|_TT|m_gen_match,preselection_TT_J,empty_vec_tstring,                   p+FF_TT_J_only_nb_SR);
          Analyzer->calcFFCorr(DRB|VSVAR|_QCD|m_gen_match,preselection_QCD,empty_vec_tstring,                     p+FF_QCD_only_drb_CR);
          Analyzer->calcFFCorr(DRB|VSVAR|SR|_QCD|m_gen_match,preselection_QCD,empty_vec_tstring,                  p+FF_QCD_only_drb_SR);
          Analyzer->calcFFCorr(DRB|VSVAR|_TT|m_gen_match,preselection_TT_J,empty_vec_tstring,                     p+FF_TT_J_only_drb_CR);
          Analyzer->calcFFCorr(DRB|VSVAR|SR|_TT|m_gen_match,preselection_TT_J,empty_vec_tstring,                  p+FF_TT_J_only_drb_SR);
        }

        if (doSRPlots){
          //SR, all samples
          cout << endl << "################### SR Plots ###############" << endl << endl;
          Analyzer->calcFFCorr(_W_JETS|SR|m_gen_match,m_preselection_data,pre_sub_wj,                    p+FF_corr_Wjets_MCsum_noGen_SR,p+weight_Wjets);
          if (useWJFF_forDY) Analyzer->calcFFCorr(_W_JETS|SR|m_gen_match,m_preselection_data,pre_sub_wj,    p+FF_corr_DY_MCsum_noGen_SR,p+weight_DY_J);
          else               Analyzer->calcFFCorr(_DY|    SR|m_gen_match,m_preselection_data,pre_sub_dy,    p+FF_corr_DY_MCsum_noGen_SR,p+weight_DY_J);
          if (useDYFF_forTT) Analyzer->calcFFCorr(_DY|    SR|m_gen_match,m_preselection_data,pre_sub_dy,    p+FF_corr_TT_MCsum_noGen_SR,p+weight_TT_J);
          else               Analyzer->calcFFCorr(_TT|    SR|m_gen_match,m_preselection_data,pre_sub_tt,    p+FF_corr_TT_MCsum_noGen_SR,p+weight_TT_J);
          if (DOQCD){ Analyzer->calcFFCorr(_QCD|SR|m_gen_match,m_preselection_data,pre_sub_qcd,             p+FF_corr_QCD_MCsum_noGen_SR,p+weight_QCD); }
          
          //SR, specific sample
          Analyzer->calcFFCorr(_W_JETS|SR|m_gen_match,preselection_Wjets,empty_vec_tstring,                    p+FF_Wjets_only_SR,p+weight_Wjets);
          if (useWJFF_forDY) Analyzer->calcFFCorr(_W_JETS|SR|m_gen_match,preselection_Wjets,empty_vec_tstring, p+FF_DY_J_only_SR,p+weight_DY_J);
          else               Analyzer->calcFFCorr(_DY|    SR|m_gen_match,preselection_DY_J,empty_vec_tstring,  p+FF_DY_J_only_SR,p+weight_DY_J);
          if (useDYFF_forTT) Analyzer->calcFFCorr(_DY|    SR|m_gen_match,preselection_DY_J,empty_vec_tstring,  p+FF_TT_J_only_SR,p+weight_TT_J);
          else               Analyzer->calcFFCorr(_TT|    SR|m_gen_match,preselection_TT_J,empty_vec_tstring,  p+FF_TT_J_only_SR,p+weight_TT_J);
          if (DOQCD){ Analyzer->calcFFCorr(_QCD|SR|m_gen_match,preselection_QCD,empty_vec_tstring,             p+FF_QCD_only_SR,p+weight_QCD); }
          
          //SR, specific sample, vs mT
          Analyzer->calcFFCorr(MT|VSVAR|_W_JETS|SR|m_gen_match,preselection_Wjets,empty_vec_tstring,                    p+FF_Wjets_only_mt_SR,p+weight_Wjets);
          if (useWJFF_forDY) Analyzer->calcFFCorr(MT|VSVAR|_W_JETS|SR|m_gen_match,preselection_Wjets,empty_vec_tstring, p+FF_DY_J_only_mt_SR,p+weight_DY_J);
          else               Analyzer->calcFFCorr(MT|VSVAR|_DY|    SR|m_gen_match,preselection_DY_J,empty_vec_tstring,  p+FF_DY_J_only_mt_SR,p+weight_DY_J);
          if (useDYFF_forTT) Analyzer->calcFFCorr(MT|VSVAR|_DY|    SR|m_gen_match,preselection_DY_J,empty_vec_tstring,  p+FF_TT_J_only_mt_SR,p+weight_TT_J);
          else               Analyzer->calcFFCorr(MT|VSVAR|_TT|    SR|m_gen_match,preselection_TT_J,empty_vec_tstring,  p+FF_TT_J_only_mt_SR,p+weight_TT_J);
          if (DOQCD){ Analyzer->calcFFCorr(MT|VSVAR|_QCD|SR|m_gen_match,preselection_QCD,empty_vec_tstring,             p+FF_QCD_only_mt_SR,p+weight_QCD); }
          
          //All regions, specific sample, vs mT
          Analyzer->calcFFCorr(MT|VSVAR|DOALL|_W_JETS|m_gen_match,preselection_Wjets,empty_vec_tstring,                 p+FF_Wjets_only_mt,p+weight_Wjets); //done above
          if (useWJFF_forDY) Analyzer->calcFFCorr(MT|VSVAR|DOALL|_W_JETS|m_gen_match,preselection_Wjets,empty_vec_tstring, p+FF_DY_J_only_mt,p+weight_DY_J);
          else               Analyzer->calcFFCorr(MT|VSVAR|DOALL|_DY|m_gen_match,preselection_DY_J,empty_vec_tstring,      p+FF_DY_J_only_mt,p+weight_DY_J);
          if (useDYFF_forTT) Analyzer->calcFFCorr(MT|VSVAR|DOALL|_DY|m_gen_match,preselection_DY_J,empty_vec_tstring,      p+FF_TT_J_only_mt,p+weight_TT_J);
          else               Analyzer->calcFFCorr(MT|VSVAR|DOALL|_TT|m_gen_match,preselection_TT_J,empty_vec_tstring,      p+FF_TT_J_only_mt,p+weight_TT_J);
          if (DOQCD){ Analyzer->calcFFCorr(MT|VSVAR|DOALL|_QCD|m_gen_match,preselection_QCD,empty_vec_tstring,          p+FF_QCD_only_mt,p+weight_QCD); }
        }
        
        //CR, specific sample
        Analyzer->calcFFCorr(_W_JETS|m_gen_match,preselection_Wjets,empty_vec_tstring,                       p+FF_Wjets_only,p+weight_Wjets);
        if (useWJFF_forDY) Analyzer->calcFFCorr(_W_JETS|m_gen_match,preselection_Wjets,empty_vec_tstring,    p+FF_DY_J_only,p+weight_DY_J);
        else               Analyzer->calcFFCorr(_DY|m_gen_match,preselection_DY_J,empty_vec_tstring,         p+FF_DY_J_only,p+weight_DY_J);
        if (useDYFF_forTT) Analyzer->calcFFCorr(_DY|m_gen_match,preselection_DY_J,empty_vec_tstring,         p+FF_TT_J_only,p+weight_TT_J);
        else               Analyzer->calcFFCorr(_TT|m_gen_match,preselection_TT_J,empty_vec_tstring,         p+FF_TT_J_only,p+weight_TT_J);
        if (DOQCD){ Analyzer->calcFFCorr(_QCD|m_gen_match,preselection_QCD,empty_vec_tstring,                p+FF_QCD_only,p+weight_QCD); }
        
        //CR, specific sample, vs mT
        Analyzer->calcFFCorr(MT|VSVAR|_W_JETS|m_gen_match,preselection_Wjets,empty_vec_tstring,                     p+FF_Wjets_only_mt_CR,p+weight_Wjets);
        if (useWJFF_forDY) Analyzer->calcFFCorr(MT|VSVAR|_W_JETS|m_gen_match,preselection_Wjets,empty_vec_tstring,  p+FF_DY_J_only_mt_CR,p+weight_DY_J);
        else               Analyzer->calcFFCorr(MT|VSVAR|_DY|m_gen_match,preselection_DY_J,empty_vec_tstring,       p+FF_DY_J_only_mt_CR,p+weight_DY_J);
        if (useDYFF_forTT) Analyzer->calcFFCorr(MT|VSVAR|_DY|m_gen_match,preselection_DY_J,empty_vec_tstring,       p+FF_TT_J_only_mt_CR,p+weight_TT_J);
        else               Analyzer->calcFFCorr(MT|VSVAR|_TT|m_gen_match,preselection_TT_J,empty_vec_tstring,       p+FF_TT_J_only_mt_CR,p+weight_TT_J);
        if (DOQCD){ Analyzer->calcFFCorr(MT|VSVAR|_QCD|m_gen_match,preselection_QCD,empty_vec_tstring,              p+FF_QCD_only_mt_CR,p+weight_QCD); }

        //Specific sample, vs mTll
        Analyzer->calcFFCorr(MTLL|VSVAR|DOALL|_DY|m_gen_match,preselection_DY_J,empty_vec_tstring,                p+FF_DY_J_only_mtll);
        Analyzer->calcFFCorr(MTLL|VSVAR|_DY|m_gen_match,preselection_DY_J,empty_vec_tstring,                      p+FF_DY_J_only_mtll_CR);
        
        //Specific sample, vs mu iso
        Analyzer->calcFFCorr(MUISO|VSVAR|DOALL|_QCD|m_gen_match,preselection_QCD,empty_vec_tstring,                p+FF_QCD_only_muiso);
        Analyzer->calcFFCorr(MUISO|VSVAR|_QCD|m_gen_match,preselection_QCD,empty_vec_tstring,                      p+FF_QCD_only_muiso_CR);
        Analyzer->calcFFCorr(MUISO|VSVAR|SR|_QCD|m_gen_match,preselection_QCD,empty_vec_tstring,                   p+FF_QCD_only_muiso_SR);
        
      }
      
    }// end if docalc==1
  }

  delete Analyzer;

  
}
  
#ifndef __CINT__
int main(int argc, char* argv[]) {
  CalcFF();    
}
#endif

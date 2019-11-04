//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Mar 21 19:40:12 2018 by ROOT version 6.06/01
// from TTree TauCheck/TauCheck
// found on file: /data/higgs/data_2016/ntuples_v2/et/ntuples_SVFIT_merged/BASIS_ntuple_DYXJetsToLL_lowMass_merged_MCSummer16_et_v2.root
//////////////////////////////////////////////////////////

#ifndef NtupleClass_h
#define NtupleClass_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TLorentzVector.h>



// Header file for the classes stored in the TTree if any.
#include "vector"

class NtupleClass {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           fileEntry;
   Int_t           entry;
   Int_t           run;
   Float_t         lumi;
   ULong64_t       evt;
   Float_t         weight;
   Float_t         lumiWeight;
   Float_t         puweight;
   Float_t         xsec;
   Float_t         genNEventsWeight;
   Float_t         idWeight_1;
   Float_t         isoWeight_1;
   Float_t         sf_reco;
   Float_t         singleTriggerSFLeg1;
   Float_t         xTriggerSFLeg1;
   Float_t         xTriggerSFLeg2;
   Float_t         sf_DoubleTauTight;
   Float_t         sf_SingleOrCrossTrigger;
   Float_t         genweight;
   Float_t         trigweight_1;
   Float_t         trigweight_2;
   Float_t         idisoweight_1;
   Float_t         idisoweight_2;
   Float_t         sf_trk;
   Float_t         stitchedWeight;
   Float_t         topPtReweightWeightRun1;
   Float_t         topPtReweightWeightRun2;
   Float_t         eleTauFakeRateWeight;
   Float_t         muTauFakeRateWeight;
   Float_t         zPtReweightWeight;
   Int_t           trg_singlemu_22; 
   Int_t           trg_doubletau_35; 
   Int_t           trg_singleelectron_25_eta2p1; 
//    Int_t           trg_mutaucross;
   Int_t           trg_crossmu_mu19tau20;
   Int_t           trg_singleelectron;
   Int_t           trg_crossele_ele24tau30;
//    Int_t           trg_singletau;
   Float_t         gen_Mll;
   Float_t         genpX;
   Float_t         genpY;
   Float_t         genpZ;
   Float_t         gen_vis_Mll;
   Float_t         vispX;
   Float_t         vispY;
   Float_t         vispZ;
   Int_t           npv;
   Float_t         npu;
   Float_t         rho;
   Int_t           NUP;
//    Int_t           passBadMuonFilter;
//    Int_t           passBadChargedHadronFilter;
//    Int_t           flagHBHENoiseFilter;
//    Int_t           flagHBHENoiseIsoFilter;
//    Int_t           flagEcalDeadCellTriggerPrimitiveFilter;
//    Int_t           flagGoodVertices;
//    Int_t           flagEeBadScFilter;
//    Int_t           flagGlobalTightHalo2016Filter;

   Int_t           flagMETFilter;
//    Float_t         matchedJetPt03_1;
//    Float_t         matchedJetPt05_1;
//    Float_t         matchedJetPt03_2;
//    Float_t         matchedJetPt05_2;
   Int_t           gen_match_1;
   Int_t           gen_match_2;
   Int_t           gen_match_jetId_1;
   Int_t           gen_match_jetId_2;
   Int_t           genJets;
   Float_t         pt_1;
   Float_t         phi_1;
   Float_t         eta_1;
   Float_t         eta_SC_1;
   Float_t         m_1;
   Int_t           q_1;
   Float_t         d0_1;
   Float_t         dZ_1;
   Float_t         mt_1;
   Float_t         iso_1;
   Int_t           againstElectronLooseMVA6_1;
   Int_t           againstElectronMediumMVA6_1;
   Int_t           againstElectronTightMVA6_1;
   Int_t           againstElectronVLooseMVA6_1;
   Int_t           againstElectronVTightMVA6_1;
   Int_t           againstMuonLoose3_1;
   Int_t           againstMuonTight3_1;
   Float_t         byCombinedIsolationDeltaBetaCorrRaw3Hits_1;
   Float_t           byIsolationMVA3newDMwoLTraw_1;
   Float_t           byIsolationMVA3oldDMwoLTraw_1;
   Int_t         byIsolationMVA3newDMwLTraw_1;
   Int_t         byIsolationMVA3oldDMwLTraw_1;
   Int_t           byVLooseIsolationMVArun2017v2DBoldDMwLT2017_1;
   Int_t           byLooseIsolationMVArun2017v2DBoldDMwLT2017_1;
   Int_t           byMediumIsolationMVArun2017v2DBoldDMwLT2017_1;
   Int_t           byTightIsolationMVArun2017v2DBoldDMwLT2017_1;
   Int_t           byVTightIsolationMVArun2017v2DBoldDMwLT2017_1;
  
   Int_t           byVVVLooseIsolationDeepTau2017v2VSjet_1;
   Int_t           byVVLooseIsolationDeepTau2017v2VSjet_1;
   Int_t           byVLooseIsolationDeepTau2017v2VSjet_1;
   Int_t           byLooseIsolationDeepTau2017v2VSjet_1;
   Int_t           byMediumIsolationDeepTau2017v2VSjet_1;
   Int_t           byTightIsolationDeepTau2017v2VSjet_1;
   Int_t           byVTightIsolationDeepTau2017v2VSjet_1;
   Int_t           byVVTightIsolationDeepTau2017v2VSjet_1;
//    Int_t           byVLooseIsolationMVArun2v1DBnewDMwLT_1;
//    Int_t           byLooseIsolationMVArun2v1DBnewDMwLT_1;
//    Int_t           byMediumIsolationMVArun2v1DBnewDMwLT_1;
//    Int_t           byTightIsolationMVArun2v1DBnewDMwLT_1;
//    Int_t           byVTightIsolationMVArun2v1DBnewDMwLT_1;
//    Int_t           byRerunMVAIdVLoose_1;
//    Int_t           byRerunMVAIdLoose_1;
//    Int_t           byRerunMVAIdMedium_1;
//    Int_t           byRerunMVAIdTight_1;
//    Int_t           byRerunMVAIdVTight_1;
//    Int_t           byRerunMVAIdVVTight_1;
//    Float_t         idMVANewDM_1;
   Float_t         chargedIsoPtSum_1;
   Float_t         neutralIsoPtSum_1;
   Float_t         puCorrPtSum_1;
   Int_t           decayModeFindingOldDMs_1;
   Int_t           decayModeFindingNewDMs_1;
   Int_t           decayMode_1;
   Float_t         id_e_mva_nt_loose_1;
   Float_t         id_m_loose_1;
   Float_t         id_m_medium_1;
   Float_t         id_m_tight_1;
   Float_t         id_m_highpt_1;
   Float_t         id_e_cut_veto_1;
   Float_t         id_e_cut_loose_1;
   Float_t         id_e_cut_medium_1;
   Float_t         id_e_cut_tight_1;
   Float_t         antilep_tauscaling;
   Float_t         pt_2;
   Float_t         phi_2;
   Float_t         eta_2;
   Float_t         m_2;
   Int_t           q_2;
   Float_t         d0_2;
   Float_t         dZ_2;
   Float_t         mt_2;
   Float_t         iso_2;
   Int_t           againstElectronLooseMVA6_2;
   Int_t           againstElectronMediumMVA6_2;
   Int_t           againstElectronTightMVA6_2;
   Int_t           againstElectronVLooseMVA6_2;
   Int_t           againstElectronVTightMVA6_2;
   Int_t           againstMuonLoose3_2;
   Int_t           againstMuonTight3_2;
   Float_t         byCombinedIsolationDeltaBetaCorrRaw3Hits_2;
   Float_t           byIsolationMVA3newDMwoLTraw_2;
   Float_t           byIsolationMVA3oldDMwoLTraw_2;
   Int_t         byIsolationMVA3newDMwLTraw_2;
   Int_t         byIsolationMVA3oldDMwLTraw_2;
   Int_t           byVLooseIsolationMVArun2017v2DBoldDMwLT2017_2;
   Int_t           byLooseIsolationMVArun2017v2DBoldDMwLT2017_2;
   Int_t           byMediumIsolationMVArun2017v2DBoldDMwLT2017_2;
   Int_t           byTightIsolationMVArun2017v2DBoldDMwLT2017_2;
   Int_t           byVTightIsolationMVArun2017v2DBoldDMwLT2017_2;

   Int_t           byVVVLooseIsolationDeepTau2017v2VSjet_2;
   Int_t           byVVLooseIsolationDeepTau2017v2VSjet_2;
   Int_t           byVLooseIsolationDeepTau2017v2VSjet_2;
   Int_t           byLooseIsolationDeepTau2017v2VSjet_2;
   Int_t           byMediumIsolationDeepTau2017v2VSjet_2;
   Int_t           byTightIsolationDeepTau2017v2VSjet_2;
   Int_t           byVTightIsolationDeepTau2017v2VSjet_2;
   Int_t           byVVTightIsolationDeepTau2017v2VSjet_2;
//    Int_t           byVLooseIsolationMVArun2v1DBnewDMwLT_2;
//    Int_t           byLooseIsolationMVArun2v1DBnewDMwLT_2;
//    Int_t           byMediumIsolationMVArun2v1DBnewDMwLT_2;
//    Int_t           byTightIsolationMVArun2v1DBnewDMwLT_2;
//    Int_t           byVTightIsolationMVArun2v1DBnewDMwLT_2;
//    Int_t           byRerunMVAIdVLoose_2;
//    Int_t           byRerunMVAIdLoose_2;
//    Int_t           byRerunMVAIdMedium_2;
//    Int_t           byRerunMVAIdTight_2;
//    Int_t           byRerunMVAIdVTight_2;
//    Int_t           byRerunMVAIdVVTight_2;
//    Float_t         idMVANewDM_2;
   Float_t         chargedIsoPtSum_2;
   Float_t         neutralIsoPtSum_2;
   Float_t         puCorrPtSum_2;
   Int_t           decayModeFindingOldDMs_2;
   Int_t           decayModeFindingNewDMs_2;
   Int_t           decayMode_2;
   Float_t         pzetavis;
   Float_t         pzetamiss;
   Float_t         dzeta;
   Float_t         pt_tt;
   Float_t         pt_vis;
   Float_t         dphi;
//    Float_t         mt_3;
   Float_t         mt_tot;
//    Float_t         pfpt_tt;
   Float_t         m_vis;
   Float_t         m_coll;
   Float_t         pt_sum;
   Float_t         dr_leptau;
   Float_t         jeta1eta2;
   Float_t         met_centrality;
   Float_t         lep_etacentrality;
   Float_t         sphericity;
   Int_t           nadditionalMu;
     
   std::vector<TLorentzVector> *addlepton_p4; //added
   std::vector<double>  *addlepton_iso; 	  //added
   std::vector<int> 	*addlepton_pdgId;	  // added
   std::vector<int> 	*addlepton_tauID;	  // added
   std::vector<int> 	*addlepton_tauDM;	  // added
   std::vector<int> 	*addlepton_tauAntiEle;	  // added
   std::vector<int> 	*addlepton_tauAntiMu;	  // added
   std::vector<double> 	*addlepton_tauCombIso;	  // added
   std::vector<int> 	*addlepton_mc_match;	  // added
   std::vector<double> 	*addlepton_mvis;	  // added
   
   std::vector<double>  *addmuon_pt;	//
   std::vector<double>  *addmuon_eta;	//
   std::vector<double>  *addmuon_phi;	//
   std::vector<double>  *addmuon_m;		//
   std::vector<int>     *addmuon_q;
   std::vector<double>  *addmuon_iso;
   std::vector<int>     *addmuon_gen_match;
   Int_t           nadditionalEle;
   std::vector<double>  *addele_pt;		//
   std::vector<double>  *addele_eta;	//
   std::vector<double>  *addele_phi;	//
   std::vector<double>  *addele_m;		//
   std::vector<int>     *addele_q;
   std::vector<double>  *addele_iso;
   std::vector<int>     *addele_gen_match;
   Int_t           nadditionalTau;
   std::vector<double>  *addtau_pt;		//
   std::vector<double>  *addtau_eta;	//
   std::vector<double>  *addtau_phi;	//
   std::vector<double>  *addtau_m;		//
   std::vector<double>  *addtau_q;

   std::vector<int>     *addtau_byVVVLooseIsolationDeepTau2017v2VSjet;
   std::vector<int>     *addtau_byVVLooseIsolationDeepTau2017v2VSjet;
   std::vector<int>     *addtau_byVLooseIsolationDeepTau2017v2VSjet;
   std::vector<int>     *addtau_byLooseIsolationDeepTau2017v2VSjet;
   std::vector<int>     *addtau_byMediumIsolationDeepTau2017v2VSjet;
   std::vector<int>     *addtau_byTightIsolationDeepTau2017v2VSjet;
   std::vector<int>     *addtau_byVTightIsolationDeepTau2017v2VSjet;
   std::vector<int>     *addtau_byVVTightIsolationDeepTau2017v2VSjet;


   std::vector<int>     *addtau_passesTauLepVetos;
   std::vector<int>     *addtau_decayMode;
   std::vector<double>  *addtau_d0;
   std::vector<double>  *addtau_dZ;
   std::vector<int>     *addtau_gen_match;
   std::vector<double>  *addtau_mt;
   std::vector<double>  *addtau_mvis;
   Int_t          passesTauLepVetos;
   Int_t          passesThirdLepVeto;
   Int_t          passesDiMuonVeto;
   Int_t          passesDiElectronVeto;
//    Bool_t          matchXTrig_obj;
   Bool_t          dilepton_veto;
   Bool_t          extraelec_veto;
   Bool_t          extramuon_veto;
   Float_t         met;
   Float_t         metphi;
   Float_t         met_ex;
   Float_t         met_ey;
   Float_t         metcov00;
   Float_t         metcov01;
   Float_t         metcov10;
   Float_t         metcov11;
   Float_t         mjj;
//    Float_t         mjjUp;
//    Float_t         mjjDown;
   Float_t         jdeta;
//    Float_t         jdetaUp;
//    Float_t         jdetaDown;
   Int_t           njetingap;
   Int_t           njetingap20;
   Float_t         dijetpt;
   Float_t         dijetphi;
   Float_t         jdphi;
   Int_t           nbtag;
   Int_t           njets;
//    Int_t           njetsUp;
//    Int_t           njetsDown;
   Int_t           njetspt20;
   Float_t         jpt_1;
//    Float_t         jptUp_1;
//    Float_t         jptDown_1;
   Float_t         jeta_1;
   Float_t         jphi_1;
   Float_t         jm_1;
   Float_t         jrawf_1;
   Float_t         jmva_1;
   Float_t         jcsv_1;
   Float_t         jpt_2;
//    Float_t         jptUp_2;
//    Float_t         jptDown_2;
   Float_t         jeta_2;
   Float_t         jphi_2;
   Float_t         jm_2;
   Float_t         jrawf_2;
   Float_t         jmva_2;
   Float_t         jcsv_2;
   Float_t         bpt_1;
   Float_t         beta_1;
   Float_t         bphi_1;
   Float_t         brawf_1;
   Float_t         bmva_1;
   Float_t         bcsv_1;
   Float_t         bpt_2;
   Float_t         beta_2;
   Float_t         bphi_2;
   Float_t         brawf_2;
   Float_t         bmva_2;
   Float_t         bcsv_2;
   Float_t         m_sv;
//    Float_t         m_sv_unc;
//    Float_t         mt_sv;
//    Float_t         mt_sv_unc;
   Float_t         pt_sv;
//    Float_t         pt_sv_unc;

   // List of branches
   TBranch        *b_fileEntry;   //!
   TBranch        *b_entry;   //!
   TBranch        *b_run;   //!
   TBranch        *b_lumi;   //!
   TBranch        *b_evt;   //!
   TBranch        *b_weight;   //!
   TBranch        *b_lumiWeight;   //!
   TBranch        *b_puweight;   //!
   TBranch        *b_xsec;
   TBranch        *b_genNEventsWeight;
   TBranch        *b_idWeight_1;
   TBranch        *b_isoWeight_1;
   TBranch        *b_sf_reco;
   TBranch        *b_singleTriggerSFLeg1;
   TBranch        *b_xTriggerSFLeg1;
   TBranch        *b_xTriggerSFLeg2;
   TBranch        *b_sf_DoubleTauTight;
   TBranch        *b_sf_SingleOrCrossTrigger;
   TBranch        *b_genweight;   //!
   TBranch        *b_trigweight_1;   //!
   TBranch        *b_trigweight_2;   //!
   TBranch        *b_idisoweight_1;   //!
   TBranch        *b_idisoweight_2;   //!
   TBranch        *b_sf_trk;   //!
   TBranch        *b_stitchedWeight;   //!
   TBranch        *b_topPtReweightWeightRun1;   //!
   TBranch        *b_topPtReweightWeightRun2;   //!
   TBranch        *b_eleTauFakeRateWeight;   //!
   TBranch        *b_muTauFakeRateWeight;   //!
   TBranch        *b_zPtReweightWeight;   //!
   TBranch        *b_trg_singlemu_22;   //!
   TBranch        *b_trg_doubletau_35;   //!

   
//    TBranch        *b_trg_mutaucross;   //!
   TBranch        *b_trg_singleelectron;   //!
   TBranch        *b_trg_crossele_ele24tau30;   //!
   TBranch        *b_trg_crossmu_mu19tau20;   //!
   TBranch        *b_trg_singleelectron_25_eta2p1;   //!

   
   TBranch        *b_gen_Mll;   //!
   TBranch        *b_genpX;   //!
   TBranch        *b_genpY;   //!
   TBranch        *b_genpZ;   //!
   TBranch        *b_gen_vis_Mll;   //!
   TBranch        *b_vispX;   //!
   TBranch        *b_vispY;   //!
   TBranch        *b_vispZ;   //!
   TBranch        *b_npv;   //!
   TBranch        *b_npu;   //!
   TBranch        *b_rho;   //!
   TBranch        *b_NUP;   //!
//    TBranch        *b_passBadMuonFilter;   //!
//    TBranch        *b_passBadChargedHadronFilter;   //!
//    TBranch        *b_flagHBHENoiseFilter;   //!
//    TBranch        *b_flagHBHENoiseIsoFilter;   //!
//    TBranch        *b_flagEcalDeadCellTriggerPrimitiveFilter;   //!
//    TBranch        *b_flagGoodVertices;   //!
//    TBranch        *b_flagEeBadScFilter;   //!
//    TBranch        *b_flagGlobalTightHalo2016Filter;   //!
   TBranch        *b_flagMETFilter;   //!
//    TBranch        *b_matchedJetPt03_1;   //!
//    TBranch        *b_matchedJetPt05_1;   //!
//    TBranch        *b_matchedJetPt03_2;   //!
//    TBranch        *b_matchedJetPt05_2;   //!
   TBranch        *b_gen_match_1;   //!
   TBranch        *b_gen_match_2;   //!
   TBranch        *b_gen_match_jetId_1;   //!
   TBranch        *b_gen_match_jetId_2;   //!
   TBranch        *b_genJets;   //!
   TBranch        *b_pt_1;   //!
   TBranch        *b_phi_1;   //!
   TBranch        *b_eta_1;   //!
   TBranch        *b_eta_SC_1;   //!
   TBranch        *b_m_1;   //!
   TBranch        *b_q_1;   //!
   TBranch        *b_d0_1;   //!
   TBranch        *b_dZ_1;   //!
   TBranch        *b_mt_1;   //!
   TBranch        *b_iso_1;   //!
   TBranch        *b_againstElectronLooseMVA6_1;   //!
   TBranch        *b_againstElectronMediumMVA6_1;   //!
   TBranch        *b_againstElectronTightMVA6_1;   //!
   TBranch        *b_againstElectronVLooseMVA6_1;   //!
   TBranch        *b_againstElectronVTightMVA6_1;   //!
   TBranch        *b_againstMuonLoose3_1;   //!
   TBranch        *b_againstMuonTight3_1;   //!
  
   TBranch        *b_byCombinedIsolationDeltaBetaCorrRaw3Hits_1;   //!
   TBranch        *b_byIsolationMVA3newDMwoLTraw_1;   //!
   TBranch        *b_byIsolationMVA3oldDMwoLTraw_1;   //!
   TBranch        *b_byIsolationMVA3newDMwLTraw_1;   //!
   TBranch        *b_byIsolationMVA3oldDMwLTraw_1;   //!
   TBranch        *b_byVLooseIsolationMVArun2017v2DBoldDMwLT2017_1;   //!
   TBranch        *b_byLooseIsolationMVArun2017v2DBoldDMwLT2017_1;   //!
   TBranch        *b_byMediumIsolationMVArun2017v2DBoldDMwLT2017_1;   //!
   TBranch        *b_byTightIsolationMVArun2017v2DBoldDMwLT2017_1;   //!
   TBranch        *b_byVTightIsolationMVArun2017v2DBoldDMwLT2017_1;   //!
   

   TBranch        *b_byVVVLooseIsolationDeepTau2017v2VSjet_1;
   TBranch        *b_byVVLooseIsolationDeepTau2017v2VSjet_1;
   TBranch        *b_byVLooseIsolationDeepTau2017v2VSjet_1;
   TBranch        *b_byLooseIsolationDeepTau2017v2VSjet_1;
   TBranch        *b_byMediumIsolationDeepTau2017v2VSjet_1;
   TBranch        *b_byTightIsolationDeepTau2017v2VSjet_1;
   TBranch        *b_byVTightIsolationDeepTau2017v2VSjet_1;
   TBranch        *b_byVVTightIsolationDeepTau2017v2VSjet_1;

//    TBranch        *b_byVLooseIsolationMVArun2v1DBnewDMwLT_1;   //!
//    TBranch        *b_byLooseIsolationMVArun2v1DBnewDMwLT_1;   //!
//    TBranch        *b_byMediumIsolationMVArun2v1DBnewDMwLT_1;   //!
//    TBranch        *b_byTightIsolationMVArun2v1DBnewDMwLT_1;   //!
//    TBranch        *b_byVTightIsolationMVArun2v1DBnewDMwLT_1;   //!
//    TBranch        *b_byRerunMVAIdVLoose_1;   //!
//    TBranch        *b_byRerunMVAIdLoose_1;   //!
//    TBranch        *b_byRerunMVAIdMedium_1;   //!
//    TBranch        *b_byRerunMVAIdTight_1;   //!
//    TBranch        *b_byRerunMVAIdVTight_1;   //!
//    TBranch        *b_byRerunMVAIdVVTight_1;   //!
//    TBranch        *b_idMVANewDM_1;   //!
   TBranch        *b_chargedIsoPtSum_1;   //!
   TBranch        *b_neutralIsoPtSum_1;   //!
   TBranch        *b_puCorrPtSum_1;   //!
   TBranch        *b_decayModeFindingOldDMs_1;   //!
   TBranch        *b_decayModeFindingNewDMs_1;   //!
   TBranch        *b_decayMode_1;   //!
   TBranch        *b_id_e_mva_nt_loose_1;   //!
   TBranch        *b_id_m_loose_1;   //!
   TBranch        *b_id_m_medium_1;   //!
   TBranch        *b_id_m_tight_1;   //!
   TBranch        *b_id_m_highpt_1;   //!
   TBranch        *b_id_e_cut_veto_1;   //!
   TBranch        *b_id_e_cut_loose_1;   //!
   TBranch        *b_id_e_cut_medium_1;   //!
   TBranch        *b_id_e_cut_tight_1;   //!
   TBranch        *b_antilep_tauscaling;   //!
   TBranch        *b_pt_2;   //!
   TBranch        *b_phi_2;   //!
   TBranch        *b_eta_2;   //!
   TBranch        *b_m_2;   //!
   TBranch        *b_q_2;   //!
   TBranch        *b_d0_2;   //!
   TBranch        *b_dZ_2;   //!
   TBranch        *b_mt_2;   //!
   TBranch        *b_iso_2;   //!
   TBranch        *b_againstElectronLooseMVA6_2;   //!
   TBranch        *b_againstElectronMediumMVA6_2;   //!
   TBranch        *b_againstElectronTightMVA6_2;   //!
   TBranch        *b_againstElectronVLooseMVA6_2;   //!
   TBranch        *b_againstElectronVTightMVA6_2;   //!
   TBranch        *b_againstMuonLoose3_2;   //!
   TBranch        *b_againstMuonTight3_2;   //!
   TBranch        *b_byCombinedIsolationDeltaBetaCorrRaw3Hits_2;   //!
   TBranch        *b_byIsolationMVA3newDMwoLTraw_2;   //!
   TBranch        *b_byIsolationMVA3oldDMwoLTraw_2;   //!
   TBranch        *b_byIsolationMVA3newDMwLTraw_2;   //!
   TBranch        *b_byIsolationMVA3oldDMwLTraw_2;   //!
   TBranch        *b_byVLooseIsolationMVArun2017v2DBoldDMwLT2017_2;   //!
   TBranch        *b_byLooseIsolationMVArun2017v2DBoldDMwLT2017_2;   //!
   TBranch        *b_byMediumIsolationMVArun2017v2DBoldDMwLT2017_2;   //!
   TBranch        *b_byTightIsolationMVArun2017v2DBoldDMwLT2017_2;   //!
   TBranch        *b_byVTightIsolationMVArun2017v2DBoldDMwLT2017_2;   //!
   

   TBranch        *b_byVVVLooseIsolationDeepTau2017v2VSjet_2;
   TBranch        *b_byVVLooseIsolationDeepTau2017v2VSjet_2;
   TBranch        *b_byVLooseIsolationDeepTau2017v2VSjet_2;
   TBranch        *b_byLooseIsolationDeepTau2017v2VSjet_2;
   TBranch        *b_byMediumIsolationDeepTau2017v2VSjet_2;
   TBranch        *b_byTightIsolationDeepTau2017v2VSjet_2;
   TBranch        *b_byVTightIsolationDeepTau2017v2VSjet_2;
   TBranch        *b_byVVTightIsolationDeepTau2017v2VSjet_2;


   TBranch        *b_chargedIsoPtSum_2;   //!
   TBranch        *b_neutralIsoPtSum_2;   //!
   TBranch        *b_puCorrPtSum_2;   //!
   TBranch        *b_decayModeFindingOldDMs_2;   //!
   TBranch        *b_decayModeFindingNewDMs_2;   //!
   TBranch        *b_decayMode_2;   //!
   TBranch        *b_pzetavis;   //!
   TBranch        *b_pzetamiss;   //!
   TBranch        *b_dzeta;   //!
   TBranch        *b_pt_tt;   //!
   TBranch        *b_pt_vis;   //!
   TBranch        *b_dphi;   //!
//    TBranch        *b_mt_3;   //!
   TBranch        *b_mt_tot;   //!
//    TBranch        *b_pfpt_tt;   //!
   TBranch        *b_m_vis;   //!
   TBranch        *b_m_coll;   //!
   TBranch        *b_pt_sum;   //!
   TBranch        *b_dr_leptau;   //!
   TBranch        *b_jeta1eta2;   //!
   TBranch        *b_met_centrality;   //!
   TBranch        *b_lep_etacentrality;   //!
   TBranch        *b_sphericity;   //!
   
   TBranch		  *b_addlepton_p4; 	//added
   TBranch		  *b_addlepton_iso;	//added 
   TBranch		  *b_addlepton_pdgId;//added
   TBranch		  *b_addlepton_tauID;//added
   TBranch		  *b_addlepton_tauDM;//added
   TBranch		  *b_addlepton_tauAntiEle;//added
   TBranch		  *b_addlepton_tauAntiMu;//added
   TBranch		  *b_addlepton_tauCombIso;//added
   TBranch		  *b_addlepton_mc_match;//added
   TBranch		  *b_addlepton_mvis;//added
   
   TBranch        *b_nadditionalMu;   //!
   TBranch        *b_addmuon_pt;   //!
   TBranch        *b_addmuon_eta;   //!
   TBranch        *b_addmuon_phi;   //!
   TBranch        *b_addmuon_m;   //!
   TBranch        *b_addmuon_q;   //!
   TBranch        *b_addmuon_iso;   //!
   TBranch        *b_addmuon_gen_match;   //!
   TBranch        *b_nadditionalEle;   //!
   TBranch        *b_addele_pt;   //!
   TBranch        *b_addele_eta;   //!
   TBranch        *b_addele_phi;   //!
   TBranch        *b_addele_m;   //!
   TBranch        *b_addele_q;   //!
   TBranch        *b_addele_iso;   //!
   TBranch        *b_addele_gen_match;   //!
   TBranch        *b_nadditionalTau;   //!
   TBranch        *b_addtau_pt;   //!
   TBranch        *b_addtau_eta;   //!
   TBranch        *b_addtau_phi;   //!
   TBranch        *b_addtau_m;   //!
   TBranch        *b_addtau_q;   //!

   TBranch        *b_addtau_byVVVLooseIsolationDeepTau2017v2VSjet;
   TBranch        *b_addtau_byVVLooseIsolationDeepTau2017v2VSjet;
   TBranch        *b_addtau_byVLooseIsolationDeepTau2017v2VSjet;
   TBranch        *b_addtau_byLooseIsolationDeepTau2017v2VSjet;
   TBranch        *b_addtau_byMediumIsolationDeepTau2017v2VSjet;
   TBranch        *b_addtau_byTightIsolationDeepTau2017v2VSjet;
   TBranch        *b_addtau_byVTightIsolationDeepTau2017v2VSjet;
   TBranch        *b_addtau_byVVTightIsolationDeepTau2017v2VSjet;


   TBranch        *b_addtau_passesTauLepVetos;   //!
   TBranch        *b_addtau_decayMode;   //!
   TBranch        *b_addtau_d0;   //!
   TBranch        *b_addtau_dZ;   //!
   TBranch        *b_addtau_gen_match;   //!
   TBranch        *b_addtau_mt;   //!
   TBranch        *b_addtau_mvis;   //!
   TBranch        *b_passesTauLepVetos;   //!
   TBranch        *b_passesThirdLepVeto;   //!
   TBranch        *b_passesDiMuonVeto;   //!
   TBranch        *b_passesDiElectronVeto;   //!
//    TBranch        *b_matchXTrig_obj;   //!
   TBranch        *b_dilepton_veto;   //!
   TBranch        *b_extraelec_veto;   //!
   TBranch        *b_extramuon_veto;   //!
   TBranch        *b_met;   //!
   TBranch        *b_metphi;   //!
   TBranch        *b_met_ex;   //!
   TBranch        *b_met_ey;   //!
   TBranch        *b_metcov00;   //!
   TBranch        *b_metcov01;   //!
   TBranch        *b_metcov10;   //!
   TBranch        *b_metcov11;   //!
   TBranch        *b_mjj;   //!
//    TBranch        *b_mjjUp;   //!
//    TBranch        *b_mjjDown;   //!
   TBranch        *b_jdeta;   //!
//    TBranch        *b_jdetaUp;   //!
//    TBranch        *b_jdetaDown;   //!
   TBranch        *b_njetingap;   //!
   TBranch        *b_njetingap20;   //!
   TBranch        *b_dijetpt;   //!
   TBranch        *b_dijetphi;   //!
   TBranch        *b_jdphi;   //!
   TBranch        *b_nbtag;   //!
   TBranch        *b_njets;   //!
//    TBranch        *b_njetsUp;   //!
//    TBranch        *b_njetsDown;   //!
   TBranch        *b_njetspt20;   //!
   TBranch        *b_jpt_1;   //!
//    TBranch        *b_jptUp_1;   //!
//    TBranch        *b_jptDown_1;   //!
   TBranch        *b_jeta_1;   //!
   TBranch        *b_jphi_1;   //!
   TBranch        *b_jm_1;   //!
   TBranch        *b_jrawf_1;   //!
   TBranch        *b_jmva_1;   //!
   TBranch        *b_jcsv_1;   //!
   TBranch        *b_jpt_2;   //!
//    TBranch        *b_jptUp_2;   //!
//    TBranch        *b_jptDown_2;   //!
   TBranch        *b_jeta_2;   //!
   TBranch        *b_jphi_2;   //!
   TBranch        *b_jm_2;   //!
   TBranch        *b_jrawf_2;   //!
   TBranch        *b_jmva_2;   //!
   TBranch        *b_jcsv_2;   //!
   TBranch        *b_bpt_1;   //!
   TBranch        *b_beta_1;   //!
   TBranch        *b_bphi_1;   //!
   TBranch        *b_brawf_1;   //!
   TBranch        *b_bmva_1;   //!
   TBranch        *b_bcsv_1;   //!
   TBranch        *b_bpt_2;   //!
   TBranch        *b_beta_2;   //!
   TBranch        *b_bphi_2;   //!
   TBranch        *b_brawf_2;   //!
   TBranch        *b_bmva_2;   //!
   TBranch        *b_bcsv_2;   //!
   TBranch        *b_m_sv;   //!
//    TBranch        *b_m_sv_unc;   //!
//    TBranch        *b_mt_sv;   //!
//    TBranch        *b_mt_sv_unc;   //!
   TBranch        *b_pt_sv;   //!
//    TBranch        *b_pt_sv_unc;   //!

   NtupleClass(TTree *tree=0);
   virtual ~NtupleClass();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef NtupleClass_cxx
NtupleClass::NtupleClass(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/data/higgs/data_2016/ntuples_v2/et/ntuples_SVFIT_merged/BASIS_ntuple_DYXJetsToLL_lowMass_merged_MCSummer16_et_v2.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/data/higgs/data_2016/ntuples_v2/et/ntuples_SVFIT_merged/BASIS_ntuple_DYXJetsToLL_lowMass_merged_MCSummer16_et_v2.root");
      }
      f->GetObject("TauCheck",tree);

   }
   Init(tree);
}

NtupleClass::~NtupleClass()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t NtupleClass::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t NtupleClass::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void NtupleClass::Init(TTree *tree)
{ 
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   addlepton_p4 = 0;	//added
   addlepton_iso = 0;	//added
   addlepton_pdgId = 0;	//added
   addlepton_tauID = 0;	//added
   addlepton_tauDM = 0;	//added
   addlepton_tauAntiEle = 0;	//added
   addlepton_tauAntiMu = 0;	//added
   addlepton_tauCombIso = 0;	//added
   addlepton_mc_match = 0;	//added
   addlepton_mvis = 0;	//added

   addmuon_pt = 0;
   addmuon_eta = 0;
   addmuon_phi = 0;
   addmuon_m = 0;
   addmuon_q = 0;
   addmuon_iso = 0;
   addmuon_gen_match = 0;
   addele_pt = 0;
   addele_eta = 0;
   addele_phi = 0;
   addele_m = 0;
   addele_q = 0;
   addele_iso = 0;
   addele_gen_match = 0;
   addtau_pt = 0;
   addtau_eta = 0;
   addtau_phi = 0;
   addtau_m = 0;
   addtau_q = 0;

   addtau_byVVVLooseIsolationDeepTau2017v2VSjet = 0;
   addtau_byVVLooseIsolationDeepTau2017v2VSjet = 0;
   addtau_byVLooseIsolationDeepTau2017v2VSjet = 0;
   addtau_byLooseIsolationDeepTau2017v2VSjet = 0;
   addtau_byMediumIsolationDeepTau2017v2VSjet = 0;
   addtau_byTightIsolationDeepTau2017v2VSjet = 0;
   addtau_byVTightIsolationDeepTau2017v2VSjet = 0;
   addtau_byVVTightIsolationDeepTau2017v2VSjet = 0;

   addtau_passesTauLepVetos = 0;
   addtau_decayMode = 0;
   addtau_d0 = 0;
   addtau_dZ = 0;
   addtau_gen_match = 0;
   addtau_mt = 0;
   addtau_mvis = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("fileEntry", &fileEntry, &b_fileEntry);
   fChain->SetBranchAddress("entry", &entry, &b_entry);
   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("lumi", &lumi, &b_lumi);
   fChain->SetBranchAddress("evt", &evt, &b_evt);
   fChain->SetBranchAddress("weight", &weight, &b_weight);
   fChain->SetBranchAddress("lumiWeight", &lumiWeight, &b_lumiWeight);
   fChain->SetBranchAddress("puweight", &puweight, &b_puweight);
   fChain->SetBranchAddress("xsec", &xsec, &b_xsec);
   fChain->SetBranchAddress("genNEventsWeight", &genNEventsWeight, &b_genNEventsWeight);
   fChain->SetBranchAddress("idWeight_1", &idWeight_1, &b_idWeight_1);
   fChain->SetBranchAddress("isoWeight_1", &isoWeight_1, &b_isoWeight_1);
   fChain->SetBranchAddress("sf_reco", &sf_reco, &b_sf_reco);
   fChain->SetBranchAddress("singleTriggerSFLeg1", &singleTriggerSFLeg1, &b_singleTriggerSFLeg1);
   fChain->SetBranchAddress("xTriggerSFLeg1", &xTriggerSFLeg1, &b_xTriggerSFLeg1);
   fChain->SetBranchAddress("xTriggerSFLeg2", &xTriggerSFLeg2, &b_xTriggerSFLeg2);
   fChain->SetBranchAddress("sf_DoubleTauTight", &sf_DoubleTauTight, &b_sf_DoubleTauTight);
   fChain->SetBranchAddress("sf_SingleOrCrossTrigger", &sf_SingleOrCrossTrigger, &b_sf_SingleOrCrossTrigger);
   fChain->SetBranchAddress("genweight", &genweight, &b_genweight);
   fChain->SetBranchAddress("trigweight_1", &trigweight_1, &b_trigweight_1);
   fChain->SetBranchAddress("trigweight_2", &trigweight_2, &b_trigweight_2);
   fChain->SetBranchAddress("idisoweight_1", &idisoweight_1, &b_idisoweight_1);
   fChain->SetBranchAddress("idisoweight_2", &idisoweight_2, &b_idisoweight_2);
   fChain->SetBranchAddress("sf_trk", &sf_trk, &b_sf_trk);
   fChain->SetBranchAddress("stitchedWeight", &stitchedWeight, &b_stitchedWeight);
   fChain->SetBranchAddress("topPtReweightWeightRun1", &topPtReweightWeightRun1, &b_topPtReweightWeightRun1);
   fChain->SetBranchAddress("topPtReweightWeightRun2", &topPtReweightWeightRun2, &b_topPtReweightWeightRun2);
   fChain->SetBranchAddress("eleTauFakeRateWeight", &eleTauFakeRateWeight, &b_eleTauFakeRateWeight);
   fChain->SetBranchAddress("muTauFakeRateWeight", &muTauFakeRateWeight, &b_muTauFakeRateWeight);
   fChain->SetBranchAddress("zPtReweightWeight", &zPtReweightWeight, &b_zPtReweightWeight);
   
   fChain->SetBranchAddress("trg_singlemu_22", &trg_singlemu_22, &b_trg_singlemu_22);
   fChain->SetBranchAddress("trg_doubletau_35", &trg_doubletau_35, &b_trg_doubletau_35);
   fChain->SetBranchAddress("trg_crossmu_mu19tau20", &trg_crossmu_mu19tau20, &b_trg_crossmu_mu19tau20);
   fChain->SetBranchAddress("trg_singleelectron_25_eta2p1", &trg_singleelectron_25_eta2p1, &b_trg_singleelectron_25_eta2p1);
   
   fChain->SetBranchAddress("gen_Mll", &gen_Mll, &b_gen_Mll);
   fChain->SetBranchAddress("genpX", &genpX, &b_genpX);
   fChain->SetBranchAddress("genpY", &genpY, &b_genpY);
   fChain->SetBranchAddress("genpZ", &genpZ, &b_genpZ);
   fChain->SetBranchAddress("gen_vis_Mll", &gen_vis_Mll, &b_gen_vis_Mll);
   fChain->SetBranchAddress("vispX", &vispX, &b_vispX);
   fChain->SetBranchAddress("vispY", &vispY, &b_vispY);
   fChain->SetBranchAddress("vispZ", &vispZ, &b_vispZ);
   fChain->SetBranchAddress("npv", &npv, &b_npv);
   fChain->SetBranchAddress("npu", &npu, &b_npu);
   fChain->SetBranchAddress("rho", &rho, &b_rho);
   fChain->SetBranchAddress("NUP", &NUP, &b_NUP);
//    fChain->SetBranchAddress("passBadMuonFilter", &passBadMuonFilter, &b_passBadMuonFilter);
//    fChain->SetBranchAddress("passBadChargedHadronFilter", &passBadChargedHadronFilter, &b_passBadChargedHadronFilter);
//    fChain->SetBranchAddress("flagHBHENoiseFilter", &flagHBHENoiseFilter, &b_flagHBHENoiseFilter);
//    fChain->SetBranchAddress("flagHBHENoiseIsoFilter", &flagHBHENoiseIsoFilter, &b_flagHBHENoiseIsoFilter);
//    fChain->SetBranchAddress("flagEcalDeadCellTriggerPrimitiveFilter", &flagEcalDeadCellTriggerPrimitiveFilter, &b_flagEcalDeadCellTriggerPrimitiveFilter);
//    fChain->SetBranchAddress("flagGoodVertices", &flagGoodVertices, &b_flagGoodVertices);
//    fChain->SetBranchAddress("flagEeBadScFilter", &flagEeBadScFilter, &b_flagEeBadScFilter);
//    fChain->SetBranchAddress("flagGlobalTightHalo2016Filter", &flagGlobalTightHalo2016Filter, &b_flagGlobalTightHalo2016Filter);
   fChain->SetBranchAddress("flagMETFilter", &flagMETFilter, &b_flagMETFilter);
//    fChain->SetBranchAddress("matchedJetPt03_1", &matchedJetPt03_1, &b_matchedJetPt03_1);
//    fChain->SetBranchAddress("matchedJetPt05_1", &matchedJetPt05_1, &b_matchedJetPt05_1);
//    fChain->SetBranchAddress("matchedJetPt03_2", &matchedJetPt03_2, &b_matchedJetPt03_2);
//    fChain->SetBranchAddress("matchedJetPt05_2", &matchedJetPt05_2, &b_matchedJetPt05_2);
   fChain->SetBranchAddress("gen_match_1", &gen_match_1, &b_gen_match_1);
   fChain->SetBranchAddress("gen_match_2", &gen_match_2, &b_gen_match_2);
   fChain->SetBranchAddress("gen_match_jetId_1", &gen_match_jetId_1, &b_gen_match_jetId_1);
   fChain->SetBranchAddress("gen_match_jetId_2", &gen_match_jetId_2, &b_gen_match_jetId_2);
   fChain->SetBranchAddress("genJets", &genJets, &b_genJets);
   fChain->SetBranchAddress("pt_1", &pt_1, &b_pt_1);
   fChain->SetBranchAddress("phi_1", &phi_1, &b_phi_1);
   fChain->SetBranchAddress("eta_1", &eta_1, &b_eta_1);
   fChain->SetBranchAddress("eta_SC_1", &eta_SC_1, &b_eta_SC_1);
   fChain->SetBranchAddress("m_1", &m_1, &b_m_1);
   fChain->SetBranchAddress("q_1", &q_1, &b_q_1);
   fChain->SetBranchAddress("d0_1", &d0_1, &b_d0_1);
   fChain->SetBranchAddress("dZ_1", &dZ_1, &b_dZ_1);
   fChain->SetBranchAddress("mt_1", &mt_1, &b_mt_1);
   fChain->SetBranchAddress("iso_1", &iso_1, &b_iso_1);
   fChain->SetBranchAddress("againstElectronLooseMVA6_1", &againstElectronLooseMVA6_1, &b_againstElectronLooseMVA6_1);
   fChain->SetBranchAddress("againstElectronMediumMVA6_1", &againstElectronMediumMVA6_1, &b_againstElectronMediumMVA6_1);
   fChain->SetBranchAddress("againstElectronTightMVA6_1", &againstElectronTightMVA6_1, &b_againstElectronTightMVA6_1);
   fChain->SetBranchAddress("againstElectronVLooseMVA6_1", &againstElectronVLooseMVA6_1, &b_againstElectronVLooseMVA6_1);
   fChain->SetBranchAddress("againstElectronVTightMVA6_1", &againstElectronVTightMVA6_1, &b_againstElectronVTightMVA6_1);
   fChain->SetBranchAddress("againstMuonLoose3_1", &againstMuonLoose3_1, &b_againstMuonLoose3_1);
   fChain->SetBranchAddress("againstMuonTight3_1", &againstMuonTight3_1, &b_againstMuonTight3_1);
   fChain->SetBranchAddress("byCombinedIsolationDeltaBetaCorrRaw3Hits_1", &byCombinedIsolationDeltaBetaCorrRaw3Hits_1, &b_byCombinedIsolationDeltaBetaCorrRaw3Hits_1);
   fChain->SetBranchAddress("byIsolationMVA3newDMwoLTraw_1", &byIsolationMVA3newDMwoLTraw_1, &b_byIsolationMVA3newDMwoLTraw_1);
   fChain->SetBranchAddress("byIsolationMVA3oldDMwoLTraw_1", &byIsolationMVA3oldDMwoLTraw_1, &b_byIsolationMVA3oldDMwoLTraw_1);
   fChain->SetBranchAddress("byIsolationMVA3newDMwLTraw_1", &byIsolationMVA3newDMwLTraw_1, &b_byIsolationMVA3newDMwLTraw_1);
   fChain->SetBranchAddress("byIsolationMVA3oldDMwLTraw_1", &byIsolationMVA3oldDMwLTraw_1, &b_byIsolationMVA3oldDMwLTraw_1);
   fChain->SetBranchAddress("byVLooseIsolationMVArun2017v2DBoldDMwLT2017_1", &byVLooseIsolationMVArun2017v2DBoldDMwLT2017_1, &b_byVLooseIsolationMVArun2017v2DBoldDMwLT2017_1);
   fChain->SetBranchAddress("byLooseIsolationMVArun2017v2DBoldDMwLT2017_1", &byLooseIsolationMVArun2017v2DBoldDMwLT2017_1, &b_byLooseIsolationMVArun2017v2DBoldDMwLT2017_1);
   fChain->SetBranchAddress("byMediumIsolationMVArun2017v2DBoldDMwLT2017_1", &byMediumIsolationMVArun2017v2DBoldDMwLT2017_1, &b_byMediumIsolationMVArun2017v2DBoldDMwLT2017_1);
   fChain->SetBranchAddress("byTightIsolationMVArun2017v2DBoldDMwLT2017_1", &byTightIsolationMVArun2017v2DBoldDMwLT2017_1, &b_byTightIsolationMVArun2017v2DBoldDMwLT2017_1);
   fChain->SetBranchAddress("byVTightIsolationMVArun2017v2DBoldDMwLT2017_1", &byVTightIsolationMVArun2017v2DBoldDMwLT2017_1, &b_byVTightIsolationMVArun2017v2DBoldDMwLT2017_1);
   
   fChain->SetBranchAddress("byVVVLooseIsolationDeepTau2017v2VSjet_1", &byVVVLooseIsolationDeepTau2017v2VSjet_1, &b_byVVVLooseIsolationDeepTau2017v2VSjet_1);
   fChain->SetBranchAddress("byVVLooseIsolationDeepTau2017v2VSjet_1", &byVVLooseIsolationDeepTau2017v2VSjet_1, &b_byVVLooseIsolationDeepTau2017v2VSjet_1);
   fChain->SetBranchAddress("byVLooseIsolationDeepTau2017v2VSjet_1", &byVLooseIsolationDeepTau2017v2VSjet_1, &b_byVLooseIsolationDeepTau2017v2VSjet_1);
   fChain->SetBranchAddress("byLooseIsolationDeepTau2017v2VSjet_1", &byLooseIsolationDeepTau2017v2VSjet_1, &b_byLooseIsolationDeepTau2017v2VSjet_1);
   fChain->SetBranchAddress("byMediumIsolationDeepTau2017v2VSjet_1", &byMediumIsolationDeepTau2017v2VSjet_1, &b_byMediumIsolationDeepTau2017v2VSjet_1);
   fChain->SetBranchAddress("byTightIsolationDeepTau2017v2VSjet_1", &byTightIsolationDeepTau2017v2VSjet_1, &b_byTightIsolationDeepTau2017v2VSjet_1);
   fChain->SetBranchAddress("byVTightIsolationDeepTau2017v2VSjet_1", &byVTightIsolationDeepTau2017v2VSjet_1, &b_byVTightIsolationDeepTau2017v2VSjet_1);
   fChain->SetBranchAddress("byVVTightIsolationDeepTau2017v2VSjet_1", &byVVTightIsolationDeepTau2017v2VSjet_1, &b_byVVTightIsolationDeepTau2017v2VSjet_1);


//    fChain->SetBranchAddress("byVLooseIsolationMVArun2v1DBnewDMwLT_1", &byVLooseIsolationMVArun2v1DBnewDMwLT_1, &b_byVLooseIsolationMVArun2v1DBnewDMwLT_1);
//    fChain->SetBranchAddress("byLooseIsolationMVArun2v1DBnewDMwLT_1", &byLooseIsolationMVArun2v1DBnewDMwLT_1, &b_byLooseIsolationMVArun2v1DBnewDMwLT_1);
//    fChain->SetBranchAddress("byMediumIsolationMVArun2v1DBnewDMwLT_1", &byMediumIsolationMVArun2v1DBnewDMwLT_1, &b_byMediumIsolationMVArun2v1DBnewDMwLT_1);
//    fChain->SetBranchAddress("byTightIsolationMVArun2v1DBnewDMwLT_1", &byTightIsolationMVArun2v1DBnewDMwLT_1, &b_byTightIsolationMVArun2v1DBnewDMwLT_1);
//    fChain->SetBranchAddress("byVTightIsolationMVArun2v1DBnewDMwLT_1", &byVTightIsolationMVArun2v1DBnewDMwLT_1, &b_byVTightIsolationMVArun2v1DBnewDMwLT_1);
//    fChain->SetBranchAddress("byRerunMVAIdVLoose_1", &byRerunMVAIdVLoose_1, &b_byRerunMVAIdVLoose_1);
//    fChain->SetBranchAddress("byRerunMVAIdLoose_1", &byRerunMVAIdLoose_1, &b_byRerunMVAIdLoose_1);
//    fChain->SetBranchAddress("byRerunMVAIdMedium_1", &byRerunMVAIdMedium_1, &b_byRerunMVAIdMedium_1);
//    fChain->SetBranchAddress("byRerunMVAIdTight_1", &byRerunMVAIdTight_1, &b_byRerunMVAIdTight_1);
//    fChain->SetBranchAddress("byRerunMVAIdVTight_1", &byRerunMVAIdVTight_1, &b_byRerunMVAIdVTight_1);
//    fChain->SetBranchAddress("byRerunMVAIdVVTight_1", &byRerunMVAIdVVTight_1, &b_byRerunMVAIdVVTight_1);
//    fChain->SetBranchAddress("idMVANewDM_1", &idMVANewDM_1, &b_idMVANewDM_1);
   fChain->SetBranchAddress("chargedIsoPtSum_1", &chargedIsoPtSum_1, &b_chargedIsoPtSum_1);
   fChain->SetBranchAddress("neutralIsoPtSum_1", &neutralIsoPtSum_1, &b_neutralIsoPtSum_1);
   fChain->SetBranchAddress("puCorrPtSum_1", &puCorrPtSum_1, &b_puCorrPtSum_1);
   fChain->SetBranchAddress("decayModeFindingOldDMs_1", &decayModeFindingOldDMs_1, &b_decayModeFindingOldDMs_1);
   fChain->SetBranchAddress("decayModeFindingNewDMs_1", &decayModeFindingNewDMs_1, &b_decayModeFindingNewDMs_1);
   fChain->SetBranchAddress("decayMode_1", &decayMode_1, &b_decayMode_1);
   fChain->SetBranchAddress("id_e_mva_nt_loose_1", &id_e_mva_nt_loose_1, &b_id_e_mva_nt_loose_1);
   fChain->SetBranchAddress("id_m_loose_1", &id_m_loose_1, &b_id_m_loose_1);
   fChain->SetBranchAddress("id_m_medium_1", &id_m_medium_1, &b_id_m_medium_1);
   fChain->SetBranchAddress("id_m_tight_1", &id_m_tight_1, &b_id_m_tight_1);
   fChain->SetBranchAddress("id_m_highpt_1", &id_m_highpt_1, &b_id_m_highpt_1);
   fChain->SetBranchAddress("id_e_cut_veto_1", &id_e_cut_veto_1, &b_id_e_cut_veto_1);
   fChain->SetBranchAddress("id_e_cut_loose_1", &id_e_cut_loose_1, &b_id_e_cut_loose_1);
   fChain->SetBranchAddress("id_e_cut_medium_1", &id_e_cut_medium_1, &b_id_e_cut_medium_1);
   fChain->SetBranchAddress("id_e_cut_tight_1", &id_e_cut_tight_1, &b_id_e_cut_tight_1);
   fChain->SetBranchAddress("antilep_tauscaling", &antilep_tauscaling, &b_antilep_tauscaling);
   fChain->SetBranchAddress("pt_2", &pt_2, &b_pt_2);
   fChain->SetBranchAddress("phi_2", &phi_2, &b_phi_2);
   fChain->SetBranchAddress("eta_2", &eta_2, &b_eta_2);
   fChain->SetBranchAddress("m_2", &m_2, &b_m_2);
   fChain->SetBranchAddress("q_2", &q_2, &b_q_2);
   fChain->SetBranchAddress("d0_2", &d0_2, &b_d0_2);
   fChain->SetBranchAddress("dZ_2", &dZ_2, &b_dZ_2);
   fChain->SetBranchAddress("mt_2", &mt_2, &b_mt_2);
   fChain->SetBranchAddress("iso_2", &iso_2, &b_iso_2);
   fChain->SetBranchAddress("againstElectronLooseMVA6_2", &againstElectronLooseMVA6_2, &b_againstElectronLooseMVA6_2);
   fChain->SetBranchAddress("againstElectronMediumMVA6_2", &againstElectronMediumMVA6_2, &b_againstElectronMediumMVA6_2);
   fChain->SetBranchAddress("againstElectronTightMVA6_2", &againstElectronTightMVA6_2, &b_againstElectronTightMVA6_2);
   fChain->SetBranchAddress("againstElectronVLooseMVA6_2", &againstElectronVLooseMVA6_2, &b_againstElectronVLooseMVA6_2);
   fChain->SetBranchAddress("againstElectronVTightMVA6_2", &againstElectronVTightMVA6_2, &b_againstElectronVTightMVA6_2);
   fChain->SetBranchAddress("againstMuonLoose3_2", &againstMuonLoose3_2, &b_againstMuonLoose3_2);
   fChain->SetBranchAddress("againstMuonTight3_2", &againstMuonTight3_2, &b_againstMuonTight3_2);
   fChain->SetBranchAddress("byCombinedIsolationDeltaBetaCorrRaw3Hits_2", &byCombinedIsolationDeltaBetaCorrRaw3Hits_2, &b_byCombinedIsolationDeltaBetaCorrRaw3Hits_2);
   fChain->SetBranchAddress("byIsolationMVA3newDMwoLTraw_2", &byIsolationMVA3newDMwoLTraw_2, &b_byIsolationMVA3newDMwoLTraw_2);
   fChain->SetBranchAddress("byIsolationMVA3oldDMwoLTraw_2", &byIsolationMVA3oldDMwoLTraw_2, &b_byIsolationMVA3oldDMwoLTraw_2);
   fChain->SetBranchAddress("byIsolationMVA3newDMwLTraw_2", &byIsolationMVA3newDMwLTraw_2, &b_byIsolationMVA3newDMwLTraw_2);
   fChain->SetBranchAddress("byIsolationMVA3oldDMwLTraw_2", &byIsolationMVA3oldDMwLTraw_2, &b_byIsolationMVA3oldDMwLTraw_2);
   fChain->SetBranchAddress("byVLooseIsolationMVArun2017v2DBoldDMwLT2017_2", &byVLooseIsolationMVArun2017v2DBoldDMwLT2017_2, &b_byVLooseIsolationMVArun2017v2DBoldDMwLT2017_2);
   fChain->SetBranchAddress("byLooseIsolationMVArun2017v2DBoldDMwLT2017_2", &byLooseIsolationMVArun2017v2DBoldDMwLT2017_2, &b_byLooseIsolationMVArun2017v2DBoldDMwLT2017_2);
   fChain->SetBranchAddress("byMediumIsolationMVArun2017v2DBoldDMwLT2017_2", &byMediumIsolationMVArun2017v2DBoldDMwLT2017_2, &b_byMediumIsolationMVArun2017v2DBoldDMwLT2017_2);
   fChain->SetBranchAddress("byTightIsolationMVArun2017v2DBoldDMwLT2017_2", &byTightIsolationMVArun2017v2DBoldDMwLT2017_2, &b_byTightIsolationMVArun2017v2DBoldDMwLT2017_2);
   fChain->SetBranchAddress("byVTightIsolationMVArun2017v2DBoldDMwLT2017_2", &byVTightIsolationMVArun2017v2DBoldDMwLT2017_2, &b_byVTightIsolationMVArun2017v2DBoldDMwLT2017_2);
   
   fChain->SetBranchAddress("byVVVLooseIsolationDeepTau2017v2VSjet_2", &byVVVLooseIsolationDeepTau2017v2VSjet_2, &b_byVVVLooseIsolationDeepTau2017v2VSjet_2);
   fChain->SetBranchAddress("byVVLooseIsolationDeepTau2017v2VSjet_2", &byVVLooseIsolationDeepTau2017v2VSjet_2, &b_byVVLooseIsolationDeepTau2017v2VSjet_2);
   fChain->SetBranchAddress("byVLooseIsolationDeepTau2017v2VSjet_2", &byVLooseIsolationDeepTau2017v2VSjet_2, &b_byVLooseIsolationDeepTau2017v2VSjet_2);
   fChain->SetBranchAddress("byLooseIsolationDeepTau2017v2VSjet_2", &byLooseIsolationDeepTau2017v2VSjet_2, &b_byLooseIsolationDeepTau2017v2VSjet_2);
   fChain->SetBranchAddress("byMediumIsolationDeepTau2017v2VSjet_2", &byMediumIsolationDeepTau2017v2VSjet_2, &b_byMediumIsolationDeepTau2017v2VSjet_2);
   fChain->SetBranchAddress("byTightIsolationDeepTau2017v2VSjet_2", &byTightIsolationDeepTau2017v2VSjet_2, &b_byTightIsolationDeepTau2017v2VSjet_2);
   fChain->SetBranchAddress("byVTightIsolationDeepTau2017v2VSjet_2", &byVTightIsolationDeepTau2017v2VSjet_2, &b_byVTightIsolationDeepTau2017v2VSjet_2);
   fChain->SetBranchAddress("byVVTightIsolationDeepTau2017v2VSjet_2", &byVVTightIsolationDeepTau2017v2VSjet_2, &b_byVVTightIsolationDeepTau2017v2VSjet_2);



//    fChain->SetBranchAddress("byVLooseIsolationMVArun2v1DBnewDMwLT_2", &byVLooseIsolationMVArun2v1DBnewDMwLT_2, &b_byVLooseIsolationMVArun2v1DBnewDMwLT_2);
//    fChain->SetBranchAddress("byLooseIsolationMVArun2v1DBnewDMwLT_2", &byLooseIsolationMVArun2v1DBnewDMwLT_2, &b_byLooseIsolationMVArun2v1DBnewDMwLT_2);
//    fChain->SetBranchAddress("byMediumIsolationMVArun2v1DBnewDMwLT_2", &byMediumIsolationMVArun2v1DBnewDMwLT_2, &b_byMediumIsolationMVArun2v1DBnewDMwLT_2);
//    fChain->SetBranchAddress("byTightIsolationMVArun2v1DBnewDMwLT_2", &byTightIsolationMVArun2v1DBnewDMwLT_2, &b_byTightIsolationMVArun2v1DBnewDMwLT_2);
//    fChain->SetBranchAddress("byVTightIsolationMVArun2v1DBnewDMwLT_2", &byVTightIsolationMVArun2v1DBnewDMwLT_2, &b_byVTightIsolationMVArun2v1DBnewDMwLT_2);
//    fChain->SetBranchAddress("byRerunMVAIdVLoose_2", &byRerunMVAIdVLoose_2, &b_byRerunMVAIdVLoose_2);
//    fChain->SetBranchAddress("byRerunMVAIdLoose_2", &byRerunMVAIdLoose_2, &b_byRerunMVAIdLoose_2);
//    fChain->SetBranchAddress("byRerunMVAIdMedium_2", &byRerunMVAIdMedium_2, &b_byRerunMVAIdMedium_2);
//    fChain->SetBranchAddress("byRerunMVAIdTight_2", &byRerunMVAIdTight_2, &b_byRerunMVAIdTight_2);
//    fChain->SetBranchAddress("byRerunMVAIdVTight_2", &byRerunMVAIdVTight_2, &b_byRerunMVAIdVTight_2);
//    fChain->SetBranchAddress("byRerunMVAIdVVTight_2", &byRerunMVAIdVVTight_2, &b_byRerunMVAIdVVTight_2);
//    fChain->SetBranchAddress("idMVANewDM_2", &idMVANewDM_2, &b_idMVANewDM_2);
   fChain->SetBranchAddress("chargedIsoPtSum_2", &chargedIsoPtSum_2, &b_chargedIsoPtSum_2);
   fChain->SetBranchAddress("neutralIsoPtSum_2", &neutralIsoPtSum_2, &b_neutralIsoPtSum_2);
   fChain->SetBranchAddress("puCorrPtSum_2", &puCorrPtSum_2, &b_puCorrPtSum_2);
   fChain->SetBranchAddress("decayModeFindingOldDMs_2", &decayModeFindingOldDMs_2, &b_decayModeFindingOldDMs_2);
   fChain->SetBranchAddress("decayModeFindingNewDMs_2", &decayModeFindingNewDMs_2, &b_decayModeFindingNewDMs_2);
   fChain->SetBranchAddress("decayMode_2", &decayMode_2, &b_decayMode_2);
   fChain->SetBranchAddress("pzetavis", &pzetavis, &b_pzetavis);
   fChain->SetBranchAddress("pzetamiss", &pzetamiss, &b_pzetamiss);
   fChain->SetBranchAddress("dzeta", &dzeta, &b_dzeta);
   fChain->SetBranchAddress("pt_tt", &pt_tt, &b_pt_tt);
   fChain->SetBranchAddress("pt_vis", &pt_vis, &b_pt_vis);
   fChain->SetBranchAddress("dphi", &dphi, &b_dphi);
//    fChain->SetBranchAddress("mt_3", &mt_3, &b_mt_3);
   fChain->SetBranchAddress("mt_tot", &mt_tot, &b_mt_tot);
//    fChain->SetBranchAddress("pfpt_tt", &pfpt_tt, &b_pfpt_tt);
   fChain->SetBranchAddress("m_vis", &m_vis, &b_m_vis);
   fChain->SetBranchAddress("m_coll", &m_coll, &b_m_coll);
   fChain->SetBranchAddress("pt_sum", &pt_sum, &b_pt_sum);
   fChain->SetBranchAddress("dr_leptau", &dr_leptau, &b_dr_leptau);
   fChain->SetBranchAddress("jeta1eta2", &jeta1eta2, &b_jeta1eta2);
   fChain->SetBranchAddress("met_centrality", &met_centrality, &b_met_centrality);
   fChain->SetBranchAddress("lep_etacentrality", &lep_etacentrality, &b_lep_etacentrality);
   fChain->SetBranchAddress("sphericity", &sphericity, &b_sphericity);
   
   fChain->SetBranchAddress("addlepton_p4", &addlepton_p4, &b_addlepton_p4);			//added
   fChain->SetBranchAddress("addlepton_iso", &addlepton_iso, &b_addlepton_iso);			//added
   fChain->SetBranchAddress("addlepton_pdgId", &addlepton_pdgId, &b_addlepton_pdgId);	//added
   fChain->SetBranchAddress("addlepton_tauID", &addlepton_tauID, &b_addlepton_tauID);	//added
   fChain->SetBranchAddress("addlepton_tauDM", &addlepton_tauDM, &b_addlepton_tauDM);	//added
   fChain->SetBranchAddress("addlepton_tauAntiEle", &addlepton_tauAntiEle, &b_addlepton_tauAntiEle);	//added
   fChain->SetBranchAddress("addlepton_tauAntiMu", &addlepton_tauAntiMu, &b_addlepton_tauAntiMu);	//added
   fChain->SetBranchAddress("addlepton_tauCombIso", &addlepton_tauCombIso, &b_addlepton_tauCombIso);	//added
   fChain->SetBranchAddress("addlepton_mc_match", &addlepton_mc_match, &b_addlepton_mc_match);	//added
   fChain->SetBranchAddress("addlepton_mvis", &addlepton_mvis, &b_addlepton_mvis);	//added
   
   fChain->SetBranchAddress("nadditionalMu", &nadditionalMu, &b_nadditionalMu);
   fChain->SetBranchAddress("addmuon_pt", &addmuon_pt, &b_addmuon_pt);
   fChain->SetBranchAddress("addmuon_eta", &addmuon_eta, &b_addmuon_eta);
   fChain->SetBranchAddress("addmuon_phi", &addmuon_phi, &b_addmuon_phi);
   fChain->SetBranchAddress("addmuon_m", &addmuon_m, &b_addmuon_m);
   fChain->SetBranchAddress("addmuon_q", &addmuon_q, &b_addmuon_q);
   fChain->SetBranchAddress("addmuon_iso", &addmuon_iso, &b_addmuon_iso);
   fChain->SetBranchAddress("addmuon_gen_match", &addmuon_gen_match, &b_addmuon_gen_match);
   fChain->SetBranchAddress("nadditionalEle", &nadditionalEle, &b_nadditionalEle);
   fChain->SetBranchAddress("addele_pt", &addele_pt, &b_addele_pt);
   fChain->SetBranchAddress("addele_eta", &addele_eta, &b_addele_eta);
   fChain->SetBranchAddress("addele_phi", &addele_phi, &b_addele_phi);
   fChain->SetBranchAddress("addele_m", &addele_m, &b_addele_m);
   fChain->SetBranchAddress("addele_q", &addele_q, &b_addele_q);
   fChain->SetBranchAddress("addele_iso", &addele_iso, &b_addele_iso);
   fChain->SetBranchAddress("addele_gen_match", &addele_gen_match, &b_addele_gen_match);
   fChain->SetBranchAddress("nadditionalTau", &nadditionalTau, &b_nadditionalTau);
   fChain->SetBranchAddress("addtau_pt", &addtau_pt, &b_addtau_pt);
   fChain->SetBranchAddress("addtau_eta", &addtau_eta, &b_addtau_eta);
   fChain->SetBranchAddress("addtau_phi", &addtau_phi, &b_addtau_phi);
   fChain->SetBranchAddress("addtau_m", &addtau_m, &b_addtau_m);
   fChain->SetBranchAddress("addtau_q", &addtau_q, &b_addtau_q);

   fChain->SetBranchAddress("addtau_byVVVLooseIsolationDeepTau2017v2VSjet", &addtau_byVVVLooseIsolationDeepTau2017v2VSjet, &b_addtau_byVVVLooseIsolationDeepTau2017v2VSjet);
   fChain->SetBranchAddress("addtau_byVVLooseIsolationDeepTau2017v2VSjet", &addtau_byVVLooseIsolationDeepTau2017v2VSjet, &b_addtau_byVVLooseIsolationDeepTau2017v2VSjet);
   fChain->SetBranchAddress("addtau_byVLooseIsolationDeepTau2017v2VSjet", &addtau_byVLooseIsolationDeepTau2017v2VSjet, &b_addtau_byVLooseIsolationDeepTau2017v2VSjet);
   fChain->SetBranchAddress("addtau_byLooseIsolationDeepTau2017v2VSjet", &addtau_byLooseIsolationDeepTau2017v2VSjet, &b_addtau_byLooseIsolationDeepTau2017v2VSjet);
   fChain->SetBranchAddress("addtau_byMediumIsolationDeepTau2017v2VSjet", &addtau_byMediumIsolationDeepTau2017v2VSjet, &b_addtau_byMediumIsolationDeepTau2017v2VSjet);
   fChain->SetBranchAddress("addtau_byTightIsolationDeepTau2017v2VSjet", &addtau_byTightIsolationDeepTau2017v2VSjet, &b_addtau_byTightIsolationDeepTau2017v2VSjet);
   fChain->SetBranchAddress("addtau_byVTightIsolationDeepTau2017v2VSjet", &addtau_byVTightIsolationDeepTau2017v2VSjet, &b_addtau_byVTightIsolationDeepTau2017v2VSjet);
   fChain->SetBranchAddress("addtau_byVVTightIsolationDeepTau2017v2VSjet", &addtau_byVVTightIsolationDeepTau2017v2VSjet, &b_addtau_byVVTightIsolationDeepTau2017v2VSjet);


//    fChain->SetBranchAddress("addtau_byVLooseIsolationMVArun2v1DBnewDMwLT", &addtau_byVLooseIsolationMVArun2v1DBnewDMwLT, &b_addtau_byVLooseIsolationMVArun2v1DBnewDMwLT);
//    fChain->SetBranchAddress("addtau_byLooseIsolationMVArun2v1DBnewDMwLT", &addtau_byLooseIsolationMVArun2v1DBnewDMwLT, &b_addtau_byLooseIsolationMVArun2v1DBnewDMwLT);
//    fChain->SetBranchAddress("addtau_byMediumIsolationMVArun2v1DBnewDMwLT", &addtau_byMediumIsolationMVArun2v1DBnewDMwLT, &b_addtau_byMediumIsolationMVArun2v1DBnewDMwLT);
//    fChain->SetBranchAddress("addtau_byTightIsolationMVArun2v1DBnewDMwLT", &addtau_byTightIsolationMVArun2v1DBnewDMwLT, &b_addtau_byTightIsolationMVArun2v1DBnewDMwLT);
//    fChain->SetBranchAddress("addtau_byVTightIsolationMVArun2v1DBnewDMwLT", &addtau_byVTightIsolationMVArun2v1DBnewDMwLT, &b_addtau_byVTightIsolationMVArun2v1DBnewDMwLT);
//    fChain->SetBranchAddress("addtau_NewMVAIDVLoose", &addtau_NewMVAIDVLoose, &b_addtau_NewMVAIDVLoose);
//    fChain->SetBranchAddress("addtau_NewMVAIDLoose", &addtau_NewMVAIDLoose, &b_addtau_NewMVAIDLoose);
//    fChain->SetBranchAddress("addtau_NewMVAIDMedium", &addtau_NewMVAIDMedium, &b_addtau_NewMVAIDMedium);
//    fChain->SetBranchAddress("addtau_NewMVAIDTight", &addtau_NewMVAIDTight, &b_addtau_NewMVAIDTight);
//    fChain->SetBranchAddress("addtau_NewMVAIDVTight", &addtau_NewMVAIDVTight, &b_addtau_NewMVAIDVTight);
//    fChain->SetBranchAddress("addtau_NewMVAIDVVTight", &addtau_NewMVAIDVVTight, &b_addtau_NewMVAIDVVTight);
   fChain->SetBranchAddress("addtau_passesTauLepVetos", &addtau_passesTauLepVetos, &b_addtau_passesTauLepVetos);
   fChain->SetBranchAddress("addtau_decayMode", &addtau_decayMode, &b_addtau_decayMode);
   fChain->SetBranchAddress("addtau_d0", &addtau_d0, &b_addtau_d0);
   fChain->SetBranchAddress("addtau_dZ", &addtau_dZ, &b_addtau_dZ);
   fChain->SetBranchAddress("addtau_gen_match", &addtau_gen_match, &b_addtau_gen_match);
   fChain->SetBranchAddress("addtau_mt", &addtau_mt, &b_addtau_mt);
   fChain->SetBranchAddress("addtau_mvis", &addtau_mvis, &b_addtau_mvis);
   fChain->SetBranchAddress("passesTauLepVetos", &passesTauLepVetos, &b_passesTauLepVetos);
   fChain->SetBranchAddress("passesThirdLepVeto", &passesThirdLepVeto, &b_passesThirdLepVeto);
   fChain->SetBranchAddress("passesDiMuonVeto", &passesDiMuonVeto, &b_passesDiMuonVeto);
   fChain->SetBranchAddress("passesDiElectronVeto", &passesDiElectronVeto, &b_passesDiElectronVeto);
//    fChain->SetBranchAddress("matchXTrig_obj", &matchXTrig_obj, &b_matchXTrig_obj);
   fChain->SetBranchAddress("dilepton_veto", &dilepton_veto, &b_dilepton_veto);
   fChain->SetBranchAddress("extraelec_veto", &extraelec_veto, &b_extraelec_veto);
   fChain->SetBranchAddress("extramuon_veto", &extramuon_veto, &b_extramuon_veto);
   fChain->SetBranchAddress("met", &met, &b_met);
   fChain->SetBranchAddress("metphi", &metphi, &b_metphi);
   fChain->SetBranchAddress("met_ex", &met_ex, &b_met_ex);
   fChain->SetBranchAddress("met_ey", &met_ey, &b_met_ey);
   fChain->SetBranchAddress("metcov00", &metcov00, &b_metcov00);
   fChain->SetBranchAddress("metcov01", &metcov01, &b_metcov01);
   fChain->SetBranchAddress("metcov10", &metcov10, &b_metcov10);
   fChain->SetBranchAddress("metcov11", &metcov11, &b_metcov11);
   fChain->SetBranchAddress("mjj", &mjj, &b_mjj);
// //    fChain->SetBranchAddress("mjjUp", &mjjUp, &b_mjjUp);
//    fChain->SetBranchAddress("mjjDown", &mjjDown, &b_mjjDown);
   fChain->SetBranchAddress("jdeta", &jdeta, &b_jdeta);
//    fChain->SetBranchAddress("jdetaUp", &jdetaUp, &b_jdetaUp);
//    fChain->SetBranchAddress("jdetaDown", &jdetaDown, &b_jdetaDown);
   fChain->SetBranchAddress("njetingap", &njetingap, &b_njetingap);
   fChain->SetBranchAddress("njetingap20", &njetingap20, &b_njetingap20);
   fChain->SetBranchAddress("dijetpt", &dijetpt, &b_dijetpt);
   fChain->SetBranchAddress("dijetphi", &dijetphi, &b_dijetphi);
   fChain->SetBranchAddress("jdphi", &jdphi, &b_jdphi);
   fChain->SetBranchAddress("nbtag", &nbtag, &b_nbtag);
   fChain->SetBranchAddress("njets", &njets, &b_njets);
//    fChain->SetBranchAddress("njetsUp", &njetsUp, &b_njetsUp);
//    fChain->SetBranchAddress("njetsDown", &njetsDown, &b_njetsDown);
   fChain->SetBranchAddress("njetspt20", &njetspt20, &b_njetspt20);
   fChain->SetBranchAddress("jpt_1", &jpt_1, &b_jpt_1);
//    fChain->SetBranchAddress("jptUp_1", &jptUp_1, &b_jptUp_1);
//    fChain->SetBranchAddress("jptDown_1", &jptDown_1, &b_jptDown_1);
   fChain->SetBranchAddress("jeta_1", &jeta_1, &b_jeta_1);
   fChain->SetBranchAddress("jphi_1", &jphi_1, &b_jphi_1);
   fChain->SetBranchAddress("jm_1", &jm_1, &b_jm_1);
   fChain->SetBranchAddress("jrawf_1", &jrawf_1, &b_jrawf_1);
   fChain->SetBranchAddress("jmva_1", &jmva_1, &b_jmva_1);
   fChain->SetBranchAddress("jcsv_1", &jcsv_1, &b_jcsv_1);
   fChain->SetBranchAddress("jpt_2", &jpt_2, &b_jpt_2);
//    fChain->SetBranchAddress("jptUp_2", &jptUp_2, &b_jptUp_2);
//    fChain->SetBranchAddress("jptDown_2", &jptDown_2, &b_jptDown_2);
   fChain->SetBranchAddress("jeta_2", &jeta_2, &b_jeta_2);
   fChain->SetBranchAddress("jphi_2", &jphi_2, &b_jphi_2);
   fChain->SetBranchAddress("jm_2", &jm_2, &b_jm_2);
   fChain->SetBranchAddress("jrawf_2", &jrawf_2, &b_jrawf_2);
   fChain->SetBranchAddress("jmva_2", &jmva_2, &b_jmva_2);
   fChain->SetBranchAddress("jcsv_2", &jcsv_2, &b_jcsv_2);
   fChain->SetBranchAddress("bpt_1", &bpt_1, &b_bpt_1);
   fChain->SetBranchAddress("beta_1", &beta_1, &b_beta_1);
   fChain->SetBranchAddress("bphi_1", &bphi_1, &b_bphi_1);
   fChain->SetBranchAddress("brawf_1", &brawf_1, &b_brawf_1);
   fChain->SetBranchAddress("bmva_1", &bmva_1, &b_bmva_1);
   fChain->SetBranchAddress("bcsv_1", &bcsv_1, &b_bcsv_1);
   fChain->SetBranchAddress("bpt_2", &bpt_2, &b_bpt_2);
   fChain->SetBranchAddress("beta_2", &beta_2, &b_beta_2);
   fChain->SetBranchAddress("bphi_2", &bphi_2, &b_bphi_2);
   fChain->SetBranchAddress("brawf_2", &brawf_2, &b_brawf_2);
   fChain->SetBranchAddress("bmva_2", &bmva_2, &b_bmva_2);
   fChain->SetBranchAddress("bcsv_2", &bcsv_2, &b_bcsv_2);
   fChain->SetBranchAddress("m_sv", &m_sv, &b_m_sv);
//    fChain->SetBranchAddress("m_sv_unc", &m_sv_unc, &b_m_sv_unc);
//    fChain->SetBranchAddress("mt_sv", &mt_sv, &b_mt_sv);
//    fChain->SetBranchAddress("mt_sv_unc", &mt_sv_unc, &b_mt_sv_unc);
   fChain->SetBranchAddress("pt_sv", &pt_sv, &b_pt_sv);
//    fChain->SetBranchAddress("pt_sv_unc", &pt_sv_unc, &b_pt_sv_unc);
   Notify();
}

Bool_t NtupleClass::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void NtupleClass::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t NtupleClass::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef NtupleClass_cxx
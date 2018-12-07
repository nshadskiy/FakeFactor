//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Jul  6 17:59:34 2016 by ROOT version 6.02/13
// from TTree Events/Events
// found on file: preselection/tt/preselection_data.root
////////////////////////////////////////////////////////// 

#ifndef SignalClass_h
#define SignalClass_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TLorentzVector.h>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"

class SignalClass {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Double_t        weight;
   Double_t        sf;
   Double_t        weight_sf;
   Int_t           passes3LVeto;
   Int_t           passesDLVeto;
   Double_t        bpt_1;
   Double_t        bpt_2;
   Int_t           njets;
   Int_t           njetingap20;
   Int_t           nbtag;
   Double_t        mjj;
   Double_t        jdeta;
   Double_t        mvamet;
   Double_t        met;
   Double_t        m_leplep;
   Double_t        lep_dR;
   Double_t        mt_leplep;
   Double_t        otherLep_pt;
   Double_t        otherLep_eta;
   Int_t           otherLep_q;
   Double_t        otherLep_iso;
   Double_t        lep_pt;
   Double_t        lep_eta;
   Double_t        lep_phi;
   Int_t           lep_q;
   Double_t        lep_iso;
   Double_t        lep_vloose;
   Double_t        lep_loose;
   Double_t        lep_medium;
   Int_t           n_iso_lep;
   Int_t           n_iso_otherLep;
   std::vector<double>  *alltau_pt;
   std::vector<double>  *alltau_eta;
   std::vector<double>  *alltau_phi;
   std::vector<double>  *alltau_q;
   std::vector<int>     *alltau_decay;
   std::vector<double>  *alltau_beta;
   std::vector<int>     *alltau_mediumBeta;
   std::vector<int>     *alltau_vlooseMVA;
   std::vector<int>     *alltau_looseMVA;
   std::vector<int>     *alltau_mediumMVA;
   std::vector<int>     *alltau_tightMVA;
   std::vector<int>     *alltau_vtightMVA;
   std::vector<int>     *alltau_lepVeto;
   std::vector<int>     *alltau_gen_match;
   std::vector<double>  *alltau_dRToLep;
   std::vector<double>  *alltau_dRToOtherLep;
   std::vector<double>  *alltau_dRToB;
   std::vector<double>  *alltau_mvis;
   std::vector<double>  *alltau_mt;
   std::vector<double>  *alltau_mt2;
   std::vector<double>  *alltau_svfit;
   std::vector<double>  *alltau_Zpt;
   
   Int_t           tau_iso_ind;

   // List of branches
   TBranch        *b_weight;   //!
   TBranch        *b_sf;   //!
   TBranch        *b_weight_sf;   //!
   TBranch        *b_passes3LVeto;   //!
   TBranch        *b_passesDLVeto;   //!
   TBranch        *b_bpt_1;   //!
   TBranch        *b_bpt_2;   //!
   TBranch        *b_njets;   //!
   TBranch        *b_njetingap20;   //!
   TBranch        *b_nbtag;   //!
   TBranch        *b_mjj;   //!
   TBranch        *b_mvamet;   //!
   TBranch        *b_met;   //!
   TBranch        *b_jdeta;   //!
   TBranch        *b_m_leplep;   //!
   TBranch        *b_lep_dR;   //!
   TBranch        *b_mt_leplep;   //!
   TBranch        *b_otherLep_pt;   //!
   TBranch        *b_otherLep_eta;   //!
   TBranch        *b_otherLep_q;   //!
   TBranch        *b_otherLep_iso;   //!
   TBranch        *b_lep_pt;   //!
   TBranch        *b_lep_eta;   //!
   TBranch        *b_lep_phi;   //!
   TBranch        *b_lep_q;   //!
   TBranch        *b_lep_iso;   //!
   TBranch        *b_lep_vloose;   //!
   TBranch        *b_lep_loose;   //!
   TBranch        *b_lep_medium;   //!
   TBranch        *b_n_iso_lep;   //!
   TBranch        *b_n_iso_otherLep;   //!
   TBranch        *b_alltau_pt;   //!
   TBranch        *b_alltau_eta;   //!
   TBranch        *b_alltau_phi;   //!
   TBranch        *b_alltau_q;   //!
   TBranch        *b_alltau_decay;   //!
   TBranch        *b_alltau_beta;   //!
   TBranch        *b_alltau_mediumBeta;   //!
   TBranch        *b_alltau_vlooseMVA;   //!
   TBranch        *b_alltau_looseMVA;     //!
   TBranch        *b_alltau_mediumMVA;   //!
   TBranch        *b_alltau_tightMVA;   //!
   TBranch        *b_alltau_vtightMVA;   //!
   TBranch        *b_alltau_lepVeto;   //!
   TBranch        *b_alltau_gen_match;   //!
   TBranch        *b_alltau_dRToLep;   //!
   TBranch        *b_alltau_dRToOtherLep;   //!
   TBranch        *b_alltau_dRToB;   //!
   TBranch        *b_alltau_mvis;   //!
   TBranch        *b_alltau_mt;   //!
   TBranch        *b_alltau_mt2;   //!
   TBranch        *b_alltau_svfit;   //!
   TBranch        *b_alltau_Zpt;   //!
   TBranch        *b_tau_iso_ind;   //!

   SignalClass(TTree *tree=0);
   virtual ~SignalClass();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef SignalClass_cxx
SignalClass::SignalClass(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("preselection/tt/preselection_data.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("preselection/tt/preselection_data.root");
      }
      f->GetObject("Events",tree);

   }
   Init(tree);
}

SignalClass::~SignalClass()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t SignalClass::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t SignalClass::LoadTree(Long64_t entry)
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

void SignalClass::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   alltau_pt = 0;
   alltau_eta = 0;
   alltau_phi = 0;
   alltau_q = 0;
   alltau_decay = 0;
   alltau_beta = 0;
   alltau_mediumBeta = 0;
   alltau_vlooseMVA = 0;
   alltau_looseMVA = 0;
   alltau_mediumMVA = 0;
   alltau_tightMVA = 0;
   alltau_vtightMVA = 0;
   alltau_lepVeto = 0;
   alltau_gen_match = 0;
   alltau_dRToLep = 0;
   alltau_dRToOtherLep = 0;
   alltau_dRToB = 0;
   alltau_mvis = 0;
   alltau_mt = 0;
   alltau_mt2 = 0;
   alltau_svfit = 0;
   alltau_Zpt = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("weight", &weight, &b_weight);
   fChain->SetBranchAddress("sf", &sf, &b_sf);
   fChain->SetBranchAddress("weight_sf", &weight_sf, &b_weight_sf);
   fChain->SetBranchAddress("passes3LVeto", &passes3LVeto, &b_passes3LVeto);
   fChain->SetBranchAddress("passesDLVeto", &passesDLVeto, &b_passesDLVeto);
   fChain->SetBranchAddress("bpt_1", &bpt_1, &b_bpt_1);
   fChain->SetBranchAddress("bpt_2", &bpt_2, &b_bpt_2);
   fChain->SetBranchAddress("njets", &njets, &b_njets);
   fChain->SetBranchAddress("nbtag", &nbtag, &b_nbtag);
   fChain->SetBranchAddress("njetingap20", &njetingap20, &b_njetingap20);
   fChain->SetBranchAddress("mjj", &mjj, &b_mjj);
   fChain->SetBranchAddress("mvamet", &mvamet, &b_mvamet);
   fChain->SetBranchAddress("met", &met, &b_met);
   fChain->SetBranchAddress("jdeta", &jdeta, &b_jdeta);
   fChain->SetBranchAddress("m_leplep", &m_leplep, &b_m_leplep);
   fChain->SetBranchAddress("lep_dR", &lep_dR, &b_lep_dR);
   fChain->SetBranchAddress("mt_leplep", &mt_leplep, &b_mt_leplep);
   fChain->SetBranchAddress("otherLep_pt", &otherLep_pt, &b_otherLep_pt);
   fChain->SetBranchAddress("otherLep_eta", &otherLep_eta, &b_otherLep_eta);
   fChain->SetBranchAddress("otherLep_q", &otherLep_q, &b_otherLep_q);
   fChain->SetBranchAddress("otherLep_iso", &otherLep_iso, &b_otherLep_iso);
   fChain->SetBranchAddress("lep_pt", &lep_pt, &b_lep_pt);
   fChain->SetBranchAddress("lep_eta", &lep_eta, &b_lep_eta);
   fChain->SetBranchAddress("lep_phi", &lep_phi, &b_lep_phi);
   fChain->SetBranchAddress("lep_q", &lep_q, &b_lep_q);
   fChain->SetBranchAddress("lep_iso", &lep_iso, &b_lep_iso);
   fChain->SetBranchAddress("lep_vloose", &lep_vloose, &b_lep_vloose);
   fChain->SetBranchAddress("lep_loose", &lep_loose, &b_lep_loose);
   fChain->SetBranchAddress("lep_medium", &lep_medium, &b_lep_medium);   
   fChain->SetBranchAddress("n_iso_lep", &n_iso_lep, &b_n_iso_lep);
   fChain->SetBranchAddress("n_iso_otherLep", &n_iso_otherLep, &b_n_iso_otherLep);
   fChain->SetBranchAddress("alltau_pt", &alltau_pt, &b_alltau_pt);
   fChain->SetBranchAddress("alltau_eta", &alltau_eta, &b_alltau_eta);
   fChain->SetBranchAddress("alltau_phi", &alltau_phi, &b_alltau_phi);
   fChain->SetBranchAddress("alltau_q", &alltau_q, &b_alltau_q);
   fChain->SetBranchAddress("alltau_decay", &alltau_decay, &b_alltau_decay);
   fChain->SetBranchAddress("alltau_beta", &alltau_beta, &b_alltau_beta);
   fChain->SetBranchAddress("alltau_mediumBeta", &alltau_mediumBeta, &b_alltau_mediumBeta);
   fChain->SetBranchAddress("alltau_vlooseMVA", &alltau_vlooseMVA, &b_alltau_vlooseMVA);
   fChain->SetBranchAddress("alltau_looseMVA", &alltau_looseMVA, &b_alltau_looseMVA);
   fChain->SetBranchAddress("alltau_mediumMVA", &alltau_mediumMVA, &b_alltau_mediumMVA);
   fChain->SetBranchAddress("alltau_tightMVA", &alltau_tightMVA, &b_alltau_tightMVA);
   fChain->SetBranchAddress("alltau_vtightMVA", &alltau_vtightMVA, &b_alltau_vtightMVA);
   fChain->SetBranchAddress("alltau_lepVeto", &alltau_lepVeto, &b_alltau_lepVeto);
   fChain->SetBranchAddress("alltau_gen_match", &alltau_gen_match, &b_alltau_gen_match);
   fChain->SetBranchAddress("alltau_dRToLep", &alltau_dRToLep, &b_alltau_dRToLep);
   fChain->SetBranchAddress("alltau_dRToOtherLep", &alltau_dRToOtherLep, &b_alltau_dRToOtherLep);
   fChain->SetBranchAddress("alltau_dRToB", &alltau_dRToB, &b_alltau_dRToB);
   fChain->SetBranchAddress("alltau_mvis", &alltau_mvis, &b_alltau_mvis);
   fChain->SetBranchAddress("alltau_mt", &alltau_mt, &b_alltau_mt);
   fChain->SetBranchAddress("alltau_mt2", &alltau_mt2, &b_alltau_mt2);
   fChain->SetBranchAddress("alltau_svfit", &alltau_svfit, &b_alltau_svfit);
   fChain->SetBranchAddress("alltau_Zpt", &alltau_Zpt, &b_alltau_Zpt);
   fChain->SetBranchAddress("tau_iso_ind", &tau_iso_ind, &b_tau_iso_ind);
   Notify();
}

Bool_t SignalClass::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void SignalClass::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t SignalClass::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef SignalClass_cxx

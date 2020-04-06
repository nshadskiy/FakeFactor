#include "ViennaTool/interface/FFCalculator.h"

#include <iostream>
#include <sstream>

#include <chrono>
#include <ctime>    

using namespace std;


FFCalculator::FFCalculator(
                           Int_t N_p_Wjets,Int_t N_p_DY,Int_t N_p_TT_SR,Int_t N_p_TT_CR,Int_t N_p_QCD, Int_t N_p_QCD_AI,
                           Int_t N_eta_Wjets,Int_t N_eta_DY,Int_t N_eta_TT,Int_t N_eta_QCD,
                           Int_t N_t_Wjets,Int_t N_t_DY,Int_t N_t_TT,Int_t N_t_QCD,
                           Int_t N_m_Wjets,Int_t N_m_DY,Int_t N_m_TT,Int_t N_m_QCD,
                           Int_t N_j_Wjets,Int_t N_j_DY,Int_t N_j_TT_SR,Int_t N_j_TT_CR,Int_t N_j_QCD,
                           const Double_t Pt_cuts_Wjets[],const Double_t Pt_cuts_DY[],const Double_t Pt_cuts_TT_SR[],const Double_t Pt_cuts_TT_CR[],const Double_t Pt_cuts_QCD[],const Double_t Pt_cuts_QCD_AI[],
                           const Double_t Eta_cuts_Wjets[],const Double_t Eta_cuts_DY[],const Double_t Eta_cuts_TT[],const Double_t Eta_cuts_QCD[],
                           const Int_t Decay_cuts_Wjets[],const Int_t Decay_cuts_DY[],const Int_t Decay_cuts_TT[],const Int_t Decay_cuts_QCD[],
                           const Double_t Mt_cuts_Wjets[],const Double_t Mt_cuts_DY[],const Double_t Mt_cuts_TT[],const Double_t Mt_cuts_QCD[],
                           const Int_t Njet_cuts_Wjets[],const Int_t Njet_cuts_DY[],const Int_t Njet_cuts_TT_SR[],const Int_t Njet_cuts_TT_CR[],const Int_t Njet_cuts_QCD[])
{
  if (DEBUG) cout<<"Analyzer created."<<std::endl;
  //Initialise constants
  n_p_Wjets=N_p_Wjets;
  pt_cuts_Wjets=(Double_t*)malloc(n_p_Wjets*sizeof(Double_t));
  for(Int_t i=0;i<n_p_Wjets;i++) pt_cuts_Wjets[i]=Pt_cuts_Wjets[i];

  n_p_DY=N_p_DY;
  pt_cuts_DY=(Double_t*)malloc(n_p_DY*sizeof(Double_t));
  for(Int_t i=0;i<n_p_DY;i++) pt_cuts_DY[i]=Pt_cuts_DY[i];

  //n_p_TT=N_p_TT;
  //pt_cuts_TT=(Double_t*)malloc(n_p_TT*sizeof(Double_t));
  //for(Int_t i=0;i<n_p_TT;i++) pt_cuts_TT[i]=Pt_cuts_TT[i];

  n_p_TT_SR=N_p_TT_SR;
  pt_cuts_TT_SR=(Double_t*)malloc(n_p_TT_SR*sizeof(Double_t));
  for(Int_t i=0;i<n_p_TT_SR;i++) pt_cuts_TT_SR[i]=Pt_cuts_TT_SR[i];

  n_p_TT_CR=N_p_TT_CR;
  pt_cuts_TT_CR=(Double_t*)malloc(n_p_TT_CR*sizeof(Double_t));
  for(Int_t i=0;i<n_p_TT_CR;i++) pt_cuts_TT_CR[i]=Pt_cuts_TT_CR[i];

  n_p_QCD=N_p_QCD;
  pt_cuts_QCD=(Double_t*)malloc(n_p_QCD*sizeof(Double_t));
  for(Int_t i=0;i<n_p_QCD;i++) pt_cuts_QCD[i]=Pt_cuts_QCD[i];

  n_p_QCD_AI=N_p_QCD_AI;
  pt_cuts_QCD_AI=(Double_t*)malloc(n_p_QCD_AI*sizeof(Double_t));
  for(Int_t i=0;i<n_p_QCD_AI;i++) pt_cuts_QCD_AI[i]=Pt_cuts_QCD_AI[i];

  n_t_Wjets=N_t_Wjets;
  decay_cuts_Wjets=(Int_t*)malloc(n_t_Wjets*sizeof(Int_t));
  for(Int_t i=0;i<n_t_Wjets;i++) decay_cuts_Wjets[i]=Decay_cuts_Wjets[i];

  n_t_DY=N_t_DY;
  decay_cuts_DY=(Int_t*)malloc(n_t_DY*sizeof(Int_t));
  for(Int_t i=0;i<n_t_DY;i++) decay_cuts_DY[i]=Decay_cuts_DY[i];

  n_t_TT=N_t_TT;
  decay_cuts_TT=(Int_t*)malloc(n_t_TT*sizeof(Int_t));
  for(Int_t i=0;i<n_t_TT;i++) decay_cuts_TT[i]=Decay_cuts_TT[i];

  n_t_QCD=N_t_QCD;
  decay_cuts_QCD=(Int_t*)malloc(n_t_QCD*sizeof(Int_t));
  for(Int_t i=0;i<n_t_QCD;i++) decay_cuts_QCD[i]=Decay_cuts_QCD[i];


  n_e_Wjets=N_e_Wjets;
  eta_cuts_Wjets=(Double_t*)malloc(n_e_Wjets*sizeof(Double_t));
  for(Int_t i=0;i<n_e_Wjets;i++) eta_cuts_Wjets[i]=Eta_cuts_Wjets[i];

  n_e_DY=N_e_DY;
  eta_cuts_DY=(Double_t*)malloc(n_e_DY*sizeof(Double_t));
  for(Int_t i=0;i<n_e_DY;i++) eta_cuts_DY[i]=Eta_cuts_DY[i];

  n_e_TT=N_e_TT;
  eta_cuts_TT=(Double_t*)malloc(n_e_TT*sizeof(Double_t));
  for(Int_t i=0;i<n_e_TT;i++) eta_cuts_TT[i]=Eta_cuts_TT[i];

  n_e_QCD=N_e_QCD;
  eta_cuts_QCD=(Double_t*)malloc(n_e_QCD*sizeof(Double_t));
  for(Int_t i=0;i<n_e_QCD;i++) eta_cuts_QCD[i]=Eta_cuts_QCD[i];


  n_m_Wjets=N_m_Wjets;
  mt_cuts_Wjets=(Double_t*)malloc(n_m_Wjets*sizeof(Double_t));
  for(Int_t i=0;i<n_m_Wjets;i++) mt_cuts_Wjets[i]=Mt_cuts_Wjets[i];

  n_m_DY=N_m_DY;
  mt_cuts_DY=(Double_t*)malloc(n_m_DY*sizeof(Double_t));
  for(Int_t i=0;i<n_m_DY;i++) mt_cuts_DY[i]=Mt_cuts_DY[i];

  n_m_TT=N_m_TT;
  mt_cuts_TT=(Double_t*)malloc(n_m_TT*sizeof(Double_t));
  for(Int_t i=0;i<n_m_TT;i++) mt_cuts_TT[i]=Mt_cuts_TT[i];

  n_m_QCD=N_m_QCD;
  mt_cuts_QCD=(Double_t*)malloc(n_m_QCD*sizeof(Double_t));
  for(Int_t i=0;i<n_m_QCD;i++) mt_cuts_QCD[i]=Mt_cuts_QCD[i];


  n_j_Wjets=N_j_Wjets;
  njet_cuts_Wjets=(Int_t*)malloc(n_j_Wjets*sizeof(Double_t));
  for(Int_t i=0;i<n_j_Wjets;i++) njet_cuts_Wjets[i]=Njet_cuts_Wjets[i];

  n_j_DY=N_j_DY;
  njet_cuts_DY=(Int_t*)malloc(n_j_DY*sizeof(Double_t));
  for(Int_t i=0;i<n_j_DY;i++) njet_cuts_DY[i]=Njet_cuts_DY[i];

  //n_j_TT=N_j_TT;
  //njet_cuts_TT=(Int_t*)malloc(n_j_TT*sizeof(Double_t));
  //for(Int_t i=0;i<n_j_TT;i++) njet_cuts_TT[i]=Njet_cuts_TT[i];

  n_j_TT_SR=N_j_TT_SR;
  njet_cuts_TT_SR=(Int_t*)malloc(n_j_TT_SR*sizeof(Double_t));
  for(Int_t i=0;i<n_j_TT_SR;i++) njet_cuts_TT_SR[i]=Njet_cuts_TT_SR[i];

  n_j_TT_CR=N_j_TT_CR;
  njet_cuts_TT_CR=(Int_t*)malloc(n_j_TT_CR*sizeof(Double_t));
  for(Int_t i=0;i<n_j_TT_CR;i++) njet_cuts_TT_CR[i]=Njet_cuts_TT_CR[i];

  n_j_QCD=N_j_QCD;
  njet_cuts_QCD=(Int_t*)malloc(n_j_QCD*sizeof(Double_t));
  for(Int_t i=0;i<n_j_QCD;i++) njet_cuts_QCD[i]=Njet_cuts_QCD[i];

  for (int i=0; i<NB_MTCORR; i++){
    corr_d[i]=-999; corr_k[i]=-999;
  }

  TH1::SetDefaultSumw2(kTRUE);
}

FFCalculator::~FFCalculator()
{
}

void FFCalculator::calcFFweights(const TString data_file, const std::vector<TString> weight_files, const std::vector<TString> presel_files, Float_t *yields, const TString m_path_img, const TString m_path_w, const TString tf_name, Int_t inclusive, Int_t mode)
{
  if (DEBUG) std::cout << "In calcFFweights" << std::endl;

  TString s_ctr[]={"1","2","3","4","5","6","7","8","9","10","11","12"};

  std::vector<TString> fnames(presel_files);
  fnames.push_back(data_file);

  std::vector<TString> wnames(weight_files);
  wnames.push_back(data_file);

  unsigned PS_SIZE=presel_files.size();

  std::vector<TH1D*> h_n; h_n.resize(PS_SIZE+1); //+1 is data
  std::vector<TH1D*> h_n_tt; h_n_tt.resize(PS_SIZE+1);
  std::vector<TH1D*> h_n_tight; h_n_tight.resize(PS_SIZE+1);

  std::vector<TH1D*> h_w; h_w.resize(PS_SIZE+1); //+1 is QCD
  std::vector<TH1D*> h_w_tight; h_w_tight.resize(PS_SIZE+1);

  TString hss_string = "h_ss_n"; TString h_qcd_rest_n = "h_qcd_rest";
  if(!inclusive){
    for(Int_t icat=0; icat<nCAT; icat++){
      if(catMode[icat] & mode) {hss_string = hss_string + categories[icat];}
      if(catMode[icat] & mode) {h_qcd_rest_n = h_qcd_rest_n + categories[icat];}
    }
  }
  TH1D* h_ss=new TH1D( hss_string,"",nbins_weight,min_weight,max_weight  );
  TH1D* h_qcd_rest=new TH1D( h_qcd_rest_n,"",nbins_weight,min_weight,max_weight  );  

  for (unsigned i=0; i<=PS_SIZE; i++){
    loadFile(fnames.at(i),"Events");
    h_n.at(i)      =new TH1D("h_n_"      +s_ctr[i],"",nbins_weight,min_weight,max_weight);
    h_n_tt.at(i)      =new TH1D("h_n_tt"      +s_ctr[i],"",nbins_weight,min_weight,max_weight);
    h_n_tight.at(i)=new TH1D("h_n_tight_"+s_ctr[i],"",nbins_weight,min_weight,max_weight);
    Int_t nentries=Int_t(event_s->fChain->GetEntries());
    std::cout<< "Processing " << fnames.at(i) << " with \t" << nentries << " events."<<std::endl;
    for(Int_t jentry=0;jentry<nentries;jentry++) {
      event_s->GetEntry(jentry);
      Double_t fracWeight=event_s->weight_sf;
      if ( !fulfillCategory(mode) ) continue;
      if ( this->isInSR(NO_SR) ){
        if (this->isLoose()) h_n.at(i)->Fill(this->getWeightBin(),fracWeight);
        else if (this->isTight()) h_n_tight.at(i)->Fill(this->getWeightBin(),fracWeight);
        if (this->isTight_alt()) h_n_tt.at(i)->Fill(this->getWeightBin(),fracWeight);
      }
      if ( this->isInSR( NO_SR | _SS ) && this->isLoose() ) 
        h_ss->Fill(this->getWeightBin(),fracWeight *(-2*(i<PS_SIZE)+1)    ); //-1 for MC, +1 for data
      if ( CHAN==kTAU && this->isInSR( NO_SR ) && this->isLoose() ) 
        h_qcd_rest->Fill(this->getWeightBin(),fracWeight *(-2*(i<PS_SIZE)+1)    ); //-1 for MC, +1 for data
      else if( CHAN!=kTAU && this->isInSR( NO_SR ) && this->isLoose() ) 
        h_qcd_rest->Fill(this->getWeightBin(),fracWeight *(-2*(i<PS_SIZE)+1)    ); //-1 for MC, +1 for data
    }
    if (DEBUG) cout << "Name: " << fnames.at(i) << " " << h_ss->Integral() << endl;
    if (DEBUG) cout << "Name: " << fnames.at(i) << " " << h_qcd_rest->Integral() << endl;
  }

  if (tf_name!=""){            //do weights from template fit

    std::vector<TH1D*> templates(h_n);
    std::vector<TH1D*> templates_tt(h_n_tt);

    TString CF = COINFLIP==1 ? "" : "_DC";
    TFile *ft=new TFile(tf_name,"RECREATE");
    for (int i=(int)fnames.size()-1; i>=0; i--){
      TString stmp=fnames.at(i); if (DEBUG) cout << stmp << endl; stmp.ReplaceAll(CF+".root",""); stmp.ReplaceAll(path_presel+"preselection_",""); stmp.ReplaceAll("_woQCD",""); stmp.ReplaceAll("MCsum","data"); if (DEBUG) cout << stmp << endl;
      if(!inclusive){
        for(Int_t icat=0; icat<nCAT; icat++){
          if(catMode[icat] & mode) {stmp = stmp + categories[icat];}
        }
      }
      //if(CALC_SS_SR) stmp=stmp+"_SS_SR";
      TH1D* h_template=(TH1D*)templates.at(i)->Clone("h_template_"+stmp); h_template->Write();
    }
    TString tf_name_tt = tf_name; tf_name_tt.ReplaceAll(".root","_vlooseAntiIso.root");
    TFile *ft_tt=new TFile(tf_name_tt,"RECREATE");
    for (int i=(int)fnames.size()-1; i>=0; i--){
      TString stmp=fnames.at(i); if (DEBUG) cout << stmp << endl; stmp.ReplaceAll(".root",""); stmp.ReplaceAll(path_presel+"preselection_",""); stmp.ReplaceAll("_woQCD",""); stmp.ReplaceAll("MCsum","data"); if (DEBUG) cout << stmp << endl;
      if(!inclusive){
        for(Int_t icat=0; icat<nCAT; icat++){
          if(catMode[icat] & mode) {stmp = stmp + categories[icat];}
        }
      }
      TH1D* h_template_tt=(TH1D*)templates_tt.at(i)->Clone("h_template_"+stmp); h_template_tt->Write();
    }
    
    ft->cd();

    TString h_template_QCD="h_template_QCD";
    if(!inclusive){
      for(Int_t icat=0; icat<nCAT; icat++) if(catMode[icat] & mode) {h_template_QCD=h_template_QCD+categories[icat];}
    }
    TH1D* h_template=(TH1D*)h_ss->Clone(h_template_QCD);
    TH1D* hqcd_OS_SS_factor=(TH1D*)h_ss->Clone("factor");
    for (int ib=0; ib<=hqcd_OS_SS_factor->GetNbinsX(); ib++){
      hqcd_OS_SS_factor->SetBinContent(ib, 1.06);
      hqcd_OS_SS_factor->SetBinError(ib, 1.06/10);
    }
    h_template->Multiply( hqcd_OS_SS_factor );

    h_template->Write();

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //FIXME: Do it after checking if fit converges!
    TString h_template_QCD_rest="h_template_QCD_rest";
    if(!inclusive){
      for(Int_t icat=0; icat<nCAT; icat++) if(catMode[icat] & mode) {h_template_QCD_rest=h_template_QCD_rest+categories[icat];}
    }
    TH1D* h_template_qcd=(TH1D*)h_qcd_rest->Clone(h_template_QCD_rest);
    for (int ib=0; ib<=h_qcd_rest->GetNbinsX(); ib++){
      if( h_qcd_rest->GetBinContent(ib) < 0. ) h_qcd_rest->SetBinContent(ib,0.);
    }
      
    h_template_qcd->Write();
    ft_tt->cd();
    h_template->Write();
    h_template_qcd->Write();
    ft->Close();
    ft_tt->Close();

    this->calcWeightFromFit(tf_name,m_path_img,m_path_w,"",yields,inclusive,mode);
    //if(CHAN==kTAU)this->calcWeightFromFit(tf_name_tt,m_path_img,m_path_w,"_vlooseAntiIso",mode); //might be interesting for other channels as well

  } else{     //do weights from MC, and QCD=data-rest MC


    //now to QCD: difference data to MC backgrounds (w/o QCD MC)
    TH1D* h_n_qcd       = new TH1D(*h_n.back()       ); //data
    TH1D* h_n_qcd_tight = new TH1D(*h_n_tight.back() ); //data
    for (unsigned i=0; i<PS_SIZE; i++){
      h_n_qcd->Add(       h_n.at(i)       , -1 );
      h_n_qcd_tight->Add( h_n_tight.at(i) , -1 );
    }

    /*
      TH1D* nMCsum=new TH1D("nMCsum","",nbins_weight,min_weight,max_weight);
      TH1D* nMCsumTight=new TH1D("nMCsumTight","",nbins_weight,min_weight,max_weight);
      
      for (unsigned i=0; i<PS_SIZE; i++){
      nMCsum->Add(h_n.at(i));
      nMCsumTight->Add(h_n_tight.at(i));
      }
    */

    if (DEBUG){
      std::cout << "Sum in looseSR:\t";
      for (unsigned i=0; i<PS_SIZE; i++) std::cout << presel_files.at(i)(13+path_presel.Length(),presel_files.at(i).Length()-5-13-path_presel.Length()) << "=" << h_n.at(i)->Integral(-1,-1) << " ";
      //    std::cout << " sum: " << nMCsum->Integral(-1,-1) << std::endl;
      std::cout << " sum: " << h_n.back()->Integral(-1,-1) << std::endl;
      
      std::cout << "1st bin in looseSR:\t";
      for (unsigned i=0; i<PS_SIZE; i++) std::cout << presel_files.at(i)(13+path_presel.Length(),presel_files.at(i).Length()-5-13-path_presel.Length()) << "=" << h_n.at(i)->GetBinContent(1) << " ";
      //    std::cout << " sum: " << nMCsum->GetBinContent(1) << std::endl;
      std::cout << " sum: " << h_n.back()->GetBinContent(1) << std::endl;
    }
    
    for (unsigned i=0; i<PS_SIZE; i++){
      h_w.at(i)      =new TH1D("h_w"                ,"",nbins_weight,min_weight,max_weight);
      h_w_tight.at(i)=new TH1D("h_w_tight"          ,"",nbins_weight,min_weight,max_weight);
      
      //    h_w.at(i)->Add(h_n.at(i));
      //    h_w.at(i)->Divide(nMCsum);
      //    h_w.at(i)->Divide(h_w.at(i), nMCsum, 1, 1, "B"); //binomial errors
      h_w.at(i)->Divide(h_n.at(i), h_n.back(), 1, 1, "B"); //binomial errors
      
      //    h_w_tight.at(i)->Add(h_n_tight.at(i));
      //    h_w_tight.at(i)->Divide(nMCsumTight);
      //    h_w_tight.at(i)->Divide(h_w_tight.at(i), nMCsumTight, 1, 1, "B"); //binomial errors
      h_w_tight.at(i)->Divide(h_n_tight.at(i), h_n_tight.back(), 1, 1, "B"); //binomial errors
    }
    
    TH1D *htmp       = new TH1D("h_w"                ,"",nbins_weight,min_weight,max_weight);
    TH1D *htmp_tight = new TH1D("h_w_tight"          ,"",nbins_weight,min_weight,max_weight);
    
    htmp->Divide(h_n_qcd, h_n.back(), 1, 1, "B"); //binomial errors
    htmp_tight->Divide(h_n_qcd_tight, h_n_tight.back(), 1, 1, "B");
    
    h_w.insert(h_w.begin()+weight_files.size()-1,htmp);
    h_w_tight.insert(h_w_tight.begin()+weight_files.size(),htmp_tight);
    
    if (DEBUG) std::cout << "weight in looseSR, 1st bin:\t";
    for (unsigned i=0; i<PS_SIZE; i++) std::cout << presel_files.at(i)(13+path_presel.Length(),presel_files.at(i).Length()-5-13-path_presel.Length()) << "=" << h_w.at(i)->GetBinContent(1) << " ";
    if (DEBUG) std::cout << "QCD=" << h_w.back() << std::endl;
  
    for (unsigned i=0; i<weight_files.size(); i++){
      TFile f(weight_files.at(i),"recreate");
      h_w.at(i)->Write();
      f.Close();
    }
  
    THStack* hs = new THStack("w","");
    THStack* hsTight = new THStack("w","");
    const int *m_smap;
    if (DOQCD) m_smap=smap; else m_smap=smap_noqcd;
    for (unsigned i=0; i<PS_SIZE+1; i++){
      h_w.at(m_smap[i])->SetFillColor(vcolor[i]);
      h_w_tight.at(m_smap[i])->SetFillColor(vcolor[i]);
      hs->Add(h_w.at(m_smap[i]),"hist"); //sample mapping to "usual" order
      hsTight->Add(h_w_tight.at(m_smap[i]),"hist");
    }
    
    TCanvas* c1 = new TCanvas("c1","c_weights",1200,800);
    hs->Draw();
    gPad->SaveAs(m_path_img+"weights.png");
    c1->Close();
    
    c1 = new TCanvas("c1","weights_tight",1200,800);
    hsTight->Draw();
    gPad->SaveAs(m_path_img+"weights_tight.png");
    c1->Close();
    
  }

  for (unsigned i=0; i<PS_SIZE+1; i++){
    delete h_w.at(i);
    delete h_w_tight.at(i);
    delete h_n.at(i);
    delete h_n_tt.at(i);
    delete h_n_tight.at(i);
  }

} //end of calcFFweights

//can also be called from external
void FFCalculator::calcWeightFromFit(const TString fname, const TString m_path_img, const TString m_path_w, const TString isolation, Float_t *yields, Int_t inclusive, Int_t mode){

  TString m_data="h_template_data";
  if(!DOQCD) m_data="h_template_woQCDdata";

  std::vector<TString> m_fix;
  m_fix.push_back("h_template_TT_L"); m_fix.push_back("h_template_TT_T"); m_fix.push_back("h_template_DY_L"); m_fix.push_back("h_template_DY_TT");
  if(useVV) {m_fix.push_back("h_template_VV_L"); m_fix.push_back("h_template_VV_T");}
  const int NFIX=m_fix.size();
  if(!inclusive){
    for(Int_t icat=0; icat<nCAT; icat++){
      for(Int_t ifix=0;ifix<NFIX;ifix++) if(catMode[icat] & mode) {m_fix.at(ifix)=m_fix.at(ifix)+categories[icat];}
    }
  }
  const int NFIT=2;
  TString m_fit[NFIT]={ "h_template_Wjets", "h_template_QCD" };
  if(!inclusive){
    for(Int_t icat=0; icat<nCAT; icat++){
      for(Int_t ifit=0;ifit<NFIT;ifit++) if(catMode[icat] & mode) {m_fit[ifit]=m_fit[ifit]+categories[icat];}
    }
  }
  const int NSUM=2;
  TString m_sum[NSUM]={ "h_template_DY_J", "h_template_TT_J" };
  if(!inclusive){
    for(Int_t icat=0; icat<nCAT; icat++){
      for(Int_t isum=0;isum<NSUM;isum++) if(catMode[icat] & mode) {m_sum[isum]=m_sum[isum]+categories[icat];}
    }
  }
  const Int_t NW=NFIT+NSUM+1;
  TString m_used[NW];
  for (int i=0; i<NFIT; i++) m_used[i]=m_fit[i];
  for (int i=0; i<NSUM; i++) m_used[NFIT+i]=m_sum[i];
  m_used[NFIT+NSUM]="rest";

  Int_t m_color[NW];
  TString m_type[NW];
  for (int j=0; j<NW; j++){
    if      ( m_used[j].Contains("Wjets") ){ m_color[j]=color_Wjets; m_type[j]="Wjets"; }
    else if ( m_used[j].Contains("QCD") ){   m_color[j]=color_QCD;   m_type[j]="QCD";}
    else if ( m_used[j].Contains("TT_J") ){  m_color[j]=color_TT_J;  m_type[j]="TT_J";}
    else if ( m_used[j].Contains("DY_J") ){  m_color[j]=color_DY_J;  m_type[j]="DY_J";}
    else if ( m_used[j].Contains("rest") ){  m_color[j]=color_sum;   m_type[j]="rest";}
    else m_color[j]=kBlack;
  }
  //  const int fractions[NFIT+(NSUM>0)]={ _W_JETS , _QCD , _DY_J | _TT_J };
  
  /*
  const int NFIX=5;
  const TString m_fix[NFIX]={ "h_template_TT_L", "h_template_TT_T", "h_template_DY_L", "h_template_TT_J", "h_template_DY_J" };
  const int NFIT=3;
  const TString m_fit[NFIT]={ "h_template_Wjets", "h_template_QCD", "h_template_DY_TT" };
  */

  /*
  const int NFIX=6;
  const TString m_fix[NFIX]={ "h_template_TT_L", "h_template_TT_T", "h_template_DY_L", "h_template_DY_TT", "h_template_TT_J", "h_template_DY_J" };
  const int NFIT=2;
  const TString m_fit[NFIT]={ "h_template_Wjets", "h_template_QCD" };
  */

  std::vector<TH1D*> h_templates;

  TFile f(fname);

  TH1D *htmp;
  TString m_data_tmp = m_data;
  
  if(!inclusive){
    for(Int_t icat=0; icat<nCAT; icat++){
      if(catMode[icat] & mode) {m_data_tmp = m_data_tmp + categories[icat];}
    }
  }
  htmp=(TH1D*) f.Get(m_data_tmp);
      
  TH1D *h_data=(TH1D*) htmp->Clone();
  TH1D *h_rest=new TH1D();
  TH1D *h_sum=new TH1D();

  //sum up the fixed components, and subtract from data
  cout << fname << endl;
  for (int i=0; i<NFIX; i++){
    htmp=(TH1D*) f.Get(m_fix.at(i));
    if (i==0) h_rest=(TH1D*) htmp->Clone();
    else h_rest->Add(htmp);
  }
  
  h_data->Add(h_rest,-1);
  //collect the templates for the fit
  for (int i=0; i<NFIT; i++){
    if ( !DOQCD && m_fit[i].Contains("_QCD") ) continue; //FIX ME -- continue from here
    htmp=(TH1D*) f.Get(m_fit[i]);
    //    if (i==1) htmp->Scale(3); //test...
    h_templates.push_back(htmp);
  }
  for (int i=0; i<NW-1; i++){
    htmp=(TH1D*) f.Get(m_used[i]);
    if(m_used[i].Contains("qcd")){
      htmp=(TH1D*) f.Get("h_template_QCD_rest");
    }
    yields[i] = htmp->Integral();
  }
  yields[4] = h_rest->Integral();

  
  ///////////////////////////////////////////////////////////////
  
  int NBINS=0;
  for (int i=0; i<NSUM; i++){
    htmp=(TH1D*) f.Get(m_sum[i]);
    if (i==0){ 
      NBINS=htmp->GetNbinsX();
      h_sum=(TH1D*) htmp->Clone();
    }
    else{ 
      h_sum->Add( htmp );
    }
  }
  if (NSUM>0) h_templates.push_back(h_sum);
  
  TH1D *h_sum_frac[NSUM];
  for (int i=0; i<NSUM; i++){
    htmp=(TH1D*) f.Get(m_sum[i]);
    h_sum_frac[i]=new TH1D( *h_sum );
    h_sum_frac[i]->Divide( htmp, h_sum, 1,1,"B" );
  }

  //get fractions before fit
  if (DEBUG && h_templates.size()>0 ){
    //as used in the fit:
    double n_templates_all=0;
    for (unsigned it=0; it<h_templates.size(); it++){
      n_templates_all+=h_templates.at(it)->Integral();
    }
    std::cout << "As in templates: Pre-fit  fraction" << std::endl;
    for (unsigned it=0; it<h_templates.size(); it++){
      std::cout << "Pre-fit  fraction:\t" << h_templates.at(it)->Integral()/n_templates_all << std::endl;
    }
    //all (split, plus sum of true bkg):
    std::cout << std::endl << "All components: Pre-fit  fraction" << std::endl;
    double n_all=n_templates_all+h_rest->Integral();

    for (int it=0; it<NFIT; it++){
      std::cout << "Pre-fit  fraction:\t" << h_templates.at(it)->Integral()/n_all << "\t" << m_type[it] << std::endl;
    }
    for (int it=0; it<NSUM; it++){
      TH1D *h_d_tmp=(TH1D*)h_sum->Clone(); h_d_tmp->Multiply(h_sum_frac[it]);
      std::cout << "Pre-fit  fraction:\t" << h_d_tmp->Integral()/n_all << "\t" << m_type[NFIT+it] << std::endl;
    }
    std::cout << "Pre-fit  fraction:\t" << h_rest->Integral()/n_all << "\t" << m_type[NFIT+NSUM] << std::endl;   
    
  }

  std::vector<TH1D*> res;
  TH1D* res_data=new TH1D();
  std::vector<TH1D*> h_w;
  //Int_t fit_result=this->doTemplateFit(h_data, h_templates, m_path_img, res, res_data, mode);
  //TEMPLATE fit no longer used for 2016 data!!!!
  Int_t fit_result=1;
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////// 
  if( !doTemplateFitForWeights || fit_result!=0 ){
    std::vector<TH1D*> h_check; //if fit doesn't converge, this vector contains all the necessary histograms
    TH1D* htmp_check;
    for (int i=0; i<NFIT; i++){
      if ( !DOQCD && m_fit[i].Contains("_QCD") ){
        htmp_check=(TH1D*) f.Get( m_fit[i] );
        for(int i=1;i<=htmp_check->GetNbinsX();i++) htmp_check->SetBinContent(i,0);
      }
      else if (m_fit[i].Contains("_QCD")){
        TString qcd_rest=m_fit[i];
        qcd_rest.ReplaceAll("_QCD","_QCD_rest");
        htmp_check=(TH1D*) f.Get(qcd_rest);
        for(int i=1;i<=htmp_check->GetNbinsX();i++){ if(htmp_check->GetBinContent(i)<0) htmp_check->SetBinContent(i,0);}
      } 
      else htmp_check=(TH1D*) f.Get(m_fit[i]);
      for(int i=1;i<=htmp_check->GetNbinsX();i++){ if(htmp_check->GetBinContent(i)<0) htmp_check->SetBinContent(i,0);}
      h_check.push_back(htmp_check);
    }
    for (int i=0; i<NSUM; i++){
      htmp_check=(TH1D*) f.Get(m_sum[i]);
      h_check.push_back(htmp_check);
      for(int i=1;i<=htmp_check->GetNbinsX();i++){ if(htmp_check->GetBinContent(i)<0) htmp_check->SetBinContent(i,0);}
    }
    //h_check.push_back(h_rest);
    TH1D *h_all;
    for(int iall=0;iall<h_check.size();iall++){
      if (iall==0) h_all=(TH1D*) h_check.at(0)->Clone();
      else h_all->Add(h_check.at(iall));
    }
    for(int i=0;i<h_check.size();i++){
      h_check.at(i)->Divide(h_all);
    }
    
    for(Int_t j=0;j<h_check.size();j++){
      TH1D *htmp = new TH1D("h_w"+sNum[j],"",nbins_weight,min_weight,max_weight);
      for(Int_t ibins=0; ibins<=NBINS; ibins++){ //ibins<h_templates.at(j)->GetNbinsX()
        if(h_check.at(j)->GetBinContent(ibins)>0) {htmp->SetBinContent( ibins, h_check.at(j)->GetBinContent(ibins) );}
        if(h_check.at(j)->GetBinContent(ibins)>0) {htmp->SetBinError( ibins, h_check.at(j)->GetBinError(ibins) );}
        
        else htmp->SetBinContent(ibins,0);
      }
      h_w.push_back(htmp);
    }
  }
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  else{
  
    //  std::cout << "RES " << res_data->Integral() << " " << res.size() << std::endl;

    if (!DOQCD){ //insert empty histogram to make the rest work
      int qcd_pos=-1;
      for (int i=0; i<NW; i++){
        if ( m_used[i].Contains("QCD") ) qcd_pos=i;
      }
      if ( qcd_pos>=0 ){
        TH1D* htmp;
        for (int i=0; i<NW; i++){ if (i!=qcd_pos){ htmp=(TH1D*)res.at(i)->Clone("qcdtmp"); break; } }
        htmp->Reset();
        res.insert(res.begin()+qcd_pos,htmp);
      }
    }

    unsigned NR=res.size();
  //  for (unsigned i=0; i<NR; i++) std::cout << res.at(i)->Integral();

    h_w.resize(NW);
    for (int j=0; j<NW; j++)    h_w.at(j) = new TH1D("h_w"+sNum[j] ,"",nbins_weight,min_weight,max_weight);
    //  for(int i=0; i<res_data->GetNbinsX(); i++){
    TH1D* h_normI=(TH1D*) res.at(0)->Clone();
    for (unsigned j=1; j<NR; j++) h_normI->Add( res.at(j) );

    TH1D* h_restI=new TH1D( *h_rest );
    h_restI->Divide(h_rest,res_data,1,1,"B");
    //h_normI->Add(h_restI);
    
    for (Int_t j=0; j<NFIT; j++)  h_w.at(j     )->Divide( res.at(j)    , h_normI , 1,1,"B");
    for (Int_t j=0; j<NSUM; j++){ 
      h_w.at(NFIT+j)->Divide(   res.at(NFIT)   , h_normI , 1,1,"B"); 
      h_w.at(NFIT+j)->Multiply( h_sum_frac[j] );
      //    for(int i=0; i<h_w.at(NFIT+j)->GetNbinsX(); i++) h_w.at(NFIT+j)->Scale( sum_frac[j].at(i) );
    }
    h_w.at(NFIT+NSUM)->Divide( h_restI , h_normI , 1,1,"B");

    for (int i=0; i<NW; i++){
      if (DEBUG){
        TH1D* h_d_tmp2=(TH1D*)h_normI->Clone(); h_d_tmp2->Multiply(res_data);
        TH1D* h_d_tmp=(TH1D*)h_w.at(i)->Clone(); h_d_tmp->Multiply( h_d_tmp2 );
        std::cout << "Post-fit fraction:\t" << h_d_tmp->Integral()/h_d_tmp2->Integral() << "\t" << m_type[i] << std::endl;
      }
    }

  }

  for (int i=0; i<NW-1; i++){
    if ( !DOQCD && m_type[i].Contains("QCD") ) continue;
    TString wname=m_path_w+"weight_"+m_type[i]+isolation;
    if(!inclusive){
      for(Int_t icat=0; icat<nCAT; icat++) if(catMode[icat] & mode) {wname=wname+categories[icat];}
    }
    if(CALC_SS_SR) wname=wname+"_SS_SR";
    TFile f(wname+".root","recreate");
    h_w.at(i)->SetName("h_w");
    h_w.at(i)->Write();
    h_w.at(i)->SetName("h_w"+sNum[i]);
    f.Close();
  }

  THStack* hs = new THStack("w","");
  for (int i=0; i<NW-1; i++){
    if ( !DOQCD&& m_type[i].Contains("QCD") ) continue;
    h_w.at(i)->SetFillColor(m_color[i]);
    hs->Add(h_w.at(i),"hist");
    //    h_w.at(m_smap[i])->SetFillColor(vcolor[i]);
    //    hs->Add(h_w.at(m_smap[i]),"hist"); //sample mapping to "usual" order
  }

  TCanvas* c1 = new TCanvas("c1","fractions",1200,800);
  hs->Draw();
  TString fracstring=m_path_img+"frac"+isolation+".png";
  fracstring.ReplaceAll( ".png", getCatString_noSel(mode)+".png" );
  if(CALC_SS_SR) fracstring.ReplaceAll( ".png", "_SS_SR.png" );
  gPad->SaveAs(fracstring);
  if (ALLPLOTS){
    fracstring.ReplaceAll( ".png", ".pdf");
    gPad->SaveAs(fracstring);
    fracstring.ReplaceAll( ".pdf", ".eps");
    gPad->SaveAs(fracstring);
  }

  //now some nicer plots
  if ( (CHAN != kTAU && nbins_weight == w_pt_n*w_dm_n) || (CHAN == kTAU && nbins_weight == w_mttot_n*w_dm_n) ){ //split by decay mode: only if total number of weight bins is #mt-bins*#dm-bins
    
    THStack* hs_split[w_dm_n]; for (int i=0; i<w_dm_n; i++) hs_split[i] = new THStack("w_split"+sNum[i],"");
    TLegend* leg = new TLegend(0.3,0.16,0.45,0.46);
    //    leg->SetFillColor(10);
    leg->SetShadowColor(10);
    leg->SetLineColor(10);
    
    std::vector<TH1D*> h_w_split[w_dm_n];
    for (int is=0; is<w_dm_n; is++){
      h_w_split[is].resize(NW);
      for (int j=0; j<NW-1; j++){
        if ( !DOQCD&& m_type[j].Contains("QCD") ) continue;
        Int_t n_tmp = 0;
        if(CHAN != kTAU) n_tmp = w_pt_n;
        else n_tmp = w_mttot_n;
        Double_t arr_tmp[n_tmp+1];
        if(CHAN != kTAU) for(int i=0;i<=n_tmp;i++) arr_tmp[i]=w_pt_v[i];
        else for(int i=0;i<=n_tmp;i++) arr_tmp[i]=w_mttot_v[i];
        
        h_w_split[is].at(j) = new TH1D("h_w_split"+mode+sNum[j]+sNum[is]+isolation ,"",n_tmp,arr_tmp);
        h_w_split[is].at(j)->SetFillColor(m_color[j]);
        for (int ib=0; ib<n_tmp; ib++){
          h_w_split[is].at(j)->SetBinContent( ib+1 , h_w.at(j)->GetBinContent(ib+1 + is*n_tmp) );
        }
        h_w_split[is].at(j)->SetMaximum(1.0);
        hs_split[is]->Add(h_w_split[is].at(j),"hist");
      }
      for (int j=NW-2; j>=0; j--){
        if (is==0){
          TString m_label="Multijet";
          for (int il=nSAMPLES-1; il>=0; il--){ if ( vsuff[il]==m_type[j] ) m_label=vlabel[il]; }
          cout << "M_LABEL: " << m_label << endl;
          leg->AddEntry(h_w_split[is].at(j),m_label,"f");
        }
      }
      TCanvas* c1s = new TCanvas("c1s","fractions_split",1200,800);
      gStyle->SetHistTopMargin(0.);
      hs_split[is]->Draw();
      //      hs_split[is]->GetYaxis()->SetRangeUser(0.0,1.0);
      hs_split[is]->SetMaximum(1.0);
      c1s->SetLogx();

      TString fracstring=m_path_img+"frac_split"+sNum[is]+isolation+".png";
      fracstring.ReplaceAll( ".png", getCatString_noSel(mode)+".png" );
      if(CALC_SS_SR) fracstring.ReplaceAll(".png","_SS_SR.png");
      gPad->SaveAs(fracstring);
      
      if(CHAN != kTAU)hs_split[is]->GetXaxis()->SetTitle(labelPt);
      else hs_split[is]->GetXaxis()->SetTitle("m_{T,tot} [GeV]");
      hs_split[is]->GetYaxis()->SetTitle("Fraction");
      hs_split[is]->Draw();
      leg->Draw();
      
      gPad->SaveAs(fracstring);
      
      if (ALLPLOTS){
        fracstring.ReplaceAll( ".png", ".pdf");
        gPad->SaveAs(fracstring);
        fracstring.ReplaceAll( ".pdf", ".eps");
        gPad->SaveAs(fracstring);
      }
      
      c1s->Close();
    }
    
  }
  
  c1->Close();
  
  delete hs;
  for (int i=0; i<NW-1; i++){
    delete h_w.at(i);
  }
  
}// end of calcWeightFromFit

Int_t FFCalculator::doTemplateFit(const TH1D *data, const std::vector<TH1D*> templates, const TString m_path_img, std::vector<TH1D*> &res, TH1D* &res_data, const Int_t mode){

  const unsigned NT=templates.size();

  TH1D *m_data=new TH1D(*data);
  //  for (int j=1; j<m_data->GetNbinsX(); j++) m_data->SetBinError(j,m_data->GetBinError(j)*5);

  THStack* hs2= new THStack("r","");
  for (unsigned i=0; i<NT; i++){
    templates.at(i)->SetFillColor(vcolor[i]);
    hs2->Add( templates.at(i),"hist" );
    //    std::cout << templates.at(i)->GetBinContent(1) << " " << templates.at(i)->GetBinContent(2) << " " << templates.at(i)->GetBinContent(3) << " " << templates.at(i)->GetBinContent(4) << " " << templates.at(i)->GetBinContent(5) << " " << templates.at(i)->GetBinContent(6) << std::endl;
  }
 
  TCanvas* cf; cf = new TCanvas("cf","fit fractions",1200,800);
  hs2->Draw();
  //  hs2->GetXaxis()->SetRangeUser(-0.5,20.5);
  m_data->SetLineWidth(3);
  m_data->SetMarkerStyle(8);
  m_data->SetMarkerSize(1.3);
  m_data->Draw("same Ep");
  /*gPad->SaveAs(m_path_img+"fraction_before_fit.png");
  if (ALLPLOTS){
    gPad->SaveAs(m_path_img+"fraction_before_fit.pdf");
    gPad->SaveAs(m_path_img+"fraction_before_fit.eps");
    //      c1->SaveAs(imagefilename+".C");                                                                                                                                                                                               
    }*/
  TString frac_before=m_path_img+"fraction_before_fit.png";
  frac_before.ReplaceAll( ".png", getCatString_noSel(mode)+".png" );
  if(CALC_SS_SR) frac_before.ReplaceAll(".png","_SS_SR.png");
  gPad->SaveAs(frac_before);
  if (ALLPLOTS){
    frac_before.ReplaceAll( ".png", ".pdf");
    gPad->SaveAs(frac_before);
    frac_before.ReplaceAll( ".pdf", ".eps");
    gPad->SaveAs(frac_before);
  }
  


  std::vector<TH1D*> c_templates(NT);
  TObjArray *m_templates = new TObjArray(NT);        // MC histograms are put in this array
  for (unsigned i=0; i<NT; i++){
    //  for (int j=1; j<templates.at(i)->GetNbinsX(); j++) templates.at(i)->SetBinError(j,templates.at(i)->GetBinError(j)*5);
    c_templates.at(i)=(TH1D*)templates.at(i)->Clone();
    for (int j=0; j<=c_templates.at(i)->GetNbinsX(); j++){ if (c_templates.at(i)->GetBinContent(j)<=0) c_templates.at(i)->SetBinContent(j,1e-36); } //avoid errors...
    m_templates->Add( c_templates.at(i) );
  }

  std::vector<Double_t> frac(NT);
  std::vector<Double_t> frac_err(NT);
  //  std::vector<TH1D*> res(NT);
  res.resize(NT); 
 
  TFractionFitter* fit = new TFractionFitter(m_data, m_templates,"Q"); // initialise
  //  TFractionFitter* fit = new TFractionFitter(m_data, m_templates); // initialise
  for(unsigned i=0; i<NT; i++) fit->Constrain(i,0.0,1.0);               // constrain fraction 1 to be between 0 and 1

  //  fit->SetRangeX(1,12);                    // use only the first 12 bins in the fit
  if (DEBUG) std::cout << "Excluding bins..." << std::endl;
  if (w_pt_n==25 && nbins_weight>=25){ for (int i=13; i<=25; i++) fit->ExcludeBin(i); } //exclude certaint mT bins with low stats
  if (w_pt_n==25 && nbins_weight>=50){ for (int i=38; i<=50; i++) fit->ExcludeBin(i); }
  Int_t status = fit->Fit();               // perform the fit
  std::cout << "fit status: " << status << std::endl;
  if (status == 0) {                       // check on fit status
    //    res_data = (TH1D*) fit->GetPlot();
    res_data=(TH1D*) m_data->Clone();
    //    res_data->Scale( 1/res_data->Integral() );
    THStack* hs = new THStack("r","");
    for (unsigned i=0; i<NT; i++){
      fit->GetResult( i, frac.at(i), frac_err.at(i) );
      std::cout << "Frac result: " << i << "\t" << frac.at(i) << " +/- " << frac_err.at(i) << std::endl;
      res.at(i) = (TH1D*)fit->GetMCPrediction(i);
      res.at(i)->Scale( 1/res.at(i)->Integral() * frac.at(i) );
      frac_err.at(i)/=frac.at(i); //relative unc
      for (int j=0; j<res.at(i)->GetNbinsX(); j++) res.at(i)->SetBinError( j+1 , frac_err.at(i)* res.at(i)->GetBinContent( j+1 ) );
      res.at(i)->SetFillColor(vcolor[i]);
      hs->Add( res.at(i),"hist" );
      //      std::cout << "     " << i << "\t" <<  res.at(i)->GetBinContent(1) << std::endl;
    }

    //    result->Draw("");
    //    m_data->Draw("same Ep");
    //    gPad->SaveAs(m_path_img+"result.png");

    hs->Draw();
    //    hs->GetXaxis()->SetRangeUser(-0.5,24.5);
    Double_t rd_int=res_data->Integral();
    res_data->Scale( 1/rd_int );
    res_data->SetLineWidth(3);
    res_data->SetMarkerStyle(8);
    res_data->SetMarkerSize(1.3);

    res_data->Draw("same Ep");

    TString frac_from=m_path_img+"fraction_from_fit.png";
    frac_from.ReplaceAll( ".png", getCatString_noSel(mode)+".png" );
    gPad->SaveAs(frac_from);
    if (ALLPLOTS){
      frac_from.ReplaceAll( ".png", ".pdf");
      gPad->SaveAs(frac_from);
      frac_from.ReplaceAll( ".pdf", ".eps");
      gPad->SaveAs(frac_from);
    }
    

    for (unsigned i=0; i<NT; i++) res.at(i)->Divide( res.at(i) , res_data , 1 , 1/res_data->Integral() );
    res_data->Scale( rd_int ); //return unnormalized histo
  }
  return status;

}

//calculate FF (with MC subtraction) for the case of subtracting any number of backgrounds, including none.
//FF_file is written out
void FFCalculator::calcFFCorr(const Int_t mode, const TString pre_main, const std::vector<TString> pre_sub, const TString FF_file, const TString weight_file, const Int_t cuts)
{

  if (DEBUG) {
    std::cout << "In calcFFCorr: \t Writing " << FF_file << std::endl;
    std::cout << "Creating counting histogram with " << this->nBins(mode) << " number of bins" << std::endl;
  }


  int doCR=1; //calculate FF in determination region
  if ( (mode & SR) ) { // for debugging purposes calculate FF in SR 
    doCR=0;
  } 


  TH1D counter_histo_proto("c_h","Counter histogram",this->nBins(mode),-0.5,this->nBins(mode)-0.5);


  TH1D* counter_histo_loose_CR = (TH1D*) counter_histo_proto.Clone("c_l"); 
  TH1D* weighted_bin_center_loose= (TH1D*) counter_histo_proto.Clone("bins_weighted");
  TH1D* counter_histo_tight_CR = (TH1D*) counter_histo_proto.Clone("c_t");


  TH1D* counter_histo_loose_CR_SS = (TH1D*) counter_histo_proto.Clone("c_l_ss"); 
  TH1D* counter_histo_tight_CR_SS = (TH1D*) counter_histo_proto.Clone("c_t_ss");
  

  TH1D* fakefactor_histo = (TH1D*) counter_histo_proto.Clone("c_f");
  
  std::vector<TH1D*> counter_histo_loose_CR_cont;
  std::vector<TH1D*> counter_histo_tight_CR_cont;
  std::vector<TH1D*> counter_histo_loose_CR_SS_cont;
  std::vector<TH1D*> counter_histo_tight_CR_SS_cont;  
  
  for (unsigned i=0; i<pre_sub.size(); i++){
    TString tmp; tmp+=i;
    counter_histo_loose_CR_cont.push_back( (TH1D*) counter_histo_proto.Clone("cc"+tmp+"_l")  );
    counter_histo_tight_CR_cont.push_back( (TH1D*) counter_histo_proto.Clone("cc"+tmp+"_t")  );
    counter_histo_loose_CR_SS_cont.push_back( (TH1D*) counter_histo_proto.Clone("cc"+tmp+"_l_ss")  );
    counter_histo_tight_CR_SS_cont.push_back( (TH1D*) counter_histo_proto.Clone("cc"+tmp+"_t_ss")  );
  }

  TH1D* counter_histo_numer = (TH1D*) counter_histo_proto.Clone("numer");
  TH1D* counter_histo_denom = (TH1D*) counter_histo_proto.Clone("denom");
  
  TH1D* counter_histo_numer_SS = (TH1D*) counter_histo_proto.Clone("numer_SS");
  TH1D* counter_histo_denom_SS = (TH1D*) counter_histo_proto.Clone("denom_SS");

  int nT=0;
  int nL=0;
  Double_t bin_values[this->getNjets(mode)*this->getNtracks(mode)][this->getNpts(mode)]={{0}}; 
  Double_t bin_counters[this->getNjets(mode)*this->getNtracks(mode)][this->getNpts(mode)]={};
  


  

  loadFile(pre_main,"Events");
  
  // Start loop over tree
  Int_t nentries = Int_t(event_s->fChain->GetEntries());
  unsigned int tau_index=0; //only consider first tau, unless MULTITAU=1
  unsigned ntau = 1;
  

  
  // TString cutstringgg = this->getCRCutString(mode); // used with Draw: for the moment event loop is faster 
  

  int ccc_t = 0;
  int ccc_l = 0;
  
  auto start = std::chrono::system_clock::now();
  auto end  = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end -start;

  for (Int_t jentry=0; jentry<nentries;jentry++) {
    event_s->GetEntry(jentry);
      
    if (  ( doCR && this->isInCR(mode,tau_index) ) || ( !doCR && this->isInSR(mode,tau_index) )    ) {
            
      nT=this->isTight(mode,tau_index); 
      nL=this->isLoose(mode,tau_index); 
      
      if (nT) {
        ccc_t++;
        counter_histo_tight_CR->Fill(    this->getBin(mode,tau_index),event_s->weight_sf);
      }
      else if (nL) {
        ccc_l++;
        counter_histo_loose_CR->Fill(    this->getBin(mode,tau_index),event_s->weight_sf);

        // Below store sum_of_weights in bin_counters and sum of weighted tau pt in bin_values
        Int_t pT_index=this->getPtIndex(mode,tau_index);
        Int_t njet_index=this->getNjetIndex(mode,tau_index);
        Int_t dm_index=this->getTrackIndex(mode,tau_index);

        bin_values[dm_index+this->getNtracks(mode)*njet_index][pT_index]   += event_s->alltau_pt->at(tau_index)*event_s->weight_sf;
        bin_counters[dm_index+this->getNtracks(mode)*njet_index][pT_index] += event_s->weight_sf;
      }
    }
    else if(mode & _W_JETS) {
    if (this->isInCR(_SS,tau_index) )  {
      nT=this->isTight(mode,tau_index); 
      nL=this->isLoose(mode,tau_index); 
      
      if (nT) {
        ccc_t++;
        counter_histo_tight_CR_SS->Fill(    this->getBin(mode,tau_index),event_s->weight_sf);
      }
      else if (nL) {
        ccc_l++;
        counter_histo_loose_CR_SS->Fill(    this->getBin(mode,tau_index),event_s->weight_sf);

      }
    }    
    }
  } //end loop over entries

  end  = std::chrono::system_clock::now();
  elapsed_seconds = end-start;

  std::cout << "******************************************************" << std::endl;
  std::cout << "Elapsed time (OLD): " << elapsed_seconds.count() << std::endl;
  std::cout << "counter histo tight: " << counter_histo_tight_CR->GetEntries() << std::endl;
  std::cout << "compare to : " << ccc_t << std::endl;
  std::cout << "counter histo loose: " << counter_histo_loose_CR->GetEntries() << std::endl;
  std::cout << "compare to : " << ccc_l << std::endl;
  std::cout << "******************************************************" << std::endl;
  
  //using Draw instead
  // start = std::chrono::system_clock::now();
  // event_s->fChain->Draw( "1>>c_t", "weight_sf * "+cutstringgg + "*" + this->getWPCutString("tight"), "goff");
  // event_s->fChain->Draw( "1>>c_l", "weight_sf * "+cutstringgg + "*" + this->getWPCutString("loose"), "goff");
  // end  = std::chrono::system_clock::now();
  // elapsed_seconds = end-start;
  
  // std::cout << "******************************************************" << std::endl;
  // cout << "Elapsed time (NEW): " << elapsed_seconds.count() << endl;
  // std::cout << "counter histo tight: " << counter_histo_tight_CR->GetEntries() << std::endl;
  // std::cout << "compare to : " << ccc_t << std::endl;
  // std::cout << "counter histo loose: " << counter_histo_loose_CR->GetEntries() << std::endl;
  // std::cout << "compare to : " << ccc_l << std::endl;
  // std::cout << "******************************************************" << std::endl;
  
  

  if (DEBUG) std::cout<<"in "<<pre_main<<": "<<counter_histo_loose_CR->Integral(-1,-1) <<" loose, "<<counter_histo_tight_CR->Integral(-1,-1)<<" tight."<<std::endl;

  ccc_t = 0;
  ccc_l = 0;
  TString tmp2; 
  for (unsigned is=0; is<pre_sub.size(); is++){ // Loop over all backgrounds that need to be subtracted
    
    loadFile(pre_sub.at(is),"Events");
    
    ccc_t  = 0;
    ccc_l  = 0;
    nentries = Int_t(event_s->fChain->GetEntries());
    
    start = std::chrono::system_clock::now();
    for (Int_t jentry=0; jentry<nentries;jentry++) {
      
      event_s->GetEntry(jentry);  
      if (  ( doCR && this->isInCR(mode,tau_index) ) || ( !doCR && this->isInSR(mode,tau_index) )   ) {
        nT=this->isTight(mode,tau_index); 
        nL=this->isLoose(mode,tau_index); 
       
        if (nT) {
          ccc_t++;
          counter_histo_tight_CR_cont.at(is)->Fill(this->getBin(mode,tau_index),event_s->weight_sf);
        }
        else if (nL) {
          counter_histo_loose_CR_cont.at(is)->Fill(this->getBin(mode,tau_index),event_s->weight_sf);
          ccc_l++;

          // Below store sum_of_weights in bin_counters and sum of weighted tau pt in bin_values
          Int_t pT_index=this->getPtIndex(mode,tau_index);
          Int_t njet_index=this->getNjetIndex(mode,tau_index);
          Int_t dm_index=this->getTrackIndex(mode,tau_index);
          bin_values[dm_index+this->getNtracks(mode)*njet_index][pT_index]=bin_values[dm_index+this->getNtracks(mode)*njet_index][pT_index]+event_s->alltau_pt->at(tau_index)*event_s->weight_sf*(-1);
          bin_counters[dm_index+this->getNtracks(mode)*njet_index][pT_index]=bin_counters[dm_index+this->getNtracks(mode)*njet_index][pT_index]+event_s->weight_sf*(-1);
        }
      }
      else if (mode & _W_JETS) {
      if (this->isInCR(_SS,tau_index) )  {
        nT=this->isTight(mode,tau_index); 
        nL=this->isLoose(mode,tau_index); 
       
        if (nT) {
          ccc_t++;
          counter_histo_tight_CR_SS_cont.at(is)->Fill(this->getBin(mode,tau_index),event_s->weight_sf);
        }
        else if (nL) {
          counter_histo_loose_CR_SS_cont.at(is)->Fill(this->getBin(mode,tau_index),event_s->weight_sf);
          ccc_l++;

        }
      }      
      }

    } // end loop over entries
    if (DEBUG) std::cout<<std::endl<<"In contamination file "<<pre_sub.at(is)<<" "<< counter_histo_loose_CR_cont.at(is)->Integral(-1,-1) <<" loose "<<counter_histo_tight_CR_cont.at(is)->Integral(-1,-1)<<" tight."<<std::endl;
    end  = std::chrono::system_clock::now();
    elapsed_seconds = end-start;
    std::cout << "******************************************************" << std::endl;
    cout << "Elapsed time (OLD): " << elapsed_seconds.count() << endl;
    std::cout << "counter histo tight: " << counter_histo_tight_CR_cont.at(is)->GetEntries() << std::endl;
    std::cout << "compare to : " << ccc_t << std::endl;
    std::cout << "counter histo loose: " << counter_histo_loose_CR_cont.at(is)->GetEntries() << std::endl;
    std::cout << "compare to : " << ccc_l << std::endl;
    std::cout << "******************************************************" << std::endl;
    
  }





  counter_histo_numer->Add(counter_histo_tight_CR);
  counter_histo_denom->Add(counter_histo_loose_CR);

  counter_histo_numer_SS->Add(counter_histo_tight_CR_SS);
  counter_histo_denom_SS->Add(counter_histo_loose_CR_SS);
  std::cout << "QCD SUB TIGHT: Integral ss data before MC sub " << counter_histo_numer_SS->Integral() << std::endl;
  std::cout << "QCD SUB LOOSE: Integral ss data before MC sub " << counter_histo_denom_SS->Integral() << std::endl;

  for (unsigned is=0; is<pre_sub.size(); is++){
    counter_histo_numer_SS->Add(counter_histo_tight_CR_SS_cont.at(is),-1.);
    counter_histo_denom_SS->Add(counter_histo_loose_CR_SS_cont.at(is),-1.);
  }

  std::cout << "QCD SUB TIGHT: Integral ss data after MC sub " << counter_histo_numer_SS->Integral() << std::endl;
  std::cout << "QCD SUB LOOSE: Integral ss data after MC sub " << counter_histo_denom_SS->Integral() << std::endl;

  std::cout << "QCD SUB TIGHT: Actual integral before QCD sub " << counter_histo_numer->Integral() << std::endl;
  std::cout << "QCD SUB LOOSE: Actual integral before QCD sub " << counter_histo_denom->Integral() << std::endl;

  counter_histo_numer->Add(counter_histo_numer_SS,-1.);
  counter_histo_denom->Add(counter_histo_denom_SS,-1.);
  std::cout << "QCD SUB TIGHT: Actual integral after QCD sub " << counter_histo_numer->Integral() << std::endl;
  std::cout << "QCD SUB LOOSE: Actual integral after QCD sub " << counter_histo_denom->Integral() << std::endl;

  TH1D* counter_histo_numer_mcup; TH1D* counter_histo_numer_mcdown; 
  TH1D* counter_histo_denom_mcup; TH1D* counter_histo_denom_mcdown; 

  counter_histo_numer_mcup =(TH1D*) counter_histo_numer->Clone("counter_histo_numer_mcup");
  counter_histo_numer_mcdown =(TH1D*) counter_histo_numer->Clone("counter_histo_numer_mcdown");
  counter_histo_denom_mcup =(TH1D*) counter_histo_denom->Clone("counter_histo_denom_mcup");
  counter_histo_denom_mcdown =(TH1D*) counter_histo_denom->Clone("counter_histo_denom_mcdown");

  for (unsigned is=0; is<pre_sub.size(); is++){
    counter_histo_numer->Add(counter_histo_tight_CR_cont.at(is),-1.);
    counter_histo_denom->Add(counter_histo_loose_CR_cont.at(is),-1.);

    counter_histo_numer_mcup->Add(counter_histo_tight_CR_cont.at(is),-1.*1.07);
    counter_histo_denom_mcup->Add(counter_histo_loose_CR_cont.at(is),-1.*1.07);
    counter_histo_numer_mcdown->Add(counter_histo_tight_CR_cont.at(is),-1./1.07);
    counter_histo_denom_mcdown->Add(counter_histo_loose_CR_cont.at(is),-1./1.07);
  }

  TString ff_file=FF_file; 
  TFile f(ff_file,"RECREATE");
  f.cd();
  
  fakefactor_histo = counter_histo_numer; 
  
  //  fakefactor_histo->Divide(counter_histo_denom); //uncorrelated errors
  fakefactor_histo->Divide(fakefactor_histo,counter_histo_denom,1,1); //Gaussian error propagation
  counter_histo_numer_mcup->Divide(counter_histo_denom_mcup);
  counter_histo_numer_mcdown->Divide(counter_histo_denom_mcdown);
  counter_histo_numer_mcup->SetTitle("FakeFactor_mcup");
  counter_histo_numer_mcdown->SetTitle("FakeFactor_mcdown");
  counter_histo_numer_mcup->SetName("c_t_mcup");
  counter_histo_numer_mcdown->SetName("c_t_mcdown");
  fakefactor_histo->SetTitle("Fakefactor");
  fakefactor_histo->SetName("c_t");
  fakefactor_histo->Write();
  counter_histo_numer_mcup->Write();
  counter_histo_numer_mcdown->Write();


  // filling histogram weighted_bin_center_loose in loose background control region CR
  for(Int_t ijets=0;ijets<this->getNjets(mode);ijets++){
    for(Int_t idm=0;idm<this->getNtracks(mode);idm++){
      for(Int_t ipt=0;ipt<this->getNpts(mode);ipt++){
        std::cout << "ijets: " << ijets << " idm: " << idm << " ipt: " << ipt << std::endl;
        if (DEBUG){
          cout << "Weighted: " << bin_values[idm+ijets*this->getNtracks(mode)][ipt] << endl;
          cout << "Counted: " << bin_counters[idm+ijets*this->getNtracks(mode)][ipt] << endl;
          cout << "Ratio: " << bin_values[idm+ijets*this->getNtracks(mode)][ipt]/bin_counters[idm+ijets*this->getNtracks(mode)][ipt] << endl;
        }
        weighted_bin_center_loose->SetBinContent(ipt+this->getNpts(mode)*idm + (this->getNpts(mode)*this->getNtracks(mode))*ijets + 1,bin_values[idm+ijets*this->getNtracks(mode)][ipt]/bin_counters[idm+ijets*this->getNtracks(mode)][ipt] ); 
      }      
    }
  }
  weighted_bin_center_loose->Write();
                                               
            
  
  f.Close();

  if (DEBUG){  
    std::cout << std::endl;
    std::cout << "Value\t\tError"<<std::endl;
    for(int i=0;i<this->nBins(mode);i++) {
      std::cout << fakefactor_histo->GetBinContent(i+1)<<"\t"<<fakefactor_histo->GetBinError(i+1)<<std::endl;
    }
  }
  
  
}



TH1D* FFCalculator::setCorrValue(const TString fname, const TString hname){
  TFile *fc = new TFile(fname);
  TH1D* h_corr;
  h_corr = (TH1D*) fc->Get(hname);
  cout << fname << " " << hname << " " << h_corr << endl;
  return h_corr;
}

//so far only works versus mT, and with specific bin choices
Double_t FFCalculator::getCorrValueFit(Double_t m_corr_d, Double_t m_corr_k, Int_t ind){

  for (int i=0; i<NB_MTCORR; i++){
    if ( corr_d[i]<-999 || corr_k[i]<-999 ){ std::cout << "ERROR: TNtupleAnalyzer::getCorrValueFit: W correction fit not initialised! Index " <<  i << std::endl; return -999; }
  }

  if ( !USE_FIT_BINS ){
    double m_mt=selVal(MT,ind);
    if ( m_mt > MT_CORR_MAX ) return 1;
    if ( m_corr_d < -900 || m_corr_k < -900 ){
      int p_ind=getPInd( event_s->alltau_decay->at(ind) );
      m_corr_d=corr_d[p_ind];
      m_corr_k=corr_k[p_ind];
    }
    return ( m_corr_d+m_mt * m_corr_k );
  }

  //from here if unit size bins for fit are used, starting at -0.5
  Double_t n_mt=selVal(MT,ind)/10.; //FIXME
  if (n_mt<0) return -1;
  if (n_mt>(nFIT_BINS-1)) return 1; //for mT>XX, FIXME

  if ( m_corr_d < -900 || m_corr_k < -900 ){
    int p_ind=getPInd( event_s->alltau_decay->at(ind) );
    m_corr_d=corr_d[p_ind];
    m_corr_k=corr_k[p_ind];
  }

  Double_t ret= m_corr_d+(n_mt-0.5)*m_corr_k; //since -0.5 on fitted histo corresponds to mt=0, and +6.5 to mt=70

  return ret;
}

Double_t FFCalculator::getCorrValueFitErr(Double_t m_mt, Int_t ind){
  Double_t n_mt;
  Double_t ret;

  int p_ind=getPInd( event_s->alltau_decay->at(ind) );
  if ( USE_FIT_BINS ){
    n_mt=m_mt/10.; //FIXME
    if (m_mt==-999) n_mt=selVal(MT,ind)/10.;
    //  if (n_mt<0) return ( this->getCorrValueFitErr(40) ); //average uncertainty - the middle fitted bin //XXX
    if (n_mt<0) return ( this->getCorrValueFitErr( FIT_BINS[ (nFIT_BINS-1)/2 ] , ind ) ); //average uncertainty - the middle fitted bin //XXX
    if (n_mt>(nFIT_BINS-1)) return 0; //for mT>70, no uncertainty due to fit
    ret= corr_d[p_ind]+(n_mt-0.5)*corr_k[p_ind]; //since -0.5 on fitted histo corresponds to mt=0, and +6.5 to mt=70
  } else{
    n_mt=m_mt;
    if ( n_mt>MT_CORR_MAX ) return 0;
    if (m_mt==-999) n_mt=selVal(MT,ind);
    if ( n_mt<0 ) return( this->getCorrValueFitErr( 40 , ind ) );
    ret= corr_d[p_ind]+n_mt*corr_k[p_ind];
  }

  if (ret==0) return -999;

  /*
   *   //correlated
     Double_t err_hi=  fabs(  (corr_d+corr_d_err)  +  (n_mt-0.5)*  (corr_k+corr_k_err)  -  ret ) / ret;
       Double_t err_lo=  fabs(  (corr_d-corr_d_err)  +  (n_mt-0.5)*  (corr_k-corr_k_err)  -  ret ) / ret;
         if ( err_hi > err_lo ) return err_hi; else return err_lo;
  */

  /*
   *   //anti-correlated
     Double_t err_hi=  fabs(  (corr_d+corr_d_err)  +  (n_mt-0.5)*  (corr_k-corr_k_err)  -  ret ) / ret;
       Double_t err_lo=  fabs(  (corr_d-corr_d_err)  +  (n_mt-0.5)*  (corr_k+corr_k_err)  -  ret ) / ret;
         if ( err_hi > err_lo ) return err_hi; else return err_lo;
  */

  //the correct way
  double y_err2=corr_k_err[p_ind]*corr_k_err[p_ind] * ( corr_SSxxOverN[p_ind] + pow( n_mt -corr_avg_x[p_ind], 2) );
  return ( sqrt(y_err2)/ret );

}

double FFCalculator::getCorrValue(const double value, const int err, TH1D* h_corr){

  int ib=h_corr->FindBin( value );
  if ( err == 0 ) return h_corr->GetBinContent(ib);
  if ( err == 1 ) return h_corr->GetBinError(ib);

  return 1;
}


void FFCalculator::createSystRatio(const TString fin1, const TString fin2, const TString fout, const int mode, const TString plotfile, const int ratio, const int incl_stat_err){

  std::cout << "In TNtupleAnalyzer::createSystRatio, creating " << fout << "...\t" << flush;

  TString xlabel="";
  TString hname="hh_";
  //  if ( description.Contains("looseSR") ) hname+="l_"; else 
  hname+="t_";
  if ( fout.Contains("_mt_")   || fout.Contains("_mt.")   ){ hname+="mt";   xlabel=labelMt;   }
  if ( fout.Contains("_mvis_") || fout.Contains("_mvis.") ){ hname+="mvis"; xlabel=labelMvis; }
  if ( fout.Contains("_pt_")   || fout.Contains("_pt.")   ){ hname+="pt";   xlabel=labelPt;   }

  TFile f1(fin1);
  TH1D* h1 = (TH1D*) f1.Get(hname);
  //  std::cout << fin1 << " " << f1.IsZombie() << " " << h1 << std::endl;
  TFile f2(fin2);
  TH1D* h2 = (TH1D*) f2.Get(hname);

  TH1D* h3; 

  if (ratio){  //ratio: for corrections
    h3=(TH1D*) h2->Clone("corr");
    h3->Divide(h1); //if a bin in either h1 or h2 is 0, it will be 0 in h3
    for (int i=0; i<=h3->GetNbinsX(); i++){
      if ( h3->GetBinContent(i)<1e-6 ) h3->SetBinContent( i , 1 );
    }
  } else{  //relative difference: for uncertainties
    h3=(TH1D*) h1->Clone("sys");
    h3->Add(h2,-1); //if a bin in either h1 or h2 is 0, it will be 0 in h3
    for (int i=0; i<=h3->GetNbinsX(); i++){
      h3->SetBinContent( i , fabs( h3->GetBinContent(i) ) );
    }
    h3->Divide(h2);
    //    h3->Divide(h2); //if a bin in either h1 or h2 is 0, it will be 0 in h3
    //    for (int i=0; i<h3->GetNbinsX(); i++){
    //      h3->SetBinContent( i , fabs( 1 - h3->GetBinContent(i) ) );
    //    }
    if (incl_stat_err){ //incl. stat unc. of the syst. unc. in the syst. unc.
      for (int i=0; i<=h3->GetNbinsX(); i++){
	double bc=h3->GetBinContent(i);
        double bcerr=h3->GetBinError(i);
	h3->SetBinContent( i , sqrt( bc*bc + bcerr*bcerr ) );
      }
    }
  }

  TFile f(fout,"RECREATE");
  h3->Write();
  f.Close();

  std::cout << "...done" << std::endl;

  if (plotfile=="") return;




  Int_t m_color=0;
  TString desc="non-closure ";
  TString l2="Sim";
  if (mode & _W_JETS)                 {    m_color=color_Wjets; desc+=vlabel[0]; }
  else if (mode & _DY){    m_color=color_DY_J;  desc+=vlabel[1]; }
  else if (mode & _TT){    m_color=color_TT_J;  desc+=vlabel[4]; }
  else if (mode & _QCD)               {    m_color=color_QCD;   desc+=vlabel[7]; l2="CR"; }
  h1->SetMarkerColor(m_color);
  h2->SetMarkerColor(m_color);
  h1->SetLineColor(m_color);
  h2->SetLineColor(m_color);

  TLegend *leg = new TLegend(0.55,0.68,0.89,0.88);
  //    leg = new TLegend(0.55,0.15,0.89,0.35);                                                                                                                                                                                
  leg->AddEntry(h1,"FF","lep");
  leg->AddEntry(h2,l2,"lep");

  this->makeRatioPlot(h1, h2, plotfile, desc, xlabel, leg);

}

void FFCalculator::createFitSystRatio(const TString FF1, const TString FF2, const TString pname1, const TString pname2, const int ind){
  Double_t m_corr_d1, m_corr_k1, m_corr_d_err1, m_corr_k_err1, m_corr_SSxxOverN1, m_corr_avg_x1;
  Double_t m_corr_d2, m_corr_k2, m_corr_d_err2, m_corr_k_err2, m_corr_SSxxOverN2, m_corr_avg_x2;
  this->doCorrFit(FF1, pname1, m_corr_d1, m_corr_k1, m_corr_d_err1, m_corr_k_err1, m_corr_SSxxOverN1, m_corr_avg_x1 );
  this->doCorrFit(FF2, pname2, m_corr_d2, m_corr_k2, m_corr_d_err2, m_corr_k_err2, m_corr_SSxxOverN2, m_corr_avg_x2 );

  sys_corr_d[ind] = m_corr_d1 - m_corr_d2;
  sys_corr_k[ind] = m_corr_k1 - m_corr_k2;

  std::cout << "createFitSystRatio: " << ind << " d1= " << m_corr_d1 << "\t k1= " << m_corr_k1 << std::endl;
  std::cout << "createFitSystRatio: " << ind << " d2= " << m_corr_d2 << "\t k2= " << m_corr_k2 << std::endl;
}

void FFCalculator::initCorrFit(const TString filename[NB_MTCORR], const TString plotfilename[NB_MTCORR], const TString formfilename){
  for (int i=0; i<NB_MTCORR; i++){
    this->doCorrFit(filename[i], plotfilename[i], corr_d[i], corr_k[i], corr_d_err[i], corr_k_err[i], corr_SSxxOverN[i], corr_avg_x[i] );
    if (formfilename!="") std::cout << "doCorrFit: " << i << " d= " << corr_d[i] << "\t k= " << corr_k[i] << std::endl;
  }

  //FIXME: only works for separate 1p/3p fit for now
  if ( formfilename!="" && NB_MTCORR==2 ){
    double d1=corr_d[0]-(5./10.)*corr_k[0];
    double k1=corr_k[0]/10;
    double d3=corr_d[1]-(5./10.)*corr_k[1];
    double k3=corr_k[1]/10;

    TString form="(x[0]<70)*((x[1]<4.5)*("; form+=k1; form+="*x[0]+"; form+=d1; form+=")+"; //1p
    form+="(x[1]>4.5)*("; form+=k3; form+="*x[0]+"; form+=d3; form+=")"; //3p
    form+=")+(x[0]>=70)"; //1 for mT>70             
    TFormula mtCorrection("form_mtCorr", form ); //parameters: 0 - mT , 1 - decayMode
    
    TFile* file = new TFile(formfilename, "recreate");
    mtCorrection.Write();
    //    file->WriteObject(factor, "ff");
    file->Close();
  }

}

void FFCalculator::doCorrFit(const TString filename, const TString plotfilename, 
				Double_t &m_corr_d, Double_t &m_corr_k, Double_t &m_corr_d_err, Double_t &m_corr_k_err, Double_t &m_corr_SSxxOverN, Double_t &m_corr_avg_x){

  TFile f(filename);
  TH1D *m_corr_histo_raw=(TH1D*)f.Get("c_t"); //mf
  TH1D *m_corr_histo; //mf
  //  if (!m_corr_histo) std::cout << "doCorrFit: histo c_t not found in " << filename << std::endl;

  TCanvas c1;

  if (m_corr_histo_raw){ //mf
    if (USE_FIT_BINS){
      m_corr_histo=(TH1D*)m_corr_histo_raw->Clone(); //mf
      m_corr_histo->SetTitle("");
      //  m_corr_histo->GetXaxis()->SetRangeUser(-0.5,MT_FIT_UP_TO+1); //6.5 for up to 70 GeV
      m_corr_histo->GetXaxis()->SetRangeUser(-0.5,MT_FIT_UP_TO); //6.5 for up to 70 GeV
      for (unsigned i=0; i<nFIT_BINS; i++){
	//    TString tmp; tmp+=p_mt_v[i]; tmp+="-"; tmp+=p_mt_v[i+1];
	TString tmp; tmp+=FIT_BINS[i]; tmp+="-"; tmp+=FIT_BINS[i+1];
	m_corr_histo->GetXaxis()->SetBinLabel(i+1,tmp);
      }
    }
    else{ //mf
      m_corr_histo=new TH1D("c_"+(TString)m_corr_histo_raw->GetName(),"",nFIT_BINS,0,FIT_BINS[nFIT_BINS-1]+FIT_BINS[1]-FIT_BINS[0]); //mf
      for (unsigned ib=1; ib<=nFIT_BINS; ib++){
	m_corr_histo->SetBinContent( ib , m_corr_histo_raw->GetBinContent(ib) );
	m_corr_histo->SetBinError( ib , m_corr_histo_raw->GetBinError(ib) );
      }
    } //mf
    m_corr_histo->SetYTitle("normalised FF");
    m_corr_histo->Scale( 1/m_corr_histo->GetBinContent(nFIT_BINS) );
  } else{
    m_corr_histo=(TH1D*)f.Get("corr");
    if (!m_corr_histo) std::cout << "doCorrFit: histo corr or c_t not found in " << filename << std::endl;
    m_corr_histo->SetTitle("");
    //    m_corr_histo->GetXaxis()->SetRangeUser(0,80); //6.5 for up to 70 GeV
    m_corr_histo->SetYTitle("FF");
  }
  if (USE_FIT_BINS){
    m_corr_histo->Fit("pol1","Q","",-0.5,MT_FIT_UP_TO);
  }else{
    if (DEBUG) m_corr_histo->Fit("pol1","" ,"",0,80);
    else       m_corr_histo->Fit("pol1","Q","",0,80);
  }
  TF1 *fitres = m_corr_histo->GetFunction("pol1");
  m_corr_histo->SetXTitle(labelMt);
  
  m_corr_d=fitres->GetParameter(0);
  m_corr_k=fitres->GetParameter(1);
  m_corr_d_err=fitres->GetParError(0);
  m_corr_k_err=fitres->GetParError(1);

  Int_t nfit=fitres->GetNumberFitPoints();

  m_corr_avg_x=0;
  for (int i=1; i<=nfit; i++){
    m_corr_avg_x+=m_corr_histo->GetBinCenter(i)*1.0/nfit;
  }
  //cout << m_corr_avg_x << std::endl;

  m_corr_SSxxOverN=0;
  for (int i=1; i<=nfit; i++){
    m_corr_SSxxOverN+=pow( m_corr_histo->GetBinCenter(i)-m_corr_avg_x , 2)/nfit;
  }
  //cout << m_corr_SSxxOverN << std::endl;
  m_corr_histo->GetYaxis()->SetRangeUser(0.0,1.3); //6.5 for up to 70 GeV

  if (plotfilename!="") gPad->SaveAs(plotfilename+".png");

  f.Close();
}

void FFCalculator::getInputs(vector<double>&inputs, Int_t ind)
{
  if(CHAN==kTAU){
    inputs.push_back(event_s->alltau_pt->at(ind) );
    inputs.push_back(event_s->lep_pt);
    inputs.push_back(event_s->alltau_decay->at(ind) );
    inputs.push_back(event_s->njets);
    inputs.push_back(event_s->alltau_mvis->at(ind) );
    inputs.push_back(event_s->lep_iso);
  }
  else{
    inputs.push_back(event_s->alltau_pt->at(ind) );
    inputs.push_back(event_s->alltau_decay->at(ind) );
    inputs.push_back(event_s->njets);
    inputs.push_back(event_s->alltau_mvis->at(ind) );
    inputs.push_back(event_s->alltau_mt->at(ind) );
    inputs.push_back(event_s->lep_iso);
  }
  
}


void FFCalculator::calc_nonclosure(const Int_t mode, const TString raw_ff, const TString compare_file, TString ff_output, const TString tight_cat, const Int_t doPlot, const Int_t subtractMC, const Int_t tau_ind){

  cout << "Calculating corrections for " << ff_output << endl;
  cout << "mode: " << mode << endl;
  cout << "raw ff: " << raw_ff << endl; // contains dm0_njet0 dm0_njet1 of type TGrapAsymmeErrors
  cout << "compare_file: " << compare_file << endl; //contains TH1Ds: hh_l_mvis, hh_l_mvis_MCsubtracted, hh_l_mvis_dataminusMC and the same for tight
  cout << "ff_output: " << ff_output << endl;
  cout << "tight_cat: " << tight_cat << endl; // always "" since not doing alt anymore
  cout << "doPlot: " << doPlot << endl; // 
  cout << "subtractMC: " << subtractMC << endl; // is probably always 1 (default) 
  cout << "tau_ind: " << tau_ind << endl;
  

  Int_t nentries = Int_t(event_s->fChain->GetEntries());
  
  TString cr_file = compare_file;
  
  if(mode & JET0 ) cr_file = cr_file.ReplaceAll("_data","_0jet_data"); // used for dedicated Njet correction
  if(mode & JET1 ) cr_file = cr_file.ReplaceAll("_data","_1jet_data"); // used for dedicated Njet correction
  
  TString sample;
  if(mode & _QCD) sample="_QCD";
  if(mode & _W_JETS) sample="_Wjets";
  if(mode & _TT) sample="_TT";
  if(!subtractMC) sample+="_MC"; // probably obsolete
  std::cout << "sample name extension " << sample << std::endl;

  
  TH1D *closure_h;
  if(mode & _TT) closure_h= new TH1D("closure"+sample,"",nbins_mvis,hist_min_mvis,hist_max_mvis); // closure plot 15 bins between [0,250]
  else closure_h= new TH1D("closure"+sample,"",w_mvis_n,w_mvis_v); // closure plot with binning {0,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,225,250,300,350,450}
  
  
  TFile *output = new TFile(ff_output.ReplaceAll(".root",tight_cat+".root"),"RECREATE"); //can be simplified. 
  TH1D *output_h = new TH1D("nonclosure_mvis","",w_mvis_n,w_mvis_v); // output histogram with binning {0,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,225,250,300,350,450}
  TH1D* output_h_mcup; TH1D* output_h_mcdown;

  TFile FF_lookup(raw_ff);
  TH1D* FF_lookup_h = nullptr;
  
  // fill the fits to the raw FFs in the vector fittedFFs. ToDo: Why is dm1 also needed - without it get segfault
  vector<TGraphAsymmErrors*> fittedFFs;
  TGraphAsymmErrors *dm0njet0 = (TGraphAsymmErrors*) FF_lookup.Get("dm0_njet0"+tight_cat); fittedFFs.push_back(dm0njet0);
  TGraphAsymmErrors *dm1njet0 = (TGraphAsymmErrors*) FF_lookup.Get("dm1_njet0"+tight_cat); fittedFFs.push_back(dm1njet0);
  TGraphAsymmErrors *dm0njet1 = (TGraphAsymmErrors*) FF_lookup.Get("dm0_njet1"+tight_cat); fittedFFs.push_back(dm0njet1);
  TGraphAsymmErrors *dm1njet1 = (TGraphAsymmErrors*) FF_lookup.Get("dm1_njet1"+tight_cat); fittedFFs.push_back(dm1njet1);
  
  if (mode & _QCD) { // ToDo: for more jet categories
    TGraphAsymmErrors *dm0njet2 = (TGraphAsymmErrors*) FF_lookup.Get("dm0_njet2"+tight_cat); fittedFFs.push_back(dm0njet2);
    TGraphAsymmErrors *dm1njet2 = (TGraphAsymmErrors*) FF_lookup.Get("dm1_njet2"+tight_cat); fittedFFs.push_back(dm1njet2);
  }

  
  TFile compare(cr_file);
  Double_t FF_value=0;

  if(subtractMC){ // always true
    TString ff_inputHist="hh_l"; 
    TH1D* compare_l              = (TH1D*) compare.Get(ff_inputHist+"_mvis");
    TH1D* compare_l_MCsubtracted = (TH1D*) compare.Get(ff_inputHist+"_mvis_MCsubtracted");
    TH1D* compare_l_dataminusMC  = (TH1D*) compare.Get(ff_inputHist+"_mvis_dataminusMC");
    
    TH1D* ratio_l_mcup                = (TH1D*)compare_l_MCsubtracted->Clone("ratio_l_mcup");
    ratio_l_mcup->Scale(1.07);
    TH1D* ratio_l_mcdown                = (TH1D*)compare_l_MCsubtracted->Clone("ratio_l_mcdown");
    ratio_l_mcdown->Scale(1.0/1.07);
    TH1D* ratio_l                = (TH1D*)compare_l_MCsubtracted->Clone("ratio_l");
  
    ratio_l->Divide(compare_l);
    ratio_l_mcup->Divide(compare_l);
    ratio_l_mcdown->Divide(compare_l);

    ///get unity histogram
    TH1D *unity_h = new TH1D("unity","",w_mvis_n,w_mvis_v);
    for(int ibin=1; ibin<=unity_h->GetNbinsX(); ibin++) unity_h->SetBinContent(ibin,1.);
    ratio_l->Add(unity_h,-1);ratio_l->Scale(-1);
    ratio_l_mcup->Add(unity_h,-1);ratio_l_mcup->Scale(-1);
    ratio_l_mcdown->Add(unity_h,-1);ratio_l_mcdown->Scale(-1);

    TH1D* compare_t              = (TH1D*) compare.Get("hh_t"+tight_cat+"_mvis");
    TH1D* compare_t_MCsubtracted = (TH1D*) compare.Get("hh_t"+tight_cat+"_mvis_MCsubtracted");
    TH1D* compare_t_MCsubtracted_mcup                = (TH1D*)compare_t_MCsubtracted->Clone("compare_t_MCsubtracted_mcup");
    TH1D* compare_t_MCsubtracted_mcdown                = (TH1D*)compare_t_MCsubtracted->Clone("compare_t_MCsubtracted_mcdown");
    compare_t_MCsubtracted_mcup->Scale(1.07);
    compare_t_MCsubtracted_mcdown->Scale(1.0/1.07);

    for (Int_t jentry=0; jentry<nentries;jentry++) {// Fill mvis distribution in closure_h where each event in the loose determination region is 
                                                     // weighted with the measured FF (extracted from the fit) to get its estimate in the tight determination region
                                                     // entries are looping over preselection data file

      event_s->GetEntry(jentry);
      if (DEBUG){ 
        if(jentry % 100000 == 0) {
          cout << jentry << "/" << nentries << endl;
          // if (jentry > 0) {
          //   break;
          // }
        }
      }
      if (mode & SR){ // happens only for TTbar
        if (  this->isInSR(mode,tau_ind) && this->isLoose(mode,tau_ind) ) {
          FF_value = this->getFittedBinContent( mode, fittedFFs );
          closure_h->Fill(event_s->alltau_mvis->at(tau_ind),FF_value*event_s->weight_sf );
        }
      }
      else{ // mode is not SR
        
        if (  this->isInCR(mode,tau_ind) && this->isLoose(mode,tau_ind) ){
          // cout << "FF_value: " << FF_value << endl;
          FF_value = this->getFittedBinContent( mode, fittedFFs );
          closure_h->Fill(event_s->alltau_mvis->at(tau_ind),FF_value*event_s->weight_sf );
        }
      }
    }
    TH1D* closure_h_mcup = (TH1D*)closure_h->Clone("closure_h_mcup");
    TH1D* closure_h_mcdown = (TH1D*)closure_h->Clone("closure_h_mcdown");

    closure_h->Multiply(ratio_l);
    closure_h_mcup->Multiply(ratio_l_mcup);
    closure_h_mcdown->Multiply(ratio_l_mcdown);

    output->cd();
    closure_h->Write();
    closure_h_mcup->Write();
    closure_h_mcdown->Write();

    output_h = (TH1D*)compare_t->Clone("nonclosure");
    output_h_mcup = (TH1D*)compare_t->Clone("nonclosure_mcup");
    output_h_mcdown = (TH1D*)compare_t->Clone("nonclosure_mcdown");

    output_h->Add(compare_t_MCsubtracted,-1);
    output_h_mcup->Add(compare_t_MCsubtracted_mcup,-1);
    output_h_mcdown->Add(compare_t_MCsubtracted_mcdown,-1);

    compare_t->Add(compare_t_MCsubtracted,-1);
    compare_t->Write();
    output_h->Divide(closure_h);
    output_h_mcup->Divide(closure_h_mcup);
    output_h_mcdown->Divide(closure_h_mcdown);
    output_h_mcup->Add(output_h,-1);
    output_h_mcdown->Add(output_h,-1);

  }
  else{ //happens for Wjets non closure correction in case of Simulation based correction 
    TH1D* compare_t              = (TH1D*) compare.Get("hh_t"+tight_cat+"_mvis");
    
    for (Int_t jentry=0; jentry<nentries;jentry++) {
      event_s->GetEntry(jentry);
      if (DEBUG){ if(jentry % 100000 == 0) cout << jentry << "/" << nentries << endl; }
      if (mode & SR){
        if (  this->isInSR(mode,tau_ind) && this->isLoose(mode,tau_ind) ){
          if( !raw_ff.Contains("_fitted") ) FF_value = FF_lookup_h->GetBinContent( this->getBin(mode|tau_ind)+1 );
          else if( raw_ff.Contains("_fitted") ){
            FF_value = this->getFittedBinContent( mode, fittedFFs );
          }
          closure_h->Fill(event_s->alltau_mvis->at(tau_ind),FF_value*event_s->weight_sf );
        }
      }
      else{
        if (  this->isInCR(mode,tau_ind) && this->isLoose(mode,tau_ind) ){
          if( !raw_ff.Contains("_fitted") ) FF_value = FF_lookup_h->GetBinContent( this->getBin(mode|tau_ind)+1 );
          else if( raw_ff.Contains("_fitted") ){
            FF_value = this->getFittedBinContent( mode, fittedFFs );
          }
          closure_h->Fill(event_s->alltau_mvis->at(tau_ind),FF_value*event_s->weight_sf );
        }
      }
    }

    output->cd();
    compare_t->Write();
    closure_h->Write();
  
    output_h = (TH1D*)compare_t->Clone("nonclosure");
    output_h->Divide(closure_h);
  }
  

  TH1D* output_fit;  TH1D* output_fit_mcup;  TH1D* output_fit_mcdown;
  output_fit = (TH1D*)output_h->Clone("nonclosure_fit");
  if(subtractMC){
    output_fit_mcup = (TH1D*)output_h_mcup->Clone("nonclosure_fit_mcup");
    output_fit_mcdown = (TH1D*)output_h_mcdown->Clone("nonclosure_fit_mcdown");
  //   for(int i=1;i<=output_h->GetNbinsX();i++){
  //    if( output_h_mcup->GetBinContent(i) < 0 ) output_h_mcup->SetBinContent(i,-output_h_mcup->GetBinContent(i));
  //    if( output_h_mcdown->GetBinContent(i) < 0 ) output_h_mcdown->SetBinContent(i,-output_h_mcdown->GetBinContent(i));
  // }
  }
  for(int i=1;i<=output_h->GetNbinsX();i++){
    // std::cout << "correction: " << output_h->GetBinContent(i) << std::endl;
    if ( output_h->GetBinContent(i) < 0 ) {
      output_h->SetBinError(i,1.);
      std::cout << "Found negative correction value !" << std::endl;
    } 
  }
  
  output->cd();
  output_fit->Write(); // at this point it is just the ratio of histograms
  if(subtractMC){
    output_fit_mcup->Write();  output_fit_mcdown->Write();
  }
  Double_t fitWidth;
  if(mode & _QCD) fitWidth=1.0; else if(mode & _W_JETS) fitWidth=1.0; else fitWidth=1.0;
  if(CHAN==kTAU) fitWidth=1.0;
  cout << "FitWidth: " << fitWidth << endl;

  // NOMINAL  
  GaussianKernelSmoother gsk;
  gsk.setInputHisto( output_fit );
  gsk.set_doWeights(1);
  gsk.set_doIgnoreZeroBins(0);
  gsk.set_kernelDistance( "lin" );
  gsk.set_doWidthInBins(1);
  gsk.set_doErrors(1);
  //if(mode & _QCD) gsk.set_lastBinFrom(150);
  gsk.setWidth(fitWidth);
  gsk.set_widthInBins_sf(3);
  

  
  gsk.getSmoothHisto();
  TH1D *h2=gsk.returnSmoothedHisto(); //nonclosure_fit_smoothed is returned
  TH1D *h22=gsk.returnWeightHisto(); 
  h2->Write();
  h22->Write();
  
  gsk.set_doErrors(1);
  gsk.getContSmoothHisto();
  TGraphAsymmErrors *g=   gsk.returnSmoothedGraph();
  Double_t x200; Double_t y200;
  if(CHAN==kMU)g->GetPoint(250*4,x200,y200);
  if(CHAN==kEL)g->GetPoint(250*4,x200,y200); // TODO CHANGE (110*4,x200,y200)
  for(int i=0; i<g->GetN(); i++){
    Double_t x; Double_t y;
    if(CHAN==kMU && i>250*4){
      g->GetPoint(i,x,y);
      g->SetPoint(i,x,y200);
    }
    else if(CHAN==kEL && i>250*4){ //CHANGE 110
      g->GetPoint(i,x,y);
      g->SetPoint(i,x,y200);
    }
    
  }
  g->SetTitle("nonclosure"+sample);
  g->SetName("nonclosure"+sample);
  g->Write();
  if(subtractMC){
    // MC UP
    GaussianKernelSmoother gsk_mcup;
    gsk_mcup.setInputHisto( output_fit_mcup );
    gsk_mcup.set_doWeights(1);
    gsk_mcup.set_doIgnoreZeroBins(0);
    gsk_mcup.set_kernelDistance( "lin" );
    gsk_mcup.set_doWidthInBins(1);
    gsk_mcup.set_doErrors(1);
    gsk_mcup.setWidth(fitWidth);
    gsk_mcup.set_widthInBins_sf(1.115);
    
    gsk_mcup.getSmoothHisto();
    TH1D *h2=gsk_mcup.returnSmoothedHisto();
    h2->Write();

    gsk_mcup.set_doErrors(1);
    //gsk_mcup.set_lastBinFrom(185);
    gsk_mcup.getContSmoothHisto();
    TGraphAsymmErrors *g_mcup=   gsk_mcup.returnSmoothedGraph();
    if(CHAN==kMU)g_mcup->GetPoint(250*4,x200,y200);
    if(CHAN==kEL)g_mcup->GetPoint(250*4,x200,y200); // TODO CHANGE (110*4,x200,y200)
    for(int i=0; i<g_mcup->GetN(); i++){
      Double_t x; Double_t y;
      if(CHAN==kMU && i>250*4){
        g_mcup->GetPoint(i,x,y);
        g_mcup->SetPoint(i,x,y200);
      }
      else if(CHAN==kEL && i>250*4){ //CHANGE 110
        g_mcup->GetPoint(i,x,y);
        g_mcup->SetPoint(i,x,y200);
      }
      
    }
    g_mcup->SetTitle("nonclosure_mcup"+sample);
    g_mcup->SetName("nonclosure_mcup"+sample);
    g_mcup->Write();

    // MC DOWN
    GaussianKernelSmoother gsk_mcdown;
    gsk_mcdown.setInputHisto( output_fit_mcdown );
    gsk_mcdown.set_doWeights(1);
    gsk_mcdown.set_doIgnoreZeroBins(0);
    gsk_mcdown.set_kernelDistance( "lin" );
    gsk_mcdown.set_doWidthInBins(1);
    gsk_mcdown.set_doErrors(1);
    gsk_mcdown.setWidth(fitWidth);
    gsk_mcdown.set_widthInBins_sf(1.115);
    
    gsk_mcdown.getSmoothHisto();
    TH1D *h2_mcdown=gsk_mcdown.returnSmoothedHisto();
    h2_mcdown->Write();

    gsk_mcdown.set_doErrors(1);
    //gsk_mcdown.set_lastBinFrom(185);
    gsk_mcdown.getContSmoothHisto();
    TGraphAsymmErrors *g_mcdown=   gsk_mcdown.returnSmoothedGraph();
    if(CHAN==kMU)g_mcdown->GetPoint(250*4,x200,y200);
    if(CHAN==kEL)g_mcdown->GetPoint(250*4,x200,y200); // TODO CHANGE (110*4,x200,y200)
    for(int i=0; i<g_mcdown->GetN(); i++){
      Double_t x; Double_t y;
      if(CHAN==kMU && i>250*4){
        g_mcdown->GetPoint(i,x,y);
        g_mcdown->SetPoint(i,x,y200);
      }
      else if(CHAN==kEL && i>250*4){ //CHANGE 110
        g_mcdown->GetPoint(i,x,y);
        g_mcdown->SetPoint(i,x,y200);
      }
      
    }
    g_mcdown->SetTitle("nonclosure_mcdown"+sample);
    g_mcdown->SetName("nonclosure_mcdown"+sample);
    g_mcdown->Write();
  }
  TGraph *gup = (TGraphAsymmErrors*)g->Clone("nonclosure"+sample+"_up");
  gup->SetTitle("nonclosure"+sample+"_up");
  for(Int_t j=0;j<g->GetN();j++) gup->SetPoint(j,g->GetX()[j],g->GetErrorYhigh(j) );
  gup->Write();
  TGraph *gdown = (TGraphAsymmErrors*)g->Clone("nonclosure"+sample+"_down");
  gdown->SetTitle("nonclosure"+sample+"_down");
  for(Int_t j=0;j<g->GetN();j++) gdown->SetPoint(j,g->GetX()[j],g->GetErrorYlow(j) );
  gdown->Write();
  

  // This down here is not necesaairy probably happens again in plotCorrections.py
  TCanvas *c2=new TCanvas();
  output_h->Draw("E");
  g->Draw("same LP");

  output_h->Draw("E same");
  output_h->SetXTitle("m_{vis}[GeV]");
  output_h->SetTitle("nonclosure m_{vis}");

  output_h->SetYTitle("Ratio");
  output_h->SetMaximum(2.);
  output_h->SetMinimum(0.);
  c2->SetName("nonclosure"+sample+"_c");
  c2->Write();
  // from obove commend to here could be deleted
  
  
  // close everything in RAM
  FF_lookup.Close();output->Close();
  delete closure_h;
  for(int i=0; i<fittedFFs.size();i++){
    delete fittedFFs.at(i);
  }
  
}


void FFCalculator::calc_nonclosure_W_lepPt(const Int_t mode, const TString raw_ff, const TString compare_file, TString ff_output, const TString tight_cat, const Int_t doPlot, const Int_t subtractMC, const Int_t tau_ind){

  cout << "Calculating corrections for " << ff_output << endl;
  cout << "mode: " << mode << endl;
  cout << "raw ff: " << raw_ff << endl;
  cout << "compare_file: " << compare_file << endl;
  cout << "ff_output: " << ff_output << endl;
  cout << "tight_cat: " << tight_cat << endl;
  cout << "subtractMC: " << subtractMC << endl; 
  cout << "tau_ind: " << tau_ind << endl;
  

  Int_t nentries = Int_t(event_s->fChain->GetEntries());
  
  TString cr_file=compare_file;   TString cr_ss_file=compare_file;
  cr_ss_file=cr_ss_file.ReplaceAll("_lepPt","_lepPt_SS");

  if(mode & JET0 ) cr_file = cr_file.ReplaceAll("_data","_0jet_data");
  if(mode & JET1 ) cr_file = cr_file.ReplaceAll("_data","_1jet_data");
  TString sample;
  if(mode & _QCD) sample="_QCD";
  if(mode & _W_JETS) sample="_Wjets";
  if(mode & _TT) sample="_TT";
  if(!subtractMC) sample+="_MC";
  
  TH1D *closure_h;
  if(mode & _TT) closure_h= new TH1D("closure"+sample,"",nbins_lepPt,hist_min_lepPt,hist_max_lepPt);
  else closure_h= new TH1D("closure"+sample,"",w_lepPt_n,w_lepPt_v);
  
  TFile *output = new TFile(ff_output.ReplaceAll(".root",tight_cat+".root"),"RECREATE");
  TH1D *output_h = new TH1D("nonclosure_lepPt","",w_lepPt_n,w_lepPt_v);
  TH1D* output_h_mcup; TH1D* output_h_mcdown;
  
  TFile FF_lookup(raw_ff);
  TH1D* FF_lookup_h = nullptr;
  if( !raw_ff.Contains("_fitted") ) FF_lookup_h = (TH1D*) FF_lookup.Get("c_t"+tight_cat);
  vector<TGraphAsymmErrors*> fittedFFs;
  if( raw_ff.Contains("_fitted") ){
    TGraphAsymmErrors *dm0njet0 = (TGraphAsymmErrors*) FF_lookup.Get("dm0_njet0"+tight_cat); fittedFFs.push_back(dm0njet0);
    TGraphAsymmErrors *dm1njet0 = (TGraphAsymmErrors*) FF_lookup.Get("dm1_njet0"+tight_cat); fittedFFs.push_back(dm1njet0);
    TGraphAsymmErrors *dm0njet1 = (TGraphAsymmErrors*) FF_lookup.Get("dm0_njet1"+tight_cat); fittedFFs.push_back(dm0njet1);
    TGraphAsymmErrors *dm1njet1 = (TGraphAsymmErrors*) FF_lookup.Get("dm1_njet1"+tight_cat); fittedFFs.push_back(dm1njet1);
  }
  
  TFile compare(cr_file);
  TFile compare_qcd(cr_ss_file);

  Double_t FF_value=0;
  if(subtractMC){
    TString ff_inputHist="hh_l"; 
    TH1D* compare_l              = (TH1D*) compare.Get(ff_inputHist+"_lepPt");
    TH1D* compare_l_MCsubtracted = (TH1D*) compare.Get(ff_inputHist+"_lepPt_MCsubtracted");
    TH1D* compare_l_qcd = (TH1D*) compare_qcd.Get("hh_l_lepPt_dataminusMC");
    compare_l_MCsubtracted->Add(compare_l_qcd);
    TH1D* ratio_l                = (TH1D*)compare_l_MCsubtracted->Clone("ratio_l");
    TH1D* ratio_l_mcup                = (TH1D*)compare_l_MCsubtracted->Clone("ratio_l_mcup");
    ratio_l_mcup->Scale(1.07);
    TH1D* ratio_l_mcdown                = (TH1D*)compare_l_MCsubtracted->Clone("ratio_l_mcdown");
    ratio_l_mcdown->Scale(1.0/1.07);
    ratio_l->Divide(compare_l);


    ratio_l_mcup->Divide(compare_l);
    ratio_l_mcdown->Divide(compare_l);
    ///get unity histogram
    TH1D *unity_h = new TH1D("unity","",w_lepPt_n,w_lepPt_v);
    for(int ibin=1; ibin<=unity_h->GetNbinsX(); ibin++) unity_h->SetBinContent(ibin,1.);
    ratio_l->Add(unity_h,-1);ratio_l->Scale(-1);

    ratio_l_mcup->Add(unity_h,-1);ratio_l_mcup->Scale(-1);
    ratio_l_mcdown->Add(unity_h,-1);ratio_l_mcdown->Scale(-1);

    TH1D* compare_t              = (TH1D*) compare.Get("hh_t"+tight_cat+"_lepPt");
    TH1D* compare_t_MCsubtracted = (TH1D*) compare.Get("hh_t"+tight_cat+"_lepPt_MCsubtracted");
    TH1D* compare_t_qcd = (TH1D*) compare_qcd.Get("hh_t_lepPt_dataminusMC");
    compare_t_MCsubtracted->Add(compare_t_qcd);

    TH1D* compare_t_MCsubtracted_mcup                = (TH1D*)compare_t_MCsubtracted->Clone("compare_t_MCsubtracted_mcup");
    TH1D* compare_t_MCsubtracted_mcdown                = (TH1D*)compare_t_MCsubtracted->Clone("compare_t_MCsubtracted_mcdown");
    compare_t_MCsubtracted_mcup->Scale(1.07);
    compare_t_MCsubtracted_mcdown->Scale(1.0/1.07);
    for (Int_t jentry=0; jentry<nentries;jentry++) {
      event_s->GetEntry(jentry);
      if (DEBUG){ if(jentry % 100000 == 0) cout << jentry << "/" << nentries << endl;}
      if (mode & SR){
        if (  this->isInSR(mode,tau_ind) && this->isLoose(mode,tau_ind) ) {
          if( !raw_ff.Contains("_fitted") ) FF_value = FF_lookup_h->GetBinContent( this->getBin(mode|tau_ind)+1 );
          else if( raw_ff.Contains("_fitted") ){
            FF_value = this->getFittedBinContent( mode, fittedFFs );
          }
          closure_h->Fill(event_s->lep_pt,FF_value*event_s->weight_sf );
        }
      }
      else{
        if (  this->isInCR(mode,tau_ind) && this->isLoose(mode,tau_ind) ){
          if( !raw_ff.Contains("_fitted") ) FF_value = FF_lookup_h->GetBinContent( this->getBin(mode|tau_ind)+1 );
          else if( raw_ff.Contains("_fitted") ){            
            FF_value = this->getFittedBinContent( mode, fittedFFs );
          }
          closure_h->Fill(event_s->lep_pt,FF_value*event_s->weight_sf );
        }
      }
    }
       

    TH1D* closure_h_mcup = (TH1D*)closure_h->Clone("closure_h_mcup");
    TH1D* closure_h_mcdown = (TH1D*)closure_h->Clone("closure_h_mcdown");
       

    closure_h->Multiply(ratio_l);
    closure_h_mcup->Multiply(ratio_l_mcup);
    closure_h_mcdown->Multiply(ratio_l_mcdown);
       

    output->cd();
    closure_h->Write();
    closure_h_mcup->Write();
    closure_h_mcdown->Write();
       

    output_h = (TH1D*)compare_t->Clone("nonclosure");
    output_h_mcup = (TH1D*)compare_t->Clone("nonclosure_mcup");
    output_h_mcdown = (TH1D*)compare_t->Clone("nonclosure_mcdown");

    output_h->Add(compare_t_MCsubtracted,-1);
    compare_t->Add(compare_t_MCsubtracted,-1);
    output_h_mcup->Add(compare_t_MCsubtracted_mcup,-1);
    output_h_mcdown->Add(compare_t_MCsubtracted_mcdown,-1);
    compare_t->Write();
    output_h->Divide(closure_h);
    output_h_mcup->Divide(closure_h_mcup);
    output_h_mcdown->Divide(closure_h_mcdown);
    output_h_mcup->Add(output_h,-1);
    output_h_mcdown->Add(output_h,-1);
       

  }
  else{ 
    TH1D* compare_t              = (TH1D*) compare.Get("hh_t"+tight_cat+"_lepPt");
  
    for (Int_t jentry=0; jentry<nentries;jentry++) {
      event_s->GetEntry(jentry);
      if (DEBUG){ if(jentry % 100000 == 0) cout << jentry << "/" << nentries << endl; }
      if (mode & SR){
        if (  this->isInSR(mode,tau_ind) && this->isLoose(mode,tau_ind) ){
          if( !raw_ff.Contains("_fitted") ) FF_value = FF_lookup_h->GetBinContent( this->getBin(mode|tau_ind)+1 );
          else if( raw_ff.Contains("_fitted") ){
            FF_value = this->getFittedBinContent( mode, fittedFFs );
          }
          closure_h->Fill(event_s->lep_pt,FF_value*event_s->weight_sf );
        }
      }
      else{
        if (  this->isInCR(mode,tau_ind) && this->isLoose(mode,tau_ind) ){
          if( !raw_ff.Contains("_fitted") ) FF_value = FF_lookup_h->GetBinContent( this->getBin(mode|tau_ind)+1 );
          else if( raw_ff.Contains("_fitted") ){
            FF_value = this->getFittedBinContent( mode, fittedFFs );
          }
          closure_h->Fill(event_s->lep_pt,FF_value*event_s->weight_sf );
        }
      }
    }
    
    output->cd();
    closure_h->Write();
    compare_t->Write();
  
    output_h = (TH1D*)compare_t->Clone("nonclosure");
    output_h->Divide(closure_h);
  }
      

  TH1D* output_fit;   TH1D* output_fit_mcup;  TH1D* output_fit_mcdown;
  output_fit = (TH1D*)output_h->Clone("nonclosure_fit");
  if(subtractMC){
    output_fit_mcup = (TH1D*)output_h_mcup->Clone("nonclosure_fit_mcup");
    output_fit_mcdown = (TH1D*)output_h_mcdown->Clone("nonclosure_fit_mcdown");
  //   for(int i=1;i<=output_h->GetNbinsX();i++){
  //    if( output_h_mcup->GetBinContent(i) < 0 ) output_h_mcup->SetBinContent(i,-output_h_mcup->GetBinContent(i));
  //    if( output_h_mcdown->GetBinContent(i) < 0 ) output_h_mcdown->SetBinContent(i,-output_h_mcdown->GetBinContent(i));
  // }
  }
  output_fit = (TH1D*)output_h->Clone("nonclosure_fit");

  for(int i=1;i<=output_h->GetNbinsX();i++){
    if( output_h->GetBinContent(i) < 0 ) output_h->SetBinError(i,1.);
  }
  
  output->cd();
  output_fit->Write();
  if(subtractMC){
    output_fit_mcup->Write();  output_fit_mcdown->Write();
  }

  Double_t fitWidth;
  if(mode & _QCD) fitWidth=1.0; else if(mode & _W_JETS) fitWidth=1.0; else fitWidth=1.0;
  if(CHAN==kTAU) fitWidth=1.0;
  cout << "FitWidth: " << fitWidth << endl;

  // NOMINAL  

  GaussianKernelSmoother gsk;
  gsk.setInputHisto( output_fit );
  gsk.set_doWeights(1);
  gsk.set_doIgnoreZeroBins(0);
  gsk.set_kernelDistance( "lin" );
  gsk.set_doWidthInBins(1);
  gsk.set_doErrors(1);
  gsk.setWidth(fitWidth);
  gsk.set_widthInBins_sf(1.);
  
  gsk.getSmoothHisto();
  TH1D *h2=gsk.returnSmoothedHisto();
  h2->Write();

  gsk.set_doErrors(1);
  //gsk.set_lastBinFrom(185);
  gsk.getContSmoothHisto();
  TGraphAsymmErrors *g=   gsk.returnSmoothedGraph();
  g->SetTitle("nonclosure"+sample);
  g->SetName("nonclosure"+sample);
  g->Write();
  if(subtractMC){
    // MC UP
    GaussianKernelSmoother gsk_mcup;
    gsk_mcup.setInputHisto( output_fit_mcup );
    gsk_mcup.set_doWeights(1);
    gsk_mcup.set_doIgnoreZeroBins(0);
    gsk_mcup.set_kernelDistance( "lin" );
    gsk_mcup.set_doWidthInBins(1);
    gsk_mcup.set_doErrors(1);
    gsk_mcup.setWidth(fitWidth);
    gsk_mcup.set_widthInBins_sf(1.);
    
    gsk_mcup.getSmoothHisto();
    TH1D *h2=gsk_mcup.returnSmoothedHisto();
    h2->Write();

    gsk_mcup.set_doErrors(1);
    //gsk_mcup.set_lastBinFrom(185);
    gsk_mcup.getContSmoothHisto();
    TGraphAsymmErrors *g_mcup=   gsk_mcup.returnSmoothedGraph();

    g_mcup->SetTitle("nonclosure_mcup"+sample);
    g_mcup->SetName("nonclosure_mcup"+sample);
    g_mcup->Write();

    // MC DOWN
    GaussianKernelSmoother gsk_mcdown;
    gsk_mcdown.setInputHisto( output_fit_mcdown );
    gsk_mcdown.set_doWeights(1);
    gsk_mcdown.set_doIgnoreZeroBins(0);
    gsk_mcdown.set_kernelDistance( "lin" );
    gsk_mcdown.set_doWidthInBins(1);
    gsk_mcdown.set_doErrors(1);
    gsk_mcdown.setWidth(fitWidth);
    gsk_mcdown.set_widthInBins_sf(1.1);
    
    gsk_mcdown.getSmoothHisto();
    TH1D *h2_mcdown=gsk_mcdown.returnSmoothedHisto();
    h2_mcdown->Write();

    gsk_mcdown.set_doErrors(1);
    //gsk_mcdown.set_lastBinFrom(185);
    gsk_mcdown.getContSmoothHisto();
    TGraphAsymmErrors *g_mcdown=   gsk_mcdown.returnSmoothedGraph();

    g_mcdown->SetTitle("nonclosure_mcdown"+sample);
    g_mcdown->SetName("nonclosure_mcdown"+sample);
    g_mcdown->Write();
  }
  TGraph *gup = (TGraphAsymmErrors*)g->Clone("nonclosure"+sample+"_up");
  gup->SetTitle("nonclosure"+sample+"_up");
  for(Int_t j=0;j<g->GetN();j++) gup->SetPoint(j,g->GetX()[j],g->GetErrorYhigh(j) );
  gup->Write();
  TGraph *gdown = (TGraphAsymmErrors*)g->Clone("nonclosure"+sample+"_down");
  gdown->SetTitle("nonclosure"+sample+"_down");
  for(Int_t j=0;j<g->GetN();j++) gdown->SetPoint(j,g->GetX()[j],g->GetErrorYlow(j) );
  gdown->Write();
  

  TCanvas *c2=new TCanvas();
  output_h->Draw("E");
  g->Draw("same LP");

  output_h->Draw("E same");
  output_h->SetXTitle("m_{vis}[GeV]");
  output_h->SetTitle("nonclosure m_{vis}");

  output_h->SetYTitle("Ratio");
  output_h->SetMaximum(2.);
  output_h->SetMinimum(0.);
  c2->SetName("nonclosure"+sample+"_c");
  c2->Write();
  TString SSstring="";
  if(CALC_SS_SR)SSstring+="_SS_SR";
  if ( doPlot)  c2->SaveAs("ViennaTool/Images/data_"+s_chan[CHAN]+"/nonclosure"+sample+SSstring+tight_cat+".png");

  FF_lookup.Close();output->Close();
  if( raw_ff.Contains("_fitted") ){
    for(int i=0; i<fittedFFs.size();i++){
      delete fittedFFs.at(i);
    }
  }
  
}


void FFCalculator::calc_nonclosure_lepPt(const Int_t mode, const TString raw_ff, const TString compare_file, const TString nonclosure_corr, TString ff_output, const TString tight_cat, const Int_t doPlot, const Int_t subtractMC, const Int_t tau_ind){

  cout << "Calculating corrections for " << ff_output << endl;
  Int_t nentries = Int_t(event_s->fChain->GetEntries());
  cout << nentries << endl;

  TString cr_file=compare_file;
  if(mode & JET0 ) cr_file = cr_file.ReplaceAll("_data","_0jet_data");
  if(mode & JET1 ) cr_file = cr_file.ReplaceAll("_data","_1jet_data");
  TString sample;
  if(mode & _QCD) sample="_QCD";
  if(mode & _W_JETS) sample="_Wjets";
  if(mode & _TT) sample="_TT";
  if(!subtractMC) sample+="_MC";
  
  TH1D *closure_h;
  Double_t FF_value=0;
  if(mode & _TT) closure_h= new TH1D("closure"+sample,"",nbins_lepPt,hist_min_lepPt,hist_max_lepPt);
  else closure_h= new TH1D("closure"+sample,"",w_lepPt_n,w_lepPt_v);
  
  TFile *output = new TFile(ff_output.ReplaceAll(".root",tight_cat+".root"),"RECREATE");
  TH1D *output_h = new TH1D("nonclosure_lepPt","",w_lepPt_n,w_lepPt_v);
  TH1D* output_h_mcup; TH1D* output_h_mcdown;

  TFile FF_lookup(raw_ff);
  TH1D* FF_lookup_h = nullptr;
  if( !raw_ff.Contains("_fitted") ) FF_lookup_h = (TH1D*) FF_lookup.Get("c_t"+tight_cat);
  vector<TGraphAsymmErrors*> fittedFFs;
  if( raw_ff.Contains("_fitted") ){
    TGraphAsymmErrors *dm0njet0 = (TGraphAsymmErrors*) FF_lookup.Get("dm0_njet0"+tight_cat); fittedFFs.push_back(dm0njet0);
    TGraphAsymmErrors *dm1njet0 = (TGraphAsymmErrors*) FF_lookup.Get("dm1_njet0"+tight_cat); fittedFFs.push_back(dm1njet0);
    TGraphAsymmErrors *dm0njet1 = (TGraphAsymmErrors*) FF_lookup.Get("dm0_njet1"+tight_cat); fittedFFs.push_back(dm0njet1);
    TGraphAsymmErrors *dm1njet1 = (TGraphAsymmErrors*) FF_lookup.Get("dm1_njet1"+tight_cat); fittedFFs.push_back(dm1njet1);
    TGraphAsymmErrors *dm0njet2 = (TGraphAsymmErrors*) FF_lookup.Get("dm0_njet2"+tight_cat); fittedFFs.push_back(dm0njet2);
    TGraphAsymmErrors *dm1njet2 = (TGraphAsymmErrors*) FF_lookup.Get("dm1_njet2"+tight_cat); fittedFFs.push_back(dm1njet2);
  }
  TFile nonclosure(nonclosure_corr);
  if(nonclosure.IsZombie()) cout << nonclosure_corr << " does not exist" << endl;
  TH1D* nonclosure_h = (TH1D*) nonclosure.Get("nonclosure_fit_smoothed");
  
  TFile compare(cr_file);
  if(subtractMC){
    TString ff_inputHist="hh_l"; 
    TH1D* compare_l              = (TH1D*) compare.Get(ff_inputHist+"_lepPt");
    TH1D* compare_l_MCsubtracted = (TH1D*) compare.Get(ff_inputHist+"_lepPt_MCsubtracted");
    
    TH1D* ratio_l_mcup                = (TH1D*)compare_l_MCsubtracted->Clone("ratio_l_mcup");
    ratio_l_mcup->Scale(1.07);
    TH1D* ratio_l_mcdown                = (TH1D*)compare_l_MCsubtracted->Clone("ratio_l_mcdown");
    ratio_l_mcdown->Scale(1.0/1.07);
    TH1D* ratio_l                = (TH1D*)compare_l_MCsubtracted->Clone("ratio_l");
  
    ratio_l->Divide(compare_l);
    ratio_l_mcup->Divide(compare_l);
    ratio_l_mcdown->Divide(compare_l);

    ///get unity histogram
    TH1D *unity_h = new TH1D("unity","",w_lepPt_n,w_lepPt_v);
    for(int ibin=1; ibin<=unity_h->GetNbinsX(); ibin++) unity_h->SetBinContent(ibin,1.);
    ratio_l->Add(unity_h,-1);ratio_l->Scale(-1);
    ratio_l_mcup->Add(unity_h,-1);ratio_l_mcup->Scale(-1);
    ratio_l_mcdown->Add(unity_h,-1);ratio_l_mcdown->Scale(-1);

    TH1D* compare_t              = (TH1D*) compare.Get("hh_t"+tight_cat+"_lepPt");
    TH1D* compare_t_MCsubtracted = (TH1D*) compare.Get("hh_t"+tight_cat+"_lepPt_MCsubtracted");
    TH1D* compare_t_MCsubtracted_mcup                = (TH1D*)compare_t_MCsubtracted->Clone("compare_t_MCsubtracted_mcup");
    TH1D* compare_t_MCsubtracted_mcdown                = (TH1D*)compare_t_MCsubtracted->Clone("compare_t_MCsubtracted_mcdown");
    compare_t_MCsubtracted_mcup->Scale(1.07);
    compare_t_MCsubtracted_mcdown->Scale(1.0/1.07);
    for (Int_t jentry=0; jentry<nentries;jentry++) {
      event_s->GetEntry(jentry);
      if (DEBUG){ 
        if(jentry % 100000 == 0) {
          cout << jentry << "/" << nentries << endl; 
        }
      }
      if (mode & SR){
        if (  this->isInSR(mode,tau_ind) && this->isLoose(mode,tau_ind) ){
          if( !raw_ff.Contains("_fitted") ) FF_value = FF_lookup_h->GetBinContent( this->getBin(mode|tau_ind)+1 );
          else if( raw_ff.Contains("_fitted") ){
            FF_value = this->getFittedBinContent( mode, fittedFFs );
          }
          closure_h->Fill(event_s->lep_pt,FF_value*event_s->weight_sf*nonclosure_h->GetBinContent( this->getWeightIndex_mvis(event_s->alltau_mvis->at(tau_ind) )+1 ) );
        } 
      }
      else{
        if (  this->isInCR(mode,tau_ind) && this->isLoose(mode,tau_ind) ){
          if( !raw_ff.Contains("_fitted") ) FF_value = FF_lookup_h->GetBinContent( this->getBin(mode|tau_ind)+1 );
          else if( raw_ff.Contains("_fitted") ){
            FF_value = this->getFittedBinContent( mode, fittedFFs );
          }
          closure_h->Fill(event_s->lep_pt,FF_value*event_s->weight_sf*nonclosure_h->GetBinContent( this->getWeightIndex_mvis(event_s->alltau_mvis->at(tau_ind) )+1 ) );
        } 
      }
    }
    TH1D* closure_h_mcup = (TH1D*)closure_h->Clone("closure_h_mcup");
    TH1D* closure_h_mcdown = (TH1D*)closure_h->Clone("closure_h_mcdown");

    closure_h->Multiply(ratio_l);
    closure_h_mcup->Multiply(ratio_l_mcup);
    closure_h_mcdown->Multiply(ratio_l_mcdown);

    output->cd();
    closure_h->Write();
    closure_h_mcup->Write();
    closure_h_mcdown->Write();

    output_h = (TH1D*)compare_t->Clone("nonclosure");
    output_h_mcup = (TH1D*)compare_t->Clone("nonclosure_mcup");
    output_h_mcdown = (TH1D*)compare_t->Clone("nonclosure_mcdown");

    output_h->Add(compare_t_MCsubtracted,-1);
    output_h_mcup->Add(compare_t_MCsubtracted_mcup,-1);
    output_h_mcdown->Add(compare_t_MCsubtracted_mcdown,-1);

    compare_t->Add(compare_t_MCsubtracted,-1);
    compare_t->Write();
    output_h->Divide(closure_h);
    output_h_mcup->Divide(closure_h_mcup);
    output_h_mcdown->Divide(closure_h_mcdown);
    output_h_mcup->Add(output_h,-1);
    output_h_mcdown->Add(output_h,-1);
  }
  else{ 
    TH1D* compare_t              = (TH1D*) compare.Get("hh_t"+tight_cat+"_lepPt");
  
    for (Int_t jentry=0; jentry<nentries;jentry++) {
      event_s->GetEntry(jentry);
      if (DEBUG){ if(jentry % 100000 == 0) cout << jentry << "/" << nentries << endl; }
      if (mode & SR){
        if (  this->isInSR(mode,tau_ind) && this->isLoose(mode,tau_ind) ){
          if( !raw_ff.Contains("_fitted") ) FF_value = FF_lookup_h->GetBinContent( this->getBin(mode|tau_ind)+1 );
          else if( raw_ff.Contains("_fitted") ){
            FF_value = this->getFittedBinContent( mode, fittedFFs );
          }
          closure_h->Fill(event_s->lep_pt,FF_value*event_s->weight_sf );
        } 
      }
      else{
        if (  this->isInCR(mode,tau_ind) && this->isLoose(mode,tau_ind) ){
          if( !raw_ff.Contains("_fitted") ) FF_value = FF_lookup_h->GetBinContent( this->getBin(mode|tau_ind)+1 );
          else if( raw_ff.Contains("_fitted") ){
            FF_value = this->getFittedBinContent( mode, fittedFFs );
          }
          closure_h->Fill(event_s->lep_pt,FF_value*event_s->weight_sf );
        } 
      }
    }
    
    output->cd();
    closure_h->Write();
  
    output_h = (TH1D*)compare_t->Clone("nonclosure");
    output_h->Divide(closure_h);
  }

  TH1D* output_fit;  TH1D* output_fit_mcup;  TH1D* output_fit_mcdown;
  output_fit = (TH1D*)output_h->Clone("nonclosure_fit");
  if(subtractMC){
    output_fit_mcup = (TH1D*)output_h_mcup->Clone("nonclosure_fit_mcup");
    output_fit_mcdown = (TH1D*)output_h_mcdown->Clone("nonclosure_fit_mcdown");
  //   for(int i=1;i<=output_h->GetNbinsX();i++){
  //    if( output_h_mcup->GetBinContent(i) < 0 ) output_h_mcup->SetBinContent(i,-output_h_mcup->GetBinContent(i));
  //    if( output_h_mcdown->GetBinContent(i) < 0 ) output_h_mcdown->SetBinContent(i,-output_h_mcdown->GetBinContent(i));
  }
  for(int i=1;i<=output_h->GetNbinsX();i++){
    if( output_h->GetBinContent(i) < 0 ) output_h->SetBinError(i,1.);
  }

  output->cd();
  output_fit->Write();
  if(subtractMC){
    output_fit_mcup->Write();  output_fit_mcdown->Write();
  }
  
  Double_t fitWidth;
  if(mode & _QCD) fitWidth=1.0; else if(mode & _W_JETS) fitWidth=1.0; else fitWidth=1.0;
  if(CHAN==kTAU) fitWidth=0.7;
  cout << "FitWidth: " << fitWidth << endl;

  //NOMINAL
  GaussianKernelSmoother gsk;
  gsk.setInputHisto( output_fit );
  gsk.set_doWeights(1);
  gsk.set_doIgnoreZeroBins(0);
  gsk.set_kernelDistance( "lin" );
  gsk.set_doWidthInBins(1);
  gsk.set_doErrors(1);

  gsk.setWidth(fitWidth);
  gsk.set_widthInBins_sf(1.);
  gsk.getSmoothHisto();
  TH1D *h2=gsk.returnSmoothedHisto();
  h2->Write();

  gsk.set_doErrors(1);
  gsk.getContSmoothHisto();
  TGraphAsymmErrors *g=   gsk.returnSmoothedGraph();
  g->SetTitle("nonclosure"+sample);
  g->SetName("nonclosure"+sample);
  g->Write();

  //UP
  GaussianKernelSmoother gsk_mcup;
  gsk_mcup.setInputHisto( output_fit_mcup );
  gsk_mcup.set_doWeights(1);
  gsk_mcup.set_doIgnoreZeroBins(0);
  gsk_mcup.set_kernelDistance( "lin" );
  gsk_mcup.set_doWidthInBins(1);
  gsk_mcup.set_doErrors(1);

  gsk_mcup.setWidth(fitWidth);
  gsk_mcup.set_widthInBins_sf(1.);
  gsk_mcup.getSmoothHisto();
  TH1D *h2_mcup=gsk_mcup.returnSmoothedHisto();
  h2_mcup->Write();

  gsk_mcup.set_doErrors(1);
  gsk_mcup.getContSmoothHisto();
  TGraphAsymmErrors *g_mcup=   gsk_mcup.returnSmoothedGraph();
  g_mcup->SetTitle("nonclosure_mcup"+sample);
  g_mcup->SetName("nonclosure_mcup"+sample);
  g_mcup->Write();

  //DOWN
  GaussianKernelSmoother gsk_mcdown;
  gsk_mcdown.setInputHisto( output_fit_mcdown );
  gsk_mcdown.set_doWeights(1);
  gsk_mcdown.set_doIgnoreZeroBins(0);
  gsk_mcdown.set_kernelDistance( "lin" );
  gsk_mcdown.set_doWidthInBins(1);
  gsk_mcdown.set_doErrors(1);

  gsk_mcdown.setWidth(fitWidth);
  gsk_mcdown.set_widthInBins_sf(1.);
  gsk_mcdown.getSmoothHisto();
  TH1D *h2_mcdown=gsk_mcdown.returnSmoothedHisto();
  h2_mcdown->Write();

  gsk_mcdown.set_doErrors(1);
  gsk_mcdown.getContSmoothHisto();
  TGraphAsymmErrors *g_mcdown=   gsk_mcdown.returnSmoothedGraph();
  g_mcdown->SetTitle("nonclosure_mcdown"+sample);
  g_mcdown->SetName("nonclosure_mcdown"+sample);
  g_mcdown->Write();

  TGraph *gup = (TGraphAsymmErrors*)g->Clone("nonclosure"+sample+"_up");
  gup->SetTitle("nonclosure"+sample+"_up");
  for(Int_t j=0;j<g->GetN();j++) gup->SetPoint(j,g->GetX()[j],g->GetErrorYhigh(j) );
  gup->Write();
  TGraph *gdown = (TGraphAsymmErrors*)g->Clone("nonclosure"+sample+"_down");
  gdown->SetTitle("nonclosure"+sample+"_down");
  for(Int_t j=0;j<g->GetN();j++) gdown->SetPoint(j,g->GetX()[j],g->GetErrorYlow(j) );
  gdown->Write();
  

  TCanvas *c2=new TCanvas();
  output_h->Draw("E");
  g->Draw("same LP");
  
  output_h->Draw("E same");
  output_h->SetXTitle("p_T [GeV]");
  output_h->SetTitle("nonclosure p_T");
  //output_h->SetXTitle("Z_{p}^{T}[GeV]");
  output_h->SetYTitle("Ratio");
  output_h->SetMaximum(2.);
  output_h->SetMinimum(0.);
  c2->SetName("nonclosure_pt"+sample+"_c");
  c2->Write();
  TString SSstring="";
  if(CALC_SS_SR)SSstring+="_SS_SR";
  if ( doPlot)  c2->SaveAs("ViennaTool/Images/data_"+s_chan[CHAN]+"/nonclosure_pt"+sample+SSstring+tight_cat+".png");
  
  FF_lookup.Close();output->Close();
  if( raw_ff.Contains("_fitted") ){
    for(int i=0; i<fittedFFs.size();i++){
      delete fittedFFs.at(i);
    }
  }
  
}

void FFCalculator::calc_muisocorr(const Int_t mode, const TString raw_ff, const TString CR_file, TString nonclosure_corr, TString ff_output, const TString tight_cat, const Int_t doPlot, const Int_t subtractMC, const Int_t tau_ind){

  cout << "Calculating corrections for " << ff_output << endl;
  Int_t nentries = Int_t(event_s->fChain->GetEntries());
  cout << nentries << endl;
  TFile *output = new TFile(ff_output.ReplaceAll(".root",tight_cat+".root"),"RECREATE");
  TH1D *output_h = new TH1D("muiso_corr","",w_muiso_n,w_muiso_v);
  TH1D *closure_h = new TH1D("closure","",w_muiso_n,w_muiso_v);
  TH1D* output_h_mcup; TH1D* output_h_mcdown;

  TString compare_file=CR_file;
  if(mode & JET0 ) compare_file = compare_file.ReplaceAll("_data","_0jet_data");
  if(mode & JET1 ) compare_file = compare_file.ReplaceAll("_data","_1jet_data");
  TFile FF_lookup(raw_ff);
  if(FF_lookup.IsZombie()) cout << raw_ff << " does not exist" << endl;
  TH1D* FF_lookup_h = nullptr;
  if( !raw_ff.Contains("_fitted") ) FF_lookup_h = (TH1D*) FF_lookup.Get("c_t"+tight_cat);
  vector<TGraphAsymmErrors*> fittedFFs;
  if( raw_ff.Contains("_fitted") ){
    TGraphAsymmErrors *dm0njet0 = (TGraphAsymmErrors*) FF_lookup.Get("dm0_njet0"+tight_cat); fittedFFs.push_back(dm0njet0);
    TGraphAsymmErrors *dm1njet0 = (TGraphAsymmErrors*) FF_lookup.Get("dm1_njet0"+tight_cat); fittedFFs.push_back(dm1njet0);
    TGraphAsymmErrors *dm0njet1 = (TGraphAsymmErrors*) FF_lookup.Get("dm0_njet1"+tight_cat); fittedFFs.push_back(dm0njet1);
    TGraphAsymmErrors *dm1njet1 = (TGraphAsymmErrors*) FF_lookup.Get("dm1_njet1"+tight_cat); fittedFFs.push_back(dm1njet1);
    TGraphAsymmErrors *dm0njet2 = (TGraphAsymmErrors*) FF_lookup.Get("dm0_njet2"+tight_cat); fittedFFs.push_back(dm0njet2);
    TGraphAsymmErrors *dm1njet2 = (TGraphAsymmErrors*) FF_lookup.Get("dm1_njet2"+tight_cat); fittedFFs.push_back(dm1njet2);
  }
  TFile nonclosure(nonclosure_corr.ReplaceAll(".root",tight_cat+".root"));
  if(nonclosure.IsZombie()) cout << nonclosure_corr << " does not exist" << endl;
  TH1D* nonclosure_h = (TH1D*) nonclosure.Get("nonclosure_fit_smoothed");
  
  TFile compare(compare_file);
  Double_t FF_value=0;
  if(compare.IsZombie()) cout << compare_file << " does not exit" << endl;
  if(subtractMC){
    TH1D* compare_l              = (TH1D*) compare.Get("hh_l_muiso");
    TH1D* compare_l_MCsubtracted = (TH1D*) compare.Get("hh_l_muiso_MCsubtracted");
    TH1D* ratio_l                = (TH1D*)compare_l_MCsubtracted->Clone("ratio_l");
    TH1D* ratio_l_mcup                = (TH1D*)compare_l_MCsubtracted->Clone("ratio_l_mcup");
    ratio_l_mcup->Scale(1.07);
    TH1D* ratio_l_mcdown                = (TH1D*)compare_l_MCsubtracted->Clone("ratio_l_mcdown");
    ratio_l_mcdown->Scale(1.0/1.07);    
    ratio_l->Divide(compare_l);
    ratio_l_mcup->Divide(compare_l);
    ratio_l_mcdown->Divide(compare_l);
    //get unity histogram
    TH1D *unity_h = new TH1D("unity","",w_muiso_n,w_muiso_v);
    for(int ibin=1; ibin<=unity_h->GetNbinsX(); ibin++) unity_h->SetBinContent(ibin,1.);
    ratio_l->Add(unity_h,-1);ratio_l->Scale(-1);
    ratio_l_mcup->Add(unity_h,-1);ratio_l_mcup->Scale(-1);
    ratio_l_mcdown->Add(unity_h,-1);ratio_l_mcdown->Scale(-1);
    TH1D* compare_t              = (TH1D*) compare.Get("hh_t"+tight_cat+"_muiso");
    TH1D* compare_t_MCsubtracted = (TH1D*) compare.Get("hh_t"+tight_cat+"_muiso_MCsubtracted");
    TH1D* compare_t_MCsubtracted_mcup                = (TH1D*)compare_t_MCsubtracted->Clone("compare_t_MCsubtracted_mcup");
    TH1D* compare_t_MCsubtracted_mcdown                = (TH1D*)compare_t_MCsubtracted->Clone("compare_t_MCsubtracted_mcdown");
    compare_t_MCsubtracted_mcup->Scale(1.07);
    compare_t_MCsubtracted_mcdown->Scale(1.0/1.07);
    for (Int_t jentry=0; jentry<nentries;jentry++) {
      event_s->GetEntry(jentry);
      if (DEBUG){ if(jentry % 100000 == 0) cout << jentry << "/" << nentries << endl; }
      if (  this->isInCR(mode,tau_ind) && this->isLoose(mode,tau_ind) ){
        if( !raw_ff.Contains("_fitted") ) FF_value = FF_lookup_h->GetBinContent( this->getBin(mode|tau_ind)+1 );
        else if( raw_ff.Contains("_fitted") ){
          FF_value = this->getFittedBinContent( mode, fittedFFs );
        }
        closure_h->Fill(event_s->lep_iso,event_s->weight_sf*FF_value*nonclosure_h->GetBinContent( this->getWeightIndex_mvis(event_s->alltau_mvis->at(tau_ind) )+1 ) );
      } 
    }
    
    TH1D* closure_h_mcup = (TH1D*)closure_h->Clone("closure_h_mcup");
    TH1D* closure_h_mcdown = (TH1D*)closure_h->Clone("closure_h_mcdown");

    closure_h->Multiply(ratio_l);
    closure_h_mcup->Multiply(ratio_l_mcup);
    closure_h_mcdown->Multiply(ratio_l_mcdown);

    output->cd();
    closure_h->Write();
    closure_h_mcup->Write();
    closure_h_mcdown->Write();

    output_h = (TH1D*)compare_t->Clone("nonclosure");
    output_h_mcup = (TH1D*)compare_t->Clone("nonclosure_mcup");
    output_h_mcdown = (TH1D*)compare_t->Clone("nonclosure_mcdown");

    output_h->Add(compare_t_MCsubtracted,-1);
    output_h_mcup->Add(compare_t_MCsubtracted_mcup,-1);
    output_h_mcdown->Add(compare_t_MCsubtracted_mcdown,-1);

    compare_t->Add(compare_t_MCsubtracted,-1);
    compare_t->Write();
    output_h->Divide(closure_h);
    output_h_mcup->Divide(closure_h_mcup);
    output_h_mcdown->Divide(closure_h_mcdown);
    output_h_mcup->Add(output_h,-1);
    output_h_mcdown->Add(output_h,-1);
  }
  else{
    TH1D* compare_t              = (TH1D*) compare.Get("hh_t"+tight_cat+"_muiso");
    for (Int_t jentry=0; jentry<nentries;jentry++) {
      event_s->GetEntry(jentry);
      if (DEBUG){ if(jentry % 100000 == 0) cout << jentry << "/" << nentries << endl; }
      if (  this->isInCR(mode,tau_ind) && this->isLoose(mode,tau_ind) ){
        if( !raw_ff.Contains("_fitted") ) FF_value = FF_lookup_h->GetBinContent( this->getBin(mode|tau_ind)+1 );
        else if( raw_ff.Contains("_fitted") ){
          FF_value = this->getFittedBinContent( mode, fittedFFs );
        }
        closure_h->Fill(event_s->lep_iso,event_s->weight_sf*FF_value*nonclosure_h->GetBinContent( this->getWeightIndex_mvis(event_s->alltau_mvis->at(tau_ind) )+1 ) );
      } 
    }
    
    output->cd();
    closure_h->Write();
  
    output_h = (TH1D*)compare_t->Clone("muiso_corr");
    output_h->Divide(closure_h);
  }
    
  output->cd();
  output_h->Write();

  TString sample;
  if(mode & _QCD) sample="_QCD";
  if(mode & _W_JETS) sample="_Wjets";
  Double_t fitWidth;
  if(!CALC_SS_SR) fitWidth=1.; else fitWidth=0.5;
  cout << "FitWidth: " << fitWidth << endl;

  //NOMINAL
  GaussianKernelSmoother gsk;
  gsk.setInputHisto( output_h );
  gsk.set_doWeights(1);
  gsk.set_doIgnoreZeroBins(1);
  //gsk.set_kernelDistance( "err" );
  gsk.set_doWidthInBins(1);
  gsk.set_doErrors(1);

  gsk.setWidth(fitWidth);
  gsk.getSmoothHisto();
  TH1D *h2=gsk.returnSmoothedHisto();
  h2->Write();

  gsk.set_doErrors(1);
  gsk.getContSmoothHisto();
  TGraphAsymmErrors *g=   gsk.returnSmoothedGraph();
  g->SetTitle("muiso"+sample);
  g->SetName("muiso"+sample);
  g->Write();

  //UP
  GaussianKernelSmoother gsk_mcup;
  gsk_mcup.setInputHisto( output_h_mcup );
  gsk_mcup.set_doWeights(1);
  gsk_mcup.set_doIgnoreZeroBins(1);
  //gsk_mcup.set_kernelDistance( "err" );
  gsk_mcup.set_doWidthInBins(1);
  gsk_mcup.set_doErrors(1);
  gsk_mcup.setWidth(fitWidth);
  gsk_mcup.getSmoothHisto();
  TH1D *h2_mcup=gsk_mcup.returnSmoothedHisto();
  h2_mcup->Write();

  gsk_mcup.set_doErrors(1);
  gsk_mcup.getContSmoothHisto();
  TGraphAsymmErrors *g_mcup=   gsk_mcup.returnSmoothedGraph();
  g_mcup->SetTitle("muiso_mcup"+sample);
  g_mcup->SetName("muiso_mcup"+sample);
  g_mcup->Write();

  //UP
  GaussianKernelSmoother gsk_mcdown;
  gsk_mcdown.setInputHisto( output_h_mcdown );
  gsk_mcdown.set_doWeights(1);
  gsk_mcdown.set_doIgnoreZeroBins(1);
  //gsk_mcdown.set_kernelDistance( "err" );
  gsk_mcdown.set_doWidthInBins(1);
  gsk_mcdown.set_doErrors(1);
  gsk_mcdown.setWidth(fitWidth);
  gsk_mcdown.getSmoothHisto();
  TH1D *h2_mcdown=gsk_mcdown.returnSmoothedHisto();
  h2_mcdown->Write();

  gsk_mcdown.set_doErrors(1);
  gsk_mcdown.getContSmoothHisto();
  TGraphAsymmErrors *g_mcdown=   gsk_mcdown.returnSmoothedGraph();
  g_mcdown->SetTitle("muiso_mcdown"+sample);
  g_mcdown->SetName("muiso_mcdown"+sample);
  g_mcdown->Write();

  TGraph *gup = (TGraphAsymmErrors*)g->Clone("muiso_corr"+sample+"_up");
  gup->SetTitle("muiso_corr"+sample+"_up");
  for(Int_t j=0;j<g->GetN();j++) gup->SetPoint(j,g->GetX()[j],g->GetErrorYhigh(j) );
  gup->Write();
  TGraph *gdown = (TGraphAsymmErrors*)g->Clone("muiso_corr"+sample+"_down");
  gdown->SetTitle("muiso_corr"+sample+"_down");
  for(Int_t j=0;j<g->GetN();j++) gdown->SetPoint(j,g->GetX()[j],g->GetErrorYlow(j) );
  gdown->Write();
  

  TCanvas *c2=new TCanvas();
  output_h->Draw("E");
  g->Draw("same LP");
  output_h->Draw("E same");
  output_h->SetTitle("iso(#mu) correction");
  output_h->SetXTitle("iso(#mu)");
  output_h->SetYTitle("Ratio");
  output_h->SetMaximum(2.);
  output_h->SetMinimum(0.55);
  c2->SetName("muiso_corr"+sample+"_c");
  c2->Write();
  if(doPlot){
    if(!CALC_SS_SR) c2->SaveAs("ViennaTool/Images/data_"+s_chan[CHAN]+"/muisocorr"+sample+tight_cat+".png");
    if(CALC_SS_SR) c2->SaveAs("ViennaTool/Images/data_"+s_chan[CHAN]+"/muisocorr"+sample+tight_cat+"_SS_SR.png");
  }
  
  FF_lookup.Close();compare.Close();nonclosure.Close();output->Close();
  if( raw_ff.Contains("_fitted") ){
    for(int i=0; i<fittedFFs.size();i++){
      delete fittedFFs.at(i);
    }
  }
  
}

void FFCalculator::calc_OSSScorr(const Int_t mode, const TString raw_ff, const TString SR_file_AI, TString nonclosure_corr, TString ff_output, const TString tight_cat, const Int_t doPlot, const Int_t subtractMC, const Int_t tau_ind){

  cout << "Calculating corrections for " << ff_output << endl;
  cout << "mode: " << mode << endl;
  cout << "raw ff: " << raw_ff << endl; // contains dm0_njet0 dm0_njet1 of type TGrapAsymmeErrors
  cout << "SR_file_AI: " << SR_file_AI << endl; // contains hh_(l or t)_mvis
  cout << "nonclosure_corr: " << nonclosure_corr << endl; 
  cout << "ff_output: " << ff_output << endl;
  cout << "tight_cat: " << tight_cat << endl; // always "" since not doing alt anymore
  cout << "doPlot: " << doPlot << endl; // 
  cout << "subtractMC: " << subtractMC << endl; // is probably always 1 (default) 
  cout << "tau_ind: " << tau_ind << endl;

  
  Int_t nentries = Int_t(event_s->fChain->GetEntries());
  
  TFile *output = new TFile(ff_output.ReplaceAll(".root",tight_cat+".root"),"RECREATE");  
  TH1D *output_h = new TH1D("OSSS_corr","",w_mvis_n,w_mvis_v);
  TH1D *closure_h = new TH1D("closure","",w_mvis_n,w_mvis_v);
  
  if (CHAN == kEL || CHAN == kMU) {   //rebin for better statistics in et and mt channel
    output_h->Rebin(2);
    closure_h->Rebin(2);
  }
  Double_t FF_value=0;
  
  TFile compare(SR_file_AI);
  if(compare.IsZombie()) cout << SR_file_AI << " does not exist" << endl;
  TFile FF_lookup(raw_ff);
  if(FF_lookup.IsZombie()) cout << raw_ff << " does not exist" << endl;
  TH1D* FF_lookup_h = nullptr;
  
  vector<TGraphAsymmErrors*> fittedFFs;
  TGraphAsymmErrors *dm0njet0 = (TGraphAsymmErrors*) FF_lookup.Get("dm0_njet0"+tight_cat); fittedFFs.push_back(dm0njet0);
  TGraphAsymmErrors *dm1njet0 = (TGraphAsymmErrors*) FF_lookup.Get("dm1_njet0"+tight_cat); fittedFFs.push_back(dm1njet0);
  TGraphAsymmErrors *dm0njet1 = (TGraphAsymmErrors*) FF_lookup.Get("dm0_njet1"+tight_cat); fittedFFs.push_back(dm0njet1);
  TGraphAsymmErrors *dm1njet1 = (TGraphAsymmErrors*) FF_lookup.Get("dm1_njet1"+tight_cat); fittedFFs.push_back(dm1njet1);
  if (mode & _QCD) { // ToDo: for more jet categories
    TGraphAsymmErrors *dm0njet2 = (TGraphAsymmErrors*) FF_lookup.Get("dm0_njet2"+tight_cat); fittedFFs.push_back(dm0njet2);
    TGraphAsymmErrors *dm1njet2 = (TGraphAsymmErrors*) FF_lookup.Get("dm1_njet2"+tight_cat); fittedFFs.push_back(dm1njet2);
  }

  TFile nonclosure(nonclosure_corr.ReplaceAll(".root",tight_cat+".root"));
  if(nonclosure.IsZombie()) cout << nonclosure_corr << " does not exist" << endl;
  TH1D* nonclosure_h = (TH1D*) nonclosure.Get("nonclosure_fit_smoothed");
  std::cout << "nonclosure_h: " << nonclosure_h << std::endl; // this is a histogram filled with zeros!?
  if(subtractMC){
    TString ff_inputHist="hh_l";
    TH1D* compare_l              = (TH1D*) compare.Get(ff_inputHist+"_mvis");
    TH1D* compare_l_MCsubtracted = (TH1D*) compare.Get(ff_inputHist+"_mvis_MCsubtracted");
    TH1D* compare_l_dataminusMC = (TH1D*) compare.Get(ff_inputHist+"_mvis_dataminusMC");
    if (CHAN == kEL || CHAN == kMU) { //rebin for better statistics in et and mt channel
      compare_l->Rebin(2);          
      compare_l_MCsubtracted->Rebin(2);
      compare_l_dataminusMC->Rebin(2); 
    }
    
    TH1D* ratio_l                = (TH1D*)compare_l_dataminusMC->Clone("ratio_l");
    ratio_l->Divide(compare_l);
    
    TH1D* compare_t              = (TH1D*) compare.Get("hh_t"+tight_cat+"_mvis");
    TH1D* compare_t_MCsubtracted = (TH1D*) compare.Get("hh_t"+tight_cat+"_mvis_MCsubtracted");
    TH1D* compare_t_dataminusMC = (TH1D*) compare.Get("hh_t"+tight_cat+"_mvis_dataminusMC");
    if (CHAN == kEL || CHAN == kMU) { //rebin for better statistics in et and mt channel
      compare_t->Rebin(2);          
      compare_t_MCsubtracted->Rebin(2);
      compare_t_dataminusMC->Rebin(2); 
    }
    TH1D* ratio_t                = (TH1D*)compare_t_dataminusMC->Clone("ratio_t");
    ratio_t->Divide(compare_t);
    
    
    for (Int_t jentry=0; jentry<nentries;jentry++) {
      event_s->GetEntry(jentry);
      if (DEBUG){ 
        if(jentry % 100000 == 0) {
          cout << jentry << "/" << nentries << endl; 
          // if (jentry > 0) {break;}
        }
        
      }
      if (  this->isInSR(mode,tau_ind) && this->isLoose(mode,tau_ind) ){
        FF_value = this->getFittedBinContent( mode, fittedFFs );
        closure_h->Fill(event_s->alltau_mvis->at(tau_ind),event_s->weight_sf*FF_value*nonclosure_h->GetBinContent( this->getWeightIndex_mvis(event_s->alltau_mvis->at(tau_ind) )+1 ) );
        
      } 
    }
    // exit(0);
    
    closure_h->Multiply(ratio_l);
    output->cd();
    ratio_l->Write();
    ratio_t->Write();
    compare_t_dataminusMC->Write();
    compare_t_MCsubtracted->Write();
    compare_t->Write();
    closure_h->Write();
    
    output_h = (TH1D*)compare_t->Clone("OSSS_corr");
    output_h->Add(compare_t_MCsubtracted,-1);
    output_h->Divide(closure_h);
    
    for(int i=1;i<=output_h->GetNbinsX();i++){
      if( output_h->GetBinContent(i) < 0 ) output_h->SetBinError(i,1.);
    }
  }
  else{
    TH1D* compare_t              = (TH1D*) compare.Get("hh_t"+tight_cat+"_mvis");
    for (Int_t jentry=0; jentry<nentries;jentry++) {
      event_s->GetEntry(jentry);
      if (DEBUG){ if(jentry % 100000 == 0) cout << jentry << "/" << nentries << endl; }
      if (  this->isInSR(mode,tau_ind) && this->isLoose(mode,tau_ind) ){
        if( !raw_ff.Contains("_fitted") ) FF_value = FF_lookup_h->GetBinContent( this->getBin(mode|tau_ind)+1 );
        else if( raw_ff.Contains("_fitted") ){
          FF_value = this->getFittedBinContent( mode, fittedFFs );
        }
        closure_h->Fill(event_s->alltau_mvis->at(tau_ind),event_s->weight_sf*FF_value*nonclosure_h->GetBinContent( this->getWeightIndex_mvis(event_s->alltau_mvis->at(tau_ind) )+1 ) );
      } 
    }
    
    output->cd();
    
    closure_h->Write();
  
    output_h = (TH1D*)compare_t->Clone("OSSS_corr");
    output_h->Divide(closure_h);
    
  }
  
  output->cd();
  output_h->Write();
  
  TString sample;
  if(mode & _QCD) sample="_QCD";
  if(mode & _W_JETS) sample="_Wjets";
  
  GaussianKernelSmoother gsk;
  int ret=gsk.setInputHisto( output_h );
  if ( ret != 0 ) return;
  gsk.set_doWeights(1);
  gsk.set_doIgnoreZeroBins(1);
  gsk.set_kernelDistance( "lin" );
  gsk.set_doWidthInBins(1);
  gsk.set_doErrors(1);
  gsk.setWidth( 2. );
  if(CHAN ==kTAU ) gsk.setWidth(0.7);
  if(CHAN ==kTAU ) gsk.set_widthInBins_sf(0.2);
  else gsk.set_widthInBins_sf(1.115);
  //if(mode & _QCD) gsk.set_lastBinFrom(170);
  gsk.getSmoothHisto();
  TH1D *h2=gsk.returnSmoothedHisto();
  h2->Write();

  gsk.set_doErrors(1);
  //if(CHAN==kMU)gsk.set_lastBinFrom(180);
  //if(CHAN==kEL)gsk.set_lastBinFrom(110);
  gsk.getContSmoothHisto();
  TGraphAsymmErrors *g=   gsk.returnSmoothedGraph();

  Double_t x200; Double_t y200;
  if(CHAN==kMU)g->GetPoint(200*4,x200,y200);
  if(CHAN==kEL)g->GetPoint(190*4,x200,y200); // TODO CHANGE (110*4,x200,y200)
  for(int i=0; i<g->GetN(); i++){
    Double_t x; Double_t y;
    if(CHAN==kMU && i>200*4){
      g->GetPoint(i,x,y);
      g->SetPoint(i,x,y200);
    }
    else if(CHAN==kEL && i>190*4){ //CHANGE 110
      g->GetPoint(i,x,y);
      g->SetPoint(i,x,y200);
    }
    
  }
    
  g->SetTitle("OSSS_corr"+sample);
  g->SetName("OSSS_corr"+sample);
  g->Write();

  TGraph *gup = (TGraphAsymmErrors*)g->Clone("OSSS_corr"+sample+"_up");
  gup->SetTitle("OSSS_corr"+sample+"_up");
  for(Int_t j=0;j<g->GetN();j++) gup->SetPoint(j,g->GetX()[j],g->GetErrorYhigh(j) );
  gup->Write();
  TGraph *gdown = (TGraphAsymmErrors*)g->Clone("OSSS_corr"+sample+"_down");
  gdown->SetTitle("OSSS_corr"+sample+"_down");
  for(Int_t j=0;j<g->GetN();j++) gdown->SetPoint(j,g->GetX()[j],g->GetErrorYlow(j) );
  gdown->Write();
  

  TCanvas *c2=new TCanvas();
  output_h->Draw("E");
  g->Draw("same LP");
  output_h->Draw("E same");
  output_h->SetTitle("OS/SS ratio");
  output_h->SetXTitle("m_{vis}[GeV]");
  output_h->SetYTitle("Ratio");
  output_h->SetMaximum(2.);
  output_h->SetMinimum(0.);
  c2->SetName("OSSS_corr"+sample+"_c");
  c2->Write();
  if(doPlot)c2->SaveAs("ViennaTool/Images/data_"+s_chan[CHAN]+"/OSSScorr"+sample+tight_cat+".png");

  FF_lookup.Close();compare.Close();nonclosure.Close();output->Close();
  if( raw_ff.Contains("_fitted") ){
    for(int i=0; i<fittedFFs.size();i++){
      delete fittedFFs.at(i);
    }
  }
}


void FFCalculator::calc_mtcorr(const Int_t mode, const TString raw_ff, const TString CR_file, TString nonclosure_corr, TString ff_output, const TString tight_cat, const Int_t doPlot, const Int_t tau_ind){

  cout << "Calculating corrections for " << ff_output << endl;
  cout << "nonclosure_corr: " << nonclosure_corr << endl;
  Int_t nentries = Int_t(event_s->fChain->GetEntries());
  cout << nentries << endl;
  TFile *output = new TFile(ff_output.ReplaceAll(".root",tight_cat+".root"),"RECREATE");
  
  TString compare_file=CR_file;
  if(mode & JET0 ) compare_file = compare_file.ReplaceAll("mt_Wjets","mt_0jet_Wjets");
  if(mode & JET1 ) compare_file = compare_file.ReplaceAll("mt_Wjets","mt_1jet_Wjets");
  TH1D *output_h = new TH1D("mt_corr","",w_mvis_n,w_mvis_v);
  TH1D *closure_h = new TH1D("closure","",w_mvis_n,w_mvis_v);
  Double_t FF_value=0;
  TFile compare(compare_file);
  TH1D* compare_t              = (TH1D*) compare.Get("hh_t"+tight_cat+"_mvis");
  TFile FF_lookup(raw_ff);
  TH1D* FF_lookup_h = nullptr;
  if( !raw_ff.Contains("_fitted") ) FF_lookup_h = (TH1D*) FF_lookup.Get("c_t"+tight_cat);
  vector<TGraphAsymmErrors*> fittedFFs;
  if( raw_ff.Contains("_fitted") ){
    TGraphAsymmErrors *dm0njet0 = (TGraphAsymmErrors*) FF_lookup.Get("dm0_njet0"+tight_cat); fittedFFs.push_back(dm0njet0);
    TGraphAsymmErrors *dm1njet0 = (TGraphAsymmErrors*) FF_lookup.Get("dm1_njet0"+tight_cat); fittedFFs.push_back(dm1njet0);
    TGraphAsymmErrors *dm0njet1 = (TGraphAsymmErrors*) FF_lookup.Get("dm0_njet1"+tight_cat); fittedFFs.push_back(dm0njet1);
    TGraphAsymmErrors *dm1njet1 = (TGraphAsymmErrors*) FF_lookup.Get("dm1_njet1"+tight_cat); fittedFFs.push_back(dm1njet1);
  }
  TFile nonclosure(nonclosure_corr);
  TH1D* nonclosure_h = (TH1D*) nonclosure.Get("nonclosure_fit_smoothed");
  for (Int_t jentry=0; jentry<nentries;jentry++) {
      event_s->GetEntry(jentry);
      if (DEBUG){ if(jentry % 100000 == 0) cout << jentry << "/" << nentries << endl; }
      
      if (  this->isInSR(mode,tau_ind) && this->isLoose(mode,tau_ind) ){
        if( !raw_ff.Contains("_fitted") ) FF_value = FF_lookup_h->GetBinContent( this->getBin(mode|tau_ind)+1 );
        else if( raw_ff.Contains("_fitted") ){
          FF_value = this->getFittedBinContent( mode, fittedFFs );
          // std::cout << "FF value: " << FF_value << std::endl;
          // cout<< "nonclosure: " << nonclosure_h->GetBinContent( this->getWeightIndex_mvis(event_s->alltau_mvis->at(tau_ind) )+1 ) << endl;
        }
        // cout << "weight index: " << this->getWeightIndex_lepPt(event_s->lep_pt)+1 << endl;
        // std::cout << "factor: " << nonclosure_h->GetBinContent( this->getWeightIndex_lepPt(event_s->lep_pt)+1 ) << std::endl;
        // std::cout << "factor: " << nonclosure_h->GetBinContent( this->getWeightIndex_mvis(event_s->alltau_mvis->at(tau_ind) )+1 ) << std::endl;
        
        // closure_h->Fill(event_s->alltau_mt->at(tau_ind),FF_value*nonclosure_h->GetBinContent( this->getWeightIndex_mvis(event_s->alltau_mvis->at(tau_ind) )+1 )*event_s->weight_sf );
        
        // lep pT case:
        closure_h->Fill(event_s->alltau_mvis->at(tau_ind),FF_value * nonclosure_h->GetBinContent( this->getWeightIndex_lepPt(event_s->lep_pt)+1 ) *event_s->weight_sf );
      }
  }

  output->cd();
  closure_h->Write();
  compare_t->Write();
  
  output_h = (TH1D*)compare_t->Clone("mt_corr");
  output_h->Divide(closure_h);
  
  output->cd();
  output_h->Write();

  TString sample;
  if(mode & _QCD) sample="_QCD";
  if(mode & _W_JETS) sample="_Wjets";
  GaussianKernelSmoother gsk;
  int ret=gsk.setInputHisto( output_h );
  if ( ret != 0 ) return;
  gsk.set_doWeights(1);
  gsk.set_doIgnoreZeroBins(1);
  gsk.set_kernelDistance( "lin" );
  gsk.set_doWidthInBins(1);
  gsk.setWidth(1.2);
  /*
  Double_t lastBin;
  // linear fit cut-off
  if(CHAN==kMU) lastBin=150;
  if(CHAN==kEL) lastBin=150;
  gsk.set_lastBinFrom(lastBin);
  */
  gsk.getSmoothHisto();
  TH1D *h2=gsk.returnSmoothedHisto();
  h2->Write();

  gsk.set_doErrors(1);
  gsk.getContSmoothHisto();
  TGraphAsymmErrors *g=   gsk.returnSmoothedGraph();
  Double_t x200; Double_t y200;
  if(CHAN==kMU)g->GetPoint(300*4,x200,y200);
  if(CHAN==kEL)g->GetPoint(300*4,x200,y200); // TODO CHANGE (110*4,x200,y200)
  for(int i=0; i<g->GetN(); i++){
    Double_t x; Double_t y;
    if(CHAN==kMU && i>300*4){
      g->GetPoint(i,x,y);
      g->SetPoint(i,x,y200);
    }
    else if(CHAN==kEL && i>300*4){ //CHANGE 110
      g->GetPoint(i,x,y);
      g->SetPoint(i,x,y200);
    }
    
  }
  g->SetTitle("mt_corr"+sample);
  g->SetName("mt_corr"+sample);
  g->Write();

  TGraph *gup = (TGraphAsymmErrors*)g->Clone("mt_corr"+sample+"_up");
  gup->SetTitle("mt_corr"+sample+"_up");
  for(Int_t j=0;j<g->GetN();j++) gup->SetPoint(j,g->GetX()[j],g->GetErrorYhigh(j) );
  gup->Write();
  TGraph *gdown = (TGraphAsymmErrors*)g->Clone("mt_corr"+sample+"_down");
  gdown->SetTitle("mt_corr"+sample+"_down");
  for(Int_t j=0;j<g->GetN();j++) gdown->SetPoint(j,g->GetX()[j],g->GetErrorYlow(j) );
  gdown->Write();
  
  TCanvas *c2=new TCanvas();
  output_h->Draw("E");
  g->Draw("same LP");
  output_h->Draw("E same");
  output_h->SetTitle("m_{T} correction");
  output_h->SetXTitle("m_{T}[GeV]");
  output_h->SetYTitle("Ratio");
  output_h->SetMaximum(2.);
  output_h->SetMinimum(0.);
  c2->SetName("mt_corr"+sample+"_c");
  c2->Write();
  if(doPlot){
    if(!CALC_SS_SR) c2->SaveAs("ViennaTool/Images/data_"+s_chan[CHAN]+"/mtcorr"+sample+tight_cat+".png");
    if(CALC_SS_SR) c2->SaveAs("ViennaTool/Images/data_"+s_chan[CHAN]+"/mtcorr"+sample+tight_cat+"_SS_SR.png");
  }

  FF_lookup.Close();compare.Close();output->Close();
  if( raw_ff.Contains("_fitted") ){
    for(int i=0; i<fittedFFs.size();i++){
      delete fittedFFs.at(i);
    }
  }
}


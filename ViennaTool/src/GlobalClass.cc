#include "ViennaTool/interface/GlobalClass.h"

#include <iostream>
#include <sstream>

using namespace std;

GlobalClass::GlobalClass()
{
  cout << "Instance of GlobalClass" << endl;
}

GlobalClass::~GlobalClass()
{
}

void GlobalClass::loadFile(TString filename, TString chain)
{
  tchain = new TChain(chain);
  tchain->Add(filename);

  if       (filename==datafile) this->curr_sample="data";
  else if  (filename==DYfile || filename==DY_NJfile) this->curr_sample="DY";
  else if  (filename==TTfile) this->curr_sample="TT";
  else if  (filename==Wjetsfile) this->curr_sample="Wjets";
  else if  (filename==QCDfile) this->curr_sample="QCD";
  else if  (filename==VVfile) this->curr_sample="VV";
  else this->curr_sample="unknown";
  
  int nev=0;
  if (chain=="Events"){  event_s = new SignalClass(tchain); if (DEBUG) nev=event_s->fChain->GetEntries(); }
  else std::cout << "unknown chain!" << std::endl;
  if (DEBUG) std::cout<<"File: "<<filename<<" loaded" << ", #events: "<< nev << std::endl;
}

void GlobalClass::closeFile()
{
  delete event_s;
  delete tchain;
}

void GlobalClass::init()
{
  TH1::SetDefaultSumw2(kTRUE);
  gROOT->SetStyle("Plain");
  //  gStyle->SetOptStat(1111111);
  gStyle->SetOptStat(0);
  //Set Color
  gStyle->SetPalette(1);
}


Int_t GlobalClass::isLoose(const Int_t mode, const Int_t ind) //default: 0,0
{
  if (mode & GEN_MATCH){ if ( event_s->alltau_gen_match->at(ind) != 6 ) return 0; }

  if (USE_MVA_ISO){
    //    if ( event_s->alltau_vlooseMVA->at(ind) && !event_s->alltau_tightMVA->at(ind)) return 1;
    if ( calcVTightFF && !event_s->alltau_vtightMVA->at(ind) && event_s->alltau_vlooseMVA->at(ind) ) return 1; 
    if ( !calcVTightFF && !event_s->alltau_tightMVA->at(ind) && event_s->alltau_vlooseMVA->at(ind) ) return 1; 
  } else{
    if (event_s->alltau_beta->at(ind)<100 && !event_s->alltau_mediumBeta->at(ind)) return 1;
  }
  //if (event_s->alltau_beta->at(ind)<100 && !event_s->alltau_looseBeta->at(ind)) return 1;

  return 0;
}

Int_t GlobalClass::isLoose_tt(const Int_t mode, const Int_t ind) //default: 0,0
{
  if (mode & GEN_MATCH){ if ( event_s->alltau_gen_match->at(ind) != 6 ) return 0; }

  if (USE_MVA_ISO){
    if ( calcVTightFF && !event_s->alltau_vtightMVA->at(ind) && event_s->alltau_vlooseMVA->at(ind) ) return 1; 
    if ( !calcVTightFF && !event_s->alltau_tightMVA->at(ind) && event_s->alltau_vlooseMVA->at(ind) ) return 1; 
  }

  return 0;
}

Int_t GlobalClass::isTight(const Int_t mode, const Int_t ind) //default: 0,0
{
  if (mode & GEN_MATCH){ if ( event_s->alltau_gen_match->at(ind) != 6 ) return 0; }

  if (USE_MVA_ISO){
    if ( calcVTightFF && event_s->alltau_vtightMVA->at(ind)) return 1; 
    if ( !calcVTightFF && event_s->alltau_tightMVA->at(ind)) return 1; 
  } else{
    if (event_s->alltau_mediumBeta->at(ind)) return 1;
  }
  //  if (event_s->alltau_looseBeta->at(ind)) return 1;

  return 0;
}

Int_t GlobalClass::isInSR(const Int_t mode, const Int_t ind)
{

  Double_t isolation; Double_t antiIso_min; Double_t antiIso_max;
  if(CHAN==kMU) isolation=LEP_ISO_CUT;
  if(CHAN==kEL) isolation=LEP_ISO_CUT_ET;
  antiIso_min=isolation; antiIso_max=isolation+0.1;
  
  if ( mode & GEN_MATCH ) {
    if ( event_s->alltau_gen_match->at(ind)!=realJet ) return 0; //FIX ME
  }

  //OS
  if ( mode & _SS || CALC_SS_SR ){
    if ( event_s->lep_q*event_s->alltau_q->at(ind)<=0. ) return 0;
  } else{
    if ( event_s->lep_q*event_s->alltau_q->at(ind)>=0. ) return 0;
  }

  //lep vetoes
  if ( !( event_s->passesDLVeto && event_s->passes3LVeto ) ) return 0;

  //mt
  if( CHAN!=kTAU ){
    if ( !(event_s->alltau_mt->at(ind)<MT_CUT || (mode & NO_SR) ) ) return 0;
  }

  //lep iso
  if ( CHAN == kTAU ){
    if ( mode & _AI && event_s->lep_iso<TAU1_ISO_CUT ) return 1;
    else if ( !(mode & _AI) && event_s->lep_iso>TAU1_ISO_CUT ) return 1; //0.5 for tight, >9 for vtight
  }else{
    if ( mode & _AI && event_s->lep_iso>antiIso_min && event_s->lep_iso<antiIso_max ) return 1; //for QCD OS/SS check
    else if ( !(mode & _AI) && (event_s->lep_iso<isolation) || ( mode & MUISO ) ) return 1;
  }
    

  return 0;

  /*
  if ((event_s->alltau_mt->at(ind)<MT_CUT || (mode & NO_SR)) &&
      //       event_s->lep_q*event_s->alltau_q->at(ind)<0.        &&
       event_s->passesDLVeto                             &&
      ( event_s->lep_iso<LEP_ISO_CUT || ( mode & MUISO ) ) &&
       event_s->passes3LVeto              )
    return 1;
  else return 0;
  */
}

Int_t GlobalClass::isInCR(const Int_t mode, const Int_t ind)
{  
  Int_t returnVal=0;
  if (mode & GEN_MATCH) {
    if ( event_s->alltau_gen_match->at(ind)!=realJet ) return 0;
  }

  Double_t isolation=0; Double_t antiIso_min; Double_t antiIso_max;
  if(CHAN==kMU) isolation=LEP_ISO_CUT;
  if(CHAN==kEL) isolation=LEP_ISO_CUT_ET;
  antiIso_min=isolation; antiIso_max=isolation+0.1;
  
  if (DEBUG==2) std::cout << "In TNtupleAnalyzer::isInCR" << std::endl;

  if  ((mode & _W_JETS && CHAN==kTAU)                   && 
       ( (event_s->alltau_mt->at(ind)>70) ||(mode & NO_SR)) &&
       event_s->passesDLVeto              &&
       event_s->passes3LVeto              &&
       event_s->lep_iso > TAU1_ISO_CUT    &&
       event_s->bpt_1<20                  &&
       ( ( event_s->lep_q*event_s->alltau_q->at(ind)<0 && !CALC_SS_SR ) || ( event_s->lep_q*event_s->alltau_q->at(ind)>=0 && CALC_SS_SR ) ) //for SS region check
       )
    returnVal=1;
  else if  ((mode & _W_JETS)                   && 
       ( (event_s->alltau_mt->at(ind)>70) ||(mode & NO_SR)) &&
       event_s->passesDLVeto              &&
       event_s->passes3LVeto              &&
       event_s->lep_iso < isolation     &&
       event_s->bpt_1<20                  &&
       ( ( event_s->lep_q*event_s->alltau_q->at(ind)<0 && !CALC_SS_SR ) || ( event_s->lep_q*event_s->alltau_q->at(ind)>=0 && CALC_SS_SR ) ) //for SS region check
       )
    returnVal=1;
  else if ((mode & _DY)                   &&
	   //	   event_s->lep_q*event_s->alltau_q->at(ind)<0. && //REMOVE? (orig: with)
	   //	   event_s->alltau_mt->at(ind)<MT_CUT   && //X (orig: with)
           event_s->lep_iso < isolation        &&
	   event_s->alltau_dRToLep->at(ind) > DR_TAU_LEP_CUT    &&
	   //TEST  fabs( event_s->alltau_mvis->at(ind)  - (MZ-1.2) )>10 &&  //1.2 because reco distribution has more entries below the peak
	   event_s->m_leplep>70                &&
	   event_s->m_leplep<110               )
    returnVal=1;
  /*else if ((mode & _TT && CHAN==kTAU)                &&
	   event_s->bpt_1>=20)
           returnVal=1;*/
  else if ((mode & _TT)                &&
	   //X	   ( (event_s->alltau_mt->at(ind)>70) || (mode & NO_SR) )   &&
	   //OLD	   event_s->otherLep_pt>10                  &&
	   //OLD	   event_s->otherLep_iso<LEP_ISO_CUT          &&
	   //OLD	   event_s->lep_iso<LEP_ISO_CUT          &&
	   //TRY	   ( event_s->n_iso_lep + event_s->n_iso_otherLep ) >= 2     &&
	   event_s->n_iso_lep >= 1                             &&
	   event_s->n_iso_otherLep >= 1                             &&
	   event_s->alltau_dRToLep->at(ind) > DR_TAU_LEP_CUT    &&
	   event_s->alltau_dRToOtherLep->at(ind) > DR_TAU_LEP_CUT    &&
	   //	   event_s->mu2_iso<0.3               &&
	   event_s->bpt_1>=20)
    returnVal=1;
  else if ((mode &_QCD && mode & SR && CHAN==kTAU)                   &&
           (event_s->lep_iso>TAU1_ISO_CUT) &&
           (event_s->lep_q*event_s->alltau_q->at(ind)<=0.)
           )
    returnVal=1;
  else if ((mode &_QCD && CHAN==kTAU)                   &&
           ( (!(mode & _AI) && event_s->lep_iso>TAU1_ISO_CUT) || ((mode & _AI) && event_s->lep_iso<TAU1_ISO_CUT) ) &&
           (event_s->lep_q*event_s->alltau_q->at(ind)>=0.)
           )
    returnVal=1;
  else if ((mode & _QCD)                  &&
	   (  ( !CALC_SS_SR && !(mode & _AI) && event_s->alltau_mt->at(ind)<40   && ( ( event_s->lep_iso > 0.05 && event_s->lep_iso<0.15 ) || ( mode & MUISO ) ) ) || //TRY
	      (  (CALC_SS_SR) && event_s->alltau_mt->at(ind)<40   &&  ( ( event_s->lep_iso > 0.15 && event_s->lep_iso<0.25 ) || ( mode & MUISO) )                    ) || //TRY
              (  mode & _AI && event_s->alltau_mt->at(ind)<40   &&   ( event_s->lep_iso > antiIso_min && event_s->lep_iso<antiIso_max )                     ) ) && //TRY
	   //	   (  ( !CALC_SS_SR && event_s->alltau_mt->at(ind)<MT_CUT   && ( event_s->lep_iso<LEP_ISO_CUT || ( mode & MUISO ) ) ) || //DEFAULT
	   //	      (  CALC_SS_SR                                     && event_s->lep_iso>LEP_ISO_CUT )   ) && //DEFAULT
	   event_s->passesDLVeto             &&
	   event_s->passes3LVeto             &&
	   event_s->lep_q*event_s->alltau_q->at(ind)>=0.
	   )
    returnVal=1;
  else returnVal=0; 

  return(returnVal);
}

Int_t GlobalClass::isInAll(const Int_t mode, const Int_t ind)
{
  if (mode & GEN_MATCH) {
    if ( event_s->alltau_gen_match->at(ind)!=realJet ) return 0; //FIX ME
  }

  if ( mode & MUISO ) return 1;
  if ( CHAN!=kTAU && event_s->lep_iso<LEP_ISO_CUT ) return 1;
  if ( CHAN==kTAU && event_s->lep_iso>TAU1_ISO_CUT ) return 1;

  return 0;
}

Int_t GlobalClass::getWeightIndex_mt(Double_t mt){
  for (int i=0; i<w_mt_n; i++){
    if ( mt>w_mt_v[i] && mt<w_mt_v[i+1] ) return i;
  }
  if (mt>w_mt_v[w_mt_n]) return 1e6; //overflow - one for all dimensions, though!
  //  if (mt>w_mt_v[w_mt_n]) return w_mt_n-1; //put overflow in last bin
  //  if (mt>w_mt_v[w_mt_n]) return w_mt_n; //overflow - only suitable for 1D!
  if (mt<w_mt_v[0]) return -1; //underflow

  return -1; //should never get here
}

Int_t GlobalClass::getWeightIndex_mvis(Double_t mvis){
  for (int i=0; i<w_mvis_n; i++){
    if ( mvis>w_mvis_v[i] && mvis<w_mvis_v[i+1] ) return i;
  }
  //if (mvis>w_mvis_v[w_mvis_n]) return 1; //overflow - one for all dimensions, though!
  //if (mvis<w_mvis_v[0]) return 1; //underflow

  return 1; //should never get here
}

Int_t GlobalClass::getWeightIndex_muiso(Double_t muiso){
  for (int i=0; i<w_muiso_n; i++){
    if ( muiso>w_muiso_v[i] && muiso<w_muiso_v[i+1] ) return i;
  }

  return 1; //should never get here
}

Int_t GlobalClass::getWeightIndex_dm(Int_t dm){
  for (int i=0; i<w_dm_n; i++){
    if ( dm>=w_dm_v[i] && dm<=w_dm_v[i+1] ) return i; //border belongs to lower bin
  }
  if (dm>w_dm_v[w_dm_n]) return w_dm_n-1;
  if (dm<w_dm_v[0]) return -1;

  return -1; //should never get here
}
//is under/overflow handled correctly above?

Int_t GlobalClass::getWeightBin(Double_t mt, Int_t dm){
  return ( this->getWeightIndex_mt(mt) + w_mt_n * this->getWeightIndex_dm(dm) );
}

Int_t GlobalClass::getWeightBin(const Int_t ind){
  return ( this->getWeightBin(event_s->alltau_mt->at(ind),event_s->alltau_decay->at(ind)) );
}

Int_t GlobalClass::getBin(const Int_t mode, const Int_t ind)
{  
  if (mode & VSVAR){
    if (mode & MT){
      if (mode & _FIT) return this->getIndex(FIT_BINS,nFIT_BINS+1,event_s->alltau_mt->at(ind));
      else return this->getIndex(p_mt_v,p_mt_n+1,event_s->alltau_mt->at(ind));
    }
    if (mode & MVIS) return this->getIndex(p_mvis_v,p_mvis_n+1,event_s->alltau_mvis->at(ind));
    if (mode & MTLL){
      if (mode & _FIT) return this->getIndex(FIT_BINS,nFIT_BINS+1,event_s->mt_leplep);
      else return this->getIndex(p_mt_v,p_mt_n+1,event_s->mt_leplep);
    }
    if (mode & MUISO) return this->getIndex(w_muiso_v,w_muiso_n+1,event_s->lep_iso);
    if (mode & NB)    return this->getIndex(p_nb_v,p_nb_n+1,event_s->nbtag);
    if (mode & DRB)   return this->getIndex(p_drb_v,p_drb_n+1,event_s->alltau_dRToB->at(ind) );
    //if (mode & DETA)  return this->getIndex(p_absdeta_v,p_absdeta_n+1,fabs(event_s->alltau_eta->at(ind)-event_s->lep_eta) );
    //if (mode & NJETS)  return this->getIndex(p_njets_v,p_njets_n+1,event_s->njets);
    //if (mode & NBJETS)  return this->getIndex(p_nbjets_v,p_nbjets_n+1,event_s->nbtag);
    
    //    if (mode & DRB){ cout << "X " << endl; cout << "X " << event_s->alltau_dRToB->size() << " " << ind << endl;  return this->getIndex(p_drb_v,p_drb_n+1,event_s->alltau_dRToB->at(ind) ); }
  }

  Int_t i_p,i_t,i_e,i_m,i_j;
  Int_t n_p=-99,n_e=-99,n_t=-99,n_j=-99;

  i_p=getPtIndex(mode,ind);
  i_t=getTrackIndex(mode,ind);
  i_e=getEtaIndex(mode,ind);
  i_j=getNjetIndex(mode,ind);

  if (mode & _W_JETS) {n_p=n_p_Wjets;n_e=n_e_Wjets;n_t=n_t_Wjets;n_j=n_j_Wjets;}
  else if ( (mode & _DY) ) {n_p=n_p_DY;n_e=n_e_DY;n_t=n_t_DY;n_j=n_j_DY;}
  else if ( (mode & _TT) && (mode & SR) )  {n_p=n_p_TT_SR;n_e=n_e_TT;n_t=n_t_TT;n_j=n_j_TT_SR;}
  else if ( (mode & _TT) ) {n_p=n_p_TT_CR;n_e=n_e_TT;n_t=n_t_TT;n_j=n_j_TT_CR;}
  //else if ( (mode & _TT) ) {n_p=n_p_TT;n_e=n_e_TT;n_t=n_t_TT;n_j=n_j_TT;}
  else if ( (mode & _QCD) && (mode & _AI) ) {n_p=n_p_QCD_AI;n_e=n_e_QCD;n_t=n_t_QCD;n_j=n_j_QCD;}
  else if ( (mode & _QCD) )     {n_p=n_p_QCD;n_e=n_e_QCD;n_t=n_t_QCD;n_j=n_j_QCD;}
  //  else {cout<<"getBin: Define a valid MODE!"<<std::endl;n_p=-99;n_e=-99;n_t=-99;}
  Int_t bin=i_e + i_p*n_e + i_t*n_p*n_e + i_j*n_t*n_p*n_e;
  // std::cout<<i_e<<" "<<i_p<<" "<<i_t<<" "<<bin<<" "<<std::endl;

  return(bin);// combined index of track-pt-eta bin
}

Int_t GlobalClass::nBins(const Int_t mode)
{
  if (mode & VSVAR){
    if (mode & _FIT ) return nFIT_BINS;
    else if ( ( mode & MT ) || ( mode & MTLL ) ) return p_mt_n;
    else if (   mode & MUISO )                   return w_muiso_n;
    else if (   mode & NB    )                   return p_nb_n;
    else if (   mode & DRB   )                   return p_drb_n;
    //    if (mode & MT ) return p_mt_n;
    //    if (mode & MTLL ) return p_mt_n;
  }

  if (mode & _W_JETS) return(n_e_Wjets*n_p_Wjets*n_t_Wjets*n_m_Wjets*n_j_Wjets);
  else if ( (mode & _DY) ) return(n_e_DY*n_p_DY*n_t_DY*n_m_DY*n_j_DY);
  else if ( (mode & _TT) && (mode & SR) ) return(n_e_TT*n_p_TT_SR*n_t_TT*n_m_TT*n_j_TT_SR);
  else if ( (mode & _TT) ) return(n_e_TT*n_p_TT_CR*n_t_TT*n_m_TT*n_j_TT_CR);
  //else if ( (mode & _TT) && (mode & SR) ) return(n_e_TT*n_p_TT*n_t_TT*n_m_TT*n_j_TT);
  else if ( (mode & _QCD) && (mode & _AI) ) return(n_e_QCD*n_p_QCD_AI*n_t_QCD*n_m_QCD*n_m_QCD*n_j_QCD);
  else if ( (mode & _QCD) )   return(n_e_QCD*n_p_QCD*n_t_QCD*n_m_QCD*n_m_QCD*n_j_QCD);

  std::cout<<"nBins(mode): No valid mode."<<std::endl;
  return -99;
}

Int_t GlobalClass::getPtIndex(const Int_t mode, const Int_t ind)
{
  // Binning in pt
  Int_t i_p=0;
  Double_t pt = event_s->alltau_pt->at(ind);
  
  if (mode & _W_JETS) {
    for(Int_t i=0;i<n_p_Wjets;i++) if (pt>=pt_cuts_Wjets[i]) i_p++;
    return(--i_p);
  } else if ( (mode & _DY) ) {
    for(Int_t i=0;i<n_p_DY;i++) if (pt>=pt_cuts_DY[i]) i_p++;
    return(--i_p);
  } else if ( (mode & _TT) && (mode & SR) ) {
    for(Int_t i=0;i<n_p_TT_SR;i++) if (pt>=pt_cuts_TT_SR[i]) i_p++;
    return(--i_p);
  } else if ( (mode & _TT) ) {
    for(Int_t i=0;i<n_p_TT_CR;i++) if (pt>=pt_cuts_TT_CR[i]) i_p++;
    return(--i_p);
    //} else if ( (mode & _TT) ) {
    //for(Int_t i=0;i<n_p_TT;i++) if (pt>=pt_cuts_TT[i]) i_p++;
    //return(--i_p);
    } else if ( (mode & _QCD && mode & _AI) ) {
    for(Int_t i=0;i<n_p_QCD_AI;i++) if (pt>=pt_cuts_QCD_AI[i]) i_p++;
    return(--i_p);    
  } else if ( (mode & _QCD) ) {
    for(Int_t i=0;i<n_p_QCD;i++) if (pt>=pt_cuts_QCD[i]) i_p++;
    return(--i_p);    
  } else {cout<<"Define a valid mode!"<<std::endl;return(-99);}
}

Int_t GlobalClass::getNjetIndex(const Int_t mode, const Int_t ind)
{
  // Binning in pt
  Int_t i_j=0;
  Double_t njet = event_s->njets;
  
  if (mode & _W_JETS) {
    for(Int_t i=0;i<n_j_Wjets;i++) if (njet>=njet_cuts_Wjets[i]) i_j++;
    return(--i_j);
  } else if ( (mode & _DY) ) {
    for(Int_t i=0;i<n_j_DY;i++) if (njet>=njet_cuts_DY[i]) i_j++;
    return(--i_j);
  } else if ( (mode & _TT) && (mode & SR) ) {
    for(Int_t i=0;i<n_j_TT_SR;i++) if (njet>=njet_cuts_TT_SR[i]) i_j++;
    return(--i_j);
  } else if ( (mode & _TT) ) {
    for(Int_t i=0;i<n_j_TT_CR;i++) if (njet>=njet_cuts_TT_CR[i]) i_j++;
    return(--i_j);
    //} else if ( (mode & _TT) ) {
    //for(Int_t i=0;i<n_j_TT;i++) if (njet>=njet_cuts_TT[i]) i_j++;
    //return(--i_j);
  } else if ( (mode & _QCD) ) {
    for(Int_t i=0;i<n_j_QCD;i++) if (njet>=njet_cuts_QCD[i]) i_j++;
    return(--i_j);
  } else {cout<<"Define a valid mode!"<<std::endl;return(-99);}
}

Int_t GlobalClass::getNjets(const Int_t mode, const Int_t ind)
{
  if(mode & _W_JETS) return N_j_Wjets;
  else if(mode & _QCD) return N_j_QCD;
  else if(mode & _DY) return N_j_DY;
  else if(mode & _TT && mode & SR) return N_j_TT_SR;
  else if(mode & _TT) return N_j_TT_CR;
  else {cout<<"Define a valid mode!"<<std::endl;return(-99);}
}
Int_t GlobalClass::getNtracks(const Int_t mode, const Int_t ind)
{
  if(mode & _W_JETS) return N_t_Wjets;
  else if(mode & _QCD) return N_t_QCD;
  else if(mode & _DY) return N_t_DY;
  else if(mode & _TT) return N_t_TT;
  else {cout<<"Define a valid mode!"<<std::endl;return(-99);}
}
Int_t GlobalClass::getNpts(const Int_t mode, const Int_t ind)
{
  if(mode & _W_JETS) return N_p_Wjets;
  else if(mode & _QCD) return N_p_QCD;
  else if(mode & _DY) return N_p_DY;
  else if(mode & _TT && mode & SR) return N_p_TT_SR;
  else if(mode & _TT) return N_p_TT_CR;
  else {cout<<"Define a valid mode!"<<std::endl;return(-99);}
}


Int_t GlobalClass::getMtIndex(const Int_t mode, const Int_t ind)
{
  // Binning in mt
  Int_t i_m=0;
  Double_t mt = event_s->alltau_mt->at(ind);
  
  if (mode & _W_JETS) {
    for(Int_t i=0;i<n_m_Wjets;i++) if (mt>=mt_cuts_Wjets[i]) i_m++;
    return(--i_m);
  } else if ( (mode & _DY) ) {
    for(Int_t i=0;i<n_m_DY;i++) if (mt>=mt_cuts_DY[i]) i_m++;
    return(--i_m);
  } else if ( (mode & _TT) ) {
    for(Int_t i=0;i<n_m_TT;i++) if (mt>=mt_cuts_TT[i]) i_m++;
    return(--i_m);
  } else if ( (mode & _QCD) ) {
    for(Int_t i=0;i<n_m_QCD;i++) if (mt>=mt_cuts_QCD[i]) i_m++;
    return(--i_m);
  } else {cout<<"Define a valid mode!"<<std::endl;return(-99);}
}

Int_t GlobalClass::getEtaIndex(const Int_t mode, const Int_t ind)
{
  // Binning in eta
  Int_t i_e=0;
  Double_t eta = event_s->alltau_eta->at(ind);
  
  if (mode & _W_JETS) {
    for(Int_t i=0;i<n_e_Wjets;i++) if (TMath::Abs(eta)>=eta_cuts_Wjets[i]) i_e++;
    return(--i_e);
  } else if ( (mode & _DY) ) {
    for(Int_t i=0;i<n_e_DY;i++) if (TMath::Abs(eta)>=eta_cuts_DY[i]) i_e++;
    return(--i_e);
  } else if ( (mode & _TT) ) {
    for(Int_t i=0;i<n_e_TT;i++) if (TMath::Abs(eta)>=eta_cuts_TT[i]) i_e++;
    return(--i_e);
  } else if ( (mode & _QCD) ) {
    for(Int_t i=0;i<n_e_QCD;i++) if (TMath::Abs(eta)>=eta_cuts_QCD[i]) i_e++;
    return(--i_e);
  } else {cout<<"Define a valid mode!"<<std::endl;return(-99);}
}

Int_t GlobalClass::getTrackIndex(const Int_t mode, const Int_t ind)
{
  // Binning in decay mode
  Int_t i_t=0;
  Int_t i_decayMode=event_s->alltau_decay->at(ind);

  if (mode & _W_JETS) {
    for(Int_t i=0;i<n_t_Wjets;i++) if (i_decayMode>=decay_cuts_Wjets[i]) i_t++;
    return(--i_t);
  } else if ( (mode & _DY) ) {
    for(Int_t i=0;i<n_t_DY;i++) if (i_decayMode>=decay_cuts_DY[i]) i_t++;
    return(--i_t);
  } else if ( (mode & _TT) ) {
    for(Int_t i=0;i<n_t_TT;i++) if (i_decayMode>=decay_cuts_TT[i]) i_t++;
    return(--i_t);
  } else if ( (mode & _QCD) ) {
    for(Int_t i=0;i<n_t_QCD;i++) if (i_decayMode>=decay_cuts_QCD[i]) i_t++;
    return(--i_t);
  } else {cout<<"Define a valid mode!"<<std::endl;return(-99);}
}

//a_size is the size of the array; last array entry is upper bound, i.e. nbin=size-1
Int_t GlobalClass::getIndex(const Double_t* a, const Int_t a_size, const Double_t val){
  if (val<a[0]) return -1;
  for (int i=0; i<(a_size-1); i++){
    if ( val>a[i] && val<=a[i+1] ) return i;
  }
  return (a_size-1);

}

Int_t GlobalClass::passesCuts(const Int_t cuts, const Int_t ind){

  Int_t ret=1;

  if (cuts & NP1){
    if ( event_s->alltau_decay->at(ind)>=5 ) ret=ret && 0;
  }
  if (cuts & NP3){
    if ( event_s->alltau_decay->at(ind)<=9 ) ret=ret && 0;
  }
  if (cuts & PT1){
    //    if ( this->getPtIndex(_W_JETS,ind)!=0   ) ret=ret && 0;
    if ( event_s->alltau_pt->at(ind)<20 || event_s->alltau_pt->at(ind)>30   ) ret=ret && 0;
  }
  if (cuts & PT2){
    //    if ( this->getPtIndex(_W_JETS,ind)!=1   ) ret=ret && 0;
    if ( event_s->alltau_pt->at(ind)<30 || event_s->alltau_pt->at(ind)>40   ) ret=ret && 0;
  }
  if (cuts & PT3){
    //    if ( this->getPtIndex(_W_JETS,ind)!=2   ) ret=ret && 0;
    if ( event_s->alltau_pt->at(ind)<40 || event_s->alltau_pt->at(ind)>1e8  ) ret=ret && 0;
  }
  if (cuts & ETA1){
    if ( fabs(event_s->alltau_eta->at(ind))>=0.8  ) ret=ret && 0;
  }
  if (cuts & ETA2){
    if ( fabs(event_s->alltau_eta->at(ind))<0.8 ||  fabs(event_s->alltau_eta->at(ind))>=1.479 ) ret=ret && 0;
  }
  if (cuts & ETA3){
    if ( fabs(event_s->alltau_eta->at(ind))<1.479 ) ret=ret && 0;
  }

  return ret;
}

Double_t GlobalClass::selVal(const Int_t mode, const Int_t ind){

  if      (mode & M2T)   {return event_s->alltau_mt2->at(ind);}
  else if (mode & MVIS) {return event_s->alltau_mvis->at(ind);}
  else if (mode & PT)   {return event_s->alltau_pt->at(ind);}
  else if (mode & MUISO) {return event_s->lep_iso;}
  else if (mode & ZPT)   {return event_s->alltau_Zpt->at(ind);}
  else if (mode & SVFIT) {return event_s->alltau_svfit->at(ind);}
  else if (mode & MT) {return event_s->alltau_mt->at(ind);}
  else if (mode & LEPPT) {return event_s->lep_pt;}
  else if (mode & MVAMET) {return event_s->mvamet;}
  else if (mode & ETA)   {return event_s->alltau_eta->at(ind);}
  else if (mode & MMTOT) {return TMath::Sqrt( TMath::Power(event_s->alltau_mt->at(ind),2) + TMath::Power(event_s->alltau_mt2->at(ind),2) + 2*event_s->lep_pt*event_s->alltau_pt->at(ind)*(1-TMath::Cos( TVector2::Phi_mpi_pi( event_s->lep_phi-event_s->alltau_phi->at(ind) ) ) ) );}
  else{ std::cout << "selVal: Warning: no valid variable given!" << std::endl; return -1; }

}

Int_t GlobalClass::getPInd( Int_t dm ){

  if ( dm < 5 ) return 0;
  if ( dm > 9 ) return 1;

  std::cout << "ERROR : Not a valid decay mode" << std::endl;
  return -1;

}

Int_t GlobalClass::fulfillCategory(Int_t categoryMode, Int_t ind){

  if ( categoryMode & _0JETLOW && (CHAN==kMU || CHAN==kEL) ){
    if(event_s->njets!=0) return 0;
    if(event_s->alltau_pt->at(ind) < 20) return 0;
    if(event_s->alltau_pt->at(ind) > 50) return 0;
    
  }
  if ( categoryMode & _0JETLOW && CHAN==kTAU ){
    if(event_s->njets!=0) return 0;
    if(event_s->alltau_pt->at(ind) < 50) return 0;
    
  }
  if ( categoryMode & _0JETHIGH && (CHAN==kMU || CHAN==kEL) ){
    if(event_s->njets!=0) return 0;
    if(event_s->alltau_pt->at(ind) < 50) return 0;
    
  }
  if ( categoryMode & _0JETHIGH && CHAN==kTAU ) return 0;

  if ( categoryMode & _1JETLOW && (CHAN==kMU || CHAN==kEL) ){
    if( !(event_s->njets==1 || (event_s->njets==2 && event_s->mjj<500) ) ) return 0;
    if( !( (event_s->alltau_pt->at(ind) > 30 && event_s->alltau_pt->at(ind) < 40) || (event_s->alltau_pt->at(ind) > 40 && event_s->alltau_Zpt->at(ind) < 140) ) ) return 0;
    
  }
  if ( categoryMode & _1JETLOW && CHAN==kTAU ){
    if( event_s->alltau_pt->at(ind) < 50 ) return 0;
    if( event_s->alltau_Zpt->at(ind) < 100 ) return 0;
    if( event_s->alltau_Zpt->at(ind) > 170 ) return 0;
    if( !(event_s->njets==1 || (event_s->njets>=2 && !(event_s->mjj<300 && abs(event_s->jdeta)>2.5 && event_s->njetingap20<1) ) ) ) return 0;
    
  }
  if ( categoryMode & _1JETHIGH && (CHAN==kMU || CHAN==kEL) ){
    if( !(event_s->njets==1 || (event_s->njets==2 && event_s->mjj<500) ) ) return 0;
    if( event_s->alltau_pt->at(ind) < 40 ) return 0;
    if( event_s->alltau_Zpt->at(ind) < 140 ) return 0;
    
  }
  if ( categoryMode & _1JETHIGH && CHAN==kTAU ){
    if( event_s->alltau_pt->at(ind) < 50 ) return 0;
    if( event_s->alltau_Zpt->at(ind) < 170 ) return 0;
    if( !(event_s->njets==1 || (event_s->njets>2 && !(event_s->mjj>300 && abs(event_s->jdeta)>2.5 && event_s->njetingap20<1) ) ) ) return 0;
    
  }
  if ( categoryMode & _VBFLOW && (CHAN==kMU || CHAN==kEL) ){
    if( event_s->njets!=2 ) return 0;
    if( event_s->alltau_pt->at(ind) < 20 ) return 0;
    if( event_s->mjj < 500 ) return 0;
    if( !(event_s->mjj < 800 || event_s->alltau_Zpt->at(ind) < 100 ) ) return 0;    
  }
  if ( categoryMode & _VBFLOW && CHAN==kTAU ){
    if( event_s->alltau_pt->at(ind) < 50 ) return 0;
    if( event_s->njets<=2 ) return 0;
    if( event_s->njetingap20 > 0 ) return 0;
    if( abs(event_s->jdeta) < 2.5 ) return 0;
    if( !( (event_s->alltau_Zpt->at(ind)<100 && event_s->mjj>300) || (event_s->alltau_Zpt->at(ind)>100 && event_s->mjj>300 && event_s->mjj<500) ) ) return 0;
  }
  if ( categoryMode & _VBFHIGH && (CHAN==kMU || CHAN==kEL) ){
    if( event_s->njets!=2 ) return 0;
    if( event_s->alltau_pt->at(ind) < 20 ) return 0;
    if( event_s->mjj < 800 ) return 0;
    if( event_s->alltau_Zpt->at(ind) < 100 ) return 0;    
  }
  if ( categoryMode & _VBFHIGH && CHAN==kTAU ){
    if( event_s->alltau_pt->at(ind) < 50 ) return 0;
    if( event_s->njets<=2 ) return 0;
    if( event_s->njetingap20 > 0 ) return 0;
    if( abs(event_s->jdeta) < 2.5 ) return 0;
    if( event_s->alltau_Zpt->at(ind)<100 ) return 0;
    if( event_s->mjj<500 ) return 0;
  }

  if ( categoryMode & _2JET && event_s->njets < 2 ) return 0;
  if ( categoryMode & _ANYB && event_s->nbtag < 1 ) {
    return 0;
  }

  
  return 1;
  
}

TString GlobalClass::getCatString_noSel(Int_t categoryMode){

  if ( categoryMode & _0JETLOW ) return categories[0];
  if ( categoryMode & _0JETHIGH ) return categories[1];
  if ( categoryMode & _1JETLOW ) return categories[2];
  if ( categoryMode & _1JETHIGH ) return categories[3];
  if ( categoryMode & _VBFLOW ) return categories[4];
  if ( categoryMode & _VBFHIGH ) return categories[5];
  if ( categoryMode & _2JET ) return categories[6];
  if ( categoryMode & _ANYB ) return categories[7];

  return "";
  
}

TString GlobalClass::getFracString(Int_t categoryMode){

  if ( categoryMode & _CATFRAC_MT ) return "_catfrac_mt";
  if ( categoryMode & _CATFRAC_ET ) return "_catfrac_et";
  if ( categoryMode & _CATFRAC_TT ) return "_catfrac_tt";
  
  if ( CHAN==kEL && categoryMode & _INCLFRAC_MT ) return "_mtfrac";
  if ( CHAN==kTAU && categoryMode & _INCLFRAC_MT ) return "_mtfrac";

  return "";
  
}

TString GlobalClass::getChannelString(Int_t categoryMode){

  if(CHAN==kMU){
    if(categoryMode & _INCLFRAC_MT) return "mt/incl";
    if(categoryMode & _CATFRAC_MT) return "mt/ZZZZZ";
  }
  if(CHAN==kEL){
    if(categoryMode & _INCLFRAC_ET) return "et/incl";
    if(categoryMode & _CATFRAC_ET) return "et/ZZZZZ";
    if(categoryMode & _INCLFRAC_MT) return "et/incl_mtfrac";
    if(categoryMode & _CATFRAC_MT) return"et/ZZZZZ_mtfrac";
  }
  if(CHAN==kTAU){
    if(categoryMode & _INCLFRAC_TT) return "tt/incl";
    if(categoryMode & _CATFRAC_TT) return "tt/ZZZZZ";
    if(categoryMode & _INCLFRAC_MT) return "tt/incl_mtfrac";
    if(categoryMode & _CATFRAC_MT) return "tt/ZZZZZ_mtfrac";
  }

  return "mt/incl";
}

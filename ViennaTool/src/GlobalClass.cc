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

TString GlobalClass::getWPCutString(const TString isolation, const Int_t mode, const Int_t useTauIndex){
  
  //std::cout << "useTauIndex: " << useTauIndex << endl;

  TString tau_index = "0";
  //This was changed - FIXME Need to understand - just guess
  if (useTauIndex) {
    tau_index = "tau_iso_ind";
    std::cout<<"set tai_iso_ind"<<std::endl;
  }

  Int_t fulfill, fail;
  TString s_genmatch = "1";
  TString s_fulfill = "1";
  TString s_fail = "1";
  

  if( isolation == "tight"){
    fulfill = wpTightFulfill;
    fail = wpTightFail;
  }else if( isolation == "loose"){
    fulfill = wpLooseFulfill;
    fail = wpLooseFail;
  }else{
    std::cout << "Error in GlobalClass::getWPCutString():  No valid isolation mode selected, use 'tight' or 'loose'! " << std::endl;
    return "0";
  }

  if (mode & GEN_MATCH) s_genmatch = "(alltau_gen_match["+tau_index+"]=="+to_string(realJet)+")";
  
  if     (fulfill == _VVVLOOSE_DNN) s_fulfill = "(alltau_vvvlooseDNN["+tau_index+"]>0.5)";
  else if(fulfill == _VVLOOSE_DNN)  s_fulfill = "(alltau_vvlooseDNN["+tau_index+"]>0.5)";
  else if(fulfill == _VLOOSE_DNN)  s_fulfill = "(alltau_vlooseDNN["+tau_index+"]>0.5)";
  else if(fulfill == _LOOSE_DNN)  s_fulfill = "(alltau_looseDNN["+tau_index+"]>0.5)";
  else if(fulfill == _MEDIUM_DNN) s_fulfill = "(alltau_mediumDNN["+tau_index+"]>0.5)";
  else if(fulfill == _TIGHT_DNN)  s_fulfill = "(alltau_tightDNN["+tau_index+"]>0.5)";
  else if(fulfill == _VTIGHT_DNN) s_fulfill = "(alltau_vtightDNN["+tau_index+"]>0.5)";
  else if(fulfill == _VVTIGHT_DNN) s_fulfill = "(alltau_vvtightDNN["+tau_index+"]>0.5)";
  else{
    std::cout << "Error in GlobalClass::getWPCutString():  No valid working point selected, use '_VLOOSE', '_LOOSE', '_MEDIUM', '_TIGHT', '_VTIGHT'! " << std::endl;
    return "0";
  }
  
  if     (fail == _VVVLOOSE_DNN) s_fail = "(alltau_vvvlooseDNN["+tau_index+"]<0.5)";
  else if(fail == _VVLOOSE_DNN)  s_fail = "(alltau_vvlooseDNN["+tau_index+"]<0.5)";
  else if(fail == _VLOOSE_DNN)  s_fail = "(alltau_vlooseDNN["+tau_index+"]<0.5)";
  else if(fail == _LOOSE_DNN)  s_fail = "(alltau_looseDNN["+tau_index+"]<0.5)";
  else if(fail == _MEDIUM_DNN) s_fail = "(alltau_mediumDNN["+tau_index+"]<0.5)";
  else if(fail == _TIGHT_DNN)  s_fail = "(alltau_tightDNN["+tau_index+"]<0.5)";
  else if(fail == _VTIGHT_DNN) s_fail = "(alltau_vtightDNN["+tau_index+"]<0.5)";
  else if(fail == _VVTIGHT_DNN) s_fail = "(alltau_vvtightDNN["+tau_index+"]<0.5)";
  else if(fail != 0){
    std::cout << "Error in GlobalClass::getWPCutString():  No valid working point selected, use '_VLOOSE', '_LOOSE', '_MEDIUM', '_TIGHT', '_VTIGHT', '0'! " << std::endl;
    return "0";
  }
  

  // if (DEBUG) {
  //   std::cout << "Returning the following WP cut string: " << "("+s_genmatch + "*" + s_fulfill + "*" + s_fail+")" <<std::endl;
  // }
  return "("+s_genmatch + "*" + s_fulfill + "*" + s_fail+")";
}

Int_t GlobalClass::isLoose(const Int_t mode, const Int_t ind) //default: 0,0
{
  if (mode & GEN_MATCH){ if ( event_s->alltau_gen_match->at(ind) != realJet ) return 0; }

  Int_t c1 = 0;
  Int_t c2 = 0;
  Int_t returnValue = 0;
  
  if      ( wpLooseFulfill == _VVVLOOSE_DNN && event_s->alltau_vvvlooseDNN->at(ind) ) c1 = 1;
  else if ( wpLooseFulfill == _VVLOOSE_DNN  && event_s->alltau_vvlooseDNN->at(ind)  ) c1 = 1;
  else if ( wpLooseFulfill == _VLOOSE_DNN  && event_s->alltau_vlooseDNN->at(ind)  ) c1 = 1;
  else if ( wpLooseFulfill == _LOOSE_DNN  && event_s->alltau_looseDNN->at(ind)  ) c1 = 1;
  else if ( wpLooseFulfill == _MEDIUM_DNN && event_s->alltau_mediumDNN->at(ind) ) c1 = 1;
  else if ( wpLooseFulfill == _TIGHT_DNN  && event_s->alltau_tightDNN->at(ind)  ) c1 = 1;
  else if ( wpLooseFulfill == _VTIGHT_DNN && event_s->alltau_vtightDNN->at(ind) ) c1 = 1;
  else if ( wpLooseFulfill == _VVTIGHT_DNN && event_s->alltau_vvtightDNN->at(ind) ) c1 = 1;

  if      ( wpLooseFail == _VVVLOOSE_DNN && !event_s->alltau_vvvlooseDNN->at(ind) ) c2 = 1;
  else if ( wpLooseFail == _VVLOOSE_DNN  && !event_s->alltau_vvlooseDNN->at(ind)  ) c2 = 1;
  else if ( wpLooseFail == _VLOOSE_DNN && !event_s->alltau_vlooseDNN->at(ind) ) c2 = 1;
  else if ( wpLooseFail == _LOOSE_DNN  && !event_s->alltau_looseDNN->at(ind)  ) c2 = 1;
  else if ( wpLooseFail == _MEDIUM_DNN && !event_s->alltau_mediumDNN->at(ind) ) c2 = 1;
  else if ( wpLooseFail == _TIGHT_DNN  && !event_s->alltau_tightDNN->at(ind)  ) c2 = 1;
  else if ( wpLooseFail == _VTIGHT_DNN && !event_s->alltau_vtightDNN->at(ind) ) c2 = 1;
  else if ( wpLooseFail == _VVTIGHT_DNN && !event_s->alltau_vvtightDNN->at(ind) ) c2 = 1;
  
  return c1*c2;
}

Int_t GlobalClass::isTight_alt(const Int_t mode, const Int_t ind) //default: 0,0
{
  // std::cout<<"alternative tight WP"<<std::endl;
  if (mode & GEN_MATCH){ if ( event_s->alltau_gen_match->at(ind) != realJet ) return 0; }

  if ( event_s->alltau_mediumDNN->at(ind) && !event_s->alltau_tightDNN->at(ind) ) return 1; 

  return 0;
}

Int_t GlobalClass::isTight(const Int_t mode, const Int_t ind) //default: 0,0
{
  if (mode & GEN_MATCH){ if ( event_s->alltau_gen_match->at(ind) != realJet ) return 0; }
  
  Int_t c1 = 0;
  Int_t c2 = 0;
  Int_t returnValue = 0;

  if      ( wpTightFulfill == _VVVLOOSE_DNN && event_s->alltau_vvvlooseDNN->at(ind) ) c1 = 1;
  else if ( wpTightFulfill == _VVLOOSE_DNN  && event_s->alltau_vvlooseDNN->at(ind)  ) c1 = 1;
  else if ( wpTightFulfill == _VLOOSE_DNN  && event_s->alltau_vlooseDNN->at(ind)  ) c1 = 1;
  else if ( wpTightFulfill == _LOOSE_DNN  && event_s->alltau_looseDNN->at(ind)  ) c1 = 1;
  else if ( wpTightFulfill == _MEDIUM_DNN && event_s->alltau_mediumDNN->at(ind) ) c1 = 1;
  else if ( wpTightFulfill == _TIGHT_DNN  && event_s->alltau_tightDNN->at(ind)  ) c1 = 1;
  else if ( wpTightFulfill == _VTIGHT_DNN && event_s->alltau_vtightDNN->at(ind) ) c1 = 1;
  else if ( wpTightFulfill == _VVTIGHT_DNN && event_s->alltau_vvtightDNN->at(ind) ) c1 = 1;
  
  if      ( wpTightFail == _VVVLOOSE_DNN && !event_s->alltau_vvvlooseDNN->at(ind) ) c2 = 1;
  else if ( wpTightFail == _VVLOOSE_DNN  && !event_s->alltau_vvlooseDNN->at(ind)  ) c2 = 1;
  else if ( wpTightFail == _VLOOSE_DNN  && !event_s->alltau_vlooseDNN->at(ind)  ) c2 = 1;
  else if ( wpTightFail == _LOOSE_DNN  && !event_s->alltau_looseDNN->at(ind)  ) c2 = 1;
  else if ( wpTightFail == _MEDIUM_DNN && !event_s->alltau_mediumDNN->at(ind) ) c2 = 1;
  else if ( wpTightFail == _TIGHT_DNN  && !event_s->alltau_tightDNN->at(ind)  ) c2 = 1;
  else if ( wpTightFail == _VTIGHT_DNN && !event_s->alltau_vtightDNN->at(ind) ) c2 = 1;
  else if ( wpTightFail == _VVTIGHT_DNN && !event_s->alltau_vvtightDNN->at(ind) ) c2 = 1;
  else if ( wpTightFail == 0) c2 = 1;
  
  return c1*c2;
}

Int_t GlobalClass::isInSR(const Int_t mode, const Int_t ind)
{

  Double_t isolation; Double_t antiIso_min; Double_t antiIso_max;
  if(CHAN==kMU) isolation=LEP_ISO_CUT;
  if(CHAN==kEL) isolation=LEP_ISO_CUT_ET;
  antiIso_min=isolation; antiIso_max=isolation+0.1;
  
  // if( mode & JET0 ){
  //   if( event_s->njets >= 1 ) return 0;
  // }
  // if( mode & JET1){
  //   if( event_s->njets < 1 ) return 0;
  // }
  //antiIso_min=isolation+0.15; antiIso_max=isolation+0.35;

  //MSSM definition of SR
  //if( !( event_s->nbtag == 0 || (event_s->nbtag>0 && event_s->njets<=1) ) ) return 0;
  // cout << "====================" << endl;
  // cout << event_s->alltau_gen_match->at(ind) << endl;
  if ( mode & GEN_MATCH ) {
    if ( event_s->alltau_gen_match->at(ind)!=realJet ) return 0; //FIX ME
  }

  //OS
  // cout << event_s->lep_q << " "  << event_s->alltau_q->at(ind) << endl;
  if ( mode & _SS || CALC_SS_SR ){
    if ( event_s->lep_q*event_s->alltau_q->at(ind)<=0. ) return 0;
  } else{
    if ( event_s->lep_q*event_s->alltau_q->at(ind)>=0. ) return 0;
  }

  //lep vetoes
  // cout << event_s->passesDLVeto << " " << event_s->passes3LVeto << endl;
  if ( !( event_s->passesDLVeto && event_s->passes3LVeto ) ) return 0;

  //mt
  if( CHAN!=kTAU ){
    if ( !(event_s->alltau_mt->at(ind)<MT_CUT || (mode & NO_SR) ) ) return 0;
  }

  //lep iso
  // cout << event_s->lep_iso << endl;
  if ( CHAN == kTAU ){
    if ( mode & _AI && event_s->lep_iso<TAU1_ISO_CUT ) return 1;
    else if ( !(mode & _AI) && event_s->lep_iso>TAU1_ISO_CUT ) return 1; //0.5 for tight, >9 for vtight
  }else{
    if ( mode & _AI && event_s->lep_iso>antiIso_min && event_s->lep_iso<antiIso_max ) return 1; //for QCD OS/SS check
    else if ( !(mode & _AI) && (event_s->lep_iso<isolation) || ( mode & MUISO ) ) return 1;
  }
    

  return 0;
 
}

TString GlobalClass::getSRCutString(const Int_t mode, const Int_t categoryMode){

  Double_t isolation; Double_t antiIso_min; Double_t antiIso_max;
  
  if(CHAN==kMU) isolation=LEP_ISO_CUT;
  if(CHAN==kEL) isolation=LEP_ISO_CUT_ET;
  
  antiIso_min=isolation; 
  antiIso_max=isolation+0.1;
  
  TString s_genmatch, s_jetmode, s_mode = "";

  if ( mode & GEN_MATCH ) s_genmatch = " * (alltau_gen_match[tau_iso_ind] == 6) ";

  if(mode & JET0) s_jetmode = " * (njets == 0) ";
  else if(mode & JET1) s_jetmode = " * (njets > 0) ";
  
  if ( mode & _SS || CALC_SS_SR ) s_mode = "( tau_iso_ind >= 0) * (lep_q * alltau_q[tau_iso_ind] >= 0)";
  else                            s_mode = "( tau_iso_ind >= 0) * (lep_q * alltau_q[tau_iso_ind] <= 0)";

  s_mode += " * (passesDLVeto > 0.5) * (passes3LVeto > 0.5)";

  if( (inclusive_selection && (CHAN==kMU || CHAN==kEL)) || categoryMode & _DUMMYCAT ) s_mode += " * (alltau_mt[tau_iso_ind] < " + to_string(MT_CUT) + ")";

  if( CHAN != kTAU ){
    if( !(mode & NO_SR) ) s_mode += " * (alltau_mt[tau_iso_ind] < "+ to_string(MT_CUT) +")";
  }

  if( CHAN == kTAU ){
    if ( mode & _AI ) s_mode += " * (lep_iso < "+to_string(TAU1_ISO_CUT) +")";
    else s_mode += " * (lep_iso > "+to_string(TAU1_ISO_CUT) +")";
  }else{
    if ( mode & _AI ) s_mode += " * (lep_iso > "+to_string(antiIso_min)+") * (lep_iso < "+to_string(antiIso_max)+") ";
    else if ( !(mode & MUISO)) s_mode += " * (lep_iso < " +to_string(isolation) + ") ";
  }
  
  return s_mode + s_genmatch + s_jetmode; 
}

TString GlobalClass::getCRCutString(const Int_t mode){
  TString s_genmatch, s_jetmode, s_mode = "";

  Double_t lep_iso_min; Double_t lep_iso_max;
  Double_t isolation=0; Double_t antiIso_min; Double_t antiIso_max;
  if(CHAN==kMU) isolation=LEP_ISO_CUT;
  if(CHAN==kEL){
    isolation=LEP_ISO_CUT_ET;
    lep_iso_min = 0.02;
    lep_iso_max = 0.15;
  }else{
    lep_iso_min = 0.05;
    lep_iso_max = 0.15;
  }
  antiIso_min=isolation; antiIso_max=isolation+0.1;

  
  if( mode & GEN_MATCH ) s_genmatch = " * (alltau_gen_match[tau_iso_ind] == 6) ";
  
  if(mode & JET0) s_jetmode = " * (njets == 0) ";
  else if(mode & JET1) s_jetmode = " * (njets > 0) ";

  if( mode & _DY ){
    s_mode = "(lep_iso < "+to_string(isolation)+")*(alltau_dRToLep[0] > "+to_string(DR_TAU_LEP_CUT)+")*(m_leplep > 70)*(m_leplep < 110)";
  }
  else if( mode & _TT ){
    s_mode = "(n_iso_lep >= 1)*(passes3LVeto < 0.5 )*(alltau_dRToLep[0] > "+to_string(DR_TAU_LEP_CUT)+")*(alltau_dRToOtherLep[0] > "+to_string(DR_TAU_LEP_CUT)+")*(njets>1)*(bpt_1>=20)";
  }
  else if( mode & _W_JETS){
    s_mode = "(passesDLVeto > 0.5) * (passes3LVeto > 0.5) * (bpt_1 < 20)";
    if( !(mode & NO_SR) ) s_mode += " * (alltau_mt[0] > 70)";
    if( CHAN == kTAU ) s_mode += " * (lep_iso > "+to_string(TAU1_ISO_CUT)+")";
    else s_mode += " * (lep_iso < "+to_string(isolation)+")";
    if( mode & _AI ) s_mode += "* (lep_q*alltau_q[0]>0.0)";
    else s_mode += "* (lep_q*alltau_q[0]<0.0)";
  }
  else if( mode & _QCD ){
    if( CHAN == kTAU ){
      if( mode & SR ){
        s_mode = "(lep_iso > "+to_string(TAU1_ISO_CUT)+")*(lep_q*alltau_q[0]<0.0)";
      }else{
        if( mode & _AI){
          s_mode = "(lep_iso < "+to_string(TAU1_ISO_CUT)+")";
        }else{
          s_mode = "(lep_iso > "+to_string(TAU1_ISO_CUT)+")";
        }
        s_mode += " * (lep_q*alltau_q[0]>0.0) * (passesDLVeto > 0.5) * (passes3LVeto > 0.5)";
      }
    }else{
      s_mode = "(alltau_mt[0] < "+to_string(MT_CUT)+")";
      s_mode += " * (lep_q * alltau_q[0] >= 0) * (passesDLVeto > 0.5) * (passes3LVeto > 0.5) ";
      if( !CALC_SS_SR * !(mode & _AI) ){
        if( !(mode & MUISO) ) s_mode += " * (lep_iso > "+to_string(lep_iso_min)+") * (lep_iso < "+to_string(lep_iso_max)+") ";
      }
      else if( CALC_SS_SR ){
        s_mode += " * (lep_q * alltau_q[0] < 0)";
        if( !(mode & MUISO) ) s_mode += " * (lep_iso > "+to_string(antiIso_min)+") * (lep_iso < "+to_string(antiIso_max)+") ";
      }
      else if( mode & _AI ){
        s_mode += " * (lep_iso > "+to_string(antiIso_min)+") * (lep_iso < "+to_string(antiIso_max)+")";
      }
    
    }
  }

  return s_mode + s_genmatch + s_jetmode; 
}

Int_t GlobalClass::isInCR(const Int_t mode, const Int_t ind)
{  
  Int_t returnVal=0;
  if (mode & GEN_MATCH) {
    if ( event_s->alltau_gen_match->at(ind)!=realJet ) return 0;
  }
  if( mode & JET0 ){
    if( event_s->njets >= 1 ) return 0;
  }
  if( mode & JET1){
    if( event_s->njets < 1 ) return 0;
  }
  Double_t lep_iso_min; Double_t lep_iso_max;
  Double_t isolation=0; Double_t antiIso_min; Double_t antiIso_max;
  if(CHAN==kMU) isolation=LEP_ISO_CUT;
  if(CHAN==kEL){
    isolation=LEP_ISO_CUT_ET;
    lep_iso_min = 0.02;
    lep_iso_max = 0.15;
  }else{
    lep_iso_min = 0.05;
    lep_iso_max = 0.15;
  }
  antiIso_min=isolation; antiIso_max=isolation+0.1;
  //antiIso_min=isolation+0.15; antiIso_max=isolation+0.35;
  
  if (DEBUG==2) std::cout << "In TNtupleAnalyzer::isInCR" << std::endl;

  if  ((mode & _W_JETS && CHAN==kTAU)                   && 
       ( (event_s->alltau_mt->at(ind)>70) ||(mode & NO_SR)) && //!(mode & _AI) && 
       event_s->passesDLVeto              &&
       event_s->passes3LVeto              &&
       event_s->lep_iso > TAU1_ISO_CUT    &&
       event_s->bpt_1<20                  &&
       ( ( event_s->lep_q*event_s->alltau_q->at(ind)<0 && !CALC_SS_SR ) || ( event_s->lep_q*event_s->alltau_q->at(ind)>=0 && CALC_SS_SR ) ) //for SS region check
       )
    returnVal=1;
  else if  ((mode & _W_JETS)                   && 
       ( (event_s->alltau_mt->at(ind)>70) ||(mode & NO_SR)) && // !(mode & _AI) && 
       event_s->passesDLVeto              &&
       event_s->passes3LVeto              &&
       event_s->lep_iso < isolation     &&
       event_s->bpt_1<20                  &&
       ( ( event_s->lep_q*event_s->alltau_q->at(ind)<0 && !CALC_SS_SR ) || ( event_s->lep_q*event_s->alltau_q->at(ind)>=0 && CALC_SS_SR ) ) //for SS region check
       )
    returnVal=1;
  else if  ((mode & _SS)                   && 
       ( (event_s->alltau_mt->at(ind)>70) ||(mode & NO_SR)) && // !(mode & _AI) && 
       event_s->passesDLVeto              &&
       event_s->passes3LVeto              &&
       event_s->lep_iso < isolation     &&
       event_s->bpt_1<20                  &&
       (( event_s->lep_q*event_s->alltau_q->at(ind)>=0) ))
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
	   event_s->n_iso_lep >= 1                             &&
	   event_s->passes3LVeto < 0.5                          &&
	   event_s->alltau_dRToLep->at(ind) > DR_TAU_LEP_CUT    &&
	   event_s->alltau_dRToOtherLep->at(ind) > DR_TAU_LEP_CUT    &&
	   event_s->njets>1               &&
	   event_s->bpt_1>=20)
    returnVal=1;
  else if ((mode &_QCD && mode & SR && CHAN==kTAU)                   &&
           (event_s->lep_iso>TAU1_ISO_CUT) &&
           (event_s->lep_q*event_s->alltau_q->at(ind)<=0.)
           )
    returnVal=1;
  else if ((mode &_QCD && CHAN==kTAU)                   &&
           ( (!(mode & _AI) && event_s->lep_iso>TAU1_ISO_CUT) || ((mode & _AI) && event_s->lep_iso<TAU1_ISO_CUT) ) &&
           (event_s->lep_q*event_s->alltau_q->at(ind)>=0.) &&
           event_s->passesDLVeto &&
           event_s->passes3LVeto
           )
    returnVal=1;
  else if ((mode & _QCD)                  &&
	   (  ( !CALC_SS_SR && !(mode & _AI) && event_s->alltau_mt->at(ind)<MT_CUT && event_s->lep_q*event_s->alltau_q->at(ind)>0.  && ( ( event_s->lep_iso > lep_iso_min && event_s->lep_iso<lep_iso_max) || ( mode & MUISO ) ) ) || //TRY
	      (  (CALC_SS_SR) && event_s->alltau_mt->at(ind)<MT_CUT   && event_s->lep_q*event_s->alltau_q->at(ind)<0. && ( ( event_s->lep_iso > antiIso_min && event_s->lep_iso<antiIso_max ) || ( mode & MUISO) )   ) || //TRY
              (  mode & _AI && event_s->alltau_mt->at(ind)<MT_CUT   &&   ( event_s->lep_iso > antiIso_min && event_s->lep_iso<antiIso_max )                     ) ) && //TRY
	   //	   (  ( !CALC_SS_SR && event_s->alltau_mt->at(ind)<MT_CUT   && ( event_s->lep_iso<LEP_ISO_CUT || ( mode & MUISO ) ) ) || //DEFAULT
	   //	      (  CALC_SS_SR                                     && event_s->lep_iso>LEP_ISO_CUT )   ) && //DEFAULT
           (event_s->lep_q*event_s->alltau_q->at(ind)>=0.) &&
            event_s->passesDLVeto             &&
            event_s->passes3LVeto        
	   ) {
      //  std::cout << "tttt test" << std::endl;
      returnVal=1;
    }
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

Int_t GlobalClass::getWeightIndex_pt(Double_t pt){
  for (int i=0; i<w_pt_n; i++){
    if ( pt>w_pt_v[i] && pt<w_pt_v[i+1] ) return i;
  }
  if (pt>w_pt_v[w_pt_n]) return 1e6; //overflow - one for all dimensions, though!
  //  if (mt>w_mt_v[w_mt_n]) return w_mt_n-1; //put overflow in last bin
  //  if (mt>w_mt_v[w_mt_n]) return w_mt_n; //overflow - only suitable for 1D!
  if (pt<w_pt_v[0]) return -1; //underflow

  return -1; //should never get here
}

Int_t GlobalClass::getWeightIndex_mttot(Double_t mttot){
  for (int i=0; i<w_mttot_n; i++){
    if ( mttot>w_mttot_v[i] && mttot<w_mttot_v[i+1] ) return i;
  }
  if (mttot>w_mttot_v[w_mttot_n]) return 1e6;
  if (mttot<w_mttot_v[0]) return -1; //underflow

  return -1; //should never get here
}

Int_t GlobalClass::getWeightIndex_mvis(Double_t mvis){
  for (int i=0; i<w_mvis_n; i++){
    if ( mvis>w_mvis_v[i] && mvis<w_mvis_v[i+1] ) return i;
  }
  return 1; //should never get here
}

Int_t GlobalClass::getWeightIndex_lepPt(Double_t lepPt){
  for (int i=0; i<w_lepPt_n; i++){
    if ( lepPt>w_lepPt_v[i] && lepPt<w_lepPt_v[i+1] ) return i;
  }
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

Int_t GlobalClass::getWeightBin(Double_t pt, Int_t dm){
  if(CHAN != kTAU) return ( this->getWeightIndex_pt(pt) + w_pt_n * this->getWeightIndex_dm(dm) );
  return ( this->getWeightIndex_mttot(pt) + w_mttot_n * this->getWeightIndex_dm(dm) );
}

Int_t GlobalClass::getWeightBin(const Int_t ind){
  if(CHAN != kTAU) return ( this->getWeightBin(event_s->alltau_pt->at(ind),event_s->alltau_decay->at(ind)) );
  Double_t mt_tot = TMath::Sqrt( TMath::Power(event_s->alltau_mt->at(ind),2) + TMath::Power(event_s->alltau_mt2->at(ind),2) + 2*event_s->lep_pt*event_s->alltau_pt->at(ind)*(1-TMath::Cos( TVector2::Phi_mpi_pi( event_s->lep_phi-event_s->alltau_phi->at(ind) ) ) ) ); 
  return ( this->getWeightBin(mt_tot,event_s->alltau_decay->at(ind)) );
}

Double_t GlobalClass::getFittedBinContent( const Int_t mode, vector<TGraphAsymmErrors*> fittedFFs, const Int_t ind){
  
  Int_t i_t=this->getTrackIndex(mode,ind);
  Int_t i_j=this->getNjetIndex(mode,ind);
  // std::cout<< "tracker index: " << i_t << std::endl;
  // std::cout<< "Njet index: " << i_j << std::endl;
  
  TGraphAsymmErrors *tmp = nullptr;
  if( i_t == 0 && i_j == 0 ) tmp = fittedFFs.at(0);
  if( i_t == 1 && i_j == 0 ) tmp = fittedFFs.at(1);
  if( i_t == 0 && i_j == 1 ) tmp = fittedFFs.at(2);
  if( i_t == 1 && i_j == 1 ) tmp = fittedFFs.at(3);
  if( i_t == 0 && i_j == 2 ) tmp = fittedFFs.at(4);
  if( i_t == 1 && i_j == 2 ) tmp = fittedFFs.at(5);

  double x=0; double y=0; double cont=0;
  for (int ipt=0; ipt<fitBins; ipt++){
    tmp->GetPoint( ipt + 1,x,y );
    if( event_s->alltau_pt->at(ind) < x && y>0 && y<100 ) return y;
  }

  return y;
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
  else {cout<<"getBin: Define a valid MODE!"<<std::endl;n_p=-99;n_e=-99;n_t=-99;}
  Int_t bin=i_e + i_p*n_e + i_t*n_p*n_e + i_j*n_t*n_p*n_e;
  // std::cout<<i_e<<" "<<i_p<<" "<<i_t<<" "<<bin<<" "<<std::endl;
  // std::cout << bin << std::endl;
  return(bin);// combined index of track-pt-eta bin
}

Int_t GlobalClass::nBins(const Int_t mode)
{
  /* 
  This function returns the number of bins depending on the mode.  
  */
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
  else if ( (mode & _TT) ) {
    // if (DEBUG) {
    //   std::cout << "Number of eta bins: " << n_e_TT << std::endl;
    //   std::cout << "Number of pt bins: " << n_p_TT_CR << std::endl;
    //   std::cout << "Number of decay mode bins: " << n_t_TT << std::endl;
    //   std::cout << "Number of mT bins: " << n_m_TT << std::endl;
    //   std::cout << "Number of Njet bins: " << n_j_TT_CR << std::endl;
      
    // }
    return(n_e_TT*n_p_TT_CR*n_t_TT*n_m_TT*n_j_TT_CR);
  }
  
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
  else if(mode & _QCD && mode & _AI) return N_p_QCD_AI;
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
  if (cuts & JET0){
    if ( event_s->njets!=0 ) ret=ret && 0;
  }
  if (cuts & JET1){
    if ( event_s->njets<1 ) ret=ret && 0;
  }

  return ret;
}

Double_t GlobalClass::selVal(const Int_t mode, const Int_t ind){

  if (mode & MVIS) {return event_s->alltau_mvis->at(ind);}
  else if (mode & PT)   {return event_s->alltau_pt->at(ind);}
  else if (mode & MUISO) {return event_s->lep_iso;}
  else if (mode & SVFIT) {return event_s->alltau_svfit->at(ind);}
  else if (mode & MT) {return event_s->alltau_mt->at(ind);}
  else if (mode & LEPPT) {return event_s->lep_pt;}
  else{ std::cout << "selVal: Warning: no valid variable given!" << std::endl; return -1; }

}

Int_t GlobalClass::getPInd( Int_t dm ){

  if ( dm < 5 ) return 0;
  if ( dm > 9 ) return 1;

  std::cout << "ERROR : Not a valid decay mode" << std::endl;
  return -1;

}

Int_t GlobalClass::fulfillCategory(Int_t categoryMode, Int_t ind){

  if( inclusive_selection && (CHAN==kMU || CHAN==kEL) ){
    if(event_s->alltau_mt->at(ind) > MT_CUT) return 0; 
  }
  
  if ( categoryMode & _DUMMYCAT ){
    if(event_s->alltau_mt->at(ind) > MT_CUT) return 0; 
  }  
    
  return 1;
  
}

TString GlobalClass::getCatString_noSel(Int_t categoryMode){

  if ( categoryMode & _DUMMYCAT ) return categories[0];

  return "";
  
}


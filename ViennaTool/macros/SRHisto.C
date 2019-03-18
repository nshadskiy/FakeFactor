#include "ViennaTool/interface/TSelectionAnalyzer.h"

#include <iostream>
#include <string>

using namespace std;

void SRHisto() {

  std::cout << std::endl << "***************************************" << std::endl;
  std::cout << "*             SRHisto                 *" << std::endl;
  std::cout << "***************************************" << std::endl << std::endl;

  const Int_t DOCUTS = doCuts;
  
  if(inclusive_selection){
  
    TSelectionAnalyzer *Analyzer = new TSelectionAnalyzer();
    
    Analyzer->init();

    std::vector<TString> ps;
    std::vector<TString> fl;
    if( EMB ){
      ps.push_back(preselection_data);
      ps.push_back(preselection_Wjets); 
      ps.push_back(preselection_EMB); 
      ps.push_back(preselection_TT_J_EMB); 
      ps.push_back(preselection_TT_L_EMB);
      ps.push_back(preselection_VV_J_EMB); 
      ps.push_back(preselection_VV_L_EMB);
      ps.push_back(preselection_DY_J_EMB); 
      ps.push_back(preselection_DY_L_EMB); 
      if(DOQCD) ps.push_back(preselection_QCD);

      fl.push_back(SR_data_mt); 
      fl.push_back(SR_Wjets_mt_sim); 
      fl.push_back(SR_EMB_mt_sim); 
      fl.push_back(SR_TT_J_mt_sim); 
      fl.push_back(SR_TT_L_mt_sim);
      fl.push_back(SR_VV_J_mt_sim); 
      fl.push_back(SR_VV_L_mt_sim);
      fl.push_back(SR_DY_J_mt_sim); 
      fl.push_back(SR_DY_L_mt_sim); 
      if(DOQCD) fl.push_back(SR_QCD_mt_sim);
    }else{
      ps.push_back(preselection_data);
      ps.push_back(preselection_Wjets); 
      ps.push_back(preselection_TT_T); 
      ps.push_back(preselection_TT_J); 
      ps.push_back(preselection_TT_L);
      ps.push_back(preselection_VV_T); 
      ps.push_back(preselection_VV_J); 
      ps.push_back(preselection_VV_L);
      ps.push_back(preselection_DY_TT); 
      ps.push_back(preselection_DY_J); 
      ps.push_back(preselection_DY_L); 
      if(DOQCD) ps.push_back(preselection_QCD);

      fl.push_back(SR_data_mt); 
      fl.push_back(SR_Wjets_mt_sim); 
      fl.push_back(SR_TT_T_mt_sim);
      fl.push_back(SR_TT_J_mt_sim); 
      fl.push_back(SR_TT_L_mt_sim);
      fl.push_back(SR_VV_T_mt_sim); 
      fl.push_back(SR_VV_J_mt_sim); 
      fl.push_back(SR_VV_L_mt_sim);
      fl.push_back(SR_DY_TT_mt_sim); 
      fl.push_back(SR_DY_J_mt_sim); 
      fl.push_back(SR_DY_L_mt_sim); 
      if(DOQCD) fl.push_back(SR_QCD_mt_sim);
    }
    
    
    //  if (DOQCD) fl.push_back(SR_QCD_mt_sim);

    Int_t nVARused = nVAR-1; //no muiso is needed here
    const TString r1[nVARused]={"_pt","_mt","_mvis"}; //
    const TString r2[nVARused]={ "_mt", "_mvis", "_pt"}; //"_mt2","_lepPt","_mvamet","_met","_eta", "_mttot","_mjj"};

    TString tmp,tmp2;
    for (unsigned i=0; i<ps.size(); i++){
      tmp=fl.at(i); //avoid editing fl
      Int_t categoryMode=0;
      if(!CALC_SS_SR && doSRHisto){
        
        if(!DOCUTS)Analyzer->calcBgEstSim( ps.at(i), MT|NO_SR, categoryMode, tmp.ReplaceAll(r1[0], r2[0]) );
        if(DOCUTS) for (unsigned l=0; l<NC; l++){ tmp2=tmp.ReplaceAll(r1[0], r2[0]); Analyzer->calcBgEstSim( ps.at(i), MT|NO_SR, categoryMode, tmp2.ReplaceAll("SR_","SR_cuts_"+c_text[l]+"_"), c_cuts[l]  ); }       
        if(!DOCUTS)Analyzer->calcBgEstSim( ps.at(i), MVIS, categoryMode, tmp.ReplaceAll(r1[1],r2[1]) );
        if(DOCUTS) for (unsigned l=0; l<NC; l++){ tmp2=tmp.ReplaceAll(r1[1], r2[1]); Analyzer->calcBgEstSim( ps.at(i), MVIS, categoryMode, tmp2.ReplaceAll("SR_","SR_cuts_"+c_text[l]+"_"), c_cuts[l]  ); }
        if(!DOCUTS)Analyzer->calcBgEstSim( ps.at(i), PT, categoryMode, tmp.ReplaceAll(r1[2],r2[2]) );
        if(DOCUTS) for (unsigned l=0; l<NC; l++){ tmp2=tmp.ReplaceAll(r1[2], r2[2]); Analyzer->calcBgEstSim( ps.at(i), PT, categoryMode, tmp2.ReplaceAll("SR_","SR_cuts_"+c_text[l]+"_"), c_cuts[l]  ); }
        
        tmp=fl.at(i); Analyzer->calcBgEstSim( ps.at(i), MVIS|_AI, categoryMode, tmp.ReplaceAll(r2[0], "_mvis_AI") );
        if(use_svfit){
          tmp=fl.at(i); Analyzer->calcBgEstSim( ps.at(i), SVFIT, categoryMode, tmp.ReplaceAll(r2[0], "_svfit"));
        }
      }

      else if(CALC_SS_SR && doSRHisto){
        if(CALC_SS_SR ){tmp2=tmp.ReplaceAll(r1[0],r2[0]); tmp2.ReplaceAll( "SR_", "SS_SR_" );     Analyzer->calcBgEstSim( ps.at(i), MT|NO_SR|_SS, categoryMode, tmp2 );}  //QCD SS
        if(CALC_SS_SR){tmp2=tmp.ReplaceAll(r1[1],r2[1]); tmp2.ReplaceAll( "SR_", "SS_SR_" );     Analyzer->calcBgEstSim( ps.at(i), MVIS|_SS, categoryMode, tmp2 );}  //QCD SS
        if(CALC_SS_SR){tmp2=tmp.ReplaceAll(r1[2],r2[2]); tmp2.ReplaceAll( "SR_", "SS_SR_" );     Analyzer->calcBgEstSim( ps.at(i),PT|_SS, categoryMode, tmp2 );}  //QCD SS
      }
      
    }

    if(inclusive_selection){
      
      TString modes[] = {"l","t","t_alt"};
      Int_t nmodes = 3;
      int nSA; if(useVV){nSA=nSAMPLES;}else{nSA=nSAMPLES-4;} //signal sample is also subtracted
      const TString *ssa=vsuff;
      //////////////////////////////////////////////////////////////////////////////////////////////////////
      //Get AI mvis histos with MC subtracted
      if(!DOMC){
        for (int iv=1; iv<2; iv++){ //loop over mt, mvis, pt
          TFile outfile ( path_sim+s_SR+"_data"+r2[iv]+"_AI_MCsubtracted.root","RECREATE"  );
          cout << "WRITING: " << path_sim+s_SR+"_data"+r2[iv]+"_AI_MCsubtracted.root" << endl;
          TFile infile( path_sim+s_SR+"_data"+r2[iv]+"_AI.root"  );
          if(infile.IsZombie() ){cout << path_sim+s_SR+"_data"+r2[iv]+"_AI.root" << " not available" << endl; break;}
          for(int imode=0; imode<nmodes; imode++){
            TH1D* inhist = (TH1D*)infile.Get("hh_"+modes[imode]+"_mvis");
            TH1D* outhist = (TH1D*)inhist->Clone("hh_"+modes[imode]+"_mvis_MCsubtracted"); outhist->Add(inhist,-1);
            for (int is=0; is<nSA; is++){ //loop over samples
              if(ssa[is]=="QCD") continue;
              cout << "WRITING: " << path_sim+s_SR+"_"+ssa[is]+r2[iv]+"_AI.root" << endl;
              TFile tmp(path_sim+s_SR+"_"+ssa[is]+r2[iv]+"_AI.root"  );
              if(tmp.IsZombie() ){cout << path_sim+s_SR+"_"+ssa[is]+r2[iv]+"_AI.root" << " not available"<<  endl; continue;}
              TH1D *tmphist = (TH1D*)tmp.Get("hh_"+modes[imode]+r2[iv]);
              /*for(int i=1; i<tmphist->GetNbinsX();i++){
                tmphist->SetBinContent( i, tmphist->GetBinContent(i)*0.9 );
                }*/
              outhist->Add(tmphist);
              tmp.Close();
            }
            outfile.cd();
            inhist->Write();
            outhist->Write();
          }
          infile.Close();outfile.Close();
        }
      }
      
      ////////////////////////////////////////////////////////////////////////////////////////////////////////
      //Get all histos with MC subtracted
      if(!DOMC){
        nVARused=3;
        for (int iv=0; iv<nVARused; iv++){ //loop over mt, mvis, pt
          TFile outfile ( path_sim+s_SR+"_data"+r2[iv]+"_MCsubtracted.root","RECREATE"  );
          TFile infile( path_sim+s_SR+"_data"+r2[iv]+".root"  );
          if(infile.IsZombie() ){cout << path_sim+s_SR+"_data"+r2[iv]+".root" << " not available" << endl; break;}
          for(int imode=0; imode<nmodes; imode++){
            TH1D* inhist = (TH1D*)infile.Get("hh_"+modes[imode]+r2[iv]);
            TH1D* outhist = (TH1D*)inhist->Clone("hh_"+modes[imode]+"_"+r2[iv]+"MCsubtracted"); outhist->Add(inhist,-1);
            for (int is=0; is<nSA; is++){ //loop over samples
              if(ssa[is]=="QCD") continue;
              TFile tmp(path_sim+s_SR+"_"+ssa[is]+r2[iv]+".root"  );
              if(tmp.IsZombie() ){cout << path_sim+s_SR+"_"+ssa[is]+r2[iv]+".root" << " not available"<<  endl; continue;}
              TH1D *tmphist = (TH1D*)tmp.Get("hh_"+modes[imode]+r2[iv]);
              outhist->Add(tmphist);
              tmp.Close();
            }
            outfile.cd();
            inhist->Write();
            outhist->Write();
          }
          infile.Close();outfile.Close();
        }
      }
     
      
    }
        
    delete Analyzer;


  } //inclusive selection
}
  
#ifndef __CINT__
int main(int argc, char* argv[]) {
  SRHisto();    
}
#endif

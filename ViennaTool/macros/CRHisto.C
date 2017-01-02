#include "ViennaTool/interface/TSelectionAnalyzer.h"

#include <iostream>
#include <string>
#include "TStyle.h"

using namespace std;

void CRHisto(int doCalc, int nCR, int nQU) {

  std::cout << std::endl << "***************************************" << std::endl;
  std::cout << "*             CRHisto                 *" << std::endl;
  std::cout << "***************************************" << std::endl << std::endl;

  TSelectionAnalyzer* Analyzer = new TSelectionAnalyzer();
  Analyzer->init();

  TString m_preselection_data=preselection_data;
  if(DOMC) m_preselection_data=preselection_MCsum;
  TString m_path_img=path_img_data;

  const int nVARused = nVARCR; //mt,mvis,pt,muiso
  const int ivar[4]={MT|NO_SR,MVIS,PT,MUISO};

  const int icr[nCR]=        {_W_JETS , _DY  , _TT  , _QCD};
  const TString scr[nCR]=    {s_Wjets, s_DY , s_TT , s_QCD};

  /*
  const int nCR=3;
  const int icr[nCR]=        {_W_JETS , _DY  , _QCD};
  const TString scr[nCR]=    {s_Wjets, s_DY , s_QCD};
  */

  /*
  const int nCR=1;
  const int icr[nCR]=        {_QCD};
  const TString scr[nCR]=    {s_QCD};
  */

  int nSA; if(useVV){nSA=nSAMPLES;}else{nSA=nSAMPLES-3;}
  const TString *ssa=vsuff;

  const TString squ[nQU]=    {s_loose, s_tight, s_loose_tt};

  if(doCRHisto){
    
    for (int ic=0; ic<nCR; ic++){ //loop over CRs
      if ( !doCalc ) break;
      // nVAR is set to 3, one has to increase the number if muiso or zpt or any other variable is required
      for (int iv=0; iv<nVARused; iv++){ //loop over mt, mvis, pt
        for (int is=0; is<nSA; is++){ //loop over samples
          Analyzer->getCRHisto(path_presel+s_preselection+"_"+ssa[is]+".root", ivar[iv]|icr[ic] , path_sim+s_CR+"_"+scr[ic]+"_"+tvarCR[iv]+"_"+ssa[is]+".root"  );
        }
        if(!DOMC) Analyzer->getCRHisto(  m_preselection_data                           , ivar[iv]|icr[ic] , path_sim+s_CR+"_"+scr[ic]+"_"+tvarCR[iv]+"_data.root"  );
        else Analyzer->getCRHisto(  m_preselection_data                           , ivar[iv]|icr[ic] , path_sim+s_CR+"_"+scr[ic]+"_"+tvarCR[iv]+"_MCsum.root"  );
      }
    }
    
    for (int ic=3; ic<nCR; ic++){ //loop over CRs
      for (int is=0; is<nSA; is++){ //loop over samples
        Analyzer->getCRHisto(path_presel+s_preselection+"_"+ssa[is]+".root", icr[ic]|LEPPT , path_sim+s_CR+"_"+scr[ic]+"_lepPt_"+ssa[is]+".root"  );
      }
      if(!DOMC) Analyzer->getCRHisto(  m_preselection_data                           , icr[ic]|LEPPT , path_sim+s_CR+"_"+scr[ic]+"_lepPt_data.root"  );
    }
    
    //get AI CR histogramms for QCD mvis nonclosure
    for (int ic=3; ic<nCR; ic++){ //loop over CRs
      if ( !doCalc ) break;
      for (int iv=1; iv<2; iv++){ //loop over mt, mvis, pt
        for (int is=0; is<nSA; is++){ //loop over samples
          Analyzer->getCRHisto(path_presel+s_preselection+"_"+ssa[is]+".root", ivar[iv]|icr[ic]|_AI , path_sim+s_CR+"_"+scr[ic]+"_"+tvarCR[iv]+"_AI_"+ssa[is]+".root"  );
        }
        if(!DOMC) Analyzer->getCRHisto(  m_preselection_data                           , ivar[iv]|icr[ic]|_AI , path_sim+s_CR+"_"+scr[ic]+"_"+tvarCR[iv]+"_AI_data.root"  );
        else Analyzer->getCRHisto(  m_preselection_data                           , ivar[iv]|icr[ic]|_AI , path_sim+s_CR+"_"+scr[ic]+"_"+tvarCR[iv]+"_AI_MCsum.root"  );
      }
    }
    
    //get AI CR histogramms for QCD mvis nonclosure
    if(CHAN==kTAU){
      for (int ic=3; ic<nCR; ic++){ //loop over CRs
        for (int is=0; is<nSA; is++){ //loop over samples
          Analyzer->getCRHisto(path_presel+s_preselection+"_"+ssa[is]+".root", LEPPT|icr[ic]|_AI , path_sim+s_CR+"_"+scr[ic]+"_lepPt_AI_"+ssa[is]+".root"  );
        }
        if(!DOMC) Analyzer->getCRHisto(  m_preselection_data                           , LEPPT|icr[ic]|_AI , path_sim+s_CR+"_"+scr[ic]+"_lepPt_AI_data.root"  );
      }
    }
    
    //get SS Wjet histogramms for SS mvis Wjets closure
    for (int ic=0; ic<1; ic++){ //loop over CRs
      if ( !doCalc ) break;
      for (int iv=1; iv<2; iv++){ //loop over mt, mvis, pt
        for (int is=0; is<nSA; is++){ //loop over samples
          Analyzer->getCRHisto(path_presel+s_preselection+"_"+ssa[is]+".root", ivar[iv]|icr[ic]|_AI , path_sim+s_CR+"_"+scr[ic]+"_"+tvarCR[iv]+"_SS_"+ssa[is]+".root"  );
        }
        if(!DOMC) Analyzer->getCRHisto(  m_preselection_data                           , ivar[iv]|icr[ic]|_AI , path_sim+s_CR+"_"+scr[ic]+"_"+tvarCR[iv]+"_SS_data.root"  );
        else Analyzer->getCRHisto(  m_preselection_data                           , ivar[iv]|icr[ic]|_AI , path_sim+s_CR+"_"+scr[ic]+"_"+tvarCR[iv]+"_SS_MCsum.root"  );
      }
    }
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //get Wjet SS histos for corrections
    Analyzer->getCRHisto(path_presel+s_preselection+"_Wjets.root", MVIS|_W_JETS|_SS , path_sim+s_CR+"_Wjets_mvis_Wjets_SS_SR.root"  );
    Analyzer->getCRHisto(path_presel+s_preselection+"_Wjets.root", MT|NO_SR|_W_JETS|_SS , path_sim+s_CR+"_Wjets_mt_Wjets_SS_SR.root"  );
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //TEST
    TString modes[] = {"l","t","ltt"};
    Int_t nmodes = 3;
    if(!DOMC){
      for (int ic=3; ic<nCR; ic++){ //loop over CRs
        TFile outfile ( path_sim+s_CR+"_"+scr[ic]+"_lepPt_data_MCsubtracted.root","RECREATE"  );
        TFile infile( path_sim+s_CR+"_"+scr[ic]+"_lepPt_data.root"  );
        for(int imode=0; imode<nmodes; imode++){
          TH1D* inhist = (TH1D*)infile.Get("hh_"+modes[imode]+"_lepPt");
          TH1D* outhist = (TH1D*)inhist->Clone("hh_"+modes[imode]+"_lepPt_MCsubtracted"); outhist->Add(inhist,-1);
          for (int is=0; is<nSA; is++){ //loop over samples
            if(scr[ic] == ssa[is]) continue;
            TFile tmp(path_sim+s_CR+"_"+scr[ic]+"_lepPt_"+ssa[is]+".root"  );
            TH1D *tmphist = (TH1D*)tmp.Get("hh_"+modes[imode]+"_lepPt");
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
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //get QCD AI MC subtracted CRs
    if(!DOMC){
      for (int ic=3; ic<nCR; ic++){ //loop over CRs
        if ( !doCalc ) break;
        for (int iv=1; iv<2; iv++){ //loop over mt, mvis, pt
          TFile outfile ( path_sim+s_CR+"_"+scr[ic]+"_"+tvarCR[iv]+"_AI_data_MCsubtracted.root","RECREATE"  );
          TFile infile( path_sim+s_CR+"_"+scr[ic]+"_"+tvarCR[iv]+"_AI_data.root"  );
          for(int imode=0; imode<nmodes; imode++){
            TH1D* inhist = (TH1D*)infile.Get("hh_"+modes[imode]+"_"+tvarCR[iv]);
            TH1D* outhist = (TH1D*)inhist->Clone("hh_"+modes[imode]+"_"+tvarCR[iv]+"_MCsubtracted"); outhist->Add(inhist,-1);
            for (int is=0; is<nSA; is++){ //loop over samples
              if(scr[ic] == ssa[is]) continue;
              TFile tmp(path_sim+s_CR+"_"+scr[ic]+"_"+tvarCR[iv]+"_AI_"+ssa[is]+".root"  );
              TH1D *tmphist = (TH1D*)tmp.Get("hh_"+modes[imode]+"_"+tvarCR[iv]);
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
    }
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //get Wjets SS MC subtracted CRs
    if(!DOMC){
      for (int ic=0; ic<1; ic++){ //loop over CRs
        if ( !doCalc ) break;
        for (int iv=1; iv<2; iv++){ //loop over mt, mvis, pt
          TFile outfile ( path_sim+s_CR+"_"+scr[ic]+"_"+tvarCR[iv]+"_SS_data_MCsubtracted.root","RECREATE"  );
          TFile infile( path_sim+s_CR+"_"+scr[ic]+"_"+tvarCR[iv]+"_SS_data.root"  );
          for(int imode=0; imode<nmodes; imode++){
            TH1D* inhist = (TH1D*)infile.Get("hh_"+modes[imode]+"_"+tvarCR[iv]);
            TH1D* outhist = (TH1D*)inhist->Clone("hh_"+modes[imode]+"_"+tvarCR[iv]+"_MCsubtracted"); outhist->Add(inhist,-1);
            for (int is=0; is<nSA; is++){ //loop over samples
              if(scr[ic] == ssa[is]) continue;
              TFile tmp(path_sim+s_CR+"_"+scr[ic]+"_"+tvarCR[iv]+"_SS_"+ssa[is]+".root"  );
              TH1D *tmphist = (TH1D*)tmp.Get("hh_"+modes[imode]+"_"+tvarCR[iv]);
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
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //get general data-MC CRs
    if(!DOMC){
      for (int ic=0; ic<nCR; ic++){ //loop over CRs
        if ( !doCalc ) break;
        // nVAR is set to 3, one has to increase the number if muiso or zpt or any other variable is required
        for (int iv=0; iv<nVARused; iv++){ //loop over mt, mvis, pt
          TFile outfile ( path_sim+s_CR+"_"+scr[ic]+"_"+tvarCR[iv]+"_data_MCsubtracted.root","RECREATE"  );
          TFile infile( path_sim+s_CR+"_"+scr[ic]+"_"+tvarCR[iv]+"_data.root"  );
          for(int imode=0; imode<nmodes; imode++){
            TH1D* inhist = (TH1D*)infile.Get("hh_"+modes[imode]+"_"+tvarCR[iv]);
            TH1D* outhist = (TH1D*)inhist->Clone("hh_"+modes[imode]+"_"+tvarCR[iv]+"_MCsubtracted"); outhist->Add(inhist,-1);
            for (int is=0; is<nSA; is++){ //loop over samples
              if(scr[ic] == ssa[is]) continue;
              TFile tmp(path_sim+s_CR+"_"+scr[ic]+"_"+tvarCR[iv]+"_"+ssa[is]+".root"  );
              TH1D *tmphist = (TH1D*)tmp.Get("hh_"+modes[imode]+"_"+tvarCR[iv]);
              if(ivar[iv] & MUISO){
                for(int i=1; i<tmphist->GetNbinsX();i++){
                  if(tmphist->GetBinContent(i) > 3){
                    Double_t err1=tmphist->GetBinError(i)/tmphist->GetBinContent(i);
                    Double_t err2=0.25;
                    tmphist->SetBinError( i,TMath::Sqrt(TMath::Power(err1,2)+TMath::Power(err2,2))*tmphist->GetBinContent(i) );
                  }
                }
              }
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
    else{
      for (int ic=0; ic<nCR; ic++){ //loop over CRs
        if ( !doCalc ) break;
        for (int iv=0; iv<nVARused; iv++){ //loop over mt, mvis, pt
          TFile outfile ( path_sim+s_CR+"_"+scr[ic]+"_"+tvarCR[iv]+"_MCsum_MCsubtracted.root","RECREATE"  );
          TFile infile( path_sim+s_CR+"_"+scr[ic]+"_"+tvarCR[iv]+"_MCsum.root"  );
          for(int imode=0; imode<nmodes; imode++){
            TH1D* inhist = (TH1D*)infile.Get("hh_"+modes[imode]+"_"+tvarCR[iv]);
            TH1D* outhist = (TH1D*)inhist->Clone("hh_"+modes[imode]+"_"+tvarCR[iv]+"_MCsubtracted"); outhist->Add(inhist,-1);
            for (int is=0; is<nSA; is++){ //loop over samples
              if(scr[ic] == ssa[is]) continue;
              TFile tmp(path_sim+s_CR+"_"+scr[ic]+"_"+tvarCR[iv]+"_"+ssa[is]+".root"  );
              TH1D *tmphist = (TH1D*)tmp.Get("hh_"+modes[imode]+"_"+tvarCR[iv]);
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
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  } //doCRHisto
  
  cout << "Now producing CR plots..." << endl;

  
  std::vector<TString> ty; for (int it=0; it<nSA; it++) ty.push_back(vsuff[it]);

  for (int ic=0; ic<nCR; ic++){ //loop over CRs
    for (int iv=0; iv<nVARused-1; iv++){ //loop over mt, mvis, pt
      for (int iq=0; iq<nQU; iq++){ //loop over loose/tight
	std::vector<TString> cr; 
	for (int is=0; is<nSA; is++){ cr.push_back(path_sim+s_CR+"_"+scr[ic]+"_"+tvarCR[iv]+"_"+ssa[is]+".root"); }
	Analyzer->plotCR(cr, ty, path_sim+s_CR+"_"+scr[ic]+"_"+tvarCR[iv]+"_data.root", squ[iq], scr[ic]    , m_path_img+s_CR+"_"+scr[ic]+"_"+squ[iq]+"_"+tvarCR[iv], tvarCR_l[iv] ); 
      }
    }
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //This is not needed now
  /*
  if(CHAN==kTAU){
    cout << "Now producing SS signal plots..." << endl;
    
    for (int iv=0; iv<nVAR; iv++){ //loop over mt, mvis, pt
      for (int iq=0; iq<nQU; iq++){ //loop over loose/tight
        std::vector<TString> cr; 
        for (int is=0; is<nSA; is++){ cr.push_back(path_sim+"SS_SR_"+ssa[is]+"_"+tvar[iv]+".root"); }
        Analyzer->plotCR(cr, ty, path_sim+"SS_SR_data_"+tvar[iv]+".root", squ[iq],   ""  , m_path_img+"SS_SR_"+squ[iq]+"_"+tvar[iv], tvar_l[iv] ); 
      }
    }
    
    cout << "Now producing SR antiIso signal plots..." << endl;
    
    for (int iv=0; iv<nVAR; iv++){ //loop over mt, mvis, pt
      for (int iq=0; iq<nQU; iq++){ //loop over loose/tight
        std::vector<TString> cr; 
        for (int is=0; is<nSA; is++){ cr.push_back(path_sim+"SR_antiIso_"+ssa[is]+"_"+tvar[iv]+".root"); }
        Analyzer->plotCR(cr, ty, path_sim+"SR_antiIso_data_"+tvar[iv]+".root", squ[iq],   ""  , m_path_img+"SR_antiIso_"+squ[iq]+"_"+tvar[iv], tvar_l[iv] ); 
      }
    }
    
    cout << "Now producing SS SR antiIso signal plots..." << endl;
    
    for (int iv=0; iv<nVAR; iv++){ //loop over mt, mvis, pt
      for (int iq=0; iq<nQU; iq++){ //loop over loose/tight
        std::vector<TString> cr; 
        for (int is=0; is<nSA; is++){ cr.push_back(path_sim+"SS_SR_antiIso_"+ssa[is]+"_"+tvar[iv]+".root"); }
        Analyzer->plotCR(cr, ty, path_sim+"SS_SR_antiIso_data_"+tvar[iv]+".root", squ[iq],   ""  , m_path_img+"SS_SR_antiIso_"+squ[iq]+"_"+tvar[iv], tvar_l[iv] ); 
      }
    }

    }*/

  delete Analyzer;

  
}
  
#ifndef __CINT__
int main(int argc, char* argv[]) {
  int doCalc = argc > 1 ? atoi(argv[1]) : 1;
  int nCR = argc > 2 ? atoi(argv[2]) : 4;
  int nQU = argc > 3 ? atoi(argv[3]) : 3;
  CRHisto(doCalc,nCR,nQU);    
}
#endif

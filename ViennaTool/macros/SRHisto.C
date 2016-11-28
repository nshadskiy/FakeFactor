#include "ViennaTool/interface/TSelectionAnalyzer.h"

#include <iostream>
#include <string>

using namespace std;

void SRHisto() {

  std::cout << std::endl << "***************************************" << std::endl;
  std::cout << "*             SRHisto                 *" << std::endl;
  std::cout << "***************************************" << std::endl << std::endl;

  const Int_t DOCUTS = doCuts;
  
  for(Int_t icat=0; icat<nCAT; icat++){
  //for(Int_t icat=6; icat<nCAT; icat++){
    if(inclusive_selection && icat>0) continue;
  
    TSelectionAnalyzer *Analyzer = new TSelectionAnalyzer();
    
    Analyzer->init();

    std::vector<TString> ps;
    ps.push_back(preselection_data);
    ps.push_back(preselection_Wjets); ps.push_back(preselection_TT_T); ps.push_back(preselection_TT_J); ps.push_back(preselection_TT_L);
    if( CHAN!=kTAU ) {ps.push_back(preselection_VV_T); ps.push_back(preselection_VV_J); ps.push_back(preselection_VV_L);}
    ps.push_back(preselection_DY_TT); ps.push_back(preselection_DY_J); ps.push_back(preselection_DY_L); 
    ps.push_back(preselection_QCD);
    ps.push_back(preselection_signal);
    //  if (DOQCD) ps.push_back(preselection_QCD);

    std::vector<TString> fl;
    fl.push_back(SR_data_mt); 
    fl.push_back(SR_Wjets_mt_sim); fl.push_back(SR_TT_T_mt_sim); fl.push_back(SR_TT_J_mt_sim); fl.push_back(SR_TT_L_mt_sim);
    if( CHAN!=kTAU ) {fl.push_back(SR_VV_T_mt_sim); fl.push_back(SR_VV_J_mt_sim); fl.push_back(SR_VV_L_mt_sim);}
    fl.push_back(SR_DY_TT_mt_sim); fl.push_back(SR_DY_J_mt_sim); fl.push_back(SR_DY_L_mt_sim); 
    fl.push_back(SR_QCD_mt_sim);
    fl.push_back(SR_signal_mt_sim);
    
    //  if (DOQCD) fl.push_back(SR_QCD_mt_sim);

    Int_t nVARused = nVAR-1; //no muiso is needed here
    const TString r1[nVARused]={"_pt","_mt","_mvis","_pt","_mt2","_lepPt","_mvamet", "_met","_eta","_mttot"};
    const TString r2[nVARused]={ "_mt", "_mvis", "_pt","_mt2","_lepPt","_mvamet","_met","_eta", "_mttot","_mjj"};

    TString tmp,tmp2;
    for (unsigned i=0; i<ps.size(); i++){
      tmp=fl.at(i); //avoid editing fl
      Int_t categoryMode=0;
      if(!inclusive_selection){
        tmp.ReplaceAll( ".root",categories[icat]+".root" );
        categoryMode=catMode[icat];
      }
      if(!CALC_SS_SR && doSRHisto){
        if(!DOCUTS)Analyzer->calcBgEstSim( ps.at(i), MT|NO_SR, categoryMode, tmp.ReplaceAll(r1[0], r2[0]) );
        if(DOCUTS) for (unsigned l=0; l<NC; l++){ tmp2=tmp.ReplaceAll(r1[0], r2[0]); Analyzer->calcBgEstSim( ps.at(i), MT|NO_SR, categoryMode, tmp2.ReplaceAll("SR_","SR_cuts_"+c_text[l]+"_"), c_cuts[l]  ); }       
        if(!DOCUTS)Analyzer->calcBgEstSim( ps.at(i), MVIS, categoryMode, tmp.ReplaceAll(r1[1],r2[1]) );
        if(DOCUTS) for (unsigned l=0; l<NC; l++){ tmp2=tmp.ReplaceAll(r1[1], r2[1]); Analyzer->calcBgEstSim( ps.at(i), MVIS, categoryMode, tmp2.ReplaceAll("SR_","SR_cuts_"+c_text[l]+"_"), c_cuts[l]  ); }
        if(!DOCUTS)Analyzer->calcBgEstSim( ps.at(i), PT, categoryMode, tmp.ReplaceAll(r1[2],r2[2]) );
        if(DOCUTS) for (unsigned l=0; l<NC; l++){ tmp2=tmp.ReplaceAll(r1[2], r2[2]); Analyzer->calcBgEstSim( ps.at(i), PT, categoryMode, tmp2.ReplaceAll("SR_","SR_cuts_"+c_text[l]+"_"), c_cuts[l]  ); }
        if(!DOCUTS)Analyzer->calcBgEstSim( ps.at(i), M2T, categoryMode, tmp.ReplaceAll(r1[3],r2[3]) );
        if(DOCUTS) for (unsigned l=0; l<NC; l++){ tmp2=tmp.ReplaceAll(r1[3], r2[3]); Analyzer->calcBgEstSim( ps.at(i), M2T, categoryMode, tmp2.ReplaceAll("SR_","SR_cuts_"+c_text[l]+"_"), c_cuts[l]  ); }
        if(!DOCUTS) Analyzer->calcBgEstSim( ps.at(i), LEPPT, categoryMode, tmp.ReplaceAll(r1[4],r2[4]) );
        if(DOCUTS) for (unsigned l=0; l<NC; l++){ tmp2=tmp.ReplaceAll(r1[4], r2[4]); Analyzer->calcBgEstSim( ps.at(i), LEPPT, categoryMode, tmp2.ReplaceAll("SR_","SR_cuts_"+c_text[l]+"_"), c_cuts[l]  ); }
        if(!DOCUTS) Analyzer->calcBgEstSim( ps.at(i), MVAMET|NO_SR, categoryMode, tmp.ReplaceAll(r1[5],r2[5]) );
        if(DOCUTS) for (unsigned l=0; l<NC; l++){ tmp2=tmp.ReplaceAll(r1[5], r2[5]); Analyzer->calcBgEstSim( ps.at(i), MVAMET, categoryMode, tmp2.ReplaceAll("SR_","SR_cuts_"+c_text[l]+"_"), c_cuts[l]  ); }
        if(!DOCUTS) Analyzer->calcBgEstSim( ps.at(i), MET|NO_SR, categoryMode, tmp.ReplaceAll(r1[6],r2[6]) );
        if(!DOCUTS) Analyzer->calcBgEstSim( ps.at(i), ETA, categoryMode, tmp.ReplaceAll(r1[7],r2[7]) );
        if(!DOCUTS) Analyzer->calcBgEstSim( ps.at(i), MMTOT, categoryMode, tmp.ReplaceAll(r1[8],r2[8]) );
        if( (categoryMode & _VBFLOW) || (categoryMode & _VBFLOW) || (categoryMode & _VBFLOW) ){
          if(!DOCUTS) Analyzer->calcBgEstSim( ps.at(i), MJJ, categoryMode, tmp.ReplaceAll(r1[9],r2[9]) );
        }
        tmp=fl.at(i); if(!inclusive_selection){tmp.ReplaceAll( ".root",categories[icat]+".root" );} Analyzer->calcBgEstSim( ps.at(i), MVIS|_AI, categoryMode, tmp.ReplaceAll(r2[0], "_mvis_AI") );
        if(use_svfit){
          tmp=fl.at(i); if(!inclusive_selection){tmp.ReplaceAll( ".root",categories[icat]+".root" );}
          Analyzer->calcBgEstSim( ps.at(i), SVFIT, categoryMode, tmp.ReplaceAll(r2[0], "_svfit"));
        }
      }

      else if(CALC_SS_SR && doSRHisto){
        if(CALC_SS_SR ){tmp2=tmp.ReplaceAll(r1[0],r2[0]); tmp2.ReplaceAll( "SR_", "SS_SR_" );     Analyzer->calcBgEstSim( ps.at(i), MT|NO_SR|_SS, categoryMode, tmp2 );}  //QCD SS
        if(CALC_SS_SR){tmp2=tmp.ReplaceAll(r1[1],r2[1]); tmp2.ReplaceAll( "SR_", "SS_SR_" );     Analyzer->calcBgEstSim( ps.at(i), MVIS|_SS, categoryMode, tmp2 );}  //QCD SS
        if(CALC_SS_SR){tmp2=tmp.ReplaceAll(r1[2],r2[2]); tmp2.ReplaceAll( "SR_", "SS_SR_" );     Analyzer->calcBgEstSim( ps.at(i),PT|_SS, categoryMode, tmp2 );}  //QCD SS
      }
      
    }

    if(inclusive_selection){

      //////////////////////////////////////////////////////////////////////////////////////////////////////
      //Get AI mvis histos with MC subtracted
      TString modes[] = {"l","t","ltt"};
      Int_t nmodes = 3;
      int nSA; if(useVV){nSA=nSAMPLES-1;}else{nSA=nSAMPLES-4;} //signal sample is also subtracted
      const TString *ssa=vsuff;
      if(!DOMC){
        if ( !doCalc ) break;
        for (int iv=1; iv<2; iv++){ //loop over mt, mvis, pt
          TFile outfile ( path_sim+s_SR+"_data"+r2[iv]+"_AI_MCsubtracted.root","RECREATE"  );
          TFile infile( path_sim+s_SR+"_data"+r2[iv]+"_AI.root"  );
          if(infile.IsZombie() ){cout << path_sim+s_SR+"_data"+r2[iv]+"_AI.root" << " not available" << endl; break;}
          for(int imode=0; imode<nmodes; imode++){
            TH1D* inhist = (TH1D*)infile.Get("hh_"+modes[imode]+"_mvis");
            TH1D* outhist = (TH1D*)inhist->Clone("hh_"+modes[imode]+"_mvis_MCsubtracted"); outhist->Add(inhist,-1);
            for (int is=0; is<nSA; is++){ //loop over samples
              if(ssa[is]=="QCD") continue;
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
        if ( !doCalc ) break;
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
      
      cout << endl << "Now saving sums..." << endl;
      
      //  const int nVARused=3;
      const unsigned nSR=3;
      //  const int NC=5;
      TH1D* hsum[nVARused][nSR];
      TH1D* hsum_cuts[nVARused][nSR][NC];
      TH1D* hsum_woQCD[nVARused][nSR];
      TH1D* hsum_cuts_woQCD[nVARused][nSR][NC];
      TH1D* hsum_SS[nVARused][nSR];
      
      TString hn[nSR]={"hh_t_","hh_l_","hh_a_"};
      
      for (unsigned j=0; j<nSR; j++){ 
        for(unsigned k=0; k<nVARused; k++){
          TString catString="";
          if(!inclusive_selection) catString=categories[icat];
          hsum[k][j] = new TH1D(hn[j] + tvar[k],"",nbins[k],hist_min[k],hist_max[k]);
          hsum_woQCD[k][j] = new TH1D( *hsum[k][j] ); //clone the above
          hsum_SS[k][j]    = new TH1D( *hsum[k][j] ); //clone the above
          if (DOCUTS){
            for(unsigned l=0; l<NC; l++){
              //	  hsum_cuts[k][j][l] = new TH1D(hn[j] + tvar[k],"",nbins[k],hist_min[k],hist_max[k]);
              hsum_cuts[k][j][l] = new TH1D( *hsum[k][j] );
              hsum_cuts_woQCD[k][j][l] = new TH1D( *hsum_cuts[k][j][l] ); //clone the above
            }
          }
          
        }
      }

      for (unsigned i=0; i<ps.size(); i++){
        TString tmp=fl.at(i);
        if(!inclusive_selection) tmp.ReplaceAll( ".root",categories[icat]+".root" );
        
        if (tmp.Contains("_data_")) continue; //do not add data to MC sum!
        
        for (unsigned k=0; k<nVARused; k++){
          
          TFile f( tmp.ReplaceAll( r1[k],r2[k] ) );
          for (unsigned j=0; j<nSR; j++){
            hsum[k][j]->Add( (TH1D*) f.Get( hn[j] + tvar[k] ) );
            if ( !tmp.Contains("_QCD_") ) hsum_woQCD[k][j]->Add( (TH1D*) f.Get( hn[j] + tvar[k] ) );
            tmp2=tmp; TFile fSS( tmp2.ReplaceAll( "SR_", "SS_SR_" ) );
            hsum_SS[k][j]->Add( (TH1D*) fSS.Get( hn[j] + tvar[k] ) );
            fSS.Close();
            
            if (DOCUTS){
              for(unsigned l=0; l<NC; l++){
                tmp2=tmp; TFile f2( tmp2.ReplaceAll( "SR_","SR_cuts_"+c_text[l]+"_" ) );
                hsum_cuts[k][j][l]->Add( (TH1D*) f2.Get( hn[j] + tvar[k] ) );
                if ( !tmp.Contains("_QCD_") ) hsum_cuts_woQCD[k][j][l]->Add( (TH1D*) f2.Get( hn[j] + tvar[k] ) );
                f2.Close();
              }
            }
            
          }
          f.Close();
        }
      }

      tmp=SR_MCsum_mt;
      if(!inclusive_selection) { tmp.ReplaceAll(".root", categories[icat]+".root"); }
      
      for (unsigned k=0; k<nVARused; k++){
        TFile* fout=new TFile(tmp.ReplaceAll( r1[k],r2[k] ),"RECREATE");
        for (unsigned j=0; j<nSR; j++){
          hsum[k][j]->Write();
        }
        fout->Close();
      }
      tmp=SR_MCsum_woQCD_mt;
      if(!inclusive_selection) { tmp.ReplaceAll(".root", categories[icat]+".root"); }
      for (unsigned k=0; k<nVARused; k++){
        TFile* fout=new TFile(tmp.ReplaceAll( r1[k],r2[k] ),"RECREATE");
        for (unsigned j=0; j<nSR; j++){
          hsum_woQCD[k][j]->Write();
        }
        fout->Close();
      }

      //write sum in root file: one per background and var (but all 3 regions in one)
      if (DOCUTS){
        tmp=SR_MCsum_mt;
        if(!inclusive_selection) { tmp.ReplaceAll(".root", categories[icat]+".root"); }
        for (unsigned k=0; k<nVARused; k++){
          tmp.ReplaceAll( r1[k],r2[k] );
          
          for(unsigned l=0; l<NC; l++){
            tmp2=tmp;
            TFile* fout=new TFile( tmp2.ReplaceAll( "SR_","SR_cuts_"+c_text[l]+"_") , "RECREATE" );
            
            for (unsigned j=0; j<nSR; j++){
              hsum_cuts[k][j][l]->Write();
            }
            fout->Close();
          }
        }
      }

      if (DOCUTS){
        tmp=SR_MCsum_woQCD_mt;
        if(!inclusive_selection) { tmp.ReplaceAll(".root", categories[icat]+".root"); }
        for (unsigned k=0; k<nVARused; k++){
          tmp.ReplaceAll( r1[k],r2[k] );
          
          for(unsigned l=0; l<NC; l++){
            tmp2=tmp;
            TFile* fout=new TFile( tmp2.ReplaceAll( "SR_","SR_cuts_"+c_text[l]+"_") , "RECREATE" );
            
            for (unsigned j=0; j<nSR; j++){
              hsum_cuts_woQCD[k][j][l]->Write();
            }
            fout->Close();
          }
        }
      }

      tmp=SR_MCsum_mt;
      if(!inclusive_selection) { tmp.ReplaceAll(".root", categories[icat]+".root"); }
      tmp.ReplaceAll( "SR_", "SS_SR_" );
      for (unsigned k=0; k<nVARused; k++){
        TFile* fout=new TFile(tmp.ReplaceAll( r1[k],r2[k] ),"RECREATE");
        for (unsigned j=0; j<nSR; j++){
          hsum_SS[k][j]->Write();
        }
        cout << "Works" << endl;
        fout->Close();
      }

      cout << "Works here" << endl;
      for (unsigned j=0; j<nSR; j++){
        for(unsigned k=0; k<nVARused; k++){
          delete hsum[k][j];
          delete hsum_woQCD[k][j];
          delete hsum_SS[k][j];
          if(DOCUTS){
            for(unsigned l=0; l<NC; l++){
              delete hsum_cuts[k][j][l];
              delete hsum_cuts_woQCD[k][j][l];
            }
          }
        }
      }

      //W+jets mT>70 renorm
      cout << "W+jets renorm..." << endl;
      TH1D* h_mt70_data[nSR];
      TH1D* h_mt70_mc[nVARused][nSR];
      for (unsigned kk=0; kk<nVARused; kk++){
        for (unsigned jj=0; jj<nSR; jj++){
          //      if (kk==0) h_mt70_data[jj]     = new TH1D( hn[jj]+tvar[0],"",nbins[0],hist_min[0],hist_max[0] );
          h_mt70_mc[kk][jj]              = new TH1D( hn[jj]+tvar[kk],"",nbins[kk],hist_min[kk],hist_max[kk] );
          if (kk==0) h_mt70_data[jj]     = new TH1D( *h_mt70_mc[kk][jj] );
        }
      }
      
      for (unsigned ii=0; ii<ps.size(); ii++){
        TString tmp=fl.at(ii);
        if(!inclusive_selection) { tmp.ReplaceAll(".root", categories[icat]+".root"); }
        for (unsigned kk=0; kk<nVARused; kk++){
          tmp.ReplaceAll( r1[kk],r2[kk] );
          
          TFile *fmt = new TFile( tmp );
          for (unsigned jj=0; jj<nSR; jj++){
            if (kk==0){
              if ( tmp.Contains("SR_data_")  ) h_mt70_data[jj]->Add(    (TH1D*)fmt->Get( hn[jj] + tvar[0] ) , +1 );
              if ( tmp.Contains("SR_TT_")    ) h_mt70_data[jj]->Add(    (TH1D*)fmt->Get( hn[jj] + tvar[0] ) , -1 );
              if ( tmp.Contains("SR_DY_")    ) h_mt70_data[jj]->Add(    (TH1D*)fmt->Get( hn[jj] + tvar[0] ) , -1 );
            }
            if ( tmp.Contains("SR_Wjets_") ) h_mt70_mc[kk][jj]->Add(   (TH1D*)fmt->Get( hn[jj] + tvar[kk] ) , +1 );
          }
        }
      }

      Double_t mtrenorm[nSR]={0};
      for (unsigned jj=0; jj<nSR; jj++) mtrenorm[jj]= h_mt70_data[jj]->Integral(8,-1)/h_mt70_mc[0][jj]->Integral(8,-1);
      
      tmp=SR_Wjets_mt_sim;
      if(!inclusive_selection) { tmp.ReplaceAll(".root", categories[icat]+".root"); }
      tmp.ReplaceAll( "SR_Wjets", "SR_Wjets_renorm" );
      for (unsigned kk=0; kk<nVARused; kk++){
        tmp.ReplaceAll( r1[kk],r2[kk] );
        TFile* fout=new TFile(tmp ,"RECREATE");
        for (unsigned jj=0; jj<nSR; jj++){
          //      cout << " XX " << j << " " << mtrenorm[jj] << endl;
          h_mt70_mc[kk][jj]->Scale( mtrenorm[jj] );
          h_mt70_mc[kk][jj]->Write();
        }
        fout->Close();
      }
      
      for (unsigned kk=0; kk<nVARused; kk++){
        for (unsigned jj=0; jj<nSR; jj++){
          if (kk==0)       delete h_mt70_data[jj];
          delete h_mt70_mc[kk][jj]; //!
        }
      }

      //QCD OS/SS
      cout << "QCD OS/SS" << endl;
      TH1D* hqcd_OS_SS_MCsum[nVARused][nSR];
      TH1D* hqcd_OS_SS_data[nVARused][nSR];
      TH1D* hqcd_OS_SS_factor[nVARused];
      for (unsigned kk=0; kk<nVARused; kk++){
        hqcd_OS_SS_factor[kk]= new TH1D("factor_"+tvar[kk]+categories[icat],"",nbins[kk],hist_min[kk],hist_max[kk]);
        for (int ib=1; ib<=nbins[kk]; ib++){
          hqcd_OS_SS_factor[kk]->SetBinContent(ib,1.06);
          hqcd_OS_SS_factor[kk]->SetBinError(ib,1.06/10);
        }
        for (unsigned jj=0; jj<nSR; jj++){
          hqcd_OS_SS_MCsum[kk][jj]= new TH1D(hn[jj]+tvar[kk],"",nbins[kk],hist_min[kk],hist_max[kk]);
          hqcd_OS_SS_data[kk][jj] = new TH1D( *hqcd_OS_SS_MCsum[kk][jj] );
        }
      }
    
      tmp2=SR_MCsum_mt;
      
      if(!inclusive_selection) { tmp2.ReplaceAll(".root", categories[icat]+".root"); }
      tmp2.ReplaceAll( "SR_", "SS_SR_" );
      for (unsigned ii=0; ii<ps.size(); ii++){
        TString tmp=fl.at(ii);
        if(!inclusive_selection) { tmp.ReplaceAll(".root", categories[icat]+".root"); }
        tmp.ReplaceAll( "SR_", "SS_SR_" );
        if ( ! tmp.Contains("_data_")) continue;
        for (unsigned kk=0; kk<nVARused; kk++){
          tmp.ReplaceAll(  r1[kk],r2[kk] );
          tmp2.ReplaceAll( r1[kk],r2[kk] );
          TFile *fSS2  = new TFile( tmp  );
          TFile *fSS2b = new TFile( tmp2 );
          
          for (unsigned jj=0; jj<nSR; jj++){
            //	hqcd_OS_SS_MCsum[kk][jj]->Add(hsum_SS[kk][jj]);
            hqcd_OS_SS_MCsum[kk][jj]->Add( (TH1D*)fSS2b->Get( hn[jj] + tvar[kk] ) );
            hqcd_OS_SS_data[kk][jj]->Add(  (TH1D*)fSS2->Get(  hn[jj] + tvar[kk] ) );
          }
          fSS2->Close();
          
        }
      }

      for (unsigned i=0; i<ps.size(); i++){
        TString tmp=fl.at(i);
        if(!inclusive_selection) { tmp.ReplaceAll(".root", categories[icat]+".root"); }
        tmp.ReplaceAll( "SR_", "SS_SR_" );
        if ( tmp.Contains("_data_") || tmp.Contains("_QCD_") ) continue;
        for (unsigned k=0; k<nVARused; k++){
          tmp.ReplaceAll( r1[k],r2[k] );
          TFile fSS( tmp );
          
          for (unsigned j=0; j<nSR; j++){
            hqcd_OS_SS_MCsum[k][j]->Add( (TH1D*) fSS.Get( hn[j] + tvar[k] ) ,-1 );
            hqcd_OS_SS_data[k][j]->Add(  (TH1D*) fSS.Get( hn[j] + tvar[k] ) ,-1 );
          }
          
        }
      }

      tmp=SR_MCsum_mt;
      if(!inclusive_selection) { tmp.ReplaceAll(".root", categories[icat]+".root"); }
      tmp.ReplaceAll( "SR_MCsum", "SR_QCDfromMCsum_OS_SS" );
      for (unsigned k=0; k<nVARused; k++){
        TFile* fout=new TFile(tmp.ReplaceAll( r1[k],r2[k] ),"RECREATE");
        for (unsigned j=0; j<nSR; j++){
          //      hqcd_OS_SS_MCsum[k][j]->Scale( 1.06 ); //run 1 rescaling factor
          hqcd_OS_SS_MCsum[k][j]->Multiply( hqcd_OS_SS_factor[k] ); //run 1 rescaling factor
          hqcd_OS_SS_MCsum[k][j]->Write();
        }
        fout->Close();
      }
      
      tmp=SR_MCsum_mt;
      if(!inclusive_selection) { tmp.ReplaceAll(".root", categories[icat]+".root"); }
      tmp.ReplaceAll( "SR_MCsum", "SR_QCDfromData_OS_SS" );
      for (unsigned k=0; k<nVARused; k++){
        TFile* fout=new TFile(tmp.ReplaceAll( r1[k],r2[k] ),"RECREATE");
        for (unsigned j=0; j<nSR; j++){
          hqcd_OS_SS_data[k][j]->Multiply( hqcd_OS_SS_factor[k] ); //run 1 rescaling factor
          hqcd_OS_SS_data[k][j]->Write();
        }
        fout->Close();
      }

      TH1D* h_bkgsum_run1[nVARused][nSR];
      
      tmp2=SR_Wjets_mt_sim;
      if(!inclusive_selection) { tmp2.ReplaceAll(".root", categories[icat]+".root"); }
      tmp2.ReplaceAll( "SR_Wjets", "SR_Wjets_renorm" );
      for (unsigned ii=0; ii<ps.size(); ii++){
        TString tmp=fl.at(ii);
        if(!inclusive_selection) { tmp.ReplaceAll(".root", categories[icat]+".root"); }
        for (unsigned kk=0; kk<nVARused; kk++){
          tmp.ReplaceAll(  r1[kk],r2[kk] );
          tmp2.ReplaceAll( r1[kk],r2[kk] );
          TFile *fb  = new TFile( tmp );
          TFile* fb2 = new TFile( tmp2 );
          for (unsigned jj=0; jj<nSR; jj++){
            if (ii==0) h_bkgsum_run1[kk][jj]= new TH1D(hn[jj]+tvar[kk],"",nbins[kk],hist_min[kk],hist_max[kk]);
            if ( tmp.Contains("SR_TT_") || tmp.Contains("SR_DY_L_") || tmp.Contains("SR_DY_J") )   h_bkgsum_run1[kk][jj]->Add(    (TH1D*) fb->Get( hn[jj] + tvar[kk] ) );
            //	if ( tmp.Contains("SR_Wjets_")    )                                                    h_bkgsum_run1[kk][jj]->Add( h_mt70_mc[kk][jj]  );
            if ( tmp.Contains("SR_Wjets_")    )                                                    h_bkgsum_run1[kk][jj]->Add(    (TH1D*)fb2->Get( hn[jj] + tvar[kk] ) );
            if ( tmp.Contains("SR_QCD_")    )                                                      h_bkgsum_run1[kk][jj]->Add( hqcd_OS_SS_data[kk][jj]  );
          }
        }
      }

      tmp=SR_MCsum_mt;
      if(!inclusive_selection) { tmp.ReplaceAll(".root", categories[icat]+".root"); }
      tmp.ReplaceAll( "SR_MCsum", "SR_Bkgsum_run1" );
      for (unsigned k=0; k<nVARused; k++){
        TFile* fout=new TFile(tmp.ReplaceAll( r1[k],r2[k] ),"RECREATE");
        for (unsigned j=0; j<nSR; j++){
          h_bkgsum_run1[k][j]->Write();
        }
        fout->Close();
      }
      
    }

    delete Analyzer;


  } //end loop over categories if any
}
  
#ifndef __CINT__
int main(int argc, char* argv[]) {
  SRHisto();    
}
#endif

#include "ViennaTool/interface/TNtupleAnalyzer.h"

#include <iostream>
#include <string>

void compressFile(TString name);

void Preselection() {

  std::cout << std::endl << "***************************************" << std::endl;
  std::cout << "*             Preselection            *" << std::endl;
  std::cout << "***************************************" << std::endl << std::endl;

  std::cout << "Number: " << num << std::endl;
  TNtupleAnalyzer *Analyzer = new TNtupleAnalyzer();
  TString tmp;



  if (num==1||num==0) {
    Analyzer->loadFile(datafile,"TauCheck");
    Analyzer->select(preselection_data,0);
    Analyzer->closeFile();
    tmp=preselection_data;
    compressFile(preselection_data);
  }
  if (num==2||num==0) {
    Analyzer->loadFile(TTfile,"TauCheck");
    Analyzer->select(preselection_TT,0);
    Analyzer->closeFile();
    tmp=preselection_TT;
    compressFile(preselection_TT);
  }
  if ( (num==2 || num==3||num==0)) {
    Analyzer->loadFile(TTfile,"TauCheck");
    Analyzer->select(preselection_TT_T,_TT|_TTAU);
    Analyzer->closeFile();
    tmp=preselection_TT_T;
    compressFile(preselection_TT_T);
  }
  if (num==2 || num==3||num==0) {
    Analyzer->loadFile(TTfile,"TauCheck");
    Analyzer->select(preselection_TT_J,_TT|_JTAU);
    Analyzer->closeFile();
    tmp=preselection_TT_J;
    compressFile(preselection_TT_J);
  }
  if (num==2 || num==5||num==0) {
    Analyzer->loadFile(TTfile,"TauCheck");
    Analyzer->select(preselection_TT_L,_TT|_LTAU);
    Analyzer->closeFile();
    compressFile(preselection_TT_L);
  }
  
  if (num==6||num==0) {
    Analyzer->loadFile(Wjetsfile,"TauCheck");
    Analyzer->select(preselection_Wjets,0);
    Analyzer->closeFile();
    compressFile(preselection_Wjets);
  }
  if (num==7 ||num==0||num==99) {
    Analyzer->loadFile(DY_NJfile,"TauCheck");
    Analyzer->select(preselection_DY,0);
    Analyzer->closeFile();
    compressFile(preselection_DY);
  }
  if ((num==8 || num==7 ||num==0||num==99)) {
    Analyzer->loadFile(DY_NJfile,"TauCheck");
    Analyzer->select(preselection_DY_TT,_DY|_TTAU);
    Analyzer->closeFile();
    compressFile(preselection_DY_TT);
  }
  if (num==8 || num==7 ||num==0||num==99) {
    Analyzer->loadFile(DY_NJfile,"TauCheck");
    Analyzer->select(preselection_DY_J,_DY|_JTAU);
    Analyzer->closeFile();
    compressFile(preselection_DY_J);
  }
  if (num==10 || num==7 ||num==0||num==99) {
    Analyzer->loadFile(DY_NJfile,"TauCheck");
    Analyzer->select(preselection_DY_L,_DY|_LTAU);
    Analyzer->closeFile();
    compressFile(preselection_DY_L);
  }
  if ( (num==11||num==0||num==99) && useVV) {
    Analyzer->loadFile(VVfile,"TauCheck");
    Analyzer->select(preselection_VV,0);
    Analyzer->closeFile();
    compressFile(preselection_VV);
  }
  if ((num==11 || num==13||num==0||num==99) && useVV) {
    Analyzer->loadFile(VVfile,"TauCheck");
    Analyzer->select(preselection_VV_T,_VV|_TTAU);
    Analyzer->closeFile();
    compressFile(preselection_VV_T);
  }
  if ( (num==11 || num==13||num==0||num==99) && useVV) {
    Analyzer->loadFile(VVfile,"TauCheck");
    Analyzer->select(preselection_VV_J,_VV|_JTAU);
    Analyzer->closeFile();
    compressFile(preselection_VV_J);
  }
  if ( (num==11 || num==14||num==0||num==99) && useVV) {
    Analyzer->loadFile(VVfile,"TauCheck");
    Analyzer->select(preselection_VV_L,_VV|_LTAU);
    Analyzer->closeFile();
    compressFile(preselection_VV_L);
  }
  if( (num==19 || num==0) && CHAN==kMU ){
    Analyzer->loadFile(QCDfile, "TauCheck");
    Analyzer->select(preselection_QCD,_QCD);
    Analyzer->closeFile();
    compressFile(preselection_QCD);
  }
  if( num==20 || num==0 ){
    Analyzer->loadFile(SIGNALfile,"TauCheck");
    Analyzer->select(preselection_signal,0);
    Analyzer->closeFile();
    compressFile(preselection_signal);
  }

  //Embedding mode follows now: 
  if (num==2 || num==3||num==0) {
    Analyzer->loadFile(TTfile,"TauCheck");
    Analyzer->select(preselection_TT_J_EMB,_TT|_JTAU);
    Analyzer->closeFile();
    tmp=preselection_TT_J;
    compressFile(preselection_TT_J_EMB);
  }
  if (num==2 || num==5||num==0) {
    Analyzer->loadFile(TTfile,"TauCheck");
    Analyzer->select(preselection_TT_L_EMB,_TT|_LTAU);
    Analyzer->closeFile();
    compressFile(preselection_TT_L_EMB);
  }
  if (num==8 || num==7 ||num==0||num==99) {
    Analyzer->loadFile(DY_NJfile,"TauCheck");
    Analyzer->select(preselection_DY_J_EMB,_DY|_JTAU);
    Analyzer->closeFile();
    compressFile(preselection_DY_J_EMB);
  }
  if (num==10 || num==7 ||num==0||num==99) {
    Analyzer->loadFile(DY_NJfile,"TauCheck");
    Analyzer->select(preselection_DY_L_EMB,_DY|_LTAU);
    Analyzer->closeFile();
    compressFile(preselection_DY_L_EMB);
  }
  if ( (num==11 || num==13||num==0||num==99) && useVV) {
    Analyzer->loadFile(VVfile,"TauCheck");
    Analyzer->select(preselection_VV_J_EMB,_VV|_JTAU);
    Analyzer->closeFile();
    compressFile(preselection_VV_J_EMB);
  }
  if ( (num==11 || num==14||num==0||num==99) && useVV) {
    Analyzer->loadFile(VVfile,"TauCheck");
    Analyzer->select(preselection_VV_L_EMB,_VV|_LTAU);
    Analyzer->closeFile();
    compressFile(preselection_VV_L_EMB);
  }
  
  ////////////////////////////////////////////////////////////////////////////
  if( EMB == 0 ){
    if (num==0) {
      std::cout << "Creating merged tree in file " << preselection_MCsum_woQCD << std::endl;
      TChain* MCch=new TChain("Events");
      MCch->Add(preselection_Wjets);
      MCch->Add(preselection_DY);
      MCch->Add(preselection_TT);
      MCch->Add(preselection_VV);
      TFile* MCf = new TFile(preselection_MCsum_woQCD,"recreate");
      MCch->Merge(MCf,0);
    }
    if (num==0) {
      std::cout << "Creating merged tree in file " << preselection_MCsum << std::endl;
      TChain* MCch=new TChain("Events");
      MCch->Add(preselection_MCsum_woQCD);
      if ( CHAN==kMU ) MCch->Add(preselection_QCD);
      
      TFile* MCf = new TFile(preselection_MCsum,"recreate");
      MCch->Merge(MCf,0);
    }
  }else{
    if (num==0) {
      std::cout << "Creating merged tree in file " << preselection_MCsum_woQCD << std::endl;
      TChain* MCch=new TChain("Events");
      MCch->Add(preselection_Wjets);
      MCch->Add(preselection_EMB);
      MCch->Add(preselection_TT_J_EMB);
      MCch->Add(preselection_TT_L_EMB);
      MCch->Add(preselection_DY_J_EMB);
      MCch->Add(preselection_DY_L_EMB);
      MCch->Add(preselection_VV_J_EMB);
      MCch->Add(preselection_VV_L_EMB);
      TFile* MCf = new TFile(preselection_MCsum_woQCD,"recreate");
      MCch->Merge(MCf,0);
    }
    if (num==0) {
      std::cout << "Creating merged tree in file " << preselection_MCsum << std::endl;
      TChain* MCch=new TChain("Events");
      MCch->Add(preselection_MCsum_woQCD);
      if ( CHAN==kMU ) MCch->Add(preselection_QCD);
      
      TFile* MCf = new TFile(preselection_MCsum,"recreate");
      MCch->Merge(MCf,0);
    }
  }
  
  delete Analyzer;
  
}

void compressFile(TString fname){
  TChain* MCch=new TChain("Events");

  TString fname2=fname; fname2.ReplaceAll(".root",".old.root");
  TString cmd_mv=".!mv "+fname+" "+fname2;
  gROOT->ProcessLine(cmd_mv);

  MCch->Add(fname2);

  TFile* MCf = new TFile(fname,"recreate");
  MCch->Merge(MCf,0);

  TString cmd_rm=".!rm -f "+fname2;
  gROOT->ProcessLine(cmd_rm);

}
  
#ifndef __CINT__
int main(int argc, char* argv[]) {
  //std::string argument = argc > 1 ? argv[2] : "default";
  Preselection();    
}
#endif

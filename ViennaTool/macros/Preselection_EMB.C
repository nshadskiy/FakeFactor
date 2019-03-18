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

  if(EMB == 1 && (num==1||num==0)){
    Analyzer->loadFile(EMBfile,"TauCheck"); 
    Analyzer->select(preselection_EMB,_DY|_TTAU); //_DY only set so it gets checked in TNtupleAnalyzer::fitsGenCategory() 
    Analyzer->closeFile();
    tmp=preselection_EMB;
    compressFile(preselection_EMB);
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

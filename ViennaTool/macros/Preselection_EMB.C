#include "ViennaTool/interface/Preselection.h"

void Preselection() {

  std::cout << std::endl << "***************************************" << std::endl;
  std::cout << "*             Preselection            *" << std::endl;
  std::cout << "***************************************" << std::endl << std::endl;


  std::vector<SelectionClass> myList;

  myList.push_back(SelectionClass(EMBfile, preselection_EMB, _DY|_TTAU));

  TNtupleAnalyzer *Analyzer = new TNtupleAnalyzer();

  for (auto entry : myList)
  {
    Analyzer->loadFile(entry.filename,_NtupleTreeName_KIT);
    Analyzer->select(entry.selection,entry.bitmask);
    Analyzer->closeFile();
    compressFile(entry.selection);  

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

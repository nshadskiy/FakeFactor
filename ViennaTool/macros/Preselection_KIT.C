#include "ViennaTool/interface/Preselection.h"

void Preselection(TString argument) {

  std::cout << std::endl << "***************************************" << std::endl;
  std::cout << "*             Preselection            *" << std::endl;
  std::cout << "***************************************" << std::endl << std::endl;


  std::vector<SelectionClass> myList;
  if (argument.Contains("EMB") || argument.Contains("all")) {
    myList.push_back(SelectionClass(EMBfile, preselection_EMB, _DY|_TTAU));
  }
  if (argument.Contains("Data") || argument.Contains("all")) {
    myList.push_back(SelectionClass(datafile, preselection_data, 0));
  }
  if (argument.Contains("WJets") || argument.Contains("Wjets") || argument.Contains("all")) {
    myList.push_back(SelectionClass(Wjetsfile, preselection_Wjets, 0));
  }
  if (argument.Contains("VV") || argument.Contains("all")) {
    myList.push_back(SelectionClass(VVfile, preselection_VV_J_EMB, _VV|_JTAU));
    myList.push_back(SelectionClass(VVfile, preselection_VV_L_EMB, _VV|_LTAU));
    myList.push_back(SelectionClass(VVfile, preselection_VV_T_EMB, _VV|_TTAU));
  }
  if (argument.Contains("TT") || argument.Contains("all")) {
    myList.push_back(SelectionClass(TTfile, preselection_TT_J_EMB, _TT|_JTAU));
    myList.push_back(SelectionClass(TTfile, preselection_TT_L_EMB, _TT|_LTAU));
    myList.push_back(SelectionClass(TTfile, preselection_TT_T_EMB, _TT|_TTAU));
    
  }
  if (argument.Contains("DY") || argument.Contains("all")) {
    myList.push_back(SelectionClass(DYfile, preselection_DY_J_EMB, _DY|_JTAU));
    myList.push_back(SelectionClass(DYfile, preselection_DY_L_EMB, _DY|_LTAU));
    myList.push_back(SelectionClass(DYfile, preselection_DY_TT_EMB, _DY|_TTAU));
    
    myList.push_back(SelectionClass(DYfile, preselection_DY_EMB, 0));
  }
  if (myList.size()==0) {
    std::cout << "Could not interpret " << argument << ". No preselection is performed." << std::endl;
  }

  TNtupleAnalyzer *Analyzer = new TNtupleAnalyzer();

  for (auto entry : myList)
  {
    TString treename;
    if (CHAN==kMU) {
        treename = "mt_nominal/ntuple";
    }
    else if (CHAN==kEL) {
        treename = "et_nominal/ntuple";
    }
    else if (CHAN==kTAU) {
        treename = "tt_nominal/ntuple";
    }
    Analyzer->loadFile(entry.filename,treename);
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
  std::string argument = argc > 1 ? argv[1] : "all";
  Preselection(argument);    
}
#endif

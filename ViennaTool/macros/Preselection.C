
#include "ViennaTool/interface/Preselection.h"

void Preselection()
{

  std::cout << std::endl << "***************************************" << std::endl;
  std::cout << "*             Preselection            *" << std::endl;
  std::cout << "***************************************" << std::endl << std::endl;


  std::vector<SelectionClass> myList;

  if (EMB==0) {
    myList.push_back(SelectionClass(datafile, preselection_data, 0));

    myList.push_back(SelectionClass(TTfile, preselection_TT  , 0));
    myList.push_back(SelectionClass(TTfile, preselection_TT_T, _TT|_TTAU));
    myList.push_back(SelectionClass(TTfile, preselection_TT_J, _TT|_JTAU));
    myList.push_back(SelectionClass(TTfile, preselection_TT_L, _TT|_LTAU));

    myList.push_back(SelectionClass(Wjetsfile, preselection_Wjets, 0));

    myList.push_back(SelectionClass(DY_NJfile, preselection_DY   , 0));
    myList.push_back(SelectionClass(DY_NJfile, preselection_DY_TT, _DY|_TTAU));
    myList.push_back(SelectionClass(DY_NJfile, preselection_DY_J , _DY|_JTAU));
    myList.push_back(SelectionClass(DY_NJfile, preselection_DY_L , _DY|_LTAU));

    myList.push_back(SelectionClass(VVfile, preselection_VV  , 0));
    myList.push_back(SelectionClass(VVfile, preselection_VV_J, _VV|_JTAU));
    myList.push_back(SelectionClass(VVfile, preselection_VV_T, _VV|_TTAU));
    myList.push_back(SelectionClass(VVfile, preselection_VV_L, _VV|_LTAU));
  
  }
  else if (EMB==1) {
    myList.push_back(SelectionClass(datafile, preselection_data, 0));
    myList.push_back(SelectionClass(Wjetsfile, preselection_Wjets, 0)); // This has to be done in order for the merged root file below

    myList.push_back(SelectionClass(TTfile, preselection_TT_J_EMB, _TT|_JTAU));
    myList.push_back(SelectionClass(TTfile, preselection_TT_L_EMB, _TT|_LTAU));

    myList.push_back(SelectionClass(DY_NJfile, preselection_DY_J_EMB, _DY|_JTAU));
    myList.push_back(SelectionClass(DY_NJfile, preselection_DY_L_EMB, _DY|_LTAU));

    myList.push_back(SelectionClass(VVfile, preselection_VV_J_EMB, _VV|_JTAU));
    myList.push_back(SelectionClass(VVfile, preselection_VV_L_EMB, _VV|_LTAU));

  }

  TNtupleAnalyzer *Analyzer = new TNtupleAnalyzer();

  for (auto entry : myList)
  {
    Analyzer->loadFile(entry.filename,_NtupleTreeName);
    Analyzer->select(entry.selection,entry.bitmask);
    Analyzer->closeFile();
    compressFile(entry.selection);  

  }
  delete Analyzer;

  std::cout << "\033[1;36m COMMENT: \033[0m Is this merging later used?" << std::endl;

  createMergedTrees();

}

void createMergedTrees() {
  std::vector<TString> toBeMerged;
  if (EMB) {
    toBeMerged.push_back(preselection_Wjets);
    toBeMerged.push_back(preselection_EMB);
    toBeMerged.push_back(preselection_TT_J_EMB);
    toBeMerged.push_back(preselection_TT_L_EMB);
    toBeMerged.push_back(preselection_DY_J_EMB);
    toBeMerged.push_back(preselection_DY_L_EMB);
    toBeMerged.push_back(preselection_VV_J_EMB);
    toBeMerged.push_back(preselection_VV_L_EMB);
  }
  else{
    toBeMerged.push_back(preselection_Wjets);
    toBeMerged.push_back(preselection_DY);
    toBeMerged.push_back(preselection_TT);
    toBeMerged.push_back(preselection_VV);
  }

  std::cout << "Creating merged tree in file " << preselection_MCsum_woQCD << " (Wjets,DY,TT and VV are merged)"<< std::endl;
  TChain* MCch=new TChain("Events");
  for (auto FileName : toBeMerged) {
    if (DEBUG) {std::cout << "Addingg file: " << FileName << std::endl;}
    MCch->Add(FileName);
  }
  TFile* MCf = new TFile(preselection_MCsum_woQCD,"recreate");
  MCch->Merge(MCf,0);

  std::cout << "Creating merged tree in file " << preselection_MCsum << std::endl;
  TChain* MCch2=new TChain("Events");
  MCch2->Add(preselection_MCsum_woQCD);
  // if ( CHAN==kMU ) MCch2->Add(preselection_QCD); //obsolete because no QCD preselection made
  
  TFile* MCf2 = new TFile(preselection_MCsum,"recreate");
  MCch2->Merge(MCf2,0);
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

  Preselection();

}
#endif
#ifndef __TSELECTIONANALYZER__
#define __TSELECTIONANALYZER__

#include "ViennaTool/interface/GlobalClass.h"
#include "ViennaTool/interface/PlotterClass.h"

class TSelectionAnalyzer: public GlobalClass, public PlotterClass{
 public:
  TSelectionAnalyzer();
  ~TSelectionAnalyzer();

  void calcBgEstSim(const TString preselection,const Int_t mode, const Int_t categoryMode, const TString output, const Int_t cuts=0);
  void getCRHisto(TString preselection,Int_t mode,TString output);
      
};



#endif

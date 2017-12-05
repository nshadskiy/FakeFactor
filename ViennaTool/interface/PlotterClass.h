#ifndef __PLOTTERCLASS__
#define __PLOTTERCLASS__

#include "ViennaTool/interface/GlobalClass.h"
#include "TPie.h"
#include "TPieSlice.h"
#include "TColor.h"

class PlotterClass{
 public:

  //void plotBgStackedAgainstData(TString data,TString data_label,std::vector<TString> mc_list,std::vector<TString> proc_labels, TString imagefile,TString description,TString xLabel,TString signalFile,Int_t mode=1,Int_t col=-99);
  //void plotBgStackedAgainstData(TString data,TString data_label,std::vector<TString> proc_list,std::vector<TString> proc_labels, std::vector<TString> proc_list_subtract, TString imagefile,TString description,TString xLabel,Int_t mode=1,Int_t col=-99);
  //void plotBgStackedAgainstData(TString data,TString data_label,TString proc,TString proc_label, TString imagefile,TString description,TString xLabel,Int_t mode=1,Int_t col=-99);
  //void plotCompBgStackedAgainstData(TString compareFile,TString compareDirectory,TString compareName,TString file, TString directory, std::vector<TString> proc_bkg,std::vector<TString> bkg_labels,TString description,TString compareLegend,TString yAxis,TString imagefile,Int_t mode);
  void plotPieFractions_mutau_etau(TString channel, TString outfile, Int_t preliminary, Float_t *yields);
  void plotPieFractions_tautau(TString channel, TString outfile, Int_t preliminary, Float_t *yields);
  void plotCR(const std::vector<TString> fname, const std::vector<TString> type, const TString fname_data, const TString iso, const TString cr, const TString imagefile, const TString xtitle);
  void makeRatioPlot(TH1D *hdata, TH1D *hmc, TString imagefilename, TString ltext, TString xtitle, TLegend *leg, TString ytitle="data/MC", THStack *hs=NULL, TH1D *hsignal=NULL);
  Int_t plotFF(const TString FF_file_CR,const TString FF_file_SR,const int mode,const TString plotfile, const TString n1="CR", const TString n2="SR", const TString tight_cat="", const Double_t* xbins=0, const Int_t xbins_size=0, const TString xlabel="");
  TString FloatToString( double num , int prec );
  //void makeComparePlots(TString toCompare,TString toCompare_label,std::vector<TString> proc_list,std::vector<TString> proc_labels,TString imagefile,TString description,TString xLabel,Int_t col);
  TString getDescription(TString);
  TString getCaption(TString);

};



#endif

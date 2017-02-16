#include "HTTutilities/Jet2TauFakes/interface/FakeFactor.h"
#include "TFile.h"

using namespace std;

void test(){

  //TString fname="/afs/hephy.at/user/j/jbrandstetter/public/Htautau/FakeRate2016/20170212/et/_2D_Boosted/fakeFactors_20170212.root";
  TString fname="/afs/hephy.at/work/j/jbrandstetter/cmssw/CMSSW_8_0_20/src/HTTutilities/Jet2TauFakes/data/mt/boosted/fakeFactors_20170215.root";
  //TString fname="/afs/hephy.at/user/j/jbrandstetter/public/Htautau/FakeRate2016/20161205_test/tt/incl/fakeFactors_20161205_test.root";
  //TString fname="/afs/hephy.at/user/j/jbrandstetter/public/Htautau/FakeRate2016/20170212/tt/incl/fakeFactors_20170212.root";
  //TString fname="/afs/hephy.at/user/j/jbrandstetter/public/Htautau/FakeRate2016/20170111/et/incl/fakeFactors_20170111.root";
  // Retrieve the fake factor
  TFile* ff_file = TFile::Open(fname);
  FakeFactor* ff    = (FakeFactor*)ff_file->Get("ff_comb");
  FakeFactor* ff_qcd_os    = (FakeFactor*)ff_file->Get("ff_qcd_os");

  // Fill inputs
  std::vector<double> inputs(6);
  inputs[0] = 100; //tau_pt;
  inputs[1] = 0;  //tau_decayMode;
  inputs[2] = 0;  //njet
  inputs[3] = 50; //mvis;
  inputs[4] = 0; //mt
  inputs[5] = 0.0; //muon_iso;

  // Retrieve fake factors
  double ff_nom = ff->value(inputs); // nominal fake factor
  double ff_nom_qcd = ff_qcd_os->value(inputs);

  double syst_qcd_up = ff->value(inputs, "ff_qcd_syst_up");
  double syst_qcd_down = ff->value(inputs, "ff_qcd_syst_down");
  double syst_w_up = ff->value(inputs, "ff_w_syst_up");
  double syst_w_down = ff->value(inputs, "ff_w_syst_down");
  double syst_tt_up = ff->value(inputs, "ff_tt_syst_up");
  double syst_tt_down = ff->value(inputs, "ff_tt_syst_down");
  double syst_qcd_os_up = ff_qcd_os->value(inputs, "ff_qcd_syst_up");

  double stat_qcd_up = ff->value(inputs, "ff_qcd_stat_up");
  double stat_qcd_down = ff->value(inputs, "ff_qcd_stat_down");
  double stat_dm0_njet0_qcd_up = ff->value(inputs, "ff_qcd_dm0_njet0_stat_up");
  double stat_dm0_njet0_qcd_down = ff->value(inputs, "ff_qcd_dm0_njet0_stat_down");
  double stat_dm0_njet1_qcd_up = ff->value(inputs, "ff_qcd_dm0_njet1_stat_up");
  double stat_dm0_njet1_qcd_down = ff->value(inputs, "ff_qcd_dm0_njet1_stat_down");
  double stat_dm1_njet0_qcd_up = ff->value(inputs, "ff_qcd_dm1_njet0_stat_up");
  double stat_dm1_njet0_qcd_down = ff->value(inputs, "ff_qcd_dm1_njet0_stat_down");
  double stat_dm1_njet1_qcd_up = ff->value(inputs, "ff_qcd_dm1_njet1_stat_up");
  double stat_dm1_njet1_qcd_down = ff->value(inputs, "ff_qcd_dm1_njet1_stat_down");
  double stat_dm0_njet0_w_up = ff->value(inputs, "ff_w_dm0_njet0_stat_up");
  double stat_dm0_njet0_w_down = ff->value(inputs, "ff_w_dm0_njet0_stat_down");
  double stat_dm0_njet1_w_up = ff->value(inputs, "ff_w_dm0_njet1_stat_up");
  double stat_dm0_njet1_w_down = ff->value(inputs, "ff_w_dm0_njet1_stat_down");
  double stat_dm1_njet0_w_up = ff->value(inputs, "ff_w_dm1_njet0_stat_up");
  double stat_dm1_njet0_w_down = ff->value(inputs, "ff_w_dm1_njet0_stat_down");
  double stat_dm1_njet1_w_up = ff->value(inputs, "ff_w_dm1_njet1_stat_up");
  double stat_dm1_njet1_w_down = ff->value(inputs, "ff_w_dm1_njet1_stat_down");
  /*/double stat_w_up = ff->value(inputs, "ff_w_stat_up");
  double stat_w_down = ff->value(inputs, "ff_w_stat_down");
  double stat_tt_up = ff->value(inputs, "ff_tt_stat_up");
  double stat_tt_down = ff->value(inputs, "ff_tt_stat_down");*/
  
  cout << "pt= " << inputs[0] << "\t dm= " << inputs[1] << "\t njet= " << inputs[2] << "\t mvis= " << inputs[3] << "\t mt= " << inputs[4] << "\t muiso= " << inputs[5] << endl;
  cout << "ff= " << ff_nom << endl;
  cout << "ff qcd= " << ff_nom_qcd << endl;
  cout << " ----- Systematic uncertainties ----- " << endl;
  cout << "Uncertainties on corrections: " << endl;
  cout << "syst(qcd)_up= " << (syst_qcd_up-ff_nom)/ff_nom*100 << "%" <<  endl;
  cout << "syst(qcd)_down= " << (syst_qcd_down-ff_nom)/ff_nom*100 << "%" <<  endl;
  cout << "syst(w)_up= " << (syst_w_up-ff_nom)/ff_nom*100 << "%" <<  endl;
  cout << "syst(w)_down= " << (syst_w_down-ff_nom)/ff_nom*100 << "%" <<  endl;
  cout << "syst(tt)_up= " << (syst_tt_up-ff_nom)/ff_nom*100 << "%" <<  endl;
  cout << "syst(tt)_down= " << (syst_tt_down-ff_nom)/ff_nom*100 << "%" <<  endl;
  
  cout << "Uncertainties on fake factors: " << endl;
  cout << "-------------------------------------------" << endl;
  cout << "stat(qcd_up)00= " << (stat_dm0_njet0_qcd_up-ff_nom)/ff_nom*100 << "%" << endl;
  cout << "stat(qcd_down)00= " << (stat_dm0_njet0_qcd_down-ff_nom)/ff_nom*100 << "%" << endl;
  cout << "stat(qcd_up)01= " << (stat_dm0_njet1_qcd_up-ff_nom)/ff_nom*100 << "%" << endl;
  cout << "stat(qcd_down)01= " << (stat_dm0_njet1_qcd_down-ff_nom)/ff_nom*100 << "%" << endl;
  cout << "stat(qcd_up)10= " << (stat_dm1_njet0_qcd_up-ff_nom)/ff_nom*100 << "%" << endl;
  cout << "stat(qcd_down)10= " << (stat_dm1_njet0_qcd_down-ff_nom)/ff_nom*100 << "%" << endl;
  cout << "stat(qcd_up)11= " << (stat_dm1_njet1_qcd_up-ff_nom)/ff_nom*100 << "%" << endl;
  cout << "stat(qcd_down)11= " << (stat_dm1_njet1_qcd_down-ff_nom)/ff_nom*100 << "%" << endl;
  cout << "stat(w_up)00= " << (stat_dm0_njet0_w_up-ff_nom)/ff_nom*100 << "%" << endl;
  cout << "stat(w_down)00= " << (stat_dm0_njet0_w_down-ff_nom)/ff_nom*100 << "%" << endl;
  cout << "stat(w_up)01= " << (stat_dm0_njet1_w_up-ff_nom)/ff_nom*100 << "%" << endl;
  cout << "stat(w_down)01= " << (stat_dm0_njet1_w_down-ff_nom)/ff_nom*100 << "%" << endl;
  cout << "stat(w_up)10= " << (stat_dm1_njet0_w_up-ff_nom)/ff_nom*100 << "%" << endl;
  cout << "stat(w_down)10= " << (stat_dm1_njet0_w_down-ff_nom)/ff_nom*100 << "%" << endl;
  cout << "stat(w_up)11= " << (stat_dm1_njet1_w_up-ff_nom)/ff_nom*100 << "%" << endl;
  cout << "stat(w_down)11= " << (stat_dm1_njet1_w_down-ff_nom)/ff_nom*100 << "%" << endl;

  delete ff;
  delete ff_qcd_os;
  ff_file->Close();

}

#ifndef __CINT__
int main(int argc, char* argv[]) {
  test();    
}
#endif

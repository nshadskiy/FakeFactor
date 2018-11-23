#include "HTTutilities/Jet2TauFakes/interface/FakeFactor.h"
#include "TFile.h"

using namespace std;

void test(){

  TString fname="/afs/hephy.at/user/f/fspreitzer/public/Htautau/FakeRate/SM_ML/FakeFactor_SM_ML_Embedding_v7/et/inclusive/fakeFactors_tight.root";
  //TString fname="/afs/hephy.at/user/j/jbrandstetter/public/Htautau/FakeRate2016/20170718/mt/inclusive/fakeFactors_mt_inclusive.root";
  //TString fname="/afs/hephy.at/work/j/jbrandstetter/cmssw/CMSSW_8_0_20/src/HTTutilities/Jet2TauFakes/data/mt/boosted/fakeFactors_20170228.root";
  //TString fname="/afs/hephy.at/user/j/jbrandstetter/public/Htautau/FakeRate2016/20170217_MC/mt/incl/fakeFactors_20170217_MC.root";
  //TString fname="/afs/hephy.at/user/j/jbrandstetter/public/Htautau/FakeRate2016/20170212/tt/incl/fakeFactors_20170212.root";
  //TString fname="/afs/hephy.at/user/j/jbrandstetter/public/Htautau/FakeRate2016/20170111/et/incl/fakeFactors_20170111.root";
  // Retrieve the fake factor
  TFile* ff_file = TFile::Open(fname);
  FakeFactor* ff    = (FakeFactor*)ff_file->Get("ff_comb");
  FakeFactor* ff_qcd_os    = (FakeFactor*)ff_file->Get("ff_qcd_os");
  FakeFactor* ff_w    = (FakeFactor*)ff_file->Get("ff_w");
  FakeFactor* ff_tt    = (FakeFactor*)ff_file->Get("ff_tt");

  // Fill inputs
  std::vector<double> inputs(6);
  /*inputs[0] = 50; //tau_pt;
  inputs[1] = 50;  //tau_pt2
  inputs[2] = 10;  //tau_decay
  inputs[3] = 0; //njets;
  inputs[4] = 100; //mvis
  inputs[5] = 200; //mttot;
  inputs[6] = 0.99;*/
  inputs[0] = 46.1241; //tau_pt;
  inputs[1] = 0;  //tau_decay;
  inputs[2] = 1;  //njets;
  inputs[3] = 222.465; //mvis;
  inputs[4] = 24.505; //mt;
  inputs[5] = 0.08; //muiso;

  // Retrieve fake factors
  double ff_nom = ff->value(inputs); // nominal fake factor
  //double ff_nom_qcd = ff_qcd_os->value(inputs);
  //double ff_nom_w = ff_w->value(inputs);
  //double ff_nom_tt = ff_tt->value(inputs);

  double syst_qcd_up = ff->value(inputs, "ff_qcd_syst_up");
  double syst_qcd_down = ff->value(inputs, "ff_qcd_syst_down");
  double syst_w_up = ff->value(inputs, "ff_w_syst_up");
  double syst_w_down = ff->value(inputs, "ff_w_syst_down");
  /*double frac_syst_w_up = ff->value(inputs, "ff_w_frac_syst_up");
  double frac_syst_w_down = ff->value(inputs, "ff_w_frac_syst_down");
  double frac_syst_tt_up = ff->value(inputs, "ff_tt_frac_syst_up");
  double frac_syst_tt_down = ff->value(inputs, "ff_tt_frac_syst_down");
  double frac_syst_dy_up = ff->value(inputs, "ff_dy_frac_syst_up");
  double frac_syst_dy_down = ff->value(inputs, "ff_dy_frac_syst_down")*/
  double syst_tt_up = ff->value(inputs, "ff_tt_syst_up");
  double syst_tt_down = ff->value(inputs, "ff_tt_syst_down");
  //double syst_qcd_os_up = ff_qcd_os->value(inputs, "ff_qcd_syst_up");

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
  //^cout << "ff qcd= " << ff_nom_qcd << endl;
  cout << " ----- Systematic uncertainties ----- " << endl;
  cout << "Uncertainties on corrections: " << endl;
  cout << "syst(qcd)_up= " << (syst_qcd_up-ff_nom)/ff_nom*100 << "%" <<  endl;
  cout << "syst(qcd)_down= " << (syst_qcd_down-ff_nom)/ff_nom*100 << "%" <<  endl;
  cout << "syst(w)_up= " << (syst_w_up-ff_nom)/ff_nom*100 << "%" <<  endl;
  cout << "syst(w)_down= " << (syst_w_down-ff_nom)/ff_nom*100 << "%" <<  endl;
  /*cout << "frac syst(w)_up= " << (frac_syst_w_up-ff_nom)/ff_nom*100 << "%" <<  endl;
  cout << "frac syst(w)_down= "<< (frac_syst_w_down-ff_nom)/ff_nom*100 << "%" <<  endl;
  cout << "frac syst(dy)_up= " << (frac_syst_dy_up-ff_nom)/ff_nom*100 << "%" <<  endl;
  cout << "frac syst(dy)_down= "<< (frac_syst_dy_down-ff_nom)/ff_nom*100 << "%" <<  endl;
  cout << "frac syst(tt)_up= " << (frac_syst_tt_up-ff_nom)/ff_nom*100 << "%" <<  endl;
  cout << "frac syst(tt)_down= "<< (frac_syst_tt_down-ff_nom)/ff_nom*100 << "%" <<  endl;*/
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
  delete ff_w;
  delete ff_tt;
  ff_file->Close();

}

#ifndef __CINT__
int main(int argc, char* argv[]) {
  test();    
}
#endif

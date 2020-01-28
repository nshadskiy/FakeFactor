#include "TString.h"

#define kMU          0
#define kEL          1
#define kTAU         2
///////////////////////////////////////////////////
#define EMB          1  
#define selCHAN      kEL 
const int CHAN     = kEL;
// FakeFactor_2016_DeepTauIDv2_v0
const TString analysis      ="ff_v14_KIT_emb";
const TString output_folder ="/home/jandrej/ff_v14_KIT_emb";
const TString ver = "2016_v14"; // first time nanoAODv5 with deepTauIDv2 
// in Globals.h specify the path where the files can be found: const TString indir = "/ceph/jbechtel/"+ver+"/";

const TString _NtupleTreeName = "TauCheck"; // name of the TTree in the Analysis-Ntuple: mt-nominal/ntuple or TauCheck
const TString _NtupleTreeName_KIT = "et_nominal/ntuple"; // name of the TTree in the Analysis-Ntuple: mt-nominal/ntuple or TauCheck
const TString DC_folder     ="/afs/hephy.at/work/j/jandrejkovic/ff_method/CMSSW_8_0_25/src/HTTutilities/Jet2TauFakes/data"; //obsolete
///////////////////////////////////////////////////
const TString user="jandrej";    
const Double_t luminosity=35.87; //according to GOLDEN JSON see https://twiki.cern.ch/twiki/bin/view/CMS/TWikiLUM    
const TString ERA = "2016"; // needed for plotting
const int use_svfit = 0; //set to 1 to change input directory name accordingly
const int DEBUG=1; //set to 1 for additional output
///////////////////////////////////////////////////
//Out of date
const int inclusive_selection=1; 
const int exclusive_selection=1; 
const int useVV=1;
const int useMVAMET=0;
///////////////////////////////////////////////////
//Out of date - no need to change 
const int ALLPLOTS=0; //set to 1 for PDFs etc
const int DOQCD=0; //set to 1 to include QCD estimate, 0 for w/o; only works for MC - QCD preselection is not done anyway
const int DOMC=0; //set to 1 for MC, 0 for data
const int doCuts=0;
const int CALC_SS_SR=0; //default: 0   //0.15<QCD_iso<0.25 for QCD FFs
const int num = 0;
const int doSRHisto = 1;
const int doCRHisto = 1;
///////////////////////////////////////////////////
//steerFF
//const int doCalcWeights=1; //calc fractions
const int doCalc=1; //calc FFs
///////////////////////////////////////////////////
//calcCorrections
const int doNJetBinning=0; //Calculate separate corrections for 0jet/1jet
///////////////////////////////////////////////////
//No need to change
const int doDebugPlots=1;    //1 to also calculate FF in SR; and do bkg estimate with unweighted FF per sample ->for control plots
const int doCutPlots=1;      //1 to also calculate cut-dependent plots (prong, eta, pt)
const int doSRPlots=0;      //1 to also calculate SR and all-region plots for FF vs default binning and mT (mtll and muiso is always done)
const int doPlotsVsMC=1;    //only works if mc has already run; no impact on sim-only runs
const int applyFF_fromCR=1; //1 for default; 0 for debugging
const int requireGenMatch_whenCalcFF=0; //0 as default
const int useDYFF_forTT=0; //0 as default
const int useWJFF_forDY=0; //1 as default
const int makePieCharts=0; //used for MSSM pie chart plots
const int doTemplateFitForWeights=0; //template fit for fractions, default: 0
//////////////////////////////////////////////////
const int fit_pT_bins = 1; //use fitted pT bins as input for ff
//////////////////////////////////////////////////
//Working point definition for deep TauID v2://
// _VVVLOOSE         1 
// _VVLOOSE          2
// _VLOOSE           4 <-
// _LOOSE            8
// _MEDIUM          16
// _TIGHT           32 <-
// _VTIGHT          64
// _VVTIGHT        128
// A WP condition is met if: (Fulfill && !Fail)
// settings for tight vs vloose&(!tight):
const int wpTightFulfill = 32; 
const int wpTightFail    = 0;
const int wpLooseFulfill = 4;
const int wpLooseFail    = 32;
///////////////////////////////////////////////////
//MUTAU Settings
#if(selCHAN==kMU)
const double fitMin =  23;
const int fitBins  =  470;
const int COINFLIP=1;
const Double_t Pt_cuts_Wjets[]    = {23,25,30.,34,39,48,60,95,110,500}; //del 75
const Double_t Pt_cuts_DY[]       = {23,30.,40.};
const Double_t Pt_cuts_TT_SR[]    = {23,26,29.,32.,35.,38.,41.,45,52,70,90,115,175,500};
const Double_t Pt_cuts_TT_CR[]    = {23.};
const Double_t Pt_cuts_QCD[]      = {23,26,29,32.5,36,42,65,500};
const Double_t Pt_cuts_QCD_AI[]   = {23,26,29,32.5,36,42,65,500};
#endif
//////////////////////////////////////////////////
//ETAU Settings
#if(selCHAN==kEL)
const double fitMin =  23;
const int fitBins  =  470;
const int COINFLIP=1;
const Double_t Pt_cuts_Wjets[]    = {23.,26.,30.,34.,39.,50,60,75,90,115,500};
const Double_t Pt_cuts_DY[]       = {23.,30.,40.};
const Double_t Pt_cuts_TT_SR[]    = {23.,25.,28.,30.,32.,34,37.,40,45,70,100,160,500};
const Double_t Pt_cuts_TT_CR[]    = {20.};
const Double_t Pt_cuts_QCD[]      = {23,28,33,40,50,500};
const Double_t Pt_cuts_QCD_AI[]   = {23,28,33,40,59,120,500};
#endif
//////////////////////////////////////////////////
//TAUTAU Settings
#if(selCHAN==kTAU)
const double fitMin =  40;
const int fitBins  =  460;
const int COINFLIP=0;
const Double_t Pt_cuts_Wjets[]    = {40.,};
const Double_t Pt_cuts_DY[]       = {40.};
const Double_t Pt_cuts_TT_SR[]    = {40.};
const Double_t Pt_cuts_TT_CR[]    = {40.};
const Double_t Pt_cuts_QCD[]      = {40.,42.5,45.,50.,55,60,65,105,500};
const Double_t Pt_cuts_QCD_AI[]   = {40,42.5,45,50,60,75,115,500};
#endif
//////////////////////////////////////////////////
const double fitMax = 500;
//////////////////////////////////////////////////
const int NB_MTCORR = 2;
const int USE_FIT_BINS = 0; //1: the mT correction is used for x value -0.5 - +0.5: mT=0-10 etc
//const Double_t FIT_BINS[]={0,10,20,30,40,150};
const Double_t FIT_BINS[] = {0,10,20,30,40,50,60,70,150 };
////const Int_t    p_mt_n=(sizeof(p_mt_v)/sizeof(Double_t)) -1;
//const Int_t MT_FIT_NORM_MIN=40; //fit up to this value; use above to normalize. Original: 70
const unsigned nFIT_BINS = (sizeof(FIT_BINS)/sizeof(Double_t)) -1;
const Double_t PTDM_BINS[] = {0,1,2,3,4,5,6,7,8};
//const Double_t PTDM_BINS[] = {0,1,2,3,4};
const unsigned nPTDM_BINS = (sizeof(PTDM_BINS)/sizeof(Double_t)) -1;
//const Double_t MT_FIT_UP_TO = nFIT_BINS - 1.5; //do not include bin normalised to 1
const Double_t PTDMJET_BINS[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
const unsigned nPTDMJET_BINS = (sizeof(PTDMJET_BINS)/sizeof(Double_t)) -1;
const Double_t MT_FIT_UP_TO = nFIT_BINS - 0.5; //include bin normalised to 1
const Double_t MT_CORR_MAX = 70;

const Double_t DR_LEP_CUT=0.5;
const Double_t LEP_ETA_CUT=2.1;
const Double_t LEP_PT_CUT=10;
const Double_t LEP_ISO_CUT=0.15;
const Double_t LEP_ISO_CUT_ET=0.15; //this is only important for signal electron, for all other selections LEP_ISO_CUT is taken
const Double_t TAU1_ISO_CUT=9; //>9(vtight/tight)
const Double_t DR_TAU_LEP_CUT=0.4;
const Double_t TAU_ETA_CUT=2.3; // used for m_Z candidate finding in preselection
const Double_t TAU_PT_CUT=20.;
const Double_t TAU_ETA_CUT_TT=2.1;
const Double_t TAU_PT_CUT_TT=40.;
const Double_t MT_CUT=50; 

const Double_t MZ=91.2; // used in preselection for Z candidate selection
const Double_t QCD_SS_TO_OS=1.06;


//////////////////////////////////////////////////
//extra fit uncertainties
const int useExtraFitUncertainties = 1;
const Double_t QCD_fitErr_dm0njet0_mt = 0.02;
const Double_t QCD_fitErr_dm0njet1_mt = 0.04;
const Double_t QCD_fitErr_dm1njet0_mt = 0.08;
const Double_t QCD_fitErr_dm1njet1_mt = 0.08;
const Double_t W_fitErr_dm0njet0_mt = 0.02;
const Double_t W_fitErr_dm0njet1_mt = 0.02;
const Double_t W_fitErr_dm1njet0_mt = 0.05;
const Double_t W_fitErr_dm1njet1_mt = 0.05;
const Double_t QCD_fitErr_dm0njet0_et = 0.02;
const Double_t QCD_fitErr_dm0njet1_et = 0.04;
const Double_t QCD_fitErr_dm1njet0_et = 0.08;
const Double_t QCD_fitErr_dm1njet1_et = 0.08;
const Double_t W_fitErr_dm0njet0_et = 0.02;
const Double_t W_fitErr_dm0njet1_et = 0.02;
const Double_t W_fitErr_dm1njet0_et = 0.05;
const Double_t W_fitErr_dm1njet1_et = 0.05;
const Double_t QCD_fitErr_dm0njet0_tt = 0.02;
const Double_t QCD_fitErr_dm0njet1_tt = 0.04;
const Double_t QCD_fitErr_dm1njet0_tt = 0.08;
const Double_t QCD_fitErr_dm1njet1_tt = 0.08;
//extra OSSS uncertainties
const int useExtraOSSSuncertainty = 1;
const Double_t OSSSuncertainty_mt = 0.1;
const Double_t OSSSuncertainty_et = 0.1;
const Double_t OSSSuncertainty_tt = 0.1;
//uncertainties for substituting DY FFs
const int useWToDYUncertainty = 1;
const Double_t WToDYUncertainty_mt = 0.05;
const Double_t WToDYUncertainty_et = 0.05;


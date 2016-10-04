#include "TString.h"

#define kMU          0
#define kEL          1
#define kTAU         2


const TString user="jbrandstetter";
const TString analysis="FakeFactor_2016";
const Double_t luminosity=12.9;

const int CHAN = kMU; //kMU,kEL,kTAU
const int use_svfit = 0;
const TString ver = "v1";
const TString inputFF_dir = "~/public/Htautau/FakeRate/";
const TString inputFF_date = "20160929";
//const Double_t FFW_REL_ERR=0.2; //place holder
const Double_t FFW_REL_ERR=0.0;
const int NERR=5; //number of toys for FF
///////////////////////////////////////////////////
const int inclusive_selection=1; //0: splitting FF procedure in categories defined in Globals.h
const int useVV=1;
///////////////////////////////////////////////////
//This defines which fractions are taken for FF bkg estimates, one of them has to be chosen
const int inclusive_frac_mt=1;
const int inclusive_frac_et=0;
const int inclusive_frac_tt=0;
const int cat_frac_mt=0;
const int cat_frac_et=0;
const int cat_frac_tt=0;
///////////////////////////////////////////////////
const int DEBUG=1; //set to 1 for additional output
const int ALLPLOTS=0; //set to 1 for PDFs etc
const int DOQCD=1; //set to 1 to include QCD estimate, 0 for w/o; only works for MC
const int DOMC=0; //set to 1 for MC, 0 for data
const int MULTITAU=0;
const int APPLY_TO_ISOTAU=1; //def: 0
const int USE_ISOTAU=1; //def: 0
const int USE_MVA_ISO=1; //def: 1
const int CALC_SS_SR=0; //default: 0   //0.15<QCD_iso<0.25 for QCD FFs
const int num = 0;
///////////////////////////////////////////////////
//steerFF
const int doDebugPlots=1;    //1 to also calculate FF in SR; and do bkg estimate with unweighted FF per sample ->for control plots
const int doCutPlots=1;      //1 to also calculate cut-dependent plots (prong, eta, pt)
const int doSRPlots=1;      //1 to also calculate SR and all-region plots for FF vs default binning and mT (mtll and muiso is always done)
const int doPlotsVsMC=1;    //only works if mc has already run; no impact on sim-only runs
const int applyFF_fromCR=1; //1 for default; 0 for debugging
const int requireGenMatch_whenCalcFF=0; //0 as default
const int useDYFF_forTT=0; //0 as default
const int useWJFF_forDY=0; //1 as default
const int doCalcWeights=0; //calc fractions
const int doCalc=1; //calc FFs
const int calcVTightFF=0;
//applyFF
const int doBgEst=1; //calc bkg estimates for different FF contributions
const int doCalcUncertainties=0; //calc uncertainties (at the moment only TT)
const int doPlots=0;  //these plots don't have any systematic uncertainties, so default is 0
//applyUncertainties
const int doApplyUncertainties=1; //apply public uncertainties to FF bkg estimates
const int doFinalPlots=1; //final plots of bkg estimates with FFs, comparisons with run1 and MCsum, ...
const int doComparePlots=0;
const int doSSSRPlots=0;
///////////////////////////////////////////////////
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
const Double_t LEP_ISO_CUT=0.1; 
const Double_t TAU1_ISO_CUT=9; //>9(vtight)
const Double_t DR_TAU_LEP_CUT=0.4;
const Double_t TAU_ETA_CUT=2.3;
const Double_t TAU_PT_CUT=20.;
const Double_t TAU_ETA_CUT_TT=2.1;
const Double_t TAU_PT_CUT_TT=40.;
const Double_t MT_CUT=40;

const Double_t MZ=91.2;
const Double_t QCD_SS_TO_OS=1.06;

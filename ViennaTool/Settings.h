#include "TString.h"

#define kMU          0
#define kEL          1
#define kTAU         2


const TString user="jbrandstetter";
const TString analysis="FakeFactor_2016_MSSM_preapproval";
const Double_t luminosity=35.9; //27.9 for ABCDEFG, 20.2 for ABCDEFG

const int CHAN = kMU;
const int use_svfit = 0;
const TString ver = "v16";
///////////////////////////////////////////////////
const int inclusive_selection=1; //0: splitting FF procedure in categories defined in Globals.h
const int useVV=1;
const int useMVAMET=0;
///////////////////////////////////////////////////
const int COINFLIP=1; //only for tautau channel: decide if usage of double count or coin flip
const int DEBUG=1; //set to 1 for additional output
const int ALLPLOTS=1; //set to 1 for PDFs etc
const int DOQCD=1; //set to 1 to include QCD estimate, 0 for w/o; only works for MC
const int DOMC=0; //set to 1 for MC, 0 for data
const int doCuts=0;
const int CALC_SS_SR=0; //default: 0   //0.15<QCD_iso<0.25 for QCD FFs
const int num = 0;
const int doSRHisto = 1;
const int doCRHisto = 1;
///////////////////////////////////////////////////
//steerFF
const int doDebugPlots=1;    //1 to also calculate FF in SR; and do bkg estimate with unweighted FF per sample ->for control plots
const int doCutPlots=1;      //1 to also calculate cut-dependent plots (prong, eta, pt)
const int doSRPlots=0;      //1 to also calculate SR and all-region plots for FF vs default binning and mT (mtll and muiso is always done)
const int doPlotsVsMC=1;    //only works if mc has already run; no impact on sim-only runs
const int applyFF_fromCR=1; //1 for default; 0 for debugging
const int requireGenMatch_whenCalcFF=0; //0 as default
const int useDYFF_forTT=0; //0 as default
const int useWJFF_forDY=0; //1 as default
const int doCalcWeights=1; //calc fractions
const int doTemplateFitForWeights=0; //template fit for fractions, default: 0
const int doCalc=1; //calc FFs
//////////////////////////////////////////////////
const int fit_pT_bins = 1; //use fitted pT bins as input for ff
#if( CHAN!=kTAU )
const double fitMin =  30;
const int fitBins  =  470;
#endif
#if( CHAN==kTAU )
const double fitMin =  40;
const int fitBins  =  460;
#endif
const double fitMax = 500;
//////////////////////////////////////////////////
//applyFF
const int doBgEst=1; //calc bkg estimates for different FF contributions
const int doCalcUncertainties=0; //calc uncertainties (at the moment only TT)
const int doPlots=0;  //these plots don't have any systematic uncertainties, so default is 0
//applyUncertainties
const int doApplyUncertainties=1; //apply public uncertainties to FF bkg estimates
const int doFinalPlots=1; //final plots of bkg estimates with FFs, comparisons with run1 and MCsum, ...
const int plotSplittedFFs=0;
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
const Double_t LEP_ISO_CUT=0.15;
const Double_t LEP_ISO_CUT_ET=0.1; //this is only important for signal electron, for all other selections LEP_ISO_CUT is taken
const Double_t TAU1_ISO_CUT=9; //>9(vtight/tight)
const Double_t DR_TAU_LEP_CUT=0.4;
const Double_t TAU_ETA_CUT=2.3;
const Double_t TAU_PT_CUT=20.;
const Double_t TAU_ETA_CUT_TT=2.1;
const Double_t TAU_PT_CUT_TT=40.;
const Double_t MT_CUT=40;

const Double_t MZ=91.2;
const Double_t QCD_SS_TO_OS=1.06;





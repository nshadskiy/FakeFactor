#include "Settings.h"
#include "TString.h"

#define _W_JETS         1
#define _DY             2
#define _TT             4
#define _QCD            8
#define _VV            16
#define _TTAU          32
#define _JTAU          64
#define _LTAU         128
#define DOALL         256
#define NO_SR         512
#define GEN_MATCH    1024
#define VSVAR        2048
#define MT           4096
#define MVIS         8192
#define PT          16384
#define MTLL        65536
#define MUISO      131072
#define NB         262144
#define DRB        524288
#define _FIT      4194304
#define _SS       8388608
#define SR       16777216      
#define _AI      33554432
#define LEPPT   268435456
#define SVFIT  1073741824

//int max:     2147483648

#define NP1           1
#define NP3           2
#define PT1           4
#define PT2           8
#define PT3          16
#define ETA1         32
#define ETA2         64
#define ETA3        128

#define JET0   67108864
#define JET1  134217728

#define _COLOR          1
#define _COLOR_RUN1     2
#define _COLOR_FF       4
#define _COLOR_CHECK    8
#define _COMPARE       16
#define _COMPARE2      32

//isolation
#define _VVVLOOSE_DNN         1
#define _VVLOOSE_DNN          2
#define _VLOOSE_DNN           4
#define _LOOSE_DNN            8
#define _MEDIUM_DNN          16
#define _TIGHT_DNN           32
#define _VTIGHT_DNN          64
#define _VVTIGHT_DNN        128

#define _VLOOSE          1
#define _LOOSE           2
#define _MEDIUM          4
#define _TIGHT           8
#define _VTIGHT          16

//be very careful to not overlap with other marks -> use category mark extra
#define _INCL              1
#define _DUMMYCAT          2

const Int_t promptE   =1;
const Int_t promptMu  =2;
const Int_t tauE      =3;
const Int_t tauMu     =4;
const Int_t tauH      =5;
const Int_t realJet   =6;


const TString curr_svfit[]    = { "woSVFIT", "SVFIT"};
const TString s_chan[]        = {"mt", "et", "tt"};
const TString s_doubleCount[] = {"_DC", ""};

const TString s_preselection ="preselection";
const TString s_weighted     ="weighted";
const TString s_SR           ="SR";
const TString s_SS_SR        ="SS_SR";
const TString s_CR           ="CR";
const TString s_MC           ="MC";
const TString s_MCsum        ="MCsum";
const TString s_corr         ="corr";
const TString s_mt           ="mt";
const TString s_mtll         ="mtll";
const TString s_nb           ="nb";
const TString s_drb          ="drb";
const TString s_mvis         ="mvis";
const TString s_mvis_nosr    ="mvis_nosr";
const TString s_pt           ="pt";
const TString s_eta           ="eta";
const TString s_svfit        ="svfit";
const TString s_muiso        ="muiso";
const TString s_mt2          ="mt2";
const TString s_lepPt        ="lepPt";
const TString s_mvamet       ="mvamet";
const TString s_met          ="met";
const TString s_mjj          ="mjj";
const TString s_mttot        ="mttot";
const TString s_Wjets        ="Wjets";
const TString s_QCD          ="QCD";
const TString s_TT           ="TT";
const TString s_TT_J         ="TT_J";
const TString s_TT_T         ="TT_T";
const TString s_TT_L         ="TT_L";
const TString s_DY           ="DY";
const TString s_DY_J         ="DY_J";
const TString s_DY_TT        ="DY_TT";
const TString s_DY_L         ="DY_L";
const TString s_EMB          ="EMB";
const TString s_loose        ="loose";
const TString s_tight_alt    ="tight_alt";
const TString s_tight        ="tight";


//Output directories
const TString path_presel        = "/ceph/"+user+"/auto-fakefactors/"+analysis+"/preselection/"+s_chan[CHAN]+"/";
const TString path_ff            = "ViennaTool/fakefactor/";
const TString path_ff_data       = path_ff+"data_"+s_chan[CHAN]+"/";
const TString path_ff_mc         = path_ff+"mc_"+s_chan[CHAN]+"/";
const TString path_ff_mc_woQCD   = path_ff+"mc_woQCD_"+s_chan[CHAN]+"/";
const TString path_sim           = "ViennaTool/sim/"+s_chan[CHAN]+"/";
const TString path_img           = "ViennaTool/Images_EMB/"; //ToDo : add path img emb and non_emb
const TString path_img_data      = path_img+"data_"+s_chan[CHAN]+"/";
const TString path_img_mc        = path_img+"mc_"+s_chan[CHAN]+"/";
const TString path_img_mc_woQCD  = path_img+"mc_woQCD_"+s_chan[CHAN]+"/";

//Input directories
const TString indir = "/ceph/jbechtel/fakefactors/"+ver+"/";
const TString datafile   = indir + s_chan[CHAN] + "-NOMINAL_ntuple_Data.root";
const TString EMBfile    = indir + s_chan[CHAN] + "-NOMINAL_ntuple_EMB.root";
const TString DY_NJfile  = indir + s_chan[CHAN] + "-NOMINAL_ntuple_DY.root";
const TString DYfile     = DY_NJfile;
const TString Wjetsfile  = indir + s_chan[CHAN] + "-NOMINAL_ntuple_WJets.root";
const TString VVfile     = indir + s_chan[CHAN] + "-NOMINAL_ntuple_VV.root";
const TString TTfile     = indir + s_chan[CHAN] + "-NOMINAL_ntuple_TT.root";

//not used:
const TString QCDfile    = indir + s_chan[CHAN] + "-NOMINAL_ntuple_QCD.root";
const TString SIGNALfile = indir + s_chan[CHAN] + "-NOMINAL_ntuple_ggH.root";
//

// Preselection files
const TString preselection_data          = path_presel+"preselection_data"+s_doubleCount[COINFLIP]+".root";
const TString preselection_EMB           = path_presel+"preselection_EMB"+s_doubleCount[COINFLIP]+".root";
const TString preselection_Wjets         = path_presel+"preselection_Wjets"+s_doubleCount[COINFLIP]+".root";
const TString preselection_DY            = path_presel+"preselection_DY"+s_doubleCount[COINFLIP]+".root";
const TString preselection_DY_EMB        = path_presel+"preselection_DY"+s_doubleCount[COINFLIP]+"_EMB.root";
const TString preselection_DY_J          = path_presel+"preselection_DY_J"+s_doubleCount[COINFLIP]+".root";
const TString preselection_DY_J_EMB      = path_presel+"preselection_DY_J"+s_doubleCount[COINFLIP]+"_EMB.root";
const TString preselection_DY_L          = path_presel+"preselection_DY_L"+s_doubleCount[COINFLIP]+".root";
const TString preselection_DY_L_EMB      = path_presel+"preselection_DY_L"+s_doubleCount[COINFLIP]+"_EMB.root";
const TString preselection_DY_TT_EMB      = path_presel+"preselection_DY_TT"+s_doubleCount[COINFLIP]+"_EMB.root";
const TString preselection_TT            = path_presel+"preselection_TT"+s_doubleCount[COINFLIP]+".root";
const TString preselection_TT_J          = path_presel+"preselection_TT_J"+s_doubleCount[COINFLIP]+".root";
const TString preselection_TT_J_EMB      = path_presel+"preselection_TT_J"+s_doubleCount[COINFLIP]+"_EMB.root";
const TString preselection_TT_L          = path_presel+"preselection_TT_L"+s_doubleCount[COINFLIP]+".root";
const TString preselection_TT_L_EMB      = path_presel+"preselection_TT_L"+s_doubleCount[COINFLIP]+"_EMB.root";
const TString preselection_VV            = path_presel+"preselection_VV"+s_doubleCount[COINFLIP]+".root";
const TString preselection_VV_J          = path_presel+"preselection_VV_J"+s_doubleCount[COINFLIP]+".root";
const TString preselection_VV_J_EMB      = path_presel+"preselection_VV_J"+s_doubleCount[COINFLIP]+"_EMB.root";
const TString preselection_VV_L          = path_presel+"preselection_VV_L"+s_doubleCount[COINFLIP]+".root";
const TString preselection_VV_L_EMB      = path_presel+"preselection_VV_L"+s_doubleCount[COINFLIP]+"_EMB.root";
const TString preselection_MCsum         = path_presel+"preselection_"+s_MCsum+s_doubleCount[COINFLIP]+".root";
const TString preselection_MCsum_woQCD   = path_presel+"preselection_woQCD"+s_MCsum+s_doubleCount[COINFLIP]+".root";
const TString preselection_QCD           = path_presel+"preselection_QCD"+s_doubleCount[COINFLIP]+".root"; // delete
const TString preselection_QCD_Pt        = path_presel+"preselection_QCD_Pt"+s_doubleCount[COINFLIP]+".root"; //delete
const TString preselection_signal        = path_presel+"preselection_signal"+s_doubleCount[COINFLIP]+".root"; //delete
const TString preselection_DY_TT         = path_presel+"preselection_DY_TT"+s_doubleCount[COINFLIP]+".root";
const TString preselection_TT_T          = path_presel+"preselection_TT_T"+s_doubleCount[COINFLIP]+".root";
const TString preselection_TT_T_EMB      = path_presel+"preselection_TT_T"+s_doubleCount[COINFLIP]+"_EMB.root";
const TString preselection_VV_T          = path_presel+"preselection_VV_T"+s_doubleCount[COINFLIP]+".root";
const TString preselection_VV_T_EMB      = path_presel+"preselection_VV_T"+s_doubleCount[COINFLIP]+"_EMB.root";


const TString fit_formula                = "fit_formula.root";

// Fakefactor weight files
const TString weight_Wjets = "weight_Wjets.root";
const TString weight_DY_J  = "weight_DY_J.root";
const TString weight_TT_J  = "weight_TT_J.root";
const TString weight_QCD   = "weight_QCD.root";
const TString weight_sum   = "weight_sum.root";
const TString a_weight[4]={weight_Wjets, weight_DY_J, weight_TT_J, weight_QCD};
const TString template_file_name = "templates.root";

// Fake factor files (single MC file)
const TString FF_Wjets_only                  = "FF_Wjets_only.root";
const TString FF_DY_J_only                   = "FF_DY_J_only.root";
const TString FF_TT_J_only                   = "FF_TT_J_only.root";
const TString FF_QCD_only                    = "FF_QCD_only.root";

const TString FF_Wjets_only_SR               = "FF_Wjets_only_"+s_SR+".root";
const TString FF_DY_J_only_SR                = "FF_DY_J_only_"+s_SR+".root";
const TString FF_TT_J_only_SR                = "FF_TT_J_only_"+s_SR+".root";
const TString FF_TT_J_only_SR_fitted         = "FF_TT_J_only_"+s_SR+"_fitted.root";
const TString FF_QCD_only_SR                 = "FF_QCD_only_"+s_SR+".root";
const TString FF_QCD_only_SS                 = "FF_QCD_only_SS.root";
const TString FF_QCD_only_iso                = "FF_QCD_only_iso.root";
const TString FF_QCD_only_mvis_SS            = "FF_QCD_only_mvis_SS.root";
const TString FF_QCD_only_mvis_iso           = "FF_QCD_only_mvis_iso.root";


// Fakefactor files (CR corrected)
const TString FF_corr_Wjets_data                                = "FF_"+s_corr+"_Wjets_data.root";
const TString FF_corr_Wjets_data_weighted                       = "FF_"+s_corr+"_Wjets_data_"+s_weighted+".root";
const TString FF_corr_Wjets_MCsum_noGen                         = "FF_"+s_corr+"_Wjets_"+s_MCsum+"_noGen.root";
const TString FF_corr_Wjets_MCsum_noGen_fitted                  = "FF_"+s_corr+"_Wjets_"+s_MCsum+"_noGen_fitted.root";
const TString FF_corr_Wjets_MC_noGen                            = "FF_"+s_corr+"_Wjets_MC_noGen.root";
const TString FF_corr_Wjets_MC_noGen_fitted                     = "FF_"+s_corr+"_Wjets_MC_noGen_fitted.root";
const TString FF_corr_Wjets_MCsum_noGen_nonclosure              = "FF_"+s_corr+"_Wjets_"+s_MCsum+"_noGen_nonclosure.root";
const TString FF_corr_Wjets_MCsum_noGen_nonclosure_0jet         = "FF_"+s_corr+"_Wjets_"+s_MCsum+"_noGen_nonclosure_0jet.root";
const TString FF_corr_Wjets_MCsum_noGen_nonclosure_1jet         = "FF_"+s_corr+"_Wjets_"+s_MCsum+"_noGen_nonclosure_1jet.root";
const TString FF_corr_Wjets_MCsum_noGen_nonclosure_SS_SR        = "FF_"+s_corr+"_Wjets_"+s_MCsum+"_noGen_nonclosure_SS_SR.root";
const TString FF_corr_Wjets_MC_noGen_nonclosure                 = "FF_"+s_corr+"_Wjets_MC_noGen_nonclosure.root";
const TString FF_corr_Wjets_MC_noGen_nonclosure_0jet            = "FF_"+s_corr+"_Wjets_MC_noGen_nonclosure_0jet.root";
const TString FF_corr_Wjets_MC_noGen_nonclosure_1jet            = "FF_"+s_corr+"_Wjets_MC_noGen_nonclosure_1jet.root";
const TString FF_corr_Wjets_MC_noGen_nonclosure_lepPt           = "FF_"+s_corr+"_Wjets_MC_noGen_nonclosure_lepPt.root";


const TString FF_corr_Wjets_MC_noGen_mtcorr                     = "FF_"+s_corr+"_Wjets_MC_noGen_mtcorr.root";
const TString FF_corr_Wjets_MC_noGen_mtcorr_0jet                = "FF_"+s_corr+"_Wjets_MC_noGen_mtcorr_0jet.root";
const TString FF_corr_Wjets_MC_noGen_mtcorr_1jet                = "FF_"+s_corr+"_Wjets_MC_noGen_mtcorr_1jet.root";
const TString FF_corr_Wjets_MC_noGen_mtcorr_SS_SR               = "FF_"+s_corr+"_Wjets_MC_noGen_mtcorr_SS_SR.root";
const TString FF_corr_Wjets_MCsum_noGen_weighted                = "FF_"+s_corr+"_Wjets_"+s_MCsum+"_noGen_"+s_weighted+".root";
const TString FF_corr_Wjets_MCsum_noGen_SR                      = "FF_"+s_corr+"_Wjets_"+s_MCsum+"_noGen_"+s_SR+".root";
const TString FF_corr_Wjets_MCsum_noGen_SR_weighted             = "FF_"+s_corr+"_Wjets_"+s_MCsum+"_noGen_"+s_SR+"_"+s_weighted+".root";
const TString FF_corr_Wjets_MCsum_Gen                           = "FF_"+s_corr+"_Wjets_"+s_MCsum+"_Gen.root";
const TString FF_corr_Wjets_MCsum_Gen_fitted                    = "FF_"+s_corr+"_Wjets_"+s_MCsum+"_Gen_fitted.root";
const TString FF_corr_Wjets_MCsum_Gen_weighted                  = "FF_"+s_corr+"_Wjets_"+s_MCsum+"_Gen_"+s_weighted+".root";
const TString FF_corr_Wjets_MCsum_noGen_nonclosure_lepPt        = "FF_"+s_corr+"_Wjets_"+s_MCsum+"_noGen_nonclosure_lepPt.root";

const TString FF_corr_DY_data                    = "FF_"+s_corr+"_DY_data.root";
const TString FF_corr_DY_data_weighted           = "FF_"+s_corr+"_DY_data_"+s_weighted+".root";
const TString FF_corr_DY_MCsum_noGen             = "FF_"+s_corr+"_DY_"+s_MCsum+"_noGen.root";
const TString FF_corr_DY_MCsum_noGen_weighted    = "FF_"+s_corr+"_DY_"+s_MCsum+"_noGen_"+s_weighted+".root";
const TString FF_corr_DY_MCsum_noGen_SR          = "FF_"+s_corr+"_DY_"+s_MCsum+"_noGen_"+s_SR+".root";
const TString FF_corr_DY_MCsum_noGen_SR_weighted = "FF_"+s_corr+"_DY_"+s_MCsum+"_noGen_"+s_SR+"_"+s_weighted+".root";
const TString FF_corr_DY_MCsum_Gen               = "FF_"+s_corr+"_DY_"+s_MCsum+"_Gen.root";
const TString FF_corr_DY_MCsum_Gen_weighted      = "FF_"+s_corr+"_DY_"+s_MCsum+"_Gen_"+s_weighted+".root";

const TString FF_corr_TT_data                    = "FF_"+s_corr+"_TT_data.root";
const TString FF_corr_TT_data_weighted           = "FF_"+s_corr+"_TT_data_"+s_weighted+".root";
const TString FF_corr_TT_MCsum_noGen             = "FF_"+s_corr+"_TT_"+s_MCsum+"_noGen.root";
const TString FF_corr_TT_MCsum_noGen_weighted    = "FF_"+s_corr+"_TT_"+s_MCsum+"_noGen_"+s_weighted+".root";
const TString FF_corr_TT_MCsum_noGen_SR          = "FF_"+s_corr+"_TT_"+s_MCsum+"_noGen_"+s_SR+".root";
const TString FF_corr_TT_MCsum_noGen_SR_weighted = "FF_"+s_corr+"_TT_"+s_MCsum+"_noGen_"+s_SR+"_"+s_weighted+".root";
const TString FF_corr_TT_MCsum_Gen               = "FF_"+s_corr+"_TT_"+s_MCsum+"_Gen.root";
const TString FF_corr_TT_MCsum_Gen_weighted      = "FF_"+s_corr+"_TT_"+s_MCsum+"_Gen_"+s_weighted+".root";
const TString FF_corr_TT_MC_noGen_nonclosure     = "FF_"+s_corr+"_TT_MC_noGen_nonclosure.root";

const TString FF_corr_QCD_data                                 = "FF_"+s_corr+"_QCD_data.root";
const TString FF_corr_QCD_data_weighted                        = "FF_"+s_corr+"_QCD_data_"+s_weighted+".root";
const TString FF_corr_QCD_MCsum_noGen                          = "FF_"+s_corr+"_QCD_"+s_MCsum+"_noGen.root";
const TString FF_corr_QCD_MCsum_noGen_fitted                   = "FF_"+s_corr+"_QCD_"+s_MCsum+"_noGen_fitted.root";
const TString FF_corr_QCD_MCsum_noGen_muisocorr                = "FF_"+s_corr+"_QCD_"+s_MCsum+"_noGen_muisocorr.root";
const TString FF_corr_QCD_MCsum_noGen_muisocorr_0jet           = "FF_"+s_corr+"_QCD_"+s_MCsum+"_noGen_muisocorr_0jet.root";
const TString FF_corr_QCD_MCsum_noGen_muisocorr_1jet           = "FF_"+s_corr+"_QCD_"+s_MCsum+"_noGen_muisocorr_1jet.root";
const TString FF_corr_QCD_MCsum_noGen_muisocorr_AI             = "FF_"+s_corr+"_QCD_"+s_MCsum+"_noGen_muisocorr_AI.root";
const TString FF_corr_QCD_MCsum_noGen_nonclosure               = "FF_"+s_corr+"_QCD_"+s_MCsum+"_noGen_nonclosure.root";
const TString FF_corr_QCD_MCsum_noGen_nonclosure_0jet          = "FF_"+s_corr+"_QCD_"+s_MCsum+"_noGen_nonclosure_0jet.root";
const TString FF_corr_QCD_MCsum_noGen_nonclosure_1jet          = "FF_"+s_corr+"_QCD_"+s_MCsum+"_noGen_nonclosure_1jet.root";
const TString FF_corr_QCD_MCsum_noGen_nonclosure_AI            = "FF_"+s_corr+"_QCD_"+s_MCsum+"_noGen_nonclosure_AI.root";
const TString FF_corr_QCD_MCsum_noGen_nonclosure_AI_0jet       = "FF_"+s_corr+"_QCD_"+s_MCsum+"_noGen_nonclosure_AI_0jet.root";
const TString FF_corr_QCD_MCsum_noGen_nonclosure_AI_1jet       = "FF_"+s_corr+"_QCD_"+s_MCsum+"_noGen_nonclosure_AI_1jet.root";
const TString FF_corr_QCD_MCsum_noGen_nonclosure_lepPt         = "FF_"+s_corr+"_QCD_"+s_MCsum+"_noGen_nonclosure_lepPt.root";
const TString FF_corr_QCD_MCsum_noGen_nonclosure_lepPt_0jet    = "FF_"+s_corr+"_QCD_"+s_MCsum+"_noGen_nonclosure_lepPt_0jet.root";
const TString FF_corr_QCD_MCsum_noGen_nonclosure_lepPt_1jet    = "FF_"+s_corr+"_QCD_"+s_MCsum+"_noGen_nonclosure_lepPt_1jet.root";
const TString FF_corr_QCD_MCsum_noGen_OSSScorr                 = "FF_"+s_corr+"_QCD_"+s_MCsum+"_noGen_OSSScorr.root";
const TString FF_corr_QCD_MCsum_noGen_OSSScorr_0jet            = "FF_"+s_corr+"_QCD_"+s_MCsum+"_noGen_OSSScorr_0jet.root";
const TString FF_corr_QCD_MCsum_noGen_OSSScorr_1jet            = "FF_"+s_corr+"_QCD_"+s_MCsum+"_noGen_OSSScorr_1jet.root";
const TString FF_corr_QCD_MCsum_noGen_OS                       = "FF_"+s_corr+"_QCD_"+s_MCsum+"_noGen_OS.root";  
const TString FF_corr_QCD_MCsum_noGen_weighted                 = "FF_"+s_corr+"_QCD_"+s_MCsum+"_noGen_"+s_weighted+".root";
const TString FF_corr_QCD_MCsum_noGen_SR                       = "FF_"+s_corr+"_QCD_"+s_MCsum+"_noGen_"+s_SR+".root";
const TString FF_corr_QCD_MCsum_noGen_AI                       = "FF_"+s_corr+"_QCD_"+s_MCsum+"_noGen_AI.root";
const TString FF_corr_QCD_MCsum_noGen_AI_fitted                = "FF_"+s_corr+"_QCD_"+s_MCsum+"_noGen_AI_fitted.root";
const TString FF_corr_QCD_MCsum_noGen_SR_weighted              = "FF_"+s_corr+"_QCD_"+s_MCsum+"_noGen_"+s_SR+"_"+s_weighted+".root";
const TString FF_corr_QCD_MCsum_Gen                            = "FF_"+s_corr+"_QCD_"+s_MCsum+"_Gen.root";
const TString FF_corr_QCD_MCsum_Gen_fitted                     = "FF_"+s_corr+"_QCD_"+s_MCsum+"_Gen_fitted.root";
const TString FF_corr_QCD_MCsum_Gen_weighted                   = "FF_"+s_corr+"_QCD_"+s_MCsum+"_Gen_"+s_weighted+".root";

const TString FF_corr_QCDISO_MCsum_noGen            = "FF_"+s_corr+"_QCDISO_"+s_MCsum+"_noGen.root";

// Those are just copies of the above files.
const TString FF_corr_data_sum                   = "FF_"+s_corr+"_data_sum.root";
const TString FF_corr_MCsum_noGen_sum            = "FF_"+s_corr+"_"+s_MCsum+"_noGen_sum.root";
const TString FF_corr_MCsum_Gen_sum              = "FF_"+s_corr+"_"+s_MCsum+"_Gen_sum.root";
const TString FF_corr_MC_noGen_sum               = "FF_"+s_corr+"_"+s_MC+"_noGen_sum.root";
const TString FF_corr_MC_Gen_sum                 = "FF_"+s_corr+"_"+s_MC+"_Gen_sum.root";


// In SR
const TString SR_EMB_mt_sim     = path_sim + s_SR+"_EMB_"+s_mt+".root";
const TString SR_EMB_mvis_sim   = path_sim + s_SR+"_EMB_"+s_mvis+".root";
const TString SR_EMB_pt_sim     = path_sim + s_SR+"_EMB_"+s_pt+".root";

const TString SR_Wjets_mt_sim     = path_sim + s_SR+"_Wjets_"+s_mt+".root";
const TString SR_Wjets_mvis_sim   = path_sim + s_SR+"_Wjets_"+s_mvis+".root";
const TString SR_Wjets_pt_sim     = path_sim + s_SR+"_Wjets_"+s_pt+".root";

const TString SR_DY_mt_sim    = path_sim + s_SR+"_DY_"+s_mt+".root";
const TString SR_DY_mvis_sim  = path_sim + s_SR+"_DY_"+s_mvis+".root";
const TString SR_DY_pt_sim    = path_sim + s_SR+"_DY_"+s_pt+".root";

const TString SR_DY_TT_mt_sim   = path_sim + s_SR+"_DY_TT_"+s_mt+".root";
const TString SR_DY_TT_mvis_sim = path_sim + s_SR+"_DY_TT_"+s_mvis+".root";
const TString SR_DY_TT_pt_sim   = path_sim + s_SR+"_DY_TT_"+s_pt+".root";

const TString SR_DY_L_mt_sim    = path_sim + s_SR+"_DY_L_"+s_mt+".root";
const TString SR_DY_L_mvis_sim  = path_sim + s_SR+"_DY_L_"+s_mvis+".root";
const TString SR_DY_L_pt_sim    = path_sim + s_SR+"_DY_L_"+s_pt+".root";

const TString SR_DY_J_mt_sim     = path_sim + s_SR+"_DY_J_"+s_mt+".root";
const TString SR_DY_J_mvis_sim   = path_sim + s_SR+"_DY_J_"+s_mvis+".root";
const TString SR_DY_J_pt_sim     = path_sim + s_SR+"_DY_J_"+s_pt+".root";

const TString SR_TT_mt_sim     = path_sim + s_SR+"_TT_"+s_mt+".root";
const TString SR_TT_mvis_sim   = path_sim + s_SR+"_TT_"+s_mvis+".root";
const TString SR_TT_pt_sim     = path_sim + s_SR+"_TT_"+s_pt+".root";

const TString SR_TT_T_mt_sim     = path_sim + s_SR+"_TT_T_"+s_mt+".root";
const TString SR_TT_T_mvis_sim   = path_sim + s_SR+"_TT_T_"+s_mvis+".root";
const TString SR_TT_T_pt_sim     = path_sim + s_SR+"_TT_T_"+s_pt+".root";

const TString SR_TT_J_mt_sim     = path_sim + s_SR+"_TT_J_"+s_mt+".root";
const TString SR_TT_J_mvis_sim   = path_sim + s_SR+"_TT_J_"+s_mvis+".root";
const TString SR_TT_J_pt_sim     = path_sim + s_SR+"_TT_J_"+s_pt+".root";

const TString SR_TT_L_mt_sim     = path_sim + s_SR+"_TT_L_"+s_mt+".root";
const TString SR_TT_L_mvis_sim   = path_sim + s_SR+"_TT_L_"+s_mvis+".root";
const TString SR_TT_L_pt_sim     = path_sim + s_SR+"_TT_L_"+s_pt+".root";

const TString SR_QCD_mt_sim     = path_sim + s_SR+"_QCD_"+s_mt+".root";
const TString SR_QCD_mvis_sim   = path_sim + s_SR+"_QCD_"+s_mvis+".root";
const TString SR_QCD_pt_sim     = path_sim + s_SR+"_QCD_"+s_pt+".root";

const TString SR_VV_mt_sim      =path_sim + s_SR+"_VV_"+s_mt+".root";
const TString SR_VV_mvis_sim    =path_sim + s_SR+"_VV_"+s_mvis+".root";
const TString SR_VV_pt_sim      =path_sim + s_SR+"_VV_"+s_pt+".root";

const TString SR_VV_T_mt_sim      =path_sim + s_SR+"_VV_T_"+s_mt+".root";
const TString SR_VV_T_mvis_sim    =path_sim + s_SR+"_VV_T_"+s_mvis+".root";
const TString SR_VV_T_pt_sim      =path_sim + s_SR+"_VV_T_"+s_pt+".root";

const TString SR_VV_J_mt_sim      =path_sim + s_SR+"_VV_J_"+s_mt+".root";
const TString SR_VV_J_mvis_sim    =path_sim + s_SR+"_VV_J_"+s_mvis+".root";
const TString SR_VV_J_pt_sim      =path_sim + s_SR+"_VV_J_"+s_pt+".root";

const TString SR_VV_L_mt_sim      =path_sim + s_SR+"_VV_L_"+s_mt+".root";
const TString SR_VV_L_mvis_sim    =path_sim + s_SR+"_VV_L_"+s_mvis+".root";
const TString SR_VV_L_pt_sim      =path_sim + s_SR+"_VV_L_"+s_pt+".root";

// In SS_SR
const TString SS_SR_EMB_mt_sim     = path_sim + s_SS_SR+"_EMB_"+s_mt+".root";
const TString SS_SR_EMB_mvis_sim   = path_sim + s_SS_SR+"_EMB_"+s_mvis+".root";
const TString SS_SR_EMB_pt_sim     = path_sim + s_SS_SR+"_EMB_"+s_pt+".root";

const TString SS_SR_Wjets_mt_sim     = path_sim + s_SS_SR+"_Wjets_"+s_mt+".root";
const TString SS_SR_Wjets_mvis_sim   = path_sim + s_SS_SR+"_Wjets_"+s_mvis+".root";
const TString SS_SR_Wjets_pt_sim     = path_sim + s_SS_SR+"_Wjets_"+s_pt+".root";

const TString SS_SR_DY_mt_sim    = path_sim + s_SS_SR+"_DY_"+s_mt+".root";
const TString SS_SR_DY_mvis_sim  = path_sim + s_SS_SR+"_DY_"+s_mvis+".root";
const TString SS_SR_DY_pt_sim    = path_sim + s_SS_SR+"_DY_"+s_pt+".root";

const TString SS_SR_DY_TT_mt_sim   = path_sim + s_SS_SR+"_DY_TT_"+s_mt+".root";
const TString SS_SR_DY_TT_mvis_sim = path_sim + s_SS_SR+"_DY_TT_"+s_mvis+".root";
const TString SS_SR_DY_TT_pt_sim   = path_sim + s_SS_SR+"_DY_TT_"+s_pt+".root";

const TString SS_SR_DY_L_mt_sim    = path_sim + s_SS_SR+"_DY_L_"+s_mt+".root";
const TString SS_SR_DY_L_mvis_sim  = path_sim + s_SS_SR+"_DY_L_"+s_mvis+".root";
const TString SS_SR_DY_L_pt_sim    = path_sim + s_SS_SR+"_DY_L_"+s_pt+".root";

const TString SS_SR_DY_J_mt_sim     = path_sim + s_SS_SR+"_DY_J_"+s_mt+".root";
const TString SS_SR_DY_J_mvis_sim   = path_sim + s_SS_SR+"_DY_J_"+s_mvis+".root";
const TString SS_SR_DY_J_pt_sim     = path_sim + s_SS_SR+"_DY_J_"+s_pt+".root";

const TString SS_SR_TT_mt_sim     = path_sim + s_SS_SR+"_TT_"+s_mt+".root";
const TString SS_SR_TT_mvis_sim   = path_sim + s_SS_SR+"_TT_"+s_mvis+".root";
const TString SS_SR_TT_pt_sim     = path_sim + s_SS_SR+"_TT_"+s_pt+".root";

const TString SS_SR_TT_T_mt_sim     = path_sim + s_SS_SR+"_TT_T_"+s_mt+".root";
const TString SS_SR_TT_T_mvis_sim   = path_sim + s_SS_SR+"_TT_T_"+s_mvis+".root";
const TString SS_SR_TT_T_pt_sim     = path_sim + s_SS_SR+"_TT_T_"+s_pt+".root";

const TString SS_SR_TT_J_mt_sim     = path_sim + s_SS_SR+"_TT_J_"+s_mt+".root";
const TString SS_SR_TT_J_mvis_sim   = path_sim + s_SS_SR+"_TT_J_"+s_mvis+".root";
const TString SS_SR_TT_J_pt_sim     = path_sim + s_SS_SR+"_TT_J_"+s_pt+".root";

const TString SS_SR_TT_L_mt_sim     = path_sim + s_SS_SR+"_TT_L_"+s_mt+".root";
const TString SS_SR_TT_L_mvis_sim   = path_sim + s_SS_SR+"_TT_L_"+s_mvis+".root";
const TString SS_SR_TT_L_pt_sim     = path_sim + s_SS_SR+"_TT_L_"+s_pt+".root";

const TString SS_SR_QCD_mt_sim     = path_sim + s_SS_SR+"_QCD_"+s_mt+".root";
const TString SS_SR_QCD_mvis_sim   = path_sim + s_SS_SR+"_QCD_"+s_mvis+".root";
const TString SS_SR_QCD_pt_sim     = path_sim + s_SS_SR+"_QCD_"+s_pt+".root";

const TString SS_SR_VV_mt_sim      =path_sim + s_SS_SR+"_VV_"+s_mt+".root";
const TString SS_SR_VV_mvis_sim    =path_sim + s_SS_SR+"_VV_"+s_mvis+".root";
const TString SS_SR_VV_pt_sim      =path_sim + s_SS_SR+"_VV_"+s_pt+".root";

const TString SS_SR_VV_T_mt_sim      =path_sim + s_SS_SR+"_VV_T_"+s_mt+".root";
const TString SS_SR_VV_T_mvis_sim    =path_sim + s_SS_SR+"_VV_T_"+s_mvis+".root";
const TString SS_SR_VV_T_pt_sim      =path_sim + s_SS_SR+"_VV_T_"+s_pt+".root";

const TString SS_SR_VV_J_mt_sim      =path_sim + s_SS_SR+"_VV_J_"+s_mt+".root";
const TString SS_SR_VV_J_mvis_sim    =path_sim + s_SS_SR+"_VV_J_"+s_mvis+".root";
const TString SS_SR_VV_J_pt_sim      =path_sim + s_SS_SR+"_VV_J_"+s_pt+".root";

const TString SS_SR_VV_L_mt_sim      =path_sim + s_SS_SR+"_VV_L_"+s_mt+".root";
const TString SS_SR_VV_L_mvis_sim    =path_sim + s_SS_SR+"_VV_L_"+s_mvis+".root";
const TString SS_SR_VV_L_pt_sim      =path_sim + s_SS_SR+"_VV_L_"+s_pt+".root";

// Control region histograms
const TString CR_Wjets_mt_Wjets    = path_sim + s_CR+"_Wjets_"+s_mt+"_Wjets.root";
const TString CR_Wjets_mvis_nosr_Wjets    = path_sim + s_CR+"_Wjets_mvis_nosr_Wjets.root";
const TString CR_Wjets_mvis_Wjets    = path_sim + s_CR+"_Wjets_"+s_mvis+"_Wjets.root";
const TString CR_Wjets_lepPt_Wjets    = path_sim + s_CR+"_Wjets_"+s_lepPt+"_Wjets.root";
const TString CR_Wjets_mt_DY   = path_sim + s_CR+"_Wjets_"+s_mt+"_DY.root";
const TString CR_Wjets_mt_TT    = path_sim + s_CR+"_Wjets_"+s_mt+"_TT.root";
const TString CR_Wjets_mt_QCD      = path_sim + s_CR+"_Wjets_"+s_mt+"_QCD.root";

const TString CR_DY_mt_Wjets   = path_sim + s_CR+"_DY_"+s_mt+"_Wjets.root";
const TString CR_DY_mt_DY  = path_sim + s_CR+"_DY_"+s_mt+"_DY.root";
const TString CR_DY_mt_TT   = path_sim + s_CR+"_DY_"+s_mt+"_TT.root";
const TString CR_DY_mt_QCD     = path_sim + s_CR+"_DY_"+s_mt+"_QCD.root";

const TString CR_TT_mt_Wjets    = path_sim + s_CR+"_TT_"+s_mt+"_Wjets.root";
const TString CR_TT_mt_DY   = path_sim + s_CR+"_TT_"+s_mt+"_DY.root";
const TString CR_TT_mt_TT    = path_sim + s_CR+"_TT_"+s_mt+"_TT.root";
const TString CR_TT_mt_QCD      = path_sim + s_CR+"_TT_"+s_mt+"_QCD.root";

const TString CR_QCD_mt_Wjets      = path_sim + s_CR+"_QCD_"+s_mt+"_Wjets.root";
const TString CR_QCD_mt_DY     = path_sim + s_CR+"_QCD_"+s_mt+"_DY.root";
const TString CR_QCD_mt_TT      = path_sim + s_CR+"_QCD_"+s_mt+"_TT.root";
const TString CR_QCD_mt_QCD        = path_sim + s_CR+"_QCD_"+s_mt+"_QCD.root";

const TString CR_QCD_mvis_data_MCsubtracted      = path_sim+s_CR+"_QCD_"+s_mvis+"_data_MCsubtracted.root";
const TString CR_QCD_mvis_AI_data_MCsubtracted   = path_sim+s_CR+"_QCD_"+s_mvis+"_AI_data_MCsubtracted.root";
const TString CR_QCD_muiso_data_MCsubtracted     = path_sim+s_CR+"_QCD_muiso_data_MCsubtracted.root";
const TString CR_Wjets_mvis_data_MCsubtracted    = path_sim+s_CR+"_Wjets_"+s_mvis+"_data_MCsubtracted.root";
const TString CR_QCD_lepPt_data_MCsubtracted     = path_sim+s_CR+"_QCD_"+s_lepPt+"_data_MCsubtracted.root";
const TString CR_Wjets_lepPt_data_MCsubtracted     = path_sim+s_CR+"_Wjets_"+s_lepPt+"_data_MCsubtracted.root";

const TString empty_mt="empty_"+s_SR+"_"+s_mt+".root";

// Signal region
const TString SR_MCsum         = path_sim+s_SR+"_"+s_MCsum;
const TString SR_MCsum_mt      = SR_MCsum+"_"+s_mt+".root";
const TString SR_MCsum_mvis    = SR_MCsum+"_"+s_mvis+".root";
const TString SR_MCsum_pt      = SR_MCsum+"_"+s_pt+".root";
const TString SR_MCsum_lepPt      = SR_MCsum+"_"+s_lepPt+".root";
const TString SR_MCsum_svfit      = SR_MCsum+"_"+s_svfit+".root";

const TString SR_MCsum_woQCD       = path_sim+s_SR+"_"+s_MCsum+"_woQCD";
const TString SR_MCsum_woQCD_mt    = SR_MCsum_woQCD+"_"+s_mt+".root";
const TString SR_MCsum_woQCD_mvis  = SR_MCsum_woQCD+"_"+s_mvis+".root";
const TString SR_MCsum_woQCD_pt    = SR_MCsum_woQCD+"_"+s_pt+".root";

const TString SR_data                       = path_sim+s_SR+"_data";
const TString SR_data_mt                    = SR_data+"_"+s_mt+".root";
const TString SR_data_mvis                  = SR_data+"_"+s_mvis+".root";
const TString SR_data_mvis_AI_MCsubtracted  = SR_data+"_"+s_mvis+"_AI_MCsubtracted.root";
const TString SR_data_pt                    = SR_data+"_"+s_pt+".root";
const TString SR_data_lepPt                 = SR_data+"_"+s_lepPt+".root";
const TString SR_data_svfit                 = SR_data+"_"+s_svfit+".root";

const TString SR_signal                = path_sim+s_SR+"_signal";
const TString SR_signal_mt_sim         = SR_signal+"_"+s_mt+".root";
const TString SR_signal_mvis_sim       = SR_signal+"_"+s_mvis+".root";
const TString SR_signal_pt_sim         = SR_signal+"_"+s_pt+".root";
const TString SR_signal_lepPt_sim      = SR_signal+"_"+s_lepPt+".root";
const TString SR_signal_svfit_sim      = SR_signal+"_"+s_svfit+".root";

const TString SS_SR_data       = path_sim+s_SS_SR+"_data";
const TString SS_SR_data_mt    = SS_SR_data+"_"+s_mt+".root";
const TString SS_SR_data_mvis  = SS_SR_data+"_"+s_mvis+".root";
const TString SS_SR_data_pt    = SS_SR_data+"_"+s_pt+".root";

// x Axis label
const TString labelMt="m_{T} [GeV]";
const TString labelMvis="m_{vis} [GeV]";
const TString labelPt="p_{T} [GeV]";
const TString labelIso="rel. muon isolation";
const TString labelNb="number of b-tags";
const TString labelDRb="#Delta R(#tau,b)";

// Binning constants
const Double_t Mt_cuts_Wjets[] = {0.};
const Double_t Mt_cuts_DY[]    = {0.};
const Double_t Mt_cuts_TT[] = {0.};
const Double_t Mt_cuts_QCD[]   = {0.};

const Int_t N_m_Wjets = sizeof(Mt_cuts_Wjets)/sizeof(Double_t);
const Int_t N_m_DY = sizeof(Mt_cuts_DY)/sizeof(Double_t);
const Int_t N_m_TT = sizeof(Mt_cuts_TT)/sizeof(Double_t);
const Int_t N_m_QCD = sizeof(Mt_cuts_QCD)/sizeof(Double_t);

//////////////////////////////////////////////////////////////////////////////////
const Int_t N_p_Wjets = sizeof(Pt_cuts_Wjets)/sizeof(Double_t);
const Int_t N_p_DY = sizeof(Pt_cuts_DY)/sizeof(Double_t);
const Int_t N_p_TT_SR = sizeof(Pt_cuts_TT_SR)/sizeof(Double_t);
const Int_t N_p_TT_CR = sizeof(Pt_cuts_TT_CR)/sizeof(Double_t);
const Int_t N_p_QCD = sizeof(Pt_cuts_QCD)/sizeof(Double_t);
const Int_t N_p_QCD_AI = sizeof(Pt_cuts_QCD_AI)/sizeof(Double_t);

const Double_t Eta_cuts_Wjets[] = {0.};//these are the lower boundaries of the |eta| bins
const Double_t Eta_cuts_DY[]    = {0.};
const Double_t Eta_cuts_TT[] = {0.};
const Double_t Eta_cuts_QCD[]   = {0.};

const Int_t N_e_Wjets = sizeof(Eta_cuts_Wjets)/sizeof(Double_t);
const Int_t N_e_DY = sizeof(Eta_cuts_DY)/sizeof(Double_t);
const Int_t N_e_TT = sizeof(Eta_cuts_TT)/sizeof(Double_t);
const Int_t N_e_QCD = sizeof(Eta_cuts_QCD)/sizeof(Double_t);

const Int_t Decay_cuts_Wjets[] = {0};//normally 0,5
const Int_t Decay_cuts_DY[]    = {0};
const Int_t Decay_cuts_TT[] = {0};
const Int_t Decay_cuts_QCD[]   = {0};

const Int_t N_t_Wjets = sizeof(Decay_cuts_Wjets)/sizeof(Int_t);
const Int_t N_t_DY = sizeof(Decay_cuts_DY)/sizeof(Int_t);
const Int_t N_t_TT = sizeof(Decay_cuts_TT)/sizeof(Int_t);
const Int_t N_t_QCD = sizeof(Decay_cuts_QCD)/sizeof(Int_t);

const Int_t Njet_cuts_Wjets[] = {0,1};
const Int_t Njet_cuts_DY[] = {0,1};
//const Int_t Njet_cuts_TT[] = {0};
const Int_t Njet_cuts_TT_SR[] = {0};
const Int_t Njet_cuts_TT_CR[] = {0};
const Int_t Njet_cuts_QCD[] = {0,1,2};

/*const Int_t Njet_cuts_Wjets[] = {0};
const Int_t Njet_cuts_DY[] = {0};
const Int_t Njet_cuts_TT[] = {0};
const Int_t Njet_cuts_QCD[] = {0};*/

const Int_t N_j_Wjets = sizeof(Njet_cuts_Wjets)/sizeof(Int_t);
const Int_t N_j_DY = sizeof(Njet_cuts_DY)/sizeof(Int_t);
const Int_t N_j_TT_SR = sizeof(Njet_cuts_TT_SR)/sizeof(Int_t);
const Int_t N_j_TT_CR = sizeof(Njet_cuts_TT_CR)/sizeof(Int_t);
//const Int_t N_j_TT = sizeof(Njet_cuts_TT)/sizeof(Int_t);
const Int_t N_j_QCD = sizeof(Njet_cuts_QCD)/sizeof(Int_t);

const Int_t nbins_svfit=35;  const Double_t hist_min_svfit=0.;  const Double_t hist_max_svfit=350.;
const Int_t nbins_lepPt=20;  const Double_t hist_min_lepPt=20.; const Double_t hist_max_lepPt=120.;
const Int_t nbins_mt=25;     const Double_t hist_min_mt=0.;     const Double_t hist_max_mt=250.;
const Int_t nbins_mvis=15;   const Double_t hist_min_mvis=0.;   const Double_t hist_max_mvis=250.;
const Int_t nbins_pt=25;     const Double_t hist_min_pt=20.;    const Double_t hist_max_pt=100.;
const Int_t nbins_eta=20;    const Double_t hist_min_eta=-3.5;  const Double_t hist_max_eta=3.5;

//binning constants: weight
const Double_t w_mt_v[]={0,10,20,30,40,50,60,70,250};

const Int_t    w_mt_n=(sizeof(w_mt_v)/sizeof(Double_t)) -1;

const Double_t w_pt_v[]={30,40,60,100,250};
const Double_t w_mttot_v[]={0,70,100,120,140,170,200,270,1000};
const Int_t    w_pt_n=(sizeof(w_pt_v)/sizeof(Double_t)) -1;
const Int_t    w_mttot_n=(sizeof(w_mttot_v)/sizeof(Double_t)) -1;

const Double_t w_mvis_v[]={0,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,200,250,450};
const Int_t w_mvis_n=(sizeof(w_mvis_v)/sizeof(Double_t)) -1;

#if(selCHAN == kEL)
const Double_t w_lepPt_v[]={23,26,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,110,120,250};
const Int_t w_lepPt_n=(sizeof(w_lepPt_v)/sizeof(Double_t)) -1;
#endif
#if(selCHAN == kMU)
const Double_t w_lepPt_v[]={25,28,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,110,120,250};
const Int_t w_lepPt_n=(sizeof(w_lepPt_v)/sizeof(Double_t)) -1;
#endif
#if(selCHAN == kTAU)
const Double_t w_lepPt_v[]={40,45,50,55,60,65,70,75,80,85,90,95,100,110,120,250};
const Int_t w_lepPt_n=(sizeof(w_lepPt_v)/sizeof(Double_t)) -1;
#endif
const Double_t w_muiso_v[]={0.00,0.02,0.05,0.1,0.15,0.2,0.25,0.3,0.4,0.5,0.7};
const Int_t w_muiso_n=(sizeof(w_muiso_v)/sizeof(Double_t)) -1;

const Int_t    w_dm_v[]={0,4,15};
//const Int_t    w_dm_v[]={0,15}; //no binning in dm
const Int_t    w_dm_n=sizeof(w_dm_v)/sizeof(Int_t) -1;

const Int_t    w_njets_v[]={0,1,10};
const Int_t    w_njets_n=sizeof(w_njets_v)/sizeof(Int_t) -1;

const Int_t nbins_weight=(CHAN!=kTAU) ? w_pt_n*w_dm_n : w_mttot_n*w_dm_n; const Double_t min_weight=-0.5;    const Double_t max_weight=nbins_weight-0.5;

const unsigned nVAR=5;
const Int_t nbins[nVAR]={nbins_mt,nbins_mvis,nbins_pt,nbins_lepPt,w_muiso_n};
const Double_t hist_min[nVAR]={hist_min_mt,hist_min_mvis,hist_min_pt,hist_min_lepPt,hist_min_pt}; //pt bin is placeholder for muiso
const Double_t hist_max[nVAR]={hist_max_mt,hist_max_mvis,hist_max_pt,hist_max_lepPt,hist_max_pt}; //pt bin is placeholder for muiso
const TString tvar[nVAR]={s_mt,s_mvis,s_pt,s_lepPt,s_muiso};
const TString tvar_l[nVAR]={"m_{T} [GeV]","m_{vis} [GeV]","p_{T} [GeV]","p_{T}(lep) [GeV]","#mu_{iso}"};

// used in CRHisto.C
const unsigned nVARCR=4;
// const Int_t nbinsCR[nVARCR]={nbins_mt,nbins_mvis,nbins_pt,w_muiso_n};
// const Double_t hist_minCR[nVARCR]={hist_min_mt,hist_min_mvis,hist_min_pt,hist_min_pt}; //pt bin is placeholder for muiso
// const Double_t hist_maxCR[nVARCR]={hist_max_mt,hist_max_mvis,hist_max_pt,hist_max_pt}; //pt bin is placeholder for muiso
const TString tvarCR[nVARCR]={s_mt,s_mvis,s_pt,s_muiso};
const TString tvarCR_l[nVARCR]={"m_{T} [GeV]","m_{vis} [GeV]","p_{T} [GeV]","#mu_{iso}"};


//plotting constants
const Double_t p_mt_v[]={0,10,20,30,40,50,60,70,100,150,250,500};
const Int_t    p_mt_n=(sizeof(p_mt_v)/sizeof(Double_t)) -1;

const Double_t p_mvis_v[]={0,50,75,100,200};
const Int_t    p_mvis_n=(sizeof(p_mvis_v)/sizeof(Double_t)) -1;

const Double_t p_iso_v[]={0.00, 0.025, 0.050, 0.075, 0.100, 0.150, 0.200, 0.300, 0.500, 10.000};
const Int_t    p_iso_n=(sizeof(p_iso_v)/sizeof(Double_t)) -1;

const Double_t p_nb_v[]={-0.5 , 0.5 , 1.5 , 2.5 , 9};
const Int_t    p_nb_n=(sizeof(p_nb_v)/sizeof(Double_t)) -1;

const Double_t p_drb_v[]={0.0 , 0.05 , 0.2 , 1.0 , 5.0};
const Int_t    p_drb_n=(sizeof(p_drb_v)/sizeof(Double_t)) -1;

const Double_t p_absdeta_v[]={0.,0.5,0.75,1.,1.5};
const Int_t    p_absdeta_n=(sizeof(p_absdeta_v)/sizeof(Double_t)) -1;

const Double_t p_njets_v[]={-0.5,0.5,1.5,2.5,3.5};
const Int_t    p_njets_n=(sizeof(p_njets_v)/sizeof(Double_t)) -1;

const Double_t p_nbjets_v[]={-0.5,0.5};
const Int_t    p_nbjets_n=(sizeof(p_nbjets_v)/sizeof(Double_t)) -1;


//const double global_tmp;
const TString sNum[]={"0","1","2","3","4","5","6","7","8","9"};

// Plotting colors
const Int_t color_Wjets =kRed;
const Int_t color_DY_J  =kBlue;
const Int_t color_DY_TT =kYellow;
const Int_t color_DY_L  =kViolet;
const Int_t color_TT_J  =kGreen;
const Int_t color_TT_T  =kGreen+2;
const Int_t color_TT_L  =kGreen-1;
const Int_t color_sum   =kMagenta;
const Int_t color_QCD   =kCyan;

#if(EMB == 0)
const int nSAMPLES=10;
const int nSAMPLES_COMP=7;
static const TString vlabel[nSAMPLES]={"W+jets","ttJ (j#rightarrow#tau)","ttT (#tau#rightarrow#tau)","ttL (l#rightarrow#tau)","ZJ (j#rightarrow#tau)","ZTT (#tau#rightarrow#tau)","ZL (l#rightarrow#tau)","VV (j#rightarrow#tau)", "VV (#tau#rightarrow#tau)","VV (l#rightarrow#tau)"};
static const TString vsuff[nSAMPLES]= {"Wjets" ,"TT_J"                  ,"TT_T"                     ,"TT_L"                  ,"DY_J"                   ,"DY_TT"                    ,"DY_L"                   ,"VV_J", "VV_T", "VV_L"};
const Int_t vcolor[nSAMPLES]=         {kRed    ,kGreen                  ,kGreen+2                   ,kGreen-1                ,kBlue                    ,kYellow                    ,kViolet                  ,kYellow-5, kYellow-6,kYellow-8};

const int smap[nSAMPLES]=      {0,2,6,7,1,4,5,3,8,9};
const int smap_noqcd[nSAMPLES-1]={0,2,5,6,1,3,4,7,8};
#endif
#if(EMB == 1)
const int nSAMPLES=8;
const int nSAMPLES_COMP=5; 
static const TString vlabel[nSAMPLES]={"W+jets","ttJ (j#rightarrow#tau)","ttL (l#rightarrow#tau)","ZJ (j#rightarrow#tau)","ZL (l#rightarrow#tau)","VV (j#rightarrow#tau)", "VV (l#rightarrow#tau)","EMB"};
static const TString vsuff[nSAMPLES]= {"Wjets" ,"TT_J"                  ,"TT_L"                  ,"DY_J"                   ,"DY_L"                   ,"VV_J", "VV_L", "EMB"};
const Int_t vcolor[10]=         {kRed    ,kGreen                  ,kGreen+2                   ,kGreen-1                ,kBlue                    ,kYellow                    ,kViolet                  ,kYellow-5, kYellow-6,kYellow-8};

const int smap[10]=      {0,2,6,7,1,4,5,3,8,9};
const int smap_noqcd[9]={0,2,5,6,1,3,4,7,8};
#endif

const unsigned NC=10;
const TString c_text[NC]={"1p","3p","pt1","pt2","pt3","eta1","eta2","eta3","jet0","jet1"};
const Int_t c_cuts[NC]={NP1,NP3,PT1,PT2,PT3,ETA1,ETA2,ETA3,JET0,JET1};

static const std::vector<TString> empty_vec_tstring;

const Int_t nCAT=1;
const TString categories[nCAT] = { "_dummycat"};
const Int_t catMode[nCAT] = {_DUMMYCAT};

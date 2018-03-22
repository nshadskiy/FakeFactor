from HTTutilities.Jet2TauFakes.Utilities import Leaf, Node, fill, FakeFactor, replace_nodes
import ROOT
import os
import argparse

parser = argparse.ArgumentParser()
parser.add_argument('--channel', dest = 'channel', help='Channel to plot: mt,et', type=str, metavar = 'TAG', required = True)
parser.add_argument('--input', dest = 'indir', help='Input directory - full string', type=str, metavar = 'TAG', required = True)
args = parser.parse_args()

channel=args.channel

isolation = ""

if(channel == "mt" or channel == "et"):
	isolation = "tight"
elif(channel == "tt"):
	isolation = "tight"


indir=args.indir

date = indir[-8:]

tag='v0.2.1'
FFtype=""
#FFtype="_alt"
categories = ['inclusive','dummycat']
#categories = ['btag_looseiso', 'nobtag_looseiso']

for x in range(0,len(categories)):

    category=categories[x]
    print 'Fake factor input file for channel {0} and category {1}'.format(channel,category)
    # Individual fake factors
    ff_qcd_os = FakeFactor(vars=['tau_pt', 'tau_decay', 'njets', 'mvis', 'mt', 'mu_iso'])
    ff_qcd_ss = FakeFactor(vars=['tau_pt', 'tau_decay', 'mvis', 'mu_iso'])
    ff_w      = FakeFactor(vars=['tau_pt', 'tau_decay', 'njets', 'mvis', 'mt'])
    ff_tt     = FakeFactor(vars=['tau_pt', 'tau_decay', 'njets', 'mvis', 'mt'])
    # Combined fake factor
    ff_comb   = FakeFactor(vars=['tau_pt', 'tau_decay', 'njets', 'mvis', 'mt', 'mu_iso', 'frac_qcd', 'frac_w', 'frac_tt'])
    
    
    home = os.getenv('HOME')
    
    ###########################################################################################################
    ### QCD fake factors
    
    qcd_os = Node(
        name='ff_qcd_os',
        formula='{isocorr_qcd}*{mviscorr_qcd}*{ff_raw_qcd}*{OSSS_corr_qcd}', # SS -> OS correction = 1.23
        #formula='{isocorr_qcd}*{mviscorr_qcd}*{ff_raw_qcd}',
        leaves=[
            Leaf(
                name='ff_raw_qcd',
                file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                object='FakeFactors_Data_QCDSS_3D_SS_Iso_Medium_SS_InvertIso_Medium_tau_pt_vs_decayMode',
                vars=['tau_pt','tau_decay','njets']
            ),
            Leaf(
                name='mviscorr_qcd',
                file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/Correction_Data_QCD_MVis{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                object='QCD_SS_MuMedium_Data_FFSSMuMediumData_mvis_correction',
                vars=['mvis']
            ),
            Leaf(
                name='isocorr_qcd',
                file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/Correction_Data_QCD_MuIso{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                object='QCD_SS_Data_FFSSMuMediumData_isomu_correction',
                vars=['mu_iso']
            ),
            Leaf(
                name='OSSS_corr_qcd',
                file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/Correction_Data_QCD_OSSS{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                object='QCD_SS_Data_FFSSMuMediumData_OSSS_correction',
                vars=['mvis']
            )
        ]
    )

    frac_qcd = replace_nodes(
        qcd_os,
        {'ff_qcd_os':
         Node(
             name='fracQCD',
             formula='{frac_qcd}+0*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='frac_qcd',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/frac_qcd.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category),
                     object='h_w_2d',
                     vars=['mt','tau_decay']
                 ),
                 qcd_os.find('ff_qcd_os')
             ]
         )
        }
    )
    
    qcd_os_up = replace_nodes(
        qcd_os, 
        {'ff_qcd_os':
         Node(
             name='ff_qcd_os_up',
             formula='(1.+{sys_qcd_up})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='sys_qcd_up',
                     file='{INDIR}/{CHANNEL}/uncertainties_QCD_W{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_QCD_MVis_Iso_SS2OS_up',
                     vars=['mvis', 'mu_iso']
                 ),
                 qcd_os.find('ff_qcd_os')
             ]
         )
        }
    )
    qcd_os_down = replace_nodes(
        qcd_os, 
        {'ff_qcd_os':
         Node(
             name='ff_qcd_os_down',
             formula='max(0.,1.-{sys_qcd_down})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='sys_qcd_down',
                     file='{INDIR}/{CHANNEL}/uncertainties_QCD_W{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_QCD_MVis_Iso_SS2OS_down',
                     vars=['mvis', 'mu_iso']
                 ),
                 qcd_os.find('ff_qcd_os')
             ]
         )
        }
    )
    
    
    qcd_os_up_stat = replace_nodes(
        qcd_os, 
        {'ff_qcd_os':
         Node(
             name='ff_qcd_os_up_stat',
             formula='(1.+{stat_qcd_up})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='stat_qcd_up',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_QCDSS_3D_SS_Iso_Medium_SS_InvertIso_Medium_tau_pt_vs_decayMode_error_high',
                     vars=['tau_pt','tau_decay','njets']
                 ),
                 qcd_os.find('ff_qcd_os')
             ]
         )
        }
    )
    
    qcd_os_down_stat = replace_nodes(
        qcd_os, 
        {'ff_qcd_os':
         Node(
             name='ff_qcd_os_down_stat',
             formula='max(0.,1.-{stat_qcd_down})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='stat_qcd_down',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_QCDSS_3D_SS_Iso_Medium_SS_InvertIso_Medium_tau_pt_vs_decayMode_error_low',
                     vars=['tau_pt','tau_decay','njets']
                 ),
             qcd_os.find('ff_qcd_os')
             ]
         )
        }
    )
    
    ###########################################################################################################
    ### W fake factors
    
    w = Node(
        name='ff_w',
        formula='{mtcorr_w}*{ff_raw_w}*{mviscorr_w}',
        leaves=[
            Leaf(
                name='ff_raw_w',
                file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_W_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                object='FakeFactors_Data_HighMT_3D_Iso_Medium_InvertIso_Medium_tau_pt_vs_decayMode',
                vars=['tau_pt','tau_decay','njets']
            ),
            Leaf(
                name='mviscorr_w',
                file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/Correction_Data_W_MVis{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                object='W_OS_Data_FFOSData_mvis_correction',
                vars=['mvis']
            ),
            Leaf(
                name='mtcorr_w',
                file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/Correction_MC_W_MT{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                object='W_OS_MC_FFOSMC_mt_correction',
                vars=['mt']
            )
        ]
    )
    
    frac_w = replace_nodes(
        w,
        {'ff_w':
         Node(
             name='fracW',
             formula='{frac_w}+0*{ff_w}',
             leaves=[
                 Leaf(
                     name='frac_w',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/frac_wjets.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category),
                     object='h_w_2d',
                     vars=['mt','tau_decay']
                 ),
                 w.find('ff_w')
             ]
         )
        }
    )
    
    frac_dy = replace_nodes(
        w,
        {'ff_w':
         Node(
             name='fracDY',
             formula='{frac_dy}+0*{ff_w}',
             leaves=[
                 Leaf(
                     name='frac_dy',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/frac_dy.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category),
                     object='h_w_2d',
                     vars=['mt','tau_decay']
                 ),
                 w.find('ff_w')
             ]
     )
        }
    )
    
    w_up = replace_nodes(
        w, 
        {'ff_w':
         Node(
             name='ff_w_up',
             formula='(1.+{sys_w_up})*{ff_w}',
             leaves=[
                 Leaf(
                     name='sys_w_up',
                     file='{INDIR}/{CHANNEL}/uncertainties_QCD_W{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_W_MVis_MT_up',
                     vars=['mvis', 'mt']
                 ),
                 w.find('ff_w')
             ]
         )
        }
    )
    w_down = replace_nodes(
        w, 
        {'ff_w':
         Node(
             name='ff_w_down',
             formula='max(0.,1.-{sys_w_down})*{ff_w}',
             leaves=[
                 Leaf(
                     name='sys_w_down',
                     file='{INDIR}/{CHANNEL}/uncertainties_QCD_W{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_W_MVis_MT_down',
                     vars=['mvis', 'mt']
                 ),
                 w.find('ff_w')
             ]
         )
        }
    )
    w_up_stat = replace_nodes(
        w, 
        {'ff_w':
         Node(
             name='ff_w_up_stat',
             formula='(1.+{stat_w_up})*{ff_w}',
             leaves=[
                 Leaf(
                     name='stat_w_up',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_W_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_HighMT_3D_Iso_Medium_InvertIso_Medium_tau_pt_vs_decayMode_error_high',
                     vars=['tau_pt','tau_decay','njets']
                 ),
                 w.find('ff_w')
             ]
         )
        }
    )
    w_down_stat = replace_nodes(
        w, 
        {'ff_w':
         Node(
             name='ff_w_down_stat',
             formula='max(0.,1.-{stat_w_down})*{ff_w}',
             leaves=[
                 Leaf(
                     name='stat_w_down',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_W_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_HighMT_3D_Iso_Medium_InvertIso_Medium_tau_pt_vs_decayMode_error_low',
                     vars=['tau_pt','tau_decay','njets']
                 ),
                 w.find('ff_w')
             ]
         )
        }
    )
    
    
    ###########################################################################################################
    ### TTbar fake factors
    tt = Node(
        name='ff_tt',
        formula='{ff_raw_tt}*{mviscorr_tt}',
        leaves=[
            Leaf(
            name='ff_raw_tt',
                file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_TT_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                object='FakeFactors_Data_TT_anyb_addLep_InvertIso_tau_pt_vs_decayMode',
                vars=['tau_pt','tau_decay','njets']
            ),
            Leaf(
                name='mviscorr_tt',
                file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/Correction_MC_TT_MVis{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                object='TT_OS_MC_mvis_correction',
                vars=['mvis']
            ),
        ]
    )

    frac_tt = replace_nodes(
        tt,
        {'ff_tt':
         Node(
             name='fracTT',
             formula='{frac_tt}+0*{ff_tt}',
             leaves=[
                 Leaf(
                     name='frac_tt',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/frac_tt.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category),
                     object='h_w_2d',
                     vars=['mt','tau_decay']
                 ),
                 tt.find('ff_tt')
             ]
         )
        }
    )
    
    tt_up = replace_nodes(
        tt,
        {'ff_tt':
         Node(
             name='ff_tt_up',
             formula='(1.+{sys_tt_up})*{ff_tt}',
             leaves=[
                 Leaf(
                     name='sys_tt_up',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/uncertainties_TT{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_TT_MVis_up',
                     vars=['tau_decay','mvis']
                 ),
                 tt.find('ff_tt')
             ]
         )
        }
    )
    tt_down = replace_nodes(
        tt,
        {'ff_tt':
         Node(
             name='ff_tt_down',
             formula='max(0.,1.-{sys_tt_down})*{ff_tt}',
             leaves=[
                 Leaf(
                     name='sys_tt_down',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/uncertainties_TT{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_TT_MVis_down',
                     vars=['tau_decay','mvis']
                 ),
                 tt.find('ff_tt')
             ]
         )
        }
    )
    tt_up_stat = replace_nodes(
        tt, 
        {'ff_tt':
         Node(
             name='ff_tt_up_stat',
             formula='(1.+{stat_tt_up})*{ff_tt}',
             leaves=[
                 Leaf(
                     name='stat_tt_up',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_TT_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_TT_anyb_addLep_InvertIso_tau_pt_vs_decayMode_error_high',
                     vars=['tau_pt','tau_decay','njets']
                 ),
                 tt.find('ff_tt')
             ]
         )
        }
    )
    tt_down_stat = replace_nodes(
        tt, 
        {'ff_tt':
         Node(
             name='ff_tt_down_stat',
             formula='max(0.,1.-{stat_tt_down})*{ff_tt}',
             leaves=[
                 Leaf(
                     name='stat_tt_down',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_TT_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_TT_anyb_addLep_InvertIso_tau_pt_vs_decayMode_error_low',
                     vars=['tau_pt','tau_decay','njets']
                 ),
                 tt.find('ff_tt')
             ]
         )
        }
    )


    ###########################################################################################################
    ### Combined fake factors
    comb = Node(
        name='ff_comb',
        formula='{frac_tt}*{ff_tt} + ({frac_w}+(1-{frac_qcd}-{frac_w}-{frac_tt}))*{ff_w} + {frac_qcd}*{ff_qcd_os}',
        leaves=[
            # Individual fake factors
            qcd_os,
            w,
            tt,
            # Fractions
            Leaf(
                name='frac_qcd',
                file='{INDIR}/constant.root'.format(INDIR=indir),
                object='constant',
                vars=['frac_qcd']
            ),
            Leaf(
                name='frac_w',
                file='{INDIR}/constant.root'.format(INDIR=indir),
                object='constant',
                vars=['frac_w']
            ),
            Leaf(
                name='frac_tt',
                file='{INDIR}/constant.root'.format(INDIR=indir),
                object='constant',
                vars=['frac_tt']
            ),
        ]
    )
    
    comb_qcd_up = replace_nodes(
        comb,
        {'ff_qcd_os':
         Node(
             name='ff_qcd_os_up',
             formula='(1.+{sys_qcd_up})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='sys_qcd_up',
                     file='{INDIR}/{CHANNEL}/uncertainties_QCD_W{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_QCD_MVis_Iso_SS2OS_up',
                     vars=['mvis', 'mu_iso']
                 ),
                 comb.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_qcd_down = replace_nodes(
        comb,
        {'ff_qcd_os':
         Node(
             name='ff_qcd_os_down',
             formula='max(0.,1.-{sys_qcd_down})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='sys_qcd_down',
                     file='{INDIR}/{CHANNEL}/uncertainties_QCD_W{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_QCD_MVis_Iso_SS2OS_down',
                     vars=['mvis', 'mu_iso']
                 ),
                 comb.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_qcd_up_stat = replace_nodes(
        comb, 
        {'ff_qcd_os':
         Node(
             name='ff_qcd_os_up_stat',
             formula='(1.+{stat_qcd_up})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='stat_qcd_up',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_QCDSS_3D_SS_Iso_Medium_SS_InvertIso_Medium_tau_pt_vs_decayMode_error_high',
                     vars=['tau_pt','tau_decay','njets']
                 ),
                 qcd_os.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_qcd_down_stat = replace_nodes(
        comb, 
        {'ff_qcd_os':
         Node(
             name='ff_qcd_os_down_stat',
             formula='max(0.,1.-{stat_qcd_down})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='stat_qcd_down',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_QCDSS_3D_SS_Iso_Medium_SS_InvertIso_Medium_tau_pt_vs_decayMode_error_low',
                     vars=['tau_pt','tau_decay','njets']
                 ),
                 qcd_os.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_qcd_up_stat_dm0_njet0 = replace_nodes(
        comb, 
        {'ff_qcd_os':
         Node(
             name='ff_qcd_os_up_stat_dm0_njet0',
             formula='(1.+{stat_qcd_up_dm0_njet0})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='stat_qcd_up_dm0_njet0',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_QCDSS_3D_SS_Iso_Medium_SS_InvertIso_Medium_tau_pt_vs_decayMode_error_dm0_njet0_high',
                     vars=['tau_pt','tau_decay','njets']
                 ),
                 qcd_os.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_qcd_down_stat_dm0_njet0 = replace_nodes(
        comb, 
        {'ff_qcd_os':
         Node(
             name='ff_qcd_os_down_stat_dm0_njet0',
             formula='max(0.,1.-{stat_qcd_down_dm0_njet0})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='stat_qcd_down_dm0_njet0',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_QCDSS_3D_SS_Iso_Medium_SS_InvertIso_Medium_tau_pt_vs_decayMode_error_dm0_njet0_low',
                     vars=['tau_pt','tau_decay','njets']
                 ),
                 qcd_os.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_qcd_up_stat_dm0_njet1 = replace_nodes(
        comb, 
        {'ff_qcd_os':
         Node(
             name='ff_qcd_os_up_stat_dm0_njet1',
             formula='(1.+{stat_qcd_up_dm0_njet1})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='stat_qcd_up_dm0_njet1',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_QCDSS_3D_SS_Iso_Medium_SS_InvertIso_Medium_tau_pt_vs_decayMode_error_dm0_njet1_high',
                     vars=['tau_pt','tau_decay','njets']
                 ),
                 qcd_os.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_qcd_down_stat_dm0_njet1 = replace_nodes(
        comb, 
        {'ff_qcd_os':
         Node(
             name='ff_qcd_os_down_stat_dm0_njet1',
             formula='max(0.,1.-{stat_qcd_down_dm0_njet1})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='stat_qcd_down_dm0_njet1',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_QCDSS_3D_SS_Iso_Medium_SS_InvertIso_Medium_tau_pt_vs_decayMode_error_dm0_njet1_low',
                     vars=['tau_pt','tau_decay','njets']
                 ),
                 qcd_os.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_qcd_up_stat_dm1_njet0 = replace_nodes(
        comb, 
        {'ff_qcd_os':
         Node(
             name='ff_qcd_os_up_stat_dm1_njet0',
             formula='(1.+{stat_qcd_up_dm1_njet0})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='stat_qcd_up_dm1_njet0',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_QCDSS_3D_SS_Iso_Medium_SS_InvertIso_Medium_tau_pt_vs_decayMode_error_dm1_njet0_high',
                     vars=['tau_pt','tau_decay','njets']
                 ),
                 qcd_os.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_qcd_down_stat_dm1_njet0 = replace_nodes(
        comb, 
        {'ff_qcd_os':
         Node(
             name='ff_qcd_os_down_stat_dm1_njet0',
             formula='max(0.,1.-{stat_qcd_down_dm1_njet0})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='stat_qcd_down_dm1_njet0',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_QCDSS_3D_SS_Iso_Medium_SS_InvertIso_Medium_tau_pt_vs_decayMode_error_dm1_njet0_low',
                     vars=['tau_pt','tau_decay','njets']
                 ),
                 qcd_os.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_qcd_up_stat_dm1_njet1 = replace_nodes(
        comb, 
        {'ff_qcd_os':
         Node(
             name='ff_qcd_os_up_stat_dm1_njet1',
             formula='(1.+{stat_qcd_up_dm1_njet1})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='stat_qcd_up_dm1_njet1',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_QCDSS_3D_SS_Iso_Medium_SS_InvertIso_Medium_tau_pt_vs_decayMode_error_dm1_njet1_high',
                     vars=['tau_pt','tau_decay','njets']
                 ),
                 qcd_os.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_qcd_down_stat_dm1_njet1 = replace_nodes(
        comb, 
        {'ff_qcd_os':
         Node(
             name='ff_qcd_os_down_stat_dm1_njet1',
             formula='max(0.,1.-{stat_qcd_down_dm1_njet1})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='stat_qcd_down_dm1_njet1',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_QCDSS_3D_SS_Iso_Medium_SS_InvertIso_Medium_tau_pt_vs_decayMode_error_dm1_njet1_low',
                     vars=['tau_pt','tau_decay','njets']
                 ),
                 qcd_os.find('ff_qcd_os')
             ]
         )
        }
    )
    ###############################################################################################################################
    comb_w_up = replace_nodes(
        comb,
        {'ff_w':
         Node(
             name='ff_w_up',
             formula='(1.+{sys_w_up})*{ff_w}',
             leaves=[
                 Leaf(
                     name='sys_w_up',
                     file='{INDIR}/{CHANNEL}/uncertainties_QCD_W{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_W_MVis_MT_up',
                     vars=['mvis', 'mt']
                 ),
                 comb.find('ff_w')
             ]
         )
        }
    )
    comb_w_down = replace_nodes(
        comb,
        {'ff_w':
         Node(
             name='ff_w_down',
             formula='max(0.,1.-{sys_w_down})*{ff_w}',
             leaves=[
                 Leaf(
                     name='sys_w_down',
                     file='{INDIR}/{CHANNEL}/uncertainties_QCD_W{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_W_MVis_MT_down',
                     vars=['mvis', 'mt']
                 ),
                 comb.find('ff_w')
             ]
         )
        }
    )
    comb_w_up_stat_dm0_njet0 = replace_nodes(
        comb, 
        {'ff_w':
         Node(
             name='ff_w_up_stat_dm0_njet0',
             formula='(1.+{stat_w_up_dm0_njet0})*{ff_w}',
             leaves=[
                 Leaf(
                     name='stat_w_up_dm0_njet0',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_W_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_HighMT_3D_Iso_Medium_InvertIso_Medium_tau_pt_vs_decayMode_error_dm0_njet0_high',
                     vars=['tau_pt','tau_decay','njets']
                 ),
                 comb.find('ff_w')
             ]
         )
        }
    )
    comb_w_down_stat_dm0_njet0 = replace_nodes(
        comb, 
        {'ff_w':
         Node(
             name='ff_w_down_stat_dm0_njet0',
             formula='max(0.,1.-{stat_w_down_dm0_njet0})*{ff_w}',
             leaves=[
                 Leaf(
                     name='stat_w_down_dm0_njet0',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_W_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_HighMT_3D_Iso_Medium_InvertIso_Medium_tau_pt_vs_decayMode_error_dm0_njet0_low',
                     vars=['tau_pt','tau_decay','njets']
                 ),
                 comb.find('ff_w')
             ]
         )
        }
    )
    comb_w_up_stat_dm0_njet1 = replace_nodes(
        comb, 
        {'ff_w':
         Node(
             name='ff_w_up_stat_dm0_njet1',
             formula='(1.+{stat_w_up_dm0_njet1})*{ff_w}',
             leaves=[
                 Leaf(
                     name='stat_w_up_dm0_njet1',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_W_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_HighMT_3D_Iso_Medium_InvertIso_Medium_tau_pt_vs_decayMode_error_dm0_njet1_high',
                     vars=['tau_pt','tau_decay','njets']
                 ),
                 comb.find('ff_w')
             ]
         )
        }
    )
    comb_w_down_stat_dm0_njet1 = replace_nodes(
        comb, 
        {'ff_w':
         Node(
             name='ff_w_down_stat_dm0_njet1',
             formula='max(0.,1.-{stat_w_down_dm0_njet1})*{ff_w}',
             leaves=[
                 Leaf(
                     name='stat_w_down_dm0_njet1',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_W_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_HighMT_3D_Iso_Medium_InvertIso_Medium_tau_pt_vs_decayMode_error_dm0_njet1_low',
                     vars=['tau_pt','tau_decay','njets']
                 ),
                 comb.find('ff_w')
             ]
         )
        }
    )
    comb_w_up_stat_dm1_njet0 = replace_nodes(
        comb, 
        {'ff_w':
         Node(
             name='ff_w_up_stat_dm1_njet0',
             formula='(1.+{stat_w_up_dm1_njet0})*{ff_w}',
             leaves=[
                 Leaf(
                     name='stat_w_up_dm1_njet0',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_W_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_HighMT_3D_Iso_Medium_InvertIso_Medium_tau_pt_vs_decayMode_error_dm1_njet0_high',
                     vars=['tau_pt','tau_decay','njets']
                 ),
                 comb.find('ff_w')
             ]
         )
        }
    )
    comb_w_down_stat_dm1_njet0 = replace_nodes(
        comb, 
        {'ff_w':
         Node(
             name='ff_w_down_stat_dm1_njet0',
             formula='max(0.,1.-{stat_w_down_dm1_njet0})*{ff_w}',
             leaves=[
                 Leaf(
                     name='stat_w_down_dm1_njet0',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_W_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_HighMT_3D_Iso_Medium_InvertIso_Medium_tau_pt_vs_decayMode_error_dm1_njet0_low',
                     vars=['tau_pt','tau_decay','njets']
                 ),
                 comb.find('ff_w')
             ]
         )
        }
    )
    comb_w_up_stat_dm1_njet1 = replace_nodes(
        comb, 
        {'ff_w':
         Node(
             name='ff_w_up_stat_dm1_njet1',
             formula='(1.+{stat_w_up_dm1_njet1})*{ff_w}',
             leaves=[
                 Leaf(
                     name='stat_w_up_dm1_njet1',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_W_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_HighMT_3D_Iso_Medium_InvertIso_Medium_tau_pt_vs_decayMode_error_dm1_njet1_high',
                     vars=['tau_pt','tau_decay','njets']
                 ),
                 comb.find('ff_w')
             ]
         )
        }
    )
    comb_w_down_stat_dm1_njet1 = replace_nodes(
        comb, 
        {'ff_w':
         Node(
             name='ff_w_down_stat_dm1_njet1',
             formula='max(0.,1.-{stat_w_down_dm1_njet1})*{ff_w}',
             leaves=[
                 Leaf(
                     name='stat_w_down_dm1_njet1',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_W_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_HighMT_3D_Iso_Medium_InvertIso_Medium_tau_pt_vs_decayMode_error_dm1_njet1_low',
                     vars=['tau_pt','tau_decay','njets']
                 ),
                 comb.find('ff_w')
             ]
         )
        }
    )
    comb_w_up_stat = replace_nodes(
        comb, 
        {'ff_w':
         Node(
             name='ff_w_up_stat',
             formula='(1.+{stat_w_up})*{ff_w}',
             leaves=[
                 Leaf(
                     name='stat_w_up',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_W_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_HighMT_3D_Iso_Medium_InvertIso_Medium_tau_pt_vs_decayMode_error_high',
                     vars=['tau_pt','tau_decay','njets']
                 ),
                 comb.find('ff_w')
             ]
         )
        }
    )
    comb_w_down_stat = replace_nodes(
        comb, 
        {'ff_w':
         Node(
             name='ff_w_down_stat',
             formula='max(0.,1.-{stat_w_down})*{ff_w}',
             leaves=[
                 Leaf(
                     name='stat_w_down',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_W_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_HighMT_3D_Iso_Medium_InvertIso_Medium_tau_pt_vs_decayMode_error_low',
                     vars=['tau_pt','tau_decay','njets']
                 ),
                 comb.find('ff_w')
             ]
         )
        }
    )
    #####################################################################################################################
    comb_tt_up = replace_nodes(
        comb,
        {'ff_tt':
         Node(
             name='ff_tt_up',
             formula='(1.+{sys_tt_up})*{ff_tt}',
             leaves=[
                 Leaf(
                     name='sys_tt_up',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/uncertainties_TT{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_TT_MVis_up',
                     vars=['tau_decay','mvis']
                 ),
                 comb.find('ff_tt')
             ]
         )
        }
    )
    comb_tt_down = replace_nodes(
        comb,
        {'ff_tt':
         Node(
             name='ff_tt_down',
             formula='max(0.,1.-{sys_tt_down})*{ff_tt}',
             leaves=[
                 Leaf(
                     name='sys_tt_down',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/uncertainties_TT{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_TT_MVis_down',
                     vars=['tau_decay','mvis']
                 ),
                 comb.find('ff_tt')
             ]
         )
        }
    )
    comb_tt_up_stat_dm0_njet0 = replace_nodes(
        comb, 
        {'ff_tt':
         Node(
             name='ff_tt_up_stat_dm0_njet0',
             formula='(1.+{stat_tt_up_dm0_njet0})*{ff_tt}',
             leaves=[
                 Leaf(
                     name='stat_tt_up_dm0_njet0',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_TT_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_TT_anyb_addLep_InvertIso_tau_pt_vs_decayMode_error_dm0_njet0_high',
                     vars=['tau_pt','tau_decay','njets']
                 ),
                 tt.find('ff_tt')
             ]
         )
        }
    )
    comb_tt_down_stat_dm0_njet0 = replace_nodes(
        comb, 
        {'ff_tt':
         Node(
             name='ff_tt_down_stat_dm0_njet0',
             formula='max(0.,1.-{stat_tt_down_dm0_njet0})*{ff_tt}',
             leaves=[
                 Leaf(
                     name='stat_tt_down_dm0_njet0',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_TT_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_TT_anyb_addLep_InvertIso_tau_pt_vs_decayMode_error_dm0_njet0_low',
                     vars=['tau_pt','tau_decay','njets']
                 ),
                 tt.find('ff_tt')
             ]
         )
        }
    )
    comb_tt_up_stat_dm0_njet1 = replace_nodes(
        comb, 
        {'ff_tt':
         Node(
             name='ff_tt_up_stat_dm0_njet1',
             formula='(1.+{stat_tt_up_dm0_njet1})*{ff_tt}',
             leaves=[
                 Leaf(
                     name='stat_tt_up_dm0_njet1',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_TT_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_TT_anyb_addLep_InvertIso_tau_pt_vs_decayMode_error_dm0_njet1_high',
                     vars=['tau_pt','tau_decay','njets']
                 ),
                 tt.find('ff_tt')
             ]
         )
        }
    )
    comb_tt_down_stat_dm0_njet1 = replace_nodes(
        comb, 
        {'ff_tt':
         Node(
             name='ff_tt_down_stat_dm0_njet1',
             formula='max(0.,1.-{stat_tt_down_dm0_njet1})*{ff_tt}',
             leaves=[
                 Leaf(
                     name='stat_tt_down_dm0_njet1',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_TT_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_TT_anyb_addLep_InvertIso_tau_pt_vs_decayMode_error_dm0_njet1_low',
                     vars=['tau_pt','tau_decay','njets']
                 ),
                 tt.find('ff_tt')
             ]
         )
        }
    )
    comb_tt_up_stat_dm1_njet0 = replace_nodes(
        comb, 
        {'ff_tt':
         Node(
             name='ff_tt_up_stat_dm1_njet0',
             formula='(1.+{stat_tt_up_dm1_njet0})*{ff_tt}',
             leaves=[
                 Leaf(
                     name='stat_tt_up_dm1_njet0',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_TT_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_TT_anyb_addLep_InvertIso_tau_pt_vs_decayMode_error_dm1_njet0_high',
                     vars=['tau_pt','tau_decay','njets']
                 ),
                 tt.find('ff_tt')
             ]
         )
        }
    )
    comb_tt_down_stat_dm1_njet0 = replace_nodes(
        comb, 
        {'ff_tt':
         Node(
             name='ff_tt_down_stat_dm1_njet0',
             formula='max(0.,1.-{stat_tt_down_dm1_njet0})*{ff_tt}',
             leaves=[
                 Leaf(
                     name='stat_tt_down_dm1_njet0',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_TT_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_TT_anyb_addLep_InvertIso_tau_pt_vs_decayMode_error_dm1_njet0_low',
                     vars=['tau_pt','tau_decay','njets']
                 ),
                 tt.find('ff_tt')
             ]
         )
        }
    )
    comb_tt_up_stat_dm1_njet1 = replace_nodes(
        comb, 
        {'ff_tt':
         Node(
             name='ff_tt_up_stat_dm1_njet1',
             formula='(1.+{stat_tt_up_dm1_njet1})*{ff_tt}',
             leaves=[
                 Leaf(
                     name='stat_tt_up_dm1_njet1',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_TT_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_TT_anyb_addLep_InvertIso_tau_pt_vs_decayMode_error_dm1_njet1_high',
                     vars=['tau_pt','tau_decay','njets']
                 ),
                 tt.find('ff_tt')
             ]
         )
        }
    )
    comb_tt_down_stat_dm1_njet1 = replace_nodes(
        comb, 
        {'ff_tt':
         Node(
             name='ff_tt_down_stat_dm1_njet1',
             formula='max(0.,1.-{stat_tt_down_dm1_njet1})*{ff_tt}',
             leaves=[
                 Leaf(
                     name='stat_tt_down_dm1_njet1',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_TT_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_TT_anyb_addLep_InvertIso_tau_pt_vs_decayMode_error_dm1_njet1_low',
                     vars=['tau_pt','tau_decay','njets']
                 ),
                 tt.find('ff_tt')
             ]
         )
        }
    )
    comb_tt_up_stat = replace_nodes(
        comb, 
        {'ff_tt':
         Node(
             name='ff_tt_up_stat',
             formula='(1.+{stat_tt_up})*{ff_tt}',
             leaves=[
                 Leaf(
                     name='stat_tt_up',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_TT_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_TT_anyb_addLep_InvertIso_tau_pt_vs_decayMode_error_high',
                     vars=['tau_pt','tau_decay','njets']
                 ),
                 tt.find('ff_tt')
             ]
         )
        }
    )
    comb_tt_down_stat = replace_nodes(
        comb, 
        {'ff_tt':
         Node(
             name='ff_tt_down_stat',
             formula='max(0.,1.-{stat_tt_down})*{ff_tt}',
             leaves=[
                 Leaf(
                     name='stat_tt_down',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_TT_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_TT_anyb_addLep_InvertIso_tau_pt_vs_decayMode_error_low',
                     vars=['tau_pt','tau_decay','njets']
                 ),
                 tt.find('ff_tt')
             ]
         )
        }
    )
    
    
    
    fill(ff_qcd_os, qcd_os)
    fill(ff_qcd_os, qcd_os_up,   sys='ff_qcd_syst_up')
    fill(ff_qcd_os, qcd_os_down, sys='ff_qcd_syst_down')
    fill(ff_qcd_os, qcd_os_up_stat,   sys='ff_qcd_stat_up')
    fill(ff_qcd_os, qcd_os_down_stat, sys='ff_qcd_stat_down')
    fill(ff_qcd_os, frac_qcd, sys='frac_qcd')
    fill(ff_w     , w)
    fill(ff_w, frac_w, sys='frac_w')
    fill(ff_w, frac_dy, sys='frac_dy')
    fill(ff_w, w_up,   sys='ff_w_syst_up')
    fill(ff_w, w_down, sys='ff_w_syst_down')
    fill(ff_w, w_up_stat,   sys='ff_w_stat_up')
    fill(ff_w, w_down_stat, sys='ff_w_stat_down')
    fill(ff_tt    , tt)
    fill(ff_tt, tt_up,   sys='ff_tt_syst_up')
    fill(ff_tt, tt_down, sys='ff_tt_syst_down')
    fill(ff_tt, tt_up_stat,   sys='ff_tt_stat_up')
    fill(ff_tt, tt_down_stat, sys='ff_tt_stat_down')
    fill(ff_tt, frac_tt, sys='frac_tt')
    fill(ff_comb  , comb)
    fill(ff_comb, comb_qcd_up,   sys='ff_qcd_syst_up')
    fill(ff_comb, comb_qcd_down,   sys='ff_qcd_syst_down')
    fill(ff_comb, comb_qcd_up_stat,   sys='ff_qcd_stat_up')
    fill(ff_comb, comb_qcd_down_stat,   sys='ff_qcd_stat_down')
    fill(ff_comb, comb_qcd_up_stat_dm0_njet0,   sys='ff_qcd_dm0_njet0_stat_up')
    fill(ff_comb, comb_qcd_down_stat_dm0_njet0,   sys='ff_qcd_dm0_njet0_stat_down')
    fill(ff_comb, comb_qcd_up_stat_dm0_njet1,   sys='ff_qcd_dm0_njet1_stat_up')
    fill(ff_comb, comb_qcd_down_stat_dm0_njet1,   sys='ff_qcd_dm0_njet1_stat_down')
    fill(ff_comb, comb_qcd_up_stat_dm1_njet0,   sys='ff_qcd_dm1_njet0_stat_up')
    fill(ff_comb, comb_qcd_down_stat_dm1_njet0,   sys='ff_qcd_dm1_njet0_stat_down')
    fill(ff_comb, comb_qcd_up_stat_dm1_njet1,   sys='ff_qcd_dm1_njet1_stat_up')
    fill(ff_comb, comb_qcd_down_stat_dm1_njet1,   sys='ff_qcd_dm1_njet1_stat_down')
    fill(ff_comb, comb_w_up,   sys='ff_w_syst_up')
    fill(ff_comb, comb_w_down,   sys='ff_w_syst_down')
    fill(ff_comb, comb_w_up_stat,   sys='ff_w_stat_up')
    fill(ff_comb, comb_w_down_stat,   sys='ff_w_stat_down')
    fill(ff_comb, comb_w_up_stat_dm0_njet0,   sys='ff_w_dm0_njet0_stat_up')
    fill(ff_comb, comb_w_down_stat_dm0_njet0,   sys='ff_w_dm0_njet0_stat_down')
    fill(ff_comb, comb_w_up_stat_dm0_njet1,   sys='ff_w_dm0_njet1_stat_up')
    fill(ff_comb, comb_w_down_stat_dm0_njet1,   sys='ff_w_dm0_njet1_stat_down')
    fill(ff_comb, comb_w_up_stat_dm1_njet0,   sys='ff_w_dm1_njet0_stat_up')
    fill(ff_comb, comb_w_down_stat_dm1_njet0,   sys='ff_w_dm1_njet0_stat_down')
    fill(ff_comb, comb_w_up_stat_dm1_njet1,   sys='ff_w_dm1_njet1_stat_up')
    fill(ff_comb, comb_w_down_stat_dm1_njet1,   sys='ff_w_dm1_njet1_stat_down')
    fill(ff_comb, comb_tt_up,   sys='ff_tt_syst_up')
    fill(ff_comb, comb_tt_down, sys='ff_tt_syst_down')
    fill(ff_comb, comb_tt_up_stat,   sys='ff_tt_stat_up')
    fill(ff_comb, comb_tt_down_stat, sys='ff_tt_stat_down')
    fill(ff_comb, comb_tt_up_stat_dm0_njet0,   sys='ff_tt_dm0_njet0_stat_up')
    fill(ff_comb, comb_tt_down_stat_dm0_njet0, sys='ff_tt_dm0_njet0_stat_down')
    fill(ff_comb, comb_tt_up_stat_dm0_njet1,   sys='ff_tt_dm0_njet1_stat_up')
    fill(ff_comb, comb_tt_down_stat_dm0_njet1, sys='ff_tt_dm0_njet1_stat_down')
    fill(ff_comb, comb_tt_up_stat_dm1_njet0,   sys='ff_tt_dm1_njet0_stat_up')
    fill(ff_comb, comb_tt_down_stat_dm1_njet0, sys='ff_tt_dm1_njet0_stat_down')
    fill(ff_comb, comb_tt_up_stat_dm1_njet1,   sys='ff_tt_dm1_njet1_stat_up')
    fill(ff_comb, comb_tt_down_stat_dm1_njet1, sys='ff_tt_dm1_njet1_stat_down')
    
    file = ROOT.TFile.Open("{INDIR}/{CHANNEL}/{CATEGORY}/fakeFactors_{DATE}_{ISOLATION}.root".format(INDIR=indir,CHANNEL=channel,CATEGORY=category, DATE=date, ISOLATION=isolation), "recreate")
    # Write meta-data
    tag_ts     = ROOT.TString(tag)
    file.WriteObject(tag_ts     , "tag")
    # Write fake factors
    file.WriteObject(ff_qcd_os.fakefactor  , "ff_qcd_os")
    file.WriteObject(ff_w.fakefactor       , "ff_w")
    file.WriteObject(ff_tt.fakefactor      , "ff_tt")
    file.WriteObject(ff_comb.fakefactor    , "ff_comb")
    #
    file.Close()
    

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

tag='v0.2.1'
FFtype=""
#FFtype="_alt"
categories = ['inclusive','dummycat']
#categories = ['btag_looseiso', 'nobtag_looseiso']

for x in range(0,len(categories)):

    category=categories[x]
    print 'Fake factor input file for channel {0} and category {1}'.format(channel,category)
    # Individual fake factors
    ff_qcd_os = FakeFactor(vars=['tau_pt', 'tau_dr', 'njets', 'mvis', 'mt', 'mu_iso'])
    ff_qcd_ss = FakeFactor(vars=['tau_pt', 'tau_dr', 'mvis', 'mu_iso'])
    ff_w      = FakeFactor(vars=['tau_pt', 'tau_dr', 'njets', 'lep_pt', 'mvis'])
    ff_tt     = FakeFactor(vars=['tau_pt', 'tau_dr', 'njets', 'mvis', 'mt'])
    # Combined fake factor
    ff_comb   = FakeFactor(vars=['tau_pt', 'tau_dr', 'njets', 'mvis', 'lep_pt', 'mt', 'mu_iso', 'frac_qcd', 'frac_w', 'frac_tt', 'frac_w_w_up', 'frac_w_w_down', 'frac_qcd_w_up', 'frac_qcd_w_down'])
    
    
    home = os.getenv('HOME')
    
    ###########################################################################################################
    ### QCD fake factors
    
    qcd_os = Node(
        name='ff_qcd_os',
        formula='{isocorr_qcd}*{mviscorr_qcd}*{OSSS_corr_qcd}*{ff_raw_qcd}', #*{OSSS_corr_qcd}', # SS -> OS correction = 1.23
        #formula='{isocorr_qcd}*{mviscorr_qcd}*{ff_raw_qcd}',
        leaves=[
            Leaf(
                name='ff_raw_qcd',
                file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                object='FakeFactors_Data_QCDSS_3D_SS_Iso_Medium_SS_InvertIso_Medium_tau_pt_vs_decayMode',
                vars=['tau_pt','tau_dr','njets']
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

    # frac_qcd = replace_nodes(
    #     qcd_os,
    #     {'ff_qcd_os':
    #      Node(
    #          name='fracQCD',
    #          formula='{frac_qcd}+0*{ff_qcd_os}',
    #          leaves=[
    #              Leaf(
    #                  name='frac_qcd',
    #                  file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/frac_qcd.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category),
    #                  object='h_w_2d',
    #                  vars=['mvis','tau_dr']
    #              ),
    #              qcd_os.find('ff_qcd_os')
    #          ]
    #      )
    #     }
    # )
    
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
                     vars=['tau_pt','tau_dr','njets']
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
                     vars=['tau_pt','tau_dr','njets']
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
        formula='{mtcorr_w}*{ff_raw_w}*{lepPtcorr_w}',
        leaves=[
            Leaf(
                name='ff_raw_w',
                file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_W_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                object='FakeFactors_Data_HighMT_3D_Iso_Medium_InvertIso_Medium_tau_pt_vs_decayMode',
                vars=['tau_pt','tau_dr','njets']
            ),
            Leaf(
                name='lepPtcorr_w',
                file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/Correction_Data_W_lepPt{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                object='W_OS_Data_FFOSData_lepPt_correction',
                vars=['lep_pt']
            ),
            Leaf(
                name='mtcorr_w',
                file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/Correction_MC_W_MT{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                object='W_OS_MC_FFOSMC_mt_correction',
                vars=['mvis']
            )
        ]
    )
    
    # frac_w = replace_nodes(
    #     w,
    #     {'ff_w':
    #      Node(
    #          name='fracW',
    #          formula='{frac_w}+0*{ff_w}',
    #          leaves=[
    #              Leaf(
    #                  name='frac_w',
    #                  file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/frac_wjets.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category),
    #                  object='h_w_2d',
    #                  vars=['mvis','tau_dr']
    #              ),
    #              w.find('ff_w')
    #          ]
    #      )
    #     }
    # )
    
    # frac_dy = replace_nodes(
    #     w,
    #     {'ff_w':
    #      Node(
    #          name='fracDY',
    #          formula='{frac_dy}+0*{ff_w}',
    #          leaves=[
    #              Leaf(
    #                  name='frac_dy',
    #                  file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/frac_dy.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category),
    #                  object='h_w_2d',
    #                  vars=['mvis','tau_dr']
    #              ),
    #              w.find('ff_w')
    #          ]
    #  )
    #     }
    # )
    
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
                     vars=['lep_pt', 'mvis']
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
                     vars=['lep_pt', 'mvis']
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
                     vars=['tau_pt','tau_dr','njets']
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
                     vars=['tau_pt','tau_dr','njets']
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
                vars=['tau_pt','tau_dr','njets']
            ),
            Leaf(
                name='mviscorr_tt',
                file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/Correction_MC_TT_MVis{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                object='TT_OS_MC_mvis_correction',
                vars=['mvis']
            ),
        ]
    )

    # frac_tt = replace_nodes(
    #     tt,
    #     {'ff_tt':
    #      Node(
    #          name='fracTT',
    #          formula='{frac_tt}+0*{ff_tt}',
    #          leaves=[
    #              Leaf(
    #                  name='frac_tt',
    #                  file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/frac_tt.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category),
    #                  object='h_w_2d',
    #                  vars=['mvis','tau_dr']
    #              ),
    #              tt.find('ff_tt')
    #          ]
    #      )
    #     }
    # )
    
    tt_up = replace_nodes(
        tt,
        {'ff_tt':
         Node(
             name='ff_tt_up',
             formula='(1.+abs({sys_tt_up}))*{ff_tt}',
             leaves=[
                 Leaf(
                     name='sys_tt_up',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/uncertainties_TT{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_TT_MVis_up',
                     vars=['tau_dr','mvis']
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
             formula='max(0.,1.-abs({sys_tt_down}))*{ff_tt}',
             leaves=[
                 Leaf(
                     name='sys_tt_down',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/uncertainties_TT{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_TT_MVis_down',
                     vars=['tau_dr','mvis']
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
                     vars=['tau_pt','tau_dr','njets']
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
                     vars=['tau_pt','tau_dr','njets']
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
        #formula='{frac_tt}*{ff_tt} + ({frac_w}+(1-{frac_qcd}-{frac_w}-{frac_tt}))*{ff_w} + {frac_qcd}*{ff_qcd_os}',
        formula='{frac_tt}*{ff_tt} + {frac_w}*{ff_w} + {frac_qcd}*{ff_qcd_os}',
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

    comb_onlyw = Node(
        formula='0*{frac_tt}*{ff_tt} + {frac_w}*{ff_w}/{frac_w} + 0*{frac_qcd}*{ff_qcd_os}',
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
    comb_onlyqcd = Node(
        formula='0*{frac_tt}*{ff_tt} + 0*{frac_w}*{ff_w} + {frac_qcd}*{ff_qcd_os}/{frac_qcd}',
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
    comb_onlytt = Node(
        formula='{frac_tt}*{ff_tt}/{frac_tt} + 0*{frac_w}*{ff_w} + 0*{frac_qcd}*{ff_qcd_os}',
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
    comb_fracw = Node(
        name='ff_fracw',
        formula='0*{frac_tt}*{ff_tt} + {frac_w}*{ff_w}/{ff_w} + 0*{frac_qcd}*{ff_qcd_os}',
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
    comb_fracqcd = Node(
        name='ff_fracqcd',
        formula='0*{frac_tt}*{ff_tt} + 0*{frac_w}*{ff_w} + {frac_qcd}*{ff_qcd_os}/{ff_qcd_os}',
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
    comb_fractt = Node(
        name='ff_fractt',
        formula='{frac_tt}*{ff_tt}/{ff_tt} + 0*{frac_w}*{ff_w} + 0*{frac_qcd}*{ff_qcd_os}',
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

    comb_frac_w_up = Node(
        name='ff_frac_w_up',
        formula='{frac_tt}*{ff_tt} + {frac_w_w_up}*{ff_w} + {frac_qcd_w_up}*{ff_qcd_os}',
        leaves=[
            # Individual fake factors
            qcd_os,
            w,
            tt,
            # Fractions
            Leaf(
                name='frac_qcd_w_up',
                file='{INDIR}/constant.root'.format(INDIR=indir),
                object='constant',
                vars=['frac_qcd_w_up']
            ),
            Leaf(
                name='frac_w_w_up',
                file='{INDIR}/constant.root'.format(INDIR=indir),
                object='constant',
                vars=['frac_w_w_up']
            ),
            Leaf(
                name='frac_tt',
                file='{INDIR}/constant.root'.format(INDIR=indir),
                object='constant',
                vars=['frac_tt']
            ),
        ]
    )
    comb_frac_w_down = Node(
        name='ff_frac_w_down',
        formula='{frac_tt}*{ff_tt} + {frac_w_w_down}*{ff_w} + {frac_qcd_w_down}*{ff_qcd_os}',
        leaves=[
            # Individual fake factors
            qcd_os,
            w,
            tt,
            # Fractions
            Leaf(
                name='frac_qcd_w_down',
                file='{INDIR}/constant.root'.format(INDIR=indir),
                object='constant',
                vars=['frac_qcd_w_down']
            ),
            Leaf(
                name='frac_w_w_down',
                file='{INDIR}/constant.root'.format(INDIR=indir),
                object='constant',
                vars=['frac_w_w_down']
            ),
            Leaf(
                name='frac_tt',
                file='{INDIR}/constant.root'.format(INDIR=indir),
                object='constant',
                vars=['frac_tt']
            ),
        ]
    )

    comb = Node(
        name='ff_comb',
        #formula='{frac_tt}*{ff_tt} + ({frac_w}+(1-{frac_qcd}-{frac_w}-{frac_tt}))*{ff_w} + {frac_qcd}*{ff_qcd_os}',
        formula='{frac_tt}*{ff_tt} + {frac_w}*{ff_w} + {frac_qcd}*{ff_qcd_os}',
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

    comb_corr_qcd_mvis_up = replace_nodes(
        comb,
        {'ff_qcd_os':
         Node(
             name='ff_corr_qcd_mvis_up',
             formula='{ff_qcd_os}*({mviscorr_qcd_temp})',
             leaves=[
                    Leaf(
                        name='mviscorr_qcd_temp',
                        file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/Correction_Data_QCD_MVis{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                        object='QCD_SS_MuMedium_Data_FFSSMuMediumData_mvis_correction',
                        vars=['mvis']
                    ),
                 comb.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_corr_qcd_mvis_down = replace_nodes(
        comb,
        {'ff_qcd_os':
         Node(
             name='ff_corr_qcd_mvis_down',
             formula='{ff_qcd_os}/({mviscorr_qcd_temp})',
             leaves=[
                    Leaf(
                        name='mviscorr_qcd_temp',
                        file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/Correction_Data_QCD_MVis{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                        object='QCD_SS_MuMedium_Data_FFSSMuMediumData_mvis_correction',
                        vars=['mvis']
                    ),
                 comb.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_corr_qcd_mvis_osss_up = replace_nodes(
        comb,
        {'ff_qcd_os':
         Node(
             name='ff_corr_qcd_mvis_osss_up',
             formula='{ff_qcd_os}*({OSSS_corr_qcd_temp})',
             leaves=[
                    Leaf(
                        name='OSSS_corr_qcd_temp',
                        file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/Correction_Data_QCD_OSSS{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                        object='QCD_SS_Data_FFSSMuMediumData_OSSS_correction',
                        vars=['mvis']
                    ),
                 comb.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_corr_qcd_mvis_osss_down = replace_nodes(
        comb,
        {'ff_qcd_os':
         Node(
             name='ff_corr_qcd_mvis_osss_down',
             formula='{ff_qcd_os}/({OSSS_corr_qcd_temp})',
             leaves=[
                    Leaf(
                        name='OSSS_corr_qcd_temp',
                        file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/Correction_Data_QCD_OSSS{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                        object='QCD_SS_Data_FFSSMuMediumData_OSSS_correction',
                        vars=['mvis']
                    ),
                 comb.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_corr_qcd_muiso_up = replace_nodes(
        comb,
        {'ff_qcd_os':
         Node(
             name='ff_corr_qcd_muiso_up',
             formula='{ff_qcd_os}*({isocorr_qcd_temp})',
             leaves=[
                    Leaf(
                        name='isocorr_qcd_temp',
                        file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/Correction_Data_QCD_MuIso{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                        object='QCD_SS_Data_FFSSMuMediumData_isomu_correction',
                        vars=['mu_iso']
                    ),
                 comb.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_corr_qcd_muiso_down = replace_nodes(
        comb,
        {'ff_qcd_os':
         Node(
             name='ff_corr_qcd_muiso_down',
             formula='{ff_qcd_os}/({isocorr_qcd_temp})',
             leaves=[
                    Leaf(
                        name='isocorr_qcd_temp',
                        file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/Correction_Data_QCD_MuIso{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                        object='QCD_SS_Data_FFSSMuMediumData_isomu_correction',
                        vars=['mu_iso']
                    ),
                 comb.find('ff_qcd_os')
             ]
         )
        }
    )

    comb_qcd_mvis_up = replace_nodes(
        comb,
        {'ff_qcd_os':
         Node(
             name='ff_qcd_mvis_up',
             formula='(1.+{sys_qcd_mvis_up})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='sys_qcd_mvis_up',
                     file='{INDIR}/{CHANNEL}/uncertainties_QCD_W{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_QCD_MVis_Iso_SS2OS_morphed_mvis_up',
                     vars=['mvis']
                 ),
                 comb.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_qcd_mvis_down = replace_nodes(
        comb,
        {'ff_qcd_os':
         Node(
             name='ff_qcd_mvis_down',
             formula='(1.+{sys_qcd_mvis_down})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='sys_qcd_mvis_down',
                     file='{INDIR}/{CHANNEL}/uncertainties_QCD_W{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_QCD_MVis_Iso_SS2OS_morphed_mvis_down',
                     vars=['mvis']
                 ),
                 comb.find('ff_qcd_os')
             ]
         )
        }
    )

    comb_qcd_mvis_osss_up = replace_nodes(
        comb,
        {'ff_qcd_os':
         Node(
             name='ff_qcd_mvis_osss_up',
             formula='(1.+{sys_qcd_mvis_osss_up})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='sys_qcd_mvis_osss_up',
                     file='{INDIR}/{CHANNEL}/uncertainties_QCD_W{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_QCD_MVis_Iso_SS2OS_morphed_mvis_osss_up',
                     vars=['mvis']
                 ),
                 comb.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_qcd_mvis_osss_down = replace_nodes(
        comb,
        {'ff_qcd_os':
         Node(
             name='ff_qcd_mvis_osss_down',
             formula='(1.+{sys_qcd_mvis_osss_down})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='sys_qcd_mvis_osss_down',
                     file='{INDIR}/{CHANNEL}/uncertainties_QCD_W{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_QCD_MVis_Iso_SS2OS_morphed_mvis_osss_down',
                     vars=['mvis']
                 ),
                 comb.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_qcd_muiso_up = replace_nodes(
        comb,
        {'ff_qcd_os':
         Node(
             name='ff_qcd_muiso_up',
             formula='(1.+{sys_qcd_muiso_up})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='sys_qcd_muiso_up',
                     file='{INDIR}/{CHANNEL}/uncertainties_QCD_W{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_QCD_MVis_Iso_SS2OS_morphed_pt_up',
                     vars=['mu_iso']
                 ),
                 comb.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_qcd_muiso_down = replace_nodes(
        comb,
        {'ff_qcd_os':
         Node(
             name='ff_qcd_muiso_down',
             formula='(1.+{sys_qcd_muiso_down})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='sys_qcd_muiso_down',
                     file='{INDIR}/{CHANNEL}/uncertainties_QCD_W{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_QCD_MVis_Iso_SS2OS_morphed_pt_down',
                     vars=['mu_iso']
                 ),
                 comb.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_qcd_mc_up = replace_nodes(
        comb,
        {'ff_qcd_os':
         Node(
             name='ff_qcd_mc_up',
             formula='(1.+sqrt(({sys_qcd_mvis_mcup}**2)+({sys_qcd_muiso_mcup}**2)+({ff_raw_qcd_mcup}**2)))*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='sys_qcd_mvis_mcup',
                     file='{INDIR}/{CHANNEL}/FF_corr_QCD_MCsum_noGen_nonclosure.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='nonclosure_mcup_QCD',
                     vars=['mvis']
                 ),
                 Leaf(
                     name='sys_qcd_muiso_mcup',
                     file='{INDIR}/{CHANNEL}/FF_corr_QCD_MCsum_noGen_muisocorr.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='muiso_mcup_QCD',
                     vars=['mu_iso']
                 ),
                Leaf(
                    name='ff_raw_qcd_mcup',
                    file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                    object='FakeFactors_Data_QCDSS_3D_SS_Iso_Medium_SS_InvertIso_Medium_tau_pt_vs_decayMode_error_mc_high',
                    vars=['tau_pt','tau_dr','njets']
                ),
                 comb.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_qcd_mc_down = replace_nodes(
        comb,
        {'ff_qcd_os':
         Node(
             name='ff_qcd_mc_down',
             formula='(1.-sqrt(({sys_qcd_mvis_mcdown}**2)+({sys_qcd_muiso_mcdown}**2)+({ff_raw_qcd_mcdown}**2)))*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='sys_qcd_mvis_mcdown',
                     file='{INDIR}/{CHANNEL}/FF_corr_QCD_MCsum_noGen_nonclosure.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='nonclosure_mcdown_QCD',
                     vars=['mvis']
                 ),
                 Leaf(
                     name='sys_qcd_muiso_mcdown',
                     file='{INDIR}/{CHANNEL}/FF_corr_QCD_MCsum_noGen_muisocorr.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='muiso_mcdown_QCD',
                     vars=['mu_iso']
                 ),
                Leaf(
                    name='ff_raw_qcd_mcdown',
                    file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                    object='FakeFactors_Data_QCDSS_3D_SS_Iso_Medium_SS_InvertIso_Medium_tau_pt_vs_decayMode_error_mc_low',
                    vars=['tau_pt','tau_dr','njets']
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
                     vars=['tau_pt','tau_dr','njets']
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
                     vars=['tau_pt','tau_dr','njets']
                 ),
                 qcd_os.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_qcd_up_stat_dr0_njet0 = replace_nodes(
        comb, 
        {'ff_qcd_os':
         Node(
             name='ff_qcd_os_up_stat_dr0_njet0',
             formula='(1.+{stat_qcd_up_dr0_njet0})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='stat_qcd_up_dr0_njet0',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_QCDSS_3D_SS_Iso_Medium_SS_InvertIso_Medium_tau_pt_vs_decayMode_error_dr0_njet0_high',
                     vars=['tau_pt','tau_dr','njets']
                 ),
                 qcd_os.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_qcd_down_stat_dr0_njet0 = replace_nodes(
        comb, 
        {'ff_qcd_os':
         Node(
             name='ff_qcd_os_down_stat_dr0_njet0',
             formula='max(0.,1.-{stat_qcd_down_dr0_njet0})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='stat_qcd_down_dr0_njet0',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_QCDSS_3D_SS_Iso_Medium_SS_InvertIso_Medium_tau_pt_vs_decayMode_error_dr0_njet0_low',
                     vars=['tau_pt','tau_dr','njets']
                 ),
                 qcd_os.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_qcd_up_stat_dr0_njet1 = replace_nodes(
        comb, 
        {'ff_qcd_os':
         Node(
             name='ff_qcd_os_up_stat_dr0_njet1',
             formula='(1.+{stat_qcd_up_dr0_njet1})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='stat_qcd_up_dr0_njet1',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_QCDSS_3D_SS_Iso_Medium_SS_InvertIso_Medium_tau_pt_vs_decayMode_error_dr0_njet1_high',
                     vars=['tau_pt','tau_dr','njets']
                 ),
                 qcd_os.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_qcd_down_stat_dr0_njet1 = replace_nodes(
        comb, 
        {'ff_qcd_os':
         Node(
             name='ff_qcd_os_down_stat_dr0_njet1',
             formula='max(0.,1.-{stat_qcd_down_dr0_njet1})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='stat_qcd_down_dr0_njet1',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_QCDSS_3D_SS_Iso_Medium_SS_InvertIso_Medium_tau_pt_vs_decayMode_error_dr0_njet1_low',
                     vars=['tau_pt','tau_dr','njets']
                 ),
                 qcd_os.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_qcd_up_stat_dr0_njet2 = replace_nodes(
        comb, 
        {'ff_qcd_os':
         Node(
             name='ff_qcd_os_up_stat_dr0_njet2',
             formula='(1.+{stat_qcd_up_dr0_njet2})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='stat_qcd_up_dr0_njet2',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_QCDSS_3D_SS_Iso_Medium_SS_InvertIso_Medium_tau_pt_vs_decayMode_error_dr0_njet2_high',
                     vars=['tau_pt','tau_dr','njets']
                 ),
                 qcd_os.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_qcd_down_stat_dr0_njet2 = replace_nodes(
        comb, 
        {'ff_qcd_os':
         Node(
             name='ff_qcd_os_down_stat_dr0_njet2',
             formula='max(0.,1.-{stat_qcd_down_dr0_njet2})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='stat_qcd_down_dr0_njet2',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_QCDSS_3D_SS_Iso_Medium_SS_InvertIso_Medium_tau_pt_vs_decayMode_error_dr0_njet2_low',
                     vars=['tau_pt','tau_dr','njets']
                 ),
                 qcd_os.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_qcd_up_stat_dr1_njet0 = replace_nodes(
        comb, 
        {'ff_qcd_os':
         Node(
             name='ff_qcd_os_up_stat_dr1_njet0',
             formula='(1.+{stat_qcd_up_dr1_njet0})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='stat_qcd_up_dr1_njet0',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_QCDSS_3D_SS_Iso_Medium_SS_InvertIso_Medium_tau_pt_vs_decayMode_error_dr1_njet0_high',
                     vars=['tau_pt','tau_dr','njets']
                 ),
                 qcd_os.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_qcd_down_stat_dr1_njet0 = replace_nodes(
        comb, 
        {'ff_qcd_os':
         Node(
             name='ff_qcd_os_down_stat_dr1_njet0',
             formula='max(0.,1.-{stat_qcd_down_dr1_njet0})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='stat_qcd_down_dr1_njet0',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_QCDSS_3D_SS_Iso_Medium_SS_InvertIso_Medium_tau_pt_vs_decayMode_error_dr1_njet0_low',
                     vars=['tau_pt','tau_dr','njets']
                 ),
                 qcd_os.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_qcd_up_stat_dr1_njet1 = replace_nodes(
        comb, 
        {'ff_qcd_os':
         Node(
             name='ff_qcd_os_up_stat_dr1_njet1',
             formula='(1.+{stat_qcd_up_dr1_njet1})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='stat_qcd_up_dr1_njet1',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_QCDSS_3D_SS_Iso_Medium_SS_InvertIso_Medium_tau_pt_vs_decayMode_error_dr1_njet1_high',
                     vars=['tau_pt','tau_dr','njets']
                 ),
                 qcd_os.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_qcd_down_stat_dr1_njet1 = replace_nodes(
        comb, 
        {'ff_qcd_os':
         Node(
             name='ff_qcd_os_down_stat_dr1_njet1',
             formula='max(0.,1.-{stat_qcd_down_dr1_njet1})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='stat_qcd_down_dr1_njet1',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_QCDSS_3D_SS_Iso_Medium_SS_InvertIso_Medium_tau_pt_vs_decayMode_error_dr1_njet1_low',
                     vars=['tau_pt','tau_dr','njets']
                 ),
                 qcd_os.find('ff_qcd_os')
             ]
         )
        }
    ) 
    comb_qcd_up_stat_dr0_njet0_morphed = replace_nodes(
        comb, 
        {'ff_qcd_os':
         Node(
             name='ff_qcd_os_up_stat_dr0_njet0_morphed',
             formula='(1.+{stat_qcd_up_dr0_njet0_morphed})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='stat_qcd_up_dr0_njet0_morphed',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_QCDSS_3D_SS_Iso_Medium_SS_InvertIso_Medium_tau_pt_vs_decayMode_error_dr0_njet0_morphed_high',
                     vars=['tau_pt','tau_dr','njets']
                 ),
                 comb.find('ff_qcd_os')
             ]
         )
        }
    )   
    comb_qcd_down_stat_dr0_njet0_morphed = replace_nodes(
        comb, 
        {'ff_qcd_os':
         Node(
             name='ff_qcd_os_down_stat_dr0_njet0_morphed',
             formula='max(0.,1.+{stat_qcd_down_dr0_njet0_morphed})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='stat_qcd_down_dr0_njet0_morphed',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_QCDSS_3D_SS_Iso_Medium_SS_InvertIso_Medium_tau_pt_vs_decayMode_error_dr0_njet0_morphed_low',
                     vars=['tau_pt','tau_dr','njets']
                 ),
                 comb.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_qcd_up_stat_dr0_njet1_morphed = replace_nodes(
        comb, 
        {'ff_qcd_os':
         Node(
             name='ff_qcd_os_up_stat_dr0_njet1_morphed',
             formula='(1.+{stat_qcd_up_dr0_njet1_morphed})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='stat_qcd_up_dr0_njet1_morphed',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_QCDSS_3D_SS_Iso_Medium_SS_InvertIso_Medium_tau_pt_vs_decayMode_error_dr0_njet1_morphed_high',
                     vars=['tau_pt','tau_dr','njets']
                 ),
                 comb.find('ff_qcd_os')
             ]
         )
        }
    )   
    comb_qcd_down_stat_dr0_njet1_morphed = replace_nodes(
        comb, 
        {'ff_qcd_os':
         Node(
             name='ff_qcd_os_down_stat_dr0_njet1_morphed',
             formula='max(0.,1.+{stat_qcd_down_dr0_njet1_morphed})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='stat_qcd_down_dr0_njet1_morphed',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_QCDSS_3D_SS_Iso_Medium_SS_InvertIso_Medium_tau_pt_vs_decayMode_error_dr0_njet1_morphed_low',
                     vars=['tau_pt','tau_dr','njets']
                 ),
                 comb.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_qcd_up_stat_dr0_njet2_morphed = replace_nodes(
        comb, 
        {'ff_qcd_os':
         Node(
             name='ff_qcd_os_up_stat_dr0_njet2_morphed',
             formula='(1.+{stat_qcd_up_dr0_njet2_morphed})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='stat_qcd_up_dr0_njet2_morphed',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_QCDSS_3D_SS_Iso_Medium_SS_InvertIso_Medium_tau_pt_vs_decayMode_error_dr0_njet2_morphed_high',
                     vars=['tau_pt','tau_dr','njets']
                 ),
                 comb.find('ff_qcd_os')
             ]
         )
        }
    )   
    comb_qcd_down_stat_dr0_njet2_morphed = replace_nodes(
        comb, 
        {'ff_qcd_os':
         Node(
             name='ff_qcd_os_down_stat_dr0_njet2_morphed',
             formula='max(0.,1.+{stat_qcd_down_dr0_njet2_morphed})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='stat_qcd_down_dr0_njet2_morphed',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_QCDSS_3D_SS_Iso_Medium_SS_InvertIso_Medium_tau_pt_vs_decayMode_error_dr0_njet2_morphed_low',
                     vars=['tau_pt','tau_dr','njets']
                 ),
                 comb.find('ff_qcd_os')
             ]
         )
        }
    )

    comb_qcd_up_stat_dr1_njet1_morphed = replace_nodes(
        comb, 
        {'ff_qcd_os':
         Node(
             name='ff_qcd_os_up_stat_dr1_njet1_morphed',
             formula='(1.+{stat_qcd_up_dr1_njet1_morphed})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='stat_qcd_up_dr1_njet1_morphed',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_QCDSS_3D_SS_Iso_Medium_SS_InvertIso_Medium_tau_pt_vs_decayMode_error_dr1_njet1_morphed_high',
                     vars=['tau_pt','tau_dr','njets']
                 ),
                 comb.find('ff_qcd_os')
             ]
         )
        }
    )   
    comb_qcd_down_stat_dr1_njet1_morphed = replace_nodes(
        comb, 
        {'ff_qcd_os':
         Node(
             name='ff_qcd_os_down_stat_dr1_njet1_morphed',
             formula='max(0.,1.+{stat_qcd_down_dr1_njet1_morphed})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='stat_qcd_down_dr1_njet1_morphed',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_QCDSS_3D_SS_Iso_Medium_SS_InvertIso_Medium_tau_pt_vs_decayMode_error_dr1_njet1_morphed_low',
                     vars=['tau_pt','tau_dr','njets']
                 ),
                 comb.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_qcd_up_stat_dr1_njet0_morphed = replace_nodes(
        comb, 
        {'ff_qcd_os':
         Node(
             name='ff_qcd_os_up_stat_dr1_njet0_morphed',
             formula='(1.+{stat_qcd_up_dr1_njet0_morphed})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='stat_qcd_up_dr1_njet0_morphed',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_QCDSS_3D_SS_Iso_Medium_SS_InvertIso_Medium_tau_pt_vs_decayMode_error_dr1_njet0_morphed_high',
                     vars=['tau_pt','tau_dr','njets']
                 ),
                 comb.find('ff_qcd_os')
             ]
         )
        }
    )   
    comb_qcd_down_stat_dr1_njet0_morphed = replace_nodes(
        comb, 
        {'ff_qcd_os':
         Node(
             name='ff_qcd_os_down_stat_dr1_njet0_morphed',
             formula='max(0.,1.+{stat_qcd_down_dr1_njet0_morphed})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='stat_qcd_down_dr1_njet0_morphed',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_QCDSS_3D_SS_Iso_Medium_SS_InvertIso_Medium_tau_pt_vs_decayMode_error_dr1_njet0_morphed_low',
                     vars=['tau_pt','tau_dr','njets']
                 ),
                 comb.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_qcd_up_stat_dr1_njet2_morphed = replace_nodes(
        comb, 
        {'ff_qcd_os':
         Node(
             name='ff_qcd_os_up_stat_dr1_njet2_morphed',
             formula='(1.+{stat_qcd_up_dr1_njet2_morphed})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='stat_qcd_up_dr1_njet2_morphed',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_QCDSS_3D_SS_Iso_Medium_SS_InvertIso_Medium_tau_pt_vs_decayMode_error_dr1_njet2_morphed_high',
                     vars=['tau_pt','tau_dr','njets']
                 ),
                 comb.find('ff_qcd_os')
             ]
         )
        }
    )   
    comb_qcd_down_stat_dr1_njet2_morphed = replace_nodes(
        comb, 
        {'ff_qcd_os':
         Node(
             name='ff_qcd_os_down_stat_dr1_njet2_morphed',
             formula='max(0.,1.+{stat_qcd_down_dr1_njet2_morphed})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='stat_qcd_down_dr1_njet2_morphed',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_QCDSS_3D_SS_Iso_Medium_SS_InvertIso_Medium_tau_pt_vs_decayMode_error_dr1_njet2_morphed_low',
                     vars=['tau_pt','tau_dr','njets']
                 ),
                 comb.find('ff_qcd_os')
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
                     vars=['lep_pt', 'mvis']
                 ),
                 comb.find('ff_w')
             ]
         )
        }
    )
    comb_w_lepPt_up = replace_nodes(
        comb,
        {'ff_w':
         Node(
             name='ff_w_lepPt_up',
             formula='(1.+{sys_w_lepPt_up})*{ff_w}',
             leaves=[
                 Leaf(
                     name='sys_w_lepPt_up',
                     file='{INDIR}/{CHANNEL}/uncertainties_QCD_W{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_W_MVis_MT_morphed_lepPt_up',
                     vars=['lep_pt']
                 ),
                 comb.find('ff_w')
             ]
         )
        }
    )
    comb_w_mc_up = replace_nodes(
        comb,
        {'ff_w':
         Node(
             name='ff_w_mc_up',
             formula='(1.+sqrt(({sys_w_lepPt_mcup}**2)+({ff_raw_w_mcup}**2)))*{ff_w}',
             leaves=[
                 Leaf(
                     name='sys_w_lepPt_mcup',
                     file='{INDIR}/{CHANNEL}/FF_corr_Wjets_MCsum_noGen_nonclosure.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='nonclosure_mcup_Wjets',
                     vars=['lep_pt']
                 ),
            Leaf(
                name='ff_raw_w_mcup',
                file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_W_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                object='FakeFactors_Data_HighMT_3D_Iso_Medium_InvertIso_Medium_tau_pt_vs_decayMode_error_mc_high',
                vars=['tau_pt','tau_dr','njets']
            ),
                 comb.find('ff_w')
             ]
         )
        }
    )
    comb_w_mc_lepPt_up = replace_nodes(
        comb,
        {'ff_w':
         Node(
             name='ff_w_mc_lepPt_up',
             formula='(1.+{sys_w_lepPt_mcup})*{ff_w}',
             leaves=[
                 Leaf(
                     name='sys_w_lepPt_mcup',
                     file='{INDIR}/{CHANNEL}/FF_corr_Wjets_MCsum_noGen_nonclosure.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='nonclosure_mcup_Wjets',
                     vars=['lep_pt']
                 ),
                 comb.find('ff_w')
             ]
         )
        }
    )
    comb_w_mc_lepPt_down = replace_nodes(
        comb,
        {'ff_w':
         Node(
             name='ff_w_mc_lepPt_down',
             formula='(1.+{sys_w_lepPt_mcdown})*{ff_w}',
             leaves=[
                 Leaf(
                     name='sys_w_lepPt_mcdown',
                     file='{INDIR}/{CHANNEL}/FF_corr_Wjets_MCsum_noGen_nonclosure.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='nonclosure_mcdown_Wjets',
                     vars=['lep_pt']
                 ),
                 comb.find('ff_w')
             ]
         )
        }
    )
    comb_w_mc_down = replace_nodes(
        comb,
        {'ff_w':
         Node(
             name='ff_w_mc_down',
             formula='(1.-sqrt(({sys_w_lepPt_mcdown}**2)+({ff_raw_w_mcdown}**2)))*{ff_w}',
             leaves=[
                 Leaf(
                     name='sys_w_lepPt_mcdown',
                     file='{INDIR}/{CHANNEL}/FF_corr_Wjets_MCsum_noGen_nonclosure.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='nonclosure_mcdown_Wjets',
                     vars=['lep_pt']
                 ),
            Leaf(
                name='ff_raw_w_mcdown',
                file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_W_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                object='FakeFactors_Data_HighMT_3D_Iso_Medium_InvertIso_Medium_tau_pt_vs_decayMode_error_mc_low',
                vars=['tau_pt','tau_dr','njets']
            ),
                 comb.find('ff_w')
             ]
         )
        }
    )
    comb_w_lepPt_down = replace_nodes(
        comb,
        {'ff_w':
         Node(
             name='ff_w_lepPt_down',
             formula='(1.+{sys_w_lepPt_down})*{ff_w}',
             leaves=[
                 Leaf(
                     name='sys_w_lepPt_down',
                     file='{INDIR}/{CHANNEL}/uncertainties_QCD_W{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_W_MVis_MT_morphed_lepPt_down',
                     vars=['lep_pt']
                 ),
                 comb.find('ff_w')
             ]
         )
        }
    )
    comb_w_mt_up = replace_nodes(
        comb,
        {'ff_w':
         Node(
             name='ff_w_mt_up',
             formula='(1.+{sys_w_mt_up})*{ff_w}',
             leaves=[
                 Leaf(
                     name='sys_w_mt_up',
                     file='{INDIR}/{CHANNEL}/uncertainties_QCD_W{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_W_MVis_MT_morphed_mt_up',
                     vars=['mvis']
                 ),
                 comb.find('ff_w')
             ]
         )
        }
    )
    comb_corr_w_lepPt_up = replace_nodes(
        comb,
        {'ff_w':
         Node(
             name='ff_corr_w_lepPt_up',
             formula='({ff_w})*({lepPtcorr_w_temp})',
             leaves=[
                    Leaf(
                        name='lepPtcorr_w_temp',
                        file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/Correction_Data_W_lepPt{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                        object='W_OS_Data_FFOSData_lepPt_correction',
                        vars=['lep_pt']
                    ),
                 comb.find('ff_w')
             ]
         )
        }
    )

    comb_corr_w_lepPt_down = replace_nodes(
        comb,
        {'ff_w':
         Node(
             name='ff_corr_w_lepPt_down',
             formula='{ff_w}/({lepPtcorr_w_temp})',
             leaves=[
                    Leaf(
                        name='lepPtcorr_w_temp',
                        file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/Correction_Data_W_lepPt{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                        object='W_OS_Data_FFOSData_lepPt_correction',
                        vars=['lep_pt']
                    ),
                 comb.find('ff_w')
             ]
         )
        }
    )
    comb_corr_w_mt_up = replace_nodes(
        comb,
        {'ff_w':
         Node(
             name='ff_corr_w_mt_up',
             formula='{ff_w}*({mtcorr_w_temp})',
             leaves=[
                    Leaf(
                        name='mtcorr_w_temp',
                        file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/Correction_MC_W_MT{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                        object='W_OS_MC_FFOSMC_mt_correction',
                        vars=['mvis']
                    ),
                 comb.find('ff_w')
             ]
         )
        }
    )

    comb_corr_w_mt_down = replace_nodes(
        comb,
        {'ff_w':
         Node(
             name='ff_corr_w_mt_down',
             formula='{ff_w}/({mtcorr_w_temp})',
             leaves=[
                    Leaf(
                        name='mtcorr_w_temp',
                        file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/Correction_MC_W_MT{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                        object='W_OS_MC_FFOSMC_mt_correction',
                        vars=['mvis']
                    ),
                 comb.find('ff_w')
             ]
         )
        }
    )


    comb_w_mt_down = replace_nodes(
        comb,
        {'ff_w':
         Node(
             name='ff_w_mt_down',
             formula='(1.+{sys_w_mt_down})*{ff_w}',
             leaves=[
                 Leaf(
                     name='sys_w_mt_down',
                     file='{INDIR}/{CHANNEL}/uncertainties_QCD_W{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_W_MVis_MT_morphed_mt_down',
                     vars=['mvis']
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
                     vars=['mvis', 'mvis']
                 ),
                 comb.find('ff_w')
             ]
         )
        }
    )
    comb_w_up_stat_dr0_njet0 = replace_nodes(
        comb, 
        {'ff_w':
         Node(
             name='ff_w_up_stat_dr0_njet0',
             formula='(1.+{stat_w_up_dr0_njet0})*{ff_w}',
             leaves=[
                 Leaf(
                     name='stat_w_up_dr0_njet0',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_W_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_HighMT_3D_Iso_Medium_InvertIso_Medium_tau_pt_vs_decayMode_error_dr0_njet0_high',
                     vars=['tau_pt','tau_dr','njets']
                 ),
                 comb.find('ff_w')
             ]
         )
        }
    )
 
    comb_w_down_stat_dr0_njet0 = replace_nodes(
        comb, 
        {'ff_w':
         Node(
             name='ff_w_down_stat_dr0_njet0',
             formula='max(0.,1.-{stat_w_down_dr0_njet0})*{ff_w}',
             leaves=[
                 Leaf(
                     name='stat_w_down_dr0_njet0',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_W_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_HighMT_3D_Iso_Medium_InvertIso_Medium_tau_pt_vs_decayMode_error_dr0_njet0_low',
                     vars=['tau_pt','tau_dr','njets']
                 ),
                 comb.find('ff_w')
             ]
         )
        }
    )
    comb_w_up_stat_dr0_njet1 = replace_nodes(
        comb, 
        {'ff_w':
         Node(
             name='ff_w_up_stat_dr0_njet1',
             formula='(1.+{stat_w_up_dr0_njet1})*{ff_w}',
             leaves=[
                 Leaf(
                     name='stat_w_up_dr0_njet1',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_W_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_HighMT_3D_Iso_Medium_InvertIso_Medium_tau_pt_vs_decayMode_error_dr0_njet1_high',
                     vars=['tau_pt','tau_dr','njets']
                 ),
                 comb.find('ff_w')
             ]
         )
        }
    )
    comb_w_down_stat_dr0_njet1 = replace_nodes(
        comb, 
        {'ff_w':
         Node(
             name='ff_w_down_stat_dr0_njet1',
             formula='max(0.,1.-{stat_w_down_dr0_njet1})*{ff_w}',
             leaves=[
                 Leaf(
                     name='stat_w_down_dr0_njet1',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_W_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_HighMT_3D_Iso_Medium_InvertIso_Medium_tau_pt_vs_decayMode_error_dr0_njet1_low',
                     vars=['tau_pt','tau_dr','njets']
                 ),
                 comb.find('ff_w')
             ]
         )
        }
    )
    comb_w_up_stat_dr0_njet2 = replace_nodes(
        comb, 
        {'ff_w':
         Node(
             name='ff_w_up_stat_dr0_njet2',
             formula='(1.+{stat_w_up_dr0_njet2})*{ff_w}',
             leaves=[
                 Leaf(
                     name='stat_w_up_dr0_njet2',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_W_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_HighMT_3D_Iso_Medium_InvertIso_Medium_tau_pt_vs_decayMode_error_dr0_njet2_high',
                     vars=['tau_pt','tau_dr','njets']
                 ),
                 comb.find('ff_w')
             ]
         )
        }
    )
    comb_w_down_stat_dr0_njet2 = replace_nodes(
        comb, 
        {'ff_w':
         Node(
             name='ff_w_down_stat_dr0_njet2',
             formula='max(0.,1.-{stat_w_down_dr0_njet2})*{ff_w}',
             leaves=[
                 Leaf(
                     name='stat_w_down_dr0_njet2',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_W_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_HighMT_3D_Iso_Medium_InvertIso_Medium_tau_pt_vs_decayMode_error_dr0_njet2_low',
                     vars=['tau_pt','tau_dr','njets']
                 ),
                 comb.find('ff_w')
             ]
         )
        }
    )
    comb_w_up_stat_dr0_njet0_morphed = replace_nodes(
        comb, 
        {'ff_w':
         Node(
             name='ff_w_up_stat_dr0_njet0_morphed',
             formula='(1.+{stat_w_up_dr0_njet0_morphed})*{ff_w}',
             leaves=[
                 Leaf(
                     name='stat_w_up_dr0_njet0_morphed',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_W_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_HighMT_3D_Iso_Medium_InvertIso_Medium_tau_pt_vs_decayMode_error_dr0_njet0_morphed_high',
                     vars=['tau_pt','tau_dr','njets']
                 ),
                 comb.find('ff_w')
             ]
         )
        }
    )   
    comb_w_down_stat_dr0_njet0_morphed = replace_nodes(
        comb, 
        {'ff_w':
         Node(
             name='ff_w_down_stat_dr0_njet0_morphed',
             formula='max(0.,1.+{stat_w_down_dr0_njet0_morphed})*{ff_w}',
             leaves=[
                 Leaf(
                     name='stat_w_down_dr0_njet0_morphed',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_W_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_HighMT_3D_Iso_Medium_InvertIso_Medium_tau_pt_vs_decayMode_error_dr0_njet0_morphed_low',
                     vars=['tau_pt','tau_dr','njets']
                 ),
                 comb.find('ff_w')
             ]
         )
        }
    )

    comb_w_up_stat_dr0_njet1_morphed = replace_nodes(
        comb, 
        {'ff_w':
         Node(
             name='ff_w_up_stat_dr0_njet1_morphed',
             formula='(1.+{stat_w_up_dr0_njet1_morphed})*{ff_w}',
             leaves=[
                 Leaf(
                     name='stat_w_up_dr0_njet1_morphed',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_W_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_HighMT_3D_Iso_Medium_InvertIso_Medium_tau_pt_vs_decayMode_error_dr0_njet1_morphed_high',
                     vars=['tau_pt','tau_dr','njets']
                 ),
                 comb.find('ff_w')
             ]
         )
        }
    )   
    comb_w_down_stat_dr0_njet1_morphed = replace_nodes(
        comb, 
        {'ff_w':
         Node(
             name='ff_w_down_stat_dr0_njet1_morphed',
             formula='max(0.,1.+{stat_w_down_dr0_njet1_morphed})*{ff_w}',
             leaves=[
                 Leaf(
                     name='stat_w_down_dr0_njet1_morphed',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_W_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_HighMT_3D_Iso_Medium_InvertIso_Medium_tau_pt_vs_decayMode_error_dr0_njet1_morphed_low',
                     vars=['tau_pt','tau_dr','njets']
                 ),
                 comb.find('ff_w')
             ]
         )
        }
    )
    comb_w_up_stat_dr0_njet2_morphed = replace_nodes(
        comb, 
        {'ff_w':
         Node(
             name='ff_w_up_stat_dr0_njet2_morphed',
             formula='(1.+{stat_w_up_dr0_njet2_morphed})*{ff_w}',
             leaves=[
                 Leaf(
                     name='stat_w_up_dr0_njet2_morphed',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_W_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_HighMT_3D_Iso_Medium_InvertIso_Medium_tau_pt_vs_decayMode_error_dr0_njet2_morphed_high',
                     vars=['tau_pt','tau_dr','njets']
                 ),
                 comb.find('ff_w')
             ]
         )
        }
    )   
    comb_w_down_stat_dr0_njet2_morphed = replace_nodes(
        comb, 
        {'ff_w':
         Node(
             name='ff_w_down_stat_dr0_njet2_morphed',
             formula='max(0.,1.+{stat_w_down_dr0_njet2_morphed})*{ff_w}',
             leaves=[
                 Leaf(
                     name='stat_w_down_dr0_njet2_morphed',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_W_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_HighMT_3D_Iso_Medium_InvertIso_Medium_tau_pt_vs_decayMode_error_dr0_njet2_morphed_low',
                     vars=['tau_pt','tau_dr','njets']
                 ),
                 comb.find('ff_w')
             ]
         )
        }
    )
    comb_w_up_stat_dr1_njet0 = replace_nodes(
        comb, 
        {'ff_w':
         Node(
             name='ff_w_up_stat_dr1_njet0',
             formula='(1.+{stat_w_up_dr1_njet0})*{ff_w}',
             leaves=[
                 Leaf(
                     name='stat_w_up_dr1_njet0',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_W_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_HighMT_3D_Iso_Medium_InvertIso_Medium_tau_pt_vs_decayMode_error_dr1_njet0_high',
                     vars=['tau_pt','tau_dr','njets']
                 ),
                 comb.find('ff_w')
             ]
         )
        }
    )
    comb_w_down_stat_dr1_njet0 = replace_nodes(
        comb, 
        {'ff_w':
         Node(
             name='ff_w_down_stat_dr1_njet0',
             formula='max(0.,1.-{stat_w_down_dr1_njet0})*{ff_w}',
             leaves=[
                 Leaf(
                     name='stat_w_down_dr1_njet0',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_W_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_HighMT_3D_Iso_Medium_InvertIso_Medium_tau_pt_vs_decayMode_error_dr1_njet0_low',
                     vars=['tau_pt','tau_dr','njets']
                 ),
                 comb.find('ff_w')
             ]
         )
        }
    )
    comb_w_up_stat_dr1_njet1 = replace_nodes(
        comb, 
        {'ff_w':
         Node(
             name='ff_w_up_stat_dr1_njet1',
             formula='(1.+{stat_w_up_dr1_njet1})*{ff_w}',
             leaves=[
                 Leaf(
                     name='stat_w_up_dr1_njet1',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_W_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_HighMT_3D_Iso_Medium_InvertIso_Medium_tau_pt_vs_decayMode_error_dr1_njet1_high',
                     vars=['tau_pt','tau_dr','njets']
                 ),
                 comb.find('ff_w')
             ]
         )
        }
    )
    comb_w_down_stat_dr1_njet1 = replace_nodes(
        comb, 
        {'ff_w':
         Node(
             name='ff_w_down_stat_dr1_njet1',
             formula='max(0.,1.-{stat_w_down_dr1_njet1})*{ff_w}',
             leaves=[
                 Leaf(
                     name='stat_w_down_dr1_njet1',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_W_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_HighMT_3D_Iso_Medium_InvertIso_Medium_tau_pt_vs_decayMode_error_dr1_njet1_low',
                     vars=['tau_pt','tau_dr','njets']
                 ),
                 comb.find('ff_w')
             ]
         )
        }
    )
    comb_w_up_stat_dr1_njet2 = replace_nodes(
        comb, 
        {'ff_w':
         Node(
             name='ff_w_up_stat_dr1_njet2',
             formula='(1.+{stat_w_up_dr1_njet2})*{ff_w}',
             leaves=[
                 Leaf(
                     name='stat_w_up_dr1_njet2',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_W_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_HighMT_3D_Iso_Medium_InvertIso_Medium_tau_pt_vs_decayMode_error_dr1_njet2_high',
                     vars=['tau_pt','tau_dr','njets']
                 ),
                 comb.find('ff_w')
             ]
         )
        }
    )
    comb_w_down_stat_dr1_njet2 = replace_nodes(
        comb, 
        {'ff_w':
         Node(
             name='ff_w_down_stat_dr1_njet2',
             formula='max(0.,1.-{stat_w_down_dr1_njet2})*{ff_w}',
             leaves=[
                 Leaf(
                     name='stat_w_down_dr1_njet2',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_W_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_HighMT_3D_Iso_Medium_InvertIso_Medium_tau_pt_vs_decayMode_error_dr1_njet2_low',
                     vars=['tau_pt','tau_dr','njets']
                 ),
                 comb.find('ff_w')
             ]
         )
        }
    )
    comb_w_up_stat_dr1_njet0_morphed = replace_nodes(
        comb, 
        {'ff_w':
         Node(
             name='ff_w_up_stat_dr1_njet0_morphed',
             formula='(1.+{stat_w_up_dr1_njet0_morphed})*{ff_w}',
             leaves=[
                 Leaf(
                     name='stat_w_up_dr1_njet0_morphed',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_W_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_HighMT_3D_Iso_Medium_InvertIso_Medium_tau_pt_vs_decayMode_error_dr1_njet0_morphed_high',
                     vars=['tau_pt','tau_dr','njets']
                 ),
                 comb.find('ff_w')
             ]
         )
        }
    )   
    comb_w_down_stat_dr1_njet0_morphed = replace_nodes(
        comb, 
        {'ff_w':
         Node(
             name='ff_w_down_stat_dr1_njet0_morphed',
             formula='max(0.,1.+{stat_w_down_dr1_njet0_morphed})*{ff_w}',
             leaves=[
                 Leaf(
                     name='stat_w_down_dr1_njet0_morphed',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_W_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_HighMT_3D_Iso_Medium_InvertIso_Medium_tau_pt_vs_decayMode_error_dr1_njet0_morphed_low',
                     vars=['tau_pt','tau_dr','njets']
                 ),
                 comb.find('ff_w')
             ]
         )
        }
    )

    comb_w_up_stat_dr1_njet1_morphed = replace_nodes(
        comb, 
        {'ff_w':
         Node(
             name='ff_w_up_stat_dr1_njet1_morphed',
             formula='(1.+{stat_w_up_dr1_njet1_morphed})*{ff_w}',
             leaves=[
                 Leaf(
                     name='stat_w_up_dr1_njet1_morphed',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_W_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_HighMT_3D_Iso_Medium_InvertIso_Medium_tau_pt_vs_decayMode_error_dr1_njet1_morphed_high',
                     vars=['tau_pt','tau_dr','njets']
                 ),
                 comb.find('ff_w')
             ]
         )
        }
    )   
    comb_w_down_stat_dr1_njet1_morphed = replace_nodes(
        comb, 
        {'ff_w':
         Node(
             name='ff_w_down_stat_dr1_njet1_morphed',
             formula='max(0.,1.+{stat_w_down_dr1_njet1_morphed})*{ff_w}',
             leaves=[
                 Leaf(
                     name='stat_w_down_dr1_njet1_morphed',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_W_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_HighMT_3D_Iso_Medium_InvertIso_Medium_tau_pt_vs_decayMode_error_dr1_njet1_morphed_low',
                     vars=['tau_pt','tau_dr','njets']
                 ),
                 comb.find('ff_w')
             ]
         )
        }
    )
    comb_w_up_stat_dr1_njet2_morphed = replace_nodes(
        comb, 
        {'ff_w':
         Node(
             name='ff_w_up_stat_dr1_njet2_morphed',
             formula='(1.+{stat_w_up_dr1_njet2_morphed})*{ff_w}',
             leaves=[
                 Leaf(
                     name='stat_w_up_dr1_njet2_morphed',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_W_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_HighMT_3D_Iso_Medium_InvertIso_Medium_tau_pt_vs_decayMode_error_dr1_njet2_morphed_high',
                     vars=['tau_pt','tau_dr','njets']
                 ),
                 comb.find('ff_w')
             ]
         )
        }
    )   
    comb_w_down_stat_dr1_njet2_morphed = replace_nodes(
        comb, 
        {'ff_w':
         Node(
             name='ff_w_down_stat_dr1_njet2_morphed',
             formula='max(0.,1.+{stat_w_down_dr1_njet2_morphed})*{ff_w}',
             leaves=[
                 Leaf(
                     name='stat_w_down_dr1_njet2_morphed',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_W_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_HighMT_3D_Iso_Medium_InvertIso_Medium_tau_pt_vs_decayMode_error_dr1_njet2_morphed_low',
                     vars=['tau_pt','tau_dr','njets']
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
                     vars=['tau_pt','tau_dr','njets']
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
                     vars=['tau_pt','tau_dr','njets']
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
                     vars=['tau_dr','mvis']
                 ),
                 comb.find('ff_tt')
             ]
         )
        }
    )
    comb_corr_tt_up = replace_nodes(
        comb,
        {'ff_tt':
         Node(
             name='ff_corr_tt_up',
             formula='{ff_tt}*({mviscorr_tt_temp})',
             leaves=[
                    Leaf(
                        name='mviscorr_tt_temp',
                        file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/Correction_MC_TT_MVis{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                        object='TT_OS_MC_mvis_correction',
                        vars=['mvis']
                    ),
                 comb.find('ff_tt')
             ]
         )
        }
    )
    comb_corr_tt_down = replace_nodes(
        comb,
        {'ff_tt':
         Node(
             name='ff_corr_tt_down',
             formula='{ff_tt}/({mviscorr_tt_temp})',
             leaves=[
                    Leaf(
                        name='mviscorr_tt_temp',
                        file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/Correction_MC_TT_MVis{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                        object='TT_OS_MC_mvis_correction',
                        vars=['mvis']
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
                     vars=['tau_dr','mvis']
                 ),
                 comb.find('ff_tt')
             ]
         )
        }
    )
    comb_tt_morphed_up = replace_nodes(
        comb,
        {'ff_tt':
         Node(
             name='ff_tt_morphed_up',
             formula='(1.+{sys_tt_morphed_up})*{ff_tt}',
             leaves=[
                 Leaf(
                     name='sys_tt_morphed_up',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/uncertainties_TT{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_TT_MVis_morphed_up',
                     vars=['mvis']
                 ),
                 comb.find('ff_tt')
             ]
         )
        }
    )
    comb_tt_morphed_down = replace_nodes(
        comb,
        {'ff_tt':
         Node(
             name='ff_tt_morphed_down',
             formula='(1.+{sys_tt_morphed_down})*{ff_tt}',
             leaves=[
                 Leaf(
                     name='sys_tt_morphed_down',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/uncertainties_TT{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_TT_MVis_morphed_down',
                     vars=['mvis']
                 ),
                 comb.find('ff_tt')
             ]
         )
        }
    )
    comb_tt_scalefactor_up = replace_nodes(
        comb,
        {'ff_tt':
         Node(
             name='ff_tt_sf_up',
             formula='(1.+{sys_tt_sf_up})*{ff_tt}',
             leaves=[
                 Leaf(
                     name='sys_tt_sf_up',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/uncertainties_TT{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_TT_MVis_sf',
                     vars=['mvis']
                 ),
                 comb.find('ff_tt')
             ]
         )
        }
    )
    comb_tt_scalefactor_down = replace_nodes(
        comb,
        {'ff_tt':
         Node(
             name='ff_tt_sf_down',
             formula='(1.-{sys_tt_sf_down})*{ff_tt}',
             leaves=[
                 Leaf(
                     name='sys_tt_sf_down',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/uncertainties_TT{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_TT_MVis_sf',
                     vars=['mvis']
                 ),
                 comb.find('ff_tt')
             ]
         )
        }
    )
    comb_tt_up_stat_dr0_njet0 = replace_nodes(
        comb, 
        {'ff_tt':
         Node(
             name='ff_tt_up_stat_dr0_njet0',
             formula='(1.+{stat_tt_up_dr0_njet0})*{ff_tt}',
             leaves=[
                 Leaf(
                     name='stat_tt_up_dr0_njet0',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_TT_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_TT_anyb_addLep_InvertIso_tau_pt_vs_decayMode_error_dr0_njet0_high',
                     vars=['tau_pt','tau_dr','njets']
                 ),
                 tt.find('ff_tt')
             ]
         )
        }
    )

    comb_tt_down_stat_dr0_njet0 = replace_nodes(
        comb, 
        {'ff_tt':
         Node(
             name='ff_tt_down_stat_dr0_njet0',
             formula='max(0.,1.-{stat_tt_down_dr0_njet0})*{ff_tt}',
             leaves=[
                 Leaf(
                     name='stat_tt_down_dr0_njet0',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_TT_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_TT_anyb_addLep_InvertIso_tau_pt_vs_decayMode_error_dr0_njet0_low',
                     vars=['tau_pt','tau_dr','njets']
                 ),
                 tt.find('ff_tt')
             ]
         )
        }
    )
    comb_tt_up_stat_dr0_njet1 = replace_nodes(
        comb, 
        {'ff_tt':
         Node(
             name='ff_tt_up_stat_dr0_njet1',
             formula='(1.+{stat_tt_up_dr0_njet1})*{ff_tt}',
             leaves=[
                 Leaf(
                     name='stat_tt_up_dr0_njet1',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_TT_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_TT_anyb_addLep_InvertIso_tau_pt_vs_decayMode_error_dr0_njet1_high',
                     vars=['tau_pt','tau_dr','njets']
                 ),
                 tt.find('ff_tt')
             ]
         )
        }
    )
    comb_tt_down_stat_dr0_njet1 = replace_nodes(
        comb, 
        {'ff_tt':
         Node(
             name='ff_tt_down_stat_dr0_njet1',
             formula='max(0.,1.-{stat_tt_down_dr0_njet1})*{ff_tt}',
             leaves=[
                 Leaf(
                     name='stat_tt_down_dr0_njet1',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_TT_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_TT_anyb_addLep_InvertIso_tau_pt_vs_decayMode_error_dr0_njet1_low',
                     vars=['tau_pt','tau_dr','njets']
                 ),
                 tt.find('ff_tt')
             ]
         )
        }
    )
    comb_tt_up_stat_dr1_njet0 = replace_nodes(
        comb, 
        {'ff_tt':
         Node(
             name='ff_tt_up_stat_dr1_njet0',
             formula='(1.+{stat_tt_up_dr1_njet0})*{ff_tt}',
             leaves=[
                 Leaf(
                     name='stat_tt_up_dr1_njet0',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_TT_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_TT_anyb_addLep_InvertIso_tau_pt_vs_decayMode_error_dr1_njet0_high',
                     vars=['tau_pt','tau_dr','njets']
                 ),
                 tt.find('ff_tt')
             ]
         )
        }
    )
    comb_tt_down_stat_dr1_njet0 = replace_nodes(
        comb, 
        {'ff_tt':
         Node(
             name='ff_tt_down_stat_dr1_njet0',
             formula='max(0.,1.-{stat_tt_down_dr1_njet0})*{ff_tt}',
             leaves=[
                 Leaf(
                     name='stat_tt_down_dr1_njet0',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_TT_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_TT_anyb_addLep_InvertIso_tau_pt_vs_decayMode_error_dr1_njet0_low',
                     vars=['tau_pt','tau_dr','njets']
                 ),
                 tt.find('ff_tt')
             ]
         )
        }
    )
    comb_tt_up_stat_dr1_njet1 = replace_nodes(
        comb, 
        {'ff_tt':
         Node(
             name='ff_tt_up_stat_dr1_njet1',
             formula='(1.+{stat_tt_up_dr1_njet1})*{ff_tt}',
             leaves=[
                 Leaf(
                     name='stat_tt_up_dr1_njet1',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_TT_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_TT_anyb_addLep_InvertIso_tau_pt_vs_decayMode_error_dr1_njet1_high',
                     vars=['tau_pt','tau_dr','njets']
                 ),
                 tt.find('ff_tt')
             ]
         )
        }
    )
    comb_tt_down_stat_dr1_njet1 = replace_nodes(
        comb, 
        {'ff_tt':
         Node(
             name='ff_tt_down_stat_dr1_njet1',
             formula='max(0.,1.-{stat_tt_down_dr1_njet1})*{ff_tt}',
             leaves=[
                 Leaf(
                     name='stat_tt_down_dr1_njet1',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_TT_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_TT_anyb_addLep_InvertIso_tau_pt_vs_decayMode_error_dr1_njet1_low',
                     vars=['tau_pt','tau_dr','njets']
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
                     vars=['tau_pt','tau_dr','njets']
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
                     vars=['tau_pt','tau_dr','njets']
                 ),
                 tt.find('ff_tt')
             ]
         )
        }
    )
    comb_tt_up_stat_dr0_njet0_morphed = replace_nodes(
        comb, 
        {'ff_tt':
         Node(
             name='ff_tt_up_stat_dr0_njet0_morphed',
             formula='(1.+{stat_tt_up_dr0_njet0_morphed})*{ff_tt}',
             leaves=[
                 Leaf(
                     name='stat_tt_up_dr0_njet0_morphed',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_TT_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_TT_anyb_addLep_InvertIso_tau_pt_vs_decayMode_error_dr0_njet0_morphed_high',
                     vars=['tau_pt','tau_dr','njets']
                 ),
                 comb.find('ff_tt')
             ]
         )
        }
    )   
    comb_tt_down_stat_dr0_njet0_morphed = replace_nodes(
        comb, 
        {'ff_tt':
         Node(
             name='ff_tt_down_stat_dr0_njet0_morphed',
             formula='max(0.,1.+{stat_tt_down_dr0_njet0_morphed})*{ff_tt}',
             leaves=[
                 Leaf(
                     name='stat_tt_down_dr0_njet0_morphed',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_TT_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_TT_anyb_addLep_InvertIso_tau_pt_vs_decayMode_error_dr0_njet0_morphed_low',
                     vars=['tau_pt','tau_dr','njets']
                 ),
                 comb.find('ff_tt')
             ]
         )
        }
    )

    comb_tt_up_stat_dr0_njet1_morphed = replace_nodes(
        comb, 
        {'ff_tt':
         Node(
             name='ff_tt_up_stat_dr0_njet1_morphed',
             formula='(1.+{stat_tt_up_dr0_njet1_morphed})*{ff_tt}',
             leaves=[
                 Leaf(
                     name='stat_tt_up_dr0_njet1_morphed',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_TT_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_TT_anyb_addLep_InvertIso_tau_pt_vs_decayMode_error_dr0_njet1_morphed_high',
                     vars=['tau_pt','tau_dr','njets']
                 ),
                 comb.find('ff_tt')
             ]
         )
        }
    )   
    comb_tt_down_stat_dr0_njet1_morphed = replace_nodes(
        comb, 
        {'ff_tt':
         Node(
             name='ff_tt_down_stat_dr0_njet1_morphed',
             formula='max(0.,1.+{stat_tt_down_dr0_njet1_morphed})*{ff_tt}',
             leaves=[
                 Leaf(
                     name='stat_tt_down_dr0_njet1_morphed',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_TT_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_TT_anyb_addLep_InvertIso_tau_pt_vs_decayMode_error_dr0_njet1_morphed_low',
                     vars=['tau_pt','tau_dr','njets']
                 ),
                 comb.find('ff_tt')
             ]
         )
        }
    )
   
    
    fill(ff_qcd_os, qcd_os)
    fill(ff_qcd_os, qcd_os_up,   sys='ff_qcd_syst_up')
    fill(ff_qcd_os, qcd_os_down, sys='ff_qcd_syst_down')
    fill(ff_qcd_os, qcd_os_up_stat,   sys='ff_qcd_stat_up')
    fill(ff_qcd_os, qcd_os_down_stat, sys='ff_qcd_stat_down')
    # fill(ff_qcd_os, frac_qcd, sys='frac_qcd')
    fill(ff_w     , w)
    # fill(ff_w, frac_w, sys='frac_w')
    # fill(ff_w, frac_dy, sys='frac_dy')
    fill(ff_w, w_up,   sys='ff_w_syst_up')
    fill(ff_w, w_down, sys='ff_w_syst_down')
    fill(ff_w, w_up_stat,   sys='ff_w_stat_up')
    fill(ff_w, w_down_stat, sys='ff_w_stat_down')
    fill(ff_tt    , tt)
    fill(ff_tt, tt_up,   sys='ff_tt_syst_up')
    fill(ff_tt, tt_down, sys='ff_tt_syst_down')
    fill(ff_tt, tt_up_stat,   sys='ff_tt_stat_up')
    fill(ff_tt, tt_down_stat, sys='ff_tt_stat_down')
    # fill(ff_tt, frac_tt, sys='frac_tt')
    fill(ff_comb  , comb)
    fill(ff_comb  , comb_onlyw, sys='ff_onlyw')
    fill(ff_comb  , comb_onlyqcd, sys='ff_onlyqcd')
    fill(ff_comb  , comb_onlytt, sys='ff_onlytt')
    fill(ff_comb  , comb_fracw, sys='ff_fracw')
    fill(ff_comb  , comb_fracqcd, sys='ff_fracqcd')
    fill(ff_comb  , comb_fractt, sys='ff_fractt')
    fill(ff_comb, comb_qcd_up,   sys='ff_qcd_syst_up')
    fill(ff_comb, comb_qcd_down,   sys='ff_qcd_syst_down')
    fill(ff_comb  , comb_frac_w_up, sys='ff_frac_w_up')
    fill(ff_comb  , comb_frac_w_down, sys='ff_frac_w_down')

    fill(ff_comb, comb_qcd_mvis_up,   sys='ff_qcd_mvis_up')
    fill(ff_comb, comb_qcd_mvis_down,   sys='ff_qcd_mvis_down')
    fill(ff_comb, comb_qcd_mvis_osss_up,   sys='ff_qcd_mvis_osss_up')
    fill(ff_comb, comb_qcd_mvis_osss_down,   sys='ff_qcd_mvis_osss_down')
    fill(ff_comb, comb_qcd_muiso_up,   sys='ff_qcd_muiso_up')
    fill(ff_comb, comb_qcd_muiso_down,   sys='ff_qcd_muiso_down')
    fill(ff_comb, comb_corr_qcd_mvis_up,   sys='ff_corr_qcd_mvis_up')
    fill(ff_comb, comb_corr_qcd_mvis_down,   sys='ff_corr_qcd_mvis_down')
    fill(ff_comb, comb_corr_qcd_mvis_osss_up,   sys='ff_corr_qcd_mvis_osss_up')
    fill(ff_comb, comb_corr_qcd_mvis_osss_down,   sys='ff_corr_qcd_mvis_osss_down')
    fill(ff_comb, comb_corr_qcd_muiso_up,   sys='ff_corr_qcd_muiso_up')
    fill(ff_comb, comb_corr_qcd_muiso_down,   sys='ff_corr_qcd_muiso_down')
    fill(ff_comb, comb_qcd_mc_up,   sys='ff_qcd_mc_up')
    fill(ff_comb, comb_qcd_mc_down,   sys='ff_qcd_mc_down')
    fill(ff_comb, comb_w_mc_lepPt_up,   sys='ff_w_mc_lepPt_up')
    fill(ff_comb, comb_w_mc_lepPt_down,   sys='ff_w_mc_lepPt_down')


    fill(ff_comb, comb_qcd_up_stat,   sys='ff_qcd_stat_up')
    fill(ff_comb, comb_qcd_down_stat,   sys='ff_qcd_stat_down')
    fill(ff_comb, comb_qcd_up_stat_dr0_njet0,   sys='ff_qcd_dr0_njet0_stat_up')
    fill(ff_comb, comb_qcd_down_stat_dr0_njet0,   sys='ff_qcd_dr0_njet0_stat_down')
    fill(ff_comb, comb_qcd_up_stat_dr0_njet1,   sys='ff_qcd_dr0_njet1_stat_up')
    fill(ff_comb, comb_qcd_down_stat_dr0_njet1,   sys='ff_qcd_dr0_njet1_stat_down')
    fill(ff_comb, comb_qcd_up_stat_dr0_njet2,   sys='ff_qcd_dr0_njet2_stat_up')
    fill(ff_comb, comb_qcd_down_stat_dr0_njet2,   sys='ff_qcd_dr0_njet2_stat_down')
    fill(ff_comb, comb_qcd_up_stat_dr1_njet0,   sys='ff_qcd_dr1_njet0_stat_up')
    fill(ff_comb, comb_qcd_down_stat_dr1_njet0,   sys='ff_qcd_dr1_njet0_stat_down')
    fill(ff_comb, comb_qcd_up_stat_dr1_njet1,   sys='ff_qcd_dr1_njet1_stat_up')
    fill(ff_comb, comb_qcd_down_stat_dr1_njet1,   sys='ff_qcd_dr1_njet1_stat_down')
    fill(ff_comb, comb_qcd_up_stat_dr0_njet0_morphed,   sys='ff_qcd_dr0_njet0_morphed_stat_up')
    fill(ff_comb, comb_qcd_down_stat_dr0_njet0_morphed,   sys='ff_qcd_dr0_njet0_morphed_stat_down')
    fill(ff_comb, comb_qcd_up_stat_dr0_njet1_morphed,   sys='ff_qcd_dr0_njet1_morphed_stat_up')
    fill(ff_comb, comb_qcd_down_stat_dr0_njet1_morphed,   sys='ff_qcd_dr0_njet1_morphed_stat_down')
    fill(ff_comb, comb_qcd_up_stat_dr0_njet2_morphed,   sys='ff_qcd_dr0_njet2_morphed_stat_up')
    fill(ff_comb, comb_qcd_down_stat_dr0_njet2_morphed,   sys='ff_qcd_dr0_njet2_morphed_stat_down')
    fill(ff_comb, comb_w_up,   sys='ff_w_syst_up')
    fill(ff_comb, comb_w_down,   sys='ff_w_syst_down')
    fill(ff_comb, comb_w_lepPt_up, sys='ff_w_lepPt_up')
    fill(ff_comb, comb_w_lepPt_down, sys='ff_w_lepPt_down')
    fill(ff_comb, comb_w_mc_up, sys='ff_w_mc_up')
    fill(ff_comb, comb_w_mc_down, sys='ff_w_mc_down')
    fill(ff_comb, comb_w_mt_up, sys='ff_w_mt_up')
    fill(ff_comb, comb_w_mt_down, sys='ff_w_mt_down')
    fill(ff_comb, comb_corr_w_lepPt_up, sys='ff_corr_w_lepPt_up')
    fill(ff_comb, comb_corr_w_lepPt_down, sys='ff_corr_w_lepPt_down')
    fill(ff_comb, comb_corr_w_mt_up, sys='ff_corr_w_mt_up')
    fill(ff_comb, comb_corr_w_mt_down, sys='ff_corr_w_mt_down')

    fill(ff_comb, comb_w_up_stat,   sys='ff_w_stat_up')
    fill(ff_comb, comb_w_down_stat,   sys='ff_w_stat_down')
    fill(ff_comb, comb_w_up_stat_dr0_njet0,   sys='ff_w_dr0_njet0_stat_up')
    fill(ff_comb, comb_w_down_stat_dr0_njet0,   sys='ff_w_dr0_njet0_stat_down')
    fill(ff_comb, comb_w_up_stat_dr0_njet1,   sys='ff_w_dr0_njet1_stat_up')
    fill(ff_comb, comb_w_down_stat_dr0_njet1,   sys='ff_w_dr0_njet1_stat_down')
    fill(ff_comb, comb_w_up_stat_dr0_njet2,   sys='ff_w_dr0_njet2_stat_up')
    fill(ff_comb, comb_w_down_stat_dr0_njet2,   sys='ff_w_dr0_njet2_stat_down')
    fill(ff_comb, comb_w_up_stat_dr0_njet0_morphed,   sys='ff_w_dr0_njet0_morphed_stat_up')
    fill(ff_comb, comb_w_down_stat_dr0_njet0_morphed,   sys='ff_w_dr0_njet0_morphed_stat_down')
    fill(ff_comb, comb_w_up_stat_dr0_njet2_morphed,   sys='ff_w_dr0_njet2_morphed_stat_up')
    fill(ff_comb, comb_w_down_stat_dr0_njet2_morphed,   sys='ff_w_dr0_njet2_morphed_stat_down')
    fill(ff_comb, comb_w_up_stat_dr0_njet1_morphed,   sys='ff_w_dr0_njet1_morphed_stat_up')
    fill(ff_comb, comb_w_down_stat_dr0_njet1_morphed,   sys='ff_w_dr0_njet1_morphed_stat_down')
    fill(ff_comb, comb_w_up_stat_dr1_njet0,   sys='ff_w_dr1_njet0_stat_up')
    fill(ff_comb, comb_w_down_stat_dr1_njet0,   sys='ff_w_dr1_njet0_stat_down')
    fill(ff_comb, comb_w_up_stat_dr1_njet1,   sys='ff_w_dr1_njet1_stat_up')
    fill(ff_comb, comb_w_down_stat_dr1_njet1,   sys='ff_w_dr1_njet1_stat_down')
    fill(ff_comb, comb_w_up_stat_dr1_njet2,   sys='ff_w_dr1_njet2_stat_up')
    fill(ff_comb, comb_w_down_stat_dr1_njet2,   sys='ff_w_dr1_njet2_stat_down')
    fill(ff_comb, comb_w_up_stat_dr1_njet0_morphed,   sys='ff_w_dr1_njet0_morphed_stat_up')
    fill(ff_comb, comb_w_down_stat_dr1_njet0_morphed,   sys='ff_w_dr1_njet0_morphed_stat_down')
    fill(ff_comb, comb_w_up_stat_dr1_njet2_morphed,   sys='ff_w_dr1_njet2_morphed_stat_up')
    fill(ff_comb, comb_w_down_stat_dr1_njet2_morphed,   sys='ff_w_dr1_njet2_morphed_stat_down')
    fill(ff_comb, comb_w_up_stat_dr1_njet1_morphed,   sys='ff_w_dr1_njet1_morphed_stat_up')
    fill(ff_comb, comb_w_down_stat_dr1_njet1_morphed,   sys='ff_w_dr1_njet1_morphed_stat_down')
    fill(ff_comb, comb_w_up_stat_dr1_njet0,   sys='ff_w_dr1_njet0_stat_up')
    fill(ff_comb, comb_w_down_stat_dr1_njet0,   sys='ff_w_dr1_njet0_stat_down')
    fill(ff_comb, comb_w_up_stat_dr1_njet1,   sys='ff_w_dr1_njet1_stat_up')
    fill(ff_comb, comb_w_down_stat_dr1_njet1,   sys='ff_w_dr1_njet1_stat_down')
    fill(ff_comb, comb_tt_up,   sys='ff_tt_syst_up')
    fill(ff_comb, comb_tt_down, sys='ff_tt_syst_down')
    fill(ff_comb, comb_corr_tt_up,   sys='ff_corr_tt_syst_up')
    fill(ff_comb, comb_corr_tt_down, sys='ff_corr_tt_syst_down')
    fill(ff_comb, comb_tt_morphed_up,   sys='ff_tt_morphed_up')
    fill(ff_comb, comb_tt_morphed_down, sys='ff_tt_morphed_down')
    fill(ff_comb, comb_tt_scalefactor_up,   sys='ff_tt_sf_up')
    fill(ff_comb, comb_tt_scalefactor_down, sys='ff_tt_sf_down')
    fill(ff_comb, comb_tt_up_stat,   sys='ff_tt_stat_up')
    fill(ff_comb, comb_tt_down_stat, sys='ff_tt_stat_down')
    fill(ff_comb, comb_tt_up_stat_dr0_njet0,   sys='ff_tt_dr0_njet0_stat_up')
    fill(ff_comb, comb_tt_down_stat_dr0_njet0, sys='ff_tt_dr0_njet0_stat_down')
    fill(ff_comb, comb_tt_up_stat_dr0_njet1,   sys='ff_tt_dr0_njet1_stat_up')
    fill(ff_comb, comb_tt_down_stat_dr0_njet1, sys='ff_tt_dr0_njet1_stat_down')
    fill(ff_comb, comb_tt_up_stat_dr1_njet0,   sys='ff_tt_dr1_njet0_stat_up')
    fill(ff_comb, comb_tt_down_stat_dr1_njet0, sys='ff_tt_dr1_njet0_stat_down')
    fill(ff_comb, comb_tt_up_stat_dr1_njet1,   sys='ff_tt_dr1_njet1_stat_up')
    fill(ff_comb, comb_tt_down_stat_dr1_njet1, sys='ff_tt_dr1_njet1_stat_down')
    fill(ff_comb, comb_tt_up_stat_dr0_njet0_morphed,   sys='ff_tt_dr0_njet0_morphed_stat_up')
    fill(ff_comb, comb_tt_down_stat_dr0_njet0_morphed,   sys='ff_tt_dr0_njet0_morphed_stat_down')
    fill(ff_comb, comb_tt_up_stat_dr0_njet1_morphed,   sys='ff_tt_dr0_njet1_morphed_stat_up')
    fill(ff_comb, comb_tt_down_stat_dr0_njet1_morphed,   sys='ff_tt_dr0_njet1_morphed_stat_down')
    file = ROOT.TFile.Open("{INDIR}/{CHANNEL}/{CATEGORY}/fakeFactors_{ISOLATION}.root".format(INDIR=indir,CHANNEL=channel,CATEGORY=category, ISOLATION=isolation), "recreate")
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
    

from HTTutilities.Jet2TauFakes.Utilities import Leaf, Node, fill, FakeFactor, replace_nodes
import ROOT
import os
import argparse

parser = argparse.ArgumentParser()
parser.add_argument('--channel', dest = 'channel', help='Channel to plot: mt,et', type=str, metavar = 'TAG', required = True)
parser.add_argument('--input', dest = 'indir', help='Input directory - full string', type=str, metavar = 'TAG', required = True)
args = parser.parse_args()

channel=args.channel
indir=args.indir
FFtype=""
#FFtype="_alt"
categories = ['inclusive', 'dummycat']
#categories = ['btag_looseiso', 'nobtag_looseiso']
isolation="tight"

for category in categories:

    print 'Fake factor input file for channel {0} and category {1}'.format(channel,category)

    ff_qcd_os = FakeFactor(vars=['tau_pt', 'tau2_pt', 'tau_decay', 'njets', 'mvis'])
    ff_w =      FakeFactor(vars=['tau_pt', 'tau2_pt', 'tau_decay', 'njets', 'mvis'])
    ff_tt =     FakeFactor(vars=['tau_pt', 'tau2_pt', 'tau_decay', 'njets', 'mvis'])
    # Combined fake factor
    ff_comb   = FakeFactor(vars=['tau_pt', 'tau2_pt', 'tau_decay', 'njets', 'mvis',  'frac_qcd', 'frac_w', 'frac_tt'])
    
    
    home = os.getenv('HOME')
    
    ###########################################################################################################
    ### QCD fake factors
    
    qcd_os = Node(
        name='ff_qcd_os',
        formula='({njet_hist}==0)*{mviscorr_qcd}*{ptcorr_qcd_0jet}*{OSSS_corr_qcd}*{ff_raw_qcd}+({njet_hist}>0)*{mviscorr_qcd}*{ptcorr_qcd_1jet}*{OSSS_corr_qcd}*{ff_raw_qcd}', 
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
                name='ptcorr_qcd_0jet',
                file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/Correction_Data_QCD_PT{FF}_0jet.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                object='QCD_SS_MuMedium_Data_FFSSMuMediumData_PT_correction',
                vars=['tau2_pt']
            ),
            Leaf(
                name='ptcorr_qcd_1jet',
                file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/Correction_Data_QCD_PT{FF}_1jet.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                object='QCD_SS_MuMedium_Data_FFSSMuMediumData_PT_correction',
                vars=['tau2_pt']
            ),
            Leaf(
               name='OSSS_corr_qcd',
               file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/Correction_Data_QCD_OSSS{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
               object='QCD_SS_Data_FFSSMuMediumData_OSSS_correction',
               vars=['mvis']
            ),
            Leaf(
               name='njet_hist',
               file='/portal/ekpbms2/home/jbechtel/fakefactors/auto_v8/2018/tt/CMSSW_8_0_25/src/ViennaTool/dummy.root',
               object='njet_hist',
               vars=['njets']
            ),
        ]
    )
    w = Node(
        name='ff_w',
        formula='({njet_hist_cw}==0)*{mviscorr_qcd_cw}*{ptcorr_qcd_0jet_cw}*{OSSS_corr_qcd_cw}*{ff_raw_qcd_cw}+({njet_hist_cw}>0)*{mviscorr_qcd_cw}*{ptcorr_qcd_1jet_cw}*{OSSS_corr_qcd_cw}*{ff_raw_qcd_cw}', 
        leaves=[
            Leaf(
                name='ff_raw_qcd_cw',
                file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                object='FakeFactors_Data_QCDSS_3D_SS_Iso_Medium_SS_InvertIso_Medium_tau_pt_vs_decayMode',
                vars=['tau_pt','tau_decay','njets']
            ),
            Leaf(
                name='mviscorr_qcd_cw',
                file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/Correction_Data_QCD_MVis{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                object='QCD_SS_MuMedium_Data_FFSSMuMediumData_mvis_correction',
                vars=['mvis']
            ),
            Leaf(
                name='ptcorr_qcd_0jet_cw',
                file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/Correction_Data_QCD_PT{FF}_0jet.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                object='QCD_SS_MuMedium_Data_FFSSMuMediumData_PT_correction',
                vars=['tau2_pt']
            ),
            Leaf(
                name='ptcorr_qcd_1jet_cw',
                file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/Correction_Data_QCD_PT{FF}_1jet.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                object='QCD_SS_MuMedium_Data_FFSSMuMediumData_PT_correction',
                vars=['tau2_pt']
            ),
            Leaf(
               name='OSSS_corr_qcd_cw',
               file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/Correction_Data_QCD_OSSS{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
               object='QCD_SS_Data_FFSSMuMediumData_OSSS_correction',
               vars=['mvis']
            ),
            Leaf(
               name='njet_hist_cw',
               file='/portal/ekpbms2/home/jbechtel/fakefactors/auto_v8/2018/tt/CMSSW_8_0_25/src/ViennaTool/dummy.root',
               object='njet_hist',
               vars=['njets']
            ),
        ]
    )
    tt = Node(
        name='ff_tt',
        formula='({njet_hist_ctt}==0)*{mviscorr_qcd_ctt}*{ptcorr_qcd_0jet_ctt}*{OSSS_corr_qcd_ctt}*{ff_raw_qcd_ctt}+({njet_hist_ctt}>0)*{mviscorr_qcd_ctt}*{ptcorr_qcd_1jet_ctt}*{OSSS_corr_qcd_ctt}*{ff_raw_qcd_ctt}', 
        leaves=[
            Leaf(
                name='ff_raw_qcd_ctt',
                file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                object='FakeFactors_Data_QCDSS_3D_SS_Iso_Medium_SS_InvertIso_Medium_tau_pt_vs_decayMode',
                vars=['tau_pt','tau_decay','njets']
            ),
            Leaf(
                name='mviscorr_qcd_ctt',
                file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/Correction_Data_QCD_MVis{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                object='QCD_SS_MuMedium_Data_FFSSMuMediumData_mvis_correction',
                vars=['mvis']
            ),
            Leaf(
                name='ptcorr_qcd_0jet_ctt',
                file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/Correction_Data_QCD_PT{FF}_0jet.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                object='QCD_SS_MuMedium_Data_FFSSMuMediumData_PT_correction',
                vars=['tau2_pt']
            ),
            Leaf(
                name='ptcorr_qcd_1jet_ctt',
                file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/Correction_Data_QCD_PT{FF}_1jet.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                object='QCD_SS_MuMedium_Data_FFSSMuMediumData_PT_correction',
                vars=['tau2_pt']
            ),
            Leaf(
               name='OSSS_corr_qcd_ctt',
               file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/Correction_Data_QCD_OSSS{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
               object='QCD_SS_Data_FFSSMuMediumData_OSSS_correction',
               vars=['mvis']
            ),
            Leaf(
               name='njet_hist_ctt',
               file='/portal/ekpbms2/home/jbechtel/fakefactors/auto_v8/2018/tt/CMSSW_8_0_25/src/ViennaTool/dummy.root',
               object='njet_hist',
               vars=['njets']
            ),
        ]
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
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/uncertainties_QCD_W{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_QCD_MVis_Iso_SS2OS_up',
                     vars=['mvis','tau2_pt']
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
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/uncertainties_QCD_W{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_QCD_MVis_Iso_SS2OS_down',
                     vars=['mvis']
                 ),
                 qcd_os.find('ff_qcd_os')
             ]
         )
        }
    )
    qcd_os_0jet_up = replace_nodes(
        qcd_os, 
        {'ff_qcd_os':
         Node(
             name='ff_qcd_os_up',
             formula='(1.+{sys_qcd_up})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='sys_qcd_up',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/uncertainties_QCD_W{FF}_0jet.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_QCD_MVis_Iso_SS2OS_up',
                     vars=['mvis','tau2_pt']
                 ),
                 qcd_os.find('ff_qcd_os')
             ]
         )
        }
    )
    qcd_os_0jet_down = replace_nodes(
        qcd_os, 
        {'ff_qcd_os':
         Node(
             name='ff_qcd_os_down',
             formula='max(0.,1.-{sys_qcd_down})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='sys_qcd_down',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/uncertainties_QCD_W{FF}_0jet.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_QCD_MVis_Iso_SS2OS_down',
                     vars=['mvis']
                 ),
                 qcd_os.find('ff_qcd_os')
             ]
         )
        }
    )
    qcd_os_1jet_up = replace_nodes(
        qcd_os, 
        {'ff_qcd_os':
         Node(
             name='ff_qcd_os_up',
             formula='(1.+{sys_qcd_up})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='sys_qcd_up',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/uncertainties_QCD_W{FF}_1jet.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_QCD_MVis_Iso_SS2OS_up',
                     vars=['mvis','tau2_pt']
                 ),
                 qcd_os.find('ff_qcd_os')
             ]
         )
        }
    )
    qcd_os_1jet_down = replace_nodes(
        qcd_os, 
        {'ff_qcd_os':
         Node(
             name='ff_qcd_os_down',
             formula='max(0.,1.-{sys_qcd_down})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='sys_qcd_down',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/uncertainties_QCD_W{FF}_1jet.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_QCD_MVis_Iso_SS2OS_down',
                     vars=['mvis']
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
    ### Combined fake factors
    comb = Node(
        name='ff_comb',
        #formula='({frac_qcd}+{frac_tt}+{frac_w}+{frac_dy})*{ff_qcd_os}',
        #formula='{frac_qcd}*{ff_qcd_os}+{mcfrac}*{frac_tt}*{ff_tt}+{mcfrac}*({frac_w}+{frac_dy})*{ff_w}',
        formula='{frac_qcd}*{ff_qcd_os}+2.0*{frac_tt}*{ff_tt}+2.0*{frac_w}*{ff_w}',
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
            #Leaf(
            #    name='mcfrac',
            #    file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/MCcount.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category),
            #    object='MCcount',
            #    vars=['MCcount'] 
            #)
        ]
    )

    comb_onlyqcd = Node(
        name='ff_onlyqcd',
        formula='{frac_qcd}*{ff_qcd_os}/{frac_qcd}+0.0*{frac_tt}*{ff_tt}+0.0*{frac_w}*{ff_w}',
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
            #Leaf(
            #    name='mcfrac',
            #    file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/MCcount.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category),
            #    object='MCcount',
            #    vars=['MCcount'] 
            #)
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

    comb_w_up = replace_nodes(
        comb,
        {'ff_w':
         Node(
             name='ff_w_up',
             formula='(1.3+0*{sys_qcd_up})*{ff_w}',
             leaves=[
                 Leaf(
                     name='sys_qcd_up',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/uncertainties_QCD_W{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_QCD_MVis_Iso_SS2OS_up',
                     vars=['mvis','tau2_pt']
                 ),
                 w.find('ff_w')
             ]
         )
        }
    )
    comb_w_down = replace_nodes(
        comb,
        {'ff_w':
         Node(
             name='ff_w_down',
             formula='(0.7+0*{sys_qcd_up})*{ff_w}',
             leaves=[
                 Leaf(
                     name='sys_qcd_up',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/uncertainties_QCD_W{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_QCD_MVis_Iso_SS2OS_up',
                     vars=['mvis','tau2_pt']
                 ),
                 w.find('ff_w')
             ]
         )
        }
    )
    comb_w_0jet_up = replace_nodes(
        comb,
        {'ff_w':
         Node(
             name='ff_w_up',
             formula='(1.3+0*{sys_qcd_up})*{ff_w}',
             leaves=[
                 Leaf(
                     name='sys_qcd_up',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/uncertainties_QCD_W{FF}_0jet.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_QCD_MVis_Iso_SS2OS_up',
                     vars=['mvis','tau2_pt']
                 ),
                 w.find('ff_w')
             ]
         )
        }
    )
    comb_w_0jet_down = replace_nodes(
        comb,
        {'ff_w':
         Node(
             name='ff_w_down',
             formula='(0.7+0*{sys_qcd_up})*{ff_w}',
             leaves=[
                 Leaf(
                     name='sys_qcd_up',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/uncertainties_QCD_W{FF}_0jet.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_QCD_MVis_Iso_SS2OS_up',
                     vars=['mvis','tau2_pt']
                 ),
                 w.find('ff_w')
             ]
         )
        }
    )
    comb_w_1jet_up = replace_nodes(
        comb,
        {'ff_w':
         Node(
             name='ff_w_up',
             formula='(1.3+0*{sys_qcd_up})*{ff_w}',
             leaves=[
                 Leaf(
                     name='sys_qcd_up',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/uncertainties_QCD_W{FF}_1jet.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_QCD_MVis_Iso_SS2OS_up',
                     vars=['mvis','tau2_pt']
                 ),
                 w.find('ff_w')
             ]
         )
        }
    )
    comb_w_1jet_down = replace_nodes(
        comb,
        {'ff_w':
         Node(
             name='ff_w_down',
             formula='(0.7+0*{sys_qcd_up})*{ff_w}',
             leaves=[
                 Leaf(
                     name='sys_qcd_up',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/uncertainties_QCD_W{FF}_1jet.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_QCD_MVis_Iso_SS2OS_up',
                     vars=['mvis','tau2_pt']
                 ),
                 w.find('ff_w')
             ]
         )
        }
    )
    comb_w_frac_up = replace_nodes(
        comb,
        {'ff_w':
         Node(
             name='ff_w_frac_up',
             formula='{frac_w_up}*{ff_w}',
             leaves=[
                 Leaf(
                     name='frac_w_up',
                     file='{INDIR}/constant.root'.format(INDIR=indir),
                     object='constant',
                     vars=['frac_w']
                 ),
                 w.find('ff_w')
             ]
         )
        }
    )
    comb_w_frac_down = replace_nodes(
        comb,
        {'ff_w':
         Node(
             name='ff_w_frac_down',
             formula='{frac_w_down}*{ff_w}',
             leaves=[
                 Leaf(
                     name='frac_w_down',
                     file='{INDIR}/constant.root'.format(INDIR=indir),
                     object='constant',
                     vars=['frac_w']
                 ),
                 w.find('ff_w')
             ]
         )
        }
    )
    comb_tt_up = replace_nodes(
        comb,
        {'ff_tt':
         Node(
             name='ff_tt_up',
             formula='(1.3+0*{sys_qcd_up})*{ff_tt}',
             leaves=[
                 Leaf(
                     name='sys_qcd_up',
                     file='{INDIR}/constant.root'.format(INDIR=indir),
                     object='constant',
                     vars=['frac_tt']
                 ),
                 tt.find('ff_tt')
             ]
         )
        }
    )
    comb_tt_down = replace_nodes(
        comb,
        {'ff_tt':
         Node(
             name='ff_tt_down',
             formula='(0.7+0*{sys_qcd_up})*{ff_tt}',
             leaves=[
                 Leaf(
                     name='sys_qcd_up',
                     file='{INDIR}/constant.root'.format(INDIR=indir),
                     object='constant',
                     vars=['frac_tt']
                 ),
                 tt.find('ff_tt')
             ]
         )
        }
    )
    comb_tt_frac_up = replace_nodes(
        comb,
        {'ff_tt':
         Node(
             name='ff_tt_frac_up',
             formula='{frac_tt_up}*{ff_tt}',
             leaves=[
                 Leaf(
                     name='frac_tt_up',
                     file='{INDIR}/constant.root'.format(INDIR=indir),
                     object='constant',
                     vars=['frac_tt']
                 ),
                 tt.find('ff_tt')
             ]
         )
        }
    )
    comb_tt_frac_down = replace_nodes(
        comb,
        {'ff_tt':
         Node(
             name='ff_tt_frac_down',
             formula='{frac_tt_down}*{ff_tt}',
             leaves=[
                 Leaf(
                     name='frac_tt_down',
                     file='{INDIR}/constant.root'.format(INDIR=indir),
                     object='constant',
                     vars=['frac_tt']
                 ),
                 tt.find('ff_tt')
             ]
         )
        }
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
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/uncertainties_QCD_W{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_QCD_MVis_Iso_SS2OS_up',
                     vars=['mvis','tau2_pt']
                 ),
                 qcd_os.find('ff_qcd_os')
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
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/uncertainties_QCD_W{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_QCD_MVis_Iso_SS2OS_down',
                     vars=['mvis','tau2_pt']
                 ),
                 qcd_os.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_qcd_0jet_up = replace_nodes(
        comb,
        {'ff_qcd_os':
         Node(
             name='ff_qcd_os_up',
             formula='(1.+{sys_qcd_up})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='sys_qcd_up',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/uncertainties_QCD_W{FF}_0jet.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_QCD_MVis_Iso_SS2OS_up',
                     vars=['mvis','tau2_pt']
                 ),
                 qcd_os.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_qcd_0jet_down = replace_nodes(
        comb,
        {'ff_qcd_os':
         Node(
             name='ff_qcd_os_down',
             formula='max(0.,1.-{sys_qcd_down})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='sys_qcd_down',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/uncertainties_QCD_W{FF}_0jet.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_QCD_MVis_Iso_SS2OS_down',
                     vars=['mvis','tau2_pt']
                 ),
                 qcd_os.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_qcd_1jet_up = replace_nodes(
        comb,
        {'ff_qcd_os':
         Node(
             name='ff_qcd_os_up',
             formula='(1.+{sys_qcd_up})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='sys_qcd_up',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/uncertainties_QCD_W{FF}_1jet.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_QCD_MVis_Iso_SS2OS_up',
                     vars=['mvis','tau2_pt']
                 ),
                 qcd_os.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_qcd_1jet_down = replace_nodes(
        comb,
        {'ff_qcd_os':
         Node(
             name='ff_qcd_os_down',
             formula='max(0.,1.-{sys_qcd_down})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='sys_qcd_down',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/uncertainties_QCD_W{FF}_1jet.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_QCD_MVis_Iso_SS2OS_down',
                     vars=['mvis','tau2_pt']
                 ),
                 qcd_os.find('ff_qcd_os')
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
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/uncertainties_QCD_W{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_QCD_MVis_Iso_SS2OS_mvis_up',
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
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/uncertainties_QCD_W{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_QCD_MVis_Iso_SS2OS_mvis_down',
                     vars=['mvis']
                 ),
                 comb.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_qcd_mvis_0jet_up = replace_nodes(
        comb,
        {'ff_qcd_os':
         Node(
             name='ff_qcd_mvis_up',
             formula='(1.+{sys_qcd_mvis_up})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='sys_qcd_mvis_up',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/uncertainties_QCD_W{FF}_0jet.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_QCD_MVis_Iso_SS2OS_mvis_up',
                     vars=['mvis']
                 ),
                 comb.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_qcd_mvis_0jet_down = replace_nodes(
        comb,
        {'ff_qcd_os':
         Node(
             name='ff_qcd_mvis_down',
             formula='(1.+{sys_qcd_mvis_down})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='sys_qcd_mvis_down',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/uncertainties_QCD_W{FF}_0jet.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_QCD_MVis_Iso_SS2OS_mvis_down',
                     vars=['mvis']
                 ),
                 comb.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_qcd_mvis_1jet_up = replace_nodes(
        comb,
        {'ff_qcd_os':
         Node(
             name='ff_qcd_mvis_up',
             formula='(1.+{sys_qcd_mvis_up})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='sys_qcd_mvis_up',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/uncertainties_QCD_W{FF}_1jet.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_QCD_MVis_Iso_SS2OS_mvis_up',
                     vars=['mvis']
                 ),
                 comb.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_qcd_mvis_1jet_down = replace_nodes(
        comb,
        {'ff_qcd_os':
         Node(
             name='ff_qcd_mvis_down',
             formula='(1.+{sys_qcd_mvis_down})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='sys_qcd_mvis_down',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/uncertainties_QCD_W{FF}_1jet.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_QCD_MVis_Iso_SS2OS_mvis_down',
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
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/uncertainties_QCD_W{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_QCD_MVis_Iso_SS2OS_mvis_osss_up',
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
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/uncertainties_QCD_W{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_QCD_MVis_Iso_SS2OS_mvis_osss_down',
                     vars=['mvis']
                 ),
                 comb.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_qcd_mvis_osss_0jet_up = replace_nodes(
        comb,
        {'ff_qcd_os':
         Node(
             name='ff_qcd_mvis_osss_up',
             formula='(1.+{sys_qcd_mvis_osss_up})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='sys_qcd_mvis_osss_up',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/uncertainties_QCD_W{FF}_0jet.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_QCD_MVis_Iso_SS2OS_mvis_osss_up',
                     vars=['mvis']
                 ),
                 comb.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_qcd_mvis_osss_0jet_down = replace_nodes(
        comb,
        {'ff_qcd_os':
         Node(
             name='ff_qcd_mvis_osss_down',
             formula='(1.+{sys_qcd_mvis_osss_down})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='sys_qcd_mvis_osss_down',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/uncertainties_QCD_W{FF}_0jet.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_QCD_MVis_Iso_SS2OS_mvis_osss_down',
                     vars=['mvis']
                 ),
                 comb.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_qcd_mvis_osss_1jet_up = replace_nodes(
        comb,
        {'ff_qcd_os':
         Node(
             name='ff_qcd_mvis_osss_up',
             formula='(1.+{sys_qcd_mvis_osss_up})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='sys_qcd_mvis_osss_up',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/uncertainties_QCD_W{FF}_1jet.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_QCD_MVis_Iso_SS2OS_mvis_osss_up',
                     vars=['mvis']
                 ),
                 comb.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_qcd_mvis_osss_1jet_down = replace_nodes(
        comb,
        {'ff_qcd_os':
         Node(
             name='ff_qcd_mvis_osss_down',
             formula='(1.+{sys_qcd_mvis_osss_down})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='sys_qcd_mvis_osss_down',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/uncertainties_QCD_W{FF}_1jet.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_QCD_MVis_Iso_SS2OS_mvis_osss_down',
                     vars=['mvis']
                 ),
                 comb.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_qcd_tau2_pt_up = replace_nodes(
        comb,
        {'ff_qcd_os':
         Node(
             name='ff_qcd_tau2_pt_up',
             formula='(1.+{sys_qcd_tau2_pt_up})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='sys_qcd_tau2_pt_up',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/uncertainties_QCD_W{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_QCD_MVis_Iso_SS2OS_pt_up',
                     vars=['tau2_pt']
                 ),
                 comb.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_qcd_tau2_pt_down = replace_nodes(
        comb,
        {'ff_qcd_os':
         Node(
             name='ff_qcd_tau2_pt_down',
             formula='(1.+{sys_qcd_tau2_pt_down})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='sys_qcd_tau2_pt_down',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/uncertainties_QCD_W{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_QCD_MVis_Iso_SS2OS_pt_down',
                     vars=['tau2_pt']
                 ),
                 comb.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_qcd_tau2_pt_0jet_up = replace_nodes(
        comb,
        {'ff_qcd_os':
         Node(
             name='ff_qcd_tau2_pt_up',
             formula='(1.+{sys_qcd_tau2_pt_up_0jet})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='sys_qcd_tau2_pt_up_0jet',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/uncertainties_QCD_W{FF}_0jet.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_QCD_MVis_Iso_SS2OS_pt_up',
                     vars=['tau2_pt']
                 ),
                 comb.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_qcd_tau2_pt_0jet_down = replace_nodes(
        comb,
        {'ff_qcd_os':
         Node(
             name='ff_qcd_tau2_pt_down',
             formula='(1.+{sys_qcd_tau2_pt_down_0jet})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='sys_qcd_tau2_pt_down_0jet',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/uncertainties_QCD_W{FF}_0jet.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_QCD_MVis_Iso_SS2OS_pt_down',
                     vars=['tau2_pt']
                 ),
                 comb.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_qcd_tau2_pt_1jet_up = replace_nodes(
        comb,
        {'ff_qcd_os':
         Node(
             name='ff_qcd_tau2_pt_up',
             formula='(1.+{sys_qcd_tau2_pt_up_1jet})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='sys_qcd_tau2_pt_up_1jet',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/uncertainties_QCD_W{FF}_1jet.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_QCD_MVis_Iso_SS2OS_pt_up',
                     vars=['tau2_pt']
                 ),
                 comb.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_qcd_tau2_pt_1jet_down = replace_nodes(
        comb,
        {'ff_qcd_os':
         Node(
             name='ff_qcd_tau2_pt_down',
             formula='(1.+{sys_qcd_tau2_pt_down_1jet})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='sys_qcd_tau2_pt_down_1jet',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/uncertainties_QCD_W{FF}_1jet.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='uncertainties_QCD_MVis_Iso_SS2OS_pt_down',
                     vars=['tau2_pt']
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
    comb_corr_qcd_mvis_0jet_up = replace_nodes(
        comb,
        {'ff_qcd_os':
         Node(
             name='ff_corr_qcd_mvis_up',
             formula='{ff_qcd_os}*({mviscorr_qcd_temp})',
             leaves=[
                    Leaf(
                        name='mviscorr_qcd_temp',
                        file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/Correction_Data_QCD_MVis{FF}_0jet.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                        object='QCD_SS_MuMedium_Data_FFSSMuMediumData_mvis_correction',
                        vars=['mvis']
                    ),
                 comb.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_corr_qcd_mvis_0jet_down = replace_nodes(
        comb,
        {'ff_qcd_os':
         Node(
             name='ff_corr_qcd_mvis_down',
             formula='{ff_qcd_os}/({mviscorr_qcd_temp})',
             leaves=[
                    Leaf(
                        name='mviscorr_qcd_temp',
                        file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/Correction_Data_QCD_MVis{FF}_0jet.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                        object='QCD_SS_MuMedium_Data_FFSSMuMediumData_mvis_correction',
                        vars=['mvis']
                    ),
                 comb.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_corr_qcd_mvis_1jet_up = replace_nodes(
        comb,
        {'ff_qcd_os':
         Node(
             name='ff_corr_qcd_mvis_up',
             formula='{ff_qcd_os}*({mviscorr_qcd_temp})',
             leaves=[
                    Leaf(
                        name='mviscorr_qcd_temp',
                        file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/Correction_Data_QCD_MVis{FF}_1jet.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                        object='QCD_SS_MuMedium_Data_FFSSMuMediumData_mvis_correction',
                        vars=['mvis']
                    ),
                 comb.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_corr_qcd_mvis_1jet_down = replace_nodes(
        comb,
        {'ff_qcd_os':
         Node(
             name='ff_corr_qcd_mvis_down',
             formula='{ff_qcd_os}/({mviscorr_qcd_temp})',
             leaves=[
                    Leaf(
                        name='mviscorr_qcd_temp',
                        file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/Correction_Data_QCD_MVis{FF}_1jet.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                        object='QCD_SS_MuMedium_Data_FFSSMuMediumData_mvis_correction',
                        vars=['mvis']
                    ),
                 comb.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_corr_qcd_tau2_pt_up = replace_nodes(
        comb,
        {'ff_qcd_os':
         Node(
             name='ff_corr_qcd_tau2_pt_up',
             formula='{ff_qcd_os}*({ptcorr_qcd_temp})',
             leaves=[
                    Leaf(
                        name='ptcorr_qcd_temp',
                        file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/Correction_Data_QCD_PT{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                        object='QCD_SS_MuMedium_Data_FFSSMuMediumData_PT_correction',
                        vars=['tau2_pt']
                    ),
                 comb.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_corr_qcd_tau2_pt_down = replace_nodes(
        comb,
        {'ff_qcd_os':
         Node(
             name='ff_corr_qcd_tau2_pt_down',
             formula='{ff_qcd_os}/({ptcorr_qcd_temp})',
             leaves=[
                    Leaf(
                        name='ptcorr_qcd_temp',
                        file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/Correction_Data_QCD_PT{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                        object='QCD_SS_MuMedium_Data_FFSSMuMediumData_PT_correction',
                        vars=['tau2_pt']
                    ),
                 comb.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_corr_qcd_tau2_pt_0jet_up = replace_nodes(
        comb,
        {'ff_qcd_os':
         Node(
             name='ff_corr_qcd_tau2_pt_up',
             formula='{ff_qcd_os}*({ptcorr_qcd_temp_0jet})',
             leaves=[
                    Leaf(
                        name='ptcorr_qcd_temp_0jet',
                        file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/Correction_Data_QCD_PT{FF}_0jet.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                        object='QCD_SS_MuMedium_Data_FFSSMuMediumData_PT_correction',
                        vars=['tau2_pt']
                    ),
                 comb.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_corr_qcd_tau2_pt_0jet_down = replace_nodes(
        comb,
        {'ff_qcd_os':
         Node(
             name='ff_corr_qcd_tau2_pt_down',
             formula='{ff_qcd_os}/({ptcorr_qcd_temp_0jet})',
             leaves=[
                    Leaf(
                        name='ptcorr_qcd_temp_0jet',
                        file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/Correction_Data_QCD_PT{FF}_0jet.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                        object='QCD_SS_MuMedium_Data_FFSSMuMediumData_PT_correction',
                        vars=['tau2_pt']
                    ),
                 comb.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_corr_qcd_tau2_pt_1jet_up = replace_nodes(
        comb,
        {'ff_qcd_os':
         Node(
             name='ff_corr_qcd_tau2_pt_up',
             formula='{ff_qcd_os}*({ptcorr_qcd_temp_1jet})',
             leaves=[
                    Leaf(
                        name='ptcorr_qcd_temp_1jet',
                        file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/Correction_Data_QCD_PT{FF}_1jet.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                        object='QCD_SS_MuMedium_Data_FFSSMuMediumData_PT_correction',
                        vars=['tau2_pt']
                    ),
                 comb.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_corr_qcd_tau2_pt_1jet_down = replace_nodes(
        comb,
        {'ff_qcd_os':
         Node(
             name='ff_corr_qcd_tau2_pt_down',
             formula='{ff_qcd_os}/({ptcorr_qcd_temp_1jet})',
             leaves=[
                    Leaf(
                        name='ptcorr_qcd_temp_1jet',
                        file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/Correction_Data_QCD_PT{FF}_1jet.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                        object='QCD_SS_MuMedium_Data_FFSSMuMediumData_PT_correction',
                        vars=['tau2_pt']
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
             formula='{ff_qcd_os}*({OSSS_corr_qcd_cw_temp})',
             leaves=[
                    Leaf(
                        name='OSSS_corr_qcd_cw_temp',
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
             formula='{ff_qcd_os}/({OSSS_corr_qcd_cw_temp})',
             leaves=[
                    Leaf(
                        name='OSSS_corr_qcd_cw_temp',
                        file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/Correction_Data_QCD_OSSS{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                        object='QCD_SS_Data_FFSSMuMediumData_OSSS_correction',
                        vars=['mvis']
                    ),
                 comb.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_corr_qcd_mvis_osss_0jet_up = replace_nodes(
        comb,
        {'ff_qcd_os':
         Node(
             name='ff_corr_qcd_mvis_osss_up',
             formula='{ff_qcd_os}*({OSSS_corr_qcd_cw_temp})',
             leaves=[
                    Leaf(
                        name='OSSS_corr_qcd_cw_temp',
                        file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/Correction_Data_QCD_OSSS{FF}_0jet.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                        object='QCD_SS_Data_FFSSMuMediumData_OSSS_correction',
                        vars=['mvis']
                    ),
                 comb.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_corr_qcd_mvis_osss_0jet_down = replace_nodes(
        comb,
        {'ff_qcd_os':
         Node(
             name='ff_corr_qcd_mvis_osss_down',
             formula='{ff_qcd_os}/({OSSS_corr_qcd_cw_temp})',
             leaves=[
                    Leaf(
                        name='OSSS_corr_qcd_cw_temp',
                        file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/Correction_Data_QCD_OSSS{FF}_0jet.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                        object='QCD_SS_Data_FFSSMuMediumData_OSSS_correction',
                        vars=['mvis']
                    ),
                 comb.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_corr_qcd_mvis_osss_1jet_up = replace_nodes(
        comb,
        {'ff_qcd_os':
         Node(
             name='ff_corr_qcd_mvis_osss_up',
             formula='{ff_qcd_os}*({OSSS_corr_qcd_cw_temp})',
             leaves=[
                    Leaf(
                        name='OSSS_corr_qcd_cw_temp',
                        file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/Correction_Data_QCD_OSSS{FF}_1jet.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                        object='QCD_SS_Data_FFSSMuMediumData_OSSS_correction',
                        vars=['mvis']
                    ),
                 comb.find('ff_qcd_os')
             ]
         )
        }
    )
    comb_corr_qcd_mvis_osss_1jet_down = replace_nodes(
        comb,
        {'ff_qcd_os':
         Node(
             name='ff_corr_qcd_mvis_osss_down',
             formula='{ff_qcd_os}/({OSSS_corr_qcd_cw_temp})',
             leaves=[
                    Leaf(
                        name='OSSS_corr_qcd_cw_temp',
                        file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/Correction_Data_QCD_OSSS{FF}_1jet.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                        object='QCD_SS_Data_FFSSMuMediumData_OSSS_correction',
                        vars=['mvis']
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
             formula='(1.+sqrt(({sys_qcd_mvis_mcup}**2)+({sys_qcd_tau2_pt_mcup}**2)+({ff_raw_qcd_mcup}**2)))*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='sys_qcd_mvis_mcup',
                     file='{INDIR}/{CHANNEL}/FF_corr_QCD_MCsum_noGen_nonclosure.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category),
                     object='nonclosure_mcup_QCD',
                     vars=['mvis']
                 ),
                 Leaf(
                     name='sys_qcd_tau2_pt_mcup',
                     file='{INDIR}/{CHANNEL}/FF_corr_QCD_MCsum_noGen_nonclosure_lepPt.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category),
                     object='nonclosure_mcup_QCD',
                     vars=['tau2_pt']
                 ),
                Leaf(
                    name='ff_raw_qcd_mcup',
                    file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                    object='FakeFactors_Data_QCDSS_3D_SS_Iso_Medium_SS_InvertIso_Medium_tau_pt_vs_decayMode_error_mc_high',
                    vars=['tau_pt','tau_decay','njets']
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
             formula='(1.-sqrt(({sys_qcd_mvis_mcdown}**2)+({sys_qcd_tau2_pt_mcdown}**2)+({ff_raw_qcd_mcdown}**2)))*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='sys_qcd_mvis_mcdown',
                     file='{INDIR}/{CHANNEL}/FF_corr_QCD_MCsum_noGen_nonclosure.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category),
                     object='nonclosure_mcdown_QCD',
                     vars=['mvis']
                 ),
                 Leaf(
                     name='sys_qcd_tau2_pt_mcdown',
                     file='{INDIR}/{CHANNEL}/FF_corr_QCD_MCsum_noGen_nonclosure_lepPt.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category),
                     object='nonclosure_mcdown_QCD',
                     vars=['tau2_pt']
                 ),
                Leaf(
                    name='ff_raw_qcd_mcdown',
                    file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                    object='FakeFactors_Data_QCDSS_3D_SS_Iso_Medium_SS_InvertIso_Medium_tau_pt_vs_decayMode_error_mc_low',
                    vars=['tau_pt','tau_decay','njets']
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
                     vars=['tau_pt','tau_decay','njets']
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
                     vars=['tau_pt','tau_decay','njets']
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
                     vars=['tau_pt','tau_decay','njets']
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
                     vars=['tau_pt','tau_decay','njets']
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
                     vars=['tau_pt','tau_decay','njets']
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
                     object='FakeFactors_Data_QCDSS_3D_SS_Iso_Medium_SS_InvertIso_Medium_tau_pt_vs_decayMode_error_dr0_njet1_low',
                     vars=['tau_pt','tau_decay','njets']
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
                     vars=['tau_pt','tau_decay','njets']
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
                     vars=['tau_pt','tau_decay','njets']
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
                     vars=['tau_pt','tau_decay','njets']
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
                     vars=['tau_pt','tau_decay','njets']
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
             name='ff_qcd_up_stat_dr0_njet0_morphed',
             formula='(1.+{stat_qcd_up_dr0_njet0_morphed})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='stat_qcd_up_dr0_njet0_morphed',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_QCDSS_3D_SS_Iso_Medium_SS_InvertIso_Medium_tau_pt_vs_decayMode_error_dr0_njet0_morphed_high',
                     vars=['tau_pt','tau_decay','njets']
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
             name='ff_qcd_down_stat_dr0_njet0_morphed',
             formula='max(0.,1.+{stat_qcd_down_dr0_njet0_morphed})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='stat_qcd_down_dr0_njet0_morphed',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_QCDSS_3D_SS_Iso_Medium_SS_InvertIso_Medium_tau_pt_vs_decayMode_error_dr0_njet0_morphed_low',
                     vars=['tau_pt','tau_decay','njets']
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
             name='ff_qcd_up_stat_dr0_njet1_morphed',
             formula='(1.+{stat_qcd_up_dr0_njet1_morphed})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='stat_qcd_up_dr0_njet1_morphed',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_QCDSS_3D_SS_Iso_Medium_SS_InvertIso_Medium_tau_pt_vs_decayMode_error_dr0_njet1_morphed_high',
                     vars=['tau_pt','tau_decay','njets']
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
             name='ff_qcd_down_stat_dr0_njet1_morphed',
             formula='max(0.,1.+{stat_qcd_down_dr0_njet1_morphed})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='stat_qcd_down_dr0_njet1_morphed',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_QCDSS_3D_SS_Iso_Medium_SS_InvertIso_Medium_tau_pt_vs_decayMode_error_dr0_njet1_morphed_low',
                     vars=['tau_pt','tau_decay','njets']
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
             name='ff_qcd_up_stat_dr0_njet2_morphed',
             formula='(1.+{stat_qcd_up_dr0_njet2_morphed})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='stat_qcd_up_dr0_njet2_morphed',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_QCDSS_3D_SS_Iso_Medium_SS_InvertIso_Medium_tau_pt_vs_decayMode_error_dr0_njet2_morphed_high',
                     vars=['tau_pt','tau_decay','njets']
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
             name='ff_qcd_down_stat_dr0_njet2_morphed',
             formula='max(0.,1.+{stat_qcd_down_dr0_njet2_morphed})*{ff_qcd_os}',
             leaves=[
                 Leaf(
                     name='stat_qcd_down_dr0_njet2_morphed',
                     file='{INDIR}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D{FF}.root'.format(INDIR=indir,CHANNEL=channel,CATEGORY=category,FF=FFtype),
                     object='FakeFactors_Data_QCDSS_3D_SS_Iso_Medium_SS_InvertIso_Medium_tau_pt_vs_decayMode_error_dr0_njet2_morphed_low',
                     vars=['tau_pt','tau_decay','njets']
                 ),
                 comb.find('ff_qcd_os')
             ]
         )
        }
    )
    fill(ff_qcd_os, qcd_os)
    fill(ff_qcd_os, qcd_os_up,   sys='ff_qcd_syst_up')
    fill(ff_qcd_os, qcd_os_down, sys='ff_qcd_syst_down')
    fill(ff_qcd_os, qcd_os_up_stat,   sys='ff_qcd_stat_up')
    fill(ff_qcd_os, qcd_os_down_stat, sys='ff_qcd_stat_down')
    fill(ff_comb  , comb)
    fill(ff_comb  , comb_onlyqcd, sys='ff_onlyqcd')
    fill(ff_comb  , comb_fracw, sys='ff_fracw')
    fill(ff_comb  , comb_fracqcd, sys='ff_fracqcd')
    fill(ff_comb  , comb_fractt, sys='ff_fractt')
    fill(ff_comb, comb_w_up,   sys='ff_w_syst_up')
    fill(ff_comb, comb_w_down,   sys='ff_w_syst_down')
    fill(ff_comb, comb_w_frac_up,   sys='ff_w_frac_syst_up')
    fill(ff_comb, comb_w_frac_down,   sys='ff_w_frac_syst_down')
    fill(ff_comb, comb_tt_up,   sys='ff_tt_syst_up')
    fill(ff_comb, comb_tt_down,   sys='ff_tt_syst_down')
    fill(ff_comb, comb_tt_frac_up,   sys='ff_tt_frac_syst_up')
    fill(ff_comb, comb_tt_frac_down,   sys='ff_tt_frac_syst_down')
    fill(ff_comb, comb_qcd_up,   sys='ff_qcd_syst_up')        
    fill(ff_comb, comb_qcd_down,   sys='ff_qcd_syst_down')
    fill(ff_comb, comb_qcd_mvis_up,   sys='ff_qcd_mvis_up')        
    fill(ff_comb, comb_qcd_mvis_down,   sys='ff_qcd_mvis_down')
    fill(ff_comb, comb_qcd_mvis_osss_up,   sys='ff_qcd_mvis_osss_up')        
    fill(ff_comb, comb_qcd_mvis_osss_down,   sys='ff_qcd_mvis_osss_down')
    fill(ff_comb, comb_qcd_tau2_pt_up,   sys='ff_qcd_tau2_pt_up')        
    fill(ff_comb, comb_qcd_tau2_pt_down,   sys='ff_qcd_tau2_pt_down')        
    fill(ff_comb, comb_corr_qcd_mvis_up,   sys='ff_corr_qcd_mvis_up')        
    fill(ff_comb, comb_corr_qcd_mvis_down,   sys='ff_corr_qcd_mvis_down')
    fill(ff_comb, comb_corr_qcd_mvis_osss_up,   sys='ff_corr_qcd_mvis_osss_up')        
    fill(ff_comb, comb_corr_qcd_mvis_osss_down,   sys='ff_corr_qcd_mvis_osss_down')
    fill(ff_comb, comb_corr_qcd_tau2_pt_up,   sys='ff_corr_qcd_tau2_pt_up')        
    fill(ff_comb, comb_corr_qcd_tau2_pt_down,   sys='ff_corr_qcd_tau2_pt_down')   
    # fill(ff_comb, comb_qcd_0jet_up,   sys='ff_qcd_syst_0jet_up')        
    # fill(ff_comb, comb_qcd_0jet_down,   sys='ff_qcd_syst_0jet_down')
    # fill(ff_comb, comb_qcd_mvis_0jet_up,   sys='ff_qcd_mvis_0jet_up')        
    # fill(ff_comb, comb_qcd_mvis_0jet_down,   sys='ff_qcd_mvis_0jet_down')
    # fill(ff_comb, comb_qcd_mvis_osss_0jet_up,   sys='ff_qcd_mvis_osss_0jet_up')        
    # fill(ff_comb, comb_qcd_mvis_osss_0jet_down,   sys='ff_qcd_mvis_osss_0jet_down')
    fill(ff_comb, comb_qcd_tau2_pt_0jet_up,   sys='ff_qcd_tau2_pt_0jet_up')        
    fill(ff_comb, comb_qcd_tau2_pt_0jet_down,   sys='ff_qcd_tau2_pt_0jet_down')        
    # fill(ff_comb, comb_corr_qcd_mvis_0jet_up,   sys='ff_corr_qcd_mvis_0jet_up')        
    # fill(ff_comb, comb_corr_qcd_mvis_0jet_down,   sys='ff_corr_qcd_mvis_0jet_down')
    # fill(ff_comb, comb_corr_qcd_mvis_osss_0jet_up,   sys='ff_corr_qcd_mvis_osss_0jet_up')        
    # fill(ff_comb, comb_corr_qcd_mvis_osss_0jet_down,   sys='ff_corr_qcd_mvis_osss_0jet_down')
    fill(ff_comb, comb_corr_qcd_tau2_pt_0jet_up,   sys='ff_corr_qcd_tau2_pt_0jet_up')        
    fill(ff_comb, comb_corr_qcd_tau2_pt_0jet_down,   sys='ff_corr_qcd_tau2_pt_0jet_down')   
    # fill(ff_comb, comb_qcd_1jet_up,   sys='ff_qcd_syst_1jet_up')        
    # fill(ff_comb, comb_qcd_1jet_down,   sys='ff_qcd_syst_1jet_down')
    # fill(ff_comb, comb_qcd_mvis_1jet_up,   sys='ff_qcd_mvis_1jet_up')        
    # fill(ff_comb, comb_qcd_mvis_1jet_down,   sys='ff_qcd_mvis_1jet_down')
    # fill(ff_comb, comb_qcd_mvis_osss_1jet_up,   sys='ff_qcd_mvis_osss_1jet_up')        
    # fill(ff_comb, comb_qcd_mvis_osss_1jet_down,   sys='ff_qcd_mvis_osss_1jet_down')
    fill(ff_comb, comb_qcd_tau2_pt_1jet_up,   sys='ff_qcd_tau2_pt_1jet_up')        
    fill(ff_comb, comb_qcd_tau2_pt_1jet_down,   sys='ff_qcd_tau2_pt_1jet_down')        
    # fill(ff_comb, comb_corr_qcd_mvis_1jet_up,   sys='ff_corr_qcd_mvis_1jet_up')        
    # fill(ff_comb, comb_corr_qcd_mvis_1jet_down,   sys='ff_corr_qcd_mvis_1jet_down')
    # fill(ff_comb, comb_corr_qcd_mvis_osss_1jet_up,   sys='ff_corr_qcd_mvis_osss_1jet_up')        
    # fill(ff_comb, comb_corr_qcd_mvis_osss_1jet_down,   sys='ff_corr_qcd_mvis_osss_1jet_down')
    fill(ff_comb, comb_corr_qcd_tau2_pt_1jet_up,   sys='ff_corr_qcd_tau2_pt_1jet_up')        
    fill(ff_comb, comb_corr_qcd_tau2_pt_1jet_down,   sys='ff_corr_qcd_tau2_pt_1jet_down')      
    fill(ff_comb, comb_qcd_mc_up,   sys='ff_qcd_mc_up')        
    fill(ff_comb, comb_qcd_mc_down,   sys='ff_qcd_mc_down')        
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
    
    file = ROOT.TFile.Open("{INDIR}/{CHANNEL}/{CATEGORY}/fakeFactors_{ISOLATION}.root".format(INDIR=indir,CHANNEL=channel,CATEGORY=category, ISOLATION=isolation), "recreate")
    # Write meta-data
    # Write fake factors
    file.WriteObject(ff_qcd_os.fakefactor  , "ff_qcd_os")
    file.WriteObject(ff_comb.fakefactor    , "ff_comb")
    #
    file.Close()
    

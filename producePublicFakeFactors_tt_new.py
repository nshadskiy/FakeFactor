from HTTutilities.Jet2TauFakes.Utilities import Leaf, Node, fill, FakeFactor, replace_nodes
import ROOT
import os

#Meta-data
version='20170415_tight'
tag='v0.2.1'
channels=["tt"]
categories = ['inclusive', 'btag', 'nobtag']

for channel in channels:
    for category in categories:

        print 'Fake factor input file for channel {0} and category {1}'.format(channel,category)
        
        # Individual fake factors
        ff_qcd_os = FakeFactor(vars=['tau_pt', 'tau2_pt', 'tau_decay', 'njets', 'mvis',  'mu_iso'])
        ff_w =      FakeFactor(vars=['tau_pt', 'tau2_pt', 'tau_decay', 'njets', 'mvis',  'mu_iso'])
        ff_tt =     FakeFactor(vars=['tau_pt', 'tau2_pt', 'tau_decay', 'njets', 'mvis',  'mu_iso'])
        # Combined fake factor
        ff_comb   = FakeFactor(vars=['tau_pt', 'tau2_pt', 'tau_decay', 'njets', 'mvis',  'mu_iso'])
        
        
        home = os.getenv('HOME')
        
        ###########################################################################################################
        ### QCD fake factors
        
        qcd_os = Node(
            name='ff_qcd_os',
            formula='{mviscorr_qcd}*{ptcorr_qcd}*{OSSS_corr_qcd}*{ff_raw_qcd}', 
            leaves=[
                Leaf(
                    name='ff_raw_qcd',
                    file='{HOME}/public/Htautau/FakeRate2016/{VERSION}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D.root'.format(HOME=home,VERSION=version,CHANNEL=channel,CATEGORY=category),
                    object='FakeFactors_Data_QCDSS_3D_SS_Iso_Medium_SS_InvertIso_Medium_tau_pt_vs_decayMode',
                    vars=['tau_pt','tau_decay','njets']
                ),
                Leaf(
                    name='mviscorr_qcd',
                    file='{HOME}/public/Htautau/FakeRate2016/{VERSION}/{CHANNEL}/{CATEGORY}/pieces/Correction_Data_QCD_MVis.root'.format(HOME=home,VERSION=version,CHANNEL=channel,CATEGORY=category),
                    object='QCD_SS_MuMedium_Data_FFSSMuMediumData_mvis_correction',
                    vars=['mvis']
                ),
                Leaf(
                    name='ptcorr_qcd',
                    file='{HOME}/public/Htautau/FakeRate2016/{VERSION}/{CHANNEL}/{CATEGORY}/pieces/Correction_Data_QCD_PT.root'.format(HOME=home,VERSION=version,CHANNEL=channel,CATEGORY=category),
                    object='QCD_SS_MuMedium_Data_FFSSMuMediumData_PT_correction',
                    vars=['tau2_pt']
                ),
                Leaf(
                    name='OSSS_corr_qcd',
                    file='{HOME}/public/Htautau/FakeRate2016/{VERSION}/{CHANNEL}/{CATEGORY}/pieces/Correction_Data_QCD_OSSS.root'.format(HOME=home,VERSION=version,CHANNEL=channel,CATEGORY=category),
                    object='QCD_SS_Data_FFSSMuMediumData_OSSS_correction',
                    vars=['mvis']
                )
            ]
        )
        w = Node(
            name='ff_w',
            formula='{mviscorr_qcd_cw}*{ptcorr_qcd_cw}*{OSSS_corr_qcd_cw}*{ff_raw_qcd_cw}', 
            leaves=[
                Leaf(
                    name='ff_raw_qcd_cw',
                    file='{HOME}/public/Htautau/FakeRate2016/{VERSION}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D.root'.format(HOME=home,VERSION=version,CHANNEL=channel,CATEGORY=category),
                    object='FakeFactors_Data_QCDSS_3D_SS_Iso_Medium_SS_InvertIso_Medium_tau_pt_vs_decayMode',
                    vars=['tau_pt','tau_decay','njets']
                ),
                Leaf(
                    name='mviscorr_qcd_cw',
                    file='{HOME}/public/Htautau/FakeRate2016/{VERSION}/{CHANNEL}/{CATEGORY}/pieces/Correction_Data_QCD_MVis.root'.format(HOME=home,VERSION=version,CHANNEL=channel,CATEGORY=category),
                    object='QCD_SS_MuMedium_Data_FFSSMuMediumData_mvis_correction',
                    vars=['mvis']
                ),
                Leaf(
                    name='ptcorr_qcd_cw',
                    file='{HOME}/public/Htautau/FakeRate2016/{VERSION}/{CHANNEL}/{CATEGORY}/pieces/Correction_Data_QCD_PT.root'.format(HOME=home,VERSION=version,CHANNEL=channel,CATEGORY=category),
                    object='QCD_SS_MuMedium_Data_FFSSMuMediumData_PT_correction',
                    vars=['tau2_pt']
                ),
                Leaf(
                    name='OSSS_corr_qcd_cw',
                    file='{HOME}/public/Htautau/FakeRate2016/{VERSION}/{CHANNEL}/{CATEGORY}/pieces/Correction_Data_QCD_OSSS.root'.format(HOME=home,VERSION=version,CHANNEL=channel,CATEGORY=category),
                    object='QCD_SS_Data_FFSSMuMediumData_OSSS_correction',
                    vars=['mvis']
                )
            ]
        )
        tt = Node(
            name='ff_tt',
            formula='{mviscorr_qcd_ctt}*{ptcorr_qcd_ctt}*{OSSS_corr_qcd_ctt}*{ff_raw_qcd_ctt}', 
            leaves=[
                Leaf(
                    name='ff_raw_qcd_ctt',
                    file='{HOME}/public/Htautau/FakeRate2016/{VERSION}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D.root'.format(HOME=home,VERSION=version,CHANNEL=channel,CATEGORY=category),
                    object='FakeFactors_Data_QCDSS_3D_SS_Iso_Medium_SS_InvertIso_Medium_tau_pt_vs_decayMode',
                    vars=['tau_pt','tau_decay','njets']
                ),
                Leaf(
                    name='mviscorr_qcd_ctt',
                    file='{HOME}/public/Htautau/FakeRate2016/{VERSION}/{CHANNEL}/{CATEGORY}/pieces/Correction_Data_QCD_MVis.root'.format(HOME=home,VERSION=version,CHANNEL=channel,CATEGORY=category),
                    object='QCD_SS_MuMedium_Data_FFSSMuMediumData_mvis_correction',
                    vars=['mvis']
                ),
                Leaf(
                    name='ptcorr_qcd_ctt',
                    file='{HOME}/public/Htautau/FakeRate2016/{VERSION}/{CHANNEL}/{CATEGORY}/pieces/Correction_Data_QCD_PT.root'.format(HOME=home,VERSION=version,CHANNEL=channel,CATEGORY=category),
                    object='QCD_SS_MuMedium_Data_FFSSMuMediumData_PT_correction',
                    vars=['tau2_pt']
                ),
                Leaf(
                    name='OSSS_corr_qcd_ctt',
                    file='{HOME}/public/Htautau/FakeRate2016/{VERSION}/{CHANNEL}/{CATEGORY}/pieces/Correction_Data_QCD_OSSS.root'.format(HOME=home,VERSION=version,CHANNEL=channel,CATEGORY=category),
                    object='QCD_SS_Data_FFSSMuMediumData_OSSS_correction',
                    vars=['mvis']
                )
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
                         file='{HOME}/public/Htautau/FakeRate2016/{VERSION}/{CHANNEL}/{CATEGORY}/pieces/uncertainties_QCD_W.root'.format(HOME=home,VERSION=version,CHANNEL=channel,CATEGORY=category),
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
                         file='{HOME}/public/Htautau/FakeRate2016/{VERSION}/{CHANNEL}/{CATEGORY}/pieces/uncertainties_QCD_W.root'.format(HOME=home,VERSION=version,CHANNEL=channel,CATEGORY=category),
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
                         file='{HOME}/public/Htautau/FakeRate2016/{VERSION}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D.root'.format(HOME=home,VERSION=version,CHANNEL=channel,CATEGORY=category),
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
                         file='{HOME}/public/Htautau/FakeRate2016/{VERSION}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D.root'.format(HOME=home,VERSION=version,CHANNEL=channel,CATEGORY=category),
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
            formula='{frac_qcd}*{ff_qcd_os}+2*{frac_tt}*{ff_tt}+2*({frac_w}+{frac_dy})*{ff_w}',
            leaves=[
                # Individual fake factors
                qcd_os,
                w,
                tt,
                # Fractions
                Leaf(
                    name='frac_qcd',
                    file='{HOME}/public/Htautau/FakeRate2016/{VERSION}/{CHANNEL}/{CATEGORY}/pieces/frac_qcd.root'.format(HOME=home,VERSION=version,CHANNEL=channel,CATEGORY=category),
                    object='h_w_2d',
                    vars=['tau_pt','tau_decay']
                ),
                Leaf(
                    name='frac_w',
                    file='{HOME}/public/Htautau/FakeRate2016/{VERSION}/{CHANNEL}/{CATEGORY}/pieces/frac_wjets.root'.format(HOME=home,VERSION=version,CHANNEL=channel,CATEGORY=category),
                    object='h_w_2d',
                    vars=['tau_pt','tau_decay']
                ),
                Leaf(
                    name='frac_dy',
                    file='{HOME}/public/Htautau/FakeRate2016/{VERSION}/{CHANNEL}/{CATEGORY}/pieces/frac_dy.root'.format(HOME=home,VERSION=version,CHANNEL=channel,CATEGORY=category),
                    object='h_w_2d',
                    vars=['tau_pt','tau_decay']
                ),
                Leaf(
                    name='frac_tt',
                    file='{HOME}/public/Htautau/FakeRate2016/{VERSION}/{CHANNEL}/{CATEGORY}/pieces/frac_tt.root'.format(HOME=home,VERSION=version,CHANNEL=channel,CATEGORY=category),
                    object='h_w_2d',
                    vars=['tau_pt','tau_decay']
                )
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
                         file='{HOME}/public/Htautau/FakeRate2016/{VERSION}/{CHANNEL}/{CATEGORY}/pieces/uncertainties_QCD_W.root'.format(HOME=home,VERSION=version,CHANNEL=channel,CATEGORY=category),
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
                         file='{HOME}/public/Htautau/FakeRate2016/{VERSION}/{CHANNEL}/{CATEGORY}/pieces/uncertainties_QCD_W.root'.format(HOME=home,VERSION=version,CHANNEL=channel,CATEGORY=category),
                         object='uncertainties_QCD_MVis_Iso_SS2OS_up',
                         vars=['mvis','tau2_pt']
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
                         file='{HOME}/public/Htautau/FakeRate2016/{VERSION}/{CHANNEL}/{CATEGORY}/pieces/uncertainties_QCD_W.root'.format(HOME=home,VERSION=version,CHANNEL=channel,CATEGORY=category),
                         object='uncertainties_QCD_MVis_Iso_SS2OS_up',
                         vars=['mvis','tau2_pt']
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
                         file='{HOME}/public/Htautau/FakeRate2016/{VERSION}/{CHANNEL}/{CATEGORY}/pieces/uncertainties_QCD_W.root'.format(HOME=home,VERSION=version,CHANNEL=channel,CATEGORY=category),
                         object='uncertainties_QCD_MVis_Iso_SS2OS_up',
                         vars=['mvis','tau2_pt']
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
                         file='{HOME}/public/Htautau/FakeRate2016/{VERSION}/{CHANNEL}/{CATEGORY}/pieces/uncertainties_QCD_W.root'.format(HOME=home,VERSION=version,CHANNEL=channel,CATEGORY=category),
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
                        file='{HOME}/public/Htautau/FakeRate2016/{VERSION}/{CHANNEL}/{CATEGORY}/pieces/uncertainties_QCD_W.root'.format(HOME=home,VERSION=version,CHANNEL=channel,CATEGORY=category),
                        object='uncertainties_QCD_MVis_Iso_SS2OS_down',
                        vars=['mvis','tau2_pt']
                    ),
                    qcd_os.find('ff_qcd_os')
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
                         file='{HOME}/public/Htautau/FakeRate2016/{VERSION}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D.root'.format(HOME=home,VERSION=version,CHANNEL=channel,CATEGORY=category),
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
                         file='{HOME}/public/Htautau/FakeRate2016/{VERSION}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D.root'.format(HOME=home,VERSION=version,CHANNEL=channel,CATEGORY=category),
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
                         file='{HOME}/public/Htautau/FakeRate2016/{VERSION}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D.root'.format(HOME=home,VERSION=version,CHANNEL=channel,CATEGORY=category),
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
                         file='{HOME}/public/Htautau/FakeRate2016/{VERSION}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D.root'.format(HOME=home,VERSION=version,CHANNEL=channel,CATEGORY=category),
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
                         file='{HOME}/public/Htautau/FakeRate2016/{VERSION}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D.root'.format(HOME=home,VERSION=version,CHANNEL=channel,CATEGORY=category),
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
                         file='{HOME}/public/Htautau/FakeRate2016/{VERSION}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D.root'.format(HOME=home,VERSION=version,CHANNEL=channel,CATEGORY=category),
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
                     file='{HOME}/public/Htautau/FakeRate2016/{VERSION}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D.root'.format(HOME=home,VERSION=version,CHANNEL=channel,CATEGORY=category),
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
                         file='{HOME}/public/Htautau/FakeRate2016/{VERSION}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D.root'.format(HOME=home,VERSION=version,CHANNEL=channel,CATEGORY=category),
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
                         file='{HOME}/public/Htautau/FakeRate2016/{VERSION}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D.root'.format(HOME=home,VERSION=version,CHANNEL=channel,CATEGORY=category),
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
                         file='{HOME}/public/Htautau/FakeRate2016/{VERSION}/{CHANNEL}/{CATEGORY}/pieces/FakeFactors_Data_QCD_3D.root'.format(HOME=home,VERSION=version,CHANNEL=channel,CATEGORY=category),
                         object='FakeFactors_Data_QCDSS_3D_SS_Iso_Medium_SS_InvertIso_Medium_tau_pt_vs_decayMode_error_dm1_njet1_low',
                         vars=['tau_pt','tau_decay','njets']
                     ),
                     qcd_os.find('ff_qcd_os')
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
        fill(ff_comb, comb_w_up,   sys='ff_w_syst_up')
        fill(ff_comb, comb_w_down,   sys='ff_w_syst_down')
        fill(ff_comb, comb_tt_up,   sys='ff_tt_syst_up')
        fill(ff_comb, comb_tt_down,   sys='ff_tt_syst_down')
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
        
        
        
        file = ROOT.TFile.Open("{HOME}/public/Htautau/FakeRate2016/{VERSION}/{CHANNEL}/{CATEGORY}/fakeFactors_{VERSION}.root".format(HOME=home,VERSION=version,CHANNEL=channel,CATEGORY=category), "recreate")
        # Write meta-data
        version_ts = ROOT.TString(version)
        tag_ts     = ROOT.TString(tag)
        file.WriteObject(version_ts , "version")
        file.WriteObject(tag_ts     , "tag")
        # Write fake factors
        file.WriteObject(ff_qcd_os.fakefactor  , "ff_qcd_os")
        file.WriteObject(ff_comb.fakefactor    , "ff_comb")
        #
        file.Close()
    

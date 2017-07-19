import ROOT as R
import argparse

if __name__ == '__main__':

     parser = argparse.ArgumentParser()
     parser.add_argument('--channel', dest = 'channel', help='Channel to plot: mt,et,tt', type=str, metavar = 'TAG', required = True)
     args = parser.parse_args()
    

     files_mt = [{'name': 'ViennaTool/fakefactor/data_mt/FF_corr_QCD_MCsum_noGen_nonclosure.root','data':'nonclosure_fit', 'graph':'nonclosure_QCD','CMS':'Preliminary','Y':[0,2],'X':[0,305], 'Label':'m_{vis} [GeV]','file':'nonclosure_QCD'},
              {'name': 'ViennaTool/fakefactor/data_mt/FF_corr_QCD_MCsum_noGen_muisocorr.root','data':'muiso_corr', 'graph':'muiso_QCD','CMS':'Preliminary','Y':[0.4,1.3],'X':[0,0.71], 'Label':'iso(#mu)','file':'muisocorr_QCD'},
              {'name': 'ViennaTool/fakefactor/data_mt/FF_corr_QCD_MCsum_noGen_OSSScorr.root','data':'OSSS_corr', 'graph':'OSSS_corr_QCD','CMS':'Preliminary','Y':[0,2],'X':[0,305], 'Label':'m_{vis} [GeV]','file':'OSSScorr_QCD'},
              {'name': 'ViennaTool/fakefactor/data_mt/FF_corr_TT_MC_noGen_nonclosure.root','data':'nonclosure_fit', 'graph':'nonclosure_TT_MC','CMS':'Simulation','Y':[0.5,1.5],'X':[0,250], 'Label':'m_{vis} [GeV]','file':'nonclosure_TT'},
              {'name': 'ViennaTool/fakefactor/data_mt/FF_corr_Wjets_MC_noGen_mtcorr.root','data':'mt_corr', 'graph':'mt_corr_Wjets','CMS':'Simulation','Y':[0.4,2],'X':[0,250], 'Label':'m_{T} [GeV]','file':'mtcorr_W'},
              {'name': 'ViennaTool/fakefactor/data_mt/FF_corr_Wjets_MCsum_noGen_nonclosure.root','data':'nonclosure_fit', 'graph':'nonclosure_Wjets','CMS':'Preliminary','Y':[0,2],'X':[0,305], 'Label':'m_{vis} [GeV]','file':'nonclosure_W'},
              #{'name': 'ViennaTool/fakefactor/data_mt/FF_corr_QCD_MCsum_noGen_nonclosure_alt.root','data':'nonclosure_fit', 'graph':'nonclosure_QCD','CMS':'Preliminary','Y':[0,2],'X':[0,305], 'Label':'m_{vis} [GeV]','file':'nonclosure_QCD_alt'},
              #{'name': 'ViennaTool/fakefactor/data_mt/FF_corr_QCD_MCsum_noGen_muisocorr_alt.root','data':'muiso_corr', 'graph':'muiso_QCD','CMS':'Preliminary','Y':[0.4,1.3],'X':[0,0.71], 'Label':'iso(#mu)','file':'muisocorr_QCD_alt'},
              #{'name': 'ViennaTool/fakefactor/data_mt/FF_corr_QCD_MCsum_noGen_OSSScorr_alt.root','data':'OSSS_corr', 'graph':'OSSS_corr_QCD','CMS':'Preliminary','Y':[0,2],'X':[0,305], 'Label':'m_{vis} [GeV]','file':'OSSScorr_QCD_alt'},
              #{'name': 'ViennaTool/fakefactor/data_mt/FF_corr_TT_MC_noGen_nonclosure_alt.root','data':'nonclosure_fit', 'graph':'nonclosure_TT_MC','CMS':'Simulation','Y':[0.5,1.5],'X':[0,250], 'Label':'m_{vis} [GeV]','file':'nonclosure_TT_alt'},
              #{'name': 'ViennaTool/fakefactor/data_mt/FF_corr_Wjets_MC_noGen_mtcorr_alt.root','data':'mt_corr', 'graph':'mt_corr_Wjets','CMS':'Simulation','Y':[0.4,2],'X':[0,250], 'Label':'m_{T} [GeV]','file':'mtcorr_W_alt'},
              #{'name': 'ViennaTool/fakefactor/data_mt/FF_corr_Wjets_MCsum_noGen_nonclosure_alt.root','data':'nonclosure_fit', 'graph':'nonclosure_Wjets','CMS':'Preliminary','Y':[0,2],'X':[0,305], 'Label':'m_{vis} [GeV]','file':'nonclosure_W_alt'}
     ]
     

     files_et = [{'name': 'ViennaTool/fakefactor/data_et/FF_corr_QCD_MCsum_noGen_nonclosure.root','data':'nonclosure_fit', 'graph':'nonclosure_QCD','CMS':'Preliminary','Y':[0,2],'X':[0,305], 'Label':'m_{vis} [GeV/c]','file':'nonclosure_QCD'},
              {'name': 'ViennaTool/fakefactor/data_et/FF_corr_QCD_MCsum_noGen_muisocorr.root','data':'muiso_corr', 'graph':'muiso_QCD','CMS':'Preliminary','Y':[0.4,1.3],'X':[0,0.71], 'Label':'iso(e)','file':'eisocorr_QCD'},
              {'name': 'ViennaTool/fakefactor/data_et/FF_corr_QCD_MCsum_noGen_OSSScorr.root','data':'OSSS_corr', 'graph':'OSSS_corr_QCD','CMS':'Preliminary','Y':[0,2],'X':[0,305], 'Label':'m_{vis} [GeV/c]','file':'OSSScorr_QCD'},
              {'name': 'ViennaTool/fakefactor/data_et/FF_corr_TT_MC_noGen_nonclosure.root','data':'nonclosure_fit', 'graph':'nonclosure_TT_MC','CMS':'Simulation','Y':[0.5,1.5],'X':[0,250], 'Label':'m_{vis} [GeV/c]','file':'nonclosure_TT'},
              {'name': 'ViennaTool/fakefactor/data_et/FF_corr_Wjets_MC_noGen_mtcorr.root','data':'mt_corr', 'graph':'mt_corr_Wjets','CMS':'Simulation','Y':[0.4,2],'X':[0,250], 'Label':'m_{T} [GeV/c]','file':'mtcorr_W'},
              {'name': 'ViennaTool/fakefactor/data_et/FF_corr_Wjets_MCsum_noGen_nonclosure.root','data':'nonclosure_fit', 'graph':'nonclosure_Wjets','CMS':'Preliminary','Y':[0,2],'X':[0,305], 'Label':'m_{vis} [GeV/c]','file':'nonclosure_W'},
              #{'name': 'ViennaTool/fakefactor/data_et/FF_corr_QCD_MCsum_noGen_nonclosure_alt.root','data':'nonclosure_fit', 'graph':'nonclosure_QCD','CMS':'Preliminary','Y':[0,2],'X':[0,305], 'Label':'m_{vis} [GeV/c]','file':'nonclosure_QCD_alt'},
              #{'name': 'ViennaTool/fakefactor/data_et/FF_corr_QCD_MCsum_noGen_muisocorr_alt.root','data':'muiso_corr', 'graph':'muiso_QCD','CMS':'Preliminary','Y':[0.4,1.3],'X':[0,0.71], 'Label':'iso(e)','file':'eisocorr_QCD_alt'},
              #{'name': 'ViennaTool/fakefactor/data_et/FF_corr_QCD_MCsum_noGen_OSSScorr_alt.root','data':'OSSS_corr', 'graph':'OSSS_corr_QCD','CMS':'Preliminary','Y':[0,2],'X':[0,305], 'Label':'m_{vis} [GeV/c]','file':'OSSScorr_QCD_alt'},
              #{'name': 'ViennaTool/fakefactor/data_et/FF_corr_TT_MC_noGen_nonclosure_alt.root','data':'nonclosure_fit', 'graph':'nonclosure_TT_MC','CMS':'Simulation','Y':[0.5,1.5],'X':[0,250], 'Label':'m_{vis} [GeV/c]','file':'nonclosure_TT_alt'},
              #{'name': 'ViennaTool/fakefactor/data_et/FF_corr_Wjets_MC_noGen_mtcorr_alt.root','data':'mt_corr', 'graph':'mt_corr_Wjets','CMS':'Simulation','Y':[0.4,2],'X':[0,250], 'Label':'m_{T} [GeV/c]','file':'mtcorr_W_alt'},
              #{'name': 'ViennaTool/fakefactor/data_et/FF_corr_Wjets_MCsum_noGen_nonclosure_alt.root','data':'nonclosure_fit', 'graph':'nonclosure_Wjets','CMS':'Preliminary','Y':[0,2],'X':[0,305], 'Label':'m_{vis} [GeV/c]','file':'nonclosure_W_alt'},
     ]
     
     files_tt = [{'name': 'ViennaTool/fakefactor/data_tt/FF_corr_QCD_MCsum_noGen_nonclosure.root','data':'nonclosure_fit', 'graph':'nonclosure_QCD','CMS':'Preliminary','Y':[0,2],'X':[0,305], 'Label':'m_{vis} [GeV/c]','file':'nonclosure_QCD'},
              {'name': 'ViennaTool/fakefactor/data_tt/FF_corr_QCD_MCsum_noGen_OSSScorr.root','data':'OSSS_corr', 'graph':'OSSS_corr_QCD','CMS':'Preliminary','Y':[0,2],'X':[0,305], 'Label':'m_{vis} [GeV/c]','file':'OSSScorr_QCD'},
              {'name': 'ViennaTool/fakefactor/data_tt/FF_corr_QCD_MCsum_noGen_nonclosure_lepPt.root','data':'nonclosure_fit', 'graph':'nonclosure_QCD','CMS':'Preliminary','Y':[0.5,1.5],'X':[40,120], 'Label':'p_{T} [GeV/c]','file':'nonclosure_pt_QCD'},
              #{'name': 'ViennaTool/fakefactor/data_tt/FF_corr_QCD_MCsum_noGen_nonclosure_alt.root','data':'nonclosure_fit', 'graph':'nonclosure_QCD','CMS':'Preliminary','Y':[0,2],'X':[0,305], 'Label':'m_{vis} [GeV/c]','file':'nonclosure_QCD_alt'},
              #{'name': 'ViennaTool/fakefactor/data_tt/FF_corr_QCD_MCsum_noGen_OSSScorr_alt.root','data':'OSSS_corr', 'graph':'OSSS_corr_QCD','CMS':'Preliminary','Y':[0,2],'X':[0,305], 'Label':'m_{vis} [GeV/c]','file':'OSSScorr_QCD_alt'},
              #{'name': 'ViennaTool/fakefactor/data_tt/FF_corr_QCD_MCsum_noGen_nonclosure_lepPt_alt.root','data':'nonclosure_fit', 'graph':'nonclosure_QCD','CMS':'Preliminary','Y':[0.5,1.5],'X':[40,120], 'Label':'p_{T} [GeV/c]','file':'nonclosure_pt_QCD_alt'}
     ]

     channel = ""
     if(args.channel == "kMU"):
          files = files_mt
          channel = "mt"
     elif(args.channel == "kEL"):
          files = files_et
          channel = "et"
     elif(args.channel == "kTAU"):
          files = files_tt
          channel = "tt"
     for el in files:
          file = R.TFile(el['name'])
          
          datapoints = file.Get(el['data'])
          graph = file.Get(el['graph'])
          canvas = R.TCanvas('new')
          R.gPad.SetBottomMargin(0.15)
          R.gPad.SetLeftMargin(0.12)
          graph.SetLineWidth(2)
          graph.SetMarkerColor(R.kRed)
          
          
          graph.SetTitle("")
          graph.SetLineColor(R.kOrange-2)
          graph.GetYaxis().SetRangeUser(el['Y'][0], el['Y'][1] )
          graph.GetYaxis().SetTitle('Ratio')
          graph.GetYaxis().SetTitleSize(0.065)
          graph.GetYaxis().SetTitleFont(62)
          graph.GetYaxis().SetLabelSize(0.045)
          graph.GetYaxis().SetTitleOffset(0.75)
          graph.GetXaxis().SetRangeUser(el['X'][0], el['X'][1])
          graph.GetXaxis().SetTitle(el['Label'])
          graph.GetXaxis().SetTitleSize(0.065)
          graph.GetXaxis().SetTitleOffset(0.95)
          graph.GetXaxis().SetTitleFont(62)
          graph.GetXaxis().SetLabelSize(0.045)
          
          datapoints.SetMarkerStyle(20)
          
          cms1 = R.TLatex( 0.12, 0.915, "CMS" )
          cms2 = R.TLatex( 0.213, 0.915, el['CMS'] )
          cms1.SetNDC();
          cms1.SetTextSize(0.06);
          
          infoRight = R.TLatex( 0.735, 0.915, "35.9 fb^{-1} (13 TeV)" )
          infoRight.SetNDC();
          infoRight.SetTextSize(0.035);
          
          
          cms2.SetNDC();
          cms2.SetTextFont(12)
          cms2.SetTextSize(0.06);
          
          
          
          #DrawErrorBand(graph)
          graph.Draw('ap')
          datapoints.Draw('e1p same')
          cms1.Draw()
          cms2.Draw()
          R.gPad.RedrawAxis()
          if(el['CMS']=='Preliminary'): infoRight.Draw()
          name = el['name'].split('/')[-1]
          canvas.Print( 'ViennaTool/Images/data_{0}/'.format(channel)  + el['file'] + '.png' )
          canvas.Print( 'ViennaTool/Images/data_{0}/'.format(channel)  + el['file'] + '.pdf' )
          #canvas.Print( 'tt/' + el['file'] + '.root')




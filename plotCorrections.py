import ROOT as R
import argparse

if __name__ == '__main__':

     parser = argparse.ArgumentParser()
     parser.add_argument('--channel', dest = 'channel', help='Channel to plot: mt,et,tt', type=str, metavar = 'TAG', required = True)
     args = parser.parse_args()
    
     preliminary = 'Preliminary'
     supplementary = 'Supplimentary'
     
     files_mt = [#{'name': 'ViennaTool/fakefactor/data_mt/FF_corr_QCD_MCsum_noGen_nonclosure.root','data':'nonclosure_fit', 'graph':'nonclosure_QCD','CMS':preliminary,'Y':[0,2],'X':[0,305], 'Label':'m_{vis} (GeV)','file':'nonclosure_QCD','plotLabel1':'#mu^{}#tau_{h} QCD multijet','plotLabel2':'Nonclosure correction'},
              #{'name': 'ViennaTool/fakefactor/data_mt/FF_corr_QCD_MCsum_noGen_muisocorr.root','data':'muiso_corr', 'graph':'muiso_QCD','CMS':preliminary,'Y':[0.4,1.3],'X':[0,0.71], 'Label':'iso(#mu)','file':'muisocorr_QCD','plotLabel1':'#mu^{}#tau_{h} QCD multijet','plotLabel2':'Iso(#mu) correction'},
              {'name': 'ViennaTool/fakefactor/data_mt/FF_corr_QCD_MCsum_noGen_OSSScorr.root','data':'OSSS_corr', 'graph':'OSSS_corr_QCD','CMS':preliminary,'Y':[0.2,2.1],'X':[0,305], 'Label':'m_{vis} (GeV)','file':'OSSScorr_QCD','plotLabel1':'#mu^{}#tau_{h} QCD multijet','plotLabel2':'opposite/same charge correction'},
              {'name': 'ViennaTool/fakefactor/data_mt/FF_corr_TT_MC_noGen_nonclosure.root','data':'nonclosure_fit', 'graph':'nonclosure_TT_MC','CMS':'Simulation '+preliminary,'Y':[0.5,1.5],'X':[0,250], 'Label':'m_{vis} (GeV)','file':'nonclosure_TT','plotLabel1':'#mu^{}#tau_{h} t#bar{t}','plotLabel2':'Nonclosure correction'},
              {'name': 'ViennaTool/fakefactor/data_mt/FF_corr_Wjets_MC_noGen_mtcorr.root','data':'mt_corr', 'graph':'mt_corr_Wjets','CMS':'Simulation '+preliminary,'Y':[0.5,1.5],'X':[0,140], 'Label':'m^{#mu}_{T} [GeV]','file':'mtcorr_W','plotLabel1':'#mu^{}#tau_{h} W+jets','plotLabel2':'m^{#mu}_{T} correction'},
              {'name': 'ViennaTool/fakefactor/data_mt/FF_corr_Wjets_MCsum_noGen_nonclosure.root','data':'nonclosure_fit', 'graph':'nonclosure_Wjets','CMS':preliminary,'Y':[0.5,1.5],'X':[0,305], 'Label':'m_{vis} (GeV)','file':'nonclosure_W','plotLabel1':'#mu^{}#tau_{h} W+jets','plotLabel2':'Nonclosure correction'},
              #{'name': 'ViennaTool/fakefactor/data_mt/FF_corr_QCD_MCsum_noGen_nonclosure_alt.root','data':'nonclosure_fit', 'graph':'nonclosure_QCD','CMS':'Preliminary','Y':[0,2],'X':[0,305], 'Label':'m_{vis} [GeV]','file':'nonclosure_QCD_alt'},
              #{'name': 'ViennaTool/fakefactor/data_mt/FF_corr_QCD_MCsum_noGen_muisocorr_alt.root','data':'muiso_corr', 'graph':'muiso_QCD','CMS':'Preliminary','Y':[0.4,1.3],'X':[0,0.71], 'Label':'iso(#mu)','file':'muisocorr_QCD_alt'},
              #{'name': 'ViennaTool/fakefactor/data_mt/FF_corr_QCD_MCsum_noGen_OSSScorr_alt.root','data':'OSSS_corr', 'graph':'OSSS_corr_QCD','CMS':'Preliminary','Y':[0,2],'X':[0,305], 'Label':'m_{vis} [GeV]','file':'OSSScorr_QCD_alt'},
              #{'name': 'ViennaTool/fakefactor/data_mt/FF_corr_TT_MC_noGen_nonclosure_alt.root','data':'nonclosure_fit', 'graph':'nonclosure_TT_MC','CMS':'Simulation','Y':[0.5,1.5],'X':[0,250], 'Label':'m_{vis} [GeV]','file':'nonclosure_TT_alt'},
              #{'name': 'ViennaTool/fakefactor/data_mt/FF_corr_Wjets_MC_noGen_mtcorr_alt.root','data':'mt_corr', 'graph':'mt_corr_Wjets','CMS':'Simulation','Y':[0.4,2],'X':[0,250], 'Label':'m_{T} [GeV]','file':'mtcorr_W_alt'},
              #{'name': 'ViennaTool/fakefactor/data_mt/FF_corr_Wjets_MCsum_noGen_nonclosure_alt.root','data':'nonclosure_fit', 'graph':'nonclosure_Wjets','CMS':'Preliminary','Y':[0,2],'X':[0,305], 'Label':'m_{vis} [GeV]','file':'nonclosure_W_alt'}
     ]
     

     files_et = [{'name': 'ViennaTool/fakefactor/data_et/FF_corr_QCD_MCsum_noGen_nonclosure.root','data':'nonclosure_fit', 'graph':'nonclosure_QCD','CMS':preliminary,'Y':[0,2],'X':[0,305], 'Label':'m_{vis} (GeV)','file':'nonclosure_QCD','plotLabel1':'e#tau_{h} QCD multijet','plotLabel2':'Nonclosure correction'},
              {'name': 'ViennaTool/fakefactor/data_et/FF_corr_QCD_MCsum_noGen_muisocorr.root','data':'muiso_corr', 'graph':'muiso_QCD','CMS':preliminary,'Y':[0.4,1.3],'X':[0,0.71], 'Label':'iso(e)','file':'eisocorr_QCD','plotLabel1':'e#tau_{h} QCD multijet','plotLabel2':'Iso(e) correction'},
              {'name': 'ViennaTool/fakefactor/data_et/FF_corr_QCD_MCsum_noGen_OSSScorr.root','data':'OSSS_corr', 'graph':'OSSS_corr_QCD','CMS':preliminary,'Y':[0,2],'X':[0,305], 'Label':'m_{vis} (GeV)','file':'OSSScorr_QCD','plotLabel1':'e#tau_{h} QCD multijet','plotLabel2':'opposite/same charge correction'},
              {'name': 'ViennaTool/fakefactor/data_et/FF_corr_TT_MC_noGen_nonclosure.root','data':'nonclosure_fit', 'graph':'nonclosure_TT_MC','CMS':'Simulation '+preliminary,'Y':[0.5,1.5],'X':[0,250], 'Label':'m_{vis} (GeV)','file':'nonclosure_TT','plotLabel1':'e#tau_{h} t#bar{t}','plotLabel2':'Nonclosure correction'},
              {'name': 'ViennaTool/fakefactor/data_et/FF_corr_Wjets_MC_noGen_mtcorr.root','data':'mt_corr', 'graph':'mt_corr_Wjets','CMS':'Simulation '+preliminary,'Y':[0.5,1.5],'X':[0,140], 'Label':'m^{e}_{T} [GeV]','file':'mtcorr_W','plotLabel1':'e#tau_{h} W+jets','plotLabel2':'m^{e}_{T} correction'},
              {'name': 'ViennaTool/fakefactor/data_et/FF_corr_Wjets_MCsum_noGen_nonclosure.root','data':'nonclosure_fit', 'graph':'nonclosure_Wjets','CMS':preliminary,'Y':[0,2],'X':[0,305], 'Label':'m_{vis} (GeV)','file':'nonclosure_W','plotLabel1':'e#tau_{h} W+jets','plotLabel2':'Nonclosure correction'},
              #{'name': 'ViennaTool/fakefactor/data_et/FF_corr_QCD_MCsum_noGen_nonclosure_alt.root','data':'nonclosure_fit', 'graph':'nonclosure_QCD','CMS':'Preliminary','Y':[0,2],'X':[0,305], 'Label':'m_{vis} [GeV/c]','file':'nonclosure_QCD_alt'},
              #{'name': 'ViennaTool/fakefactor/data_et/FF_corr_QCD_MCsum_noGen_muisocorr_alt.root','data':'muiso_corr', 'graph':'muiso_QCD','CMS':'Preliminary','Y':[0.4,1.3],'X':[0,0.71], 'Label':'iso(e)','file':'eisocorr_QCD_alt'},
              #{'name': 'ViennaTool/fakefactor/data_et/FF_corr_QCD_MCsum_noGen_OSSScorr_alt.root','data':'OSSS_corr', 'graph':'OSSS_corr_QCD','CMS':'Preliminary','Y':[0,2],'X':[0,305], 'Label':'m_{vis} [GeV/c]','file':'OSSScorr_QCD_alt'},
              #{'name': 'ViennaTool/fakefactor/data_et/FF_corr_TT_MC_noGen_nonclosure_alt.root','data':'nonclosure_fit', 'graph':'nonclosure_TT_MC','CMS':'Simulation','Y':[0.5,1.5],'X':[0,250], 'Label':'m_{vis} [GeV/c]','file':'nonclosure_TT_alt'},
              #{'name': 'ViennaTool/fakefactor/data_et/FF_corr_Wjets_MC_noGen_mtcorr_alt.root','data':'mt_corr', 'graph':'mt_corr_Wjets','CMS':'Simulation','Y':[0.4,2],'X':[0,250], 'Label':'m_{T} [GeV/c]','file':'mtcorr_W_alt'},
              #{'name': 'ViennaTool/fakefactor/data_et/FF_corr_Wjets_MCsum_noGen_nonclosure_alt.root','data':'nonclosure_fit', 'graph':'nonclosure_Wjets','CMS':'Preliminary','Y':[0,2],'X':[0,305], 'Label':'m_{vis} [GeV/c]','file':'nonclosure_W_alt'},
     ]
     
     files_tt = [{'name': 'ViennaTool/fakefactor/data_tt/FF_corr_QCD_MCsum_noGen_nonclosure.root','data':'nonclosure_fit', 'graph':'nonclosure_QCD','CMS':preliminary,'Y':[0.5,1.5],'X':[0,305], 'Label':'m_{vis} (GeV)','file':'nonclosure_QCD','plotLabel1':'#tau_{h}#tau_{h} QCD multijet','plotLabel2':'Nonclosure correction'},
              {'name': 'ViennaTool/fakefactor/data_tt/FF_corr_QCD_MCsum_noGen_OSSScorr.root','data':'OSSS_corr', 'graph':'OSSS_corr_QCD','CMS':preliminary,'Y':[0.5,1.5],'X':[0,305], 'Label':'m_{vis} (GeV)','file':'OSSScorr_QCD','plotLabel1':'#tau_{h}#tau_{h} QCD multijet','plotLabel2':'opposite/same charge correction'},
              {'name': 'ViennaTool/fakefactor/data_tt/FF_corr_QCD_MCsum_noGen_nonclosure_lepPt.root','data':'nonclosure_fit', 'graph':'nonclosure_QCD','CMS':preliminary,'Y':[0.5,1.5],'X':[40,120], 'Label':'p_{T} (GeV)','file':'nonclosure_pt_QCD','plotLabel1':'#tau_{h}#tau_{h} QCD multijet','plotLabel2':'p_{T} correction'},
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
          canvas2 = R.TCanvas('new2','test2',800,800)
          canvas = R.TCanvas('new','test',800,800)
          canvas.cd()
          R.gPad.SetBottomMargin(0.15)
          R.gPad.SetLeftMargin(0.15)
          graph.SetLineWidth(2)
          graph.SetMarkerColor(R.kBlack)
          
          
          graph.SetTitle("")
          graph.SetLineColor(R.kOrange-2)
          graph.GetYaxis().SetRangeUser(el['Y'][0], el['Y'][1] )
          graph.GetYaxis().SetTitle('Correction')
          graph.GetYaxis().SetTitleSize(0.06)
          graph.GetYaxis().SetTitleFont(42)
          graph.GetYaxis().SetLabelSize(0.045)
          graph.GetYaxis().SetTitleOffset(1.07)
          graph.GetYaxis().SetNdivisions(5,5,0)
          graph.GetXaxis().SetRangeUser(el['X'][0], el['X'][1])
          graph.GetXaxis().SetTitle(el['Label'])
          graph.GetXaxis().SetTitleSize(0.06)
          graph.GetXaxis().SetTitleOffset(1.06)
          graph.GetXaxis().SetTitleFont(42)
          graph.GetXaxis().SetLabelSize(0.045)

          R.gStyle.SetEndErrorSize(0)
          R.gStyle.SetErrorX(0)
          datapoints.SetMarkerStyle(20)
          datapoints.SetLineWidth(1)
          datapoints.SetMarkerSize(1.5)

          legendGraph = R.TGraph();
          legendGraph.SetLineColor(R.kBlack)
          legendGraph.SetLineWidth(4)
          legendGraph.SetFillColor(R.kOrange-2)
          
          leg = R.TLegend(0.7,0.73,0.88,0.88);
          leg.SetShadowColor(10)
          leg.SetLineColor(10)
          leg.SetTextFont(42)
          leg.SetTextSize(0.035)
          leg.AddEntry(datapoints,"Measured","EP")
          leg.AddEntry(legendGraph,"#splitline{Smoothed}{curve}","lf")
          
          cms1 = R.TLatex( 0.16, 0.915, "CMS" )
          cms2 = R.TLatex( 0.298, 0.915, el['CMS'] )
          cms2b = R.TLatex( 0.298, 0.915, el['CMS'].replace(preliminary,supplementary) )
          cms1.SetNDC();
          cms1.SetTextFont(62);
          cms1.SetTextSize(0.06);
          
          infoRight = R.TLatex( 0.68, 0.915, "35.9 fb^{-1} (13 TeV)" )
          infoRight.SetNDC();
          infoRight.SetTextSize(0.03);
          infoRight.SetTextFont(42);
          
          
          cms2.SetNDC();
          cms2.SetTextFont(52)
          cms2.SetTextSize(0.05);
          cms2b.SetNDC();
          cms2b.SetTextFont(52)
          cms2b.SetTextSize(0.05);

          cms3 = R.TLatex( 0.19,0.86, el['plotLabel1'])
          cms3.SetNDC()
          cms3.SetTextFont(42)
          cms3.SetTextSize(0.035)
          cms4 = R.TLatex( 0.19,0.815, el['plotLabel2'])
          cms4.SetNDC()
          cms4.SetTextFont(42)
          cms4.SetTextSize(0.035)
          
          
          #DrawErrorBand(graph)
          graph.Draw('ap')
          datapoints.Draw('e1p same')
          cms1.Draw()
          cms3.Draw()
          cms4.Draw()
          leg.Draw("same")
          #if( 'Simulation' in el['CMS'] ): cms2.Draw()
          R.gPad.RedrawAxis()
          R.gPad.Modified()
          l=R.TLine()
          #l.DrawLine(R.gPad.GetUxmin(), R.gPad.GetUymax(), R.gPad.GetUxmax(), R.gPad.GetUymax());
          l.DrawLine(el['X'][1], el['Y'][0], el['X'][1], el['Y'][1] );
          if(el['CMS']==preliminary): infoRight.Draw()
          name = el['name'].split('/')[-1]

          ############################################################
          ##
          canvas2.cd();
          canvas.DrawClonePad();
          canvas.cd();
          ############################################################
          for i in range(0,2):
               if(i==0):
                    cms2.Draw()
                    canvas.Print( 'ViennaTool/Images/data_{0}/'.format(channel)  + el['file'] + '_'+channel+'_preliminary.png' )
                    canvas.Print( 'ViennaTool/Images/data_{0}/'.format(channel)  + el['file'] + '_'+channel+'_preliminary.pdf' )
               if(i==1):
                    canvas2.cd()
                    cms2b.Draw()
                    canvas2.Print( 'ViennaTool/Images/data_{0}/'.format(channel)  + el['file'] + '_'+channel+'.png' )
                    canvas2.Print( 'ViennaTool/Images/data_{0}/'.format(channel)  + el['file'] + '_'+channel+'.pdf' )
          
          #canvas.Print( 'tt/' + el['file'] + '.root')




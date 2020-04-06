import ROOT as R
from ROOT import TGraphAsymmErrors, TAxis
import argparse

if __name__ == '__main__':

     R.gROOT.SetBatch(True)

     parser = argparse.ArgumentParser()
     parser.add_argument('--channel', dest = 'channel', help='Channel to plot: kMU,kEL,kTAU', type=str, metavar = 'TAG', required = True)
     parser.add_argument('--doNjetBinning', dest = 'do_njetbinning', help='Defines if corrections are binned in 0jet/1jet', type=int, metavar = 'TAG', required = True)
     parser.add_argument('--usePt_nonclosure_Wjets', dest = 'do_pt_lep', help='use pt binned wjets corrections', type=int, metavar = 'TAG', required = True)


     args = parser.parse_args()
    
     preliminary = 'Preliminary'
     supplementary = 'Supplimentary'
     
     files_mt = [
              {'name': 'ViennaTool/fakefactor/data_mt/FF_corr_QCD_MCsum_noGen_nonclosure.root','data':'nonclosure_fit', 'graph':'nonclosure_QCD','CMS':preliminary,'Y':[0,2],'X':[0,450], 'Label':'m_{vis} (GeV)','file':'corr_QCD_nonclosure','plotLabel1':'#mu^{}#tau_{h} QCD multijet','plotLabel2':'Nonclosure correction'},
              {'name': 'ViennaTool/fakefactor/data_mt/FF_corr_QCD_MCsum_noGen_muisocorr.root','data':'nonclosure', 'graph':'muiso_QCD','CMS':preliminary,'Y':[0.4,1.3],'X':[0,0.31], 'Label':'iso(#mu)','file':'corr_QCD_lepiso','plotLabel1':'#mu^{}#tau_{h} QCD multijet','plotLabel2':'Iso(#mu) correction'},
              {'name': 'ViennaTool/fakefactor/data_mt/FF_corr_QCD_MCsum_noGen_OSSScorr.root','data':'OSSS_corr', 'graph':'OSSS_corr_QCD','CMS':preliminary,'Y':[0.2,2.1],'X':[0,450], 'Label':'m_{vis} (GeV)','file':'corr_QCD_OSSS','plotLabel1':'#mu^{}#tau_{h} QCD multijet','plotLabel2':'opposite/same charge correction'},
              {'name': 'ViennaTool/fakefactor/data_mt/FF_corr_TT_MC_noGen_nonclosure.root','data':'nonclosure_fit', 'graph':'nonclosure_TT_MC','CMS':'Simulation '+preliminary,'Y':[0.5,1.5],'X':[0,250], 'Label':'m_{vis} (GeV)','file':'corr_TT_nonclosure','plotLabel1':'#mu^{}#tau_{h} t#bar{t}','plotLabel2':'Nonclosure correction'},
              {'name': 'ViennaTool/fakefactor/data_mt/FF_corr_Wjets_MC_noGen_mtcorr.root','data':'mt_corr', 'graph':'mt_corr_Wjets','CMS':'Simulation '+preliminary,'Y':[0.5,1.5],'X':[0,450], 'Label':'m_{vis} (GeV)','file':'corr_W_mt','plotLabel1':'#mu^{}#tau_{h} W+jets','plotLabel2':'DR-SR correction'},
              {'name': 'ViennaTool/fakefactor/data_mt/FF_corr_Wjets_MCsum_noGen_nonclosure.root','data':'nonclosure_fit', 'graph':'nonclosure_Wjets','CMS':preliminary,'Y':[0.5,1.5],'X':[20,250], 'Label':'Muon p_{T} (GeV)','file':'corr_W_nonclosure','plotLabel1':'#mu^{}#tau_{h} W+jets','plotLabel2':'Nonclosure correction'},
              #{'name': 'ViennaTool/fakefactor/data_mt/FF_corr_QCD_MCsum_noGen_nonclosure_lepPt.root','data':'nonclosure_fit', 'graph':'nonclosure_QCD','CMS':preliminary,'Y':[0.5,1.5],'X':[20,120], 'Label':'p_{T} (GeV)','file':'corr_QCD_nonclosure_pt','plotLabel1':'#mu^{}#tau_{h} QCD multijet','plotLabel2':'p_{T} correction'},
              #{'name': 'ViennaTool/fakefactor/data_mt/FF_corr_Wjets_MCsum_noGen_nonclosure_lepPt.root','data':'nonclosure_fit', 'graph':'nonclosure_Wjets','CMS':preliminary,'Y':[0.5,1.5],'X':[25,120], 'Label':'p_{T} (GeV)','file':'corr_Wjets_nonclosure_pt','plotLabel1':'#mu^{}#tau_{h} W+jets','plotLabel2':'p_{T} correction'},

              #{'name': 'ViennaTool/fakefactor/data_mt/FF_corr_QCD_MCsum_noGen_nonclosure_alt.root','data':'nonclosure_fit', 'graph':'nonclosure_QCD','CMS':'Preliminary','Y':[0,2],'X':[0,305], 'Label':'m_{vis} (GeV)','file':'nonclosure_QCD_alt'},
              #{'name': 'ViennaTool/fakefactor/data_mt/FF_corr_QCD_MCsum_noGen_muisocorr_alt.root','data':'muiso_corr', 'graph':'muiso_QCD','CMS':'Preliminary','Y':[0.4,1.3],'X':[0,0.51], 'Label':'iso(#mu)','file':'muisocorr_QCD_alt'},
              #{'name': 'ViennaTool/fakefactor/data_mt/FF_corr_QCD_MCsum_noGen_OSSScorr_alt.root','data':'OSSS_corr', 'graph':'OSSS_corr_QCD','CMS':'Preliminary','Y':[0,2],'X':[0,305], 'Label':'m_{vis} (GeV)','file':'OSSScorr_QCD_alt'},
              #{'name': 'ViennaTool/fakefactor/data_mt/FF_corr_TT_MC_noGen_nonclosure_alt.root','data':'nonclosure_fit', 'graph':'nonclosure_TT_MC','CMS':'Simulation','Y':[0.5,1.5],'X':[0,250], 'Label':'m_{vis} (GeV)','file':'nonclosure_TT_alt'},
              #{'name': 'ViennaTool/fakefactor/data_mt/FF_corr_Wjets_MC_noGen_mtcorr_alt.root','data':'mt_corr', 'graph':'mt_corr_Wjets','CMS':'Simulation','Y':[0.4,2],'X':[0,250], 'Label':'m_{T} (GeV)','file':'mtcorr_W_alt'},
              #{'name': 'ViennaTool/fakefactor/data_mt/FF_corr_Wjets_MCsum_noGen_nonclosure_alt.root','data':'nonclosure_fit', 'graph':'nonclosure_Wjets','CMS':'Preliminary','Y':[0,2],'X':[0,305], 'Label':'m_{vis} (GeV)','file':'nonclosure_W_alt'}
     ]
     if(args.do_njetbinning == 1):
          files_mt.extend([
               {'name': 'ViennaTool/fakefactor/data_mt/FF_corr_QCD_MCsum_noGen_nonclosure_0jet.root','data':'nonclosure_fit', 'graph':'nonclosure_QCD','CMS':preliminary,'Y':[0,2],'X':[0,450], 'Label':'m_{vis} (GeV)','file':'corr_QCD_nonclosure_0jet','plotLabel1':'#mu^{}#tau_{h} QCD multijet','plotLabel2':'Nonclosure correction, 0jet'},
              {'name': 'ViennaTool/fakefactor/data_mt/FF_corr_QCD_MCsum_noGen_nonclosure_1jet.root','data':'nonclosure_fit', 'graph':'nonclosure_QCD','CMS':preliminary,'Y':[0,2],'X':[0,450], 'Label':'m_{vis} (GeV)','file':'corr_QCD_nonclosure_1jet','plotLabel1':'#mu^{}#tau_{h} QCD multijet','plotLabel2':'Nonclosure correction, #geq 1jet'},
              {'name': 'ViennaTool/fakefactor/data_mt/FF_corr_QCD_MCsum_noGen_muisocorr_0jet.root','data':'muiso_corr', 'graph':'muiso_QCD','CMS':preliminary,'Y':[0.4,1.3],'X':[0,0.51], 'Label':'iso(#mu)','file':'corr_QCD_lepiso_0jet','plotLabel1':'#mu^{}#tau_{h} QCD multijet','plotLabel2':'Iso(#mu) correction, 0jet'},
              {'name': 'ViennaTool/fakefactor/data_mt/FF_corr_QCD_MCsum_noGen_muisocorr_1jet.root','data':'muiso_corr', 'graph':'muiso_QCD','CMS':preliminary,'Y':[0.4,1.3],'X':[0,0.51], 'Label':'iso(#mu)','file':'corr_QCD_lepiso_1jet','plotLabel1':'#mu^{}#tau_{h} QCD multijet','plotLabel2':'Iso(#mu) correction, #geq 1jet'},
              {'name': 'ViennaTool/fakefactor/data_mt/FF_corr_Wjets_MC_noGen_mtcorr_0jet.root','data':'mt_corr', 'graph':'mt_corr_Wjets','CMS':'Simulation '+preliminary,'Y':[0.5,1.5],'X':[0,350], 'Label':'m^{#mu}_{T} (GeV)','file':'corr_W_mt_0jet','plotLabel1':'#mu^{}#tau_{h} W+jets','plotLabel2':'m^{#mu}_{T} correction, 0jet'},
              {'name': 'ViennaTool/fakefactor/data_mt/FF_corr_Wjets_MC_noGen_mtcorr_1jet.root','data':'mt_corr', 'graph':'mt_corr_Wjets','CMS':'Simulation '+preliminary,'Y':[0.5,1.5],'X':[0,50], 'Label':'m^{#mu}_{T} (GeV)','file':'corr_W_mt_1jet','plotLabel1':'#mu^{}#tau_{h} W+jets','plotLabel2':'m^{#mu}_{T} correction, #geq 1jet'},
              {'name': 'ViennaTool/fakefactor/data_mt/FF_corr_Wjets_MCsum_noGen_nonclosure_0jet.root','data':'nonclosure_fit', 'graph':'nonclosure_Wjets','CMS':preliminary,'Y':[0.5,1.5],'X':[0,450], 'Label':'m_{vis} (GeV)','file':'corr_W_nonclosure_0jet','plotLabel1':'#mu^{}#tau_{h} W+jets','plotLabel2':'Nonclosure correction, 0jet'},
              {'name': 'ViennaTool/fakefactor/data_mt/FF_corr_Wjets_MCsum_noGen_nonclosure_1jet.root','data':'nonclosure_fit', 'graph':'nonclosure_Wjets','CMS':preliminary,'Y':[0.5,1.5],'X':[0,450], 'Label':'m_{vis} (GeV)','file':'corr_W_nonclosure_1jet','plotLabel1':'#mu^{}#tau_{h} W+jets','plotLabel2':'Nonclosure correction, #geq 1jet'},
              ])
     

     files_et = [{'name': 'ViennaTool/fakefactor/data_et/FF_corr_QCD_MCsum_noGen_nonclosure.root','data':'nonclosure_fit', 'graph':'nonclosure_QCD','CMS':preliminary,'Y':[0,2],'X':[0,450], 'Label':'m_{vis} (GeV)','file':'corr_QCD_nonclosure','plotLabel1':'e#tau_{h} QCD multijet','plotLabel2':'Nonclosure correction'},
              {'name': 'ViennaTool/fakefactor/data_et/FF_corr_QCD_MCsum_noGen_muisocorr.root','data':'nonclosure', 'graph':'muiso_QCD','CMS':preliminary,'Y':[0.4,1.3],'X':[0,0.31], 'Label':'iso(e)','file':'corr_QCD_lepiso','plotLabel1':'e#tau_{h} QCD multijet','plotLabel2':'Iso(e) correction'},
              {'name': 'ViennaTool/fakefactor/data_et/FF_corr_QCD_MCsum_noGen_OSSScorr.root','data':'OSSS_corr', 'graph':'OSSS_corr_QCD','CMS':preliminary,'Y':[0,2],'X':[0,450], 'Label':'m_{vis} (GeV)','file':'corr_QCD_OSSS','plotLabel1':'e#tau_{h} QCD multijet','plotLabel2':'opposite/same charge correction'},
              {'name': 'ViennaTool/fakefactor/data_et/FF_corr_TT_MC_noGen_nonclosure.root','data':'nonclosure_fit', 'graph':'nonclosure_TT_MC','CMS':'Simulation '+preliminary,'Y':[0.5,1.5],'X':[0,250], 'Label':'m_{vis} (GeV)','file':'corr_TT_nonclosure','plotLabel1':'e#tau_{h} t#bar{t}','plotLabel2':'Nonclosure correction'},
              {'name': 'ViennaTool/fakefactor/data_et/FF_corr_Wjets_MC_noGen_mtcorr.root','data':'mt_corr', 'graph':'mt_corr_Wjets','CMS':'Simulation '+preliminary,'Y':[0.5,1.5],'X':[0,450], 'Label':'m_{vis} (GeV)','file':'corr_mt_W','plotLabel1':'e#tau_{h} W+jets','plotLabel2':'DR-SR correction'},
              {'name': 'ViennaTool/fakefactor/data_et/FF_corr_Wjets_MCsum_noGen_nonclosure.root','data':'nonclosure_fit', 'graph':'nonclosure_Wjets','CMS':preliminary,'Y':[0,2],'X':[20,250], 'Label':'Electron p_{T} (GeV)','file':'corr_W_nonclosure','plotLabel1':'e#tau_{h} W+jets','plotLabel2':'Nonclosure correction'},
     ]
     if(args.do_njetbinning == 1):
          files_et.extend([
               {'name': 'ViennaTool/fakefactor/data_et/FF_corr_QCD_MCsum_noGen_nonclosure_0jet.root','data':'nonclosure_fit', 'graph':'nonclosure_QCD','CMS':preliminary,'Y':[0,2],'X':[0,305], 'Label':'m_{vis} (GeV)','file':'corr_QCD_nonclosure_0jet','plotLabel1':'e#tau_{h} QCD multijet','plotLabel2':'Nonclosure correction, 0jet'},
              {'name': 'ViennaTool/fakefactor/data_et/FF_corr_QCD_MCsum_noGen_nonclosure_1jet.root','data':'nonclosure_fit', 'graph':'nonclosure_QCD','CMS':preliminary,'Y':[0,2],'X':[0,305], 'Label':'m_{vis} (GeV)','file':'corr_QCD_nonclosure_1jet','plotLabel1':'e#tau_{h} QCD multijet','plotLabel2':'Nonclosure correction, #geq 1jet'},
              {'name': 'ViennaTool/fakefactor/data_et/FF_corr_QCD_MCsum_noGen_muisocorr_0jet.root','data':'muiso_corr', 'graph':'muiso_QCD','CMS':preliminary,'Y':[0.4,1.3],'X':[0,0.51], 'Label':'iso(e)','file':'corr_QCD_lepiso_0jet','plotLabel1':'e#tau_{h} QCD multijet','plotLabel2':'Iso(e) correction, 0jet'},
              {'name': 'ViennaTool/fakefactor/data_et/FF_corr_QCD_MCsum_noGen_muisocorr_1jet.root','data':'muiso_corr', 'graph':'muiso_QCD','CMS':preliminary,'Y':[0.4,1.3],'X':[0,0.51], 'Label':'iso(e)','file':'corr_QCD_lepiso_1jet','plotLabel1':'e#tau_{h} QCD multijet','plotLabel2':'Iso(e) correction, #geq 1jet'},
              {'name': 'ViennaTool/fakefactor/data_et/FF_corr_Wjets_MC_noGen_mtcorr_0jet.root','data':'mt_corr', 'graph':'mt_corr_Wjets','CMS':'Simulation '+preliminary,'Y':[0.5,1.5],'X':[0,50], 'Label':'m^{e}_{T} (GeV)','file':'corr_mt_W_0jet','plotLabel1':'e#tau_{h} W+jets','plotLabel2':'m^{e}_{T} correction, 0jet'},
              {'name': 'ViennaTool/fakefactor/data_et/FF_corr_Wjets_MC_noGen_mtcorr_1jet.root','data':'mt_corr', 'graph':'mt_corr_Wjets','CMS':'Simulation '+preliminary,'Y':[0.5,1.5],'X':[0,50], 'Label':'m^{e}_{T} (GeV)','file':'corr_mt_W_1jet','plotLabel1':'e#tau_{h} W+jets','plotLabel2':'m^{e}_{T} correction, #geq 1jet'},
              {'name': 'ViennaTool/fakefactor/data_et/FF_corr_Wjets_MCsum_noGen_nonclosure_0jet.root','data':'nonclosure_fit', 'graph':'nonclosure_Wjets','CMS':preliminary,'Y':[0,2],'X':[0,305], 'Label':'m_{vis} (GeV)','file':'corr_W_nonclosure_0jet','plotLabel1':'e#tau_{h} W+jets','plotLabel2':'Nonclosure correction, 0jet'},
              {'name': 'ViennaTool/fakefactor/data_et/FF_corr_Wjets_MCsum_noGen_nonclosure_1jet.root','data':'nonclosure_fit', 'graph':'nonclosure_Wjets','CMS':preliminary,'Y':[0,2],'X':[0,305], 'Label':'m_{vis} (GeV)','file':'corr_W_nonclosure_1jet','plotLabel1':'e#tau_{h} W+jets','plotLabel2':'Nonclosure correction, #geq 1jet'},
          ])
     
     files_tt = [
              {'name': 'ViennaTool/fakefactor/data_tt/FF_corr_QCD_MCsum_noGen_nonclosure.root','data':'nonclosure_fit', 'graph':'nonclosure_QCD','CMS':preliminary,'Y':[0.5,1.5],'X':[0,450], 'Label':'m_{vis} (GeV)','file':'corr_QCD_nonclosure','plotLabel1':'#tau_{h}#tau_{h} QCD multijet','plotLabel2':'Nonclosure correction'},
              {'name': 'ViennaTool/fakefactor/data_tt/FF_corr_QCD_MCsum_noGen_OSSScorr.root','data':'OSSS_corr', 'graph':'OSSS_corr_QCD','CMS':preliminary,'Y':[0.5,1.5],'X':[0,450], 'Label':'m_{vis} (GeV)','file':'corr_QCD_OSSS','plotLabel1':'#tau_{h}#tau_{h} QCD multijet','plotLabel2':'opposite/same charge correction'},
              {'name': 'ViennaTool/fakefactor/data_tt/FF_corr_QCD_MCsum_noGen_nonclosure_lepPt.root','data':'nonclosure_fit', 'graph':'nonclosure_QCD','CMS':preliminary,'Y':[0.5,1.5],'X':[40,250], 'Label':'p_{T} (GeV)','file':'corr_QCD_nonclosure_pt','plotLabel1':'#tau_{h}#tau_{h} QCD multijet','plotLabel2':'p_{T} correction'},
              #{'name': 'ViennaTool/fakefactor/data_tt/FF_corr_QCD_MCsum_noGen_nonclosure_alt.root','data':'nonclosure_fit', 'graph':'nonclosure_QCD','CMS':'Preliminary','Y':[0,2],'X':[0,305], 'Label':'m_{vis} [GeV/c]','file':'nonclosure_QCD_alt'},
              #{'name': 'ViennaTool/fakefactor/data_tt/FF_corr_QCD_MCsum_noGen_OSSScorr_alt.root','data':'OSSS_corr', 'graph':'OSSS_corr_QCD','CMS':'Preliminary','Y':[0,2],'X':[0,305], 'Label':'m_{vis} [GeV/c]','file':'OSSScorr_QCD_alt'},
              #{'name': 'ViennaTool/fakefactor/data_tt/FF_corr_QCD_MCsum_noGen_nonclosure_lepPt_alt.root','data':'nonclosure_fit', 'graph':'nonclosure_QCD','CMS':'Preliminary','Y':[0.5,1.5],'X':[40,120], 'Label':'p_{T} [GeV/c]','file':'nonclosure_pt_QCD_alt'}
     ]
     if(args.do_njetbinning == 1):
          files_tt.extend([
               {'name': 'ViennaTool/fakefactor/data_tt/FF_corr_QCD_MCsum_noGen_nonclosure_0jet.root','data':'nonclosure_fit', 'graph':'nonclosure_QCD','CMS':preliminary,'Y':[0.5,1.5],'X':[0,450], 'Label':'m_{vis} (GeV)','file':'corr_QCD_nonclosure_0jet','plotLabel1':'#tau_{h}#tau_{h} QCD multijet','plotLabel2':'Nonclosure correction, 0jet'},
              {'name': 'ViennaTool/fakefactor/data_tt/FF_corr_QCD_MCsum_noGen_nonclosure_1jet.root','data':'nonclosure_fit', 'graph':'nonclosure_QCD','CMS':preliminary,'Y':[0.5,1.5],'X':[0,450], 'Label':'m_{vis} (GeV)','file':'corr_QCD_nonclosure_1jet','plotLabel1':'#tau_{h}#tau_{h} QCD multijet','plotLabel2':'Nonclosure correction, #geq 1jet'},
              {'name': 'ViennaTool/fakefactor/data_tt/FF_corr_QCD_MCsum_noGen_nonclosure_lepPt_0jet.root','data':'nonclosure_fit', 'graph':'nonclosure_QCD','CMS':preliminary,'Y':[0.5,1.5],'X':[40,250], 'Label':'p_{T} (GeV)','file':'corr_QCD_nonclosure_pt_0jet','plotLabel1':'#tau_{h}#tau_{h} QCD multijet','plotLabel2':'p_{T} correction, 0jet'},
              {'name': 'ViennaTool/fakefactor/data_tt/FF_corr_QCD_MCsum_noGen_nonclosure_lepPt_1jet.root','data':'nonclosure_fit', 'graph':'nonclosure_QCD','CMS':preliminary,'Y':[0.5,1.5],'X':[40,250], 'Label':'p_{T} (GeV)','file':'corr_QCD_nonclosure_pt_1jet','plotLabel1':'#tau_{h}#tau_{h} QCD multijet','plotLabel2':'p_{T} correction, #geq 1jet'},
              ])

     

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
          
          datapoints_graph = TGraphAsymmErrors(datapoints.GetNbinsX())
          for i in range(1,1+datapoints.GetNbinsX()):
               datapoints_graph.SetPoint(i, datapoints.GetBinCenter(i), datapoints.GetBinContent(i))
               datapoints_graph.SetPointEYhigh(i, datapoints.GetBinError(i))
               datapoints_graph.SetPointEYlow(i, datapoints.GetBinError(i))
               datapoints_graph.SetPointEXhigh(i, datapoints.GetBinCenter(i)-datapoints.GetBinLowEdge(i))
               datapoints_graph.SetPointEXlow(i, datapoints.GetBinLowEdge(i+1)-datapoints.GetBinCenter(i))

          datapoints_graph.RemovePoint(0)
          
          datapoints_graph.SetMarkerStyle(20)
          datapoints_graph.SetLineWidth(1)
          datapoints_graph.SetMarkerSize(1.5)


          legendGraph = R.TGraph();
          legendGraph.SetLineColor(R.kBlack)
          legendGraph.SetLineWidth(4)
          legendGraph.SetFillColor(R.kOrange-2)
          
          leg = R.TLegend(0.7,0.73,0.88,0.88);
          leg.SetShadowColor(10)
          leg.SetLineColor(10)
          leg.SetTextFont(42)
          leg.SetTextSize(0.035)
          leg.AddEntry(datapoints_graph,"Measured","EP")
          leg.AddEntry(legendGraph,"#splitline{Smoothed}{curve}","lf")
          
          cms1 = R.TLatex( 0.16, 0.915, "CMS" )
          cms2 = R.TLatex( 0.298, 0.915, el['CMS'] )
          cms2b = R.TLatex( 0.298, 0.915, el['CMS'].replace(preliminary,supplementary) )
          cms1.SetNDC();
          cms1.SetTextFont(62);
          cms1.SetTextSize(0.06);
          
          infoRight = R.TLatex( 0.68, 0.915, "59.74 fb^{-1} (13 TeV)" )
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
          datapoints_graph.Draw('e1p same')
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
          cms2.Draw()
          #cms2b.Draw()
          canvas.Print( 'ViennaTool/Images_EMB/data_{0}/'.format(channel)  + el['file'] + '_'+channel+'.png' )
          canvas.Print( 'ViennaTool/Images_EMB/data_{0}/'.format(channel)  + el['file'] + '_'+channel+'.pdf' )
	  canvas.SaveAs('ViennaTool/Images_EMB/data_{0}/'.format(channel)  + el['file'] + '_'+channel+'.C' )
          #canvas.Print( 'tt/' + el['file'] + '.root')




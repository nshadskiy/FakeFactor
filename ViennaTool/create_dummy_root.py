import ROOT

tfile = ROOT.TFile("/portal/ekpbms2/home/jbechtel/fakefactors/auto_v8/2018/tt/CMSSW_8_0_25/src/ViennaTool/dummy.root","RECREATE")
tfile.cd()

hist = ROOT.TH1D("njet_hist","njet_hist",51,-0.5,50.5)
for xbin in range(hist.GetNbinsX()):
    hist.SetBinContent(xbin,xbin-1)
    print hist.GetBinLowEdge(xbin)
    print hist.GetBinLowEdge(xbin+1)
    print "Content:"
    print hist.GetBinContent(xbin)


hist.Write()

tfile.Write()
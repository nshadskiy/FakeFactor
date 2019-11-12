CXX=g++  -std=c++11
INCDIR=.
ROOTINC=$(shell root-config --incdir)
ROOTLIB=$(shell root-config --libs)

all: NtupleClass.o SignalClass.o GlobalClass.o TNtupleAnalyzer.o TSelectionAnalyzer.o PlotterClass.o GaussianKernelSmoother.o FFCalculator.o CustomFit.o test fitFakeFactors Preselection Preselection_EMB Preselection_KIT SRHisto CRHisto steerFF convert_inputs calcCorrections

%.o: ViennaTool/%.C
	$(CXX) -I$(INCDIR) -I$(ROOTINC) $(ROOTLIB) -fpic -c $<

%.o: ViennaTool/src/%.cc
	$(CXX) -I$(INCDIR) -I$(ROOTINC) $(ROOTLIB) -fpic -c $<

test: ViennaTool/macros/test.C
	$(CXX) -I$(INCDIR) -I$(ROOTINC) $(ROOTLIB) -o $@ ../tmp/slc6_amd64_gcc530/src/HTTutilities/Jet2TauFakes/src/HTTutilitiesJet2TauFakes/libHTTutilitiesJet2TauFakes.so ViennaTool/macros/test.C

Preselection: ViennaTool/macros/Preselection.C
	$(CXX) -I$(INCDIR) -I$(ROOTINC) $(ROOTLIB) -o $@ NtupleClass.o TNtupleAnalyzer.o ViennaTool/macros/Preselection.C

Preselection_EMB: ViennaTool/macros/Preselection_EMB.C
	$(CXX) -I$(INCDIR) -I$(ROOTINC) $(ROOTLIB) -o $@ NtupleClass.o TNtupleAnalyzer.o ViennaTool/macros/Preselection_EMB.C

Preselection_KIT: ViennaTool/macros/Preselection_KIT.C
	$(CXX) -I$(INCDIR) -I$(ROOTINC) $(ROOTLIB) -o $@ NtupleClass.o TNtupleAnalyzer.o ViennaTool/macros/Preselection_KIT.C

SRHisto: ViennaTool/macros/SRHisto.C
	$(CXX) -I$(INCDIR) -I$(ROOTINC) $(ROOTLIB) -o $@ SignalClass.o GlobalClass.o PlotterClass.o TSelectionAnalyzer.o ViennaTool/macros/SRHisto.C

CRHisto: ViennaTool/macros/CRHisto.C
	$(CXX) -I$(INCDIR) -I$(ROOTINC) $(ROOTLIB) -o $@ SignalClass.o GlobalClass.o PlotterClass.o TSelectionAnalyzer.o ViennaTool/macros/CRHisto.C

steerFF: ViennaTool/macros/steerFF.C
	$(CXX) -I$(INCDIR) -I$(ROOTINC) $(ROOTLIB) -o $@ SignalClass.o GlobalClass.o PlotterClass.o ../tmp/slc6_amd64_gcc530/src/HTTutilities/Jet2TauFakes/src/HTTutilitiesJet2TauFakes/libHTTutilitiesJet2TauFakes.so ViennaTool/macros/steerFF.C

calcCorrections: ViennaTool/macros/calcCorrections.C
	$(CXX) -I$(INCDIR) -I$(ROOTINC) $(ROOTLIB) -o $@ SignalClass.o GlobalClass.o PlotterClass.o ../tmp/slc6_amd64_gcc530/src/HTTutilities/Jet2TauFakes/src/HTTutilitiesJet2TauFakes/libHTTutilitiesJet2TauFakes.so ViennaTool/macros/calcCorrections.C


convert_inputs: ViennaTool/macros/convert_inputs.C
	$(CXX) -I$(INCDIR) -I$(ROOTINC) $(ROOTLIB) -o $@ GaussianKernelSmoother.o ViennaTool/macros/convert_inputs.C

fitFakeFactors: ViennaTool/macros/fitFakeFactors.C
	$(CXX) -I$(INCDIR) -I$(ROOTINC) $(ROOTLIB) -o $@ CustomFit.o SignalClass.o GlobalClass.o PlotterClass.o ViennaTool/macros/fitFakeFactors.C

clean:
	rm *.o test Preselection Preselection_EMB SRHisto CRHisto convert_inputs ApplyFF fitFakeFactors calcCorrections







CXX=g++  -std=c++11
INCDIR=.
ROOTINC=$(shell root-config --incdir)
ROOTLIB=$(shell root-config --libs)

all: ViennaTool/test

#NtupleClass.o: NtupleClass.C
#	$(CXX) -I$(INCDIR) -I$(ROOTINC) $(ROOTLIB) -c NtupleClass.C

ViennaTool/test: ViennaTool/macros/test.C
	$(CXX) -I$(INCDIR) -I$(ROOTINC) $(ROOTLIB) -o $@ ../tmp/slc6_amd64_gcc493/src/HTTutilities/Jet2TauFakes/src/HTTutilitiesJet2TauFakes/libHTTutilitiesJet2TauFakes.so ViennaTool/macros/test.C 

clean:
	rm *.o ViennaTool/test


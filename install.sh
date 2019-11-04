cmsrel CMSSW_8_0_25  
cd CMSSW_8_0_25/src/; cmsenv  

git clone https://github.com/jandrejk/FakeFactor.git -b FF2016DeepTauID .
git clone https://github.com/CMS-HTT/Jet2TauFakes.git HTTutilities/Jet2TauFakes  
cd HTTutilities/Jet2TauFakes  
git checkout v0.2.1  
cd ../../  
scram b -j 8  
git init  
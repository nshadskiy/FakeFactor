# FakeFactor  

cmsrel CMSSW_8_0_25  
cd CMSSW_8_0_25/src/; cmsenv  
git clone https://github.com/CMS-HTT/Jet2TauFakes.git HTTutilities/Jet2TauFakes  
cd HTTutilities/Jet2TauFakes  
git checkout v0.2.1  
cd ../../  
scram b -j 8  
git init  

git clone https://github.com/fspreitzer/FakeFactor.git -b FF2017ML_Embedding  
cd FakeFactor   
mv * ..  
cd ..  
rm -rf FakeFactor  

cd ViennaTool/  
em Settings.h  
#const TString output_folder ="/afs/hephy.at/user/f/fspreitzer/public/Htautau/FakeRate/SM_ML/20180323";  
#const TString DC_folder     ="/afs/hephy.at/work/f/fspreitzer/cmssw/ff_test/CMSSW_8_0_25/src/ViennaTool/HTTutilities/Jet2TauFakes/data";  
#const TString user="fspreitzer";  
em steerAll.sh  
em BuildStructure.sh  
#user=fspreitzer  
#fftype=FakeFactor_SM_ML  



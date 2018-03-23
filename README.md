# FakeFactor

############################

cmsrel CMSSW_8_0_25

cd CMSSW_8_0_25/src/; cmsenv

git clone https://github.com/CMS-HTT/Jet2TauFakes.git HTTutilities/Jet2TauFakes

cd HTTutilities/Jet2TauFakes

git checkout v0.2.1

cd ../../

scram b

git init

git remote add origin git@github.com:jbrands/FakeFactor.git

git fetch

git pull origin FF2016ML

git checkout FF2016ML

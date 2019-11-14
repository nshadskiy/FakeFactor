# FakeFactor  

cmsrel CMSSW_8_0_25  
cd CMSSW_8_0_25/src/; cmsenv  

git clone https://github.com/jandrejk/FakeFactor.git -b FF2017DeepTauID . </br>
git clone https://github.com/CMS-HTT/Jet2TauFakes.git HTTutilities/Jet2TauFakes  
cd HTTutilities/Jet2TauFakes  
git checkout v0.2.1  
cd ../../  
scram b -j 8  
git init  



# Running the code 

cd ViennaTool/ 

sh steerAll.sh 

# Settings 

Settings.h and Globals.h store many user parameters

# Calculate Fractions for the FF

* The file `ViennaTool/createFractions/CutObject/config/default_cuts.json` defines the cuts for the application region (`-ANTIISO-`). Also other aliases like Trigger, Lepton vetoes are defined there.
* The file `ViennaTool/createFractions/Fractions/fractions_input.py` stores the paths to the Ntuples. Each entry gets a new era tag, e.g. `2016_KIT_emb`
* Inside `ViennaTool/createFractions/Fractions/Fractions.py` one can define the binning of the variable(s) w.r.t. which the fractions are computed.

## Running the fraction calculation

cd ViennaTool/createFractions/Fractions/Fractions.py

python Fractions.py -e ERA 

use the -v for plotting the fractions (this options skips the calculation) or use -p to compute and plot the fractions in one go.

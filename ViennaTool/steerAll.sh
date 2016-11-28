#!/bin/bash

echo "Compiling the framework"
sh BuildStructure.sh
cd ../
make -B
#./Preselection
#./SRHisto
#./CRHisto
./steerFF
./fitFakeFactors
./convert_inputs
#./ApplyFF
#cp ViennaTool/fakefactor/data_mt/FFestimate_mt.root ViennaTool/fakefactor/data_mt/FFestimate_wUncertainties_mt.root
#cp ViennaTool/fakefactor/data_mt/FFestimate_mvis.root ViennaTool/fakefactor/data_mt/FFestimate_wUncertainties_mvis.root
#cp ViennaTool/fakefactor/data_mt/FFestimate_pt.root ViennaTool/fakefactor/data_mt/FFestimate_wUncertainties_pt.root
#./ApplyUncertainties

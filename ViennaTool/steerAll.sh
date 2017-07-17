#!/bin/bash

channel=$(grep 'int CHAN' "Settings.h" | awk -F'[=;]' '{print $2}')

echo "Compiling the framework"
sh BuildStructure.sh
cd ../
make -B

#./Preselection
#./SRHisto
#./CRHisto
#./steerFF
#./fitFakeFactors
#./calcCorrections
python plotCorrections.py --channel $channel
#./convert_inputs
#./ApplyFF
#cp ViennaTool/fakefactor/data_mt/FFestimate_mt.root ViennaTool/fakefactor/data_mt/FFestimate_wUncertainties_mt.root
#cp ViennaTool/fakefactor/data_mt/FFestimate_mvis.root ViennaTool/fakefactor/data_mt/FFestimate_wUncertainties_mvis.root
#cp ViennaTool/fakefactor/data_mt/FFestimate_pt.root ViennaTool/fakefactor/data_mt/FFestimate_wUncertainties_pt.root
#./ApplyUncertainties

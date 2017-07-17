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
#python plotCorrections.py --channel $channel
./convert_inputs


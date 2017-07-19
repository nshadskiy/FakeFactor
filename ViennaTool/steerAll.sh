#!/bin/bash

channel=$(grep 'int CHAN' "Settings.h" | awk -F'[=;]' '{print $2}')
output=$(grep 'output_folder' "Settings.h" | awk -F'[=;]' '{print $2}' | tr -d '"')
echo $output

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
./convert_inputs
python cpTDHaftPublic.py --destination $output --channel $channel
python producePublicFakeFactors.py --input $output --channel $channel


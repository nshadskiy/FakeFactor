#!/bin/bash

channel=$(grep 'int CHAN' "Settings.h" | awk -F'[=;]' '{print $2}')
output=$(grep 'output_folder' "Settings.h" | awk -F'[=;]' '{print $2}' | tr -d '"')
analysis=$(grep 'analysis' "Settings.h" | awk -F'[=;]' '{print $2}' | tr -d '"')
echo $output

sed s/user=\"whoami\"/user=\"$USER\"/g Settings.h >/tmp/Settings.h
cp /tmp/Settings.h .
sed s/user=whoami/user=$USER/g BuildStructure.sh >/tmp/BuildStructure.sh
cp /tmp/BuildStructure.sh .
sed s/fftype=fftype/fftype=$analysis/g BuildStructure.sh >/tmp/BuildStructure.sh
cp /tmp/BuildStructure.sh .

echo "Compiling the framework"
sh BuildStructure.sh
cd ../
make -B

./Preselection
./SRHisto
./CRHisto
./steerFF
./fitFakeFactors
./calcCorrections
python plotCorrections.py --channel $channel
./convert_inputs
python cpTDHaftPublic.py --destination $output --channel $channel
python producePublicFakeFactors.py --input $output --channel $channel


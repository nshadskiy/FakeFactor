#!/bin/bash
# steerAll.sh   #to run all
# steerAll.sh 1 #skip preselection (any other argument works as well)

channel=$(grep 'int CHAN' "Settings.h" | awk -F'[=;]' '{print $2}')
embedding=$(grep '#define EMB' "Settings.h" | awk -F'[B]' '{print $2}')
output=$(grep 'output_folder' "Settings.h" | awk -F'[=;]' '{print $2}' | tr -d '"')
analysis=$(grep 'analysis' "Settings.h" | awk -F'[=;]' '{print $2}' | tr -d '"')
#dc_path=$(grep 'DC_folder' "Settings.h" | awk -F'[=;]' '{print $2}' | tr -d '"')
if [ "$channel" == " kEL" ];  then chan="et"; fi
if [ "$channel" == " kMU" ];  then chan="mt"; fi
if [ "$channel" == " kTAU" ]; then chan="tt"; fi
echo Channel: $chan
echo Output: $output
echo Embedding: $embedding
#echo $dc_path

sed s/user=\"whoami\"/user=\"$USER\"/g Settings.h >/tmp/Settings$USER.h
yes | mv /tmp/Settings$USER.h Settings.h
sed s/user=whoami/user=$USER/g BuildStructure.sh >/tmp/BuildStructure$USER.sh
yes | mv /tmp/BuildStructure$USER.sh BuildStructure.sh
sed s/fftype=fftype/fftype=$analysis/g BuildStructure.sh >/tmp/BuildStructure$USER.sh
yes | mv /tmp/BuildStructure$USER.sh BuildStructure.sh

ff_tocheck='ff_QCD_dm?_njet?_??.pdf ff_QCD_AI_dm?_njet?_??.pdf'
if [ "$channel" != " kTAU" ]; then ff_tocheck+=' ff_Wjets_dm?_njet?_??.pdf ff_Wjets_MC_dm?_njet?_??.pdf ff_TT_dm?_njet?_??.pdf'; fi

echo "Compiling the framework"
sh BuildStructure.sh
cd ../
make -B

if [ "${1}" == "" ]; then
    # ./Preselection
    # exit 0
    if [ $embedding == 0 ]; then 
        # ./SRHisto
        # exit 0 
        ./CRHisto
    fi
fi

exit 0

./steerFF
./fitFakeFactors

cd ViennaTool/Images/data_$chan
#gs -dSAFER -dBATCH -dNOPAUSE -q -sDEVICE=pdfwrite -sOutputFile=toCheck.pdf ff_QCD_dm?_njet?_??.pdf ff_QCD_AI_dm?_njet?_??.pdf ff_Wjets_dm?_njet?_??.pdf ff_Wjets_MC_dm?_njet?_??.pdf ff_TT_dm?_njet?_??.pdf
gs -dSAFER -dBATCH -dNOPAUSE -q -sDEVICE=pdfwrite -sOutputFile=toCheck.pdf $ff_tocheck
cd -

./calcCorrections
python plotCorrections.py --channel $channel

./convert_inputs

python cpTDHaftPublic.py --destination $output --channel $channel
python producePublicFakeFactors.py --input $output --channel $channel
#python cpPublicFFtoDC.py --source $output --destination $dc_path --channel $channel

rm $output/constant.root

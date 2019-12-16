#!/bin/bash
# steerAll.sh   #to run all
# steerAll.sh 1 #skip preselection (any other argument works as well)

# extract channel, whether to use embedding, output directory and analysis name

# this is a comment not a question
channel=$(grep 'int CHAN' "Settings.h" | awk -F'[=;]' '{print $2}')
embedding=$(grep '#define EMB' "Settings.h" | awk -F'[B]' '{print $2}')
output=$(grep 'output_folder' "Settings.h" | awk -F'[=;]' '{print $2}' | tr -d '"')
analysis=$(grep 'analysis' "Settings.h" | awk -F'[=;]' '{print $2}' | tr -d '"')
njetbinning=$(grep 'doNJetBinning' "Settings.h" | awk -F'[=;]' '{print $2}' )

do_presel=$1 # 0 or 1 (default)
ntuples=$2 # Use "KIT" to process KIT ntuples, otherwise Vienna is assumed

if [ -z "$do_presel" ]; then
    do_presel=1
fi


if [ "$channel" == " kEL" ];  then chan="et"; fi
if [ "$channel" == " kMU" ];  then chan="mt"; fi
if [ "$channel" == " kTAU" ]; then chan="tt"; fi

echo Channel: $chan
echo Output: $output
echo Embedding: $embedding
echo User: $USER	
echo Name: $analysis
echo doNjetBinning: $njetbinning
echo NTuples: $ntuples

sed s/fftype=.*/fftype=$analysis/g BuildStructure.sh >/tmp/BuildStructure$USER.sh
yes | mv /tmp/BuildStructure$USER.sh BuildStructure.sh


ff_tocheck='ff_QCD_dm?_njet?_??.pdf ff_QCD_AI_dm?_njet?_??.pdf'
if [ "$channel" != " kTAU" ]; then ff_tocheck+=' ff_Wjets_dm?_njet?_??.pdf ff_Wjets_MC_dm?_njet?_??.pdf ff_TT_dm?_njet?_??.pdf'; fi


sh BuildStructure.sh

cd ../
echo "Compiling the framework... "

make -B -j 4

for process in DY EMB Data VV TT WJets
do
./Preselection_KIT $process &
done
wait


./SRHisto &
./CRHisto &
wait

./steerFF

./fitFakeFactors
cd ViennaTool/Images_EMB/data_$chan
gs -dSAFER -dBATCH -dNOPAUSE -q -sDEVICE=pdfwrite -sOutputFile=toCheck.pdf $ff_tocheck
cd -

./calcCorrections
python plotCorrections.py --channel $channel  --doNjetBinning $njetbinning
./convert_inputs


python cpTDHaftPublic.py --destination $output --channel $channel --doNjetBinning $njetbinning
echo $output $channel $njetbinning
python producePublicFakeFactors.py --input $output --channel $channel --njetbinning $njetbinning

echo "------ END OF steerAll.sh ---------"

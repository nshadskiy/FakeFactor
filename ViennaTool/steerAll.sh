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
usePt_nonclosure=$(grep 'usePt_nonclosure_Wjets' "Settings.h" | awk -F'[=;]' '{print $2}' )

do_presel=$1 # 0 or 1 (default)
ntuples=$2 # Use "KIT" to process KIT ntuples, otherwise Vienna is assumed
saveWork=$3 # 0 or 1 whether plots / root files will be saved to /ceph/USER/analysis , i.e. where the preselection is found

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
echo savework: $saveWork

sed -i 's#fftype=.*#fftype='$analysis'#g' BuildStructure.sh
# sed s/fftype=.*/fftype=$analysis/g BuildStructure.sh >/tmp/BuildStructure$USER.sh
#yes | mv /tmp/BuildStructure$USER.sh BuildStructure.sh


f_tocheck='ff_QCD_dm?_njet?_??.pdf ff_QCD_AI_dm?_njet?_??.pdf'
if [ "$channel" != " kTAU" ]; then ff_tocheck+=' ff_Wjets_dm?_njet?_??.pdf ff_Wjets_MC_dm?_njet?_??.pdf ff_TT_dm?_njet?_??.pdf'; fi

read -p "Are the above settings ok? If so, press enter to continue"

sh BuildStructure.sh

cd ../
echo "Compiling the framework... "
	
make -B -j 4
if [ $do_presel == 1 ]; then
for process in DY EMB Data VV TT WJets
do
./Preselection_KIT $process &
done
wait
fi

for process in DY VV TT
do
cp -rs ${output}/preselection/${chan}/preselection_${process}_J_EMB.root  ${output}/preselection/${chan}/preselection_${process}_J.root
cp -rs ${output}/preselection/${chan}/preselection_${process}_L_EMB.root  ${output}/preselection/${chan}/preselection_${process}_L.root
done

#./SRHisto &
#./CRHisto &
#wait

#./steerFF
#./fitFakeFactors
#cd ViennaTool/Images_EMB/data_$chan
#gs -dSAFER -dBATCH -dNOPAUSE -q -sDEVICE=pdfwrite -sOutputFile=toCheck.pdf $ff_tocheck
#cd -

# ./calcCorrections
#python plotCorrections.py --channel $channel  --doNjetBinning $njetbinning --usePt_nonclosure_Wjets $usePt_nonclosure

./convert_inputs

rsync -vhrP ViennaTool/fakefactor/data_${chan}/FF* ${output}/${chan}/.
rsync -vhrP ViennaTool/sim/${chan}/* ${output}/${chan}/sim/.
rsync -vhrP ViennaTool/Images_EMB/data_${chan}/ff_* ${output}/${chan}/Images_EMB/.
rsync -vhrP ViennaTool/Images_EMB/data_${chan}/corr_* ${output}/${chan}/Images_EMB/.
rsync -vhrP ViennaTool/ff_2d/tt/incl/*  ${output}/${chan}/inclusive/pieces/.
rsync -vhrP ViennaTool/ff_2d/tt/incl/*  ${output}/${chan}/dummycat/pieces/.

python cpTDHaftPublic.py --destination $output --channel $channel --doNjetBinning $njetbinning

echo $output $channel $njetbinning
python producePublicFakeFactors.py --input $output --channel $channel --njetbinning $njetbinning

if [ $saveWork == 1 ] ; then
	echo "------- SAVE WORK ---------"
	cd ViennaTool
	if [ ! -d save_$analysis ]; then
		mkdir save_$analysis
	fi
	cp -r Images_EMB save_$analysis
	cp -r fakefactor save_$analysis
	cp -r ff_2d save_$analysis
	cp -r sim save_$analysis
	if [ -d /ceph/$USER/$analysis/save_$analysis ]; then
		rm -rf /ceph/$USER/$analysis/save_$analysis
	fi
	mv save_$analysis /ceph/$USER/$analysis
fi

echo "------ END OF steerAll.sh ---------"

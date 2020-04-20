source ~/747_init.sh
cd -

era=$1
channel=$2

python plot_sr.py --era $era -c $channel -v pt mvis mt mvis_AI  --emb
python plot_cr.py --era $era -c $channel -v lepPt lepPt_SS pt mvis mt mvis_SS  --emb

python plot_cr.py --era $era -c $channel -v lepPt mvis pt  --emb --plot-qcd


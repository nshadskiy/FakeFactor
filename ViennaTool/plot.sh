source /home/jbechtel/747_init.sh
cd -

channel=$1

python plot_sr.py --era 2016 -c $channel -v pt mvis mt mvis_AI  --emb
python plot_cr.py --era 2016 -c $channel -v pt mvis mt  --emb



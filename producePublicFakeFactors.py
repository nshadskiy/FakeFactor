import ROOT as R
import argparse
import subprocess as sp

if __name__ == '__main__':

	parser = argparse.ArgumentParser()
	parser.add_argument('--channel', dest = 'channel', help='Channel for producing public FFs: mt,et,tt', type=str, metavar = 'TAG', required = True)
	parser.add_argument('--input', dest = 'input', help='Input directory - full string', type=str, metavar = 'TAG', required = True)
	parser.add_argument('--njetbinning', dest = 'njetbinning', help='Use corrections binned in NJets or not', type=str, metavar = 'TAG', required = True)
	args = parser.parse_args()

	#create Histogram with X-Axis interval [0,1], filled with binwidth 0.01 according to function f(x)=x
	#those are needed for inputs of fractions calculated in the datacard producer
	h = R.TH1D('constant', 'Constant function y=x for fractions', 101, -0.005, 1.005)
	for i in range(101): 
		h.Fill(i/100.0, i/100.0)
	
	file = R.TFile.Open("{INDIR}/constant.root".format(INDIR=args.input), "recreate")
	# write constant function
	file.WriteObject(h, "constant")
	file.Close()

	channel = args.channel
	if(args.channel == "kMU"):
		channel = "mt"
	elif(args.channel == "kEL"):
		channel = "et"
	elif(args.channel == "kTAU"):
		channel = "tt"
	print "njetbinning %s"%(args.njetbinning)
	if( channel == "mt" or channel == "et"):
		log = open('copy.log', 'a')
		if( args.njetbinning ):
			p = sp.Popen(["python producePublicFakeFactors_mt_et.py --channel {0} --input {1}".format(channel,args.input)],shell=True)
		else: 
			p = sp.Popen(["python producePublicFakeFactors_mt_et_NJETBINNING.py --channel {0} --input {1}".format(channel,args.input)],shell=True)
		p.wait()
	if( channel == "tt"):
		if( args.njetbinning ):
			p = sp.Popen(["python producePublicFakeFactors_tt.py --channel {0} --input {1}".format(channel,args.input)],shell=True)
		else:
			p = sp.Popen(["python producePublicFakeFactors_tt_NJETBINNING.py --channel {0} --input {1}".format(channel,args.input)],shell=True)
		p.wait()


				 


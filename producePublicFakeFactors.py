import ROOT as R
import argparse
import subprocess as sp

if __name__ == '__main__':

     parser = argparse.ArgumentParser()
     parser.add_argument('--channel', dest = 'channel', help='Channel for producing public FFs: mt,et,tt', type=str, metavar = 'TAG', required = True)
     parser.add_argument('--input', dest = 'input', help='Input directory - full string', type=str, metavar = 'TAG', required = True)
     args = parser.parse_args()
    
     channel = args.channel
     if(args.channel == "kMU"):
          channel = "mt"
     elif(args.channel == "kEL"):
          channel = "et"
     elif(args.channel == "kTAU"):
          channel = "tt"

     if( channel == "mt" or channel == "et"):
          log = open('copy.log', 'a')
          p = sp.Popen(["python producePublicFakeFactors_mt_et.py --channel {0} --input {1}".format(channel,args.input)],shell=True)
          p.wait()
     if( channel == "tt"):
          p = sp.Popen(["python producePublicFakeFactors_tt.py --channel {0} --input {1}".format(channel,args.input)],shell=True)
          p.wait()


                     


from __future__ import print_function
import subprocess as sp
import shutil
import multiprocessing as mp
import numpy as np
import shlex
import argparse
import time
import os
import sys



#Copy FFinput to public tool
class CMCHandler():
    def __init__(self, source, dest, channel, categories, ttcategories):
        self.source 	= source
        self.dest   	= dest
        self.channel 	= channel
        self.cats   	= categories
        self.ttcats 	= ttcategories
                
    def copyFF(self):

        cmd_list = []
        channel = self.channel
        if os.path.exists(self.source + '/' + channel):
            if channel == 'tt':
		categories = self.ttcats
	    else: categories = self.cats
   	    #copy root files in top folder of channel
	    path = self.source + '/' + channel
	    files = [f for f in os.listdir(path) if os.path.isfile(path + '/' +f) and (f.endswith('.root') or f.endswith('.ROOT'))]
	    if len(files) > 0:
		cmd_list.append('cp {0} {1}'.format( path + '/' + files[0], self.dest + '/' + channel + '/' + files[0] ) )
	    #copy FF files for each category
	    for cat in self.cats:
		if os.path.exists(self.source + '/' + channel + '/' + cat):
		    path = self.source + '/' + channel + '/' + cat
		    files = [f for f in os.listdir(path) if os.path.isfile(path + '/' +f) and (f.endswith('.root') or f.endswith('.ROOT'))]
		    if len(files) > 0:
		        cmd_list.append('cp {0} {1}'.format( path + '/' + files[0], self.dest + '/' + channel + '/' + cat + '/' + files[0] ) )
        if(len(cmd_list)>=1):
            self.applyCmdMulti( cmd_list )

    def checkFolderStructure(self, recreate = False):

        if os.path.exists(self.dest) and recreate:
            print( '{0} will be created anew'.format(self.dest) )
            shutil.rmtree( self.dest )
            os.makedirs( self.dest )
            channel = self.channel
            if os.path.exists(self.source + '/' + channel):
	        if channel == 'tt':
	       	    categories = self.ttcats
	        else: categories = self.cats
	        for cat in cats:
	    	    if os.path.exists(self.source + '/' + channel + '/' + cat):
		        os.makedirs( self.dest+'/' + channel + '/' +cat)
        elif os.path.exists(self.dest) and not recreate:
            print( '{0} already exists'.format(self.dest) )
            channel = self.channel
            if os.path.exists(self.source + '/' + channel):
		if channel == 'tt':
		    categories = self.ttcats
		else: categories = self.cats
		for cat in self.cats:
		    if os.path.exists(self.source + '/' + channel + '/' + cat) and not os.path.exists(self.dest + '/' + channel + '/' + cat):
			os.makedirs( self.dest+'/' + channel + '/' +cat)
        elif not os.path.exists(self.dest):
            os.makedirs( self.dest )
            channel = self.channel
            if os.path.exists(self.source + '/' + channel):
		if channel == 'tt':
		    categories = self.ttcats
		else: categories = self.cats
		for cat in self.cats:
		    if os.path.exists(self.source + '/' + channel + '/' + cat) and not os.path.exists(self.dest + '/' + channel + '/' + cat):
			os.makedirs( self.dest+'/' + channel + '/' +cat)

    
    def exec_cmd(self,cmd, q):
        shlCmd = shlex.split(cmd)
            
        log = open('copy.log', 'a')
        p = sp.Popen(shlCmd,stdout = log, stderr = log, shell=False)

        p.wait()
        q.put(object)


    def applyCmdMulti(self,cmd_list, max_proc=4):
        count = 0
        done_queue = mp.Queue()
        nCmd = 50./float( len(cmd_list) )
        for i, cmd in enumerate(cmd_list):
            if i > max_proc:
                done_queue.get(block=True)
            proc = mp.Process(target=self.exec_cmd, args=(cmd, done_queue))
            proc.start()
            if i == len(cmd_list)-1:
                proc.join()

            count += nCmd
            print('\r[{0}>{1}]  ( {2}/{3} )'.format('='*int(count),' '*(50-int(count) ), i+1, len(cmd_list) ), end='')

        while done_queue.qsize() > 0:
            done_queue.get()
            time.sleep(1)



if __name__ == '__main__':

    parser = argparse.ArgumentParser()
    parser.add_argument('--source', dest = 'source', help='Public FFs', type=str, metavar = 'TAG', required = True)
    parser.add_argument('--channel', dest = 'channel', help='Channel to copy', type=str, metavar = 'TAG', required = True)
    parser.add_argument('--destination', dest = 'destination', help='Destination folder', type=str, metavar = 'TAG', required = True)
    parser.add_argument('-f', dest='force', help='Force overwrite', action='store_true')

    args = parser.parse_args()
    
    source = args.source
    dest = args.destination

    print("Source:",source)
    print("Destination:",dest)

    channel 	=args.channel
    if(args.channel=="kMU"):
        channel = "mt"
    elif(args.channel=="kEL"):
        channel = "et"
    elif(args.channel=="kTAU"):
        channel = "tt"
    categories	=['inclusive','dummycat']
    ttcategories=['inclusive','dummycat']
    
    ch = CMCHandler(source, dest, channel, categories, ttcategories)
    
    ch.checkFolderStructure(recreate = args.force)
    ch.copyFF()





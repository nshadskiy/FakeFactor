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
    def __init__(self, channel, source, dest, in_categories, categories, in_altcategories, altcategories, in_ttcategories, ttcategories, QCDWUncertainties, FF3D, altFF3D, ttFF3D, fracs, corrections, altcorrections, ttcorrections):
        self.channel = channel
        self.source = source
        self.dest = dest
        if(self.channel == "mt"):
            self.incats = in_categories
            self.inaltcats = in_altcategories
            self.cats = categories
            self.altcats = altcategories
            self.FF3D = FF3D
            self.altFF3D = altFF3D
            self.corrections = corrections
            self.altcorrections = altcorrections
        elif(self.channel == "et"):
            self.incats = in_categories
            self.inaltcats = in_altcategories
            self.cats = categories
            self.altcats = altcategories
            self.FF3D = FF3D
            self.altFF3D = altFF3D
            self.corrections = corrections
            self.altcorrections = altcorrections
        elif(self.channel == "tt"):
            self.incats = in_ttcategories
            self.inaltcats = in_ttaltcategories
            self.cats = ttcategories
            self.altcats = ttaltcategories
            self.FF3D = ttFF3D
            self.altFF3D = ttaltFF3D
            self.corrections = ttcorrections
            self.altcorrections = ttaltcorrections
        else:
            print("ERROR: No valid channel")
            sys.exit()
        self.QCDWUncertainties = QCDWUncertainties
        self.fracs = fracs
        

    def checkFolderStructure(self, recreate = False):

        if os.path.exists(self.dest) and recreate:
            print( '{0} will be created anew'.format(self.dest) )
            shutil.rmtree( self.dest )
            os.makedirs( self.dest )
            for cat in self.cats:
                os.makedirs( self.dest+cat+'/pieces')
            for cat in self.altcats:
                os.makedirs( self.dest+cat+'/pieces')
        elif os.path.exists(self.dest) and not recreate:
            print( '{0} already exists'.format(self.dest) )
            for cat in self.cats:
                if not os.path.exists( self.dest+cat+'/pieces'):
                    os.makedirs( self.dest+cat+'/pieces')
            for cat in self.altcats:
                if not os.path.exists( self.dest+cat+'/pieces'):
                    os.makedirs( self.dest+cat+'/pieces')
        elif not os.path.exists(self.dest):
            os.makedirs( self.dest )
            for cat in self.cats:
                os.makedirs( self.dest+cat+'/pieces')
            for cat in self.altcats:
                os.makedirs( self.dest+cat+'/pieces')

                
    def copyQCDWUncertainties(self):

        print('Copying uncertainties_QCD_W.root')
        cmd_list = []
        if os.path.exists( self.source+'incl/{0}'.format( self.QCDWUncertainties[0] ) ):
            cmd_list.append('cp {0}incl/{1} {2}'.format( self.source,self.QCDWUncertainties[0],self.dest ) )
        else:
            print('WARNING: {0}incl/{1} does not exist'.format( self.source,self.QCDWUncertainties[0] ) )
        if os.path.exists( self.source+'incl/{0}'.format( self.QCDWUncertainties[1] ) ):
            cmd_list.append('cp {0}incl/{1} {2}'.format( self.source,self.QCDWUncertainties[1],self.dest ) )
        else:
            print('WARNING: {0}incl/{1} does not exist'.format( self.source,self.QCDWUncertainties[1] ) )
        if(len(cmd_list)>=1):
            self.applyCmdMulti( cmd_list )

    def copyQCDWUncertainties_tt(self):

        print('Copying uncertainties_QCD_W.root')
        cmd_list = []
        for i,cat in enumerate(self.incats):
            if os.path.exists( self.source+'incl/{0}'.format( self.QCDWUncertainties[0] ) ):
                cmd_list.append('cp {0}incl/{1} {2}/{3}/pieces/'.format( self.source,self.QCDWUncertainties[0],self.dest,self.cats[i] ) )
            else:
                print('WARNING: {0}incl/{1} does not exist'.format( self.source,self.QCDWUncertainties[0] ) )
        for i,cat in enumerate(self.inaltcats):
            if os.path.exists( self.source+'incl/{0}'.format( self.QCDWUncertainties[1] ) ):
                cmd_list.append('cp {0}incl/{1} {2}/{3}/pieces/'.format( self.source,self.QCDWUncertainties[1],self.dest,self.altcats[i] ) )
            else:
                print('WARNING: {0}incl/{1} does not exist'.format( self.source,self.QCDWUncertainties[1] ) )

        if(len(cmd_list)>=1):
            self.applyCmdMulti( cmd_list )
            
    def copyFFinput(self):

        print('Copying FF input files')
        cmd_list = []
        for FFfile in self.FF3D:
            if os.path.exists( self.source+'incl/{0}'.format( FFfile ) ):
                for cat in self.cats:
                    cmd_list.append('cp {0}incl/{1} {2}/{3}/pieces/'.format( self.source,FFfile,self.dest,cat ) )
            else:
                print('WARNING: {0}incl/{1} does not exist'.format( self.source,FFfile ) )
        for FFfile in self.altFF3D:
            if os.path.exists( self.source+'incl/{0}'.format( FFfile ) ):
                for cat in self.altcats:
                    cmd_list.append('cp {0}incl/{1} {2}/{3}/pieces/'.format( self.source,FFfile,self.dest,cat ) )
            else:
                print('WARNING: {0}incl/{1} does not exist'.format( self.source,FFfile ) )


            
        if(len(cmd_list)>=1):
            self.applyCmdMulti( cmd_list )


    def copyFFfrac(self):

        print('Copying FF fractions')
        cmd_list = []

        for i,cat in enumerate(self.incats):
            for frac in self.fracs:
                if os.path.exists( self.source+'{0}/{1}'.format( cat,frac ) ):
                    cmd_list.append('cp {0}{1}/{2} {3}{4}/pieces/'.format( self.source,cat,frac,self.dest,self.cats[i] ) )
                else:
                    print('WARNING: {0}{1}/{2} does not exist'.format( self.source,cat,frac ) )
        for i,cat in enumerate(self.inaltcats):
            for frac in self.fracs:
                if os.path.exists( self.source+'{0}/{1}'.format( cat,frac ) ):
                    cmd_list.append('cp {0}{1}/{2} {3}{4}/pieces/'.format( self.source,cat,frac,self.dest,self.altcats[i] ) )
                else:
                    print('WARNING: {0}{1}/{2} does not exist'.format( self.source,cat,frac ) )
            

        if(len(cmd_list)>=1):
            self.applyCmdMulti( cmd_list )
        

    def copyFFcorrections(self):

        print('Copying FF correction files')
        cmd_list = []
        for corrfile in self.corrections:
            if os.path.exists( self.source+'incl/{0}'.format( corrfile ) ):
                for cat in self.cats:
                    cmd_list.append('cp {0}incl/{1} {2}/{3}/pieces/'.format( self.source,corrfile,self.dest,cat ) )
            else:
                print('WARNING: {0}incl/{1} does not exist'.format( self.source,corrfile ) )
        for corrfile in self.altcorrections:
            if os.path.exists( self.source+'incl/{0}'.format( corrfile ) ):
                for cat in self.altcats:
                    cmd_list.append('cp {0}incl/{1} {2}/{3}/pieces/'.format( self.source,corrfile,self.dest,cat ) )
            else:
                print('WARNING: {0}incl/{1} does not exist'.format( self.source,corrfile ) )


            
        if(len(cmd_list)>=1):
            self.applyCmdMulti( cmd_list )
            

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
    parser.add_argument('--channel', dest = 'channel', help='Channel to copy', type=str, metavar = 'TAG', required = True)
    parser.add_argument('--destination', dest = 'destination', help='Destination folder', type=str, metavar = 'TAG', required = True)
    parser.add_argument('-f', dest='force', help='Force overwrite', action='store_true')
    parser.add_argument('--doNjetBinning', dest = 'do_njetbinning', help='Defines if corrections are binned in 0jet/1jet', type=str, metavar = 'TAG', required = True)

    args = parser.parse_args()

    channel = args.channel
    if(args.channel=="kMU"):
        channel = "mt"
    elif(args.channel=="kEL"):
        channel = "et"
    elif(args.channel=="kTAU"):
        channel = "tt"

    
    source = 'ViennaTool/ff_2d/{0}/'.format( channel )
    dest_channel = channel
    dest = '{0}/{1}/'.format( args.destination, dest_channel )

    print("Source:",source)
    print("Destination:",dest_channel)

    in_categories=['incl','_dummycat']
    in_altcategories=[]
    in_ttcategories=['incl','_dummycat']
    in_ttaltcategories=[]
    categories=['inclusive','dummycat']
    altcategories=[]
    ttcategories=['inclusive','dummycat']
    ttaltcategories=[]
    QCDWUncertainties=['uncertainties_QCD_W.root','uncertainties_QCD_W_alt.root']
    FF3D=['FakeFactors_Data_QCD_3D.root','FakeFactors_Data_W_3D.root','FakeFactors_Data_TT_3D.root']
    ttFF3D=['FakeFactors_Data_QCD_3D.root']
    altFF3D=[]
    ttaltFF3D=[]
    fractions=['frac_qcd.root','frac_tt.root','frac_dy.root','frac_wjets.root']
    corrections=['Correction_Data_QCD_MuIso.root','Correction_Data_QCD_MVis.root','Correction_Data_QCD_OSSS.root','Correction_Data_W_MVis.root','Correction_Data_W_lepPt.root','Correction_MC_W_MT.root','Correction_MC_TT_MVis.root','uncertainties_TT.root']
    if(args.do_njetbinning == 1):
        corrections.extend(['Correction_Data_QCD_MuIso_0jet.root','Correction_Data_QCD_MuIso_1jet.root','Correction_Data_QCD_MVis_0jet.root','Correction_Data_QCD_MVis_1jet.root','Correction_Data_W_MVis_0jet.root','Correction_Data_W_MVis_1jet.root','Correction_MC_W_MT_0jet.root','Correction_MC_W_MT_1jet.root'])    
    altcorrections=[]
    ttcorrections=['Correction_Data_QCD_PT.root','Correction_Data_QCD_MVis.root','Correction_Data_QCD_OSSS.root']
    if(args.do_njetbinning == 1):
        ttcorrections.extend(['Correction_Data_QCD_PT_0jet.root','Correction_Data_QCD_PT_1jet.root','Correction_Data_QCD_MVis_0jet.root','Correction_Data_QCD_MVis_1jet.root'])    
    ttaltcorrections=[]
    #ttaltcorrections=['Correction_Data_QCD_PT_alt.root','Correction_Data_QCD_MVis_alt.root','Correction_Data_QCD_OSSS_alt.root']
    ch = CMCHandler(channel, source, dest, in_categories, categories, in_altcategories, altcategories, in_ttcategories, ttcategories, QCDWUncertainties, FF3D, altFF3D, ttFF3D, fractions, corrections, altcorrections, ttcorrections)
    ch.checkFolderStructure(recreate = args.force)
    if(channel=="tt"):
        ch.copyQCDWUncertainties_tt()
    else:
        ch.copyQCDWUncertainties()
    ch.copyFFinput()
    ch.copyFFfrac()
    ch.copyFFcorrections()

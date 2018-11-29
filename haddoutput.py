import os,sys,datetime,time
from ROOT import *
execfile("/uscms_data/d3/rsyarif/EOSSafeUtils.py")

start_time = time.time()

#IO directories must be full paths
input  = sys.argv[1]
output = sys.argv[2]
shift = sys.argv[3]

inputDir='/eos/uscms/store/user/lpcljm/'+input+'/'+shift
outputDir='/eos/uscms/store/user/lpcljm/'+output+'/'+shift

inDir=inputDir[10:]
outDir=outputDir[10:]

os.system('eos root://cmseos.fnal.gov/ mkdir -p '+outDir)

# signalList = [
# #     'TprimeTprime_M-1000_TuneCP5_13TeV-madgraph-pythia8',
#     'TprimeTprime_M-1100_TuneCP5_13TeV-madgraph-pythia8',
#     'TprimeTprime_M-1200_TuneCP5_13TeV-madgraph-pythia8',
#     'TprimeTprime_M-1300_TuneCP5_13TeV-madgraph-pythia8',
#     'TprimeTprime_M-1400_TuneCP5_13TeV-madgraph-pythia8',
#     'TprimeTprime_M-1500_TuneCP5_13TeV-madgraph-pythia8',
#     'TprimeTprime_M-1600_TuneCP5_13TeV-madgraph-pythia8',
#     'TprimeTprime_M-1700_TuneCP5_13TeV-madgraph-pythia8',
#     'TprimeTprime_M-1800_TuneCP5_13TeV-madgraph-pythia8',
#     ]
# 
# signalOutList = ['BWBW','TZBW','THBW','TZTH','TZTZ','THTH']
# 
# for sample in signalList:
#     for outlabel in signalOutList:
# 
#         rootfiles = EOSlist_root_files(inputDir+'/'+sample+'_'+outlabel)
# #        print 'N root files in',sample,'=',len(rootfiles)
# #         haddcommand = 'hadd root://cmseos.fnal.gov/'+outDir+'/'+sample+'_'+outlabel+'_hadd.root '
#         haddcommand = 'hadd -f root://cmseos.fnal.gov/'+outDir+'/'+sample+'_'+outlabel+'_hadd.root '
# 
#         print '##########'*15
#         print 'HADDING:', sample,'_',outlabel
#         print '##########'*15
# 
#         for file in rootfiles:
# 
#             haddcommand+=' root://cmseos.fnal.gov/'+inDir+'/'+sample+'_'+outlabel+'/'+file
# 
#         os.system(haddcommand)
# #        print haddcommand
# 

# signalList = [
#     'BprimeBprime_M-1000_TuneCP5_13TeV-madgraph-pythia8',
#     'BprimeBprime_M-1100_TuneCP5_13TeV-madgraph-pythia8',
#     'BprimeBprime_M-1200_TuneCP5_13TeV-madgraph-pythia8',
#     'BprimeBprime_M-1300_TuneCP5_13TeV-madgraph-pythia8',
#     'BprimeBprime_M-1400_TuneCP5_13TeV-madgraph-pythia8',
#     'BprimeBprime_M-1500_TuneCP5_13TeV-madgraph-pythia8',
#     'BprimeBprime_M-1600_TuneCP5_13TeV-madgraph-pythia8',
#     'BprimeBprime_M-1700_TuneCP5_13TeV-madgraph-pythia8',
#     'BprimeBprime_M-1800_TuneCP5_13TeV-madgraph-pythia8',
#     ]
# 
# signalOutList = ['TWTW','BZTW','BHTW','BZBH','BZBZ','BHBH']
# 
# for sample in signalList:
#     for outlabel in signalOutList:
# 
#         rootfiles = EOSlist_root_files(inputDir+'/'+sample+'_'+outlabel)
# #        print 'N root files in',sample,'=',len(rootfiles)
#         haddcommand = 'hadd root://cmseos.fnal.gov/'+outDir+'/'+sample+'_'+outlabel+'_hadd.root '
# 
#         print '##########'*15
#         print 'HADDING:', sample,'_',outlabel
#         print '##########'*15
# 
#         for file in rootfiles:
# 
#             haddcommand+=' root://cmseos.fnal.gov/'+inDir+'/'+sample+'_'+outlabel+'/'+file
# 
#         os.system(haddcommand)
# #        print haddcommand


dirList = [
	#### As requested by Cristina Botta (ARC B2G-17-011).
# 	'TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8',
# 	'ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8',
# 	'TTZToLL_M-1to10_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',

# 	'WZTo3LNu_13TeV-powheg-pythia8',
# 	'ZZTo4L_13TeV_powheg_pythia8',
# 	'WWW_4F_TuneCP5_13TeV-amcatnlo-pythia8',
# 	'WWZ_4F_TuneCP5_13TeV-amcatnlo-pythia8',
# 	'WZZ_TuneCP5_13TeV-amcatnlo-pythia8',
# 	'ZZZ_TuneCP5_13TeV-amcatnlo-pythia8',
# 	'TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8',
# 	'TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8',
# 	'WW_TuneCP5_13TeV-pythia8',	
	
    ]

if shift == 'nominal':
# 	dirList.append('EGamma_RunA')
# 	dirList.append('EGamma_RunC')
# 	dirList.append('EGamma_RunD')
# 	dirList.append('DoubleMuon_RunA')
# 	dirList.append('DoubleMuon_RunB')
# 	dirList.append('DoubleMuon_RunC')
# 	dirList.append('DoubleMuon_RunD')
	dirList.append('EGamma_RunB_26Sep2018')
	dirList.append('EGamma_RunB')
	dirList.append('MuonEG_RunA')
	dirList.append('MuonEG_RunB')
	dirList.append('MuonEG_RunC')
	dirList.append('MuonEG_RunD')

for sample in dirList:

    rootfiles = EOSlist_root_files(inputDir+'/'+sample)
#    print 'N root files in',sample,'=',len(rootfiles)
    haddcommand = 'hadd -f root://cmseos.fnal.gov/'+outDir+'/'+sample+'_hadd.root '

    print '##########'*15
    print 'HADDING:', sample
    print '##########'*15

    nFilesPerHadd = 1000
#     nFilesPerHadd = 500

    if len(rootfiles) < nFilesPerHadd:
        haddcommand = 'hadd -f root://cmseos.fnal.gov/'+outDir+'/'+sample+'_hadd.root '
        for file in rootfiles:
            haddcommand+=' root://cmseos.fnal.gov/'+inDir+'/'+sample+'/'+file
        os.system(haddcommand)
    else:
        for i in range(int(len(rootfiles)/nFilesPerHadd)):
            haddcommand = 'hadd -f root://cmseos.fnal.gov/'+outDir+'/'+sample+'_'+str(i+1)+'_hadd.root '
            begin=i*nFilesPerHadd
            end=begin+nFilesPerHadd
            if len(rootfiles) - end < nFilesPerHadd: end=len(rootfiles)
            for j in range(begin,end):
                haddcommand+=' root://cmseos.fnal.gov/'+inDir+'/'+sample+'/'+rootfiles[j]
            os.system(haddcommand)
            #        print haddcommand
#
# # not needed yet in 80X, waiting for high mass samples to finish
# sample = 'TT_TuneCUETP8M2T4_13TeV-powheg-pythia8'
# TTOutList = ['Mtt0to700','Mtt700to1000','Mtt1000toInf']
#
# for outlabel in TTOutList:
#
#     rootfiles = EOSlist_root_files(inputDir+'/'+sample+'_'+outlabel)
# #    print 'N root files in',sample,'=',len(rootfiles)
#     haddcommand = 'hadd root://cmseos.fnal.gov/'+outDir+'/'+sample+'_'+outlabel+'_hadd.root '
#
#     print '##########'*15
#     print 'HADDING:', sample,'_',outlabel
#     print '##########'*15
#
#     for file in rootfiles:
#
#         haddcommand+=' root://cmseos.fnal.gov/'+inDir+'/'+sample+'_'+outlabel+'/'+file
#
#     os.system(haddcommand)
#
# print("--- %s minutes ---" % (round(time.time() - start_time, 2)/60))




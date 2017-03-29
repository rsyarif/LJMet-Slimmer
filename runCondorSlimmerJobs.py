import os,shutil,datetime,time
import getpass
from ROOT import *
execfile("/uscms_data/d3/rsyarif/EOSSafeUtils.py")

start_time = time.time()

shift = sys.argv[1]

#IO directories must be full paths

relbase = '/uscms_data/d3/rsyarif/Fermilab2017/LJMet80xSlimmer/CMSSW_8_0_17/'

# inputDir='/eos/uscms/store/user/lpcljm/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_2017_2_24_rizki/'+shift+'/' #DY HTbinned is here
inputDir='/eos/uscms/store/user/lpcljm/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_saveLooseMC_2017_3_4_rizki/'+shift+'/' #ttbar
# inputDir='/eos/uscms/store/user/lpcljm/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_saveVeryLooseMC_2017_3_6_rizki/'+shift+'/'
# inputDir='/eos/uscms/store/user/lpcljm/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_saveLooseMC_2017_3_7_rizki/'+shift+'/' #new DYsamples
# inputDir='/eos/uscms/store/user/lpcljm/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_saveLooseMC_newTT_2017_3_21_rizki/'+shift+'/' #new binned ttbar samples
# inputDir='/eos/uscms/store/user/lpcljm/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_newRunH_2017_3_21_rizki/'+shift+'/'

# outputDir='/eos/uscms/store/user/lpcljm/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_2017_2_24_rizki_step1/'+shift+'/'
# outputDir='/eos/uscms/store/user/lpcljm/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_2017_2_24_rizki_PRv6_FRv22_step1/'+shift+'/'
# outputDir='/eos/uscms/store/user/lpcljm/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_2017_2_24_rizki_PRv6_FRv22_newMuTrkSF_step1/'+shift+'/'
# outputDir='/eos/uscms/store/user/lpcljm/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_2017_2_24_rizki_PRv6_FRv24_newMuTrkSF_step1/'+shift+'/'
# outputDir='/eos/uscms/store/user/lpcljm/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_saveLooseMC_2017_3_4_rizki_PRv6_FRv24_newMuTrkSF_step1/'+shift+'/'
# outputDir='/eos/uscms/store/user/lpcljm/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_saveLooseMC_2017_3_4_rizki_PRv6_FRv25ttbar_newMuTrkSF_step1/'+shift+'/'
# outputDir='/eos/uscms/store/user/lpcljm/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_saveLooseMC_2017_3_4_rizki_PRv6_FRv26ttbar_newMuTrkSF_step1/'+shift+'/'
# outputDir='/eos/uscms/store/user/lpcljm/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_2017_2_24_rizki_PRv6_FRv27_newMuTrkSF_step1/'+shift+'/'
# outputDir='/eos/uscms/store/user/lpcljm/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_saveLooseMC_2017_3_4_rizki_PRv6_FRv28ttbar_newMuTrkSF_step1/'+shift+'/'
# outputDir='/eos/uscms/store/user/lpcljm/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_2017_2_24_rizki_PRv6_FRv29CR1_newMuTrkSF_step1/'+shift+'/'
# outputDir='/eos/uscms/store/user/lpcljm/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_saveLooseMC_2017_3_4_rizki_PRv6_FRv28ttbar_newMuTrkSF_PromptCount_step1/'+shift+'/'
# outputDir='/eos/uscms/store/user/lpcljm/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_saveLooseMC_2017_3_4_rizki_PRv6_FRv28ttbar_newMuTrkSF_PromptCount_V2_step1/'+shift+'/'
# outputDir='/eos/uscms/store/user/lpcljm/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_saveLooseMC_2017_3_4_rizki_PRv6_FRv28ttbar_newMuTrkSF_PromptCount_V3_DEBUGGED_step1/'+shift+'/'
# outputDir='/eos/uscms/store/user/lpcljm/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_saveVeryLooseMC_2017_3_6_rizki_PRv6_FRv28ttbar_step1/'+shift+'/'
# outputDir='/eos/uscms/store/user/lpcljm/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_saveLooseMC_2017_3_4_rizki_PRv6_FRv28ttbar_newMuTrkSF_PromptCount_V4_DEBUGGED_step1/'+shift+'/'
# outputDir='/eos/uscms/store/user/lpcljm/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_saveLooseMC_2017_3_4_rizki_PRv6_FRv28ttbar_newMuTrkSF_PromptCount_V5_DEBUGGED_step1/'+shift+'/'
# outputDir='/eos/uscms/store/user/lpcljm/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_saveLooseMC_2017_3_4_rizki_PRv6_FRv28ttbar_newMuTrkSF_PromptCount_V6_DEBUGGED_step1/'+shift+'/'
# outputDir='/eos/uscms/store/user/lpcljm/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_saveLooseMC_2017_3_4_rizki_PRv6_FRv28ttbar_newMuTrkSF_PromptCount_V7_DEBUGGED_step1/'+shift+'/'
# outputDir='/eos/uscms/store/user/lpcljm/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_saveLooseMC_2017_3_4_rizki_PRv6_FRv28ttbar_newMuTrkSF_PromptCount_V8_DEBUGGED_step1/'+shift+'/'
# outputDir='/eos/uscms/store/user/lpcljm/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_2017_2_24_rizki_PRv9_FRv24_postPreapproval_step1/'+shift+'/'
# outputDir='/eos/uscms/store/user/lpcljm/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_saveLooseMC_2017_3_4_rizki_PRv6_FRv28ttbar_newMuTrkSF_PromptCount_V9_DEBUGGED_step1/'+shift+'/'
# outputDir='/eos/uscms/store/user/lpcljm/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_saveLooseMC_2017_3_7_rizki_PRv9_FRv24_postPreapproval_step1/'+shift+'/'
# outputDir='/eos/uscms/store/user/lpcljm/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_saveLooseMC_2017_3_4_rizki_PRv9_FRv24_postPreapprovalF_PromptCount_V9_extScan_step1/'+shift+'/' #type 'F' after postPreapproval
# outputDir='/eos/uscms/store/user/lpcljm/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_2017_2_24_rizki_PRv9_FRv29CR1_postPreapproval_step1/'+shift+'/'
# outputDir='/eos/uscms/store/user/lpcljm/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_2017_2_24_rizki_PRv9_FRv24_postPreapproval_step1/'+shift+'/'
# outputDir='/eos/uscms/store/user/lpcljm/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_2017_2_24_rizki_PRvElPRtest_FRv24_postPreapproval_step1/'+shift+'/'
# outputDir='/eos/uscms/store/user/lpcljm/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_2017_2_24_rizki_PRvMuPRtest_FRv24_postPreapproval_step1/'+shift+'/'
# outputDir='/eos/uscms/store/user/lpcljm/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_2017_2_24_rizki_PRv9_FRvMuEtatest_postPreapproval_step1/'+shift+'/'
# outputDir='/eos/uscms/store/user/lpcljm/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_saveLooseMC_2017_3_7_rizki_mcClosure_step1/'+shift+'/'
# outputDir='/eos/uscms/store/user/lpcljm/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_saveLooseMC_newTT_2017_3_21_rizki_mcClosure_step1/'+shift+'/'
# outputDir='/eos/uscms/store/user/lpcljm/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_newRunH_2017_3_21_rizki_PRv9_FRv24_step1/'+shift+'/'
# outputDir='/eos/uscms/store/user/lpcljm/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_newRunH_2017_3_21_rizki_PRv9_FRv30CR2_step1/'+shift+'/'
# outputDir='/eos/uscms/store/user/lpcljm/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_newRunH_2017_3_21_rizki_PRv9_FRv31CR1_step1/'+shift+'/'
# outputDir='/eos/uscms/store/user/lpcljm/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_newRunH_2017_3_21_rizki_PRvElPRtest_FRv30CR2_step1/'+shift+'/'
# outputDir='/eos/uscms/store/user/lpcljm/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_newRunH_2017_3_21_rizki_PRvMuPRtest_FRv30CR2_step1/'+shift+'/'
# outputDir='/eos/uscms/store/user/lpcljm/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_newRunH_2017_3_21_rizki_PRv9_FRvMuEtatest_step1/'+shift+'/'
outputDir='/eos/uscms/store/user/lpcljm/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_saveLooseMC_2017_3_4_rizki_PRv9_FRv24_postPreapprovalF_PromptCount_V9_extScan_step1/'+shift+'/' #type 'F' after postPreapproval

# condorDir='/uscms_data/d3/rsyarif/Fermilab2017/LJMet80xSlimmer/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_2017_2_24_rizki_step1/'+shift+'/'
# condorDir='/uscms_data/d3/rsyarif/Fermilab2017/LJMet80xSlimmer/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_2017_2_24_rizki_PRv6_FRv22_step1/'+shift+'/'
# condorDir='/uscms_data/d3/rsyarif/Fermilab2017/LJMet80xSlimmer/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_2017_2_24_rizki_PRv6_FRv22_newMuTrkSF_step1/'+shift+'/'
# condorDir='/uscms_data/d3/rsyarif/Fermilab2017/LJMet80xSlimmer/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_2017_2_24_rizki_PRv6_FRv24_newMuTrkSF_step1/'+shift+'/'
# condorDir='/uscms_data/d3/rsyarif/Fermilab2017/LJMet80xSlimmer/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_saveLooseMC_2017_3_4_rizki_PRv6_FRv24_newMuTrkSF_step1/'+shift+'/'
# condorDir='/uscms_data/d3/rsyarif/Fermilab2017/LJMet80xSlimmer/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_saveLooseMC_2017_3_4_rizki_PRv6_FRv25ttbar_newMuTrkSF_step1/'+shift+'/'
# condorDir='/uscms_data/d3/rsyarif/Fermilab2017/LJMet80xSlimmer/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_saveLooseMC_2017_3_4_rizki_PRv6_FRv26ttbar_newMuTrkSF_step1/'+shift+'/'
# condorDir='/uscms_data/d3/rsyarif/Fermilab2017/LJMet80xSlimmer/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_2017_2_24_rizki_PRv6_FRv27_newMuTrkSF_step1/'+shift+'/'
# condorDir='/uscms_data/d3/rsyarif/Fermilab2017/LJMet80xSlimmer/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_saveLooseMC_2017_3_4_rizki_PRv6_FRv28ttbar_newMuTrkSF_step1/'+shift+'/'
# condorDir='/uscms_data/d3/rsyarif/Fermilab2017/LJMet80xSlimmer/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_2017_2_24_rizki_PRv6_FRv29CR1_newMuTrkSF_step1/'+shift+'/'
# condorDir='/uscms_data/d3/rsyarif/Fermilab2017/LJMet80xSlimmer/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_saveLooseMC_2017_3_4_rizki_PRv6_FRv28ttbar_newMuTrkSF_PromptCount_step1/'+shift+'/'
# condorDir='/uscms_data/d3/rsyarif/Fermilab2017/LJMet80xSlimmer/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_saveLooseMC_2017_3_4_rizki_PRv6_FRv28ttbar_newMuTrkSF_PromptCount_V2_step1/'+shift+'/'
# condorDir='/uscms_data/d3/rsyarif/Fermilab2017/LJMet80xSlimmer/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_saveLooseMC_2017_3_4_rizki_PRv6_FRv28ttbar_newMuTrkSF_PromptCount_V3_DEBUGGED_step1/'+shift+'/'
# condorDir='/uscms_data/d3/rsyarif/Fermilab2017/LJMet80xSlimmer/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_saveVeryLooseMC_2017_3_6_rizki_PRv6_FRv28ttbar_step1/'+shift+'/'
# condorDir='/uscms_data/d3/rsyarif/Fermilab2017/LJMet80xSlimmer/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_saveLooseMC_2017_3_4_rizki_PRv6_FRv28ttbar_newMuTrkSF_PromptCount_V4_DEBUGGED_step1/'+shift+'/'
# condorDir='/uscms_data/d3/rsyarif/Fermilab2017/LJMet80xSlimmer/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_saveLooseMC_2017_3_4_rizki_PRv6_FRv28ttbar_newMuTrkSF_PromptCount_V5_DEBUGGED_step1/'+shift+'/'
# condorDir='/uscms_data/d3/rsyarif/Fermilab2017/LJMet80xSlimmer/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_saveLooseMC_2017_3_4_rizki_PRv6_FRv28ttbar_newMuTrkSF_PromptCount_V6_DEBUGGED_step1/'+shift+'/'
# condorDir='/uscms_data/d3/rsyarif/Fermilab2017/LJMet80xSlimmer/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_saveLooseMC_2017_3_4_rizki_PRv6_FRv28ttbar_newMuTrkSF_PromptCount_V7_DEBUGGED_step1/'+shift+'/'
# condorDir='/uscms_data/d3/rsyarif/Fermilab2017/LJMet80xSlimmer/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_saveLooseMC_2017_3_4_rizki_PRv6_FRv28ttbar_newMuTrkSF_PromptCount_V8_DEBUGGED_step1/'+shift+'/'
# condorDir='/uscms_data/d3/rsyarif/Fermilab2017/LJMet80xSlimmer/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_2017_2_24_rizki_PRv9_FRv24_postPreapproval_step1/'+shift+'/'
# condorDir='/uscms_data/d3/rsyarif/Fermilab2017/LJMet80xSlimmer/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_saveLooseMC_2017_3_4_rizki_PRv9_FRv24_newMuTrkSF_PromptCount_V9_DEBUGGED_step1/'+shift+'/' //this is the correct label
# condorDir='/uscms_data/d3/rsyarif/Fermilab2017/LJMet80xSlimmer/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_saveLooseMC_2017_3_7_rizki_PRv9_FRv24_postPreapproval_step1/'+shift+'/'
# condorDir='/uscms_data/d3/rsyarif/Fermilab2017/LJMet80xSlimmer/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_saveLooseMC_2017_3_4_rizki_PRv9_FRv24_postPreapprovalF_PromptCount_V9_extScan_step1/'+shift+'/'
# condorDir='/uscms_data/d3/rsyarif/Fermilab2017/LJMet80xSlimmer/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_2017_2_24_rizki_PRv9_FRv29CR1_postPreapproval_step1/'+shift+'/'
# condorDir='/uscms_data/d3/rsyarif/Fermilab2017/LJMet80xSlimmer/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_2017_2_24_rizki_PRv9_FRv24_postPreapproval_step1/'+shift+'/'
# condorDir='/uscms_data/d3/rsyarif/Fermilab2017/LJMet80xSlimmer/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_2017_2_24_rizki_PRvElPRtest_FRv24_postPreapproval_step1/'+shift+'/'
# condorDir='/uscms_data/d3/rsyarif/Fermilab2017/LJMet80xSlimmer/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_2017_2_24_rizki_PRvMuPRtest_FRv24_postPreapproval_step1/'+shift+'/'
# condorDir='/uscms_data/d3/rsyarif/Fermilab2017/LJMet80xSlimmer/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_2017_2_24_rizki_PRv9_FRvMuEtatest_postPreapproval_step1/'+shift+'/'
# condorDir='/uscms_data/d3/rsyarif/Fermilab2017/LJMet80xSlimmer/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_saveLooseMC_2017_3_7_rizki_mcClosure_step1/'+shift+'/'
# condorDir='/uscms_data/d3/rsyarif/Fermilab2017/LJMet80xSlimmer/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_saveLooseMC_newTT_2017_3_21_rizki_mcClosure_step1/'+shift+'/'
# condorDir='/uscms_data/d3/rsyarif/Fermilab2017/LJMet80xSlimmer/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_newRunH_2017_3_21_rizki_PRv9_FRv24_step1/'+shift+'/'
# condorDir='/uscms_data/d3/rsyarif/Fermilab2017/LJMet80xSlimmer/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_newRunH_2017_3_21_rizki_PRv9_FRv30CR2_step1/'+shift+'/'
# condorDir='/uscms_data/d3/rsyarif/Fermilab2017/LJMet80xSlimmer/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_newRunH_2017_3_21_rizki_PRv9_FRv31CR1_step1/'+shift+'/'
# condorDir='/uscms_data/d3/rsyarif/Fermilab2017/LJMet80xSlimmer/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_newRunH_2017_3_21_rizki_PRvElPRtest_FRv30CR2_step1/'+shift+'/'
# condorDir='/uscms_data/d3/rsyarif/Fermilab2017/LJMet80xSlimmer/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_newRunH_2017_3_21_rizki_PRvMuPRtest_FRv30CR2_step1/'+shift+'/'
# condorDir='/uscms_data/d3/rsyarif/Fermilab2017/LJMet80xSlimmer/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_newRunH_2017_3_21_rizki_PRv9_FRvMuEtatest_step1/'+shift+'/'
condorDir='/uscms_data/d3/rsyarif/Fermilab2017/LJMet80xSlimmer/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_saveLooseMC_2017_3_4_rizki_PRv9_FRv24_postPreapprovalF_PromptCount_V9_extScan_step1/'+shift+'/'

runDir=os.getcwd()
# Can change the file directory if needed
#if '' not in shift: runDirPost = ''
#else: runDirPost = shift+'Files'
runDirPost = ''
print 'Files from',runDirPost

gROOT.ProcessLine('.x compileStep1.C')

cTime=datetime.datetime.now()
date='%i_%i_%i_%i_%i_%i'%(cTime.year,cTime.month,cTime.day,cTime.hour,cTime.minute,cTime.second)

inDir=inputDir[10:]
outDir=outputDir[10:]

print 'Getting proxy'
proxyPath=os.popen('voms-proxy-info -path')
proxyPath=proxyPath.readline().strip()

print 'Starting submission'
count=0

# signalList = [
#     #'TprimeTprime_M-700_TuneCUETP8M1_13TeV-madgraph-pythia8',
#     'TprimeTprime_M-800_TuneCUETP8M1_13TeV-madgraph-pythia8',
#     'TprimeTprime_M-900_TuneCUETP8M1_13TeV-madgraph-pythia8',
#     'TprimeTprime_M-1000_TuneCUETP8M1_13TeV-madgraph-pythia8',
#     'TprimeTprime_M-1100_TuneCUETP8M1_13TeV-madgraph-pythia8',
#     'TprimeTprime_M-1200_TuneCUETP8M1_13TeV-madgraph-pythia8',
#     'TprimeTprime_M-1300_TuneCUETP8M1_13TeV-madgraph-pythia8',
#     'TprimeTprime_M-1400_TuneCUETP8M1_13TeV-madgraph-pythia8',
#     'TprimeTprime_M-1500_TuneCUETP8M1_13TeV-madgraph-pythia8',
#     'TprimeTprime_M-1600_TuneCUETP8M1_13TeV-madgraph-pythia8',
#     'TprimeTprime_M-1700_TuneCUETP8M1_13TeV-madgraph-pythia8',
#     'TprimeTprime_M-1800_TuneCUETP8M1_13TeV-madgraph-pythia8',
#     ]
# 
# signalOutList = ['BWBW','TZBW','THBW','TZTH','TZTZ','THTH']
# 
# for sample in signalList:
#     rootfiles = EOSlist_root_files(inputDir+sample)
#     relPath = sample        
#     for outlabel in signalOutList:
#         os.system('eos root://cmseos.fnal.gov/ mkdir -p '+outDir+sample+'_'+outlabel)
#         os.system('mkdir -p '+condorDir+sample+'_'+outlabel)
# 
#         for file in rootfiles:
#             #        print file
#             rawname = file[:-5]
#             count+=1
#             dict={'RUNDIR':runDir, 'POST':runDirPost, 'RELPATH':relPath, 'LABEL':outlabel, 'CONDORDIR':condorDir, 'INPUTDIR':inDir, 'FILENAME':rawname, 'PROXY':proxyPath, 'CMSSWBASE':relbase, 'OUTPUTDIR':outDir}
#             jdfName=condorDir+'/%(RELPATH)s_%(LABEL)s/%(FILENAME)s_%(LABEL)s.job'%dict
#             print jdfName
#             jdf=open(jdfName,'w')
#             jdf.write(
#                 """x509userproxy = %(PROXY)s
# universe = vanilla
# Executable = %(RUNDIR)s/makeStep1.sh
# Should_Transfer_Files = YES
# WhenToTransferOutput = ON_EXIT
# Transfer_Input_Files = %(RUNDIR)s/makeStep1.C, %(RUNDIR)s/%(POST)s/step1.cc, %(RUNDIR)s/%(POST)s/step1.h, %(RUNDIR)s/%(POST)s/step1_cc.d, %(RUNDIR)s/%(POST)s/step1_cc.so, %(RUNDIR)s/%(POST)s/fakerate_3lep_ptEta_rizki.h
# Output = %(FILENAME)s_%(LABEL)s.out
# Error = %(FILENAME)s_%(LABEL)s.err
# Log = %(FILENAME)s_%(LABEL)s.log
# Notification = Never
# Arguments = %(FILENAME)s.root %(FILENAME)s_%(LABEL)s.root %(INPUTDIR)s/%(RELPATH)s %(OUTPUTDIR)s/%(RELPATH)s_%(LABEL)s
# 
# Queue 1"""%dict)
#             jdf.close()
#             os.chdir('%s/%s_%s'%(condorDir,relPath,outlabel))
#             os.system('condor_submit %(FILENAME)s_%(LABEL)s.job'%dict)
#             os.system('sleep 0.5')                                
#             os.chdir('%s'%(runDir))
#             print count, "jobs submitted!!!"
# 
# #, %(RUNDIR)s/csc2015_Dec01.txt, %(RUNDIR)s/ecalscn1043093_Dec01.txt

# signalList = [
#     #'BprimeBprime_M-700_TuneCUETP8M1_13TeV-madgraph-pythia8',
# #     'BprimeBprime_M-800_TuneCUETP8M1_13TeV-madgraph-pythia8',
# #     'BprimeBprime_M-900_TuneCUETP8M1_13TeV-madgraph-pythia8',
# #     'BprimeBprime_M-1000_TuneCUETP8M1_13TeV-madgraph-pythia8',
# #     'BprimeBprime_M-1100_TuneCUETP8M1_13TeV-madgraph-pythia8',
# #     'BprimeBprime_M-1200_TuneCUETP8M1_13TeV-madgraph-pythia8',
# #     'BprimeBprime_M-1300_TuneCUETP8M1_13TeV-madgraph-pythia8',
# #     'BprimeBprime_M-1400_TuneCUETP8M1_13TeV-madgraph-pythia8',
# #     'BprimeBprime_M-1500_TuneCUETP8M1_13TeV-madgraph-pythia8',
# #     'BprimeBprime_M-1600_TuneCUETP8M1_13TeV-madgraph-pythia8',
# #     'BprimeBprime_M-1700_TuneCUETP8M1_13TeV-madgraph-pythia8',
# #     'BprimeBprime_M-1800_TuneCUETP8M1_13TeV-madgraph-pythia8',
#     ]
# 
# signalOutList = ['TWTW','BZTW','BHTW','BZBH','BZBZ','BHBH']
# 
# for sample in signalList:
#     rootfiles = EOSlist_root_files(inputDir+sample)
#     relPath = sample        
#     for outlabel in signalOutList:
#         os.system('eos root://cmseos.fnal.gov/ mkdir -p '+outDir+sample+'_'+outlabel)
#         os.system('mkdir -p '+condorDir+sample+'_'+outlabel)
# 
#         for file in rootfiles:
#             #        print file
#             rawname = file[:-5]
#             count+=1
#             dict={'RUNDIR':runDir, 'POST':runDirPost, 'RELPATH':relPath, 'LABEL':outlabel, 'CONDORDIR':condorDir, 'INPUTDIR':inDir, 'FILENAME':rawname, 'PROXY':proxyPath, 'CMSSWBASE':relbase, 'OUTPUTDIR':outDir}
#             jdfName=condorDir+'/%(RELPATH)s_%(LABEL)s/%(FILENAME)s_%(LABEL)s.job'%dict
#             print jdfName
#             jdf=open(jdfName,'w')
#             jdf.write(
#                 """x509userproxy = %(PROXY)s
# universe = vanilla
# Executable = %(RUNDIR)s/makeStep1.sh
# Should_Transfer_Files = YES
# WhenToTransferOutput = ON_EXIT
# Transfer_Input_Files = %(RUNDIR)s/makeStep1.C, %(RUNDIR)s/%(POST)s/step1.cc, %(RUNDIR)s/%(POST)s/step1.h, %(RUNDIR)s/%(POST)s/step1_cc.d, %(RUNDIR)s/%(POST)s/step1_cc.so, %(RUNDIR)s/%(POST)s/fakerate_3lep_ptEta_rizki.h
# Output = %(FILENAME)s_%(LABEL)s.out
# Error = %(FILENAME)s_%(LABEL)s.err
# Log = %(FILENAME)s_%(LABEL)s.log
# Notification = Never
# Arguments = %(FILENAME)s.root %(FILENAME)s_%(LABEL)s.root %(INPUTDIR)s/%(RELPATH)s %(OUTPUTDIR)s/%(RELPATH)s_%(LABEL)s
# 
# Queue 1"""%dict)
#             jdf.close()
#             os.chdir('%s/%s_%s'%(condorDir,relPath,outlabel))
#             os.system('condor_submit %(FILENAME)s_%(LABEL)s.job'%dict)
#             os.system('sleep 0.5')                                
#             os.chdir('%s'%(runDir))
#             print count, "jobs submitted!!!"
# 
# #, %(RUNDIR)s/csc2015_Dec01.txt, %(RUNDIR)s/ecalscn1043093_Dec01.txt

# dirList = [
# 
# 	'TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8',       
# 	'TTWJetsToQQ_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8',	  
# 	'TTZToQQ_TuneCUETP8M1_13TeV-amcatnlo-pythia8',			  
# 	'TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8',			  
# # 	'TT_TuneCUETP8M1_13TeV-powheg-pythia8',
# 	'TT_TuneCUETP8M2T4_13TeV-powheg-pythia8', # MOriondMC			  
# 	'TT_Mtt-1000toInf_TuneCUETP8M2T4_13TeV-powheg-pythia8',
# 	'TT_Mtt-700to1000_TuneCUETP8M2T4_13TeV-powheg-pythia8',


# # 
# # 	'ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1',	  
# # 	'ST_t-channel_top_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1',	  
# # 	'ST_t-channel_antitop_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1',	  
# # 	'ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1', 
# # 	'ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1',	  
# # 
# 	'DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8',
# # 	'DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
# 	'DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8',
# 	'DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
# 	'DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_combined',
# 	'DYJetsToLL_M-50_TuneCUETHS1_13TeV-madgraphMLM-herwigpp',

# 	'DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',   
# 	'DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',   
# 	'DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',   
# 	'DYJetsToLL_M-50_HT-600to800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',    
# 	'DYJetsToLL_M-50_HT-800to1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',   
# 	'DYJetsToLL_M-50_HT-1200to2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8', 
# 	'DYJetsToLL_M-50_HT-2500toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',  
# 
# 	'DYJetsToLL_Pt-50To100_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8', 
# 	'DYJetsToLL_Pt-100To250_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8', 
# 	'DYJetsToLL_Pt-250To400_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8', 
# 	'DYJetsToLL_Pt-400To650_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8', 
# 	'DYJetsToLL_Pt-650ToInf_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8', 
	
# # 
# 	'WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8',   
# # 	'WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',   
# # 	'WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',   
# # 	'WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8', 
# # 	'WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',   
# # 	'WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',   
# # 	'WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',   
# # 	'WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',  
# # 	'WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8', 
# # 
# 	'WW_TuneCUETP8M1_13TeV-pythia8',
# 	'WZ_TuneCUETP8M1_13TeV-pythia8',
# 	'ZZ_TuneCUETP8M1_13TeV-pythia8',
# # 	
# # 	#Additionally for multilepton:
# 	'WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8',
# 	'ZZTo4L_13TeV_powheg_pythia8',
# 	'WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-pythia8',
# 	'WWZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8',
# 	'WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8',
# 	'ZZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8',       
#       
#     ]

# if shift == 'nominal':
# 	dirList.append('DoubleEG_RRB')
# 	dirList.append('DoubleMuon_RRB')
# 	dirList.append('MuonEG_RRB')
# 	dirList.append('DoubleEG_RRC')
# 	dirList.append('DoubleMuon_RRC')
# 	dirList.append('MuonEG_RRC')
# 	dirList.append('DoubleEG_RRD')
# 	dirList.append('DoubleMuon_RRD')
# 	dirList.append('MuonEG_RRD')
# 	dirList.append('DoubleEG_RRE')
# 	dirList.append('DoubleMuon_RRE')
# 	dirList.append('MuonEG_RRE')
# 	dirList.append('DoubleEG_RRF')
# 	dirList.append('DoubleMuon_RRF')
# 	dirList.append('MuonEG_RRF')
# 	dirList.append('DoubleEG_RRG')
# 	dirList.append('DoubleMuon_RRG')
# 	dirList.append('MuonEG_RRG')
# 	dirList.append('DoubleEG_RRH')
# 	dirList.append('DoubleMuon_RRH')
# 	dirList.append('MuonEG_RRH')


# for sample in dirList:
#     os.system('eos root://cmseos.fnal.gov/ mkdir -p '+outDir+sample)
#     os.system('mkdir -p '+condorDir+sample)
#     relPath = sample
# 
#     rootfiles = EOSlist_root_files(inputDir+sample)
#     for file in rootfiles:
# #        print file
# 
#         rawfile = file[:-5]
#         count+=1
#         dict={'RUNDIR':runDir, 'POST':runDirPost, 'RELPATH':relPath, 'CONDORDIR':condorDir, 'INPUTDIR':inDir, 'FILENAME':rawfile, 'PROXY':proxyPath, 'CMSSWBASE':relbase, 'OUTPUTDIR':outDir}
#         jdfName=condorDir+'/%(RELPATH)s/%(FILENAME)s.job'%dict
#         print jdfName
#         jdf=open(jdfName,'w')
#         jdf.write(
#             """x509userproxy = %(PROXY)s
# universe = vanilla
# Executable = %(RUNDIR)s/makeStep1.sh
# Should_Transfer_Files = YES
# WhenToTransferOutput = ON_EXIT
# Transfer_Input_Files = %(RUNDIR)s/makeStep1.C, %(RUNDIR)s/%(POST)s/step1.cc, %(RUNDIR)s/%(POST)s/step1.h, %(RUNDIR)s/%(POST)s/step1_cc.d, %(RUNDIR)s/%(POST)s/step1_cc.so, %(RUNDIR)s/%(POST)s/fakerate_3lep_ptEta_rizki.h
# Output = %(FILENAME)s.out
# Error = %(FILENAME)s.err
# Log = %(FILENAME)s.log
# Notification = Never
# Arguments = %(FILENAME)s.root %(FILENAME)s.root %(INPUTDIR)s/%(RELPATH)s %(OUTPUTDIR)s/%(RELPATH)s
# 
# Queue 1"""%dict)
#         jdf.close()
#         os.chdir('%s/%s'%(condorDir,relPath))
#         os.system('condor_submit %(FILENAME)s.job'%dict)
#         os.system('sleep 0.5')                                
#         os.chdir('%s'%(runDir))
#         print count, "jobs submitted!!!"
# 
# #, %(RUNDIR)s/csc2015_Dec01.txt, %(RUNDIR)s/ecalscn1043093_Dec01.txt

sample = 'TT_TuneCUETP8M2T4_13TeV-powheg-pythia8'
TTOutList = ['Mtt0to700','Mtt700to1000','Mtt1000toInf']

rootfiles = EOSlist_root_files(inputDir+sample)
relPath = sample        
for outlabel in TTOutList:
    os.system('eos root://cmseos.fnal.gov/ mkdir -p '+outDir+sample+'_'+outlabel)
    os.system('mkdir -p '+condorDir+sample+'_'+outlabel)

    for file in rootfiles:
        #        print file
        rawname = file[:-5]
        count+=1
        dict={'RUNDIR':runDir, 'POST':runDirPost, 'RELPATH':relPath, 'LABEL':outlabel, 'CONDORDIR':condorDir, 'INPUTDIR':inDir, 'FILENAME':rawname, 'PROXY':proxyPath, 'CMSSWBASE':relbase, 'OUTPUTDIR':outDir}
        jdfName=condorDir+'/%(RELPATH)s_%(LABEL)s/%(FILENAME)s_%(LABEL)s.job'%dict
        print jdfName
        jdf=open(jdfName,'w')
        jdf.write(
            """x509userproxy = %(PROXY)s
universe = vanilla
Executable = %(RUNDIR)s/makeStep1.sh
Should_Transfer_Files = YES
WhenToTransferOutput = ON_EXIT
Transfer_Input_Files = %(RUNDIR)s/makeStep1.C, %(RUNDIR)s/%(POST)s/step1.cc, %(RUNDIR)s/%(POST)s/step1.h, %(RUNDIR)s/%(POST)s/step1_cc.d, %(RUNDIR)s/%(POST)s/step1_cc.so, %(RUNDIR)s/%(POST)s/fakerate_3lep_ptEta_rizki.h
Output = %(FILENAME)s_%(LABEL)s.out
Error = %(FILENAME)s_%(LABEL)s.err
Log = %(FILENAME)s_%(LABEL)s.log
Notification = Never
Arguments = %(FILENAME)s.root %(FILENAME)s_%(LABEL)s.root %(INPUTDIR)s/%(RELPATH)s %(OUTPUTDIR)s/%(RELPATH)s_%(LABEL)s

Queue 1"""%dict)
        jdf.close()
        os.chdir('%s/%s_%s'%(condorDir,relPath,outlabel))
        os.system('condor_submit %(FILENAME)s_%(LABEL)s.job'%dict)
        os.system('sleep 0.5')                                
        os.chdir('%s'%(runDir))
        print count, "jobs submitted!!!"

print("--- %s minutes ---" % (round(time.time() - start_time, 2)/60))




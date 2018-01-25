#!/bin/bash

######### Check FR,PR in fakerate_3lep_ptEta_rizki.h
######### Check input/outputs in runCondorSlimmerJobs.py
######### select correct step1.C below!

date

# source switchTo_LJMet80x_rizki_Full2016_28Feb2017.sh #default for data 2016 analysis

# source switchTo_LJMet80x_rizki_Full2016_6Mar2017_ttbarClosureV2.sh
# source switchTo_LJMet80x_rizki_Full2016_15Mar2017_mcClosure.sh
# source switchTo_LJMet80x_rizki_Full2016_18Apr2017_ttbarClosureV3.sh #use this for 1orMoreLeps -- Closure test
# source switchTo_LJMet80x_rizki_Full2016_ddbkg_30Apr2017_ttbarClosureV4.sh #use this for ddbkg ttbar (3leps or more)
# source switchTo_LJMet80x_rizki_Full2016_1orMoreLeps_10May2017_DYClosure.sh
source switchTo_LJMet80x_rizki_Full2016_7Dec2017_ttG.sh #specifically looking at conversion rates

echo "SUBMITTING nominal"

python -u runCondorSlimmerJobs.py nominal

sleep 5

# echo "SUBMITTING JECup"
#
# python -u runCondorSlimmerJobs.py JECup
#
# sleep 5
#
# echo "SUBMITTING JECdown"
#
# python -u runCondorSlimmerJobs.py JECdown
#
# sleep 5
#
# echo "SUBMITTING JERup"
#
# python -u runCondorSlimmerJobs.py JERup
#
# sleep 5
#
# echo "SUBMITTING JERdown"
#
# python -u runCondorSlimmerJobs.py JERdown
#
# sleep 5

echo "DONE"

date


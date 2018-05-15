#!/bin/bash


# input=LJMet80X_1lep_XCone_2018_1_18_rizki_step1
# input=LJMet80X_1lep_XCone_2018_1_26_rizki_step1 #just WJetsToLNu and TT_TuneCUETP8M2T4_v1_13TeV-powheg-pythia8
# input=LJMet80X_1lep_XCone_2018_1_29_rizki_step1 #just WJetsToLNu HT600-800

# postStr=hadds
# output=$input$postStr

# output=LJMet80X_1lep_XCone_2018_1_18_and_2018_1_26_rizki_step1hadds #and 2018_1_29
# output=LJMet80X_1lep_XCone_2018_1_18_and_2018_1_26_and_2018_1_29_rizki_step1hadds #and 2018_1_29 v2 updated TrifEffWeightRMA

### March27-2018 including maxMlep3XConeJets
input=LJMet80X_1lep_XCone_2018_1_18_rizki_step1_v2
# input=LJMet80X_1lep_XCone_2018_1_26_rizki_step1_v2 #just WJetsToLNu and TT_TuneCUETP8M2T4_v1_13TeV-powheg-pythia8
# input=LJMet80X_1lep_XCone_2018_1_29_rizki_step1_v2 #just WJetsToLNu HT600-800
output=LJMet80X_1lep_XCone_2018_1_18_and_2018_1_26_and_2018_1_29_rizki_step1_v2_hadds #and 2018_1_29 


echo "HADDING NOMINAL"

python -u haddoutput.py $input $output nominal

# echo "HADDING JECUP"
# 
# python -u haddoutput.py $input $output JECup
# 
# echo "HADDING JECDOWN"
# python -u haddoutput.py $input $output JECdown
# 
# echo "HADDING JERUP"
# 
# python -u haddoutput.py $input $output JERup
# 
# echo "HADDING JERDOWN"
# 
# python -u haddoutput.py $input $output JERdown

echo "DONE"

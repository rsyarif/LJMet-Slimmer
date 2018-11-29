#!/bin/bash

input=LJMet102x_3lepTT_2018datasets_2018_11_22_rizki_step1 

postStr=hadds
output=$input$postStr

echo "HADDING NOMINAL"
python -u haddoutput.py $input $output nominal

# echo "HADDING JECUP"
# python -u haddoutput.py $input $output JECup
#
# echo "HADDING JECDOWN"
# python -u haddoutput.py $input $output JECdown
#
# echo "HADDING JERUP"
# python -u haddoutput.py $input $output JERup
#
# echo "HADDING JERDOWN"
# python -u haddoutput.py $input $output JERdown

echo "DONE"


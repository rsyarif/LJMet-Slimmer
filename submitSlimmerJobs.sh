#!/bin/bash

date

source switchTo_LJMet80x_rizki_Full2016_20Jan2017.sh

echo "SUBMITTING nominal"

python -u runCondorSlimmerJobs.py nominal

sleep 5

echo "SUBMITTING JECup"

python -u runCondorSlimmerJobs.py JECup

sleep 5

echo "SUBMITTING JECdown"

python -u runCondorSlimmerJobs.py JECdown

sleep 5

echo "SUBMITTING JERup"

python -u runCondorSlimmerJobs.py JERup

sleep 5

echo "SUBMITTING JERdown"

python -u runCondorSlimmerJobs.py JERdown

sleep 5

echo "DONE"

date


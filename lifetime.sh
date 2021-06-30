#!/bin/bash
# Basic while loop
counter=2
np=4
P=10000
T=$1
while [ $counter -le 10 ]
do
    make S=$counter np=$np P=$P T=$T snake$counter.txt 
    wait
((counter++))
done
python3 dimension.py
echo All done

#!/bin/bash
# Basic while loop
counter=2
while [ $counter -le 5 ]
do
    make lifetime.txt S=$counter
    wait
((counter++))
done
echo All done

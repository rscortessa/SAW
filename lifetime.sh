#!/bin/bash
# Basic while loop
counter=2
while [ $counter -le 7 ]
do
    make lifetime.txt S=$counter
    wait
((counter++))
done
make lifetime.pdf
echo All done

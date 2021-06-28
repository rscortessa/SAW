 #!/bin/bash
# Basic while loop
counter=2
np=5
while [ $counter -le 10 ]
do
    make lifetime.txt S=$counter np=$5
    wait
((counter++))
done
make lifetime.pdf
echo All done

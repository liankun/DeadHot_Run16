#!/bin/bash

for i in $(seq 23 44);
  do
  echo "run $i"
  if [ -f $i/sum_sum.root ];
    then
    rm -f $i/high_deadhot.txt
    rm -f $i/low_deadhot.txt
#    mv $i/high_deadhot.txt $i/high_deadhot_3sigma_no_discrete.txt
#    mv $i/low_deadhot.txt $i/low_deadhot_3sigma_no_discrete.txt
    cp high_discrete.txt $i/high_deadhot.txt
    cp low_discrete.txt $i/low_deadhot.txt
    echo "$i/sum_sum.root exists and will make dead hot" 
    ./make_bad_ped.sh $i
    ./make_bad_rad_ped.sh $i
  fi
done

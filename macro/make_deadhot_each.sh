#!/bin/bash
for i in `ls -d 45*`;
  do
  echo "run $i"
  if [ -f $i/sum.root ];
    then
#    rm -f $i/high_deadhot.txt
#    rm -f $i/low_deadhot.txt
    mv $i/high_deadhot.txt $i/high_deadhot_bk2.txt
    mv $i/low_deadhot.txt $i/low_deadhot_bk2.txt
    echo "$i/sum.root exists and will make dead hot" 
    ./make_bad_ped.sh $i
    ./make_bad_rad_ped.sh $i
  fi
done

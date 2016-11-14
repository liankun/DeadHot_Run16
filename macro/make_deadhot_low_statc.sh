#!/bin/bash
runlist="
454794
454798
454799
454802
454808
454809
454810
454811
455206
455342
"
for i in ${runlist};
  do
  echo "run $i"
  if [ -f $i/sum.root ];
    then
    echo "$i/sum.root exists and will make dead hot" 
    cp $i/high_deadhot.txt $i/high_deadhot_MB.txt
    cp $i/low_deadhot.txt $i/low_deadhot_MB.txt
    rm -f $i/high_deadhot.txt
    rm -f $i/low_deadhot.txt
    ./make_bad_ped.sh $i
    ./make_bad_rad_ped.sh $i
  fi
done

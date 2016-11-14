#!/bin/bash
for i in `ls -d 45*`;
  do
  echo "run $i"
  if [ -f $i/sum.root ];
    then
    echo "$i/sum.root exists and will make dead hot repass"
    cp $i/high_deadhot.txt $i/high_deadhot_repass.txt
    cp $i/low_deadhot.txt $i/low_deadhot_repass.txt
    ./make_bad_ped_repass.sh $i
    ./make_bad_rad_ped_repass.sh $i
  fi
done

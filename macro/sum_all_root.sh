#! /bin/bash
for i in `ls -d 45*`;
  do
  echo $i
  Num=`ls $i/Run16Ana_MinBias_NoCMN_Sub-${i}*.root |wc -l`
  echo $Num
  rm -f $i/sum.root
  if [ $Num -gt 0 ] && [ ! -f $i/sum.root ];
    then
    echo "run merge for this directory"
    ./sum_root_hadd.sh ${i}
  fi
done

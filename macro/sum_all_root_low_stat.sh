#! /bin/bash
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
  echo $i
  Num=`ls $i/Run16Ana_MinBias_NoCMN_Sub-${i}*.root |wc -l`
  echo $Num
  cp $i/sum.root $i/sum_mb1.root
  rm -f $i/sum.root
  if [ $Num -gt 0 ] && [ ! -f $i/sum.root ];
    then
    echo "run merge for this directory"
    ./sum_root_hadd_low_stat.sh ${i}
  fi
done

#! /bin/bash
for i in `seq 5 8`;
  do
  echo $i
  mkdir work_2016_07_27/$i
  root -l -q -b chi2_test.C'('$i')'
  root -l -q -b draw_all_deadhot.C'('$i')'
done

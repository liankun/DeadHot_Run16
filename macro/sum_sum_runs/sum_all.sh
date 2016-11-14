#!/bin/bash
sumlist=""
for i in $(seq 0 43);
  do
#   echo $i
   sumlist="$sumlist $i/sum_sum.root"
done
#echo $sumlist
hadd all_runs.root $sumlist

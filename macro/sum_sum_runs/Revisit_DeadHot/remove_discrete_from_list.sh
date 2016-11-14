#!/bin/bash
for i in `cat high_discrete.txt`;
  do
#  echo $i
  sed s/$i// <high_real_deadhot_add_discrete.txt >out.txt
done

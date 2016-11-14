#!/bin/bash
for i in $(seq 0 43 );
  do
  echo $i
  root -l -q -b deadhot_diff.C'('$i')'
done

#!/bin/bash
for i in $(seq 0 43);
  do
    echo "run $i"
    root -l -q -b adc_in_group.C'('$i')'
done

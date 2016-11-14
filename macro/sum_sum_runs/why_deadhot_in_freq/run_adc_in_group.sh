#!/bin/bash
key=395
group_list="0 10"
#echo $group_list

for i in $group_list;
  do
  echo $i
  root -l -b -q adc_in_group.C'('$i','$key')'
done


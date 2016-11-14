#!/bin/bash
#high pedestal

runNumber=$1
pass=3
echo "run Number: $runNumber "
#type 1 pass (remove deadhot by row in one sensor)
for j in $(seq 1 $pass);
  do
   echo pass $j
   root -l -q -b deadhot.C'('${runNumber}')'
   root -l -q -b readitg.C'('${runNumber}')'
   high_ped="1 2 3 4"
   high_merge=""
   for i in $high_ped;
     do 
     high_merge=" $high_merge ${runNumber}/bad_high_itg$i.txt"
   done
   rm -f ${runNumber}/temp_deadhot.txt 
   cat $high_merge > ${runNumber}/temp_deadhot.txt
   sort -u -n ${runNumber}/temp_deadhot.txt > ${runNumber}/high_deadhot.txt
   rm -f ${runNumber}/temp_deadhot.txt
   low_ped="1 2 3 4"
   low_merge=""
   for i in $low_ped;
     do
      low_merge="$low_merge ${runNumber}/bad_low_itg$i.txt"
   done
   rm -f ${runNumber}/temp_deadhot.txt
   cat $low_merge > ${runNumber}/temp_deadhot.txt
   sort -u -n ${runNumber}/temp_deadhot.txt > ${runNumber}/low_deadhot.txt
   rm -f ${runNumber}/temp_deadhot.txt
done

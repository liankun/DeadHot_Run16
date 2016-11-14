#!/bin/bash
cut 44/high_deadhot.txt -d " " -f1 > out.txt
cat out.txt Ashley_deadhot/high_bad_ped_db_out.txt > out2.txt
sort -u -n out2.txt > high_deadhot_list.txt
cp high_deadhot_list.txt Ashley_deadhot/high_deadhot_list_group44.txt

cut 44/low_deadhot.txt -d " " -f1 > out.txt
cat out.txt Ashley_deadhot/low_bad_ped_db_out.txt > out2.txt
sort -u -n out2.txt > low_deadhot_list.txt
cp low_deadhot_list.txt Ashley_deadhot/low_deadhot_list_group44.txt

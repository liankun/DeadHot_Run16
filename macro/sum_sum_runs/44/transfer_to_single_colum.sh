#!/bin/bash
cut high_deadhot.txt -d " " -f1 > out.txt
cat out.txt ../Ashley_deadhot/high_bad_ped_db_out.txt > out2.txt
sort -u -n out2.txt > high_deadhot_list.txt

cut low_deadhot.txt -d " " -f1 > out.txt
cat out.txt ../Ashley_deadhot/low_bad_ped_db_out.txt > out2.txt
sort -u -n out2.txt > low_deadhot_list.txt

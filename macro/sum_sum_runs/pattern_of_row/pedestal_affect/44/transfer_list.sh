#!/bin/bash
cat bad_high_itg1.txt bad_high_itg2.txt bad_high_itg3.txt bad_high_itg4.txt > high_out.txt
cat bad_low_itg1.txt bad_low_itg2.txt bad_low_itg3.txt bad_low_itg4.txt > low_out.txt
cut high_out.txt -d " " -f1 > high_out2.txt
cut low_out.txt -d " " -f1 > low_out2.txt
sort -u -n high_out2.txt > high_deadhot_row_pattern.txt
sort -u -n low_out2.txt > low_deadhot_row_pattern.txt

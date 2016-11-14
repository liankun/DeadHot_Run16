#!/bin/bash
sort -n -u high_bad_list.txt > out.txt
cp out.txt high_bad_list.txt
sort -n -u low_bad_list.txt > out.txt
cp out.txt low_bad_list.txt

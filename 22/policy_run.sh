#!/bin/bash
POLICIES=("FIFO" "LRU" "OPT" "UNOPT" "RAND" "CLOCK")

for policy in "${POLICIES[@]}"
do
    for i in 1 2 3 4
    do
        ./paging_policy.py -c -f ./transform.txt -p "$policy" -C "$i" > "$policy"_"$i".txt
    done
    echo ""
done
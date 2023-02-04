#!/bin/bash

output="hybrid3_reverse.txt"
sort_name="hybrid_sort3"
distribution="r"

for ((i =0; i <= 24; i++)) do
    ./sort $sort_name $((2**i)) $distribution $output
    cat $output
done

mv $output avg_dists/



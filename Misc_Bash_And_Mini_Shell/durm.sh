#!/bin/bash

# if a trash bin doesn't exist, prompt and exit
if [ ! -d $TRASH ]; then
    echo "No memory to free."
    echo "There currently is no safe-trash directory."
    exit 1
fi

# get shell options and positional variables
set `du -bs $TRASH/`

# store arguments 
val=("$@")

# add up the total bytes inside of the TRASH folder
for((i=0;i<$#;i++,i++)); do
    prev=${val[i]}
    let current+=$prev
    echo "$i: ${val[i]}"
done

# subtract the last argument, which is the size of the TRASH folder
total=$(expr $current - 4096)

# prompt stdout with the result
echo "Running the trash program will recover $total bytes."

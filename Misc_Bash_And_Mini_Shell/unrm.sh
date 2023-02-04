#!/bin/bash

# store arguments to array
val=("$@")

# create variable for the command to be executed
com=$"mv -f "

# check if a safe bin exists.  If not, prompt and exit
if [ ! -d $TRASH ]; then
    echo "There is currently no safe trash bin."
    echo "You cannot unremove files that don't exist."
    exit 1
fi

# check to make sure the user typed something to remove
if [ $# -lt 1 ]; then
    echo "Please provide an argument."
    exit 1
else
    # loop and add any arguments to be moved
    for((i=0;i<$#;i++)); do
	    com="${com} $TRASH/${val[i]}"
    done
fi

# add the destination directory to the command
com="${com} `pwd`"

# execute the unremove
$com

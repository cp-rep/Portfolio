#!/bin/bash

# store all arguments to an array
val=("$@")

# the command variable to execute at the end
com="ls -lS"

# directory flag
flag=0

# a variable for storing any file-name arguments
arguments=""

# loop through all arguments
for ((i=0;i<$#;i++)); do
    # if an argument is an option, test if it's valid
    if [[ ${val[i]} == -* ]]; then
	# test for valid options
	if [[ ${val[i]} =~ ^-[^aAbBcCdDfFGhHIklLmnNopqQStTuUvwxXZ1]*$ ]]; then
	    echo "lss: invalid option -- ${val[i]}"
	    exit 1
	fi
    # check if an argument is a directory, if so set a flag to use later
    elif [[ -d ${val[i]} ]]; then
	flag=1
    fi
    # append any resulting argument
    arguments="${arguments} ${val[i]}"
done

# append the -d option to the command variable if a directory was found
if [[ $flag -eq 1 ]]; then
    com="${com} -d"
fi

# append the arguments and execute the command
$com $arguments

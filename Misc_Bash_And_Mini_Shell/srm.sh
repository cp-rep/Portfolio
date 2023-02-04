#!/bin/bash

# store arguments in array
val=("$@")

# create variable to use for executing command
mvCom="mv -in "
rmCom="rm -i "
flag=0

# if there are no arguments, let the user know and exit
if [ $# == 0 ]; then
    echo "Please include a file to safe remove."
    exit 1
fi

# if a trash doesn't exist, create it
if [ ! -d $TRASH ]; then
    mkdir $TRASH
fi

# loop through and add any files to safely remove
for((i=0;i<$#;i++)); do
    # if there are any options, prepare for a rm command
    if [[ ${val[i]} == -* ]]; then
	flag=1
	# if an option isn't recognized, notify and exit safely
	if [[ ${val[i]} =~ ^-[^fiIrRdv]*$ ]]; then
	    echo "Invalid option -- ${val[i]}"
	    exit 1
	# otherwise, add the option
	else
	    rmCom="${rmCom} ${val[i]}"
	fi
    # if it wasn't an option, it's a file. add to remove lists
    else
	# if a duplicate file name is already in the safety remove bin, prompt
	# the user and exit
	if [ -f $TRASH/${val[i]} ] && [ -f `pwd`/${val[i]} ]; then
	    echo "Duplicate file name ${val[i]} already exists in the safe-bin."
	    exit 1
	# if a file is already safely removed, prompt the user and exit
	elif [ -f $TRASH/${val[i]} ]; then
	    echo "File ${val[i]} is already in the safe-bin."
	    echo "Please use the trash program to permanently delete the file."
	    exit 1
	# else, add it to the list
	else
	    rmCom="${rmCom} ${val[i]}"	    
	    mvCom="${mvCom} ${val[i]}"
	fi
    fi
done

# if there were options, delete any file arguments
if [[ $flag -eq 1 ]]; then
    $rmCom
else
    # there weren't any options, safely remove file arguments
    $mvCom $TRASH
fi

#!/bin/bash

# if a trash bin doesn't exist, prompt and exit
if [ ! -d $TRASH ]; then
    echo "There is currently no safe trash bin."
    echo "You cannot list files that don't exist."
    exit 1
fi

# list it's contents
ls -l $TRASH

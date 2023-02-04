#!/bin/bash

# check if a safe bin exists.  If not, prompt and exist
if [ ! -d $TRASH ]; then
    echo "There is nothing to permanantly remove."
    echo "No directory exists at location \$TRASH."
    exit 1
else
    # the bin exists, force remove all of it's contents
    rm -rf $TRASH*
fi

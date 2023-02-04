#!/bin/bash

# get a random 16 character alphanumeric string 
randomFolderName=$(cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w 16 | head -n 1)
tempDirectory=/tmp/$randomFolderName

# sanity output the random generated string and the temp directory
#echo $randomFolderName
#echo $tempDirectory

# create a temporary directory with the string
mkdir $tempDirectory

# remove the "./" from the front of the command
tempName=$0
tempName=$(echo $tempName | sed 's/.\///')
tempName="$tempName".c

#compile it and move it to the new temporary directory
gcc $tempName
mv a.out $tempDirectory

# create a variable that will act as the execution file name to be called and append
# any arguments
executeFile="a.out $@"

# run the program with all supplied arguments
$tempDirectory/$executeFile

# remove the temporary folder and associated files
function cleanup()
{
    rm -rfv $tempDirectory
}

trap cleanup 0 # EXIT
trap cleanup 1 # HANGUP
trap cleanup 2 # INTERRUPT
trap cleanup 3 # QUIT
trap cleanup 15 # TERMINATE

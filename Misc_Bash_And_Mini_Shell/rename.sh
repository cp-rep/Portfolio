#!/bin/bash

# check if overwrite is enabled. set appropriate flag
if [ $1 == "-f" ]; then
    overwrite=1
    i=2
else
    overwrite=0
    i=1
fi

# get the sed command from the command line based on its position
#get the first character of the sed command to be used as the delimiter to change
if [ $overwrite == 1 ]; then
    sed_command=$2
    separator=${2:0:1};
else
    sed_command=$1
    separator=${1:0:1};
fi 

# get all command line arguments
args=("$@")

# rename the file
for((i=$i;i<$#;i++)); do
    new_sed=$(sed 's/'$separator'/\//g' <<<"$sed_command")
    
    # get the input variable and check if it is a full path to a directory
    var=${args[i]}

    # length of the current file name
    len=${#var}
    slash_flag=0
    isDirectory=0
    dir_file=""
    new_file=""
    out_file=""
    
    # find out if it's a directory
    m=`expr $len + 1`
    for((m=$m;$m>0;m--)); do
	j=`expr $m - 1`
	
	file_char=${var:$j:1};

	if [ "$file_char" == "/" ]; then
	    q=$j
	    isDirectory=1
	    for((j=$j+1;$j<$len;j++)); do
       		out_file+=${var:$j:1};
	    done
	    break;
	fi
    done

    if [ $isDirectory == 0 ]; then
	out_file=$var
    fi
	
    new_file=$(sed 's'$new_sed'' <<<"$out_file")
    echo New File: $new_file

    # if it is a directory append it, else move it
    if [ $isDirectory == 1 ]; then
	q=`expr $q + 1`
	echo Is in directory: Yes
	for((z=0;$z<$q;z++)); do
	    dir_file+=${var:$z:1}
	done
	
	echo Directory path: $dir_file

	# append the new file name to the path directory
	dir_file+=$new_file

	echo Directory path + new file name: $dir_file

	# check if the new directory/file name already exists
	if [ -f "$dir_file" ]; then
	    # if it exists and -f option, overwrite it	    
	    if [ $overwrite == 1 ]; then
		echo Overwriting old directory file: \"$dir_file\" with \"$var\"
		mv $var $dir_file
	    # notify output that the file exists but don't overwrite it		
	    else
		echo File \"$dir_file\" already exists.  Add -f option to overwrite file.
	    fi
	# the file doesnt exist. rename it	    
	else
	    echo \"$dir_file\" doesnt exist. Rename \"$var\" to \"$dir_file\"
	    mv $var $dir_file
	fi
    else
	echo Is in directory: No.
	# check if the file already exists
	if [ -f "$new_file" ]; then
	    # if it exists and -f option, overwrite it
	    if [ $overwrite == 1 ]; then
		echo Overwriting old non-directory file \"$new_file\" with \"$var\"
		mv $var $new_file
	    # notify output that the file exists but don't overwrite it
	    else
		echo File \"$new_file\" already exists.  Add -f option to overwrite file.
	    fi
	# the file doesnt exist. rename it
	else
	    echo File $new_file doesnt exist.  Move $var to $new_file
	    mv $var $new_file
	fi
    fi
done

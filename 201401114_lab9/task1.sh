#!/bin/bash

var=""
if [ "$1" == "$var" ]
then
	echo " ERROR: Require file" 1>&2	
elif [ ! -e $1 ]
then 
	echo "ERROR: $1 doesn't exist " 1>&2
elif [ -d $1 ]	#its a directory
then
	echo "size of directory is: "
	ls -s $1 | cut -d " " -f 2		
elif [ -f $1 ]	#its a file
then 	
	echo "size of file is: "
 	ls -l $1 | cut -d " " -f 5	
fi

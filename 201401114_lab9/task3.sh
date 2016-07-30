#!/bin/bash

size1=$1
size2=$(ls -l $2  2> /dev/null | cut -d " " -f 5 ) 
re='^-?[0-9]+([.][0-9]+)?$'

#if  ! [[ $size1 =~ $re ]]   
#then
#	echo "ERROR: Require a number for $size1" 1>&2
#elif [ $size1 -lt 0 ]
#then 
#	echo "ERROR: Require a positive number for -1" 1>&2	

if [ $# -ne 2 ]
then 
	echo "ERROR: Require path and size" 1>&2
	exit 2
elif  ! [[ $size1 =~ $re ]]
then
        echo "ERROR: Require a number for $size1" 1>&2
	exit 3
elif [ $size1 -lt 0 ]
then
        echo "ERROR: Require a positive number for -1" 1>&2
	exit 4
elif [ ! -e $2 ]
then
        echo "ERROR: File $2 doesn't exist " 1>&2
	exit 5
elif [ $size1 -lt $size2 ] || [ $size1 -eq $size2 ]
then
	echo "yes"
	exit 0
else
	echo "no"
	exit 1
fi


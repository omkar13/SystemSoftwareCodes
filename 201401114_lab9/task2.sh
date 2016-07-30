#!/bin/bash

for arg in $*
do
	echo -n "$arg "
	if [ ! -e $arg ]
	then
        	echo "File doesn't exist " 1>&2
	else
		ls -l $arg | cut -d " " -f 5
	fi
done

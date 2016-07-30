#!/bin/bash

#string
var=amit
if [ $1 = $var ] 
then 
	echo "string $1 equals $var"
fi

if [ $1  == $var ] ;  then echo "string $1 equals $var" ; fi
if [ $1 != $var ] ; then echo "string $1 does not equals $var" ; fi
if [ -z $1 ] ; then echo "string $1 is empty!"; fi
if [ -n $1 ] ; then echo "string $1 is not empty!"; fi 



a=1
if [ $a -eq $1 ] ; then echo "number $1 equals $a" ; fi
if [ $a -ne $1 ] ; then echo "number $1 does not equal $a" ; fi
if [ $a -gt $1 ] ; then echo "$a is greater than $1" ; fi
if [ $a -lt $1 ] ; then echo "$a is less than $1" ; fi

 

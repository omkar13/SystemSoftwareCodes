#!/bin/bash

#file/dir properties
if [ -d $1 ] ; then echo "$1 exists and is a directory!" ; fi
if [ -e $1 ] ; then echo "$1 exists!" ; fi
if [ -f $1 ] ; then echo "$1 exists and is not a directory!" ; fi
if [ -r $1 ] ; then echo "$1 exists and is readable!" ; fi
if [ -s $1 ] ; then echo "$1 exists and has size greater than zero!" ; fi
if [ -w $1 ] ; then echo "$1 exists and is writable!" ; fi
if [ -x $1 ] ; then echo "$1 exists and is executable!" ; fi


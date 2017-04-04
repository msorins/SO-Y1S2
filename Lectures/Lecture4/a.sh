#!/bin/bash

#Checks if the number of parameters is lower than 15, and then gives an error
if [ $# -lt 15 ]; then
	echo "Not enough parameters" >&2
	exit 1
fi

shift 2
K=0
while [ $K -lt 3 ]; do
	echo $0;
	if [ ! -d $1 ]; then
	   echo At $K: Not a directory >&2
	   exit 1
	elif [ ! -f $2 ]; then
           echo At $K: Not a file >&2
           exit 2
        elif ! echo $3 | grep -q "^[0-9]\+$"; then
           echo At $K Not an integer  >&2
           exit 3
        elif !  echo $4 | grep -q -i "^[a-z]\+$"; then
           echo At $K Not text >&2
           exit 4
        fi
	
	K = `expr $K + 1`
	shift 4
done


#These two are the same
# [ -f a.txt]
# test -f a.txt


#Then + does ls -la
#alias +='ls -la'

#Aliases
ln -s /usr/bin/gcc gecece

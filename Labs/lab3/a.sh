#!/bin/sh
#grep "^(\<[a-zA-Z]+\>)
sed  's/^\(\<\w+\>\).*\1$//' a.txt


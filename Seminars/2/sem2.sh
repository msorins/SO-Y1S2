#!/bin/sh
if test $# - ne 2; then
	echo "Please give a file"
	exit(1
fi
if test-r #1; then
	echo "please give a file"
	exit(0)
fi
if file $1 | grep -q text, then
	awk '{
	printf("%s, $1);
	printf("%s %s", $3, $2);
	for(i = 4; i<= NF; i++)
		printf("%s ", $i);
	printf("\n");
	}$1
else
	echo
	exit(3);
}

#!/bin/sh

LAST=6
PASS=true
for ((i=1;i<=$LAST;i++)); do
    ./hw4a $(cat arg"$i"a.txt) < in"$i"a.txt > out.txt
	echo out"$i"a.txt
    DIFF=$(diff out.txt out"$i"a.txt)
    if [ "$DIFF" != "" ]; then
       echo "4a: FAILED test $i!"
       PASS=false
       break
    fi
done
if [ $PASS = true ]; then
    echo "4a: PASSED all tests"
fi


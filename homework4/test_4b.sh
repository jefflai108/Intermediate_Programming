#!/bin/sh

LAST=6
PASS=true
for ((i=1;i<=$LAST;i++)); do
    ./hw4b $(cat arg"$i"b.txt) < in"$i"b.txt > out.txt
	echo out"$i"b.txt
    DIFF=$(diff out.txt out"$i"b.txt)
    if [ "$DIFF" != "" ]; then
       echo "4b: FAILED test $i!"
       PASS=false
       break
    fi
done
if [ $PASS = true ]; then
    echo "4b: PASSED all tests"
fi


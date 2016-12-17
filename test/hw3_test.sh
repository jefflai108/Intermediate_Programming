#!/bin/sh

LAST=5
PASS=true
for ((i=1;i<=$LAST;i++)); do
    ./hw3 catalog$i.txt < in$i.txt > out.txt
    DIFF=$(diff out.txt out$i.txt)
    if [ "$DIFF" != "" ]; then
		    echo "FAILED test $i!"
        PASS=false
        break
    fi
done
if [ PASS = true ]; then
    echo "PASSED all tests"
fi

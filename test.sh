#!/bin/sh

FILE=svm
if test ! -f "$FILE"; 
then
    echo "Compile the project before running tests."
    exit 1
fi

cd examples

FAILED=0
PASS=0

for i in *.svm;
do
    if [ "$1" = "rec" ]
    then
        echo "Recording $i"
        ../svm $i > $i.out
    else
        FILE=$i.out
        if test -f "$FILE"; 
        then
            echo "Running $i"
            run="$(../svm $i)"
            out="$(cat $i.out)"
            if [ "$run" = "$out" ]
            then
                echo "  PASS: $i"
                ((PASS=PASS+1))
            else
                echo "  FAIL: $i"
                ((FAILED=FAILED+1))
            fi
        else
            echo "Run './test.sh rec' before running the tests."
            exit 1
        fi
        
    fi
done

echo ""
echo "Results from $((PASS+FAILED)) tests:"
echo "Pass: $PASS"
echo "Failed: $FAILED"
echo ""

cd ..
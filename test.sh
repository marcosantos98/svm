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
NOT_RECORDED=0

for i in *.svm;
do
    if [ "$1" = "rec" ]
    then
        echo "Recording $i"
        ../svm $i > $i.out
    elif [ "$1" = "-or" ]
    then
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
            echo "  Not recorded: $i"
            ((NOT_RECORDED=NOT_RECORDED+1))
        fi
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
            echo "Run './test.sh rec' before running the tests or run './test.sh -or'."
            exit 1
        fi
        
    fi
done

echo ""
echo "Results from $((PASS+FAILED+NOT_RECORDED)) tests:"
echo "Pass: $PASS"
echo "Failed: $FAILED"
echo "Not recorded: $NOT_RECORDED"
echo ""

cd ..
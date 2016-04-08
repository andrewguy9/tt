#!/bin/bash

SIZE=$1
DATASET=$2

echo "awk trial:"
AWK_TEMP=$(mktemp)
time ./naive_awk.sh $SIZE < $DATASET > $AWK_TEMP

echo "tt trial:"
TT_TEMP=$(mktemp)
time ./tt_perf.out $SIZE < $DATASET > $TT_TEMP

./error.py $AWK_TEMP $TT_TEMP

rm -f $AWK_TEMP $TT_TEMP

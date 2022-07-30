#!/usr/bin/env bash

echo -e "Running tests for DNA program...\n"

TESTS="$(cat ./tests/tests.txt |
       sed 's/Run your program as //' |
       sed 's/python/python3/' |
       sed 's/\. Your program should output /,/' |
       sed 's/\.$//')"

echo "$TESTS" | while read -r line
do
    CMD=$(echo "$line" | sed 's/,.*//')
    TST_RSLT=$(echo "$line" | sed 's/.*,//')
    echo -e "Command: $CMD\nExpected result: $TST_RSLT"
    RSLT=$($CMD)
    echo -e "Actual result: $RSLT\n"
done

echo -e "Tests complete.\n"

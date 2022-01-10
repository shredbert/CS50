#!/usr/bin/env bash

# Get filename & execute style50 & check50 tests
if [[ ! "$1" ]]; then
    echo "Enter path!!!"
    exit 1
elif [[ "$2" ]]; then
    echo "Too many args!!!"
    exit 1
elif [[ ! -f "$1" ]]; then
    echo "Not a file!!!"
    exit 1
fi
style50 "$1"

checkPth="cs50/problems/2022/x"
dir="$(pwd)"
file="${1%.*}"
if [[ "$file" == "mario" ]]; then
    if [[ "$dir" == *"less"* ]]; then
        check50 "$checkPth"/"$file"/less
    else
        check50 "$checkPth"/"$file"/more
    fi
else
    check50 "$checkPth"/"$file"
fi


#!/usr/bin/bash
# Time the different sorting programs & print results to file
# Check if results file exists & remove if so
rslts="results.txt"
if [[ -e "$rslts" ]]; then
    echo -e "$rslts found!!!\n"
    echo "Removing $rslts..."
    rm "$rslts" &&\
        echo -e "$rslts removed\n"
    else 
        echo -e "$rslts not found!!!\n"
fi

# Create new results file
echo "Creating $rslts..."
touch "$rslts" &&\
    echo -e "$rslts created\n"

# Iterate through 3 sorting programs, time each data file with each, & print
# results to file
for s in sort*; do
    if [[ "$s" == "sort1" || "$s" == "sort2" || "$s" == "sort3" ]]; then
        echo "Timing $s...";
        for f in *.txt; do
            if [[ "$f" != "answers.txt" && "$f" != "results.txt" ]]; then
                echo "Timing program $s, data $f...";

                # echo "$f";
            fi
        done;
    fi
done;

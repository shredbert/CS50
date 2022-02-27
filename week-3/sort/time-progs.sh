#!/usr/bin/bash
# Time the different sorting programs & print results to file
# Check if results file exists & remove if so
rslts="results.txt"
if [[ -e "$rslts" ]]; then
    echo -e "$rslts found!!!\n"
    echo "Removing $rslts..."
    rm "$rslts" &&\
        echo -e "$rslts removed\n" ||\
        exit 1
    else 
        echo -e "$rslts not found!!!\n"
fi

# Create new results file
echo "Creating $rslts..."
touch "$rslts" &&\
    echo -e "$rslts created\n" ||\
    exit 1

# Iterate through 3 sorting programs, time each data file with each, & print
# results to file
echo -e "Timing sort programs in $rslts..."
for s in sort*; do
    if [[ "$s" == "sort1" || "$s" == "sort2" || "$s" == "sort3" ]]; then
        echo -e "**********Executing $s**********\n" >> "$rslts"
        data=("sorted5000" "sorted10000" "sorted50000" \
              "reversed5000" "reversed10000" "reversed50000" \
              "random5000" "random10000" "random50000")
        for n in ${data[@]}; do
            f="$n.txt"
            if [[ -e "$f" ]]; then
                echo "Time for $s -- $f:" >> "$rslts"
                /usr/bin/time -f "%E" -a -o "$rslts" ./"$s" "$f" > /dev/null
                echo -e "\n" >> "$rslts"
            fi
        done;
        # echo -e "\n" #>> "$rslts"
        echo -e "**********$s complete.**********\n" >> "$rslts"
    fi
done;
echo -e "Sort programs timed in $rslts"

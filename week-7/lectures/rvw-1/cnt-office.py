#!/usr/bin/env python3

import csv
import re


def main():
    count = 0

    with open("../favourites.csv", "r") as file:
        reader = csv.DictReader(file)

        for row in reader:
            title = row["title"].strip().upper()
            if re.search("THE.+OFFICE", title):
                count += 1

    print(f"The Office is favourited {count} times")


if __name__ == "__main__":
    main()

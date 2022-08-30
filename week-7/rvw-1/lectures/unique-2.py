#!/usr/bin/env python3

import csv

favourites = set()

with open("../favourites.csv", "r") as file:
    reader = csv.DictReader(file)

    for row in reader:
        title = row["title"].strip().upper()
        favourites.add(title)

for favourite in favourites:
    print(favourite)

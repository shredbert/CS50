#!/usr/bin/env python3

import csv

favourites = []

with open("../favourites.csv", "r") as file:
    reader = csv.DictReader(file)

    for row in reader:
        title = row["title"].strip().upper()
        if title not in favourites:
            favourites.append(title)

for favourite in favourites:
    print(favourite)

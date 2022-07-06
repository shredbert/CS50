#!/usr/bin/python3

import csv
import sys

houses = {
    "Gryffindor": 0,
    "Hufflepuff": 0,
    "Ravenclaw": 0,
    "Slytherin": 0
}

with open("../assets/houses.csv", "r") as file:
    reader = csv.reader(file)
    next(reader)
    for row in reader:
        # print(houses[row[1]])
        house = row[1]
        houses[house] += 1

for house in houses:
    count = houses[house]
    print(f"{house}: {count}")

sys.exit(0)

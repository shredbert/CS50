#!/usr/bin/python3

import sys
import csv
import cs50

name = cs50.get_string("Name: ")
num = cs50.get_string("Num: ")

with open("../assets/phonebook.csv", "a") as file:
    writer = csv.writer(file)
    writer.writerow([name, num])

sys.exit(0)

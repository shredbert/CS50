#!/usr/bin/python3

import cs50
import csv
import sys

file = open("../assets/phonebook.csv", "a")

name = cs50.get_string("Name: ")
num = cs50.get_string("Num: ")

writer = csv.writer(file)
writer.writerow([name, num])

file.close()
sys.exit(0)

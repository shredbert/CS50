#!/usr/bin/python3

import csv
import sys
import cs50

file = open("../assets/phonebook.csv", "a")

name = cs50.get_string("Enter name: ")
num = cs50.get_string("Enter num: ")

writer = csv.writer(file)
writer.writerow([name, num])

file.close()
sys.exit(0)

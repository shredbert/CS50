#!/usr/bin/python3

import sys

names = ["Bill", "Charlie", "Fred", "George", "Ginny", "Percy", "Ron"]
name = "Ron"

if name in names:
    print(f"{name} found!!!")
    sys.exit(0)

print(f"{name} not found...")
sys.exit(1)

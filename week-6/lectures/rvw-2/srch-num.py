#!/usr/bin/python3

import sys

numbers = [4, 6, 8, 2, 7, 5, 0]
n = 18

if n in numbers:
    print("Found!")
    sys.exit(0)

print("Not found!")
sys.exit(1)

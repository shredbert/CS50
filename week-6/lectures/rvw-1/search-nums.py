#!/usr/bin/python3

import sys

numbers = [4, 6, 8, 2, 7, 5, 0]
number = 0

if number in numbers:
    print(f"{number} found!!!")
    sys.exit(0)

print(f"{number} not found...")
sys.exit(1)

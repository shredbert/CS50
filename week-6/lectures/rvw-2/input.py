#!/usr/bin/python3

import sys

try:
    x = int(input("X: "))
    y = int(input("Y: "))
except ValueError:
    print("Bad val entered!")
    sys.exit(1)

print(f"{x} + {y} = {x + y}")
sys.exit(0)

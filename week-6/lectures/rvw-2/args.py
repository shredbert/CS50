#!/usr/bin/python3

import sys

if (len(sys.argv) < 2):
    print("Bad args!")
    sys.exit(1)

for arg in sys.argv[1:]:
    print(arg)

sys.exit(0)

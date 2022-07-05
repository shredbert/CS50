#!/usr/bin/python3

import sys, cs50

people = {
    "Carter": "+1-617-495-1000",
    "David": "+1-949-468-2750"
}

search = cs50.get_string("Search name: ")

if search in people:
    num = people[search]
    print(f"{search} found: {num}")
    sys.exit(0)

print(f"{search} not found...")
sys.exit(1)

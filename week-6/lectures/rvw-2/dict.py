#!/usr/bin/python3

import sys
import cs50

people = {
    "Carter": "+1-617-495-1000",
    "David": "+1-949-468-2750"
}

person = cs50.get_string("Enter name: ")

if person in people:
    print(f"{person} found! {people[person]}")
    sys.exit(0)

print(f"{person} not found...")
sys.exit(1)

#!/usr/bin/python3

import cs50

s = cs50.get_string("Do you agree? ").lower()

if s in ["y", "yes", "yarp"]:
    print("Agreed!")
elif s in ["n", "no", "narp"]:
    print("Disagreed!")
else:
    print("Dumb!")

exit(0)

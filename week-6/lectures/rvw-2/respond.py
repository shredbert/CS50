#!/usr/bin/python3

import sys
import cs50

text = cs50.get_string("Say something: ").lower()

if "hello" in text:
    print("Hey there!")
elif "how are you" in text:
    print("Good, yourself?")
elif "goodbye" in text:
    print("Goodbye!")
else:
    print("???")

sys.exit(0)

#!/usr/bin/python3

import cs50
import sys

text = cs50.get_string("Say something: ").lower()

if "hello" in text:
    print("Hello to you too!")
elif "how are you" in text:
    print("I am well, thanks!") 
elif "goodbye" in text:
    print("Goodbye to you too!")
else:
    print("Huh?")

sys.exit(0)

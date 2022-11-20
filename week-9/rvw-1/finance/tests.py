#!/usr/bin/env python3
from helpers import is_valid_password

print("Testing passwords...")

assert not is_valid_password("Test1!"), "Not enough characters failed"
assert not is_valid_password("test123!"), "No caps failed"
assert not is_valid_password("Testonetwothree!"), "No nums failed"
assert not is_valid_password("Test1234"), "No symbols failed"
assert not is_valid_password("Test 123!"), "Contains spaces (invalid char) failed"

print("Tests pass")

#!/usr/bin/env python3
from helpers import is_valid_password

assert is_valid_password("test") is False, "Not enough characters"
assert is_valid_password("test") is False, "No caps"
assert is_valid_password("test") is False, "No nums"
assert is_valid_password("test") is False, "No symbols"
assert is_valid_password("test") is False, "Contains spaces (invalid char)"

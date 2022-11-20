#!/usr/bin/env python3
from helpers import is_valid_password

print("Testing passwords...")

# assert is_valid_password("Test_12!"), "Valid short PW not accepted"
# assert is_valid_password("Test_12345!"), "Valid longer PW not accepted"
# assert is_valid_password("Test_1234578901234567890!#$%!"), "Valid longest PW not accepted"

assert not is_valid_password("Test1!"), "Invalid PW with not enough characters accepted"
assert not is_valid_password("test123!"), "Invalid PW with no caps accepted"
assert not is_valid_password("Testonetwothree!"), "Invalid PW with no nums accepted"
assert not is_valid_password("Test 123!"), "Invalid PW with spaces accepted"
assert not is_valid_password("Test1234"), "Invalid PW with no symbols accepted"

print("Tests pass")

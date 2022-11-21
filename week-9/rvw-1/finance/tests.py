#!/usr/bin/env python3
from helpers import is_valid_password

print("Testing passwords...")

assert is_valid_password("1Test_2!"), "Valid PW not accepted"
assert is_valid_password("Test_12!"), "Valid PW not accepted"
assert is_valid_password("!Test_1 2"), "Valid PW not accepted"
assert is_valid_password("Test 012!"), "Valid PW not accepted"
assert is_valid_password("Test_012345789!@#"), "Valid PW not accepted"

assert not is_valid_password("Test1!"), "Invalid PW with not enough characters accepted"
assert not is_valid_password("test123!"), "Invalid PW with no caps accepted"
assert not is_valid_password("Testonetwothree!"), "Invalid PW with no nums accepted"
assert not is_valid_password("Test1234"), "Invalid PW with no symbols accepted"
assert not is_valid_password("TEST1234!"), "Invalid PW with no lowers accepted"

# Accept all ascii symbols (30 total) -- `~!@#$%^&*()-_=+[{]}\|'",<.>/?
# assert is_valid_password("Test123`"), "Valid PW with symbols not accepted"
# assert is_valid_password("Test123~"), "Valid PW with symbols not accepted"
# assert is_valid_password("Test123!"), "Valid PW with symbols not accepted"
# assert is_valid_password("Test123@"), "Valid PW with symbols not accepted"
# assert is_valid_password("Test123#"), "Valid PW with symbols not accepted"
# assert is_valid_password("Test123$"), "Valid PW with symbols not accepted"
# assert is_valid_password("Test123%"), "Valid PW with symbols not accepted"
# assert is_valid_password("Test123^"), "Valid PW with symbols not accepted"
# assert is_valid_password("Test123&"), "Valid PW with symbols not accepted"
# assert is_valid_password("Test123*"), "Valid PW with symbols not accepted"
# assert is_valid_password("Test123("), "Valid PW with symbols not accepted"
# assert is_valid_password("Test123)"), "Valid PW with symbols not accepted"
# assert is_valid_password("Test123-"), "Valid PW with symbols not accepted"
# assert is_valid_password("Test123_"), "Valid PW with symbols not accepted"
# assert is_valid_password("Test123="), "Valid PW with symbols not accepted"
# assert is_valid_password("Test123+"), "Valid PW with symbols not accepted"
# assert is_valid_password("Test123["), "Valid PW with symbols not accepted"
# assert is_valid_password("Test123{"), "Valid PW with symbols not accepted"
# assert is_valid_password("Test123]"), "Valid PW with symbols not accepted"
# assert is_valid_password("Test123}"), "Valid PW with symbols not accepted"
# assert is_valid_password("Test123\\"), "Valid PW with symbols not accepted"
# assert is_valid_password("Test123|"), "Valid PW with symbols not accepted"
# assert is_valid_password("Test123'"), "Valid PW with symbols not accepted"
# assert is_valid_password("Test123\""), "Valid PW with symbols not accepted"
# assert is_valid_password("Test123,"), "Valid PW with symbols not accepted"
# assert is_valid_password("Test123<"), "Valid PW with symbols not accepted"
# assert is_valid_password("Test123."), "Valid PW with symbols not accepted"
# assert is_valid_password("Test123>"), "Valid PW with symbols not accepted"
# assert is_valid_password("Test123/"), "Valid PW with symbols not accepted"
# assert is_valid_password("Test123?"), "Valid PW with symbols not accepted"

print("Tests pass")

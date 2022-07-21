#!/usr/bin/env python3
# Print whether submitted credit card number is Visa, MasterCard, or Amex
import sys
from cs50 import get_string
import re


def main():
    # Amex = 15 digits, Visa = 13 or 16 digits, & MasterCard = 16 digits
    valid_lengths = [13, 15, 16]

    # Get string -- using regex lib to parse
    number = get_string("Number: ")

    # Store regex for validation
    rgx_only_nums = re.compile(r"^\d+$")
    match = rgx_only_nums.fullmatch(number)

    # Check only nums of valid length
    if (len(number) not in valid_lengths or not match):
        print("INVALID")
        sys.exit(1)

    type = get_card_type(number)
    valid = test_card_valid(number)
    if not valid or not type:
        print("INVALID")
        sys.exit(1)

    print(type)

def get_card_type(number):
    # Amex starts with 34 or 37 & is 15 digits
    rgx_amex = re.compile(r"^3[47]*")
    # amex_match = rgx_amex.match(number)
    amex_match = rgx_amex.match(number) and len(number) == 15

    # MasterCard starts with 51-55 & is 16 digits
    rgx_mc = re.compile(r"^5[1-5]*")
    mc_match = rgx_mc.match(number) and len(number) == 16

    # Visa starts with 4 & is either 13 or 16 digits
    rgx_visa = re.compile(r"^4*")
    visa_match = rgx_visa.match(number) and (len(number) == 13 or len(number) == 16)
    
    if amex_match:
        return "Amex"
    elif mc_match:
        return "MasterCard"
    elif visa_match:
        return "Visa"
    else:
        return ""


def test_card_valid(number):
    # TODO: Implement Luhn's algorithm

    # TODO: Start with 2nd last, multiply every other digit by 2 & add DIGITS
    # ONLY (i.e., if product has multiple digits, add those together)

    # TODO: Add the sum of all even digits

    # TODO: Test if % 10 == 0 -- if so, valid

    return True


if __name__ == "__main__":
    main()

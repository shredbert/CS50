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
    # TODO: Include valid lengths in regex?
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
    visa_match = (rgx_visa.match(number) and
                  (len(number) == 13 or len(number) == 16))

    if amex_match:
        return "Amex"
    elif mc_match:
        return "MasterCard"
    elif visa_match:
        return "Visa"
    # Return blank str if no match -- falsey
    else:
        return ""


def test_card_valid(number):
    # Implement Luhn's algorithm -- start with 2nd last, multiply every other
    # digit by 2, & add DIGITS ONLY (i.e., if product has multiple digits, add
    # those together)
    evens = []
    odds = []
    for i, n in enumerate(reversed(number)):
        # Adds all evens/odds from end to respective lists
        if (i + 1) % 2 == 0:
            evens.append(n)
        else:
            odds.append(n)

    # Add the sum of the digits within the products of the even digits
    # multiplied by 2
    evn_sum = sum_dbld_digits(evens)
    # Add the sum of all odd digits
    odd_sum = sum_digits(odds)
    # Test if total % 10 == 0 -- if so, valid
    return ((evn_sum + odd_sum) % 10) == 0


# Accept a list of strings containing numbers, multiply by 2, & return the sum
# of each number's digits
def sum_dbld_digits(nums):
    products = []

    for n in nums:
        # Throw error if can't cast to int
        try:
            products.append(int(n) * 2)
        except ValueError:
            print("Error parsing nums")
            sys.exit(1)

    # Need to sum each individual digit of each number
    product_digits = return_digits(products)

    return sum(product_digits)


# Accept a list of numbers & return a modified list with just the individual
# digits in each number
def return_digits(nums):
    digits = []
    # Max decimal place is tens
    start = 10
    for n in nums:
        i = start
        while i >= 1:
            digit = ((n % (i * 10)) - (n % i)) / i
            digits.append(digit)
            i /= 10
    return digits


# Accept a list of strings containing numbers & return the sum of those numbers
def sum_digits(nums):
    sum = 0
    for n in nums:
        # Throw error if can't parse list values to ints
        try:
            sum += int(n)
        except ValueError:
            print("Error parsing nums")
            sys.exit(1)
    return sum


if __name__ == "__main__":
    main()

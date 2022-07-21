#!/usr/bin/env python3
# Print whether submitted credit card number is Visa, MasterCard, or Amex
import sys
from cs50 import get_string
import re


def main():
    # Amex = 15 digits, Visa = 13 or 16 digits, & MasterCard = 16 digits
    valid_lengths = [13, 15, 16]

    # Store regex for use in conditional
    regex_only_nums = re.compile(r"*[0-9]*")
    print(regex_only_nums.search())

    # # Get string -- using regex lib to parse
    # number = get_string("Number: ")

    # if (len(number) not in valid_lengths or
    #         not regex_only_nums.search(number)):
    #     print("Invalid")
    #     sys.exit(1)


if __name__ == "__main__":
    main()

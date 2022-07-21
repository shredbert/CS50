#!/usr/bin/env python3
from cs50 import get_float


def main():
    # Input always max 2 decimals, no formatting
    while True:
        change = get_float("Change owed: ")
        # Must have value to accept
        if change > 0:
            break
    print_coins(change)


def print_coins(change):
    # Multiply by 100 so don't have to worry about rounding
    change *= 100
    coins = 0

    # Using // to truncate values automatically
    quarters = change // 25
    change -= quarters * 25
    coins += quarters

    dimes = change // 10
    change -= dimes * 10
    coins += dimes

    nickels = change // 5
    change -= nickels * 5
    coins += nickels

    pennies = change // 1
    change -= pennies * 1
    coins += pennies

    # Cast to int since guaranteed to be whole number
    print(int(coins))


if __name__ == "__main__":
    main()

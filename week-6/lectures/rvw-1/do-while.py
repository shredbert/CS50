#!/usr/bin/python3

import cs50


def main():
    height = get_height()
    for i in range(height):
        print("#")


def get_height():
    while True:
        n = cs50.get_int("Enter height: ")
        if (n > 0):
            break
    return n


main()

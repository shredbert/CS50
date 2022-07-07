#!/usr/bin/python3

import cs50


def main():
    height = get_height()
    for i in range(height):
        print("#")


def get_height():
    wnhile True:
        n = cs50.get_int("Enter # of rows: ")
        if n > 0:
            break
    return n


main()

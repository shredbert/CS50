#!/usr/bin/python3

import cs50


def main():
    height = get_height()
    for i in range(height):
        for j in range(height):
            print("#", end="")
        print()


def get_height():
    while True:
        n = cs50.get_int("Height: ")
        if n > 0:
            break
    return n


main()

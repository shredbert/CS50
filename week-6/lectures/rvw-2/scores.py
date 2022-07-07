#!/usr/bin/python3

import cs50
import sys


def main():
    scores = []
    for i in range(3):
        score = get_score()
        scores.append(score)
    avg = sum(scores) / len(scores)
    print(f"Avg: {avg}")
    sys.exit(0)


def get_score():
    while True:
        score = cs50.get_int("Score: ")
        if score > 0:
            break
    return score


main()

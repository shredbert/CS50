#!/usr/bin/env python3
from cs50 import get_string
import re


def main():
    # Get string of text from user for analysis
    text = get_string("Text: ")
    # TEST
    print(text)

    # TODO: Calculate num of letters (A-Z/a-z)
    letters = len(re.match(r"[A-Za-z]", text).groups)
    # TODO: Calculate num of words (chars separated by spaces)
    words = re.match(r"[A-Za-z0-9'] [A-Za-z0-9']", text)
    # TODO: Calculate num of sentences (.!?)
    sentences = re.match(r"[A-Za-z0-9'][.!?][A-Za-z0-9']", text)
    print(letters)

    # print(letters)
    # print(words)
    # print(sentences)

    # TODO: Use Coleman-Liau formula to calculate reading level of input text
    # 0.0588 * L - 0.296 * S - 15.8
    # L = avg letters per 100 words, S = avg sentences per 100 words

    # TODO: Print grade level
    # TODO: If 16+, print "16+" -- senior undergraduate reading level
    # TODO: If < 1, print "Before Grade 1"
    # TODO: Round result to whole num for output


if __name__ == "__main__":
    main()

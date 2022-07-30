#!/usr/bin/env python3
from cs50 import get_string
import re


def main():
    # Get string of text from user for analysis
    text = get_string("Text: ")

    # Calculate num of letters (A-Z/a-z)
    letters = len(re.findall(r"[A-Za-z]", text))

    # Calculate num of words (any sequence of chars separated by spaces on
    # either end)
    words = len(re.findall(r"\s*\S+\s*", text))

    # Calculate num of sentences (.!?)
    sentences = len(re.findall(r"(\w*)[.!?]", text))

    # Calculate avg letters per 100 words
    avg_letters = letters / words * 100

    # Calculate avg sentences per 100 words
    avg_sentences = sentences / words * 100

    # Use Coleman-Liau formula to calculate reading level of input text
    reading_level = 0.0588 * avg_letters - 0.296 * avg_sentences - 15.8

    # Print grade level
    # If < 1, print "Before Grade 1"
    if reading_level < 1:
        print("Before Grade 1")
    # If 16+, print "16+" -- senior undergraduate reading level
    elif reading_level >= 16:
        print("Grade 16+")
    # Else round result to whole num for output
    else:
        print(f"Grade {reading_level:.0f}")


if __name__ == "__main__":
    main()

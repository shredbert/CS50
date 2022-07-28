#!/usr/bin/env python3
from cs50 import get_string
import re


def main():
    # Get string of text from user for analysis
    text = get_string("Text: ")
    # TEST
    print(text)

    # Calculate num of letters (A-Z/a-z)
    letters = len(re.findall(r"[A-Za-z]", text))

    # Calculate num of words (any sequence of chars separated by spaces on
    # EITHER END)
    words = re.findall(r"\W", text)
    print(words)
    # words = len(re.findall(r"(\W+)", text))

    # Calculate num of sentences (.!?)
    sentences = len(re.findall(r"(\w*)[.!?]", text))

    # # TODO: Calculate avg letters per 100 words
    # avg_letters = letters / words * 100

    # # TODO: Calculate avg sentences per 100 words
    # avg_sentences = sentences / words * 100

    # # TODO: Use Coleman-Liau formula to calculate reading level of input text
    # reading_level = 0.0588 * avg_letters - 0.296 * avg_sentences - 15.8

    # # TODO: Print grade level
    # # TODO: If < 1, print "Before Grade 1"
    # if reading_level < 1:
    #     print("Before Grade 1")
    # # TODO: If 16+, print "16+" -- senior undergraduate reading level
    # elif reading_level >= 16:
    #     print("Grade 16+")
    # # TODO: Else round result to whole num for output
    # else:
    #     print(f"Grade {reading_level:.0f}")

    # # TEST
    # print(f"Letters: {letters}")
    # print(f"Words: {words}")
    # print(f"Sentences: {sentences}")
    # print(f"Avg letters / 100 words: {avg_letters}")
    # print(f"Avg sentences / 100 words: {avg_sentences}")
    # print()


if __name__ == "__main__":
    main()

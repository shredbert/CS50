#!/usr/bin/env python3

import csv


def main():
    title_counts = {}

    with open("../favourites.csv", "r") as file:
        reader = csv.DictReader(file)

        for row in reader:
            title = row["title"].strip().upper()
            if title not in title_counts:
                title_counts[title] = 0
            title_counts[title] += 1

    for title in sorted(title_counts, key=lambda title: title_counts[title],
                        reverse=True):
        print(f"{title}: {title_counts[title]}")


if __name__ == "__main__":
    main()

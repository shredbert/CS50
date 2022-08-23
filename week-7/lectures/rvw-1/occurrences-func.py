#!/usr/bin/env python3

import csv


def main():
    title_counts = {}

    def get_count(title):
        return title_counts[title]

    with open("../favourites.csv", "r") as file:
        reader = csv.DictReader(file)

        for row in reader:
            title = row["title"].strip().upper()
            if title not in title_counts:
                title_counts[title] = 0
            title_counts[title] += 1

    for title in sorted(title_counts, key=get_count, reverse=True):
        print(f"{title}: {title_counts[title]}")


if __name__ == "__main__":
    main()

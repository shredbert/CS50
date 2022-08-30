#!/usr/bin/env python3

import csv


def main():
    srch_ttl = input("Title to Search: ")
    count = 0

    with open("../favourites.csv", "r") as file:
        reader = csv.DictReader(file)

        for row in reader:
            fav_ttl = row["title"].strip().upper()
            if fav_ttl == srch_ttl.strip().upper():
                count += 1

    print(f"{srch_ttl} is favourited {count} times!!!")


if __name__ == "__main__":
    main()

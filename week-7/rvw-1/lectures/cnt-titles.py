#!/usr/bin/env python3

import cs50


def main():
    db = cs50.SQL("sqlite:///favourites.db")
    title = input("Title to search: ").strip()

    count = db.execute("SELECT COUNT(*) AS count FROM favourites WHERE title LIKE ?",
                       title)[0]["count"]

    print(f"{title} favourited {count} times")


if __name__ == "__main__":
    main()

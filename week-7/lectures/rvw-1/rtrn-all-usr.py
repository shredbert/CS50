#!/usr/bin/env python3

import cs50


def main():
    db = cs50.SQL("sqlite:///favourites.db")
    title = input("Title to list matches for: ").strip()

    titles = db.execute("SELECT title FROM favourites WHERE title LIKE ?",
                        title)

    for title in titles:
        print(title["title"])


if __name__ == "__main__":
    main()

#!/usr/bin/env python3

import csv
import cs50


def main():
    # Create new SQLite DB & connect
    open("favourites_new.db", "w").close()
    db = cs50.SQL("sqlite:///favourites_new.db")

    # Create tables
    db.execute("CREATE TABLE shows(id INTEGER, title TEXT NOT NULL, PRIMARY KEY(id))")
    db.execute("CREATE TABLE genres(show_id INTEGER, genre TEXT NOT NULL, FOREIGN KEY (show_id) REFERENCES shows (id))")

    # Load data
    with open("../favourites.csv", "r") as file:
        reader = csv.DictReader(file)

        for row in reader:
            title = row["title"].strip().upper()
            show_id = db.execute("INSERT INTO shows (title) VALUES (?)", title)

            for genre in row["genres"].split(", "):
                db.execute("INSERT INTO genres (show_id, genre) VALUES (?, ?)", show_id, genre)


if __name__ == "__main__":
    main()

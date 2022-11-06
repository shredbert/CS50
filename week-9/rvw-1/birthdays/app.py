import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session, url_for

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():

    if request.method == "POST":

        # Add the user's entry into the database
        name = request.form.get("birth_name")
        month = request.form.get("birth_month")
        day = request.form.get("birth_day")

        if name and month and day:
            db.execute(
                "INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?)",
                name, month, day
            )

        return redirect(url_for("index"))

    elif request.method == "GET":

        # Display the entries in the database on index.html
        birthdays = db.execute("SELECT * FROM birthdays")

        return render_template("index.html", birthdays=birthdays)


@app.route("/update", methods=["POST"])
def update():
    # Update the user's entry in the database
    birthday_id = request.form.get("id")
    name = request.form.get("birth_name")
    month = request.form.get("birth_month")
    day = request.form.get("birth_day")

    if birthday_id and name and month and day:
        db.execute(
            "UPDATE birthdays SET name = ?, month = ?, day = ? WHERE id = ?",
            name, month, day, birthday_id
        )

    return redirect(url_for("index"))


@app.route("/delete", methods=["POST"])
def delete():
    # Delete the user's entry from the database
    birthday_id = request.form.get("id")
    if birthday_id:
        db.execute("DELETE FROM birthdays WHERE id = ?", birthday_id)

    return redirect(url_for("index"))

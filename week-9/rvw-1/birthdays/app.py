import os
import sys

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


# @app.after_request
# def after_request(response):
#     """Ensure responses aren't cached"""
#     response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
#     response.headers["Expires"] = 0
#     response.headers["Pragma"] = "no-cache"
#     return response


@app.route("/", methods=["GET", "DELETE", "POST", "PUT"])
def index():
    if request.method == "POST":

        # TODO: Add the user's entry into the database
        name = request.form.get("birth_name")
        month = request.form.get("birth_month")
        day = request.form.get("birth_day")

        if name and month and day:
            db.execute(
                "INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?)",
                name, month, day
            )

        return redirect("/")

    elif request.method == "PUT":
        
        birthday_id = request.form.get("id")
        name = request.form.get("birth_name")
        month = request.form.get("birth_month")
        day = request.form.get("birth_day")
        
        if birthday_id and name and month and day:
            db.execute(
                "UPDATE birthdays SET name = ?, month = ?, day = ? WHERE id = ?",
                name, month, day, birthday_id
            )

        return redirect("/")

    elif request.method == "DELETE":
        birthday_id = request.args.get()
        if birthday_id:
            db.execute("DELETE FROM birthdays WHERE id = ?", birthday_id)

        return redirect("/")

    elif request.method == "GET":

        # Display the entries in the database on index.html
        birthdays = db.execute("SELECT * FROM birthdays")

        # return render_template("index.html", birthdays=birthdays)
        return jsonify(birthdays)

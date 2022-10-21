from flask import Flask, redirect, render_template, request
from cs50 import SQL

app = Flask(__name__)

SPORTS = ["Basketball", "Hockey", "Volleyball"]

db = SQL("sqlite:///froshims.db")


@app.route("/")
def index():
    return render_template("index.html", sports=SPORTS)


@app.route("/register", methods=["POST"])
def register():
    name = request.form.get("name")
    if not name:
        return render_template("error.html", message="No name!")

    sport = request.form.get("sport")
    if not sport:
        return render_template("error.html", message="No sport!")

    if sport not in SPORTS:
        return render_template("error.html", message="Bad sport!")

    db.execute(
        "INSERT INTO registrants (name, sport) VALUES (?, ?)", name, sport
    )

    return redirect("registrants")


@app.route("/registrants")
def registrants():
    registrants = db.execute("SELECT id, name, sport FROM registrants")
    return render_template("registrants.html", registrants=registrants)


@app.route("/delete", methods=["POST"])
def delete():
    id = request.form.get("id")
    print(id)
    db.execute("DELETE FROM registrants WHERE id = ?", id)
    return redirect("registrants")

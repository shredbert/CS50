from flask import Flask, render_template, request
import sys

app = Flask(__name__)

SPORTS = ["Basketball", "Hockey", "Volleyball"]


@app.route("/")
def index():
    return render_template("index.html", sports=SPORTS)


@app.route("/register", methods=["POST"])
def register():

    # Register with checkboxes
    name = request.form.get("name")
    if len(name) == 0:
        return render_template("message.html", message="No name!")

    selectedSports = []

    basketball = request.form.get("Basketball")
    if basketball == "on":
        selectedSports.append(basketball)

    hockey = request.form.get("Hockey")
    if hockey == "on":
        selectedSports.append(hockey)

    volleyball = request.form.get("Volleyball")
    if volleyball == "on":
        selectedSports.append(volleyball)

    if not selectedSports:
        return render_template("message.html", message="No sport!")

    return render_template("message.html", message="Success!")

    # # Register with dropdown
    # name = request.form.get("name")
    # sport = request.form.get("sport")
    # if not name:
    #     return render_template("message.html", message="No name!")
    # if not sport:
    #     return render_template("message.html", message="No sport!")
    # if sport not in SPORTS:
    #     return render_template("message.html", message="Bad sport!")

    # return render_template("message.html", message="Success!")

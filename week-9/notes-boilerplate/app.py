from flask import Flask, redirect, render_template, request, session
from flask_session import Session
from cs50 import SQL

app = Flask(__name__)

db = SQL("sqlite:///??.db")

app.config["SESSION_TYPE"] = "filesystem"
app.config["SESSION_PERMANENT"] = False
Session(app)


@app.route("/")
def index():
    return render_template("index.html")

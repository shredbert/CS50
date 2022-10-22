from flask import Flask, redirect, render_template, request
from cs50 import SQL

app = Flask(__name__)

db = SQL("sqlite:///??.db")


@app.route("/")
def index():
    return render_template("index.html")

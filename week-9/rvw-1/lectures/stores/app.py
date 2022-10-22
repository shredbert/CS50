from flask import Flask, redirect, render_template, request, session
from flask_session import Session
from cs50 import SQL

app = Flask(__name__)

db = SQL("sqlite:///stores.db")

app.config["SESSION_TYPE"] = "filesystem"
app.config["SESSION_PERMANENT"] = False
Session(app)


@app.route("/")
def index():
    books = db.execute("SELECT * FROM books")
    return render_template("index.html", books=books)


@app.route("/cart", methods=["GET", "POST"])
def cart():
    # Store list of book IDs in cart

    # if not session.get("cart"): # can also use:
    if "cart" not in session:
        session["cart"] = []

    if request.method == "POST":
        selected_id = request.form.get("id")
        session["cart"].append(selected_id)
        return redirect("/cart")

    books_in_cart = db.execute(
        "SELECT * FROM books WHERE id IN (?)",
        session["cart"]
    )
    return render_template("cart.html", books=books_in_cart)

import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, \
    url_for
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    return apology("Working on home page!!!")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "GET":
        return render_template("buy-stocks.html")

    if request.method == "POST":
        # Get stock symbol
        stock_symbol = None or request.form.get("symbol")

        # Error if symbol missing
        if not stock_symbol:
            return apology("Please submit a symbol", 403)

        # Lookup stock info
        stock_info = None or lookup(stock_symbol)

        # Error if symbol invalid
        if not lookup(stock_symbol):
            return apology("Please submit a valid symbol", 403)

        # Get num of shares to buy
        number_of_shares = None or request.form.get("shares")

        # Error if # shares missing
        if not number_of_shares:
            return apology("Please submit the number of shares to buy", 403)
        # Error if # shares <= 0
        elif number_of_shares <= 0:
            return apology("Please submit a valid number of shares to buy", 403)

        # Look up user's balance
        user_balance = db.execute(
            "SELECT cash FROM users WHERE id = ?",
            session["user_id"]
        )

        # Error if user balance < # shares * price
        if user_balance < (number_of_shares * stock_info.price):
            return apology("Not enough cash to purchase stocks", 403)

        # TODO: Store purchases -- purchase id (unique/PK), user id (FK), symbol
        # name, # shares, price, total $ (calculated field?), datetime

        return apology("TODO")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?",
            request.form.get("username")
        )

        # Ensure username exists and password is correct
        if (len(rows) != 1 or
                not check_password_hash(
                    rows[0]["hash"], request.form.get("password")
                )):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect(url_for("index"))

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect(url_for("index"))


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("search-quotes.html")
    else:
        stock_symbol = None or request.form.get("symbol")
        lookup_results = None or lookup(stock_symbol)

        if not stock_symbol:
            return apology("Must input a stock symbol to search", 403)

        if not lookup_results:
            flash("Invalid symbol -- please try again")
            return render_template("search-quotes.html")
            # return apology("That symbol is invalid", 403)

        print(lookup_results)
        return render_template("quote-results.html", quote=lookup_results)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")
    else:
        if (not request.form.get("username") or
                not request.form.get("password") or
                not request.form.get("confirmation")):
            return apology("All fields required", 403)

        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("Passwords do not match", 403)

        username = request.form.get("username")
        password = generate_password_hash(request.form.get("password"))

        existing_user_id = db.execute(
            "SELECT id FROM users WHERE username = ?",
            username
        )
        if existing_user_id:
            return apology("That username already exists", 403)

        new_row = db.execute(
            "INSERT INTO users (username, hash) VALUES (?, ?)",
            username,
            password
        )

        if not new_row:
            return apology("Could not register -- please try again", 403)

        flash("Registration successful")
        return render_template("login.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    return apology("TODO")

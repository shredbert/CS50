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
    try:
        # Store portfolio as list & initialize total wealth
        user_portfolio = []
        total_wealth = 0

        # Get distinct stock symbols owned & the total # of each
        stocks_owned = db.execute(
            ("SELECT DISTINCT stock_symbol, SUM(number_of_shares) "
             "AS total_shares "
             "FROM stock_transactions "
             "WHERE user_id = ? "
             "GROUP BY stock_symbol"),
            session["user_id"]
        )

        # Look up the current price for each stock & calc the total
        # current value
        for stock in stocks_owned:
            stock_info = lookup(stock["stock_symbol"])

            portfolio_item = {}
            portfolio_item["symbol"] = stock_info["symbol"]
            portfolio_item["shares"] = int(stock["total_shares"])
            portfolio_item["company_name"] = stock_info["name"]
            portfolio_item["current_price"] = stock_info["price"]
            portfolio_item["total_value"] = portfolio_item["shares"] * \
                portfolio_item["current_price"]

            total_wealth += portfolio_item["total_value"]
            user_portfolio.append(portfolio_item)

        # TODO: Get user's current balance & grand total -- i.e., cash + total
        # value of stocks
        user_wealth = {}
        user_cash = db.execute(
            "SELECT cash FROM users WHERE id = ?",
            session["user_id"]
        )[0]["cash"]
        total_wealth += user_cash
        user_wealth["cash"] = user_cash
        user_wealth["total"] = total_wealth

    # TODO: Figure out specific exception for DB lookup
    except:
        return apology("Error looking up portfolio information", 400)

    return render_template(
        "index.html",
        user_wealth=user_wealth,
        user_portfolio=user_portfolio
    )


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "GET":
        return render_template("buy-stocks.html")

    elif request.method == "POST":
        # Get stock symbol
        stock_symbol = request.form.get("symbol")

        # Error if symbol missing
        if not stock_symbol:
            return apology("Please submit a symbol", 403)

        # Look up stock info
        stock_info = lookup(stock_symbol)

        # Error if symbol invalid
        if not lookup(stock_symbol):
            return apology("Please submit a valid stock symbol", 403)

        try:
            # Get num of shares to buy
            number_of_shares = int(request.form.get("shares"))

            # Error if # shares missing
            if not number_of_shares:
                return apology("Please enter the number of shares to buy", 403)
            # Error if # shares < 1
            elif (number_of_shares < 1):
                return apology(
                    ("Please submit a number of shares to buy that is greater "
                     "than 0"),
                    403
                )

        # Error if # shares not valid int
        except (TypeError, ValueError):
            return apology(
                "Please submit the number of shares to buy as a valid number",
                403
            )

        try:
            # Look up user's balance
            user_balance = float(db.execute(
                "SELECT cash FROM users WHERE id = ?",
                session["user_id"])[0]["cash"]
            )
        except (TypeError, ValueError):
            return apology(
                "Error fetching user balance -- incorrect format",
                403
            )

        # Error if user balance < # shares * price
        total_cost = number_of_shares * stock_info["price"]

        if user_balance < total_cost:
            return apology(
                ("Not enough cash to purchase stocks. Your balance is "
                 f"${user_balance:,.2f} & {number_of_shares} share(s) of "
                 f"{stock_info['name']} costs ${total_cost:,.2f}."),
                403
            )

        # Calculate new balance
        new_balance = user_balance - total_cost

        # Store purchase -- user_id, stock_symbol, number_of_shares,
        # stock_price
        new_purchase_id = db.execute(
            ("INSERT INTO stock_transactions (user_id, transaction_type, "
             "stock_symbol, number_of_shares, stock_price) "
             "VALUES (?, ?, ?, ?, ?)"),
            session["user_id"],
            "buy",
            stock_symbol,
            number_of_shares,
            stock_info['price']
        )

        # Update user's balance
        user_rows_updated = db.execute(
            ("UPDATE users "
             "SET cash = ? "
             "WHERE id = ?"),
            new_balance,
            session["user_id"]
        )

        if not new_purchase_id or not user_rows_updated:
            return apology(
                "Purchase could not be completed -- please try again",
                403
            )

        flash(
            (f"You successfully purchased {number_of_shares} share(s) of "
             f"{stock_info['name']} for ${total_cost:,.2f}.")
        )

        return redirect(url_for("index"))


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
        stock_symbol = request.form.get("symbol")

        if not stock_symbol:
            return apology("Must input a stock symbol to search", 403)

        lookup_results = lookup(stock_symbol)

        if not lookup_results:
            flash("Invalid symbol -- please try again")
            return render_template("search-quotes.html")
            # Better UX to take back to message for re-searching & giving
            # feedback there
            # return apology("That symbol is invalid", 403)

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

        flash(f"Hi, {username}! You've registered successfully.")
        # Use render_template instead of redirect to display message -- login
        # route deletes session so won't display message
        return render_template("login.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "GET":
        # TODO: Pass all distinct stock symbols where user has > 0 shares
        stocks_owned = db.execute(
            ("SELECT DISTINCT stock_symbol, SUM(number_of_shares) "
             "AS total_shares "
             "FROM stock_transactions "
             "WHERE user_id = ? "
             "GROUP BY stock_symbol"),
            session["user_id"]
        )
        print(stocks_owned)
        return render_template("sell-stocks.html", stocks_owned=stocks_owned)
    elif request.method == "POST":
        # TODO: Error if user doesn't submit valid stock as "symbol"
        # TODO: Error if user doesn't own any shares of selected stock
        # TODO: Error if user doesn't submit shares to sell as "shares"
        # TODO: Error if shares < 1
        # TODO: Look up shares of selected stock user currently owns
        # TODO: Error if shares selected > shares owned
        # TODO: Add sale to transactions table & return to home page
        return redirect(url_for("index"))

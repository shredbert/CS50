import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, \
    url_for, jsonify
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd, is_valid_password

# TODO: Verify all try/except blocks make sense -- consolidate all within each
# function? Or keep sprinkled throughout?

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

        # Get distinct stock symbols owned & the total # bought & sold
        stocks_owned = db.execute(
            "SELECT DISTINCT stock_symbol, \
            CAST(\
                (TOTAL(number_of_shares) FILTER(\
                    WHERE transaction_type = 'buy'\
                )) - \
                (TOTAL(number_of_shares) FILTER(\
                    WHERE transaction_type = 'sell'\
                )) AS INT\
            ) AS total_shares \
            FROM stock_transactions \
            WHERE user_id = ? \
            GROUP BY stock_symbol \
            HAVING (\
                (TOTAL(number_of_shares) \
                 FILTER(WHERE transaction_type = 'buy')) - \
                (TOTAL(number_of_shares) \
                 FILTER(WHERE transaction_type = 'sell'))\
            ) > 0",
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

        # Get user's current balance & grand total -- i.e., cash + total
        # value of stocks
        user_wealth = {}
        user_cash = db.execute(
            "SELECT cash FROM users WHERE id = ?",
            session["user_id"]
        )[0]["cash"]
        total_wealth += user_cash
        user_wealth["cash"] = user_cash
        user_wealth["total"] = total_wealth

    # Error if no results/DB error
    except (IndexError, RuntimeError):
        return apology(
            "Sorry, your portfolio could not be fetched -- please try again.",
            500
        )
    # Error if can't convert # of stocks to int
    except (TypeError, ValueError):
        return apology(
            ("Sorry, an error was found with your portfolio data -- please "
             "try again."),
            500
        )

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

        # Get stock symbol -- case DOESN'T matter to API
        stock_symbol = request.form.get("symbol")

        # Error if symbol missing
        if not stock_symbol:
            return apology("Please submit a stock symbol", 400)

        # Look up stock info
        stock_info = lookup(stock_symbol)

        # Error if symbol invalid
        if not lookup(stock_symbol):
            return apology("Please submit a valid stock symbol", 400)

        try:
            # Get num of shares to buy
            number_of_shares = int(request.form.get("shares"))

            # Error if # shares missing
            if not number_of_shares:
                return apology("Please enter the number of shares to buy", 400)
            # Error if # shares < 1
            elif (number_of_shares < 1):
                return apology(
                    ("Please submit a number of shares to buy that is greater "
                     "than 0"),
                    400
                )

        # Error if # shares not valid int
        except (TypeError, ValueError):
            return apology(
                "Please submit the number of shares to buy as a valid number",
                400
            )

        try:
            # Look up user's balance
            user_balance = float(db.execute(
                "SELECT cash FROM users WHERE id = ?",
                session["user_id"])[0]["cash"]
            )

            # Error if user balance < # shares * price
            buy_amount = number_of_shares * stock_info["price"]

            if user_balance < buy_amount:
                return apology(
                    ("Not enough cash to purchase stocks. Your balance is "
                     f"${user_balance:,.2f} & {number_of_shares} share(s) of "
                     f"{stock_info['name']} costs ${buy_amount:,.2f}."),
                    400
                )

            # Calculate new balance
            # TODO: Is this less efficient than calculating in DB & retrieving
            # afterwards?
            new_balance = user_balance - buy_amount

            # Store purchase -- user_id, stock_symbol, number_of_shares,
            # stock_price
            new_transaction = db.execute(
                "INSERT INTO stock_transactions (user_id, transaction_type, \
                 stock_symbol, number_of_shares, stock_price) \
                 VALUES (?, ?, ?, ?, ?)",
                session["user_id"],
                "buy",
                # Use symbol retrieved from API -- stored in uppercase
                # TODO: Better than just uppercasing?
                stock_info['symbol'],
                number_of_shares,
                stock_info['price']
            )

            # Update user's balance
            db.execute(
                "UPDATE users \
                 SET cash = cash - ? \
                 WHERE id = ?",
                buy_amount,
                session["user_id"]
            )

        except (IndexError, RuntimeError):
            return apology(
                ("Sorry, your purchase could not be completed -- please try "
                 "again"),
                500
            )

        success_message = (
            f"You successfully purchased {number_of_shares} share(s) of "
            f"{stock_info['name']} for ${buy_amount:,.2f}."
        )

        flash(success_message)
        return redirect(url_for("index"))


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # TODO: Format time to be more user-friendly in query?
    transactions = db.execute(
        "SELECT stock_symbol AS symbol, transaction_type AS type, \
            transaction_price AS price, number_of_shares AS shares, \
            DATE(transaction_time) AS transaction_date, \
            TIME(transaction_time, 'localtime') AS transaction_time \
         FROM stock_transactions \
         WHERE user_id = ? \
         ORDER BY transaction_time DESC",
        session["user_id"]
    )
    return render_template("history.html", transactions=transactions)


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
            return apology("Must input a stock symbol to search", 400)

        lookup_results = lookup(stock_symbol)

        if not lookup_results:
            return apology("That symbol is invalid", 400)

            # TODO: Better UX to flash message on same page
            # flash("Invalid symbol -- please try again")
            # return render_template("search-quotes.html")

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
            return apology("All fields required", 400)

        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("Passwords do not match", 400)

        elif not is_valid_password(request.form.get("password")):
            return apology(
                ("Password must be 8+ chars & have at least 1 lower, 1 cap, 1 "
                 "num, & 1 symbol"),
                400
            )

        username = request.form.get("username")
        password = generate_password_hash(request.form.get("password"))

        try:
            existing_user_id = db.execute(
                "SELECT id FROM users WHERE username = ?",
                username
            )

            if existing_user_id:
                return apology("That username already exists", 400)

            db.execute(
                "INSERT INTO users (username, hash) VALUES (?, ?)",
                username,
                password
            )

        except (IndexError, RuntimeError):
            return apology(
                ("Sorry, your account could not be registered. Please try "
                 "again."),
                500
            )

        flash(f"Hi, {username}! You've registered successfully.")
        # Use render_template instead of redirect to display message -- login
        # route deletes session so won't display message
        return render_template("login.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "GET":

        # Pass all distinct stock symbols where user has > 0 shares
        # TODO: Include company name for display to users -- better UX?
        try:
            stocks_owned = db.execute(
                "SELECT DISTINCT stock_symbol, \
                CAST(\
                    (TOTAL(number_of_shares) FILTER(\
                        WHERE transaction_type = 'buy'\
                    )) - \
                    (TOTAL(number_of_shares) FILTER(\
                        WHERE transaction_type = 'sell'\
                    )) AS INT\
                ) AS total_shares \
                FROM stock_transactions \
                WHERE user_id = ? \
                GROUP BY stock_symbol \
                HAVING (\
                    (TOTAL(number_of_shares) \
                     FILTER(WHERE transaction_type = 'buy')) - \
                    (TOTAL(number_of_shares) \
                     FILTER(WHERE transaction_type = 'sell'))\
                ) > 0",
                session["user_id"]
            )
        except RuntimeError:
            return apology(
                "Sorry, your stocks could not be found -- please try again.",
                500
            )

        return render_template("sell-stocks.html", stocks_owned=stocks_owned)

    elif request.method == "POST":
        # Error if user doesn't submit a stock "symbol"
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Must submit a stock symbol to sell", 400)

        # Error if stock symbol isn't valid
        stock_info = lookup(symbol)
        if not stock_info:
            return apology("Sorry, that stock symbol is not valid", 400)

        # Error if user doesn't submit shares to sell as "shares", isn't
        # valid number, or # of shares < 1
        try:
            shares_to_sell = int(request.form.get("shares"))
            if shares_to_sell < 1:
                return apology(
                    "Please submit 1 or more shares to sell",
                    400
                )

        except (TypeError, ValueError):
            return apology(
                "Please submit a valid number of shares to sell",
                400
            )

        # Look up shares of selected stock user currently owns
        # Looking up again in case has changed after initial display
        try:
            stocks_owned = db.execute(
                "SELECT DISTINCT stock_symbol, \
                CAST(\
                    (TOTAL(number_of_shares) FILTER(\
                        WHERE transaction_type = 'buy'\
                    )) - \
                    (TOTAL(number_of_shares) FILTER(\
                        WHERE transaction_type = 'sell'\
                    )) AS INT\
                ) AS total_shares \
                FROM stock_transactions \
                WHERE user_id = ?\
                GROUP BY stock_symbol \
                HAVING stock_symbol = ?\
                AND (\
                    (TOTAL(number_of_shares) \
                        FILTER(WHERE transaction_type = 'buy')) - \
                    (TOTAL(number_of_shares) \
                        FILTER(WHERE transaction_type = 'sell'))\
                ) > 0",
                session["user_id"],
                symbol
            )[0]['total_shares']

            # Error if # of shares < 1 or shares selected > shares owned
            if shares_to_sell > stocks_owned:
                return apology(
                    "Sorry, you don't own enough of those shares to sell",
                    400
                )

            # Add sale to transactions table
            db.execute(
                "INSERT INTO stock_transactions (\
                    user_id, transaction_type, stock_symbol, \
                    number_of_shares, stock_price\
                 ) VALUES (?, ?, ?, ?, ?)",
                session["user_id"],
                "sell",
                stock_info["symbol"],
                shares_to_sell,
                stock_info["price"]
            )

            # Update user cash balance
            sell_amount = stock_info["price"] * shares_to_sell
            db.execute(
                "UPDATE users \
                 SET cash = cash + ? \
                 WHERE id = ?",
                sell_amount,
                session["user_id"]
            )

        # Error if don't own any of those stocks
        except (TypeError, ValueError):
            return apology("Sorry, you don't own any of those stocks", 400)

        # Error if any queries fail
        except (IndexError, RuntimeError):
            return apology(
                "Sorry, your stock(s) could not be sold. Please try again.",
                500
            )

        # Give feedback & return to home page
        flash(
            (f"You successfully sold {shares_to_sell} share(s) of "
             f"{stock_info['name']} stock for "
             f"${shares_to_sell * stock_info['price']:,.2f}.")
        )

        return redirect(url_for("index"))


@app.route("/settings")
def settings():
    if request.method == "GET":
        try:
            # Fetch current balance to show in form for adding cash
            balance = db.execute(
                "SELECT cash \
                 FROM users \
                 WHERE id = ?",
                session["user_id"]
            )[0]["cash"]

            return render_template("user-settings.html", balance=balance)

        except (KeyError, RuntimeError):
            return apology(
                ("Sorry, your settings could not be loaded -- please "
                 "try again later."),
                500
            )


@app.route("/update-password", methods=["POST"])
def update_password():
    try:
        # Check all fields submitted
        usr_existing_pw = request.form.get("existing")
        new_pw = request.form.get("new")
        confirm_pw = request.form.get("confirm")

        if not usr_existing_pw or not new_pw or not confirm_pw:
            return apology("Please submit all fields", 400)

        # Fetch current password & dehash
        db_existing_pw = db.execute(
            "SELECT hash FROM users WHERE id = ?",
            session["user_id"]
        )[0]["hash"]

        # Check existing DB & user PWs match
        if not check_password_hash(db_existing_pw, usr_existing_pw):
            return apology("Sorry, your existing password is incorrect", 400)

        # Check "new" & "confirm" are equivalent
        elif new_pw != confirm_pw:
            return apology(
                "Sorry, your new & confirmation passwords do not match", 400
            )

        # Check existing & new PWs don't match
        elif usr_existing_pw == new_pw:
            return apology(
                ("Please enter a new password that is different from your old "
                 "one"),
                400
            )

        elif not is_valid_password(new_pw):
            return apology(
                ("Password must be 8+ chars & have at least 1 lower, 1 cap, 1 "
                 "num, & 1 symbol"),
                400
            )

        # Hash "new" & replace PW in DB
        db.execute(
            "UPDATE users \
             SET hash = ? \
             WHERE id = ?",
            generate_password_hash(new_pw),
            session["user_id"]
        )

        # TODO: Log user out & back in to ensure they've stored it in their PW
        # manager but ISSUE: How to provide feedback after signing them out?
        flash("Your password has been successfully updated.")
        return redirect(url_for("index"))

    except (IndexError, RuntimeError):
        return apology("Sorry, your password could not be updated", 500)


@app.route("/add-cash", methods=["POST"])
def add_cash():
    try:
        # Get amount to add
        amount_to_add = float(request.form.get("amount"))

        # Check amount to add > 0
        if amount_to_add <= 0:
            return apology(
                ("Please submit a positive dollar value to add to your "
                 "balance"),
                400
            )

    # Check amount to add submitted & valid #
    except (ValueError):
        return apology("Please submit an amount to add as a valid number", 400)

    # Add submitted amount to cash balance
    try:
        db.execute(
            "UPDATE users \
             SET cash = cash + ? \
             WHERE id = ?",
            amount_to_add,
            session["user_id"]
        )

        flash(f"You successfully added ${amount_to_add:,.2f} to your account.")
        return redirect(url_for("index"))

    except (IndexError, RuntimeError):
        return apology("Sorry, your balance could not be updated", 500)

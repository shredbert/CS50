import os
import re
import requests
import urllib.parse

from flask import redirect, render_template, request, session
from functools import wraps


def apology(message, code=400):
    """Render message as an apology to user."""
    def escape(s):
        """
        Escape special characters.

        https://github.com/jacebrowning/memegen#special-characters
        """
        for old, new in [("-", "--"), (" ", "-"), ("_", "__"), ("?", "~q"),
                         ("%", "~p"), ("#", "~h"), ("/", "~s"), ("\"", "''")]:
            s = s.replace(old, new)
        return s
    return render_template("apology.html", top=code, bottom=escape(message)), code


def login_required(f):
    """
    Decorate routes to require login.

    https://flask.palletsprojects.com/en/1.1.x/patterns/viewdecorators/
    """
    @wraps(f)
    def decorated_function(*args, **kwargs):
        if session.get("user_id") is None:
            return redirect("/login")
        return f(*args, **kwargs)
    return decorated_function


def lookup(symbol):
    """Look up quote for symbol."""

    # Contact API
    try:
        api_key = os.environ.get("API_KEY")
        url = f"https://cloud.iexapis.com/stable/stock/{urllib.parse.quote_plus(symbol)}/quote?token={api_key}"
        response = requests.get(url)
        response.raise_for_status()
    except requests.RequestException:
        return None

    # Parse response
    try:
        quote = response.json()
        return {
            "name": quote["companyName"],
            "price": float(quote["latestPrice"]),
            "symbol": quote["symbol"]
        }
    except (KeyError, TypeError, ValueError):
        return None


def usd(value):
    """Format value as USD."""
    return f"${value:,.2f}"


# Check that password is 8+ chars with 1 capital, 1 lowercase, 1 number, & 1
# symbol
# Accept all ascii symbols (30 total) -- `~!@#$%^&*()-_=+[{]}\|'",<.>/?
# Reference for regex troubleshooting:
# https://devsheet.com/code-snippet/validate-password-with-and-without-regex-in-python/#:~:text=Validate%20Password%20using%20regex%20in%20python%201%201.,4.%20Password%20must%20contain%20at%20least%20one%20number.
def is_valid_password(password):
    regex = r"^(?=.+\S{8,}$)"
    print("Password:", password)

    # if len(password) < 8 or not re.search(regex, password):
    if re.search(regex, password):
        print("Invalid")
        return False

    print("Valid")
    return True

import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd
app.jinja_env.filters["abs"] = abs

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


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
    # Get all stocks owned by user, grouped by symbol
    holdings = db.execute(
        "SELECT symbol, SUM(shares) AS total_shares FROM transactions WHERE user_id = ? GROUP BY symbol HAVING total_shares > 0",
        session["user_id"]
    )

    # Get current price for each stock and calculate total value
    total_stock_value = 0
    for holding in holdings:
        quote = lookup(holding["symbol"])
        holding["name"] = quote["name"]
        holding["price"] = quote["price"]
        holding["total_value"] = holding["total_shares"] * quote["price"]
        total_stock_value += holding["total_value"]

    # Get user's cash balance
    user = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    cash = user[0]["cash"]

    grand_total = cash + total_stock_value

    return render_template("index.html", holdings=holdings, cash=cash, grand_total=grand_total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol").upper()
        shares = request.form.get("shares")

        # Validate symbol
        if not symbol:
            return apology("must provide symbol", 400)
        quote = lookup(symbol)
        if not quote:
            return apology("invalid symbol", 400)

        # Validate shares
        if not shares or not shares.isdigit() or int(shares) <= 0:
            return apology("must provide a positive integer number of shares", 400)
        shares = int(shares)

        # Check if user can afford it
        user = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        cash = user[0]["cash"]
        total_cost = quote["price"] * shares

        if cash < total_cost:
            return apology("can't afford", 400)

        # Record the transaction
        db.execute(
            "INSERT INTO transactions (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)",
            session["user_id"], symbol, shares, quote["price"]
        )

        # Deduct cash from user
        db.execute(
            "UPDATE users SET cash = cash - ? WHERE id = ?",
            total_cost, session["user_id"]
        )

        flash(f"Bought {shares} share(s) of {symbol}!")
        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute(
        "SELECT symbol, shares, price, transacted_at FROM transactions WHERE user_id = ? ORDER BY transacted_at DESC",
        session["user_id"]
    )
    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        return redirect("/")

    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""
    session.clear()
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")

        if not symbol:
            return apology("must provide symbol", 400)

        quote = lookup(symbol)
        if not quote:
            return apology("invalid symbol", 400)

        return render_template("quoted.html", quote=quote)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Validate inputs
        if not username:
            return apology("must provide username", 400)
        if not password:
            return apology("must provide password", 400)
        if not confirmation:
            return apology("must confirm password", 400)
        if password != confirmation:
            return apology("passwords do not match", 400)

        # Insert new user, catching duplicate username
        try:
            db.execute(
                "INSERT INTO users (username, hash) VALUES (?, ?)",
                username, generate_password_hash(password)
            )
        except ValueError:
            return apology("username already exists", 400)

        # Log the new user in
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)
        session["user_id"] = rows[0]["id"]

        flash("Registered!")
        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    # Get stocks the user owns
    holdings = db.execute(
        "SELECT symbol, SUM(shares) AS total_shares FROM transactions WHERE user_id = ? GROUP BY symbol HAVING total_shares > 0",
        session["user_id"]
    )

    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Validate symbol
        if not symbol:
            return apology("must select a stock", 400)

        # Check user actually owns this stock
        owned = next((h for h in holdings if h["symbol"] == symbol), None)
        if not owned:
            return apology("you don't own that stock", 400)

        # Validate shares
        if not shares or not shares.isdigit() or int(shares) <= 0:
            return apology("must provide a positive integer number of shares", 400)
        shares = int(shares)

        if shares > owned["total_shares"]:
            return apology("too many shares", 400)

        # Get current price
        quote = lookup(symbol)

        # Record the transaction (negative shares = sell)
        db.execute(
            "INSERT INTO transactions (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)",
            session["user_id"], symbol, -shares, quote["price"]
        )

        # Add cash back to user
        db.execute(
            "UPDATE users SET cash = cash + ? WHERE id = ?",
            quote["price"] * shares, session["user_id"]
        )

        flash(f"Sold {shares} share(s) of {symbol}!")
        return redirect("/")

    else:
        return render_template("sell.html", holdings=holdings)


@app.route("/password", methods=["GET", "POST"])
@login_required
def password():
    """Allow user to change password (personal touch)"""
    if request.method == "POST":
        current = request.form.get("current_password")
        new = request.form.get("new_password")
        confirmation = request.form.get("confirmation")

        if not current or not new or not confirmation:
            return apology("must fill out all fields", 400)
        if new != confirmation:
            return apology("new passwords do not match", 400)

        # Verify current password
        rows = db.execute("SELECT hash FROM users WHERE id = ?", session["user_id"])
        if not check_password_hash(rows[0]["hash"], current):
            return apology("current password is incorrect", 403)

        # Update password
        db.execute(
            "UPDATE users SET hash = ? WHERE id = ?",
            generate_password_hash(new), session["user_id"]
        )

        flash("Password changed!")
        return redirect("/")

    else:
        return render_template("password.html")
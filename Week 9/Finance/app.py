from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd


# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure database
db = SQL("sqlite:///finance.db")


# Make sure transactions table exists
db.execute("""
    CREATE TABLE IF NOT EXISTS transactions (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        user_id INTEGER NOT NULL,
        symbol TEXT NOT NULL,
        shares INTEGER NOT NULL,
        price NUMERIC NOT NULL,
        transacted_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
    )
""")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached."""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks."""

    user_id = session["user_id"]

    # Get user's cash
    user = db.execute(
        "SELECT cash FROM users WHERE id = ?",
        user_id
    )

    cash = user[0]["cash"]

    # Get stocks owned by the user
    transactions = db.execute(
        """
        SELECT symbol, SUM(shares) AS shares
        FROM transactions
        WHERE user_id = ?
        GROUP BY symbol
        HAVING SUM(shares) > 0
        """,
        user_id
    )

    portfolio = []
    total_stock_value = 0

    for transaction in transactions:

        quote = lookup(transaction["symbol"])

        if quote is None:
            continue

        shares = transaction["shares"]
        price = quote["price"]
        total = shares * price

        total_stock_value += total

        portfolio.append({
            "symbol": quote["symbol"],
            "name": quote["name"],
            "shares": shares,
            "price": price,
            "total": total
        })

    grand_total = cash + total_stock_value

    return render_template(
        "index.html",
        portfolio=portfolio,
        cash=cash,
        total=grand_total
    )


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock."""

    if request.method == "POST":

        symbol = request.form.get("symbol")

        # Check symbol
        if not symbol:
            return apology("must provide symbol", 400)

        quote = lookup(symbol)

        if quote is None:
            return apology("invalid symbol", 400)

        # Check shares
        shares = request.form.get("shares")

        if not shares:
            return apology("must provide number of shares", 400)

        try:
            shares = int(shares)
        except ValueError:
            return apology("shares must be a positive integer", 400)

        if shares <= 0:
            return apology("shares must be a positive integer", 400)

        user_id = session["user_id"]

        # Get user's cash
        user = db.execute(
            "SELECT cash FROM users WHERE id = ?",
            user_id
        )

        cash = user[0]["cash"]

        # Calculate purchase cost
        total_cost = quote["price"] * shares

        # Check affordability
        if total_cost > cash:
            return apology("can't afford that purchase", 400)

        # Record transaction
        db.execute(
            """
            INSERT INTO transactions
            (user_id, symbol, shares, price)
            VALUES (?, ?, ?, ?)
            """,
            user_id,
            quote["symbol"],
            shares,
            quote["price"]
        )

        # Remove money
        db.execute(
            "UPDATE users SET cash = cash - ? WHERE id = ?",
            total_cost,
            user_id
        )

        flash("Purchase successful!")

        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions."""

    user_id = session["user_id"]

    transactions = db.execute(
        """
        SELECT symbol, shares, price, transacted_at
        FROM transactions
        WHERE user_id = ?
        ORDER BY transacted_at DESC
        """,
        user_id
    )

    return render_template(
        "history.html",
        transactions=transactions
    )


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in."""

    # Forget any previous user
    session.clear()

    if request.method == "POST":

        username = request.form.get("username")
        password = request.form.get("password")

        if not username:
            return apology("must provide username", 403)

        if not password:
            return apology("must provide password", 403)

        # Find user
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?",
            username
        )

        # Check username and password
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"],
            password
        ):
            return apology(
                "invalid username and/or password",
                403
            )

        # Remember user
        session["user_id"] = rows[0]["id"]

        return redirect("/")

    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out."""

    session.clear()

    return redirect("/login")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "POST":

        symbol = request.form.get("symbol")

        if not symbol:
            return apology("must provide symbol", 400)

        quote_data = lookup(symbol)

        if quote_data is None:
            return apology("invalid symbol", 400)

        return render_template(
            "quoted.html",
            quote=quote_data
        )

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user."""

    if request.method == "POST":

        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Username
        if not username:
            return apology("must provide username", 400)

        # Password
        if not password:
            return apology("must provide password", 400)

        # Confirmation
        if not confirmation:
            return apology("must confirm password", 400)

        # Matching passwords
        if password != confirmation:
            return apology("passwords do not match", 400)

        # Insert user
        try:

            db.execute(
                """
                INSERT INTO users (username, hash)
                VALUES (?, ?)
                """,
                username,
                generate_password_hash(password)
            )

        except ValueError:
            return apology("username already exists", 400)

        flash("Registration successful!")

        return redirect("/login")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock."""

    user_id = session["user_id"]

    if request.method == "POST":

        symbol = request.form.get("symbol")

        if not symbol:
            return apology("must select a stock", 400)

        # Check how many shares the user owns
        rows = db.execute(
            """
            SELECT SUM(shares) AS shares
            FROM transactions
            WHERE user_id = ? AND symbol = ?
            """,
            user_id,
            symbol
        )

        owned = rows[0]["shares"]

        if owned is None or owned <= 0:
            return apology("you do not own this stock", 400)

        # Number of shares to sell
        shares = request.form.get("shares")

        if not shares:
            return apology("must provide number of shares", 400)

        try:
            shares = int(shares)
        except ValueError:
            return apology("shares must be a positive integer", 400)

        if shares <= 0:
            return apology("shares must be a positive integer", 400)

        if shares > owned:
            return apology("you do not own that many shares", 400)

        # Get current stock price
        quote = lookup(symbol)

        if quote is None:
            return apology("invalid symbol", 400)

        price = quote["price"]

        # Add a negative transaction
        db.execute(
            """
            INSERT INTO transactions
            (user_id, symbol, shares, price)
            VALUES (?, ?, ?, ?)
            """,
            user_id,
            quote["symbol"],
            -shares,
            price
        )

        # Add money to cash
        total_value = shares * price

        db.execute(
            """
            UPDATE users
            SET cash = cash + ?
            WHERE id = ?
            """,
            total_value,
            user_id
        )

        flash("Sale successful!")

        return redirect("/")

    else:

        # Get stocks owned by user
        stocks = db.execute(
            """
            SELECT symbol, SUM(shares) AS shares
            FROM transactions
            WHERE user_id = ?
            GROUP BY symbol
            HAVING SUM(shares) > 0
            """,
            user_id
        )

        return render_template(
            "sell.html",
            stocks=stocks
        )


@app.route("/add_cash", methods=["GET", "POST"])
@login_required
def add_cash():
    """Add cash to account."""

    if request.method == "POST":

        amount = request.form.get("amount")

        if not amount:
            return apology("must provide an amount", 400)

        try:
            amount = float(amount)
        except ValueError:
            return apology("invalid amount", 400)

        if amount <= 0:
            return apology("amount must be positive", 400)

        db.execute(
            """
            UPDATE users
            SET cash = cash + ?
            WHERE id = ?
            """,
            amount,
            session["user_id"]
        )

        flash("Cash added successfully!")

        return redirect("/")

    return render_template("add_cash.html")

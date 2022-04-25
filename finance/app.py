import os

from datetime import datetime
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
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
    stockList = db.execute("SELECT * from account WHERE id_user =?", session["user_id"])
    total = 0
    for stock in stockList:
        current_price = lookup(stock["symbol"])["price"]
        id = stock["id"]
        shares = stock["shares"]
        db.execute("UPDATE account SET current_price = ? WHERE id = ?", current_price, id)
        total += current_price * shares
    accountInfo = db.execute("SELECT * from account where id_user = ?", session["user_id"])
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
    return render_template("index.html", accountInfo = accountInfo, cash = cash, total = total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":

        #anti-injection
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        if lookup(symbol) == None:
            return apology("Sorry, Stock not found")
        try:
            int(shares)
        except:
            return apology("Sorry, try int in shares field")
        if int(shares) <= 0:
            return apology("Sorry, Shares not avaliable")

        #look up for price
        stockinfo = lookup(symbol)
        name = stockinfo["name"]
        price = stockinfo["price"]
        cash = db.execute("SELECT cash from users where id = ?", session["user_id"])[0]["cash"]
        total = float(price) * int(shares)
        if total >= int(cash):
            return apology("Sorry, not enough cash")
        #new database
        db.execute("INSERT INTO history (symbol, purchase_price, id_user, date_of_purchuse, shares) VALUES (?)", (symbol, price, session["user_id"], datetime.now(), shares))
        db.execute("UPDATE users SET cash = ? WHERE id = ?", (cash - total), session["user_id"])
        if db.execute("SELECT shares FROM account WHERE symbol = ?", symbol):
            db_shares = int(db.execute("SELECT shares FROM account WHERE symbol = ? AND id_user = ?", symbol, session["user_id"])[0]["shares"])
            db.execute("UPDATE account SET shares = ? WHERE symbol = ? AND id_user = ?", (int(shares) + int(db_shares)), symbol, session["user_id"])
        else:
            db.execute("INSERT INTO account (stock_name, total, symbol, shares, current_price, id_user) VALUES (?)", (name, total, symbol, shares, price, session["user_id"]))
        return redirect("/")
    return render_template("buy.html")





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
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        returndic = lookup(symbol)
        if returndic == None:
            return apology("Sorry, Stock not found")
        return render_template("quoted.html", returndic = returndic)
    return render_template("quote.html")



@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # Ensure username was submitted
    if request.method == "POST":
        try:
            username = request.form.get("username")
            password = request.form.get("password")
            if not request.form.get("username"):
                return apology("must provide username", 400)
            # Ensure password was submitted
            elif not request.form.get("password"):
                return apology("must provide password", 400)
            elif not request.form.get("password") == request.form.get("confirmation"):
                return apology("passwords do not match", 400)
            db.execute("INSERT INTO users (username, hash) VALUES (?)", (username, generate_password_hash(password)))
        except ValueError:
            return apology("you have already been registered!", 400)
        return redirect("/")
    return render_template("register.html")



@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        #update account db
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        print(symbol)
        stock_info = lookup(symbol)
        price = float(stock_info["price"])
        db_shares = int(db.execute("SELECT shares FROM account WHERE symbol = ? AND id_user = ?", symbol, session["user_id"])[0]["shares"])
        remain_shares = int(db_shares) - int(shares)
        if remain_shares >= 0:
            if remain_shares == 0:
                db.execute("DELETE FROM account WHERE symbol = ? AND id_user = ?", symbol, session["user_id"])
            else:
                db.execute("UPDATE account SET shares = ? WHERE symbol = ? AND id_user = ?", remain_shares, symbol, session["user_id"])
            #insert history db
            db.execute("INSERT INTO history (symbol, purchase_price, id_user, date_of_purchuse, shares) VALUES (?)", (symbol, -float(price), session["user_id"], datetime.now(), shares))
            #update user db
            cash = db.execute("SELECT cash from users where id = ?", session["user_id"])[0]["cash"]
            total = price * int(shares)
            db.execute("UPDATE users SET cash = ? WHERE id = ?", (cash + total), session["user_id"])
            return redirect("/")
        else:
            return apology("Sorry, not enough stocks")
    # get
    stock_list = db.execute("SELECT symbol FROM account WHERE id_user = ?", session["user_id"])
    return render_template("sell.html", stock_list = stock_list)

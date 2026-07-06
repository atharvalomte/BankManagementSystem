# Bank Management System

A bank account management system with a C++ backend and a web-based frontend.
The core logic (accounts, deposits, withdrawals, balance checks, transaction
history) is written in C++, and a small Python server sits in between so the
browser can talk to the C++ program.

## Why it's built this way

The C++ program itself is a normal console application — it doesn't know
anything about the web. To let a browser interact with it, I added a small
Flask server that takes requests from the frontend, runs the C++ program
with the right inputs, and sends the output back as a response. This avoids
having to write networking code directly in C++.

## How it works

```
Browser (HTML/CSS/JS)  --->  Flask server (app.py)  --->  C++ program (bank_system)
```

1. The frontend sends a request (e.g., "deposit 500 into account 12").
2. The Flask server receives it, runs the compiled C++ binary with the
   matching input, and reads back whatever it prints.
3. The C++ program reads/writes account data to `accounts.txt` and returns
   the result.
4. Flask converts that result into JSON and sends it back to the browser.

## Files

```
├── Account.h        # Account class definition
├── Account.cpp       # Account methods (deposit, withdraw, etc.)
├── Bank.h            # Bank class definition (holds all accounts)
├── Bank.cpp          # Core logic + file handling (accounts.txt)
├── main.cpp          # Console entry point
├── app.py            # Flask server that connects frontend to the C++ binary
├── index.html         # Frontend page
├── style.css          # Styling
└── app.js             # Handles frontend requests to the Flask server
```

## Features

- Create a new account
- Deposit and withdraw money
- Check account balance
- View transaction history
- Data is saved to a file (`accounts.txt`) so it persists between runs

## Running it

**1. Compile the C++ program**

```bash
g++ -std=c++17 main.cpp Bank.cpp Account.cpp -o bank_system
```

**2. Install and run the Flask server**

```bash
pip install flask flask-cors
python app.py
```

This starts the server on `http://localhost:5000` (or whichever port is set
in `app.py`).

**3. Open the frontend**

Open `index.html` in your browser, or run it through VS Code's Live Server
extension.

## Notes / things I'd improve

- Right now the C++ program is called as a subprocess for every request,
  which works but isn't the most efficient way to do this — a proper
  approach would be exposing the C++ logic directly over a socket instead
  of going through the console each time.
- Data is stored in a flat text file. Switching to SQLite would make it
  easier to query and less error-prone than manually parsing lines.
- No authentication yet — anyone with access to the page can access any
  account.
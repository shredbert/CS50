-- Turn on FKs
-- PRAGMA foreign_keys = ON;

-- Record buys & sales of stocks
CREATE TABLE stock_transactions (
    id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    user_id INTEGER NOT NULL,
    transaction_type TEXT NOT NULL CHECK(transaction_type IN ("buy", "sell")),
    stock_symbol TEXT NOT NULL,
    number_of_shares INTEGER NOT NULL CHECK(number_of_shares > 0),
    stock_price REAL NOT NULL CHECK(stock_price > 0),
    transaction_price GENERATED ALWAYS AS(number_of_shares * stock_price)
        STORED NOT NULL,
    transaction_time TEXT NOT NULL DEFAULT (DATETIME('now')),
    FOREIGN KEY(user_id) REFERENCES users(id)
);

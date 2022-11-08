CREATE TABLE purchases (
    id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    user_id INTEGER NOT NULL,
    stock_symbol TEXT NOT NULL,
    number_of_shares INTEGER NOT NULL CHECK(number_of_shares > 0),
    stock_price REAL NOT NULL CHECK(stock_price > 0)
        CHECK(stock_price = ROUND(stock_price, 2)),
    transaction_time TEXT NOT NULL DEFAULT (DATETIME('now')),
    transaction_price GENERATED ALWAYS AS(number_of_shares * stock_price)
        STORED NOT NULL,
    FOREIGN KEY(user_id) REFERENCES users(id)
)

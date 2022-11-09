-- -- Test data
-- INSERT INTO users (id, username, hash)
-- VALUES (1, 'test', 123456);

-- Valid
INSERT INTO purchases (user_id, stock_symbol, number_of_shares, stock_price)
VALUES (1, 'NFLX', 3, 5.00);

-- Errors

-- -- Error for no FK
-- INSERT INTO purchases (stock_symbol, number_of_shares, stock_price)
-- VALUES ('NFLX', 3, 5);

-- -- Error for invalid FK
-- INSERT INTO purchases (user_id, stock_symbol, number_of_shares, stock_price)
-- VALUES (100, 'NFLX', 3, 5);

-- -- Error for no symbol
-- INSERT INTO purchases (user_id, number_of_shares, stock_price)
-- VALUES (1, 3, 5);

-- -- Error for no # shares
-- INSERT INTO purchases (user_id, stock_symbol, stock_price)
-- VALUES (1, 'NFLX', 5);

-- -- Error for no stock price
-- INSERT INTO purchases (user_id, stock_symbol, number_of_shares)
-- VALUES (1, 'NFLX', 3);

-- -- Error for # shares not being > 0
-- INSERT INTO purchases (user_id, stock_symbol, number_of_shares, stock_price)
-- VALUES (1, 'NFLX', 0, 5);

-- -- Error for stock price not being > 0
-- INSERT INTO purchases (user_id, stock_symbol, number_of_shares, stock_price)
-- VALUES (1, 'NFLX', 3, 0);


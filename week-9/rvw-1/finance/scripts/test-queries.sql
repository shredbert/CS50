SELECT DISTINCT stock_symbol, 
CAST(
    (
        (TOTAL(number_of_shares) FILTER(WHERE transaction_type = 'buy')) - 
        (TOTAL(number_of_shares) FILTER(WHERE transaction_type = 'sell'))
    ) AS INT
) AS total_shares 
FROM stock_transactions 
WHERE user_id = 3
GROUP BY stock_symbol 
HAVING stock_symbol = 'NFLX'
AND (
    (TOTAL(number_of_shares) FILTER(WHERE transaction_type = 'buy')) - 
    (TOTAL(number_of_shares) FILTER(WHERE transaction_type = 'sell'))
) > 0;

SELECT DISTINCT stock_symbol, 
(TOTAL(number_of_shares) FILTER(
WHERE transaction_type = 'buy'
)) - (TOTAL(number_of_shares) FILTER(
WHERE transaction_type = 'sell'
)) AS total_shares 
FROM stock_transactions 
WHERE user_id = 4
GROUP BY stock_symbol
HAVING (
(TOTAL(number_of_shares) 
 FILTER(WHERE transaction_type = 'buy')) - 
(TOTAL(number_of_shares) 
 FILTER(WHERE transaction_type = 'sell'))
) > 0;

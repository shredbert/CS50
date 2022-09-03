-- Keep a log of any SQL queries you execute as you solve the mystery.

/*
Find crime scene report for theft on 2021/07/28 on Humphrey Street
*/

SELECT street, description
FROM crime_scene_reports
WHERE year = 2021
    AND month = 07
    AND day = 28
    AND street = 'Humphrey Street'
    AND description LIKE '%theft%';

/*
RESULTS:
- theft occurred at 10:15AM
- 3 witnesses interviewed same day, each *mentions bakery*
*/

/*
Find 3 interviews of witnesses to crime noted in crime scene report -> each
mentioned *bakery*
*/

SELECT name, transcript
FROM interviews
WHERE year = 2021
    AND month = 07
    AND day = 28
    AND transcript LIKE '%bakery%';

/*
RESULTS:
- Ruth saw thief leave within 10 minutes of the theft from bakery parking lot
- Eugene saw thief withdraw from ATM that morning on Leggett Street
- Raymond heard thief have a <1 min phone convo
- Raymond heard thief leaving on earliest flight out of Fiftyville on following
day
*/

/*
Get name based on:
- License plates matching those from bakery security logs within 10 min of
robbery (2021/07/28, from 10:15-10:25)
- Name of bank account holders that made withdrawals from ATM on Leggett Street
before 10:15AM on 2021/07/28
- Passport numbers of passengers on first flight out of Fiftyville on
2021/07/29
- Names of callers after theft on 2021/07/29 with duration <60 sec
*/

SELECT p.name
FROM people AS p
-- License plates from bakery security logs within 10 min of theft
WHERE p.license_plate IN
    (SELECT license_plate
    FROM bakery_security_logs
    WHERE year = 2021
    AND month = 07
    AND day = 28
    AND hour = 10
    AND minute BETWEEN 15 AND 25
    AND activity = 'exit')
-- Names of account holders making ATM withdrawals on Leggett Street before
-- theft
AND p.name IN
    (SELECT p.name
    FROM people AS p
        JOIN bank_accounts AS b
            ON p.id = b.person_id

        JOIN atm_transactions AS t
            ON b.account_number = t.account_number
    WHERE t.year = 2021
    AND t.month = 07
    AND t.day = 28
    AND t.atm_location = 'Leggett Street'
    AND t.transaction_type = 'withdraw')
-- Passport numbers from first flight on 2021/07/29
AND p.passport_number IN
    (SELECT p.passport_number
    FROM people AS p
        JOIN passengers AS ps
            ON ps.passport_number = p.passport_number

    -- ID of first flight leaving from Fiftyville on 2021/07/29
    WHERE ps.flight_id = 
        (SELECT f.id
        FROM flights AS f
            JOIN airports AS a
                ON a.id = f.origin_airport_id

        WHERE a.city = 'Fiftyville'
        AND f.year = 2021
        AND f.month = 7
        AND f.day = 29
        ORDER BY hour, minute
        LIMIT 1))
-- Phone numbers of callers with conversations of <60 sec
AND p.phone_number IN
    (SELECT c.caller
    FROM phone_calls AS c
    WHERE c.year = 2021
    AND c.month = 7
    AND c.day = 28
    AND c.duration < 60);

/*
Results:
- Bruce
*/

/*
Get destination city based on:
- Destination of first flight out of Fiftyville on 2021/07/29
*/

SELECT a.city
FROM airports AS a
    JOIN flights AS f
        ON a.id = f.destination_airport_id

WHERE f.id = 
    (SELECT f.id
    FROM flights AS f
        JOIN airports AS a
            ON a.id = f.origin_airport_id

    WHERE a.city = 'Fiftyville'
    AND f.year = 2021
    AND f.month = 7
    AND f.day = 29
    ORDER BY hour, minute
    LIMIT 1);

/*
Results:
- New York City
*/

/*
Get accomplice based on:
- Receiver of call after theft on 2021/07/29 with duration <60 sec
*/

SELECT p.name
FROM people AS p
    JOIN phone_calls AS c
        ON p.phone_number = c.receiver

WHERE c.id IN
    (SELECT c.id
    FROM phone_calls AS c
        JOIN people AS p
            ON p.phone_number = c.caller

    WHERE p.name = 'Bruce'
    AND c.year = 2021
    AND c.month = 7
    AND c.day = 28
    AND c.duration < 60);

/*
Results:
- Robin
*/

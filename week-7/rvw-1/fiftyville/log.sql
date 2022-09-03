-- Keep a log of any SQL queries you execute as you solve the mystery.

-- -- Find crime scene report for theft on 2021/07/28 on Humphrey Street
-- SELECT street, description
-- FROM crime_scene_reports
-- WHERE year = 2021
--     AND month = 07
--     AND day = 28
--     AND street = 'Humphrey Street'
--     AND description LIKE '%theft%';

/*
RESULTS:
- theft occurred at 10:15AM
- 3 witnesses interviewed same day, each *mentions bakery*
*/

-- -- Find 3 interviews of witnesses to crime noted in crime scene report -> each
-- -- mentioned *bakery*
-- SELECT name, transcript
-- FROM interviews
-- WHERE year = 2021
--     AND month = 07
--     AND day = 28
--     AND transcript LIKE '%bakery%';

/*
RESULTS:
- Ruth saw thief leave within 10 minutes of the theft from bakery parking lot
- Eugene saw thief withdraw from ATM that morning on Leggett Street
- Raymond heard <1 min phone convo -> leaving on earliest flight out of
Fiftyville on following day
*/

-- -- Review bakery security logs within 10 min of robbery (2021/07/28 @10:15)
-- SELECT hour, minute, activity, license_plate
-- FROM bakery_security_logs
-- WHERE year = 2021
--     AND month = 07
--     AND day = 28
--     AND hour = 10
--     AND minute BETWEEN 15 AND 25
--     AND activity = 'exit';

/*
RESULTS:
- possible license plates leaving between 10:15 & 10:25:
    - 5P2BI95
    - 94KL13X
    - 6P58WS2
    - 4328GD8
    - G412CB7
    - L93JTIZ
    - 322W7JE
    - 0NTHK55
*/

-- Check withdrawals from ATM on Leggett Street < 10:15AM
-- 8 bank accounts = 8 names?
-- Get names -> atm_transactions < bank_accounts < people
SELECT p.name, p.phone_number, p.passport_number, p.license_plate
FROM people AS p
    JOIN bank_accounts AS b
    ON p.id = b.person_id

    JOIN atm_transactions AS t
    ON b.account_number = t.account_number
WHERE t.year = 2021
    AND t.month = 07
    AND t.day = 28
    AND t.atm_location = 'Leggett Street'
    AND t.transaction_type = 'withdraw';

/*
RESULTS:
Bruce|(367) 555-5533|5773159633|94KL13X
Diana|(770) 555-1861|3592750733|322W7JE
Brooke|(122) 555-4581|4408372428|QX4YZN3
Kenny|(826) 555-1652|9878712108|30G67EN
Iman|(829) 555-5269|7049073643|L93JTIZ
Luca|(389) 555-5198|8496433585|4328GD8
Taylor|(286) 555-6063|1988161715|1106N58
Benista|(338) 555-6650|9586786673|8X428L0
*/

-- Check who's on earliest flight out of Fiftyville on 2021/07/29

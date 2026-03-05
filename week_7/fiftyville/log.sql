-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT * FROM crime_scene_reports
WHERE year = 2024 AND month = 7 AND day = 28 AND street = 'Humphrey Street';

SELECT * FROM interviews
WHERE year = 2024 AND month = 7 AND day = 28 AND transcript LIKE '%bakery%';

SELECT * FROM bakery_security_logs
WHERE year = 2024 AND month = 7 AND day = 28
  AND activity = 'exit'
  AND hour = 10 AND minute BETWEEN 15 AND 25;

SELECT * FROM atm_transactions
WHERE year = 2024 AND month = 7 AND day = 28
  AND atm_location = 'Leggett Street'
  AND transaction_type = 'withdraw';

SELECT * FROM phone_calls
WHERE year = 2024 AND month = 7 AND day = 28 AND duration < 60;

SELECT * FROM airports WHERE city = 'Fiftyville';

SELECT DISTINCT p.*
FROM people p
JOIN bank_accounts ba ON ba.person_id = p.id
JOIN passengers pa ON pa.passport_number = p.passport_number
WHERE ba.account_number IN (28500762, 28296815, 76054385, 49610011, 16153065, 25506511, 81061156, 26013199)
  AND pa.flight_id = 36
  AND p.license_plate IN ('5P2BI95', '94KL13X', '6P58WS2', '4328GD8', 'G412CB7', 'L93JTIZ', '322W7JE', '0NTHK55')
  AND p.phone_number IN ('(130) 555-0289', '(499) 555-9472', '(367) 555-5533',
                         '(286) 555-6063', '(770) 555-1861', '(031) 555-6622',
                         '(826) 555-1652', '(338) 555-6650');

SELECT * FROM phone_calls
WHERE caller = '(367) 555-5533'
  AND year = 2024 AND month = 7 AND day = 28
  AND duration < 60;

SELECT * FROM people WHERE phone_number = '(375) 555-8161';
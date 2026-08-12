-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Find the crime scene report for the theft on Humphrey Street.
SELECT *
FROM crime_scene_reports
WHERE year = 2025
  AND month = 7
  AND day = 28
  AND street = 'Humphrey Street';

-- Find the witness interviews mentioning the bakery.
SELECT *
FROM interviews
WHERE year = 2025
  AND month = 7
  AND day = 28
  AND transcript LIKE '%bakery%';

-- Find cars that exited the bakery parking lot within ten minutes of the theft.
SELECT *
FROM bakery_security_logs
WHERE year = 2025
  AND month = 7
  AND day = 28
  AND hour = 10
  AND minute BETWEEN 15 AND 25
  AND activity = 'exit';

-- Find the people who own those cars.
SELECT name, license_plate
FROM people
WHERE license_plate IN (
    '5P2BI95',
    '94KL13X',
    '6P58WS2',
    '4328GD8',
    'G412CB7',
    'L93JTIZ',
    '322W7JE',
    '0NTHK55'
);

-- Find withdrawals from the ATM on Leggett Street.
SELECT *
FROM atm_transactions
WHERE year = 2025
  AND month = 7
  AND day = 28
  AND atm_location = 'Leggett Street'
  AND transaction_type = 'withdraw';

-- Find the people who own those bank accounts.
SELECT people.name, bank_accounts.account_number
FROM people
JOIN bank_accounts
    ON people.id = bank_accounts.person_id
WHERE bank_accounts.account_number IN (
    28500762,
    28296815,
    76054385,
    49610011,
    16153065,
    25506511,
    81061156,
    26013199
);

-- Find phone calls lasting less than one minute on the day of the theft.
SELECT *
FROM phone_calls
WHERE year = 2025
  AND month = 7
  AND day = 28
  AND duration < 60;

-- Check which remaining suspects made short calls.
SELECT people.name, people.phone_number, phone_calls.receiver, phone_calls.duration
FROM people
JOIN phone_calls
    ON people.phone_number = phone_calls.caller
WHERE people.name IN ('Bruce', 'Diana', 'Iman', 'Luca')
  AND phone_calls.year = 2025
  AND phone_calls.month = 7
  AND phone_calls.day = 28
  AND phone_calls.duration < 60;

-- Find the earliest flight out of Fiftyville on July 29.
SELECT *
FROM flights
WHERE year = 2025
  AND month = 7
  AND day = 29
ORDER BY hour, minute
LIMIT 1;

-- Check whether Bruce or Diana was on the earliest flight.
SELECT people.name, passengers.passport_number
FROM passengers
JOIN people
    ON passengers.passport_number = people.passport_number
WHERE passengers.flight_id = 36
  AND people.name IN ('Bruce', 'Diana');

-- Find the city where Flight 36 arrived.
SELECT *
FROM airports
WHERE id = 4;

-- Find the person who owns the phone number Bruce called.
SELECT name, phone_number
FROM people
WHERE phone_number = '(375) 555-8161';

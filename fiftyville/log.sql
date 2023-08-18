-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Search if there was a crime scene reports in the same day of the theft:
SELECT * FROM crime_scene_reports
WHERE year = 2021 AND month = 07 AND day = 28;
-- crime_scene_reports.id ==> 295 / 10:15am at Humphrey Street bakery

-- Search for the interviews:
SELECT * FROM interviews
WHERE year = 2021 AND month = 07 AND day = 28;
-- Interviews ==> id 161: Parking lot, drive away (10min of the theft), look camera
               -- id 162: ATM on Leggett Street, thief was swithdrawing some money, in the morning before the theft
               -- id 163: Phone call less than 1 minute, earliest flight out of fiftyville tomorrow, thief ask person on phone to buy ticket

-- Search for info after interview for THE CAR:
SELECT * FROM bakery_security_logs
WHERE year = 2021 AND month = 07 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 30;
-- 8 cars exit the bakery in ten minutes of the theft, bakery_security_logs.id 260 to 267
-- Get the information of the people with the license plate:
SELECT * FROM people
JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate
WHERE bakery_security_logs.id >= 260 AND bakery_security_logs.id <= 267;

-- Search for info after interview for the ATM TRANSACTION:
SELECT * FROM atm_transactions
WHERE year = 2021 AND month = 07 AND day = 28 AND atm_location = "Leggett Street";
-- 8 whithdraw (all less than 80) this day and 1 deposit (10)

--Get the 9 persons info from the account_number:
SELECT * FROM people
JOIN bank_accounts ON bank_accounts.person_id = people.id
WHERE account_number IN (SELECT account_number FROM atm_transactions
WHERE year = 2021 AND month = 07 AND day = 28 AND atm_location = "Leggett Street");

-- Search for info after interview for the PHONE CALL:
SELECT * FROM phone_calls
WHERE year = 2021 AND month = 07 AND day = 28 AND duration < 60;
-- 9 calls less than 1 minute this day

-- Is there a caller that was in the parking in Baker street:
SELECT phone_number FROM (SELECT phone_number FROM people
JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate
WHERE bakery_security_logs.id >= 260 AND bakery_security_logs.id <= 267)
WHERE phone_number IN(SELECT caller FROM phone_calls
WHERE year = 2021 AND month = 07 AND day = 28 AND duration < 60);
-- 4 phone calls less than 1 minute that left the bakery parking less than 10 min of he theft

-- Get info on the 4 person that did a phone call and left the bakery:
SELECT * FROM people
WHERE phone_number IN(SELECT phone_number FROM (SELECT phone_number FROM people
JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate
WHERE bakery_security_logs.id >= 260 AND bakery_security_logs.id <= 267)
WHERE phone_number IN(SELECT caller FROM phone_calls
WHERE year = 2021 AND month = 07 AND day = 28 AND duration < 60));

-- Was one of the four at the atm the morning of the theft:
SELECT * FROM people
WHERE people.id IN (SELECT people.id FROM people
WHERE phone_number IN(SELECT phone_number FROM (SELECT phone_number FROM people
JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate
WHERE bakery_security_logs.id >= 260 AND bakery_security_logs.id <= 267)
WHERE phone_number IN(SELECT caller FROM phone_calls
WHERE year = 2021 AND month = 07 AND day = 28 AND duration < 60)))
AND people.id IN ((SELECT people.id FROM people
JOIN bank_accounts ON bank_accounts.person_id = people.id
WHERE account_number IN (SELECT account_number FROM atm_transactions
WHERE year = 2021 AND month = 07 AND day = 28 AND atm_location = "Leggett Street")));
-- Only 1 person : people.id 686048
-- Bruce info:
SELECT * FROM people
WHERE people.id = 686048;

-- Who this person call this morning ?
SELECT * FROM people
WHERE phone_number IN (SELECT receiver FROM phone_calls
WHERE year = 2021 AND month = 07 AND day = 28 AND duration < 60 AND caller = "(367) 555-5533");
-- Bruce called Robin : people.id 864400

-- Robin info:
SELECT * FROM people
where people.id = 864400;

--What did Bruce at he the ATM:
SELECT * FROM atm_transactions
WHERE account_number = 49610011 AND account_number IN (SELECT account_number FROM people
JOIN bank_accounts ON bank_accounts.person_id = people.id
WHERE account_number IN (SELECT account_number FROM atm_transactions
WHERE year = 2021 AND month = 07 AND day = 28 AND atm_location = "Leggett Street"));

-- Did bruce take a flight:
SELECT * FROM passengers
WHERE passport_number IN (SELECT passport_number FROM people WHERE people.id = 686048);
-- YES

-- Search info the flight:
SELECT * FROM flights
WHERE flights.id IN (SELECT flight_id FROM passengers
WHERE passport_number IN (SELECT passport_number FROM people WHERE people.id = 686048));

-- Search info of the ariports:
SELECT * FROM airports
WHERE id IN (SELECT destination_airport_id FROM flights
WHERE flights.id IN (SELECT flight_id FROM passengers
WHERE passport_number IN (SELECT passport_number FROM people WHERE people.id = 686048)));

-- Bruce went to New York City

-- Did Robin bought a ticket for Bruce?
SELECT * FROM bank_accounts
WHERE person_id IN (SELECT people.id FROM people
where people.id = 864400);

SELECT * FROM atm_transactions
WHERE account_number IN (SELECT account_number FROM bank_accounts
WHERE person_id IN (SELECT people.id FROM people
where people.id = 864400));

-- We don't know
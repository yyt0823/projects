-- Keep a log of any SQL queries you execute as you solve the mystery.

select day, year, month
from crime_scene_reports
where year = 2021 and month = 7 and day = 28;



select description
from crime_scene_reports
where year = 2021 and month = 7 and day = 28 and street = "Humphrey Street";
--Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
    --Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.
--Littering took place at 16:36. No known witnesses.

select *
from interviews
where transcript LIKE '%bakery%' and year = 2021 and month = 7 and day = 28;

-- within ten minutes of the theft, security footage from the bakery parking lot, drive away        checked
-- In shop, whispering into a phone for about half an hour                                          checked
-- Earlier this morning , ATM on Leggett Street, thief there withdrawing some money.                checked
-- when leaving the bakery, planning to take the earliest flight out of Fiftyville tomorrow         checked

-- security footage
select *
from bakery_security_logs
where year = 2021 and month = 7 and day = 28;

-- license_plate
select name
from bakery_security_logs
join people
on bakery_security_logs.license_plate = people.license_plate
where year = 2021 and month = 7 and day = 28 and hour >= 10 and hour <= 11 and minute < 25 and minute > 15 and activity = "exit";
-- +---------+
-- | Vanessa |
-- | Bruce   |
-- | Barry   |
-- | Luca    |
-- | Sofia   |
-- | Iman    |
-- | Diana   |
-- | Kelsey  |
-- +---------+

--account_number
select *
from atm_transactions
where year = 2021 and month = 7 and day = 28;

select name
from atm_transactions
join bank_accounts on atm_transactions.account_number = bank_accounts.account_number
join people on bank_accounts.person_id = people.id
where year = 2021 and month = 7 and day = 28 and transaction_type = "withdraw" and atm_location = "Leggett Street";
-- +---------+
-- | Bruce   |
-- | Diana   |
-- | Brooke  |
-- | Kenny   |
-- | Iman    |
-- | Luca    |
-- | Taylor  |
-- | Benista |
-- +---------+

--caller
select *
from phone_calls
where year = 2021 and month = 7 and day = 28 and duration < 60 ;

select name
from phone_calls
join people
on people.phone_number = phone_calls.caller
where year = 2021 and month = 7 and day = 28 and duration < 60 ;
-- +---------+
-- | Sofia   |
-- | Kelsey  |
-- | Bruce   |
-- | Kelsey  |
-- | Taylor  |
-- | Diana   |
-- | Carina  |
-- | Kenny   |
-- | Benista |
-- +---------+

--airports
select *
from airports
where city = "Fiftyville";
--airport id = 8

--flight
select *
from flights
where origin_airport_id = 8 and year = 2021 and month = 7 and day = 29
order by hour
limit 1;
--flight id = 36

--passangers
select name
from passengers
join people on people.passport_number = passengers.passport_number
where passengers.flight_id = 36;


--destination_airport
select city
from airports
join flights
on airports.id = 4
limit 1;
--destination_airport is LaGuardia Airport
--city is NYC




--THIEF
select name
from people
where name in (select name from phone_calls join people on people.phone_number = phone_calls.caller where year = 2021 and month = 7 and day = 28 and duration < 60)
and name in (select name from atm_transactions join bank_accounts on atm_transactions.account_number = bank_accounts.account_number join people on bank_accounts.person_id = people.id where year = 2021 and month = 7 and day = 28 and transaction_type = "withdraw" and atm_location = "Leggett Street")
and name in (select name from bakery_security_logs join people on bakery_security_logs.license_plate = people.license_plate where year = 2021 and month = 7 and day = 28 and hour >= 10 and hour <= 11 and minute < 25 and minute > 15 and activity = "exit")
and name in (select name from passengers join people on people.passport_number = passengers.passport_number where passengers.flight_id = 36);
--Bruce

--ACCOMPLICE
select receiver
from phone_calls
join people
on people.phone_number = phone_calls.caller
where year = 2021 and month = 7 and day = 28 and duration < 60 and name = "Bruce";

select name
from people
join (select receiver from phone_calls join people on people.phone_number = phone_calls.caller where year = 2021 and month = 7 and day = 28 and duration < 60 and name = "Bruce") on people.phone_number = receiver;

--Robin

#!/usr/bin/env python3
import random

MONTH_NAME = [
    "",
    "JAN",
    "FEB",
    "MAR",
    "APR",
    "MAY",
    "JUN",
    "JUL",
    "AUG",
    "SEP",
    "OCT",
    "NOV",
    "DEC",
]

MONTH_DAY = (
    (0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31),
    (0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31),
)


def is_julian_leap(year: int) -> bool:
    return year % 4 == 0


def is_gregorian_leap(year: int) -> bool:
    if year % 400 == 0:
        return True
    if year % 100 == 0:
        return False
    return year % 4 == 0


def get_month_day(year: int, month: int) -> int:
    leap = 0
    if year < 1582:
        leap = 1 if is_julian_leap(year) else 0
    elif year > 1582:
        leap = 1 if is_gregorian_leap(year) else 0
    return MONTH_DAY[leap][month]


def random_date():
    special_years = [1, 4, 100, 400, 1581, 1582, 1583, 1600, 1700, 1900, 2000]
    if random.randint(1, 100) <= 35:
        year = random.choice(special_years)
    else:
        year = random.randint(1, 2500)

    month = random.randint(1, 12)
    if year == 1582 and month == 10:
        day = random.choice(list(range(1, 5)) + list(range(15, 32)))
    else:
        day = random.randint(1, get_month_day(year, month))

    return day, month, year


def main():
    random.seed()
    day, month, year = random_date()
    print(f"{day}{MONTH_NAME[month]}{year}")


if __name__ == "__main__":
    main()

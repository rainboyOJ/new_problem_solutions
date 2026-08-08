#!/usr/bin/env python3
import random


def is_leap(year):
    if year % 400 == 0:
        return True
    if year % 100 == 0:
        return False
    return year % 4 == 0


def days_in_month(year, month):
    if month in (1, 3, 5, 7, 8, 10, 12):
        return 31
    if month in (4, 6, 9, 11):
        return 30
    return 29 if is_leap(year) else 28


def next_day(year, month, day):
    day += 1
    if day <= days_in_month(year, month):
        return year, month, day
    day = 1
    month += 1
    if month <= 12:
        return year, month, day
    return year + 1, 1, 1


def format_date(year, month, day):
    return f"{year:04d}{month:02d}{day:02d}"


def random_date():
    year = random.randint(0, 3000)
    month = random.randint(1, 12)
    day = random.randint(1, days_in_month(year, month))
    return year, month, day


def main():
    random.seed()
    year, month, day = random_date()
    left = format_date(year, month, day)

    span = random.randint(0, 2500)
    for _ in range(span):
        year, month, day = next_day(year, month, day)
    right = format_date(year, month, day)

    print(left)
    print(right)


if __name__ == "__main__":
    main()

year, month, day = map(int, input().split("-"))


def is_leap(current_year: int) -> bool:
    return current_year % 400 == 0 or current_year % 4 == 0 and current_year % 100 != 0


month_lengths = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
month_lengths[1] += is_leap(year)
day += 1
if day > month_lengths[month - 1]:
    day = 1
    month += 1
    if month == 13:
        month = 1
        year += 1

print(f"{year:04d}-{month:02d}-{day:02d}")

def days_before_year(year: int) -> int:
    year -= 1
    return 365 * year + year // 4 - year // 100 + year // 400


def is_leap(year: int) -> bool:
    return year % 400 == 0 or year % 4 == 0 and year % 100 != 0


month_lengths = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
case_count = int(input())

for _ in range(case_count):
    clock, date = input().split()
    hour, minute, second = map(int, clock.split(":"))
    day, month, year = map(int, date.split("."))
    days = days_before_year(year) - days_before_year(2000)
    days += sum(month_lengths[: month - 1]) + (month > 2 and is_leap(year)) + day - 1
    special_year, special_day = divmod(days, 1000)
    ordinary_seconds = hour * 3600 + minute * 60 + second
    # 两种历法的“一天”等长，日内的 86400 个普通秒按比例映射为 100000 个特殊秒。
    remaining = ordinary_seconds * 100_000 // 86_400
    special_hour, remaining = divmod(remaining, 10_000)
    special_minute, special_second = divmod(remaining, 100)
    print(f"{special_hour}:{special_minute}:{special_second} {special_day % 100 + 1}.{special_day // 100 + 1}.{special_year}")

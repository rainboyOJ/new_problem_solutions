def is_leap_year(year):
    return year % 400 == 0 or (year % 4 == 0 and year % 100 != 0)

start, end = map(int, input().split())
years = [year for year in range(start, end + 1) if is_leap_year(year)]

print(len(years))
print(*years)

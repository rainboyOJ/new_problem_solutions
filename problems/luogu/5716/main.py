y, m = map(int, input().split())

is_leap = (y % 4 == 0 and y % 100 != 0) or (y % 400 == 0)
days = [31, 29 if is_leap else 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]

print(days[m - 1], end="")

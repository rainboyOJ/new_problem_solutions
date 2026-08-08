x, n = map(int, input().split())

full_weeks, rest_days = divmod(n, 7)
work_days = full_weeks * 5

for i in range(rest_days):
    weekday = (x + i - 1) % 7 + 1
    if weekday <= 5:
        work_days += 1

print(work_days * 250, end="")

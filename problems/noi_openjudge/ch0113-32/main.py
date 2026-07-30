from datetime import date, timedelta

elapsed_days = int(input())
current = date(2000, 1, 1) + timedelta(days=elapsed_days)
weekdays = ["Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"]

print(f"{current:%Y-%m-%d} {weekdays[current.weekday()]}")

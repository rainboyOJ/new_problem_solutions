import calendar

year, month = map(int, input().split())
weeks = calendar.Calendar(firstweekday=6).monthdayscalendar(year, month)

print("Sun Mon Tue Wed Thu Fri Sat")
for week in weeks:
    print(" ".join(f"{day:3d}" if day else "   " for day in week).rstrip())

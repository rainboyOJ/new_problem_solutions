year = int(input())
is_leap = year % 4 == 0 and (year % 100 != 0 or year % 400 == 0) and year % 3200 != 0
print("Y" if is_leap else "N")

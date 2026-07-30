haab_months = ["pop", "no", "zip", "zotz", "tzec", "xul", "yoxkin", "mol", "chen", "yax", "zac", "ceh", "mac", "kankin", "muan", "pax", "koyab", "cumhu", "uayet"]
tzolkin_days = ["imix", "ik", "akbal", "kan", "chicchan", "cimi", "manik", "lamat", "muluk", "ok", "chuen", "eb", "ben", "ix", "mem", "cib", "caban", "eznab", "canac", "ahau"]
month_index = {month: index for index, month in enumerate(haab_months)}

count = int(input())
print(count)
for _ in range(count):
    day, month, year = input().split()
    total_days = int(year) * 365 + month_index[month] * 20 + int(day[:-1])
    print(total_days % 13 + 1, tzolkin_days[total_days % 20], total_days // 260)

from math import ceil

s, v = map(int, input().split())
need = ceil(s / v) + 10

latest = (8 * 60 - need) % (24 * 60)
hour, minute = divmod(latest, 60)

print(f"{hour:02d}:{minute:02d}", end="")

from math import ceil
s, v = map(int, input().split())
h, m = divmod((8 * 60 - (ceil(s / v) + 10)) % (24 * 60), 60)
print(f'{h:02d}:{m:02d}', end='')

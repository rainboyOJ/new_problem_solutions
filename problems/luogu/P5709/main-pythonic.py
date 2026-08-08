from math import ceil
m, t, s = map(int, input().split())
print(0 if t == 0 else max(0, m - ceil(s / t)), end='')

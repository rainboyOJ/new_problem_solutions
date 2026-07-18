from math import ceil

m, t, s = map(int, input().split())

if t == 0:
    print(0, end="")
else:
    eaten = ceil(s / t)
    print(max(0, m - eaten), end="")

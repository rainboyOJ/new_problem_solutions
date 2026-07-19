from math import gcd
a, b, c = sorted(map(int, input().split()))
g = gcd(a, c)
print(f'{a // g}/{c // g}')

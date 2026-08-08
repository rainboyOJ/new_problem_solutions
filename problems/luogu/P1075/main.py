from math import isqrt


n = int(input())

for d in range(2, isqrt(n) + 1):
    if n % d == 0:
        print(n // d)
        break

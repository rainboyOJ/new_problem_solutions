from math import gcd
a, b = map(int, input().split())
print(4 * (a + b - gcd(a, b)))

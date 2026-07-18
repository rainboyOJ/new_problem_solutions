from math import gcd

length, width = map(int, input().split())
print(4 * (length + width - gcd(length, width)))

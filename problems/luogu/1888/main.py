from math import gcd

sides = sorted(map(int, input().split()))
numerator = sides[0]
denominator = sides[2]

g = gcd(numerator, denominator)
print(f"{numerator // g}/{denominator // g}", end="")

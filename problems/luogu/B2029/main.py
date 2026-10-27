import math


h, r = map(int, input().split())
bucket = 3.14 * r * r * h / 1000
print(math.ceil(20 / bucket))

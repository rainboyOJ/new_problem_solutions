import math

height, radius = map(int, input().split())
bucket_volume = 3.14159 * radius * radius * height
print(math.ceil(20000 / bucket_volume))

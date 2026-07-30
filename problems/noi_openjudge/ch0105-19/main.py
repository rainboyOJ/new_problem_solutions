import math

rooftop_count = int(input())
total_time = 0.0

for _ in range(rooftop_count):
    x, y, people = map(float, input().split())
    total_time += 2 * math.hypot(x, y) / 50 + people * 1.5

print(math.ceil(total_time))

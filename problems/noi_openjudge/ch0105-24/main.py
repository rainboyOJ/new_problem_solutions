measurement_count = int(input())
current = longest = 0

for _ in range(measurement_count):
    systolic, diastolic = map(int, input().split())
    if 90 <= systolic <= 140 and 60 <= diastolic <= 90:
        current += 1
        longest = max(longest, current)
    else:
        current = 0

print(longest)

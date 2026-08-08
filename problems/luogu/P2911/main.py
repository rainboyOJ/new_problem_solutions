s1, s2, s3 = map(int, input().split())

count = [0] * (s1 + s2 + s3 + 1)

for a in range(1, s1 + 1):
    for b in range(1, s2 + 1):
        for c in range(1, s3 + 1):
            count[a + b + c] += 1

best_sum = 0
best_count = -1

for total, times in enumerate(count):
    if times > best_count:
        best_count = times
        best_sum = total

print(best_sum)

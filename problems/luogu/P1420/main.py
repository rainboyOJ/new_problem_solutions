n = int(input())
numbers = list(map(int, input().split()))

best = 1
current = 1

for i in range(1, n):
    if numbers[i] == numbers[i - 1] + 1:
        current += 1
    else:
        current = 1
    best = max(best, current)

print(best)

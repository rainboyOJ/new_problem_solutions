left, right = map(int, input().split())

count = [0] * 10

for value in range(left, right + 1):
    for digit in str(value):
        count[int(digit)] += 1

print(*count)

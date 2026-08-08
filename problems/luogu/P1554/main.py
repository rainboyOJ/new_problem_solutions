left, right = map(int, input().split())

count = [0] * 10

for value in range(left, right + 1):
    x = value
    while True:
        count[x % 10] += 1
        x //= 10
        if x == 0:
            break

print(*count)

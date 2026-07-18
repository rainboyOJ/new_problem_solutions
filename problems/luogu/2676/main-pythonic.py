import sys

data = list(map(int, sys.stdin.buffer.read().split()))
n = data[0]
target = data[1]
heights = data[2:2 + n]
heights.sort(reverse=True)

total = 0
count = 0

for height in heights:
    total += height
    count += 1
    if total >= target:
        break

print(count)

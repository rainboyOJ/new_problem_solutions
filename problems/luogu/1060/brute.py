import sys

data = list(map(int, sys.stdin.buffer.read().split()))
n, m = data[0], data[1]
items = []
idx = 2
for _ in range(m):
    v, p = data[idx], data[idx + 1]
    idx += 2
    items.append((v, p))

best = 0
for mask in range(1 << m):
    cost = 0
    value = 0
    for i in range(m):
        if mask >> i & 1:
            v, p = items[i]
            cost += v
            value += v * p
    if cost <= n:
        best = max(best, value)

print(best)

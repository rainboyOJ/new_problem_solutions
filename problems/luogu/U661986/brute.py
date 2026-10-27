#!/usr/bin/env python3
import sys
data = list(map(int, sys.stdin.buffer.read().split()))
n, V = data[0], data[1]
items = [(data[i], data[i + 1]) for i in range(2, len(data), 2)]

ans = 0
for mask in range(1 << n):
    w = val = 0
    for i in range(n):
        if mask >> i & 1:
            w += items[i][0]
            val += items[i][1]
    if w <= V and val > ans:
        ans = val
print(ans)

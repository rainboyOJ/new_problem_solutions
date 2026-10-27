#!/usr/bin/env python3
import sys
MOD = 10 ** 9 + 7
data = list(map(int, sys.stdin.buffer.read().split()))
n, V = data[0], data[1]
vols = data[2:]

cnt = 0
for mask in range(1 << n):
    total = 0
    for i in range(n):
        if mask >> i & 1:
            total += vols[i]
    if total == V:
        cnt += 1
print(cnt % MOD)

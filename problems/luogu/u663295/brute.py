#!/usr/bin/env python3
import sys
data = list(map(int, sys.stdin.buffer.read().split()))
n, V = data[0], data[1]
vols = data[2:]

for mask in range(1 << n):
    total = 0
    for i in range(n):
        if mask >> i & 1:
            total += vols[i]
    if total == V:
        print("true")
        sys.exit()
print("false")

#!/usr/bin/env python3
import sys

data = list(map(int, sys.stdin.buffer.read().split()))
n, V = data[0], data[1]
v = data[2:2 + 2 * n:2]
w = data[3:3 + 2 * n:2]

best_val = 0
best_schemes = []

for mask in range(1 << n):
    total_v = 0
    total_w = 0
    scheme = []
    for i in range(n):
        if mask >> i & 1:
            total_v += v[i]
            total_w += w[i]
            scheme.append(i + 1)
    if total_v > V:
        continue
    if total_w > best_val:
        best_val = total_w
        best_schemes = [scheme]
    elif total_w == best_val:
        best_schemes.append(scheme)

best_schemes.sort()
for scheme in best_schemes:
    if scheme:
        print(*scheme)
    else:
        print()

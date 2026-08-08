import sys
from itertools import combinations

data = list(map(int, sys.stdin.buffer.read().split()))
n, p, S = data[0], data[1], data[2]
files = []
idx = 3
for _ in range(n):
    w, v = data[idx], data[idx + 1]
    idx += 2
    files.append((w, v))

best_L = 10**9
for mask in range(1 << n):
    total_w = 0
    total_v = 0
    max_file_w = 0
    for i in range(n):
        if mask >> i & 1:
            w, v = files[i]
            total_w += w
            total_v += v
            max_file_w = max(max_file_w, w)
    if total_w <= S and total_v >= p:
        best_L = min(best_L, max_file_w)

if best_L == 10**9:
    print('No Solution!')
else:
    print(best_L)

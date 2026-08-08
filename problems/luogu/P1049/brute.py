from itertools import combinations
import sys

data = list(map(int, sys.stdin.buffer.read().split()))
V = data[0]
n = data[1]
volumes = data[2:2 + n]

best_used = 0
for r in range(n + 1):
    for chosen in combinations(volumes, r):
        s = sum(chosen)
        if s <= V and s > best_used:
            best_used = s
print(V - best_used)

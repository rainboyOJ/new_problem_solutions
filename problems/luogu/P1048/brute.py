from itertools import combinations
import sys

data = list(map(int, sys.stdin.buffer.read().split()))
T, M = data[0], data[1]
herbs = list(zip(data[2::2], data[3::2]))

ans = 0
for r in range(M + 1):
    for chosen in combinations(herbs, r):
        total_time = sum(t for t, _ in chosen)
        if total_time <= T:
            ans = max(ans, sum(v for _, v in chosen))
print(ans)

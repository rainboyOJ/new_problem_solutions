import sys
from itertools import combinations


MOD = 1_000_000_007

data = list(map(int, sys.stdin.buffer.read().split()))
n = data[0]
sticks = data[1:1 + n]

answer = 0
for chosen in combinations(sticks, 4):
    a, b, c, d = sorted(chosen)
    if a + b == c == d:
        answer += 1

print(answer % MOD)

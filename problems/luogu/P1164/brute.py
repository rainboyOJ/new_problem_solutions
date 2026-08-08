from itertools import combinations
import sys


data = list(map(int, sys.stdin.buffer.read().split()))
n, target = data[0], data[1]
prices = data[2:2 + n]
answer = 0
for size in range(n + 1):
    answer += sum(sum(chosen) == target for chosen in combinations(prices, size))
print(answer)

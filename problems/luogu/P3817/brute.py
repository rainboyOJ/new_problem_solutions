from itertools import product
import sys


def greedy(n, x, candies):
    candies = candies[:]
    answer = 0
    for i in range(1, n):
        extra = candies[i - 1] + candies[i] - x
        if extra > 0:
            eat = min(extra, candies[i])
            candies[i] -= eat
            answer += eat
            extra -= eat
            if extra > 0:
                candies[i - 1] -= extra
                answer += extra
    return answer


data = list(map(int, sys.stdin.buffer.read().split()))
n, x = data[0], data[1]
a = data[2:2 + n]

state_count = 1
for value in a:
    state_count *= value + 1

if state_count > 300000:
    print(greedy(n, x, a))
else:
    best_keep = 0
    for remain in product(*(range(value + 1) for value in a)):
        if all(remain[i] + remain[i + 1] <= x for i in range(n - 1)):
            best_keep = max(best_keep, sum(remain))
    print(sum(a) - best_keep)

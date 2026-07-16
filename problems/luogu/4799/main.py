import sys
from bisect import bisect_right


n, budget = map(int, sys.stdin.buffer.readline().split())
prices = list(map(int, sys.stdin.buffer.readline().split()))


def subset_sums(values):
    sums = [0]
    for value in values:
        sums += [total + value for total in sums if total + value <= budget]
    return sums


middle = n // 2
left = subset_sums(prices[:middle])
right = sorted(subset_sums(prices[middle:]))
print(sum(bisect_right(right, budget - total) for total in left))

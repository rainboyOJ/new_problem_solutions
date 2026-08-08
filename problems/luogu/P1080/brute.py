from itertools import permutations
import sys


def score(order, king_left):
    prefix = king_left
    worst = 0
    for left, right in order:
        worst = max(worst, prefix // right)
        prefix *= left
    return worst


def greedy(ministers, king_left):
    return score(sorted(ministers, key=lambda item: item[0] * item[1]), king_left)


data = list(map(int, sys.stdin.buffer.read().split()))
n = data[0]
king_left = data[1]
ministers = [(data[i], data[i + 1]) for i in range(3, len(data), 2)]

if n > 8:
    print(greedy(ministers, king_left))
else:
    print(min(score(order, king_left) for order in permutations(ministers)))

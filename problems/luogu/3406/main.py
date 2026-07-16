import sys
from itertools import accumulate, pairwise


data = iter(map(int, sys.stdin.buffer.read().split()))
n, m = next(data), next(data)
route = [next(data) for _ in range(m)]
difference = [0] * (n + 1)
for start, end in pairwise(route):
    left, right = sorted((start, end))
    difference[left] += 1
    difference[right] -= 1

uses = accumulate(difference)
answer = 0
for count in list(uses)[1:n]:
    paper, card, cost = next(data), next(data), next(data)
    answer += min(count * paper, count * card + cost)
print(answer)

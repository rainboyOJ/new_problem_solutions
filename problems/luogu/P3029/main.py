import sys
from collections import Counter


data = iter(map(int, sys.stdin.buffer.read().split()))
n = next(data)
cows = sorted((next(data), next(data)) for _ in range(n))
required = len({breed for _, breed in cows})
counts = Counter()
answer = 10**30
left = 0

for right, (position, breed) in enumerate(cows):
    counts[breed] += 1
    while len(counts) == required:
        answer = min(answer, position - cows[left][0])
        left_breed = cows[left][1]
        counts[left_breed] -= 1
        if not counts[left_breed]:
            del counts[left_breed]
        left += 1

print(answer)

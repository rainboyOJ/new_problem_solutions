import sys


data = iter(map(int, sys.stdin.buffer.read().split()))
n, limit = next(data), next(data)
diamonds = sorted(data)
right = [0] * n
j = 0
for i, smallest in enumerate(diamonds):
    j = max(j, i)
    while j + 1 < n and diamonds[j + 1] - smallest <= limit:
        j += 1
    right[i] = j

best_suffix = [0] * (n + 1)
for i in range(n - 1, -1, -1):
    best_suffix[i] = max(best_suffix[i + 1], right[i] - i + 1)

print(max(right[i] - i + 1 + best_suffix[right[i] + 1] for i in range(n)))

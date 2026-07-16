import sys


data = iter(map(int, sys.stdin.buffer.read().split()))
n = next(data)
values = [next(data) for _ in range(n)]
rank = {value: i + 1 for i, value in enumerate(sorted(set(values)))}
tree = [0] * (len(rank) + 1)
answer = 0

for seen, value in enumerate(values):
    index = rank[value]
    prefix = 0
    i = index
    while i:
        prefix += tree[i]
        i -= i & -i
    answer += seen - prefix
    while index < len(tree):
        tree[index] += 1
        index += index & -index

print(answer)

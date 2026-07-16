import sys


data = iter(map(int, sys.stdin.buffer.read().split()))
n, query_count = next(data), next(data)
values = [next(data) for _ in range(n)]
ordered = sorted(range(n), key=values.__getitem__)
pairs = []

for position, index in enumerate(ordered):
    left_gap = values[index] - values[ordered[position - 1]] if position else 10**30
    right_gap = values[ordered[position + 1]] - values[index] if position + 1 < n else 10**30
    if left_gap <= right_gap:
        other = ordered[position - 1]
        pairs.append((max(index, other), min(index, other)))
    if right_gap <= left_gap:
        other = ordered[position + 1]
        pairs.append((max(index, other), min(index, other)))

queries = sorted(((next(data) - 1, next(data) - 1, identity + 1)
                  for identity in range(query_count)), key=lambda query: query[1])
pairs.sort()
tree = [0] * (n + 1)


def add(index):
    index += 1
    while index <= n:
        tree[index] += 1
        index += index & -index


def prefix(end):
    result = 0
    while end:
        result += tree[end]
        end -= end & -end
    return result


pointer = 0
answer = 0
for left, right, identity in queries:
    while pointer < len(pairs) and pairs[pointer][0] <= right:
        add(pairs[pointer][1])
        pointer += 1
    answer += (pointer - prefix(left)) * identity
print(answer)

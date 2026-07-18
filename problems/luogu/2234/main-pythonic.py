import sys

data = list(map(int, sys.stdin.buffer.read().split()))
n = data[0]
values = data[1:1 + n]
ordered = sorted(set(values))
rank = {value: index + 1 for index, value in enumerate(ordered)}
tree = [0] * (len(ordered) + 1)

def add(index):
    while index < len(tree):
        tree[index] += 1
        index += index & -index

def prefix_sum(index):
    total = 0
    while index:
        total += tree[index]
        index -= index & -index
    return total

def kth(order):
    index = 0
    step = 1 << (len(tree).bit_length() - 1)
    while step:
        nxt = index + step
        if nxt < len(tree) and tree[nxt] < order:
            index = nxt
            order -= tree[nxt]
        step >>= 1
    return index + 1

answer = values[0]
seen = {values[0]}
add(rank[values[0]])

for value in values[1:]:
    if value in seen:
        continue
    index = rank[value]
    less = prefix_sum(index - 1)
    total = len(seen)
    differences = []
    if less:
        differences.append(value - ordered[kth(less) - 1])
    if less < total:
        differences.append(ordered[kth(less + 1) - 1] - value)
    answer += min(differences)
    seen.add(value)
    add(index)

print(answer)

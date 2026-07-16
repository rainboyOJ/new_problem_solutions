import sys


data = list(map(int, sys.stdin.buffer.read().split()))
n, values = data[0], data[1:]
rank = {value: index for index, value in enumerate(sorted(set(values)), 1)}
size = len(rank)


def add(tree, index):
    while index <= size:
        tree[index] += 1
        index += index & -index


def query(tree, index):
    result = 0
    while index:
        result += tree[index]
        index -= index & -index
    return result


left_count = []
tree = [0] * (size + 1)
for value in values:
    position = rank[value]
    left_count.append(query(tree, position - 1))
    add(tree, position)

right_count = [0] * n
tree = [0] * (size + 1)
seen = 0
for index in range(n - 1, -1, -1):
    position = rank[values[index]]
    right_count[index] = seen - query(tree, position)
    add(tree, position)
    seen += 1

print(sum(left * right for left, right in zip(left_count, right_count)))

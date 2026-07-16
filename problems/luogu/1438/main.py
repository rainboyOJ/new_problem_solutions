import sys
from array import array


data = iter(map(int, sys.stdin.buffer.read().split()))
n, operations = next(data), next(data)
values = [next(data) for _ in range(n)]
constant = array("q", [0]) * (n + 2)
linear = array("q", [0]) * (n + 2)


def add(tree, index, value):
    while index <= n:
        tree[index] += value
        index += index & -index


def prefix(tree, index):
    result = 0
    while index:
        result += tree[index]
        index -= index & -index
    return result


def range_add(tree, left, right, value):
    add(tree, left, value)
    if right < n:
        add(tree, right + 1, -value)


answers = []
for _ in range(operations):
    operation = next(data)
    if operation == 1:
        left, right, first, difference = (next(data) for _ in range(4))
        range_add(constant, left, right, first - left * difference)
        range_add(linear, left, right, difference)
    else:
        position = next(data)
        answers.append(str(values[position - 1] + prefix(constant, position)
                          + position * prefix(linear, position)))
print("\n".join(answers))

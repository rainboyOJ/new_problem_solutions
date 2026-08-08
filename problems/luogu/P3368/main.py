import os
import sys
from array import array


def integers():
    number = 0
    sign = 1
    reading = False
    while chunk := os.read(0, 1 << 20):
        for byte in chunk:
            if byte == 45:
                sign = -1
            elif 48 <= byte <= 57:
                number = number * 10 + byte - 48
                reading = True
            elif reading:
                yield sign * number
                number, sign, reading = 0, 1, False
    if reading:
        yield sign * number


data = iter(integers())
n, operation_count = next(data), next(data)
tree = array("q", [0]) * (n + 1)


def add(index, value):
    while index <= n:
        tree[index] += value
        index += index & -index


def prefix(index):
    result = 0
    while index:
        result += tree[index]
        index -= index & -index
    return result


previous = 0
for i in range(1, n + 1):
    value = next(data)
    add(i, value - previous)
    previous = value
answers = []
for _ in range(operation_count):
    operation, left = next(data), next(data)
    if operation == 1:
        right, value = next(data), next(data)
        add(left, value)
        if right < n:
            add(right + 1, -value)
    else:
        answers.append(str(prefix(left)))
print("\n".join(answers))

import sys
from bisect import bisect_left, bisect_right


data = iter(map(int, sys.stdin.buffer.read().split()))
operations = [(next(data), next(data)) for _ in range(next(data))]
coordinates = sorted({value for operation, value in operations if operation != 4})
tree = [0] * (len(coordinates) + 1)


def add(index, delta):
    index += 1
    while index < len(tree):
        tree[index] += delta
        index += index & -index


def prefix(end):
    result = 0
    while end:
        result += tree[end]
        end -= end & -end
    return result


def kth(rank):
    index = 0
    step = 1 << (len(tree).bit_length() - 1)
    while step:
        target = index + step
        if target < len(tree) and tree[target] < rank:
            index = target
            rank -= tree[target]
        step >>= 1
    return coordinates[index]


answers = []
for operation, value in operations:
    if operation == 1:
        add(bisect_left(coordinates, value), 1)
    elif operation == 2:
        add(bisect_left(coordinates, value), -1)
    elif operation == 3:
        answers.append(str(prefix(bisect_left(coordinates, value)) + 1))
    elif operation == 4:
        answers.append(str(kth(value)))
    elif operation == 5:
        answers.append(str(kth(prefix(bisect_left(coordinates, value)))))
    else:
        answers.append(str(kth(prefix(bisect_right(coordinates, value)) + 1)))

print("\n".join(answers))

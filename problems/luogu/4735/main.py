import sys
from array import array


MAX_BIT = 23
input = sys.stdin.buffer.readline
n, operation_count = map(int, input().split())
initial = map(int, input().split())
left = array("i", [0])
right = array("i", [0])
count = array("i", [0])


def clone(node):
    left.append(left[node])
    right.append(right[node])
    count.append(count[node])
    return len(count) - 1


def insert(previous_root, value):
    root = clone(previous_root)
    count[root] += 1
    previous, current = previous_root, root
    for bit in range(MAX_BIT, -1, -1):
        if value >> bit & 1:
            child = clone(right[previous])
            right[current] = child
            previous = right[previous]
        else:
            child = clone(left[previous])
            left[current] = child
            previous = left[previous]
        current = child
        count[current] += 1
    return root


def maximum_xor(older_root, newer_root, value):
    answer = 0
    for bit in range(MAX_BIT, -1, -1):
        if value >> bit & 1:
            wanted_old, wanted_new = left[older_root], left[newer_root]
            other_old, other_new = right[older_root], right[newer_root]
        else:
            wanted_old, wanted_new = right[older_root], right[newer_root]
            other_old, other_new = left[older_root], left[newer_root]
        if count[wanted_new] > count[wanted_old]:
            answer |= 1 << bit
            older_root, newer_root = wanted_old, wanted_new
        else:
            older_root, newer_root = other_old, other_new
    return answer


roots = array("i", [0])
prefix_xor = 0
roots.append(insert(0, 0))
for value in initial:
    prefix_xor ^= value
    roots.append(insert(roots[-1], prefix_xor))

answers = []
for _ in range(operation_count):
    operation = input().split()
    if operation[0] == b"A":
        prefix_xor ^= int(operation[1])
        roots.append(insert(roots[-1], prefix_xor))
    else:
        left_index, right_index, value = map(int, operation[1:])
        value ^= prefix_xor
        answers.append(str(maximum_xor(roots[left_index - 1], roots[right_index], value)))

print("\n".join(answers))

import sys
from array import array
from bisect import bisect_left, bisect_right


input = sys.stdin.buffer.readline
request_count = int(input())
kinds = bytearray()
request_x = array("q")
request_y = array("q")
points = []
for _ in range(request_count):
    operation, x, y = input().split()
    kind = 0 if operation == b'add' else 1 if operation == b'remove' else 2
    x, y = int(x), int(y)
    kinds.append(kind)
    request_x.append(x)
    request_y.append(y)
    if kind == 0:
        points.append((x, y))

points.sort()
x_values_list = []
y_values_list = []
y_offsets_list = []
previous = None
for point in points:
    if point == previous:
        continue
    x, y = point
    if not x_values_list or x != x_values_list[-1]:
        x_values_list.append(x)
        y_offsets_list.append(len(y_values_list))
    y_values_list.append(y)
    previous = point
y_offsets_list.append(len(y_values_list))
del points

x_values = array("q", x_values_list)
y_values = array("q", y_values_list)
y_offsets = array("i", y_offsets_list)
del x_values_list, y_values_list, y_offsets_list

groups = len(x_values)
bit_offsets = array("i", [0])
for group in range(groups):
    bit_offsets.append(bit_offsets[-1] + y_offsets[group + 1] - y_offsets[group] + 1)
fenwick = array("i", [0]) * bit_offsets[-1]
counts = array("i", [0]) * groups
size = 1
while size < groups:
    size <<= 1
segment = array("q", [-1]) * (2 * size)


def bit_add(group, index, delta):
    base = bit_offsets[group]
    length = y_offsets[group + 1] - y_offsets[group]
    while index <= length:
        fenwick[base + index] += delta
        index += index & -index


def bit_sum(group, index):
    base = bit_offsets[group]
    result = 0
    while index:
        result += fenwick[base + index]
        index -= index & -index
    return result


def bit_kth(group, target):
    base = bit_offsets[group]
    length = y_offsets[group + 1] - y_offsets[group]
    index = 0
    step = 1 << (length.bit_length() - 1)
    while step:
        next_index = index + step
        if next_index <= length and fenwick[base + next_index] < target:
            index = next_index
            target -= fenwick[base + index]
        step >>= 1
    return index + 1


def set_leaf(index, value):
    node = size + index
    segment[node] = value
    node //= 2
    while node:
        segment[node] = max(segment[node * 2], segment[node * 2 + 1])
        node //= 2


def first_x(node, left, right, start, y):
    if right <= start or segment[node] <= y:
        return -1
    if right - left == 1:
        return left
    middle = (left + right) // 2
    result = first_x(node * 2, left, middle, start, y)
    return result if result != -1 else first_x(node * 2 + 1, middle, right, start, y)


answers = []
for kind, x, y in zip(kinds, request_x, request_y):
    if kind < 2:
        group = bisect_left(x_values, x)
        start, end = y_offsets[group], y_offsets[group + 1]
        position = bisect_left(y_values, y, start, end) - start + 1
        delta = 1 if kind == 0 else -1
        bit_add(group, position, delta)
        counts[group] += delta
        if counts[group]:
            maximum = y_values[start + bit_kth(group, counts[group]) - 1]
        else:
            maximum = -1
        set_leaf(group, maximum)
        continue
    group = first_x(1, 0, size, bisect_right(x_values, x), y)
    if group == -1 or group >= groups:
        answers.append('-1')
        continue
    start, end = y_offsets[group], y_offsets[group + 1]
    position = bisect_right(y_values, y, start, end) - start
    target = bit_sum(group, position) + 1
    answer_y = y_values[start + bit_kth(group, target) - 1]
    answers.append(f'{x_values[group]} {answer_y}')
sys.stdout.write('\n'.join(answers))

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

# 离线坐标压缩：x 升序去重后，组号 = 下标 + 1（与 main2.cpp 的 1-based 组号一致）
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
# 组 g（1-based）的候选 y 是 y_values[y_offsets[g-1] .. y_offsets[g]-1]
bit_offsets = array("i", [0]) * (groups + 2)
for group in range(1, groups + 1):
    bit_offsets[group + 1] = bit_offsets[group] + (y_offsets[group] - y_offsets[group - 1]) + 1
fenwick = array("i", [0]) * bit_offsets[groups + 1]
counts = array("i", [0]) * (groups + 1)
segment = array("q", [-1]) * (4 * groups + 4)


def bit_length_of(group):
    """组 group 的候选 y 个数。"""
    return y_offsets[group] - y_offsets[group - 1]


def bit_add(group, index, delta):
    base = bit_offsets[group]
    length = bit_length_of(group)
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
    """组内找第 target 个活跃 y 的压缩下标（1-based）。"""
    base = bit_offsets[group]
    length = bit_length_of(group)
    index = 0
    step = 1 << (length.bit_length() - 1)
    while step:
        next_index = index + step
        if next_index <= length and fenwick[base + next_index] < target:
            index = next_index
            target -= fenwick[base + index]
        step >>= 1
    return index + 1


def seg_update(node, left, right, pos, value):
    """点更新：把第 pos 组的叶子值改成 value，并向上合并区间最大值。"""
    if left == right:
        segment[node] = value
        return
    middle = (left + right) // 2
    if pos <= middle:
        seg_update(node * 2, left, middle, pos, value)
    else:
        seg_update(node * 2 + 1, middle + 1, right, pos, value)
    segment[node] = max(segment[node * 2], segment[node * 2 + 1])


def first_x(node, left, right, start, y):
    """找最小的组号 g 使 start <= g 且第 g 组的最大 y > y；不存在返回 0。"""
    if right < start or segment[node] <= y:  # 整段在起点左边，或整段最大值都够不到 y
        return 0
    if left == right:
        return left
    middle = (left + right) // 2
    result = first_x(node * 2, left, middle, start, y)  # 先左后右，返回的组号自然最小
    return result if result else first_x(node * 2 + 1, middle + 1, right, start, y)


answers = []
for kind, x, y in zip(kinds, request_x, request_y):
    if kind < 2:
        group = bisect_left(x_values, x) + 1  # 组号从 1 开始
        start, end = y_offsets[group - 1], y_offsets[group]
        position = bisect_left(y_values, y, start, end) - start + 1
        delta = 1 if kind == 0 else -1
        bit_add(group, position, delta)
        counts[group] += delta
        if counts[group]:
            maximum = y_values[start + bit_kth(group, counts[group]) - 1]
        else:
            maximum = -1
        seg_update(1, 1, groups, group, maximum)
        continue
    group = first_x(1, 1, groups, bisect_right(x_values, x) + 1, y)
    if group == 0:
        answers.append('-1')
        continue
    start, end = y_offsets[group - 1], y_offsets[group]
    position = bisect_right(y_values, y, start, end) - start
    target = bit_sum(group, position) + 1
    answer_y = y_values[start + bit_kth(group, target) - 1]
    answers.append(f'{x_values[group - 1]} {answer_y}')
sys.stdout.write('\n'.join(answers))

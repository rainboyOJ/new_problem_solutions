import sys


def read_all_ints():
    return list(map(int, sys.stdin.buffer.read().split()))


data = read_all_ints()
length, interval_count = data[0], data[1]
has_tree = [True] * (length + 1)
pos = 2
for _ in range(interval_count):
    left, right = data[pos], data[pos + 1]
    pos += 2
    for x in range(left, right + 1):
        has_tree[x] = False
print(sum(has_tree))

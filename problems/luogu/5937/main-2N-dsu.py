# P5937 [CEOI 1999] Parity Game — 2N 并查集解法
# 对每个前缀位置建两个节点：
#   x     → prefix[x] = 0
#   x+K   → prefix[x] = 1（K 是不同前缀坐标的数量）
# (实际用字典映射到连续编号后偏移)

import sys


input = sys.stdin.buffer.readline
_ = int(input())
m = int(input())

# 先读完所有回答，再把出现过的前缀位置压成 0..k-1。
# 这样第二层节点统一使用 x + k，offset 不会在处理中途改变。
queries = []
coordinates = []
for _ in range(m):
    left, right, word = input().split()
    left, right = int(left) - 1, int(right)
    parity = word == b"odd"
    queries.append((left, right, parity))
    coordinates.append(left)
    coordinates.append(right)

coordinates = sorted(set(coordinates))
node_id = {value: index for index, value in enumerate(coordinates)}
offset = len(coordinates)

# 普通并查集（无额外权值），总节点数为 2 * offset。
parent = list(range(2 * offset))
size = [1] * (2 * offset)


def find(x):
    while parent[x] != x:
        parent[x] = parent[parent[x]]
        x = parent[x]
    return x


def unite(a, b):
    ra, rb = find(a), find(b)
    if ra == rb:
        return
    if size[ra] < size[rb]:
        ra, rb = rb, ra
    parent[rb] = ra
    size[ra] += size[rb]


answer = m
for i, (left, right, parity) in enumerate(queries):
    a = node_id[left]
    b = node_id[right]

    if parity == 0:
        # prefix[A] == prefix[B]
        # → A0 和 B0 在一起，A1 和 B1 在一起
        unite(a, b)
        unite(a + offset, b + offset)
    else:
        # prefix[A] != prefix[B]
        # → A0 和 B1 在一起，A1 和 B0 在一起
        unite(a, b + offset)
        unite(a + offset, b)

    # 判冲突：A0 和 A1 是否被逼到了同一集合？
    if find(a) == find(a + offset) or find(b) == find(b + offset):
        answer = i
        break

print(answer)

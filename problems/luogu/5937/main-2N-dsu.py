# P5937 [CEOI 1999] Parity Game — 2N 并查集解法
# 对每个前缀位置建两个节点：
#   x     → prefix[x] = 0
#   x+N   → prefix[x] = 1
# (实际用字典映射到连续编号后偏移)

import sys


input = sys.stdin.buffer.readline
_ = int(input())
m = int(input())

# 把出现的前缀位置映射到稠密编号
node_id = {}
nodes = []


def get_id(x):
    """给前缀位置 x 分配一个基础编号"""
    if x not in node_id:
        node_id[x] = len(node_id)
    return node_id[x]


# 普通并查集（无额外权值）
parent = []
size = []


def add_node():
    parent.append(len(parent))
    size.append(1)


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
for i in range(m):
    left, right, word = input().split()
    left, right = int(left) - 1, int(right)

    a = get_id(left)
    b = get_id(right)

    # 确保有足够的节点：每个前缀位置需要 2 个节点
    while len(parent) < (len(node_id)) * 2:
        add_node()

    offset = len(node_id)          # 偏转量 = 出现过的不同前缀数量

    if word == b"even":
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
    if find(a) == find(a + offset):
        answer = i
        break

print(answer)

# P5937 [CEOI 1999] Parity Game — 带权并查集解法
#
# 核心转换：
#   区间 [l,r] 中 1 的奇偶性 = prefix[r] XOR prefix[l-1]
#   每条回答变成两个前缀位置之间的关系约束。
#
# 带权并查集维护：
#   parity[x] = 节点 x 与它的根节点之间的 XOR 关系
#              0 → x 和根取值相同
#              1 → x 和根取值相反

import sys


input = sys.stdin.buffer.readline
_ = int(input())               # n 只用于读入，后面不需要
m = int(input())

# ---- 三个字典实现带权并查集（n 可达 1e9，只存出现过的位置）----
parent = {}   # parent[x] = x 的父节点，根指向自己
size = {}     # size[x]   = 以 x 为根的集合大小（按大小合并用）
parity = {}   # parity[x] = x 相对于父节点 parent[x] 的 XOR 关系


def add(x):
    """向并查集中加入一个新节点，初始为孤立点"""
    if x not in parent:
        parent[x] = x       # 自己是自己的根
        size[x] = 1         # 集合大小 = 1
        parity[x] = 0       # 自己和自己当然相同


def find(x):
    """
    查找 x 的根，并做路径压缩。
    路径压缩时要同步更新 parity：把 x 到根的 XOR 链折叠。
    """
    if parent[x] != x:
        old_parent = parent[x]
        parent[x] = find(old_parent)          # 递归到根
        # 此时 old_parent 已经指向了根，
        # parity[old_parent] 是 old_parent 到根的关系
        # 那么 x 到根 = x 到 old_parent XOR old_parent 到根
        parity[x] ^= parity[old_parent]
    return parent[x]


def unite(x, y, expected):
    """
    尝试合并两个节点 x 和 y。
    expected = 0: 要求 prefix[x] == prefix[y] （even）
    expected = 1: 要求 prefix[x] != prefix[y] （odd）

    返回 True 表示一致，False 表示矛盾。
    """
    root_x, root_y = find(x), find(y)

    # ---- 推导 root_x 和 root_y 之间应有的关系 ----
    # 已知:
    #   prefix[x]  = prefix[root_x] XOR parity[x]
    #   prefix[y]  = prefix[root_y] XOR parity[y]
    #   constraint: prefix[x] XOR prefix[y] = expected
    #
    # 代入:
    #   prefix[root_x] XOR parity[x] XOR
    #   prefix[root_y] XOR parity[y] = expected
    #
    # 移项:
    #   prefix[root_x] XOR prefix[root_y]
    #     = expected XOR parity[x] XOR parity[y]
    #
    # 令 relation = 上式右侧，这表示 root_x 和 root_y 之间的 XOR 关系:
    #   relation = 0 → roots 取值相同
    #   relation = 1 → roots 取值相反
    relation = parity[x] ^ parity[y] ^ expected

    # ---- 已在同一集合：检查是否一致 ----
    if root_x == root_y:
        # 此时 root_x == root_y，所以它们之间关系必须是 0（相同）
        return relation == 0     # relation == 0 → 一致；!= 0 → 矛盾

    # ---- 不在同一集合：按大小合并 ----
    if size[root_x] < size[root_y]:
        root_x, root_y = root_y, root_x       # 保证 root_x 是较大的树

    parent[root_y] = root_x                   # root_y 挂到 root_x 下
    parity[root_y] = relation                 # 记录 root_y 与 root_x 的关系
    size[root_x] += size[root_y]              # 更新大小
    return True


# ---- 主循环：逐条处理回答 ----
answer = m                        # 哨兵，默认所有回答都正确
for i in range(m):
    left, right, word = input().split()
    left, right = int(left) - 1, int(right)   # 转为 prefix[l-1] 和 prefix[r]
    add(left)
    add(right)

    # word == b"odd" → True(=1)，否则 False(=0)
    if answer == m and not unite(left, right, word == b"odd"):
        answer = i                # 记录第一条矛盾的回答编号（0-based）

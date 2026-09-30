#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 13:32
# update_at: 2026-09-30 13:46

import sys
from array import array

BITS = 31  # 实测边权最大 2147400037 < 2^31，字典树固定走 31 层（高位到低位）


def insert(trie: array, x: int) -> None:
    """把 x 插入 01 字典树：trie[2*node+bit] 是该节点第 bit 位的孩子下标，-1 表示空。"""
    node = 0
    for b in range(BITS - 1, -1, -1):
        bit = x >> b & 1
        child = trie[node << 1 | bit]
        if child < 0:
            child = len(trie) >> 1            # 新节点编号 = 当前节点总数
            trie[node << 1 | bit] = child
            trie.extend((-1, -1))             # 给新节点预留两个孩子槽
        node = child


def max_xor(trie: array, x: int) -> int:
    """在 01 字典树里贪心走每一位：能取反就取反，返回与 x 异或的最大值。"""
    node, ans = 0, 0
    for b in range(BITS - 1, -1, -1):
        bit = x >> b & 1
        other = trie[node << 1 | 1 - bit]  # 走"这一位不同"的分支，本位异或得 1
        if other >= 0:
            node = other
            ans |= 1 << b
        else:
            node = trie[node << 1 | bit]  # 只剩同位分支，本位异或得 0
    return ans


def prefix_xors(g: list[list[tuple[int, int]]], root: int) -> list[int]:
    """求根到每个点的边权异或和 d（d[u]^d[v] 即 u→v 路径异或和），按遍历序返回。"""
    d: list[int] = []
    stack: list[tuple[int, int | None, int]] = [(root, None, 0)]  # (点, 父点, 累计异或和)；迭代 DFS 防止链状树递归爆栈
    while stack:
        u, parent, acc = stack.pop()
        d.append(acc)
        for v, w in g[u]:
            if v != parent:
                stack.append((v, u, acc ^ w))
    return d


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    g: list[list[tuple[int, int]]] = [[] for _ in range(n + 1)]
    for _ in range(n - 1):
        u, v, w = next(data), next(data), next(data)
        g[u].append((v, w))
        g[v].append((u, w))

    # d[u]^d[v] 恰好等于 u→v 路径异或和，故答案 = 任意两点 d 的最大异或对
    d = prefix_xors(g, 1)

    trie = array("i", (-1, -1))  # 节点 0 为根
    ans = 0
    for x in d:
        insert(trie, x)
        # 插入后查询允许走到自己（x^x=0），不改变最大值，还避开了空树查询
        ans = max(ans, max_xor(trie, x))

    print(ans)


if __name__ == "__main__":
    solve()

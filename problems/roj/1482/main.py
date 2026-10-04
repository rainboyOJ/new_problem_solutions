#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 14:00
# update_at: 2026-09-30 14:04

import sys
from collections import deque


def build_ac(words: list[str]) -> tuple[list[int], list[int], list[int]]:
    """构建 AC 自动机并返回 (各前缀经过计数, 各模式串对应节点, 广搜拓扑序)。"""
    trie: list[dict[str, int]] = [{}]
    cnt: list[int] = [0]
    pos: list[int] = []

    for w in words:
        u = 0
        for ch in w:
            if ch not in trie[u]:
                trie[u][ch] = len(trie)
                trie.append({})
                cnt.append(0)
            u = trie[u][ch]
            cnt[u] += 1  # 记录所有模式串前缀在该节点的覆盖次数
        pos.append(u)

    fail = [0] * len(trie)
    q = deque(trie[0].values())
    order: list[int] = []

    while q:
        u = q.popleft()
        order.append(u)
        for ch, v in trie[u].items():
            f = fail[u]
            while f and ch not in trie[f]:
                f = fail[f]
            fail[v] = trie[f][ch] if ch in trie[f] else 0
            q.append(v)

    return cnt, fail, order, pos


def count_occurrences(cnt: list[int], fail: list[int], order: list[int], pos: list[int]) -> list[int]:
    """按 fail 树自底向上聚合子树计数，返回每个模式串在所有串中的总出现次数。"""
    for u in reversed(order):
        cnt[fail[u]] += cnt[u]
    return [cnt[p] for p in pos]


def solve() -> None:
    data = sys.stdin.read().split()
    if not data:
        return
    n = int(data[0])
    words = data[1:n + 1]

    cnt, fail, order, pos = build_ac(words)
    ans = count_occurrences(cnt, fail, order, pos)
    print('\n'.join(map(str, ans)))


if __name__ == "__main__":
    solve()

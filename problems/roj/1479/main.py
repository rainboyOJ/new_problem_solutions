#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 13:35
# update_at: 2026-09-30 13:35

import sys
from collections import deque


def build_automaton(words: list[bytes]) -> tuple[list[dict[int, int]], list[int], list[int], list[int]]:
    """插入查询词建 trie 并 BFS 求 fail，返回转移表 go、fail 数组、词尾计数 cnt 与 BFS 序。"""
    go: list[dict[int, int]] = [{}]   # 根是 0；每节点一个 dict，只存真实存在的边
    cnt: list[int] = [0]              # cnt[v]：以 v 结尾的查询词个数（重复词各计一次）

    for w in words:
        node = 0
        for c in w:
            nxt = go[node].get(c)
            if nxt is None:
                go[node][c] = len(go)
                go.append({})
                cnt.append(0)
                nxt = len(go) - 1
            node = nxt
        cnt[node] += 1

    fail: list[int] = [0] * len(go)
    order: list[int] = []             # BFS 出队序：深度不减，任何节点都排在自己 fail 之后
    queue = deque(go[0].values())     # 根的孩子 fail 默认就是根
    while queue:
        node = queue.popleft()
        order.append(node)
        for c, nxt in go[node].items():
            f = fail[node]            # 沿 fail 链找能接下字符 c 的祖先
            while f and c not in go[f]:
                f = fail[f]
            fail[nxt] = go[f].get(c, 0)
            queue.append(nxt)
    return go, fail, cnt, order


def count_hits(article: bytes, go: list[dict[int, int]], fail: list[int], cnt: list[int], order: list[int]) -> int:
    """扫描文章标出到达过的状态，再沿 fail 树自底向上合并命中，返回出现过的查询词个数。"""
    hit = bytearray(len(go))
    node = 0
    for c in article:
        while node and c not in go[node]:   # 没有对应边就沿 fail 链回退
            node = fail[node]
        node = go[node].get(c, 0)
        hit[node] = 1

    # 状态 v 到达 ⇒ v 的整个 fail 祖先链上的词都出现过；逆 BFS 序保证祖先后处理
    for v in reversed(order):
        if hit[v]:
            hit[fail[v]] = 1
    return sum(c for c, h in zip(cnt, hit) if h)


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    T = int(next(data))
    out: list[str] = []
    for _ in range(T):
        n = int(next(data))
        words = [next(data) for _ in range(n)]
        article = next(data)
        go, fail, cnt, order = build_automaton(words)
        out.append(str(count_hits(article, go, fail, cnt, order)))
    print('\n'.join(out))


if __name__ == "__main__":
    solve()

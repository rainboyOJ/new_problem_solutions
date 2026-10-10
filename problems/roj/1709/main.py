#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 17:43
# update_at: 2026-10-07 17:43

import sys
from collections import deque

LOG = 5  # 2^5 = 32 > 串长上界 30，够跳完任意深度

type Trie = list[dict[int, int]]  # 出边表：第 u 个结点存 字符 -> 子结点编号
type Up = list[list[int]]         # 倍增祖先表：up[k][u] 是 u 向上 2^k 步的祖先


def build_trie(words: list[bytes]) -> tuple[Trie, list[int], list[int]]:
    """把所有串插入 trie，返回（出边表, 父亲, 深度）。

    trie 上每个非根结点恰好对应一个非空前缀串，于是结点数 cnt 就是集合 |P|。
    """
    nxt: Trie = [{}]
    fa: list[int] = [0]
    dep: list[int] = [0]  # 深度 = 该结点代表的前缀串长度
    for word in words:
        u = 0
        for c in word:
            v = nxt[u].get(c)
            if v is None:
                v = len(nxt)
                nxt[u][c] = v
                nxt.append({})
                fa.append(u)
                dep.append(dep[u] + 1)
            u = v
    return nxt, fa, dep


def build_fail(nxt: Trie) -> tuple[list[int], list[int]]:
    """BFS 求 AC 自动机的 fail 指针，同时返回按深度递增的访问序。

    找 fail 时沿失配链跳一步看有没有对应字符的边；链长 ≤ 30，代价可忽略。
    """
    cnt = len(nxt) - 1
    fail = [0] * (cnt + 1)
    order: list[int] = []
    queue = deque(nxt[0].values())
    while queue:
        u = queue.popleft()
        order.append(u)
        for c, v in nxt[u].items():
            f = fail[u]
            while f and c not in nxt[f]:
                f = fail[f]
            fail[v] = nxt[f].get(c, 0)
            queue.append(v)
    return fail, order


def build_up(fa: list[int]) -> Up:
    """建倍增祖先表：up[k][u] 为 u 向上 2^k 步的祖先。"""
    up: Up = [fa]
    for _ in range(LOG):
        prev = up[-1]
        up.append([prev[x] for x in prev])
    return up


def ancestor_at(up: Up, node: int, height: int) -> int:
    """从 node 向上走 height 步（height ≤ 30，按二进制位拆开跳）。"""
    bit = 0
    while height:
        if height & 1:
            node = up[bit][node]
        height >>= 1
        bit += 1
    return node


def count_good(
    cnt: int,
    fail: list[int],
    dep: list[int],
    sub: list[int],
    up: Up,
) -> int:
    """好串个数：先按 cnt² 记，再扣掉每个平移块带来的重复切分。

    u 有非空真后缀（fail[u] 不是根）时，平移块 t 是 u 向上 dep[fail[u]] 步的祖先；
    sub[t] - 1 即以 t 为严格后缀的 P 内串个数，也就是这一块多算的次数。
    """
    ans = cnt * cnt
    for u in range(1, cnt + 1):
        if not fail[u]:
            continue
        t = ancestor_at(up, u, dep[fail[u]])
        ans -= sub[t] - 1
    return ans


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    n = int(next(data))
    words = [next(data) for _ in range(n)]

    nxt, fa, dep = build_trie(words)
    cnt = len(nxt) - 1

    # fail 树子树大小：fail 指向更浅的结点，按访问序倒着累加即可
    fail, order = build_fail(nxt)
    sub = [1] * (cnt + 1)
    for u in reversed(order):
        sub[fail[u]] += sub[u]

    print(count_good(cnt, fail, dep, sub, build_up(fa)))


if __name__ == "__main__":
    solve()

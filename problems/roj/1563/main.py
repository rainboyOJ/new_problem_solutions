#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 18:30
# update_at: 2026-09-30 18:30

import sys
from collections.abc import Iterator

EMPTY_LAZY = -1  # 线段树区间覆盖懒标记默认空哨兵


def build_hld(
    n: int, adj: list[list[int]]
) -> tuple[list[int], list[int], list[int], list[int], list[int]]:
    """以 1 为根对无向树做轻重链剖分，返回 (parent, depth, top, dfn, rev)。"""
    parent = [0] * (n + 1)
    depth = [0] * (n + 1)
    sz = [1] * (n + 1)
    heavy = [0] * (n + 1)

    order: list[int] = []
    stack = [1]
    depth[1] = 1

    while stack:
        u = stack.pop()
        order.append(u)
        for v in adj[u]:
            if v != parent[u]:
                parent[v] = u
                depth[v] = depth[u] + 1
                stack.append(v)

    for u in reversed(order):
        p = parent[u]
        max_c = 0
        h = 0
        for v in adj[u]:
            if v != p:
                sz[u] += sz[v]
                if sz[v] > max_c:
                    max_c = sz[v]
                    h = v
        heavy[u] = h

    top = [0] * (n + 1)
    dfn = [0] * (n + 1)
    rev = [0] * (n + 1)
    timer = 0

    chain_stack = [(1, 1)]
    while chain_stack:
        u, t = chain_stack.pop()
        timer += 1
        dfn[u] = timer
        rev[timer] = u
        top[u] = t

        h = heavy[u]
        for v in adj[u]:
            if v != parent[u] and v != h:
                chain_stack.append((v, v))
        if h:
            chain_stack.append((h, t))

    return parent, depth, top, dfn, rev


def solve() -> None:
    input_data = sys.stdin.buffer.read().split()
    if not input_data:
        return
    it = iter(input_data)
    n = int(next(it))
    m = int(next(it))

    init_col = [0] + [int(next(it)) for _ in range(n)]

    adj: list[list[int]] = [[] for _ in range(n + 1)]
    for _ in range(n - 1):
        u, v = int(next(it)), int(next(it))
        adj[u].append(v)
        adj[v].append(u)

    parent, depth, top, dfn, rev = build_hld(n, adj)

    tree_cnt = [0] * (4 * n + 5)
    tree_lc = [0] * (4 * n + 5)
    tree_rc = [0] * (4 * n + 5)
    lazy = [EMPTY_LAZY] * (4 * n + 5)

    def build_seg(o: int, l: int, r: int) -> None:
        if l == r:
            c = init_col[rev[l]]
            tree_cnt[o] = 1
            tree_lc[o] = c
            tree_rc[o] = c
            return
        mid = (l + r) >> 1
        lo = o << 1
        ro = lo | 1
        build_seg(lo, l, mid)
        build_seg(ro, mid + 1, r)
        tree_cnt[o] = tree_cnt[lo] + tree_cnt[ro] - (1 if tree_rc[lo] == tree_lc[ro] else 0)
        tree_lc[o] = tree_lc[lo]
        tree_rc[o] = tree_rc[ro]

    sys.setrecursionlimit(200000)
    build_seg(1, 1, n)

    def push_down(o: int) -> None:
        c = lazy[o]
        if c != EMPTY_LAZY:
            lo = o << 1
            ro = lo | 1
            lazy[lo] = c
            tree_cnt[lo] = 1
            tree_lc[lo] = c
            tree_rc[lo] = c

            lazy[ro] = c
            tree_cnt[ro] = 1
            tree_lc[ro] = c
            tree_rc[ro] = c

            lazy[o] = EMPTY_LAZY

    def update(o: int, l: int, r: int, ql: int, qr: int, c: int) -> None:
        if ql <= l and r <= qr:
            lazy[o] = c
            tree_cnt[o] = 1
            tree_lc[o] = c
            tree_rc[o] = c
            return
        push_down(o)
        mid = (l + r) >> 1
        lo = o << 1
        ro = lo | 1
        if ql <= mid:
            update(lo, l, mid, ql, qr, c)
        if qr > mid:
            update(ro, mid + 1, r, ql, qr, c)
        tree_cnt[o] = tree_cnt[lo] + tree_cnt[ro] - (1 if tree_rc[lo] == tree_lc[ro] else 0)
        tree_lc[o] = tree_lc[lo]
        tree_rc[o] = tree_rc[ro]

    def query(o: int, l: int, r: int, ql: int, qr: int) -> tuple[int, int, int]:
        if ql <= l and r <= qr:
            return tree_cnt[o], tree_lc[o], tree_rc[o]
        push_down(o)
        mid = (l + r) >> 1
        lo = o << 1
        ro = lo | 1
        if qr <= mid:
            return query(lo, l, mid, ql, qr)
        if ql > mid:
            return query(ro, mid + 1, r, ql, qr)
        cnt1, lc1, rc1 = query(lo, l, mid, ql, qr)
        cnt2, lc2, rc2 = query(ro, mid + 1, r, ql, qr)
        same_middle = rc1 == lc2
        return cnt1 + cnt2 - (1 if same_middle else 0), lc1, rc2

    def tree_update(u: int, v: int, c: int) -> None:
        while top[u] != top[v]:
            if depth[top[u]] < depth[top[v]]:
                u, v = v, u
            update(1, 1, n, dfn[top[u]], dfn[u], c)
            u = parent[top[u]]
        if depth[u] > depth[v]:
            u, v = v, u
        update(1, 1, n, dfn[u], dfn[v], c)

    def tree_query(u: int, v: int) -> int:
        ans = 0
        last_u = -1
        last_v = -1
        while top[u] != top[v]:
            if depth[top[u]] >= depth[top[v]]:
                cnt, lc, rc = query(1, 1, n, dfn[top[u]], dfn[u])
                ans += cnt
                if rc == last_u:
                    ans -= 1
                last_u = lc
                u = parent[top[u]]
            else:
                cnt, lc, rc = query(1, 1, n, dfn[top[v]], dfn[v])
                ans += cnt
                if rc == last_v:
                    ans -= 1
                last_v = lc
                v = parent[top[v]]
        if depth[u] >= depth[v]:
            cnt, lc, rc = query(1, 1, n, dfn[v], dfn[u])
            ans += cnt
            if rc == last_u:
                ans -= 1
            if lc == last_v:
                ans -= 1
        else:
            cnt, lc, rc = query(1, 1, n, dfn[u], dfn[v])
            ans += cnt
            if lc == last_u:
                ans -= 1
            if rc == last_v:
                ans -= 1
        return ans

    out: list[str] = []
    for _ in range(m):
        op = next(it)
        if op == b'C':
            u = int(next(it))
            v = int(next(it))
            c = int(next(it))
            tree_update(u, v, c)
        else:
            u = int(next(it))
            v = int(next(it))
            out.append(str(tree_query(u, v)))

    sys.stdout.write('\n'.join(out) + '\n')


if __name__ == "__main__":
    solve()

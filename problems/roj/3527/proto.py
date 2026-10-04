#!/usr/bin/env python3
# prototype: layer-by-layer memoized DP
import sys
from functools import cache

def solve() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    n, m = data[0], data[1]
    adj = [[] for _ in range(n)]
    for k in range(m):
        a, b = data[2 + 2 * k] - 1, data[3 + 2 * k] - 1
        adj[a].append(b)
        adj[b].append(a)
    # root at 0
    parent = [-1] * n
    order = [0]
    for u in order:
        for v in adj[u]:
            if v != parent[u]:
                if parent[v] == -1 and v != 0:
                    parent[v] = u
                    order.append(v)
    children = [[] for _ in range(n)]
    for v in range(n):
        if parent[v] != -1:
            children[parent[v]].append(v)
    sz = [1] * n
    for u in reversed(order):
        for v in children[u]:
            sz[u] += sz[v]
    CH = [0] * n
    for u in range(n):
        for v in children[u]:
            CH[u] |= 1 << v

    @cache
    def W(mask: int) -> int:
        if mask == 0:
            return 0
        kids = 0
        m = mask
        while m:
            lsb = m & -m
            kids |= CH[lsb.bit_length() - 1]
            m ^= lsb
        best = 0
        m = mask
        while m:
            lsb = m & -m
            v = lsb.bit_length() - 1
            val = sz[v] + W(kids & ~CH[v])
            if val > best:
                best = val
            m ^= lsb
        return best

    saved = W(CH[0])
    print(n - saved)
    print(f"[stats] states={W.cache_info().currsize}", file=sys.stderr)

solve()

#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 19:06
# update_at: 2026-10-07 19:06

import sys
from collections.abc import Iterator

NONE = -1  # 链式前向星里"没有下一条边"的哨兵

# 类型别名（Python 3.12+ 的 type 语句），相当于 C++ 的 using / typedef
type Adj = list[int]                 # 链式前向星的 head / nxt / to / wt 表
type Tree = list[list[tuple[int, int]]]  # 桥树邻接表：(边双编号, 桥的权) 列表的列表


def ints(raw: bytes) -> Iterator[int]:
    """顺序产出输入里的整数；比 split() 省内存（本题单组可达 3e5 行、Σm 达 3e6）。"""
    num = 0
    in_num = False
    for b in raw:
        if b > 32:
            num = num * 10 + b - 48
            in_num = True
        elif in_num:
            yield num
            num = 0
            in_num = False
    if in_num:
        yield num


def bridges(n: int, head: Adj, nxt: Adj, to: Adj) -> bytearray:
    """回答"每条有向边是不是割边的某一侧"：tarjan 显式栈迭代，避免长链爆栈。"""
    dfn = [0] * (n + 1)
    low = [0] * (n + 1)
    it_e = [0] * (n + 1)         # 迭代 DFS 中当前扫到的出边
    par_e = [-1] * (n + 1)       # 结点在 DFS 树中的入边下标
    is_br = bytearray(len(to))   # 成对下标的反向边同时置 1
    timer = 0

    for root in range(1, n + 1):
        if dfn[root]:
            continue
        timer += 1
        dfn[root] = low[root] = timer
        it_e[root] = head[root]
        par_e[root] = NONE
        stack = [root]
        while stack:
            u = stack[-1]
            e = it_e[u]
            if e != NONE:
                it_e[u] = nxt[e]
                parent_back = par_e[u] != NONE and e == (par_e[u] ^ 1)
                if parent_back:
                    continue                       # 不走父边的反向边（重边才需要靠边下标区分）
                v = to[e]
                if not dfn[v]:                     # 树边：继续深搜
                    par_e[v] = e
                    it_e[v] = head[v]
                    timer += 1
                    dfn[v] = low[v] = timer
                    stack.append(v)
                elif dfn[v] < low[u]:              # 返祖边：用 dfn 更新 low
                    low[u] = dfn[v]
            else:
                stack.pop()                        # u 出栈，把 low 回传给父亲
                pe = par_e[u]
                if pe != NONE:
                    p = to[pe ^ 1]
                    if low[u] < low[p]:
                        low[p] = low[u]
                    if low[u] > dfn[p]:            # (p,u) 是割边
                        is_br[pe] = is_br[pe ^ 1] = 1
    return is_br


def shrink(n: int, m: int, to: Adj, wt: Adj, is_br: bytearray) -> tuple[list[int], list[bool]]:
    """非割边连通块缩成边双：返回 comp（结点 -> 边双编号）与 has_art（边双内部是否有权 1 边）。"""
    fa = list(range(n + 1))
    size = [1] * (n + 1)

    def root(x: int) -> int:
        while fa[x] != x:
            fa[x] = fa[fa[x]]                      # 路径折半压缩
            x = fa[x]
        return x

    for e in range(0, 2 * m, 2):
        if not is_br[e]:
            a, b = root(to[e]), root(to[e ^ 1])
            if a != b:
                if size[a] < size[b]:
                    a, b = b, a
                fa[b] = a
                size[a] += size[b]

    comp = [root(v) for v in range(n + 1)]
    has_art = [False] * (n + 1)
    for e in range(0, 2 * m, 2):
        if not is_br[e] and wt[e]:
            has_art[comp[to[e]]] = True            # 这块边双内部有魔法石，路过就能取
    return comp, has_art


def can_collect(cs: int, cd: int, tree: Tree, has_art: list[bool]) -> bool:
    """桥树上 cs -> cd 的唯一路径上，是否经过权 1 的桥或内部有石的边双。"""
    acc = {cs: has_art[cs]}                        # 前缀或：从 cs 走到该边双时能否已取到石
    stack = [cs]
    while stack and cd not in acc:
        u = stack.pop()
        for v, w in tree[u]:
            if v in acc:
                continue
            acc[v] = acc[u] or w == 1 or has_art[v]
            stack.append(v)
    return acc.get(cd, False)                      # cd 不在同一连通块时为 False


def solve_case(data: Iterator[int]) -> str:
    """读入一组数据，返回该组的 YES / NO。"""
    n, m = next(data), next(data)
    head = [NONE] * (n + 1)
    nxt = [NONE] * (2 * m)
    to = [0] * (2 * m)
    wt = [0] * (2 * m)
    for e in range(0, 2 * m, 2):                   # 边成对加入，e ^ 1 是反向边
        x, y, c = next(data), next(data), next(data)
        to[e], wt[e], nxt[e], head[x] = y, c, head[x], e
        to[e + 1], wt[e + 1], nxt[e + 1], head[y] = x, c, head[y], e + 1

    is_br = bridges(n, head, nxt, to)
    comp, has_art = shrink(n, m, to, wt, is_br)

    tree: Tree = [[] for _ in range(n + 1)]        # 桥树的边就是原图的割边
    for e in range(0, 2 * m, 2):
        if is_br[e]:
            u, v = comp[to[e]], comp[to[e ^ 1]]
            tree[u].append((v, wt[e]))
            tree[v].append((u, wt[e]))

    src, dst = next(data), next(data)
    return "YES" if can_collect(comp[src], comp[dst], tree, has_art) else "NO"


def solve() -> None:
    data = ints(sys.stdin.buffer.read())
    T = next(data)
    print("\n".join(solve_case(data) for _ in range(T)))


if __name__ == "__main__":
    solve()

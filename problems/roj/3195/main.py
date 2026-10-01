#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 00:56
# update_at: 2026-10-02 01:20

import sys
from array import array


def mark_bridges(n: int, head: array, nxt: array, to: array) -> bytearray:
    """迭代 Tarjan 求桥：bridge[e] = 1 表示弧 e 属于某条桥。

    无向边存成两条配对弧 2i 与 2i+1，所以弧 e 的配对弧就是 e ^ 1；
    栈帧写成 [当前点, 待处理的邻接弧, 进入当前点的那条弧]，
    第三条专门用来跳过沿同一条边回到父亲的配对弧。
    """
    tin = array('i', bytes(4 * (n + 1)))            # 0 兼作“没访问过”
    low = array('i', bytes(4 * (n + 1)))
    bridge = bytearray(len(to))
    timer = 0
    for s in range(1, n + 1):
        if tin[s]:
            continue
        timer += 1
        tin[s] = low[s] = timer
        stack = [[s, head[s], -1]]
        while stack:
            top = stack[-1]
            e = top[1]
            if e:
                top[1] = nxt[e]
                if e == (top[2] ^ 1):               # 配对弧：无向边不能当回边用
                    continue
                u, v = top[0], to[e]
                if tin[v]:
                    if tin[v] < low[u]:
                        low[u] = tin[v]
                else:
                    timer += 1
                    tin[v] = low[v] = timer
                    stack.append([v, head[v], e])
            else:
                stack.pop()
                if stack:
                    p = stack[-1][0]
                    if low[top[0]] < low[p]:
                        low[p] = low[top[0]]
                    if low[top[0]] > tin[p]:        # 子树回不到 p 之上，这条弧的边是桥
                        bridge[top[2]] = bridge[top[2] ^ 1] = 1
    return bridge


def label_blocks(n: int, head: array, nxt: array, to: array, bridge: bytearray) -> tuple[array, int]:
    """删掉所有桥后给每个点标出它所属的块，返回块号表与块总数。"""
    block = array('i', bytes(4 * (n + 1)))
    total = 0
    for s in range(1, n + 1):
        if block[s]:
            continue
        total += 1
        block[s] = total
        stack = [s]
        while stack:
            u = stack.pop()
            e = head[u]
            while e:
                v = to[e]
                if not bridge[e] and not block[v]:
                    block[v] = total
                    stack.append(v)
                e = nxt[e]
    return block, total


def bridge_forest(blocks: int, tree_edges: int, block: array, to: array, bridge: bytearray) -> tuple[array, array]:
    """把块当成点、桥当成边，建出桥森林，返回每个块的父块与深度（根深度 0）。

    桥森林的边数等于桥数，而且两个端点由配对弧 e 与 e ^ 1 直接给出，
    所以只扫偶数编号的弧就够了。原图连通时它就是一棵树。
    """
    thead = array('i', bytes(4 * (blocks + 1)))
    tnxt = array('i', bytes(8 * tree_edges + 8))
    tto = array('i', bytes(8 * tree_edges + 8))
    cnt = 0
    for e in range(2, len(to), 2):
        if not bridge[e]:
            continue
        x, y = block[to[e]], block[to[e ^ 1]]
        cnt += 1
        tnxt[cnt] = thead[x]; tto[cnt] = y; thead[x] = cnt
        cnt += 1
        tnxt[cnt] = thead[y]; tto[cnt] = x; thead[y] = cnt

    parent = array('i', bytes(4 * (blocks + 1)))     # 0 = 没访问过，-1 = 所在树的根
    depth = array('i', bytes(4 * (blocks + 1)))
    for s in range(1, blocks + 1):
        if parent[s]:
            continue
        parent[s] = -1                              # 根用 -1 做哨兵，0 留给“没访问过”
        stack = [s]
        while stack:
            u = stack.pop()
            e = thead[u]
            while e:
                v = tto[e]
                if parent[v] == 0:
                    parent[v] = u
                    depth[v] = depth[u] + 1
                    stack.append(v)
                e = tnxt[e]
    return parent, depth


def find(uf: array, x: int) -> int:
    """并查集找根，同时做路径压缩（迭代写法，避免递归深度）。"""
    r = x
    while uf[r] != r:
        r = uf[r]
    while uf[x] != r:
        uf[x], x = r, uf[x]
    return r


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    case_no = 0
    while True:
        n, m = next(data), next(data)
        if n == 0 and m == 0:
            break
        case_no += 1

        head = array('i', bytes(4 * (n + 1)))
        nxt = array('i', bytes(8 * m + 8))
        to = array('i', bytes(8 * m + 8))
        for i in range(1, m + 1):
            a, b = next(data), next(data)
            nxt[2 * i], to[2 * i], head[a] = head[a], b, 2 * i
            nxt[2 * i + 1], to[2 * i + 1], head[b] = head[b], a, 2 * i + 1

        bridge = mark_bridges(n, head, nxt, to)
        block, blocks = label_blocks(n, head, nxt, to, bridge)
        tree_edges = sum(bridge) // 2              # 两条配对弧都被标记，除以 2 才是边数
        tparent, tdepth = bridge_forest(blocks, tree_edges, block, to, bridge)

        remaining = tree_edges
        uf = array('i', range(blocks + 1))          # 已经缩成一团的块用并查集合并（每个块自成一类）

        q = next(data)
        answers = []
        for _ in range(q):
            a, b = next(data), next(data)
            u, v = find(uf, block[a]), find(uf, block[b])
            while u != v:                           # 只会往上并，最后一次询问前必然停止
                if tdepth[u] < tdepth[v]:
                    u, v = v, u                     # 让 u 是更深的那一侧
                up = tparent[u]                     # 深的一侧到父亲的桥必然落在路径上
                uf[u] = find(uf, up)
                u = uf[u]
                remaining -= 1
            answers.append(remaining)

        out.append(f"Case {case_no}:")
        out += map(str, answers)
        out.append("")

    sys.stdout.write("\n".join(out))


if __name__ == "__main__":
    solve()

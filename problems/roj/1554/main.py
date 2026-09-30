#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 17:59
# update_at: 2026-09-30 18:08

import sys
from bisect import bisect_left

ADD = 43      # 事件首字节 '+'：点 x 上出现异象石
QUERY = 63    # 事件首字节 '?'：询问连通所有异象石的最短边集长度
              # 删除（首字节 '-'）是默认分支，不单独登记


def euler_tour(
    head: list[int], nxt: list[int], to: list[int], weight: list[int], n: int
) -> tuple[list[int], list[int], list[int], list[int]]:
    """迭代 DFS，返回 (进入时刻 tin, 深度 dep, 父节点 up, 根到点的距离 root_dist)。

    用显式栈代替递归：树可以退化成链，深度 10^5 会让 Python 递归直接爆栈。
    tin 随进入顺序单调递增，所以"按 tin 排序"就是"按 DFS 序排序"。
    """
    tin, dep, up = [0] * (n + 1), [0] * (n + 1), [0] * (n + 1)
    root_dist = [0] * (n + 1)
    timer = 0
    stack = [(1, head[1])]
    while stack:
        u, e = stack.pop()
        if e == -1:                       # 边扫完了：u 的子树处理结束
            continue
        if e == head[u]:                  # 第一次弹出 u：登记进入时刻
            timer += 1
            tin[u] = timer
        stack.append((u, nxt[e]))         # 压回"接着扫 u 的下一条邻边"
        v = to[e]
        if v != up[u]:                    # 不沿来路边走回父亲
            up[v] = u
            dep[v] = dep[u] + 1
            root_dist[v] = root_dist[u] + weight[e]   # 父节点的距离此刻已经算好
            stack.append((v, head[v]))
    return tin, dep, up, root_dist


def build_up(up: list[int], n: int, levels: int) -> list[list[int]]:
    """倍增表 jump[k][v] = v 的第 2^k 级祖先；节点 0 是根的父亲，作哨兵。"""
    jump = [up]
    for _ in range(levels - 1):
        prev = jump[-1]
        jump.append([prev[prev[v]] for v in range(n + 1)])
    return jump


def solve() -> None:
    data = sys.stdin.buffer.read().split()
    pos = 0

    n = int(data[pos]); pos += 1

    # 链式前向星：head[u] 是 u 的第一条边，nxt[e] 是共享 u 的下一条边
    head = [-1] * (n + 1)
    to: list[int] = []
    nxt: list[int] = []
    weight: list[int] = []
    for _ in range(n - 1):
        x, y, z = int(data[pos]), int(data[pos + 1]), int(data[pos + 2]); pos += 3
        to += [y, x]
        weight += [z, z]
        nxt += [head[x], head[y]]
        head[x] = len(to) - 2
        head[y] = len(to) - 1

    tin, dep, up, root_dist = euler_tour(head, nxt, to, weight, n)
    levels = max(1, n.bit_length())
    jump = build_up(up, n, levels)

    def lca(u: int, v: int) -> int:
        """倍增求最近公共祖先。"""
        if dep[u] < dep[v]:
            u, v = v, u
        diff = dep[u] - dep[v]
        for k in range(levels):
            if diff >> k & 1:
                u = jump[k][u]
        if u == v:
            return u
        for k in range(levels - 1, -1, -1):
            if jump[k][u] != jump[k][v]:
                u, v = jump[k][u], jump[k][v]
        return up[u]

    # 欧拉序的时刻 -> 节点，用于把环上的前驱后继还原成节点编号
    rev = [0] * (n + 2)
    for v in range(1, n + 1):
        rev[tin[v]] = v

    def dist(u: int, v: int) -> int:
        """树上两点距离 = 根距离之和 - 2 * 根到 LCA 的距离。"""
        w = lca(u, v)
        return root_dist[u] + root_dist[v] - 2 * root_dist[w]

    order: list[int] = []   # 当前所有异象石按 tin 升序排列
    # total 是欧拉环上相邻距离之和，它恰好是答案（最小连通边集长度）的两倍：
    # 环游一圈会把斯坦纳树的每条边正反各走一次，所以输出时折半。
    total = 0
    out: list[str] = []

    m = int(data[pos]); pos += 1
    for _ in range(m):
        kind = data[pos][0]
        if kind == QUERY:
            pos += 1
            out.append(str(total // 2))       # 偶数，整除无舍入
            continue

        x = int(data[pos + 1]); pos += 2
        i = bisect_left(order, tin[x])
        if kind == ADD:                           # 把环上 (前驱, 后继) 换成 (前驱, x) + (x, 后继)
            order.insert(i, tin[x])
            prev = rev[order[i - 1]]                  # -1 绕回环尾
            next_node = rev[order[(i + 1) % len(order)]]  # 只有一个元素时指向自己
        else:                                     # '-'：先取出删掉后占住 i 的后继，再弹出 x
            next_node = rev[order[(i + 1) % len(order)]]
            prev = rev[order[i - 1]]
            order.pop(i)
        # 插入加、删除减，增量公式完全一致
        delta = dist(prev, x) + dist(x, next_node) - dist(prev, next_node)
        total += delta if kind == ADD else -delta

    sys.stdout.write('\n'.join(out) + ('\n' if out else ''))


if __name__ == "__main__":
    solve()

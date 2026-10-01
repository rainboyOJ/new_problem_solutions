#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 03:11
# update_at: 2026-10-02 03:16

import sys
from collections import deque

NO_EDGE = -1    # 链式前向星：没有下一条弧
UNREACHED = -1  # BFS 分层：本轮还没访问到 / 从 s 到不了


def add_edge(head: list[int], to: list[int], nxt: list[int], cap: list[int],
             u: int, v: int, c: int) -> None:
    """加一条 u->v 容量 c 的弧，紧跟一条容量 0 的反向弧：两条弧编号互为 e ^ 1。

    反向弧的容量表示"这条正向弧上已推了多少水"，走它就等于把水退回去。
    """
    to.append(v)
    cap.append(c)
    nxt.append(head[u])
    head[u] = len(to) - 1
    to.append(u)
    cap.append(0)
    nxt.append(head[v])
    head[v] = len(to) - 1


def build_levels(head: list[int], to: list[int], nxt: list[int], cap: list[int],
                 s: int) -> list[int]:
    """BFS 分层：只沿还有剩余容量的弧走，返回每点离 s 的弧数，够不到记 UNREACHED。"""
    level = [UNREACHED] * len(head)
    level[s] = 0
    queue = deque([s])
    while queue:
        u = queue.popleft()
        e = head[u]
        while e != NO_EDGE:
            v = to[e]
            if cap[e] > 0 and level[v] == UNREACHED:
                level[v] = level[u] + 1
                queue.append(v)
            e = nxt[e]
    return level


def blocking_flow(head: list[int], to: list[int], nxt: list[int], cap: list[int],
                  level: list[int], s: int, t: int) -> int:
    """在当前分层图上推阻塞流：只走层号严格 +1 的弧，直到再也走不到 t，返回流量。

    用显式栈代替递归：栈里存 (点, 从它走出去的弧号)。层号接不上的弧本轮永远接不上，
    由当前弧 it[u] 跳过；某点的出弧全废就把它的层号抹掉，回退时不再进来。
    """
    it = head[:]                           # 当前弧：每条弧走废后本轮不再重扫
    path: list[tuple[int, int]] = []
    flow = 0
    u = s
    while True:
        if u == t:
            bottle = min(cap[e] for _, e in path)
            for _, e in path:
                cap[e] -= bottle
                cap[e ^ 1] += bottle    # 反向弧加容量 = 允许把这段水退回去
            flow += bottle
            # 只退回到第一条被榨干的弧，从那里接着找下一条增广路
            first = next(i for i, (_, e) in enumerate(path) if cap[e] == 0)
            path = path[:first]
            u = to[path[-1][1]] if path else s
        else:
            e, advance = it[u], NO_EDGE
            while e != NO_EDGE:
                v = to[e]
                if cap[e] > 0 and level[v] == level[u] + 1:
                    advance = e            # 分层图上唯一可走的出弧
                    break
                e = nxt[e]
            it[u] = e
            if advance != NO_EDGE:
                path.append((u, advance))
                u = to[advance]
            elif not path:                 # 源点的弧全废，本轮阻塞流已挖空
                break
            else:                          # 死路：抹掉层号并退回上一个点
                level[u] = UNREACHED
                u = path.pop()[0]
    return flow


def max_flow(head: list[int], to: list[int], nxt: list[int], cap: list[int],
             s: int, t: int) -> int:
    """Dinic：反复"分层 + 推阻塞流"，直到残量网络里 t 不可达。"""
    flow = 0
    while True:
        level = build_levels(head, to, nxt, cap, s)
        if level[t] == UNREACHED:          # 无增广路，当前流已是最大流
            return flow
        flow += blocking_flow(head, to, nxt, cap, level, s, t)


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)
    s, t = 1, m                             # 交叉点 1 是池塘（源），交叉点 m 是河（汇）

    head = [NO_EDGE] * (m + 1)
    to: list[int] = []
    nxt: list[int] = []
    cap: list[int] = []
    for _ in range(n):
        u, v, c = next(data), next(data), next(data)
        add_edge(head, to, nxt, cap, u, v, c)  # 水只能沿 Si -> Ei 流

    print(max_flow(head, to, nxt, cap, s, t))


if __name__ == "__main__":
    solve()

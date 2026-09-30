#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 16:25
# update_at: 2026-09-30 16:25

import sys

# 边访问标记
VISITED_FLAG = 1


def euler_undirected(n: int, m: int, head: list[int], to: list[int], nxt: list[int], eid: list[int]) -> list[int]:
    """Hierholzer 非递归求无向图欧拉回路：当前弧优化推进，退栈时记录逆序回路。"""
    used = [0] * (m + 1)
    cur = head[:]
    tour: list[int] = []
    stk_u: list[int] = [next((v for v in range(1, n + 1) if head[v] != -1), 1)]
    stk_e: list[int] = []

    while stk_u:
        u = stk_u[-1]
        e = cur[u]
        while e != -1 and used[abs(eid[e])]:
            e = nxt[e]
        cur[u] = e
        if e != -1:
            edge_id = eid[e]
            used[abs(edge_id)] = VISITED_FLAG
            cur[u] = nxt[e]
            stk_u.append(to[e])
            stk_e.append(edge_id)
        else:
            stk_u.pop()
            if stk_e:
                tour.append(stk_e.pop())

    tour.reverse()
    return tour


def euler_directed(n: int, m: int, head: list[int], to: list[int], nxt: list[int], eid: list[int]) -> list[int]:
    """Hierholzer 非递归求有向图欧拉回路：当前弧优化推进，退栈时记录逆序回路。"""
    used = [0] * (m + 1)
    cur = head[:]
    tour: list[int] = []
    stk_u: list[int] = [next((v for v in range(1, n + 1) if head[v] != -1), 1)]
    stk_e: list[int] = []

    while stk_u:
        u = stk_u[-1]
        e = cur[u]
        while e != -1 and used[eid[e]]:
            e = nxt[e]
        cur[u] = e
        if e != -1:
            edge_id = eid[e]
            used[edge_id] = VISITED_FLAG
            cur[u] = nxt[e]
            stk_u.append(to[e])
            stk_e.append(edge_id)
        else:
            stk_u.pop()
            if stk_e:
                tour.append(stk_e.pop())

    tour.reverse()
    return tour


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    try:
        t = int(next(data))
    except StopIteration:
        return
    n, m = int(next(data)), int(next(data))

    if m == 0:
        print("YES\n")
        return

    deg = [0] * (n + 1)
    head = [-1] * (n + 1)

    if t == 1:
        # 无向图前向星：边成对存储，第 i 条边编号为 +(i+1) 与 -(i+1)
        tot = m * 2
        to = [0] * tot
        nxt = [0] * tot
        eid = [0] * tot
        edge_cnt = 0
        for i in range(1, m + 1):
            u, v = int(next(data)), int(next(data))
            deg[u] += 1
            deg[v] += 1
            to[edge_cnt], nxt[edge_cnt], eid[edge_cnt] = v, head[u], i
            head[u] = edge_cnt
            edge_cnt += 1
            to[edge_cnt], nxt[edge_cnt], eid[edge_cnt] = u, head[v], -i
            head[v] = edge_cnt
            edge_cnt += 1

        degree_valid = all(d % 2 == 0 for d in deg)
        if not degree_valid:
            print("NO")
            return

        tour = euler_undirected(n, m, head, to, nxt, eid)
    else:
        # 有向图前向星：记录出度与入度之差
        to = [0] * m
        nxt = [0] * m
        eid = [0] * m
        edge_cnt = 0
        for i in range(1, m + 1):
            u, v = int(next(data)), int(next(data))
            deg[u] -= 1
            deg[v] += 1
            to[edge_cnt], nxt[edge_cnt], eid[edge_cnt] = v, head[u], i
            head[u] = edge_cnt
            edge_cnt += 1

        degree_valid = all(d == 0 for d in deg)
        if not degree_valid:
            print("NO")
            return

        tour = euler_directed(n, m, head, to, nxt, eid)

    connected = len(tour) == m
    if not connected:
        print("NO")
        return

    print("YES")
    print(" ".join(map(str, tour)))


if __name__ == "__main__":
    solve()

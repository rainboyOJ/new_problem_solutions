#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 20:32
# update_at: 2026-10-07 20:32

import sys
from collections.abc import Iterator

NONE = -1  # 哨兵：不存在的前驱 / 后继 / 街道编号一律用它，含义只在这一行解释

# 类型别名（Python 3.12+ 的 type 语句），相当于 C++ 的 using / typedef
type IntList = list[int]                    # 一整族按街道编号下标的数组
type SuperEdges = tuple[IntList, IntList]   # 收缩后超边族的（起点序列, 终点序列）


def contract_chains(m: int, eu: IntList, ev: IntList, nxt: IntList, prv: IntList) -> SuperEdges | None:
    """把被片段逼成一串的街道收缩成超边，返回 (起点序列, 终点序列)；无解时返回 None。

    片段逼出的是 succ(街道) = 必须紧跟的那条街道，无冲突时每条街道至多一个后继而
    至多一个前驱，所以粘合关系分解成「链」和「环」。链整块连着走，对外只暴露链首
    起点与链尾终点，收缩成一条超边；环则必须吞掉全部 m 条街道（succ 本身是覆盖全部
    街道的唯一大环），此时回路已被唯一确定，收缩成一条落在环上某点的自环。
    """
    unit_of = [NONE] * m
    tails: IntList = []
    heads: IntList = []
    for i in range(m):                                 # 链：从没有被逼出前驱的街道起步
        if prv[i] != NONE or unit_of[i] != NONE:
            continue
        unit_id, e = len(tails), i
        while True:
            unit_of[e] = unit_id
            if nxt[e] == NONE:
                break
            e = nxt[e]
        tails.append(eu[i])   # 链首所在点给一条出边
        heads.append(ev[e])   # 链尾所在点给一条入边

    # 剩下每条街道都被逼出了后继，它们的 nxt 构成闭合轨道（succ 的闭合块）。succ 必须是
    # 覆盖全部 m 条街道的单环，所以轨道只能有一条且吞掉全部街道；两条轨道、或轨道之外
    # 还残留着链，都会让轨道在自己的街道集合里绕圈，接不上其余街道。
    orbits = 0
    for i in range(m):
        if unit_of[i] != NONE:
            continue
        orbits += 1
        if orbits > 1:
            return None
        unit_id, e = len(tails), i
        covered = 0
        while True:
            unit_of[e] = unit_id
            covered += 1
            e = nxt[e]
            if e == NONE or e == i:
                break
        if covered != m:      # 轨道没能吞掉全部街道
            return None
        tails.append(eu[i])   # 整图就是这条回路，收缩成一条落在环上某点的自环
        heads.append(eu[i])
    return tails, heads


def start_reachable(n: int, din: IntList, dout: IntList, adj: list[IntList]) -> bool:
    """有街道的点是否都落在同一个连通块里；接不进同一条回路的街道永远走不到。"""
    start = next((v for v in range(1, n + 1) if din[v] or dout[v]), 1)
    seen = bytearray(n + 1)
    seen[start] = 1
    stack = [start]
    while stack:
        for w in adj[stack.pop()]:
            if not seen[w]:
                seen[w] = 1
                stack.append(w)
    return all(seen[v] for v in range(1, n + 1) if din[v] or dout[v])


def solve() -> None:
    data: Iterator[int] = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)   # 岔路口数、街道数
    base = n + 1                    # (a,b) 的唯一编码 a*base+b，题面保证街道不重复

    eu: IntList = [0] * m   # 街道起点，下标即街道编号
    ev: IntList = [0] * m   # 街道终点
    id_of: dict[int, int] = {}
    deg1 = 0                # 路口 1 的关联度数：为 0 时邮递员寸步难行
    for i in range(m):
        a, b = next(data), next(data)
        eu[i], ev[i] = a, b
        id_of[a * base + b] = i
        deg1 += (a == 1) + (b == 1)

    nxt: IntList = [NONE] * m   # 被片段逼出的后继
    prv: IntList = [NONE] * m   # 被片段逼出的前驱
    stamp: IntList = [0] * m    # stamp[e] == 当前片段编号 → 这条街道在本片段里已走过
    t = next(data)              # 片段数
    for f in range(1, t + 1):
        k = next(data)          # 片段长度
        if k < 1:
            continue
        prev_vertex, prev_edge = next(data), NONE
        for _ in range(k - 1):
            cur = next(data)
            e = id_of.get(prev_vertex * base + cur, NONE)   # 片段要求走的这条街道
            if e == NONE:                # 片段引用了一条不存在的街道
                print("NIE")
                return
            if stamp[e] == f:            # 同一条街道在一个片段里要求走两次
                print("NIE")
                return
            stamp[e] = f
            if prev_edge != NONE:
                conflict = nxt[prev_edge] not in (NONE, e) or prv[e] not in (NONE, prev_edge)
                if conflict:             # 一条街道被两个片段逼着接不同的后继 / 前驱
                    print("NIE")
                    return
                nxt[prev_edge], prv[e] = e, prev_edge
            prev_edge, prev_vertex = e, cur

    units = contract_chains(m, eu, ev, nxt, prv)
    if units is None:
        print("NIE")
        return
    tails, heads = units

    din: IntList = [0] * (n + 1)    # 收缩图上每点的入度
    dout: IntList = [0] * (n + 1)   # 收缩图上每点的出度
    adj: list[IntList] = [[] for _ in range(n + 1)]
    for a, b in zip(tails, heads):   # 超边只给两端点加度数，链中间穿过的点进一次出一次
        dout[a] += 1
        din[b] += 1
        adj[a].append(b)             # 只判弱连通，两个方向都要能走
        adj[b].append(a)

    balanced = all(din[v] == dout[v] for v in range(1, n + 1))   # 欧拉回路的度数条件
    on_route = deg1 > 0 or m == 0   # 路线必须从路口 1 出发，1 得真的关联着街道
    print("TAK" if balanced and on_route and start_reachable(n, din, dout, adj) else "NIE")


if __name__ == "__main__":
    solve()

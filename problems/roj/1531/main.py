#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 16:39
# update_at: 2026-09-30 16:39

import sys

UNUSED = -1   # nxt[i] 的取值：这条街还没走过
PENDING = -2  # nxt[i] 的取值：街已进路径但还没并进回路，同样按"走过"处理


def extend_trail(
    junction: int,
    streets: list[tuple[int, int, int]],
    adj: list[list[int]],
    nxt: list[int],
    prv: list[int],
    ptr: list[int],
) -> tuple[int, int, int]:
    """从 junction 沿没走过的街贪心走到走不动，返回 (首街, 尾街, 停住的路口)。"""
    first, last = -1, -1
    while True:
        # 每个路口的关联街按编号升序存放，ptr 记住查到哪了，跳过已走的街
        incident, p = adj[junction], ptr[junction]
        while p < len(incident) and nxt[incident[p]] != UNUSED:
            p += 1
        ptr[junction] = p
        if p == len(incident):
            return first, last, junction  # 这个路口再没有没走的街
        s = incident[p]
        if first == -1:  # 新路径的第一条街
            first = s
            prv[s] = PENDING
        else:
            prv[s] = last
            nxt[last] = s
        nxt[s] = PENDING
        last = s
        x, y, _ = streets[s]
        junction = x if x != junction else y  # 走到街的另一端；自环两端相同则原地不动


def euler_circuit(streets: list[tuple[int, int, int]], home: int) -> list[int] | None:
    """Hierholzer 求经过每条街恰好一次、从 home 出发又回到 home 的街编号序列。

    streets 按街编号升序排列，于是每个路口的取边顺序也是编号升序；
    回路不存在（存在奇数度路口导致贪心路停在别处）时返回 None。
    """
    n = len(streets)
    size = max(max(x, y) for x, y, _ in streets) + 1
    adj: list[list[int]] = [[] for _ in range(size)]
    for i, (x, y, _) in enumerate(streets):
        adj[x].append(i)
        if y != x:
            adj[y].append(i)

    nxt = [UNUSED] * n  # 回路中的下一条街
    prv = [UNUSED] * n  # 回路中的上一条街
    ptr = [0] * size    # 各路口关联街的扫描位置

    first, last, stop = extend_trail(home, streets, adj, nxt, prv, ptr)
    if stop != home:  # 贪心路停在别的路口：该路口奇数度，回路不存在
        return None
    prv[first] = last
    nxt[last] = first  # 首尾相接成一个闭合回路
    cursor, junction = first, home

    while True:
        # 当前路口再贪心走出的必是闭合路径：插到 cursor 街前面，直到走不动为止
        while True:
            s, e, stop = extend_trail(junction, streets, adj, nxt, prv, ptr)
            if stop != junction:
                return None  # 停在别处：奇数度路口，回路不存在
            if s == -1 or e == -1:
                break
            before = prv[cursor]
            prv[s] = before
            nxt[before] = s
            prv[cursor] = e
            nxt[e] = cursor
        cursor = prv[cursor]  # 沿回路后退一条街，继续在下一个路口找可并入的路径
        x, y, _ = streets[cursor]
        junction = x if x != junction else y  # 路口挪到这条街的另一端
        if cursor == first:  # 退回起点：整圈扫完，所有街都已进回路
            break

    circuit: list[int] = []
    s = first
    while True:
        circuit.append(streets[s][2])
        s = nxt[s]
        if s == first:
            break
    return circuit


def solve() -> None:
    tokens = list(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    pos = 0

    while pos + 1 < len(tokens):
        # 一组数据：若干 "x y z"（街 z 连接路口 x、y），"0 0" 结束本组，单独的 0 结束输入
        group: list[tuple[int, int, int]] = []
        while pos + 1 < len(tokens):
            x, y = tokens[pos], tokens[pos + 1]
            pos += 2
            if x == 0 or y == 0:
                break
            z = tokens[pos]
            pos += 1
            group.append((x, y, z))
        if not group:
            break  # 又读到 0：整个输入结束

        home = min(group[0][0], group[0][1])  # 起点：第一条街两端编号较小的路口
        streets = sorted(group, key=lambda street: street[2])  # 街编号升序决定取边顺序
        circuit = euler_circuit(streets, home)
        out.append(
            'Round trip does not exist.'
            if circuit is None
            else ' '.join(map(str, circuit))
        )

    print('\n'.join(out))


if __name__ == "__main__":
    solve()

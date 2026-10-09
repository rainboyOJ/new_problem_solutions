#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-09 13:40
# update_at: 2026-10-09 14:16

import sys
from collections.abc import Iterator

type Know = list[set[int]]                # know[i] = 第 i 个人认识的人（1-indexed）
type Sides = tuple[list[int], list[int]]  # 一个连通块在补图两侧的成员编号
type Blocks = list[Sides]                 # 补图的全部连通块


def read_know(n: int, data: Iterator[int]) -> Know:
    """读每个人的熟人表：每行若干编号，以 0 结尾（缺尾 0 时按剩余 token 截断）。"""
    know: Know = [set() for _ in range(n + 1)]
    for i in range(1, n + 1):
        for v in data:
            if v == 0:
                break
            know[i].add(v)
    return know


def split_blocks(n: int, know: Know) -> Blocks | None:
    """补图（不能同队的两人连边）二分染色；有奇环则无解，返回 None。

    两个人能同队 ⟺ 互相认识，所以补图里的一条边就是「必须分队」的强制约束；
    同队 ⇒ 补图无边 ⇒ 每支队伍是补图的独立集 ⇒ 合法分队就是二染色。
    """
    color = [-1] * (n + 1)
    blocks: Blocks = []
    for start in range(1, n + 1):
        if color[start] != -1:
            continue
        color[start] = 0
        stack = [start]
        side: Sides = ([], [])
        while stack:
            u = stack.pop()
            side[color[u]].append(u)
            for v in range(1, n + 1):
                mutual = v in know[u] and u in know[v]   # 互为熟人 ⇒ 可同队 ⇒ 补图无边
                if u == v or mutual:
                    continue
                if color[v] == -1:
                    color[v] = color[u] ^ 1
                    stack.append(v)
                elif color[v] == color[u]:
                    return None           # 同色相邻 ⇒ 奇环 ⇒ 无解
        blocks.append(side)
    return blocks


def pick_teams(n: int, blocks: Blocks) -> tuple[list[int], list[int]] | None:
    """每个连通块整块归队，背包求两队人数差最小的分配，并回退出成员。

    can[i][j]：前 i 块能否让队 1 恰好有 j 人；path[i][j] 记录第 i 块给队 1 的侧。
    """
    cnt = len(blocks)
    can = [[False] * (n + 1) for _ in range(cnt + 1)]
    path = [[0] * (n + 1) for _ in range(cnt + 1)]
    can[0][0] = True
    for i, (a, b) in enumerate(blocks, 1):
        weight = (len(a), len(b))
        for j in range(n + 1):
            if not can[i - 1][j]:
                continue
            for s in (0, 1):
                if j + weight[s] <= n:
                    can[i][j + weight[s]] = True
                    path[i][j + weight[s]] = s

    best, best_diff = -1, n + 1
    for j in range(1, n):               # 两队各至少 1 人 ⇒ 队 1 人数只能是 1..n-1
        if can[cnt][j] and abs(2 * j - n) < best_diff:
            best, best_diff = j, abs(2 * j - n)
    if best < 0:
        return None

    team1: list[int] = []
    team2: list[int] = []
    for i in range(cnt, 0, -1):
        a, b = blocks[i - 1]
        s = path[i][best]
        team1 += a if s == 0 else b
        team2 += b if s == 0 else a
        best -= len(a) if s == 0 else len(b)
    # 真实数据里同一队的成员按编号升序给出，逐字节比对要求保持一致
    team1.sort()
    team2.sort()
    return team1, team2


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data, 0)
    if n <= 0:
        return

    blocks = split_blocks(n, read_know(n, data))
    if blocks is None:
        print("No solution")
        return

    pick = pick_teams(n, blocks)
    if pick is None:
        print("No solution")
        return

    team1, team2 = pick
    print(f"{len(team1)} " + " ".join(map(str, team1)))
    print(f"{len(team2)} " + " ".join(map(str, team2)))


if __name__ == "__main__":
    solve()

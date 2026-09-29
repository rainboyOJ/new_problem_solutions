#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 22:27
# update_at: 2026-09-29 22:30

import sys

RATIO = 150  # 面试线定在计划录取人数的 150% 名次上
FULL = 100   # 百分号的分母


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, admitted_plan = next(data), next(data)  # 题目中的 n、m
    players: list[tuple[int, int]] = [(next(data), next(data)) for _ in range(n)]

    # 成绩从高到低；成绩相同按报名号从小到大，元组比较正好就是这两级
    players.sort(key=lambda p: (-p[1], p[0]))

    # 面试线 = 第 floor(m*150/100) 名的成绩；同分者全部进入面试，实际人数可能超过该名次
    cut_rank = admitted_plan * RATIO // FULL
    # 个别数据里 floor(m*1.5) 会超出总人数，此时没人被淘汰，分数线记作 0（成绩至少为 1）
    line = players[cut_rank - 1][1] if cut_rank <= n else 0
    admitted = [p for p in players if p[1] >= line]

    out = [f"{line} {len(admitted)}"]
    out += [f"{k} {s}" for k, s in admitted]
    print('\n'.join(out))


if __name__ == "__main__":
    solve()

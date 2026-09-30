#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-04-18 10:00
# update_at: 2026-04-18 10:00

import sys
from collections.abc import Iterator
from functools import reduce
from operator import xor

MAX_A = 10000  # 石子堆规模上限，每堆石子数不超过 10^4


def compute_sg(moves: list[int], limit: int) -> list[int]:
    """预计算 0 到 limit 的 SG 函数值表。

    状态 x 的后继状态为 {x - s | s in moves, s <= x}，
    SG(x) 为所有后继状态 SG 值的 mex（最小未出现的非负整数）。
    """
    sorted_moves = sorted(moves)
    sg = [0] * (limit + 1)
    tag = [0] * (len(sorted_moves) + 2)

    for x in range(1, limit + 1):
        for s in sorted_moves:
            if s > x:
                break
            v = sg[x - s]
            if v < len(tag):
                tag[v] = x
        mex = 0
        while tag[mex] == x:
            mex += 1
        sg[x] = mex

    return sg


def solve() -> None:
    data: Iterator[int] = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []

    while True:
        k = next(data, 0)
        if k == 0:
            break

        moves = [next(data) for _ in range(k)]
        sg = compute_sg(moves, MAX_A)

        m = next(data)
        out.append(
            "".join(
                "W" if reduce(xor, (sg[next(data)] for _ in range(next(data))), 0) else "L"
                for _ in range(m)
            )
        )

    print("\n".join(out))


if __name__ == "__main__":
    solve()

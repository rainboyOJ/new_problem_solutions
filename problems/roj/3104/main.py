#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 17:27
# update_at: 2026-10-01 17:27

import sys
from functools import cache, reduce
from math import isqrt
from operator import xor


@cache
def sg(p: int) -> int:
    """单堆 p 颗魔法珠的 SG 值。

    一次操作把 p 换成它的全部真约数，再删掉其中一堆：等于在一个「真约数堆」的
    游戏里挑一堆放弃，剩下各堆仍是互不干扰的子游戏，所以每个可选局面的价值是
    剩余堆的异或。于是先求全部真约数的异或 nx，删掉 d 后的价值就是 nx ^ sg(d)。
    """
    proper = {d for i in range(1, isqrt(p) + 1) if p % i == 0 for d in (i, p // i)} - {p}
    nx = reduce(xor, map(sg, proper), 0)          # 全部真约数堆的异或和
    options = {nx ^ sg(d) for d in proper}        # 每一种「删掉 d」后到达的局面的 SG
    mex = 0
    while mex in options:
        mex += 1
    return mex                                    # 没有后继（p = 1）时 mex 就是 0


def solve() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    pos, out = 0, []
    while pos < len(data):                        # 组数没有给出，一直读到 EOF
        n = data[pos]
        piles = data[pos + 1:pos + 1 + n]
        pos += n + 1
        # 每一轮可以动任意一堆，多堆是一个「和游戏」：整局 SG 就是各堆异或
        out.append("freda" if reduce(xor, map(sg, piles), 0) else "rainbow")
    print("\n".join(out))


if __name__ == "__main__":
    solve()

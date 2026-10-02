#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47

import sys


def momentum(pos: int, m: int, count: int) -> int:
    """count 位工兵落在 pos 号兵营产生的带符号气势：龙方为正、虎方为负。"""
    return count * (m - pos)


def best_camp(delta: int, m: int, s2: int, n: int) -> int:
    """在气势差 delta（龙-虎）基础上投放 s2 人，返回使 |delta| 最小的兵营编号。"""
    ans, best = m, abs(delta)  # 不投也允许（p2 = m），初值就是"投到 m"的效果
    for p in range(1, n + 1):
        cur = abs(delta + momentum(p, m, s2))
        if cur < best:
            ans, best = p, cur
    return ans


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    c = [next(data) for _ in range(n)]
    m, p1, s1, s2 = next(data), next(data), next(data), next(data)

    c[p1 - 1] += s1  # 天降神兵：先落位 s1

    # 龙方气势为正、虎方气势为负，二者之差就是 delta（m 号兵营两侧贡献都为 0）
    delta = sum(momentum(pos, m, c[pos - 1]) for pos in range(1, n + 1))
    print(best_camp(delta, m, s2, n))


if __name__ == "__main__":
    solve()

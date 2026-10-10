#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 04:53
# update_at: 2026-10-08 04:53

import sys
from itertools import accumulate

MOD = 10 ** 9 + 7        # 答案取模的模数

type Point = tuple[int, int]   # 山上的一个坑 (x, y)

FAC: list[int] = []      # FAC[i] = i! mod MOD，由 build_tables 按 2N 上界填充
INVFAC: list[int] = []   # INVFAC[i] = (i!)^(-1) mod MOD


def build_tables(limit: int) -> None:
    """填充阶乘表与阶乘逆元表：任意组合数 C(n, k) 之后可以 O(1) 算出。"""
    global FAC, INVFAC
    FAC = [1, *accumulate(range(1, limit + 1), lambda a, b: a * b % MOD)]
    # 从 inv(limit!) 出发逐个乘回 i，第 k 项是 inv((limit-k)!)；倒置后就是升序的
    # INVFAC[i] = inv(i!)（i = 0..limit）
    INVFAC = [*accumulate(range(limit, 0, -1), lambda a, b: a * b % MOD,
                          initial=pow(FAC[limit], MOD - 2, MOD))][::-1]


def paths(sx: int, sy: int, tx: int, ty: int) -> int:
    """从 (sx,sy) 走到 (tx,ty) 且全程不越过直线 y=x 的路径数（反射原理，O(1)）。"""
    if tx < sx or ty < sy:
        return 0                                     # 终点落在起点左下方，根本走不到
    total = tx - sx + ty - sy                        # 总步数 dx + dy
    all_ways = FAC[total] * INVFAC[tx - sx] % MOD * INVFAC[ty - sy] % MOD
    reflect_pick = ty - sx - 1                       # 越过 y=x+1 的路径数即 C(total, ty-sx-1)
    if reflect_pick < 0:
        return all_ways                              # 起点已经在高处，不可能碰到 y=x+1
    bad_ways = FAC[total] * INVFAC[reflect_pick] % MOD * INVFAC[total - reflect_pick] % MOD
    return (all_ways - bad_ways) % MOD


def count_paths(n: int, holes: list[Point]) -> int:
    """容斥：返回 (0,0)->(n,n)、全程不越过 y=x 且不踩任何坑的路径数。

    holes 已按 (x, y) 升序去重；把踩了坑的路径按"踩到的第一个坑"分类，前缀由 first[j]
    保证不踩坑、后缀从 j 走到 i 只需保持合法，两者相乘即该类路径数。
    """
    first: list[int] = []       # first[i] = 走到 holes[i] 且它是首个被踩到的坑的方案数
    for xi, yi in holes:
        ways = paths(0, 0, xi, yi)                     # 先算无视其他坑的方案数
        for (xj, yj), fj in zip(holes, first):         # zip 到 first 结束，即只枚举更早的坑
            if yj <= yi:                               # 否则坑 j 不可能出现在通往坑 i 的路上
                ways -= fj * paths(xj, yj, xi, yi)     # 扣除"首个坑是 j、随后走到 i"的方案
        first.append(ways % MOD)

    ans = paths(0, 0, n, n) - sum(
        f * paths(x, y, n, n) for (x, y), f in zip(holes, first)   # 末尾踩过坑的路径按首坑扣除
    )
    return ans % MOD


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, c = next(data), next(data)
    pts: list[Point] = [(next(data), next(data)) for _ in range(c)]   # 每个坑的坐标

    build_tables(2 * n + 1)                 # 一条路径最多走 2N 步，组合数上界是 2N
    holes = sorted(set(pts))                # 去重并按 (x,y) 升序，保证 DP 只从前往后转移
    print(count_paths(n, holes))


if __name__ == "__main__":
    solve()

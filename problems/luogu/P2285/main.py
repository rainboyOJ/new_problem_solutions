#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-26 14:05
# update_at: 2026-10-26 14:25

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    _n = next(data)
    m = next(data)

    ts = [0] * m  # 出现时刻
    xs = [0] * m  # 行
    ys = [0] * m  # 列
    for i in range(m):
        ts[i] = next(data)
        xs[i] = next(data)
        ys[i] = next(data)

    dp = [0] * m               # dp[i]：以第 i 只鼹鼠作为最后一只时最多打死的数目
    buckets = [[] for _ in range(m + 1)]  # buckets[d]：dp 值等于 d 的那些下标
    ans = 1

    for i in range(m):
        ti = ts[i]
        xi = xs[i]
        yi = ys[i]
        best = 1  # 初始位置自由，第 i 只总能被当作第一只
        # 按 dp 从大到小找第一个赶得上的前驱：它就是最优前驱，于是可以立刻停手
        for d in range(ans, 0, -1):
            found = False
            for j in buckets[d]:
                if abs(xi - xs[j]) + abs(yi - ys[j]) <= ti - ts[j]:
                    best = d + 1
                    found = True
                    break
            if found:
                break
        dp[i] = best
        buckets[best].append(i)
        if best > ans:
            ans = best

    print(ans)


if __name__ == "__main__":
    solve()

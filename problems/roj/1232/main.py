#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 00:56
# update_at: 2026-09-30 00:56

import sys
from collections.abc import Iterator


def cross(times: list[int]) -> int:
    """返回 times 中所有人过河的最短总时间（已升序）。

    dp[i] = 送走最慢的 i+1 个人所需时间。送走最慢者 a[i] 只有两种不交叉的运输剧本，
    每轮都让 a[0] 或 a[1] 划船回来，故 dp[i] = min(dp[i-1] + a[0] + a[i],
    dp[i-2] + a[0] + 2*a[1] + a[i])。原地滚动两个变量即可，不必开数组。
    """
    dp_prev2: int = times[0]          # dp[0]：只剩一人时他自己过河
    if len(times) == 1:
        return dp_prev2
    dp_prev1: int = times[1]          # dp[1]：两人一起过河，慢者定速

    for i in range(2, len(times)):
        # best 方案：最快者来回送最慢者，一次只消耗掉一个最慢者
        solo = dp_prev1 + times[0] + times[i]
        # duo 方案：最快两人先过、次快者带船回、两慢者同过、最快者带船回
        duo = dp_prev2 + times[0] + 2 * times[1] + times[i]
        dp_prev2, dp_prev1 = dp_prev1, min(solo, duo)  # 滚动：省掉长度 n 的数组

    return dp_prev1


def solve() -> None:
    """逐组读入 n 与 n 个过河时间，输出每组的最短总时间。"""
    data: Iterator[int] = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    for _ in range(next(data)):       # 组数 t，每组输出一行
        n = next(data)
        times = sorted(next(data) for _ in range(n))  # 只有有序才能按"最慢者"递推
        out.append(str(cross(times)))
    print('\n'.join(out))


if __name__ == "__main__":
    solve()

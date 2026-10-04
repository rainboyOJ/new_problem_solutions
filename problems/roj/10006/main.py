#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 18:07
# update_at: 2026-10-02 18:07

import sys
from itertools import accumulate

MOD = 10**9 + 7  # 答案模数


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m, x, y = next(data), next(data), next(data), next(data)

    # 工资降序排列；pre[j] = 前 j 大的工资之和
    salary = sorted((next(data) for _ in range(n)), reverse=True)
    pre = [0, *accumulate(salary)]

    if m == 1:
        # 只有一年：无人会连续两年拿 C，开除不会发生，拿 C 者照领原工资
        ans = 3 * pre[x] + 2 * (pre[x + y] - pre[x]) + (pre[n] - pre[x + y])
    else:
        # 两年起：工资最小的 k = n-x-y 人在第 1、2 年连续拿 C 被开除，
        # 幸存者恰好 x + y 人，此后年年涨薪，名额零浪费
        three, two = pow(3, m, MOD), pow(2, m, MOD)
        ans = three * pre[x] + two * (pre[x + y] - pre[x])

    print(ans % MOD)


if __name__ == "__main__":
    solve()

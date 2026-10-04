#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 19:41
# update_at: 2026-10-02 19:41

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)      # 门数：门围成一圈，相邻门距离 1
    rounds = next(data)  # 行走次数 p
    k = next(data)      # 每行走 k 次翻转一次前进方向
    now = next(data)    # 起始门
    steps = [next(data) for _ in range(rounds)]  # 每次行走的距离 a_i

    # 第 i 次行走（0 起）落在第 i//k 个方向块：偶数块顺时针 +a，奇数块逆时针 -a。
    # 环上每步只贡献有符号位移，总位移的模就是答案，不必逐步模拟位置。
    drift = sum(a if (i // k) % 2 == 0 else -a for i, a in enumerate(steps))
    print((now + drift) % n)  # Python 的 % 对正除数恒落在 [0, n)


if __name__ == "__main__":
    solve()

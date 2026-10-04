#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://roj.ac.cn  https://rbook.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 16:23
# update_at: 2026-10-02 16:23

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)  # 数的个数
    values = [next(data) for _ in range(n)]  # n 个数

    sp = sum(v for v in values if v > 0)   # 正数之和 P
    sn = sum(-v for v in values if v < 0)  # 负数绝对值之和 N

    # 设 x 次单个操作、y 次成对操作：单个操作不改变 P-N，故 x >= |P-N|；
    # 每次操作至多让 P+N 减 2，故 x+2y >= P+N。
    # 两式相加：2(x+y) >= (P+N)+|P-N| = 2*max(P,N)，而先配对 min(P,N) 次、
    # 再单个消掉 |P-N| 恰好做到 max(P,N) 次。
    print(max(sp, sn))


if __name__ == "__main__":
    solve()

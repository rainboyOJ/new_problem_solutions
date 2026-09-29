#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47

import sys


def solve() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    m, n = data[0], data[1]

    # 区间 [m, n] 中第一个能被 17 整除的数
    first = m if m % 17 == 0 else m + (17 - m % 17)

    # 等差数列求和：首项 first，末项 last，项数 k
    last = n - n % 17
    if first > last:
        print(0)
        return

    k = (last - first) // 17 + 1
    ans = (first + last) * k // 2
    print(ans)


if __name__ == "__main__":
    solve()

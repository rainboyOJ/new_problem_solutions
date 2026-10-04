#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 05:31
# update_at: 2026-10-01 05:31

import sys
from functools import cache


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    a = [next(data) for _ in range(n)]

    @cache
    def gain(l: int, r: int) -> int:
        """先手在区间 [l, r] 上能比后手多拿多少分（后手同样最优）。"""
        if l > r:
            return 0
        # 取左端就让对手先手于 [l+1, r]，取右端同理，两式取优即零和博弈的对抗转移
        return max(a[l] - gain(l + 1, r), a[r] - gain(l, r - 1))

    diff = gain(0, n - 1)
    total = sum(a)
    # 双方得分和恒为 total，且先手 - 后手 = diff，解这个二元一次方程组
    print((total + diff) // 2, (total - diff) // 2)


if __name__ == "__main__":
    solve()

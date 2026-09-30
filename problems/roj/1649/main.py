#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 00:48
# update_at: 2026-10-01 00:48

import sys
from math import comb


def count_r(k: int, w: int) -> int:
    """按位数 n 分类计数：所有满足条件的 2^k 进制数 r 的个数。"""
    m = 1 << k  # 数位集合 {0, 1, ..., 2^k - 1}，共 m 个数位
    total = 0
    for n in range(2, m):  # 至少 2 位；首位非 0，n 个递增数位至多从 m-1 个里选
        if k * (n - 1) >= w:  # r ≥ 2^{k(n-1)} ≥ 2^w，位数再增必然超长
            break
        if k * n <= w:  # r < 2^{kn} ≤ 2^w，位数不超长则每一位都合法
            total += comb(m - 1, n)  # 从 1..m-1 里选 n 个数位，严格递增唯一对应一个 r
        else:
            # 只剩首位 d1 能"救"超长：d1·2^{k(n-1)} ≤ r，故需 d1 < 2^{w-k(n-1)}；
            # 反之 d1 满足该上界时 r ≤ 2^w - 1 必然不超长，条件恰为 d1 < top。
            top = 1 << (w - k * (n - 1))
            total += sum(comb(m - 1 - d1, n - 1) for d1 in range(1, top))  # 余下 n-1 位从 d1+1..m-1 选
    return total


def solve() -> None:
    k, w = map(int, sys.stdin.read().split())
    print(count_r(k, w))


if __name__ == "__main__":
    solve()

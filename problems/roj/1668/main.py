#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 01:22
# update_at: 2026-10-01 01:22

import sys
from collections import Counter


def losing(count: Counter) -> bool:
    """当前局面先手是否必败。k1/k2 = 大小为 1/2 的堆数，n = 堆数，s = 石子总数。"""
    k1, k2 = count[1], count[2]
    n = sum(count.values())
    s = sum(a * c for a, c in count.items())
    if max(count) > 2:  # 有大堆：必败 ⇔ k1 为偶数 且 (s+n) 为奇数
        return k1 % 2 == 0 and (s + n) % 2 == 1
    # 只有 1、2 堆：k2<=1 时看 k1 模 3；k2 为奇数时看 k1 奇偶；k2 为偶数(>=2)时必胜
    return k1 % 3 == 0 if k2 < 2 else k1 % 2 == 0 if k2 % 2 else False


def solve() -> None:
    it = iter(map(int, sys.stdin.buffer.read().split()))
    print('\n'.join(  # 先读 T，再对每组先读 n、后读 n 个数
        "NO" if losing(Counter(next(it) for _ in range(next(it)))) else "YES"
        for _ in range(next(it))))


if __name__ == "__main__":
    solve()

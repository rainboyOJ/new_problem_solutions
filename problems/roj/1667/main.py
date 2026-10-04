#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 01:10
# update_at: 2026-10-01 01:10

import sys


def has_zero_subset(bars: list[int]) -> bool:
    """盒中是否存在一个非空子集，其异或和为 0（即棒长组线性相关）。

    逐个把棒长插入线性基：x 与基中每个元素异或，只会使最高位严格变小，
    所以 x 最终必为 0 或落入基中——这正是「子集异或和能否为 0」的判定。
    """
    basis: list[int] = []
    for x in bars:
        for b in basis:
            x = min(x, x ^ b)  # 与基中元素异或直到最高位无法再降
        if not x:
            return True  # x 被现有基表出 → 出现异或和为 0 的子集
        basis.append(x)
    return False


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    for _ in range(10):
        n = next(data)
        bars = [next(data) for _ in range(n)]
        # 先手能把任意非空子集一次性移出盒子：
        # 移出的部分若能凑出异或和为 0，先手就掌握一个后手永远拿不回的 Nim 必胜态
        win = has_zero_subset(bars)
        print('NO' if win else 'YES')  # 胜则 NO，负则 YES


if __name__ == "__main__":
    solve()

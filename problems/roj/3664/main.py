#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 14:11
# update_at: 2026-10-02 14:11

import sys


def split_powers(n: int) -> list[int]:
    """优秀的拆分：取 n 二进制中每个置位 k（k >= 1）对应的 2^k，按 k 从大到小排列。

    二进制展开是把正整数写成"不同 2 的幂之和"的唯一方式，所以拆分合法
    当且仅当展开里不需要 2^0，即 n 是偶数；此时直接删掉第 0 位就是答案。
    """
    if n & 1:  # 奇数必须用到 2^0 = 1，而 1 不是 2 的正整数次幂
        return []
    return [1 << k for k in range(n.bit_length() - 1, 0, -1) if n >> k & 1]


def solve() -> None:
    n = int(sys.stdin.buffer.read())
    powers = split_powers(n)
    print(' '.join(map(str, powers)) if powers else -1)


if __name__ == "__main__":
    solve()

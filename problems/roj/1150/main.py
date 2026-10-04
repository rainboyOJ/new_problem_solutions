#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 21:03
# update_at: 2026-09-30 09:15

import sys


def perfect_upto(n: int) -> list[int]:
    """返回 [2, n] 内的全部完全数，从小到大。

    n ≤ 1000，直接枚举每个 i，用试除法累加真因子：成对枚举 d 与 i//d，
    每个数只试到 √i，总代价 O(n√n)，与 std.cpp 同阶。
    """
    ans: list[int] = []
    for i in range(2, n + 1):
        s = 1                                    # 1 是所有 i ≥ 2 的真因子，先记上
        d = 2
        while d * d < i:                         # d < √i 时补上成对因子 (d, i//d)
            if i % d == 0:
                s += d + i // d
            d += 1
        if d * d == i:                            # i 恰为完全平方数，√i 只算一次
            s += d
        if s == i:
            ans.append(i)
    return ans


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)  # 上界 n
    print('\n'.join(map(str, perfect_upto(n))))


if __name__ == "__main__":
    solve()

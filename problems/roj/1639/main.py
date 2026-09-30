#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 23:31
# update_at: 2026-09-30 23:31

import sys
from itertools import count

MOD = [23, 28, 33]      # 体力、情感、智力三个周期的长度
M = 23 * 28 * 33        # 21252：三个周期的公共周期，答案必落在其中


def triple_peak(rem: list[int]) -> int:
    """求 x ≡ rem[k] (mod MOD[k]) 的最小非负解（中国剩余定理）。"""
    return sum(
        r * (M // m) * pow(M // m, -1, m)  # M//m 与其逆的乘积只在 mod m 处取 1，其余模数处取 0
        for m, r in zip(MOD, rem)
    ) % M


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []

    for case in count(1):
        p, e, i, d = next(data), next(data), next(data), next(data)
        if p == e == i == d == -1:  # 输入结束哨兵
            break

        # 同天时刻 x 满足三个同余；下一次严格晚于 d 的同天时刻相距 (x - d) mod M，
        # 恰好落在 d 上时按题意跳过，答案取整个周期 M
        days = (triple_peak([p, e, i]) - d - 1) % M + 1
        out.append(f"Case {case}: the next triple peak occurs in {days} days.")

    print('\n'.join(out))


if __name__ == "__main__":
    solve()

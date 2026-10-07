#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 04:05
# update_at: 2026-10-08 04:05

import sys


def count_pairs(n: int) -> int:
    """统计 [1,n] 内满足 gcd(a,b) = a xor b 的无序数对 (a,b) 个数。

    gcd(a,b) = a xor b 迫使 gcd(a,b) = a-b = a xor b = c（等号链），
    故只需枚举公约数 c 与它的倍数 a = b + c，再验证 b + c 相加不进位。
    """
    ans = 0
    # c 是较小的数 b，同时充当公约数：b = c, a = k*c（k >= 2）
    for c in range(1, n // 2 + 1):
        # (a - c) & c == 0 说明低位的 1 不重叠，即 a = (a-c) + c 不进位、异或等于 c
        ans += sum(1 for a in range(c + c, n + 1, c) if (a - c) & c == 0)
    return ans


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    n = int(next(data))  # 单点单整数，全文只有这一个 token
    print(count_pairs(n))


if __name__ == "__main__":
    solve()

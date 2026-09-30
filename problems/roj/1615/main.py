#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 22:19
# update_at: 2026-09-30 22:19

import sys

MOD = 200907  # 题目指定的模数


def nth_term(a: int, b: int, c: int, k: int) -> int:
    """前三项为 a,b,c 的等差或等比序列，求第 k 项对 MOD 的值。"""
    is_arith = 2 * b == a + c  # 前三项等差 ⇔ 中项的两倍等于首尾和；否则必为等比
    if is_arith:
        # 等差通项 a + (k-1)d，d = b-a ≥ 0；k 可达 1e9，先取模再输出
        return (a + (k - 1) * (b - a)) % MOD
    # 等比通项 a·r^(k-1)，公比 r = b/a 为整数（数据保证 a 整除 b）；
    # 三参数 pow 是二进制快速幂，O(log k) 次乘法边乘边取模
    return a % MOD * pow(b // a, k - 1, MOD) % MOD


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    T = next(data)

    out: list[str] = []
    for _ in range(T):
        a, b, c, k = next(data), next(data), next(data), next(data)
        out.append(str(nth_term(a, b, c, k)))

    print('\n'.join(out))


if __name__ == "__main__":
    solve()

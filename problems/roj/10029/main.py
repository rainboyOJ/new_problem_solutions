#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 19:07
# update_at: 2026-10-02 19:07

import sys

MOD = 1_000_000_007


def solve() -> None:
    """读入 N，输出 N 的回文拆分数 mod 1e9+7。"""
    n = int(sys.stdin.buffer.read())

    # f[k] = k 的回文拆分数。由归纳定义推出：f(1)=1，
    # 奇数与前一个偶数相等 f(2m+1)=f(2m)，偶数再叠上"两半相同"的 f(m)。
    f = [0, 1] + [0] * (n - 1)
    for k in range(2, n + 1):
        f[k] = (f[k - 1] + (f[k // 2] if k % 2 == 0 else 0)) % MOD

    print(f[n])


if __name__ == "__main__":
    solve()

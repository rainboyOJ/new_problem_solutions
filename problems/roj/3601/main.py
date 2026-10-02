#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 10:05
# update_at: 2026-10-02 10:05

import sys


def inv_mod(a: int, b: int) -> int:
    """扩展欧几里得求逆元：返回最小正整数 x，使 a·x ≡ 1 (mod b)。

    不变量：余数 r0 ≡ 系数 s0 · a (mod b)。辗转相除结束时 r0 = gcd(a, b) = 1，
    于是 s0 就是 a 的一个逆元；对 b 取模落到 [0, b) 即最小正整数解。
    """
    r0, r, s0, s = a, b, 1, 0
    while r:
        q = r0 // r
        r0, r = r, r0 - q * r   # 标准辗转相除
        s0, s = s, s0 - q * s   # 系数同步消去，维持上面的同余不变量
    return s0 % b


def solve() -> None:
    a, b = map(int, sys.stdin.buffer.read().split())
    print(inv_mod(a, b))


if __name__ == "__main__":
    solve()

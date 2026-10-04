#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 23:35
# update_at: 2026-09-30 23:35

import sys


def ext_gcd(a: int, b: int) -> tuple[int, int, int]:
    """返回 (g, x, y) 满足 a*x + b*y = g = gcd(a, b)。"""
    if b == 0:
        return a, 1, 0
    g, x, y = ext_gcd(b, a % b)
    return g, y, x - (a // b) * y


def loop_times(a: int, b: int, c: int, k: int) -> str:
    """k 位系统里循环几次到达 B：解同余方程 c*t ≡ B-A (mod 2^k) 的最小非负 t。"""
    mod = 1 << k
    g, x, _ = ext_gcd(c, mod)   # c 在 mod 下的逆相关系数
    diff = b - a
    if diff % g:
        return "FOREVER"        # gcd 不整除差值 → 无解 → 死循环
    period = mod // g           # 解在模 period 意义下唯一
    return str(x * (diff // g) % period)


def solve() -> None:
    nums = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    for a, b, c, k in zip(nums, nums, nums, nums):  # 同一迭代器 zip 四次 = 每次取一行四个数
        if a == b == c == k == 0:
            break
        out.append(loop_times(a, b, c, k))
    print('\n'.join(out))


if __name__ == "__main__":
    solve()

#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 23:08
# update_at: 2026-09-30 23:08

import sys

IMPOSSIBLE = "Impossible"  # gcd(y-x, L) 不整除差值时的答案


def exgcd(a: int, b: int) -> tuple[int, int, int]:
    """返回 (g, s, t)，满足 a*s + b*t = g = gcd(a, b)，g 取非负。"""
    if b == 0:
        return a, 1, 0
    g, s, t = exgcd(b, a % b)
    return g, t, s - a // b * t  # 回代：a*x + b*y = g 的解由下层 (s,t) 推出


def solve() -> None:
    x, y, m, n, L = map(int, sys.stdin.buffer.read().split())

    # t 次跳跃后相遇 ⇔ x + m*t ≡ y + n*t (mod L) ⇔ (m-n)*t ≡ y-x (mod L)
    a = (m - n) % L            # 化成 0 ≤ a < L 的同余系数
    c = (y - x) % L            # 化成 0 ≤ c < L 的目标余数
    g, s, _ = exgcd(a, L)

    if c % g:
        print(IMPOSSIBLE)
    else:
        # a*s ≡ g (mod L)，两边乘 c/g 得特解，再除以 g/L 归一化周期
        step = L // g
        print(s * (c // g) % step)


if __name__ == "__main__":
    solve()

#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 23:30
# update_at: 2026-09-30 23:30

import sys
from math import gcd

NO_SOLUTION = -1  # 同余式组无解时的输出


def merge(state: tuple[int, int], r2: int, m2: int) -> tuple[int, int] | None:
    """把 x ≡ r2 (mod m2) 合并进 state = (r1, m1)，返回等价的最小同余式；无解返回 None。

    由 r1 + m1*k ≡ r2 得线性同余方程 m1*k ≡ r2-r1 (mod m2)：
    g = gcd(m1,m2) 不整除差值时无解，否则约去 g 后 m1/g 与 m2/g 互质，可直接求逆。
    k 取模 m2/g 的最小非负解，于是新余数 r1+m1*k 已落在 [0, lcm) 内，天然最小。
    """
    r1, m1 = state
    g = gcd(m1, m2)
    diff = r2 - r1
    if diff % g:
        return None
    k = diff // g * pow(m1 // g, -1, m2 // g) % (m2 // g)
    return r1 + m1 * k, m1 // g * m2


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    for n in data:
        # 模数两两不互质，套不了 CRT 的乘积公式，只能逐条合并同余式。
        pairs = [(next(data), next(data)) for _ in range(n)]
        state: tuple[int, int] | None = (0, 1)  # 空同余式组 x ≡ 0 (mod 1) 恒成立
        for m, a in pairs:
            if state is not None:  # 已判定无解就跳过计算，但仍要读完本组数据
                state = merge(state, a, m)
        out.append(str(NO_SOLUTION if state is None else state[0]))
    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    solve()

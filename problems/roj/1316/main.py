#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 04:54
# update_at: 2026-09-30 04:54

import sys


def count_forms(n: int) -> int:
    """返回自然数 n 按规则能生成的所有数的个数（含 n 本身）。

    记 f(i) 为 i 能生成的数的个数：i 本身算一个，再加上「左边补一个不超过 i/2 的
    数 x」得到的全部数，每个 x 贡献 f(x) 个，故 f(i) = 1 + sum(f(1..i//2))。
    与前一式作差：i 为奇数时 i//2 == (i-1)//2，不新增可用的前半段；
    i 为偶数时多出一项 f(i//2)，于是 f(i) = f(i-1) + (i 为偶数 ? f(i//2) : 0)。
    """
    f = [1] * (n + 1)                      # f[0] = f[1] = 1：0 和 1 都只能算自身
    for i in range(2, n + 1):
        f[i] = f[i - 1] + (f[i // 2] if i % 2 == 0 else 0)
    return f[n]


def solve() -> None:
    n = next(iter(map(int, sys.stdin.buffer.read().split())))
    print(count_forms(n))


if __name__ == "__main__":
    solve()

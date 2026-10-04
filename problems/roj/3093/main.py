#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 16:27
# update_at: 2026-10-01 16:27

import sys
from math import factorial

MOD = 10**9 + 9


def cycle_lengths(p: list[int]) -> list[int]:
    """排列每个轮换的长度（不含长度 1 的不动点，它们不参与任何交换）。"""
    n = len(p)
    seen = [False] * n
    return [length
            for start in range(n)
            if not seen[start]
            for length in [walk_cycle(start, p, seen)]]


def walk_cycle(start: int, p: list[int], seen: list[bool]) -> int:
    """从 start 沿置换走一圈，标访问并返回这一圈的长度。"""
    length = 0
    j = start
    while not seen[j]:
        seen[j] = True
        j = p[j] - 1  # p 存的是 1-based 的值，走的是「值 → 下标」这一步
        length += 1
    return length


def count_min_swaps(n: int, p: list[int]) -> int:
    """最少 m 次交换把 p 排好序的方案数。

    m = n - 轮换个数；每次交换使轮换个数恰好 +1（分裂），所以最短方案中
    每次交换都分裂一个轮换。逆着操作看是把 c 个元素合并成 c-轮换，由
    Dénes 定理（Cayley 公式）恰有 c^(c-2) 种合并方式；再乘上
    m 次操作的自由穿插 m!，除掉每组内部相对顺序 (c-1)!。
    """
    lengths = cycle_lengths(p)
    m = n - len(lengths)  # 最少交换次数
    ans = factorial(m) % MOD
    for c in lengths:
        if c > 1:
            ans = ans * pow(c, c - 2, MOD) % MOD              # 该组的合并方式数
            ans = ans * pow(factorial(c - 1), MOD - 2, MOD) % MOD  # 除以 (c-1)! 取模
    return ans


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    T = next(data)

    for _ in range(T):
        n = next(data)
        p = [next(data) for _ in range(n)]
        out.append(str(count_min_swaps(n, p)))

    print('\n'.join(out))


if __name__ == "__main__":
    solve()

#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 17:43
# update_at: 2026-09-29 17:50

import sys
from collections.abc import Iterator


def fraction_terms(n: int) -> Iterator[float]:
    """依次产出分数序列的前 n 项：分母接上一项的分子，新分子是两者之和。"""
    p, q = 1, 2  # p_1 = 1，q_1 = 2
    for _ in range(n):
        yield q / p
        p, q = q, p + q  # 下一项的分母换成当前项的分子


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)  # 求和的项数
    print(f"{sum(fraction_terms(n)):.4f}")


if __name__ == "__main__":
    solve()

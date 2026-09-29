#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com  github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 20:02
# update_at: 2026-09-29 20:02

import sys
from collections.abc import Iterable, Iterator


def transpose(rows: Iterable[Iterable[int]]) -> Iterator[tuple[int, ...]]:
    """转置矩阵：第 j 行输出原矩阵的第 j 列。"""
    return zip(*rows)


def solve() -> None:
    lines = iter(sys.stdin.read().split('\n'))
    n, m = map(int, next(lines).split())                  # 行数 n、列数 m

    a = [list(map(int, next(lines).split())) for _ in range(n)]

    at = transpose(a)                                     # AT 共 m 行、每行 n 个
    sys.stdout.write('\n'.join(' '.join(map(str, row)) for row in at) + '\n')


if __name__ == "__main__":
    solve()

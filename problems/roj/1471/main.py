#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 12:43
# update_at: 2026-09-30 12:43

import sys
from itertools import pairwise


def has_prefix_pair(words: list[bytes]) -> bool:
    """判断是否存在两个串互为前缀：排序后只需看相邻两串（等串也算）。"""
    return any(b.startswith(a) for a, b in pairwise(sorted(words)))


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    out: list[str] = []
    T = int(next(data))

    for _ in range(T):
        n = int(next(data))
        words = [next(data) for _ in range(n)]
        # 有前缀对输出 NO，否则输出 YES（题面的反直觉对应关系）
        out.append("NO" if has_prefix_pair(words) else "YES")

    print("\n".join(out))


if __name__ == "__main__":
    solve()

#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 09:38
# update_at: 2026-10-01 09:38

import sys
from collections.abc import Iterator


def schemes(n: int, chosen: int = 0, nxt: int = 1) -> Iterator[list[int]]:
    """递归枚举下标 nxt 选或不选；chosen 第 i-1 位为 1 表示整数 i 已选。"""
    if nxt > n:
        # 叶子：把位掩码还原成升序序列，没有选中任何数时还原成空列表
        yield [i for i in range(1, n + 1) if chosen >> (i - 1) & 1]
        return
    yield from schemes(n, chosen, nxt + 1)                     # 不选 nxt
    yield from schemes(n, chosen | 1 << (nxt - 1), nxt + 1)    # 选 nxt


def solve() -> None:
    n = int(sys.stdin.buffer.read())  # 题面只有一个整数 n
    print("\n".join(" ".join(map(str, choice)) for choice in schemes(n)))


if __name__ == "__main__":
    solve()

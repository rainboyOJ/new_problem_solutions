#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 11:30
# update_at: 2026-09-29 11:40

import sys
from collections.abc import Iterator


def next_case(tokens: Iterator[int]) -> tuple[int, list[int]] | None:
    """读出下一组数据 (n, a)；输入耗尽时返回 None。"""
    try:
        n = next(tokens)
    except StopIteration:
        return None
    return n, [next(tokens) for _ in range(n)]


def alice_wins(a: list[int]) -> bool:
    """判定该局面是否 Alice 必胜。"""
    # 唯一的必胜态：只剩一堆且为偶数 —— Alice 一次拿光，Bob 面对空局
    return len(a) == 1 and a[0] % 2 == 0


def solve() -> None:
    tokens = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []

    while (case := next_case(tokens)) is not None:
        _n, a = case
        out.append("YES" if alice_wins(a) else "NO")

    print("\n".join(out))


if __name__ == "__main__":
    solve()

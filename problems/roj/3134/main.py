#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 19:08
# update_at: 2026-10-01 19:09

import sys
from functools import cache


@cache
def count(rows: tuple[int, ...], caps: tuple[int, ...]) -> int:
    """已放好 rows[i] 个人的状态下，继续从高到低放完所有人（ tallest 未放者）的方案数。"""
    if rows == caps:  # 所有位置都放满，剩下的恰好填满
        return 1
    # 当前最高的未放者必须站在某排最左的空位：第 i 排未满，
    # 且它前面一排（更靠后）已放人数更多，保证列不悬空。
    return sum(
        count(rows[:i] + (r + 1,) + rows[i + 1:], caps)
        for i, r in enumerate(rows)
        if r < caps[i] and (i == 0 or rows[i - 1] > r)
    )


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []

    while (k := next(data)) != 0:
        caps = tuple(next(data) for _ in range(k))  # 从后向前每排容量，非增
        out.append(str(count((0,) * k, caps)))

    print('\n'.join(out))


if __name__ == "__main__":
    solve()

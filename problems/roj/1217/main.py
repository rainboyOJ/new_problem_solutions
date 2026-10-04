#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 00:03
# update_at: 2026-09-30 00:21

import sys
from functools import cache


@cache
def count(rows: tuple[int, ...], row: int, k: int, used: int) -> int:
    """第 row 行及以下放完剩余棋子、已占列集合为 used 时的方案数。

    每放一枚棋子必然占掉一列，所以"已经放了几枚"由 used 里 1 的个数决定，
    不必再单独传一个参数——这正是把状态从"摆到哪"换成"占了哪些列"的收益。
    """
    rest = k - used.bit_count()                   # 还差几枚棋子没放
    if rest == 0:
        return 1                                  # 棋子恰好放完：记一种方案
    if len(rows) - row < rest:
        return 0                                  # 剩下的行数不够摆，本分支作废
    free = rows[row] & ~used                      # 本行既能放、列又还空闲的位置
    return count(rows, row + 1, k, used) + sum(
        count(rows, row + 1, k, used | 1 << c)    # 本行在第 c 列摆一枚
        for c in range(len(rows))
        if free >> c & 1
    )


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    out: list[str] = []
    while True:
        n, k = int(next(data)), int(next(data))
        if n == -1 and k == -1:                   # 题面的输入结束标记
            break
        # 每行压成一个 n 位列掩码：第 c 位为 1 表示 (row, c) 是可放的 '#'
        rows = tuple(
            sum(1 << c for c, cell in enumerate(next(data).decode()) if cell == '#')
            for _ in range(n)
        )
        out.append(str(count(rows, 0, k, 0)))
        count.cache_clear()                       # 换棋盘就换命名空间，缓存不跨题累积
    print('\n'.join(out))


if __name__ == "__main__":
    solve()

#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 23:53
# update_at: 2026-09-30 00:11

from collections.abc import Iterator

SIZE = 8                      # 棋盘边长，本题固定为八皇后
ALL_ROWS = (1 << SIZE) - 1    # 八行全满：掩码的低 8 位全是 1


def queens(cols: int, d1: int, d2: int) -> Iterator[tuple[int, ...]]:
    """按列深搜，依次产出每个解：第 c 项是第 c 列皇后所在的行号（0 起）。

    cols / d1 / d2 分别是已被占用的行、副对角线（左上→右下）、
    主对角线（左下→右上）掩码；列每右移一格，两条对角线掩码就各整体移位一位，
    于是"对角线冲突"退化成一次位与。每层都先取最低位的可放行，
    所以产出顺序就是题目样例的顺序：列优先，每列按行号升序。
    """
    if cols == ALL_ROWS:                  # 八列都放好了，前缀就是一个完整解
        yield ()
        return
    avail = ALL_ROWS & ~(cols | d1 | d2)  # 这一列还能落在哪些行
    while avail:
        bit = avail & -avail              # 最低位的可行行
        avail ^= bit                      # 该行枚举过就划掉
        for tail in queens(cols | bit, (d1 | bit) << 1, (d2 | bit) >> 1):
            yield (bit.bit_length() - 1,) + tail   # 行号 = 二进制位数 - 1


def board(solution: tuple[int, ...]) -> Iterator[str]:
    """把一个解翻译成 8 行 `0/1` 棋盘文本：第 r 行只有 solution[c] == r 的那格是 1。"""
    yield from (
        ' '.join('1' if solution[c] == r else '0' for c in range(SIZE)) + ' '
        for r in range(SIZE)
    )


def solve() -> None:
    solutions = list(queens(0, 0, 0))     # 八皇后共 92 个解，按列枚举一次全部展开
    out: list[str] = []
    for no, solution in enumerate(solutions, 1):
        out.append(f'No. {no}')
        out += board(solution)
    print('\n'.join(out))


if __name__ == "__main__":
    solve()

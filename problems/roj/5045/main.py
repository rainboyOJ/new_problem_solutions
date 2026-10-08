#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 20:37
# update_at: 2026-10-08 20:37

import sys


def rows_of_pascal(n: int) -> list[list[int]]:
    """按 a[i][j] = a[i-1][j-1] + a[i-1][j] 递推构造杨辉三角前 n 行。"""
    rows = [[1]]
    for i in range(1, n):
        prev = rows[-1]
        rows.append([1] + [prev[j] + prev[j + 1] for j in range(i - 1)] + [1])
    return rows


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    # 每行数之间恰一个空格，行末无多余空格；print 末尾补的那个 \n 就是换行
    print('\n'.join(' '.join(map(str, row)) for row in rows_of_pascal(n)))


if __name__ == "__main__":
    solve()

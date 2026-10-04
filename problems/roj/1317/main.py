#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 04:53
# update_at: 2026-09-30 04:53

import sys


def combos(n: int, r: int):
    """按字典序递归产出 1..n 中取 r 个的严格递增组合。"""
    if r == 0:  # 不再取数：当前前缀就是一个完整组合
        yield ()
        return
    # 还要取 r 个数，下一个数最大只能到 n-r+1，否则后面取不满
    for head in range(1, n - r + 2):
        for tail in combos(n - head, r - 1):  # 从 head+1..n 里再取 r-1 个（平移成 1..n-head）
            yield (head,) + tuple(head + value for value in tail)


def solve() -> None:
    n, r = map(int, sys.stdin.buffer.read().split())
    # 题面的「占三个字符」实为标准程序的 "  "+十进制：两位数多占一格
    lines = (''.join(f'  {value}' for value in combo) for combo in combos(n, r))
    sys.stdout.write('\n'.join(lines) + '\n')


if __name__ == '__main__':
    solve()

#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 20:04
# update_at: 2026-09-29 20:04

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)  # 图像行数、列数
    src = [[next(data) for _ in range(m)] for _ in range(n)]

    # 边界像素原样继承，所以直接复制一份再只改内部
    res = [row[:] for row in src]
    for r in range(1, n - 1):
        for c in range(1, m - 1):
            # 十字 5 格之和：自身 + 上下左右
            cross = src[r][c] + src[r - 1][c] + src[r + 1][c] + src[r][c - 1] + src[r][c + 1]
            # 和是整数，除以 5 的小数部分只可能是 .0/.2/.4/.6/.8，不会出现 .5，
            # 所以 (2*cross+5)//10 就是普通四舍五入，不用 round()
            res[r][c] = (2 * cross + 5) // 10

    print('\n'.join(' '.join(map(str, row)) for row in res))


if __name__ == "__main__":
    solve()

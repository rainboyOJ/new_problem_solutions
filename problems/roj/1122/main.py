#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com  github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 19:50
# update_at: 2026-09-29 19:50

import sys


def solve() -> None:
    a = [list(map(int, line.split())) for line in sys.stdin.read().split('\n')[:5]]

    col_min = [min(col) for col in zip(*a)]                      # 每列的最小值

    # 鞍点：行最大值位置恰好也是该列最小值；矩阵保证唯一，next 找不到给默认值
    ans = next(
        ((i + 1, j + 1, row[j])
         for i, row in enumerate(a)                                # 逐行找最大值所在列 j
         for j in [max(range(5), key=lambda j: row[j])]
         if row[j] == col_min[j]),
        None)

    print('not found' if ans is None else '{} {} {}'.format(*ans))


if __name__ == "__main__":
    solve()

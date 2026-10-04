#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 11:52
# update_at: 2026-10-01 11:55

import heapq
import sys
from itertools import islice


def merge_top_n(a: list[int], b: list[int], n: int) -> list[int]:
    """把「前若干个序列能凑出的最小 n 个和」再叠加一个序列 b，返回新的最小 n 个和。

    a、b 都非降序且各含 n 个数；只需考虑加法表 a[i] + b[j]（n x n 个格子）中最小的 n 个。
    坑点是去重：每个格子只能入堆一次，所以固定每个格子的生成者——非第一列的 (i, j)
    只由左邻 (i, j-1) 生成；第一列的 (i, 0) 则在弹出 (i-1, 0) 时顺延生成。
    """
    table = [(a[0] + b[0], 0, 0)]      # 候选三元组 (和, 与 a 配对的下标, 与 b 配对的下标)
    result: list[int] = []
    for _ in range(n):
        total, i, j = heapq.heappop(table)
        result.append(total)
        if j == 0 and i + 1 < n:                       # 第一列：顺延出下一行的开头 a[i+1] + b[0]
            heapq.heappush(table, (a[i + 1] + b[0], i + 1, 0))
        if j + 1 < n:                                  # 同一行内把 b 往后挪一格
            heapq.heappush(table, (a[i] + b[j + 1], i, j + 1))
    return result


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []

    for _ in range(next(data)):                        # T 组测试用例
        m, n = next(data), next(data)

        rows: list[list[int]] = []
        for _ in range(m):
            length = n                                 # 题面保证每个序列恰好 n 个数
            rows.append(sorted(islice(data, length)))  # 只有最小的 n 个数可能参与答案，先排好序

        top = rows[0]                                  # 只取第一个序列时，「最小的 n 个和」就是它自己
        for row in rows[1:]:
            top = merge_top_n(top, row, n)

        out.append(' '.join(map(str, top)))

    print('\n'.join(out))


if __name__ == "__main__":
    solve()

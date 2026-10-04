#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 11:03
# update_at: 2026-10-01 11:04

import sys
from itertools import accumulate


def solve() -> None:
    """枚举上下边界，按列求和压成一维，再用 Kadane 求最大子段和。"""
    data = sys.stdin.read().split()
    n = int(data[0])
    a = [[int(x) for x in data[1 + i * n:1 + (i + 1) * n]] for i in range(n)]

    # s[i][c] = 前 i 行第 c 列的元素和，s[0] 全 0 作哨兵
    s = list(accumulate([[0] * n] + a,
                        lambda pre, row: [p + x for p, x in zip(pre, row)]))

    # 固定行区间 [i, j)：第 c 列的竖条和为 s[j][c] - s[i][c]，
    # accumulate 递推 cur = max(cur, 0) + colsum 正是一维 Kadane
    ans = max(
        max(accumulate((s[j][c] - s[i][c] for c in range(n)),
                       lambda cur, x: cur + x if cur > 0 else x))
        for i in range(n) for j in range(i + 1, n + 1)
    )
    print(ans)


if __name__ == "__main__":
    solve()

#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 03:07
# update_at: 2026-10-01 03:11

import sys
from functools import reduce


def extend(above: list[int], row: list[int]) -> list[int]:
    """把“走到上一行为止的最大路径和”延伸到本行：每格只可能从正上方或左上方走来。

    先把上一行首尾各复制一份（`above[0]` 补在左边、`above[-1]` 补在右边），
    第 j 格的两个来源就固定是补长后的 `sources[j]` 与 `sources[j+1]`；
    越界一侧复制到的正是自己，`max` 于是等价于“该格只有一个来源”。
    """
    sources = [above[0], *above, above[-1]]
    return [v + max(sources[j], sources[j + 1]) for j, v in enumerate(row)]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    row_count = next(data)                                     # 题面的 R
    # 第 i 层恰好有 i 个数，按三角结构逐层消费 token，不依赖文件在哪里换行
    rows = (
        [next(data) for _ in range(length)]
        for length in range(1, row_count + 1)
    )
    # 自顶向下折叠：每折一层得到该层每格的最大路径和，只需保留最新一行
    print(max(reduce(extend, rows)))


if __name__ == "__main__":
    solve()

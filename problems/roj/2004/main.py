#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 02:28
# update_at: 2026-10-01 02:28

import sys


def merge(spans: list[tuple[int, int]]) -> list[list[int]]:
    """把挤奶区间并成互不相邻的极大连通块。

    输入已按左端点升序，所以新区间只可能和「最后一个」块重叠：接得上就并入，
    接不上就开新块，不必回头检查更早的块。
    """
    blocks: list[list[int]] = []
    for start, end in spans:
        if blocks and start <= blocks[-1][1]:          # 重叠、或恰好首尾相接
            blocks[-1][1] = max(blocks[-1][1], end)    # 被包含的区间不能缩短右端
        else:
            blocks.append([start, end])
    return blocks


def solve() -> None:
    data = sys.stdin.buffer.read().split()
    n = int(data[0])
    # 每行两个整数：先读左端点，元组排序即按左端点升序
    spans = sorted((int(data[1 + 2 * i]), int(data[2 + 2 * i])) for i in range(n))

    blocks = merge(spans)
    milked = max(end - start for start, end in blocks)  # 有奶：取最长的块
    gaps = (next_start - prev_end                       # 空档只出现在相邻两块之间
            for (_, prev_end), (next_start, _) in zip(blocks, blocks[1:]))
    idle = max(gaps, default=0)                         # 只有一块时不存在空档

    print(milked, idle)


if __name__ == "__main__":
    solve()

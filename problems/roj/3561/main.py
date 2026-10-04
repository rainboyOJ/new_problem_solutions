#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47

import sys

rows: list[list[int]]  # rows[i] = i 与 i+1 行之间开通道能隔开的说话对数
cols: list[list[int]]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    m, n, k, l, d = next(data), next(data), next(data), next(data), next(data)

    # 统计每个"行缝"（i 与 i+1 行之间）和"列缝"（j 与 j+1 列之间）各能隔开几对
    rows = [0] * m
    cols = [0] * n
    for _ in range(d):
        x, y, p, q = next(data), next(data), next(data), next(data)
        if x == p:
            cols[min(y, q)] += 1
        else:
            rows[min(x, p)] += 1

    # 各取隔开对数最多的 K / L 条缝：排序后取前 K（L）个下标再升序输出
    row_id = sorted(range(1, m), key=lambda i: -rows[i])[:k]
    col_id = sorted(range(1, n), key=lambda j: -cols[j])[:l]
    print(' '.join(map(str, sorted(row_id))))
    print(' '.join(map(str, sorted(col_id))))


if __name__ == "__main__":
    solve()

#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 06:11
# update_at: 2026-10-01 06:11

import sys


def find_lds_with_unique_ways(prices: list[int]) -> tuple[int, int]:
    """计算最长严格下降子序列的长度以及数值去重后的最长方案数。"""
    # 追加 0 作为末尾哨兵，汇聚所有最长下降子序列终点
    extended = prices + [0]
    total_len = len(extended)
    lengths = [1] * total_len
    ways = [1] * total_len

    for i in range(total_len):
        cur_price = extended[i]
        best_len = 1
        for j in range(i):
            if extended[j] > cur_price and lengths[j] + 1 > best_len:
                best_len = lengths[j] + 1
        lengths[i] = best_len

        if best_len == 1:
            ways[i] = 1
        else:
            total_ways = 0
            visited: set[int] = set()
            target_len = best_len - 1
            # 倒序遍历取同数值的最靠后位置，避免前驱数值相同的子序列重复累加
            for j in range(i - 1, -1, -1):
                prev_price = extended[j]
                if prev_price > cur_price and lengths[j] == target_len and prev_price not in visited:
                    visited.add(prev_price)
                    total_ways += ways[j]
            ways[i] = total_ways

    return lengths[-1] - 1, ways[-1]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    prices = [next(data) for _ in range(n)]

    max_len, total_schemes = find_lds_with_unique_ways(prices)
    print(f"{max_len} {total_schemes}")


if __name__ == "__main__":
    solve()

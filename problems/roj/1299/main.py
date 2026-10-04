#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 03:53
# update_at: 2026-09-30 03:53

import sys

NEG = -(1 << 60)  # 不可达哨兵：最大合法总和仅 10^8，再叠加一件糖果后仍远小于 0


def best_multiple(candies: list[int], k: int) -> int:
    """返回能带走的糖果总数最大值（必须是 k 的倍数），凑不出 k 的倍数时返回 0。

    dp[j] = 只扫过前面的糖果、且当前总数对 k 取余恰为 j 时能达到的最大总数，
    NEG 表示该余数暂时凑不出来。dp[0] 恒 >= 0（一件都不取的方案），所以它天然
    满足“凑不出就输出 0”，不需要额外兜底。
    """
    dp = [0] + [NEG] * (k - 1)  # 一件都不拿：总数 0，余数 0 可达
    for value in candies:
        r = value % k
        # 每件糖果只有“不取”（保留 dp[j]）和“取”（从余数 (j-r) mod k 转移、总数加 value）
        # 两种去向；右侧整体读旧表，保证同一件糖果不会被取两次。
        dp = [max(keep, dp[(j - r) % k] + value) for j, keep in enumerate(dp)]
    return dp[0]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, k = next(data), next(data)
    candies = [next(data) for _ in range(n)]
    print(best_multiple(candies, k))


if __name__ == "__main__":
    solve()

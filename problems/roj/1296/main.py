#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 03:41
# update_at: 2026-09-30 03:41

import sys

NONE = 0  # 位置升序，i 前面可能一家都接不上；利润恒正，0 就是「没有前驱」的哨兵


def max_profit(spots: list[int], profits: list[int], k: int) -> int:
    """求「任选若干地点且相邻两店距离严格大于 k」的最大利润和。

    dp[i] 表示以第 i 个地点收尾时的最大利润：要么前面一家都不开（前驱利润记 NONE），
    要么接在某个满足 spots[i] - spots[j] > k 的地点 j 后面。
    每个 i 只依赖前面这一段的 dp 最优值，所以单独扫一遍前缀即可。
    """
    dp = profits[:]  # 初值 = 只开 i 这一家
    for i in range(len(spots)):
        # spots 升序，能接的前驱必定是前缀；取该前缀上 dp 的最大值
        dp[i] += max((dp[j] for j in range(i) if spots[i] - spots[j] > k), default=NONE)
    return max(dp)


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    T = next(data)  # 测试数据组数
    out: list[str] = []

    for _ in range(T):
        n, k = next(data), next(data)          # 地点数、距离限制
        spots = [next(data) for _ in range(n)]  # 升序的位置序列 m
        profits = [next(data) for _ in range(n)]
        out.append(str(max_profit(spots, profits, k)))

    print('\n'.join(out))


if __name__ == "__main__":
    solve()

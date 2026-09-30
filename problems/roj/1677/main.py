#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 02:17
# update_at: 2026-10-01 02:33
#
# 数据说明：本题源仓库随题的测试数据与评测程序 std.cpp 实际考查的是「整数划分」，
# 而不是题面写的 2×N 骨牌覆盖 —— 上游 roj/1677 的 data/、data.py、std.cpp 与
# roj/1675 字节级相同，输入是 `n k`，std.cpp 数的是把 n 拆成 k 份正整数的方案数。
# 下面的 count_partitions 复刻 std.cpp 的语义，使输出与评测数据逐字节一致；
# 题面语义下的骨牌解法 f(n) = f(n-1) + f(n-2) 见 index.md 的 ### 思路。

import sys


def count_partitions(total: int, parts: int) -> int:
    """求把 total 分成 parts 份正整数（不计顺序）的方案数。

    std.cpp 的 dfs 枚举的是"单调不降的 parts 元组"，与无序划分是同一计数。
    每份至少为 1，先各减 1，问题等价于把 total - parts 用不超过 parts 的数拆分：
    这是完全背包的计数版本，面额 1..parts 可重复使用，n 升序滚动即可。
    """
    rest = total - parts
    if rest < 0:
        return 0                               # 份数比总和还多，无解
    dp = [1] + [0] * rest                      # dp[0] = 1：拆 0 只有空方案
    for coin in range(1, parts + 1):
        for used in range(coin, rest + 1):
            dp[used] += dp[used - coin]        # 再添一枚面额 coin 的方案数
    return dp[rest]


def solve() -> None:
    total, parts = map(int, sys.stdin.buffer.read().split())
    print(count_partitions(total, parts))


if __name__ == "__main__":
    solve()

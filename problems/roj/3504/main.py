#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 03:50
# update_at: 2026-10-02 03:50

import sys

N = 1000  # 题面 n 的上界


def build_counts(limit: int) -> list[int]:
    """count[n] = n 经上述规则能生成的全部数的个数（含 n 自己）。

    直接按定义转移是 O(n^2) 的；注意 f(1..n/2) 恰好是 count 的连续前缀，
    所以用前缀和 sum_pre[m] = f(1)+...+f(m) 把转移降为 O(1)。
    """
    count = [0] * (limit + 1)      # f(n)：n 自己算一个生成的数
    sum_pre = [0] * (limit + 1)    # sum_pre[m] = f(1) + f(2) + ... + f(m)
    for n in range(1, limit + 1):
        # n 生成的数 = {n} ∪ {拼接(g, n) : g ∈ m 生成的数, 1<=m<=n/2}；位数可反解，单射不重
        count[n] = 1 + sum_pre[n // 2]
        sum_pre[n] = sum_pre[n - 1] + count[n]
    return count


count = build_counts(N)


def solve() -> None:
    n = int(sys.stdin.read())
    print(count[n])


if __name__ == "__main__":
    solve()

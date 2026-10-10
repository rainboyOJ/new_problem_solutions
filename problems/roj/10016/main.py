#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-10 07:12
# update_at: 2026-10-10 08:23
import sys


def solve() -> None:
    """dp[i][j][s]：前 i 个位置用了 j 次修改、i 是否为山谷点时的最大价值。"""
    data = iter(map(int, sys.stdin.buffer.read().split()))
    try:
        n, k = next(data), next(data)
    except StopIteration:
        return

    a = [0] + [next(data) for _ in range(n)] + [0]   # a[1..n]，两端补 0 便于取邻居
    # 转移只依赖 i-1 一行，所以滚动成一维：prev 是 i-1 行，cur 是第 i 行；状态量 O(nk) 降到 O(k)
    prev0, prev1 = [0] * (k + 1), [0] * (k + 1)
    cur0, cur1 = [0] * (k + 1), [0] * (k + 1)
    ans = 0

    for i in range(2, n):                            # 首尾都不可能是山谷点
        left, mid, right = a[i - 1], a[i], a[i + 1]
        is_valley = mid < left and mid < right       # 原本就是山谷点，不花修改次数
        best_lowered = min(left, right) - 1          # 花 1 次修改后 a[i] 能达到的最大值
        for j in range(k + 1):
            if is_valley:
                cur1[j] = prev0[j] + mid             # 保留它：前一个位置不能是山谷点
                cur0[j] = prev1[j]                   # 放弃它：只能因为前一个位置成了山谷点
            else:
                cur1[j] = prev0[j - 1] + best_lowered if j else 0
                cur0[j] = max(prev0[j], prev1[j])
            ans = max(ans, cur0[j], cur1[j])
        prev0, cur0 = cur0, prev0
        prev1, cur1 = cur1, prev1

    print(ans)


if __name__ == "__main__":
    solve()

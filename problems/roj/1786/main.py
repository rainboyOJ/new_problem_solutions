#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 02:28
# update_at: 2026-10-08 02:28

import sys


def chain(f: list[int], pre: list[int]) -> list[int]:
    """回答"一条同余链上每个位置的最佳转移"：返回转移后的链 g。

    链上第 i 个位置的容量是 r + i*s，g[i] = max{ f[t] + pre[i-t] : 0 <= t <= i }。
    pre 是凹函数（增量单调不增），故任意两个决策点 t1 < t2 的优劣至多反转一次，
    argmax 关于 i 单调不减 —— 用分治优化，每个结点只扫 [optl, mid] 这一段。
    显式栈代替递归，避免链长达 1e5 时爆栈。
    """
    length = len(f) - 1
    g = [0] * (length + 1)
    stack = [0, length, 0, length]    # 依次压入 (左界, 右界, 决策下界, 决策上界)
    while stack:
        opt_hi = stack.pop(); opt_lo = stack.pop()
        right = stack.pop(); left = stack.pop()
        mid = (left + right) >> 1
        lo = opt_lo
        hi = opt_hi if opt_hi < mid else mid   # 转移来源 t 不能超过当前位 i
        best = f[lo] + pre[mid - lo]
        best_t = lo
        for t in range(lo + 1, hi + 1):
            cand = f[t] + pre[mid - t]
            if cand > best:
                best = cand
                best_t = t
        g[mid] = best
        if left <= mid - 1:                   # 左半段的决策上界收到 best_t
            stack += (left, mid - 1, opt_lo, best_t)
        if mid + 1 <= right:                  # 右半段的决策下界抬到 best_t
            stack += (mid + 1, right, best_t, opt_hi)
    return g


def use_group(dp: list[int], values: list[int], s: int) -> None:
    """把体积为 s 的一整组物品并入 dp（原地更新 dp[0..m]）。

    同体积物品取 k 个一定取价值最大的 k 个，所以组内降序后做前缀和 pre[k]；
    k 超过组内个数时常数延拓 = 取价值 0 的幽灵物品，因 dp 单调不减而永不更优，
    于是窗口约束消失，转移简化为按 j mod s 拆链后的卷积。
    """
    values.sort(reverse=True)                 # 组内价值降序 => pre 凹
    m = len(dp) - 1
    k_max = m // s                            # 链上最多取 k_max 个（i - t <= k_max）
    pre = [0] * (k_max + 1)
    acc = 0
    for k in range(1, k_max + 1):
        if k <= len(values):
            acc += values[k - 1]
        pre[k] = acc                          # k > 组内个数时保持常数（延拓）

    for r in range(min(s, m + 1)):            # 余数 r 的链：容量 r, r+s, r+2s, ...
        dp[r::s] = chain(dp[r::s], pre)


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    m = next(data)

    groups: dict[int, list[int]] = {}         # 体积 -> 该体积的所有物品价值
    for _ in range(n):
        s = next(data)
        v = next(data)
        if s <= m:                            # 体积超过容量上限，任何答案都用不到
            groups.setdefault(s, []).append(v)

    dp = [0] * (m + 1)                        # dp[j]：容量 <= j 时的最大价值
    for s in sorted(groups):
        use_group(dp, groups[s], s)

    sys.stdout.write(' '.join(map(str, dp[1:])) + '\n')


if __name__ == "__main__":
    solve()

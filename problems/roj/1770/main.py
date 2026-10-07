#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 01:25
# update_at: 2026-10-08 01:25

import sys
from bisect import bisect_right
from itertools import accumulate

NEG = -(1 << 60)  # 哨兵：罚分非负，这个值表示“该方向不存在”，小到绝不会被取到

type Row = list[int]  # 一行的格子（下标 0 是占位，1 起与题面列号对应）


def row_next(a_row: Row, cost: Row) -> Row:
    """算出本行每列的 f[j]：Alice 站在第 j 列（该格已付）后还需付的最小罚分。

    本行的博弈只由 cost[c]（在 (i,c) 下楼的落格数字加上后续最优罚分）决定：
    Bob 会在本行下方留一段门区间 [l, r] 且必须含 j，Alice 要么直接下楼，
    要么被两侧的门逼着把区间扫一遍再折返。Bob 取让她最亏的那段区间。
    """
    m = len(a_row) - 1
    pre = list(accumulate(a_row))  # pre[k] = a[1] + ... + a[k]
    # dk[c] = cost[c] - pre[c-1]：单门向左扫、以及“折返判定”都用到它
    dk = [NEG] + [cost[c] - pre[c - 1] for c in range(1, m + 1)]
    # sv[c] = pre[c] + cost[c]：从 c 下楼的总代价，同时也是门列 c 的“门槛值”
    sv = [NEG] + [pre[c] + cost[c] for c in range(1, m + 1)]
    # bv[c] = pre[c] + pre[c-1]：向左折返时越过 c 的横穿量
    bv = [NEG] + [pre[c] + pre[c - 1] for c in range(1, m + 1)]

    pk = list(accumulate(dk, max))  # pk[l] = max(dk[1..l])，dk[0]=NEG 不干扰
    sk = [NEG] * (m + 2)            # sk[r] = max(sv[r..m])，向右扫的候选取自右侧
    for r in range(m, 0, -1):
        sk[r] = max(sk[r + 1], sv[r])

    f: Row = [0] * (m + 1)
    for j in range(1, m + 1):
        best = cost[j]  # 门就开在 j：Alice 直接下楼
        if j > 1:       # 右门就是 j：只能向左扫到 l 再从 l 下楼
            best = max(best, pre[j - 1] + pk[j - 1])
        if j < m:       # 左门就是 j：只能向右扫到 r 再从 r 下楼
            best = max(best, -pre[j] + sk[j + 1])
        if 1 < j < m:   # 两门夹住 j：Alice 先探一侧，Bob 立刻封掉那一侧
            right = sorted(range(j + 1, m + 1), key=dk.__getitem__)  # 右侧门按 dk 升序
            keys = [dk[c] for c in right]
            head = list(accumulate([sv[c] for c in right], max))            # 前缀最大 sv
            tail = list(accumulate([bv[c] for c in right][::-1], max))[::-1]  # 后缀最大 bv
            theta = pre[j] + pre[j - 1]  # 折返分界：dk[r] <= sv[l] - theta 时走 v1 更省
            for l in range(1, j):
                cut = bisect_right(keys, sv[l] - theta)  # <= 分界线的门列个数
                if cut:                                  # v1：向左扫到底再折返到右门下楼
                    best = max(best, pre[j - 1] - pre[l - 1] - pre[l] + head[cut - 1])
                if cut < len(keys):                      # v2：向右扫到底再折返到左门下楼
                    best = max(best, dk[l] - pre[j] + tail[cut])
        f[j] = best
    return f


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    T = next(data)

    for _ in range(T):
        n, m = next(data), next(data)
        a: list[Row] = [[0] * (m + 1)]  # a[i][j]：第 i 行第 j 列的格子数字
        for _ in range(n):
            a.append([0] + [next(data) for _ in range(m)])

        if n == 1:  # Alice 一开始就在第 n 行，游戏立刻结束
            out.append(str(min(a[1][1:])))
            continue

        f: Row = [0] * (m + 1)  # 第 n 行已到终点，不用再往下走
        for i in range(n - 1, 0, -1):  # 自下而上倒推：无后效性，Alice 从 (i,j) 出发的结果固定
            cost = [0] + [a[i + 1][c] + f[c] for c in range(1, m + 1)]
            f = row_next(a[i], cost)
        out.append(str(min(a[1][j] + f[j] for j in range(1, m + 1))))

    print("\n".join(out))


if __name__ == "__main__":
    solve()

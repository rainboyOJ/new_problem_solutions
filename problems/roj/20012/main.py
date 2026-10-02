#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 19:55
# update_at: 2026-10-02 20:05

import sys

INF = 10**15  # "还够不着"的不可达哨兵，远大于任何合法生气总量


def min_anger(pos: list[int], anger: list[int], s: int) -> int:
    """区间 DP：客户按坐标升序、起点为下标 s，返回送完全部客户的最小生气总量。"""
    n = len(pos)

    # 前缀和：S[r+1]-S[l] = 区间 [l,r] 已送达客户的生气值之和
    S = [0]
    for a in anger:
        S.append(S[-1] + a)
    total = S[n]

    # f[l][r][0/1]：已送达连续区间 [l,r]、人停在左端 l(0) / 右端 r(1)，
    # 此时已发生的生气总量最小值。未送达客户在这段时间里一直按 t*A 累加。
    f = [[[INF, INF] for _ in range(n)] for _ in range(n)]
    f[s][s][0] = f[s][s][1] = 0

    for length in range(2, n + 1):
        for l in range(n - length + 1):
            r = l + length - 1
            # 走路期间仍在生气的是"区间外 + 正要收进来的那端"：
            # 由 [l+1,r] 走向 l：剩下 {0..l} 与 {r+1..n-1}
            wait_from_right = total - (S[r + 1] - S[l + 1])
            # 由 [l,r-1] 走向 r：剩下 {0..l-1} 与 {r..n-1}
            wait_from_left = total - (S[r] - S[l])

            f[l][r][0] = min(
                f[l + 1][r][0] + (pos[l + 1] - pos[l]) * wait_from_right,  # 左邻直走
                f[l + 1][r][1] + (pos[r] - pos[l]) * wait_from_right,       # 从右端折返
            )
            f[l][r][1] = min(
                f[l][r - 1][0] + (pos[r] - pos[l]) * wait_from_left,        # 从左端横穿
                f[l][r - 1][1] + (pos[r] - pos[r - 1]) * wait_from_left,    # 右邻直走
            )

    return min(f[0][n - 1])


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, c = next(data), next(data)
    raw = [(next(data), next(data)) for _ in range(n)]  # (位置 p, 生气值 A)

    order = sorted(range(n), key=raw.__getitem__)  # 按位置升序，区间 DP 依赖有序
    s = order.index(c - 1)                         # 起点客户排序后落在哪个下标
    pos = [raw[i][0] for i in order]
    anger = [raw[i][1] for i in order]

    print(min_anger(pos, anger, s))


if __name__ == "__main__":
    solve()

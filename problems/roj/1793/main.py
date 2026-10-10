#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 03:30
# update_at: 2026-10-08 03:30

import sys
from collections import deque

HULL_NEED = 2  # 下凸壳至少留几个点才能判断中间点冗余

type IndexQueue = deque[int]  # 决策点下标队列：方法① 的凸壳与方法② 的滑动窗口各用一个


def delete_costs(n: int, a: int, b: int, c: int, d: int, lmin: int, rmax: int,
                 s: bytes, dif: list[int]) -> list[int]:
    """依次算出删去每个前缀 [1,i] 的最少用时：返回长度 n 的答案表 dp[1..n]。

    方法①（代价 a*x^2+b）用斜率优化维护下凸壳；方法②（代价 c*x+d）的合法分割点构成
    随 i 单调右移的连续区间，用双指针维护区间端点、单调队列取区间内最小值。
    """
    pre = [0] * (n + 1)                                  # pre[i] = 前缀 [1,i] 的删除难度之和
    for i in range(1, n + 1):
        pre[i] = pre[i - 1] + dif[i - 1]                 # dif >= 0，故 pre 单调不减

    dp = [0] * (n + 1)                                   # dp[i] = 删去前缀 [1,i] 的最少用时
    occ: list[list[int]] = [[] for _ in range(26)]       # occ[ch] = 字符 ch 出现位置的升序表
    hull: IndexQueue = deque()                           # 下凸壳上的决策点下标
    window: IndexQueue = deque()                         # 合法区间内 h(j) 递增的决策点下标

    def yval(j: int) -> int:
        """方法① 凸壳上决策点 j 的纵坐标 dp[j] + a*pre[j]^2。"""
        return dp[j] + a * pre[j] * pre[j]

    def hvalue(j: int) -> int:
        """方法② 中与右端点无关的贡献 dp[j] - c*pre[j]。"""
        return dp[j] - c * pre[j]

    def hull_push(j: int) -> None:
        """把决策点 j 压入方法① 的下凸壳（横坐标重合时只留纵坐标更小者）。"""
        xj = pre[j]
        if hull and pre[hull[-1]] == xj:                 # dif 含 0 时横坐标会重合，凸壳不能带重复 x
            if yval(hull[-1]) <= yval(j):
                return
            hull.pop()
        while len(hull) >= HULL_NEED:
            p, q = hull[-2], hull[-1]
            # 下凸壳约定：slope(p,q) >= slope(q,j) 说明 q 在弦上方，应丢弃。
            # 交叉相乘代替除法，避免 dif=0 时除零，也避免浮点误差。
            q_redundant = (yval(q) - yval(p)) * (xj - pre[q]) >= (yval(j) - yval(q)) * (pre[q] - pre[p])
            if not q_redundant:
                break
            hull.pop()
        hull.append(j)

    def hull_best(k: int) -> int:
        """在查询斜率 k = 2a*pre[i] 下取最优决策点；k 单调不减，队头只往前移。"""
        while len(hull) >= HULL_NEED:
            j0, j1 = hull[0], hull[1]
            # 队头不如第二个点时就弹掉队头（k 递增，被弹掉的不会再变好）
            front_worse = yval(j0) - k * pre[j0] >= yval(j1) - k * pre[j1]
            if not front_worse:
                break
            hull.popleft()
        return hull[0]

    sL = sR = 0      # 方法② 的合法决策区间固定是 [sR, sL-1]，两个端点都随 i 单调不减
    pushed = -1      # window 中已经推入的最大下标
    ans: list[int] = []

    for i in range(1, n + 1):
        ch = s[i - 1] - 97                               # 当前字符
        occ[ch].append(i)
        cnt = len(occ[ch])
        # 第 (cnt-lmin+1) 次出现的位置：左端点取它时窗口内 ch 恰有 lmin 个 => maxfreq >= lmin
        if cnt >= lmin:
            sL = max(sL, occ[ch][cnt - lmin])
        # 第 (cnt-rmax) 次出现的位置：左端点越过它后 ch 就超过 rmax 个 => maxfreq <= rmax
        if cnt > rmax:
            sR = max(sR, occ[ch][cnt - rmax - 1])

        while pushed < sL - 1:                           # 右端点单调不减，逐个把新决策点推进去
            pushed += 1
            hv = hvalue(pushed)
            while window and hvalue(window[-1]) >= hv:
                window.pop()
            window.append(pushed)
        while window and window[0] < sR:                 # 左端点单调不减，弹出过期决策点
            window.popleft()                             # lmin > rmax 时区间为空，队列被清空

        hull_push(i - 1)
        j1 = hull_best(2 * a * pre[i])                   # 方法①：凸壳上的最优分割点
        best = dp[j1] + a * (pre[i] - pre[j1]) ** 2 + b

        if window:                                       # 方法②：区间非空才可用
            j2 = window[0]
            cand = dp[j2] - c * pre[j2] + c * pre[i] + d
            if cand < best:
                best = cand

        dp[i] = best
        ans.append(best)
    return ans


def solve() -> None:
    # 输入是严格的三行结构：第一行 7 个整数、第二行字符串、第三行 n 个整数，按行读最直接。
    n, a, b, c, d, lmin, rmax = map(int, sys.stdin.buffer.readline().split())
    s = sys.stdin.buffer.readline().strip()               # 字符串行，取下标得 ASCII 码
    dif = list(map(int, sys.stdin.buffer.read().split()))
    print("\n".join(map(str, delete_costs(n, a, b, c, d, lmin, rmax, s, dif))))


if __name__ == "__main__":
    solve()

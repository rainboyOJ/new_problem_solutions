#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 21:53
# update_at: 2026-09-30 22:05

import sys
from array import array
from collections import deque
from itertools import accumulate


def max_power(a: int, b: int, c: int, pre: array) -> int:
    """前 n 个士兵编队的最大修正战斗力和（斜率优化，O(n)）。

    设 f[i] 为前 i 人的答案，最后一队是 (j, i]，则
        f[i] = max_j { f[j] + g(S[i] - S[j]) },  g(u) = a·u² + b·u + c。
    展开 g，把只与 j 有关的项收成 Y[j] = f[j] + a·S[j]² - b·S[j]：
        f[i] = max_j { Y[j] + u[i]·S[j] } + a·S[i]² + b·S[i] + c,  u[i] = -2a·S[i]。
    每个候选切点 j 于是是一条直线 l_j(u) = S[j]·u + Y[j]（斜率 S[j]、截距 Y[j]），
    转移变成"在直线族的上包络上查询 u = u[i] 处的最大值"。
    a < 0 ⇒ 查询点 u[i] 随 i 递增；x[i] ≥ 1 ⇒ 直线斜率 S[j] 随 j 递增。
    新直线只接在包络右端、查询点又只向右走，两条单调 ⇒ 单调队列：
    队头弹出已被超过的直线，队尾弹出被新直线压得不再可能是最优的直线；
    每条直线进出队各一次，摊还 O(1)。
    """
    n = len(pre) - 1
    f = array('q', [0]) * (n + 1)  # f[i]：前 i 人的最优值，f[0] = 0
    y = array('q', [0]) * (n + 1)  # 直线截距 Y[i] = f[i] + a·S[i]² - b·S[i]
    hull = deque([0])              # 上包络上的直线编号，斜率 S[j] 随入队递增

    for i in range(1, n + 1):
        s = pre[i]
        k = 2 * a * s  # k = -u[i]：两边同乘 -1，把 max l_j(u) 写成 max(Y[j] - k·S[j])
        while len(hull) >= 2:
            head, second = hull[0], hull[1]
            if y[head] - k * pre[head] <= y[second] - k * pre[second]:
                hull.popleft()  # 次队头已不比队头差，u[i] 只会更大，队头此后再也用不到
            else:
                break
        j = hull[0]  # 最优直线：最后一段的左边界
        f[i] = f[j] + a * (s - pre[j]) ** 2 + b * (s - pre[j]) + c
        y[i] = f[i] + a * s * s - b * s
        while len(hull) >= 2:
            p, q = hull[-2], hull[-1]
            # 判据即交点位置 x[p][q] ≥ x[q][i]：直线 q 的领先区间为空，可丢；交叉相乘免去除法
            slope_pq = (y[q] - y[p]) * (s - pre[q])
            slope_qi = (y[i] - y[q]) * (pre[q] - pre[p])
            if slope_pq <= slope_qi:
                hull.pop()  # q 被直线 p 与 i 夹在包络之下，不再出现在上包络上
            else:
                break
        hull.append(i)
    return f[n]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)  # 士兵数
    a, b, c = next(data), next(data), next(data)  # 经验公式系数
    pre = array('q', accumulate((next(data) for _ in range(n)), initial=0))  # S[0..n]
    print(max_power(a, b, c, pre))


if __name__ == "__main__":
    solve()

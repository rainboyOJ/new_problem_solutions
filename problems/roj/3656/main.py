#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 13:42
# update_at: 2026-10-02 13:42

import sys
from bisect import bisect_right
from collections import deque


def min_wait(t: list[int], m: int) -> int:
    """所有同学等车时间之和的最小值：以发车时刻为状态做 DP，凸壳优化"非被迫"转移。"""
    n = len(t)
    pre = [0] * (n + 1)                      # 到达时刻前缀和，供 O(1) 算一段的等待总量
    for i, v in enumerate(t, 1):
        pre[i] = pre[i - 1] + v

    # 发车时刻状态闭包：每班要么卡在某位同学的到达时刻发（非被迫），
    # 要么上一班返程即刻发、时刻 = 上一班 + m，且 (dep, dep+m] 里必须还有同学（被迫）。
    arrival = sorted(set(t))
    states = set(arrival)
    stack = arrival[:]
    while stack:
        dep = stack.pop()
        has_new = bisect_right(t, dep + m) > bisect_right(t, dep)   # (dep, dep+m] 里还有同学
        if has_new and dep + m not in states:
            states.add(dep + m)
            stack.append(dep + m)
    deps = sorted(states)                    # 按发车时刻递增处理，任一前驱必先于后继定值

    # 凸壳：维护一簇直线 y = a*x + b 的逐点最小值。前驱 D 的转移贡献改写成
    #   cnt(dep)*dep - pre[cnt(dep)] + (dp[D] + pre[cnt(D)] - cnt(D)*dep)
    # 括号里是关于 dep 的一条直线（斜率 -cnt(D)），于是"取最优前驱"就是凸壳查询。
    hull: deque[list[int]] = deque([[0, 0]])  # 虚拟前驱：一个同学都还没接，直线 y = 0
    pending: deque[tuple[int, int, int]] = deque()  # 已入壳、等前驱+m<=dep 才生效的直线 (dep, a, b)

    def hull_add(a: int, b: int) -> None:
        """把 y = a*x + b 并入凸壳：斜率不增地加入，弹掉永远取不到最小值的尾部直线。"""
        while len(hull) >= 2:
            a1, b1 = hull[-2]
            a2, b2 = hull[-1]
            if a == a2:                      # 同斜率只留截距更小的那条
                if b >= b2:
                    return
                hull.pop()
                continue
            # 新线与倒数第二条的交点不晚于旧交点时，末尾那条被夹在中间、永远轮不到
            if (b2 - b1) * (a2 - a) >= (b - b2) * (a1 - a2):
                hull.pop()
            else:
                break
        hull.append([a, b])

    def hull_min(x: int) -> int:
        """查询已生效直线在 x 处的最小值；查询 x 递增，队头被超过就弹掉。"""
        while len(hull) >= 2 and hull[0][0] * x + hull[0][1] >= hull[1][0] * x + hull[1][1]:
            hull.popleft()
        return hull[0][0] * x + hull[0][1]

    dp: dict[int, int] = {}
    finals: list[int] = []

    for dep in deps:
        cnt = bisect_right(t, dep)           # 到 dep 为止送完了前 cnt 位同学

        # 直线前驱 D 只在"返程赶得上"（D + m <= dep）时才接得了这一班
        while pending and pending[0][0] <= dep - m:
            _, a, b = pending.popleft()
            hull_add(a, b)

        # 非被迫转移：前驱 D 送完前 cnt(D) 人，本班 dep 出发带走 cnt(D)+1..cnt 人
        best = cnt * dep - pre[cnt] + hull_min(dep)

        # 被迫转移：前驱 D = dep - m 返程即刻发车，把 (D, dep] 里等车的同学一并带走
        prev, prev_cnt = dep - m, bisect_right(t, dep - m)
        if prev_cnt < cnt and prev in dp:
            forced = dp[prev] + (cnt - prev_cnt) * dep - (pre[cnt] - pre[prev_cnt])
            if forced < best:
                best = forced

        dp[dep] = best
        if cnt < n:                          # 还有同学没上车：登记本班直线，供 dep+m 起查询
            pending.append((dep, -cnt, best + pre[cnt]))
        else:
            finals.append(best)              # 全员送达：记一次候选答案

    return min(finals)


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    m = next(data)
    t = sorted(next(data) for _ in range(n))  # 分组必然是排序后的连续段，先排序
    print(min_wait(t, m))


if __name__ == "__main__":
    solve()

#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 21:17
# update_at: 2026-09-30 21:26

import sys
from collections import deque

INF = 10**9  # 不可达哨兵（真实答案至多 k，远小于它）


def relax(old: list[int], dp: list[int], w: int, c: int, k: int) -> None:
    """加入面值 w、数量不超过 c 的硬币：对每个同余类做单调队列优化的有界松弛。"""
    if w > k:  # 面值超过目标的硬币一枚也用不上
        return
    # 位置 r+m*w 上（m 表示"该类里第几个位置"）：
    # dp[r+m*w] = min_{t<=c} old[r+(m-t)*w] + t = m + min_{u in [m-c, m]} (old[r+u*w] - u)
    # 窗口 [m-c, m] 只向右滑动，用单调队列维护键 old[r+u*w] - u 的最小值。
    for r in range(w):  # 同余类内部位置等距 w，类间互不干扰
        dq: deque[int] = deque()
        m = 0
        while (pos := r + m * w) <= k:
            key = old[pos] - m  # 候选下标 u=m 的键
            while dq and old[r + dq[-1] * w] - dq[-1] >= key:
                dq.pop()  # 队尾更差的下标不可能再成为最小值
            dq.append(m)
            while m - dq[0] > c:  # 队首滑出窗口 [m-c, m]
                dq.popleft()
            dp[pos] = m + old[r + dq[0] * w] - dq[0]
            m += 1


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    values = [next(data) for _ in range(n)]  # 面值 b_i（严格递增）
    counts = [next(data) for _ in range(n)]  # 各面值数量 c_i
    k = next(data)  # 要凑的目标面值

    dp = [INF] * (k + 1)
    dp[0] = 0  # 0 面值付 0 个硬币
    for w, c in zip(values, counts):
        relax(dp[:], dp, w, c, k)  # 松弛前先取快照，同余类内要读"上一轮"的值

    print(dp[k])


if __name__ == "__main__":
    solve()

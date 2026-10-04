#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 09:05
# update_at: 2026-10-02 09:05

import sys
from itertools import product


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)
    a = [next(data) for _ in range(n)]  # a[i]：第 i+1 格的分数（0 起下标）

    cnt = [0] * 5  # cnt[k]：数字为 k 的卡片张数，cnt[0] 不用
    for _ in range(m):
        cnt[next(data)] += 1

    # dp[(c1,c2,c3,c4)]：四类卡片分别用了 c1..c4 张时的最大得分。
    # 用牌总数唯一决定当前位置（第 1 格 + 已走步数），所以状态里不必再存位置。
    # 题目保证用光 M 张牌恰好到终点，答案就是四类牌全部用完时的状态值。
    dp = {(0, 0, 0, 0): a[0]}  # 起点：还没出牌，已自动获得第 1 格分数
    for c1, c2, c3, c4 in product(range(cnt[1] + 1), range(cnt[2] + 1),
                                  range(cnt[3] + 1), range(cnt[4] + 1)):
        state = (c1, c2, c3, c4)
        cur = dp.get(state)
        if cur is None:
            continue  # 这个用牌组合从起点走不到
        pos = c1 + 2 * c2 + 3 * c3 + 4 * c4  # 已走步数 = 当前格子的 0 起下标
        for k in range(1, 5):
            nxt_pos = pos + k
            if state[k - 1] == cnt[k] or nxt_pos >= n:
                continue  # 数字 k 的牌已用完，或这一步会跳出棋盘
            nxt = state[:k - 1] + (state[k - 1] + 1,) + state[k:]
            gain = cur + a[nxt_pos]
            if gain > dp.get(nxt, -1):
                dp[nxt] = gain

    print(dp[(cnt[1], cnt[2], cnt[3], cnt[4])])


if __name__ == "__main__":
    solve()

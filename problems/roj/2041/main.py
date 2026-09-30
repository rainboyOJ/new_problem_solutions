#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 04:45
# update_at: 2026-10-01 04:45

import sys


def best_total(limit: int, types: list[tuple[int, int]]) -> int:
    """在限时 limit 内，从这些 (耗时, 得分) 种类里任选题目，最多能拿多少分。"""
    # dp[t] = 限时 t 内的最大得分。容量维正序遍历，dp[t - w] 已含本轮结果，
    # 同一种类因此能被反复选取；若每种至多选一题，这里必须改成倒序。
    dp = [0] * (limit + 1)
    for minutes, points in types:  # types 已按耗时升序
        if minutes > limit:
            break  # 耗时升序，后面的种类耗时更长，连一题都放不下
        if dp[minutes] >= points:
            # 前面（耗时不超过 minutes）的种类已经能用不超过 minutes 的时间拿到不少于 points
            # 的分：把最优解里每道这种题目都换成那一份，耗时不增、得分不降，所以这种类
            # 不会出现在任何最优解里，直接剪掉；同耗时的种类也因此只留下得分最高的那个。
            continue
        for t in range(minutes, limit + 1):
            candidate = dp[t - minutes] + points  # 至少再选一道这种题目
            if candidate > dp[t]:
                dp[t] = candidate
    return dp[limit]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    limit, count = next(data), next(data)  # 竞赛限时 M 与题目"种类"数 N
    tokens = [next(data) for _ in range(2 * count)]  # 每个种类两个数：得分在前、耗时在后
    # 重排成 (耗时, 得分) 并按耗时升序；耗时相同时得分高的排前面，低分的会被剪掉。
    types = sorted(zip(tokens[1::2], tokens[0::2]), key=lambda kind: (kind[0], -kind[1]))

    print(best_total(limit, types))


if __name__ == "__main__":
    solve()

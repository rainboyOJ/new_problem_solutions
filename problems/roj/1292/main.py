#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 03:40
# update_at: 2026-09-30 03:43

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    balls = next(data)  # 题面第一维：小智拥有的精灵球数量，是花费上限
    power = next(data)  # 题面第二维：皮卡丘的初始体力
    kinds = next(data)  # 野生小精灵的种类数

    # dp[ball_limit][hp_limit]：精灵球不超过 ball_limit、体力消耗不超过 hp_limit 时的最大收服数。
    # 体力维只开到 power-1：题面规定体力降到 0 或以下就必须结束狩猎，那只小精灵也收服不了。
    hp_cap = power - 1
    dp = [[0] * (hp_cap + 1) for _ in range(balls + 1)]

    for _ in range(kinds):
        cost_ball = next(data)  # 收服这只小精灵要用的精灵球
        cost_hp = next(data)    # 收服过程中皮卡丘要承受的伤害
        if cost_ball > balls or cost_hp > hp_cap:
            continue  # 这一只无论如何都收服不了，直接跳过，省掉整轮双维扫描

        # 两个维度都要倒序：它们共用同一只小精灵，正序会让这只被重复收服。
        for ball_limit in range(balls, cost_ball - 1, -1):
            row = dp[ball_limit]
            src = dp[ball_limit - cost_ball]
            for hp_limit in range(hp_cap, cost_hp - 1, -1):
                better = src[hp_limit - cost_hp] + 1  # 收服这一只：先在低一档的花费里再加 1
                if better > row[hp_limit]:
                    row[hp_limit] = better

    # 主目标收服数量最多，次目标皮卡丘受伤最少；球数只是花费上限，不参与比较。
    best = dp[balls][hp_cap]
    min_hp = dp[balls].index(best)  # 这一行随体力上限单调不减，首个达到 best 的下标就是最少消耗
    print(best, power - min_hp)


if __name__ == "__main__":
    solve()

#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 05:52
# update_at: 2026-10-02 05:52

import sys

MONTHLY_ALLOWANCE = 300  # 妈妈每月月初给的零花钱
DEPOSIT_LINE = 100       # 月末结余达到这个数才值得把整百存出去
BONUS_RATE = 5           # 年末利息 20% = 1/5，本金是 100 的倍数，整除即可


def solve() -> None:
    budgets = list(map(int, sys.stdin.buffer.read().split()))  # 1~12 月预算
    hand = 0    # 津津手中现金
    saved = 0   # 存在妈妈那里的本金（年末前取不出）

    for month, need in enumerate(budgets, 1):
        hand += MONTHLY_ALLOWANCE             # 月初先拿到零花钱
        if hand < need:                        # 手里的钱不够这个月的原定预算
            print(-month)                      # 输出第一个出问题的月份
            return
        hand -= need                           # 按预算花完，得到月末结余
        if hand >= DEPOSIT_LINE:               # 结余 ≥100，把整百存出去
            deposit = hand // 100 * 100
            hand -= deposit
            saved += deposit

    # 年末：妈妈还回本金 + 20% 利息，加上自己手里的现金
    print(hand + saved + saved // BONUS_RATE)


if __name__ == "__main__":
    solve()

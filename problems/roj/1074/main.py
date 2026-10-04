#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 17:30
# update_at: 2026-09-29 17:30

import sys


def solve() -> None:
    budgets = [int(s) for s in sys.stdin.read().split()]  # 1~12 月的预算
    hand = 0   # 自己手中的余钱（百元以内）
    saved = 0  # 存在妈妈那里的钱（全是整百）
    for month, budget in enumerate(budgets, 1):
        hand += 300 - budget              # 月初领 300，月末恰好花掉预算
        if hand < 0:                      # 这个月入不敷出，计划破产
            print(-month)
            return
        saved += hand // 100 * 100        # 预计月末还有 ≥100，就存整百
        hand %= 100
    print(hand + saved * 6 // 5)          # 年末取回存款并加 20%


if __name__ == "__main__":
    solve()

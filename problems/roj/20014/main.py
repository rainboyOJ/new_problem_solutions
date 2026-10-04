#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 20:11
# update_at: 2026-10-02 20:11

import sys
from functools import cache

POS: list[int] = []    # 客户位置，升序（位置可负、互不为 0）
EARN: list[int] = []   # EARN[i] 是位置 POS[i] 处外卖的价格 e


@cache
def best(l: int, r: int, side: int, passed: int) -> int:
    """还没决定去留的客户恰为区间 [l, r]，无人机停在 side 端，
    区间外已走过 passed 个"未决定"客户时的最大净赚。"""
    if l == r:  # 最后一个未决定客户：要么现在送，要么永远放弃
        x = POS[l]
        return max(EARN[l] - abs(x) * (passed + 1), -abs(x) * passed)
    if side == 0:  # 在左端，决定最左客户 l 的去留
        x, nxt, far = POS[l], POS[l + 1], POS[r]
        return max(
            EARN[l] + best(l + 1, r, 0, passed + 1) - (nxt - x) * (passed + 1),  # 送，继续向左
            EARN[l] + best(l + 1, r, 1, passed + 1) - (far - x) * (passed + 1),  # 送，掉头向右
            best(l + 1, r, 0, passed) - (nxt - x) * passed,                      # 放弃，继续向左
            best(l + 1, r, 1, passed) - (far - x) * passed,                      # 放弃，掉头向右
        )
    x, prv, far = POS[r], POS[r - 1], POS[l]  # 在右端，决定最右客户 r 的去留
    return max(
        EARN[r] + best(l, r - 1, 1, passed + 1) - (x - prv) * (passed + 1),  # 送，继续向右
        EARN[r] + best(l, r - 1, 0, passed + 1) - (x - far) * (passed + 1),  # 送，掉头向左
        best(l, r - 1, 1, passed) - (x - prv) * passed,                      # 放弃，继续向右
        best(l, r - 1, 0, passed) - (x - far) * passed,                      # 放弃，掉头向左
    )


def solve() -> None:
    global POS, EARN
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    pos = [next(data) for _ in range(n)]   # 客户位置（可负、可乱序）
    earn = [next(data) for _ in range(n)]  # 对应客户的外卖价格
    pairs = sorted(zip(pos, earn))         # 按位置排序，区间 DP 才能从两端逐个决定
    POS = [x for x, _ in pairs]
    EARN = [v for _, v in pairs]
    print(max(best(0, n - 1, 0, 0), best(0, n - 1, 1, 0)))


if __name__ == "__main__":
    solve()

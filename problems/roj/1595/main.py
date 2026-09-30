#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 20:38
# update_at: 2026-09-30 20:38

import sys


def is_row_valid(mask: int) -> bool:
    """判断单行内炮兵间距是否均大于 2：左右两格内不能有其他炮兵。"""
    return not (mask & (mask << 1)) and not (mask & (mask << 2))


def solve() -> None:
    tokens = sys.stdin.read().split()
    if not tokens:
        return
    n, m = int(tokens[0]), int(tokens[1])
    hill_masks: list[int] = [
        sum((1 if ch == "H" else 0) << (m - 1 - col) for col, ch in enumerate(row))
        for row in tokens[2 : 2 + n]
    ]

    # 单行无冲突的基准状态集合（M <= 10 时最多仅 60 种）
    valid_states: list[int] = [mask for mask in range(1 << m) if is_row_valid(mask)]
    cannon_counts: dict[int, int] = {mask: mask.bit_count() for mask in valid_states}

    # dp[(s_prev2, s_prev1)]: 上上一行状态为 s_prev2、上一行状态为 s_prev1 时的最大炮兵数
    dp: dict[tuple[int, int], int] = {(0, 0): 0}

    for row_hills in hill_masks:
        nxt: dict[tuple[int, int], int] = {}
        # 当前行候选：不能与山地重合
        candidates = [s for s in valid_states if not (s & row_hills)]
        for (s0, s1), total in dp.items():
            for s2 in candidates:
                if not (s2 & s1) and not (s2 & s0):
                    pair = (s1, s2)
                    new_val = total + cannon_counts[s2]
                    if new_val > nxt.get(pair, -1):
                        nxt[pair] = new_val
        dp = nxt

    print(max(dp.values(), default=0))


if __name__ == "__main__":
    solve()

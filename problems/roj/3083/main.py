#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 15:38
# update_at: 2026-10-01 15:38

import sys

SIDE = 4                    # 村子是 4 x 4 的网格，区域按行优先编号 0..15
WINDOW = 2                  # 云是 2 x 2 的
SPOTS = SIDE - WINDOW + 1   # 云的左上角只能落在 3 x 3 个位置上
CENTER = SPOTS + 1          # 云在正中盖住中部 6-7-10-11，第一天它固定在这里
STREAK = 6                  # 同一块地连续 6 天不下雨还合法，第 7 天必须下
LAND_MASK = (1 << SIDE * SIDE) - 1

# 每天可选的位移：东南西北各 1 或 2 格，再加上原地不动，共 13 种。
MOVES = tuple(
    (dr, dc)
    for dr in range(-2, 3)
    for dc in range(-2, 3)
    if (dr == 0 or dc == 0) and abs(dr) + abs(dc) <= 2
)

# 以云位置 code = row * SPOTS + col 为下标的两张预处理表。
# COVER[code]：这块云淋到的 16 个区域，按行优先拍平成一个 16 位整数。
# NEXT[code]：这块云明天所有可选的左上角位置。
COVER = tuple(
    sum(
        1 << (r * SIDE + c)
        for r in range(row, row + WINDOW)
        for c in range(col, col + WINDOW)
    )
    for row in range(SPOTS)
    for col in range(SPOTS)
)  # 9 种云位置
NEXT = tuple(
    tuple(
        (row + dr) * SPOTS + col + dc
        for dr, dc in MOVES
        if 0 <= row + dr < SPOTS and 0 <= col + dc < SPOTS
    )
    for row in range(SPOTS)
    for col in range(SPOTS)
)  # 9 种云位置


def advance(
    states: set[tuple[int, tuple[int, ...]]], plan: int, enforce: bool
) -> set[tuple[int, tuple[int, ...]]]:
    """推进一步，返回下一天所有仍合法的 (云位置, 雨迹)。

    雨迹是 STREAK - 1 个 16 位掩码，第 k 项记录"最近 k+1 天里下过雨的区域并集"
    （最近一天就是当前云盖住的那片，随云的位置即可推出，不必另存）。
    plan 第 i 位为 1 表示区域 i 有赶集过节，当天不能下雨；enforce 为假表示
    历史还没攒满 6 天，这时不可能有人旱满 7 天，可以跳过判罚。
    """
    return {
        # 把今天的云并进每一项：旧的第 0 项是昨天的云，new_hist[-1] 就是"最近 6 天雨迹"
        (nxt, tuple(cover | rain for rain in (COVER[code],) + rain_hist[: STREAK - 2]))
        for code, rain_hist in states
        for nxt in NEXT[code]
        for cover in (COVER[nxt],)
        if not cover & plan                                     # 赶集过节的区域不能被淋到
        # 最近 6 天一滴雨没沾的区域今天必须轮到它下，否则就凑满 7 天旱
        and not (enforce and (LAND_MASK ^ rain_hist[-1]) & (LAND_MASK ^ cover))
    }


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []

    while True:
        days = next(data)
        if days == 0:                                           # N = 0 表示输入结束
            break
        # 每一天的 16 个 0/1 压成一个掩码，第 i 位为 1 表示区域 i 有赶集过节。
        plans = [
            sum(next(data) << i for i in range(SIDE * SIDE))
            for _ in range(days)
        ]

        # 第一天云固定在正中间、不允许移动，于是它的位置是唯一确定的。
        states: set[tuple[int, tuple[int, ...]]] = set()
        if not plans[0] & COVER[CENTER]:                        # 中部有赶集过节就无解
            states.add((CENTER, (COVER[CENTER],) * (STREAK - 1)))

        for day, plan in enumerate(plans[1:], 1):
            states = advance(states, plan, day >= STREAK)
            if not states:                                      # 已经无解，剩下的日程不必再看
                break

        out.append("1" if states else "0")

    print("\n".join(out))


if __name__ == "__main__":
    solve()

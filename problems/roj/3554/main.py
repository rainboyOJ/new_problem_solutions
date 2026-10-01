#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 07:11
# update_at: 2026-10-02 07:11

import sys


def rests(magic: int, flashes: int) -> int:
    """凑足 flashes 次闪烁最少需要休息几秒（初始 magic 点，每次休息回 4 点）。"""
    deficit = 10 * flashes - magic
    return (deficit + 3) // 4 if deficit > 0 else 0


def farthest(magic: int, t: int) -> int:
    """t 秒内三种动作各做任意整数秒（每秒恰好一个动作）能走的最远距离。"""
    flash_max = min(t, (4 * t + magic) // 14)  # 一闪一休均速 60/3.5 > 17，闪越多越快
    best = 0
    for flashes in (flash_max, flash_max - 1):
        if flashes < 0:
            continue
        best = max(best, 60 * flashes + 17 * (t - flashes - rests(magic, flashes)))
    return best


def solve() -> None:
    magic, dist, time_limit = map(int, sys.stdin.buffer.read().split())  # 题面的 M, S, T

    # 逃离时刻 t 只取决于 farthest(magic, t)，每秒刷新一次即可
    escape_time = next((t for t in range(time_limit + 1) if farthest(magic, t) >= dist), -1)
    if escape_time >= 0:
        print(f"Yes\n{escape_time}")
    else:
        print(f"No\n{farthest(magic, time_limit)}")


if __name__ == "__main__":
    solve()

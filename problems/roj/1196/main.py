#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 23:04
# update_at: 2026-09-29 23:24

import sys


def solve() -> None:
    """走 n 步且不重复踩格的方案数：按当前端点的「本行是否横走过」分两类计数。"""
    n = int(sys.stdin.buffer.read())
    # 终点（最后一步的落点）总在最高的一行上，而这一行踩过的格子必是连续一段。
    # fresh：终点所在行只有它自己，向北/东/西都踩新格子（3 种走法）。
    # walked：终点所在行已有别的格子，终点是区间端点，只剩向北 + 唯一一侧的横走（2 种）。
    fresh, walked = 1, 0
    for _ in range(n):
        # 向北都只踏入全新的一行（两类都变 fresh）；横向走法数才是差别：
        # fresh 有 2 种、walked 只剩 1 种，都会让本行多踩一格（变 walked）。
        fresh, walked = fresh + walked, 2 * fresh + walked
    print(fresh + walked)


if __name__ == "__main__":
    solve()

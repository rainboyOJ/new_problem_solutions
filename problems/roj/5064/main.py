#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-09 01:40
# update_at: 2026-10-09 01:40

# 题面给出的两组观测：N1 头牛正好吃 T1 天，N2 头牛正好吃 T2 天
N1, T1, N2, T2 = 15, 20, 20, 10


def new_grass_per_day() -> int:
    """每天新生的草量可供几头牛吃 1 天。

    设初始草量 G、每天新生草量 g：G + T1*g = N1*T1，G + T2*g = N2*T2，
    两式相减消去 G 得 (T1 - T2)*g = N1*T1 - N2*T2，本题恰好整除。
    """
    return (N1 * T1 - N2 * T2) // (T1 - T2)


def solve() -> None:
    print(new_grass_per_day())


if __name__ == "__main__":
    solve()

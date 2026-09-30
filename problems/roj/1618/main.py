#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 22:18
# update_at: 2026-09-30 22:23

import sys

MOD = 100003  # 题面要求的模数


def solve() -> None:
    """总状态数减掉「相邻房间宗教都不同」的状态数，剩下的就是至少有一对相邻同教的状态数。"""
    m, n = map(int, sys.stdin.buffer.read().split())

    all_states = pow(m, n, MOD)  # 每个房间从 m 种宗教里任选
    safe_states = m * pow(m - 1, n - 1, MOD)  # 第 1 间任选，之后每间避开左邻的宗教

    print((all_states - safe_states) % MOD)


if __name__ == "__main__":
    solve()

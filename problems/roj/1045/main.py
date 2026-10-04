#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 16:10
# update_at: 2026-09-29 16:10

import sys

LUCKY_NEED = 10  # 兑换大奖所需的“幸运”瓶盖数
ENCOURAGE_NEED = 20  # 兑换大奖所需的“鼓励”瓶盖数


def solve() -> None:
    data = map(int, sys.stdin.buffer.read().split())
    lucky, encourage = next(data), next(data)  # “幸运”与“鼓励”的瓶盖数
    # 两条兑换路径满足任意一条即可兑奖
    can_reward = lucky >= LUCKY_NEED or encourage >= ENCOURAGE_NEED
    print(1 if can_reward else 0)


if __name__ == "__main__":
    solve()

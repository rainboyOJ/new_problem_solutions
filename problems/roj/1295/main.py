#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 03:39
# update_at: 2026-09-30 03:39

import sys
from itertools import islice


def min_leftover(capacity: int, volumes: list[int]) -> int:
    """箱子最少剩多少空间：位掩码第 s 位为 1 表示体积 s 能被若干物品恰好拼出。"""
    reachable = 1  # 一个物品都不选：体积 0 可达
    for w in volumes:
        reachable |= reachable << w  # 选/不选该物品 = 把已可达集合整体平移 w 后并入

    # 只关心不超过容量的位：与容量掩码相与后取最高位，就是最多能装下的体积
    filled = (reachable & ((1 << (capacity + 1)) - 1)).bit_length() - 1
    return capacity - filled


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    capacity = next(data)  # 箱子容量 V
    item_count = next(data)  # 物品数 n
    # 实测数据可能不足 n 个体积：读不到的位置等价于体积 0，截取即可
    volumes = list(islice(data, item_count))

    print(min_leftover(capacity, volumes))


if __name__ == "__main__":
    solve()

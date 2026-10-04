#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 09:45
# update_at: 2026-10-02 09:45

import sys
from collections.abc import Iterator
from itertools import accumulate

MOD = 20123  # 密钥的模数


def climb_floor(stairs: list[int], pre: list[int], start: int, x: int) -> int:
    """从 start 号房出发，返回逆时针数第 x 个有楼梯房间的编号。

    x 可能远大于本层楼梯数 total，先绕整圈消掉：第 x 个等价于第
    k = (x-1) % total + 1 个。再按前缀和把它定位到 [start, M-1] 段
    或回绕后的 [0, start) 段，两段各自一次下标计算即可。
    """
    total = len(stairs)
    k = (x - 1) % total + 1          # 去掉整圈后还差 k 个楼梯
    before = total - pre[start]      # 房间 [start, M-1] 上的楼梯数
    if before >= k:                  # 不用回绕：这是本段里第 k 个楼梯
        return stairs[pre[start] + k - 1]
    return stairs[k - before - 1]    # 回绕后只剩 k-before 个，落在前缀段里


def read_floors(rooms: Iterator[int], n: int, m: int) -> list[tuple[list[int], list[int], list[int]]]:
    """读入 n 层楼，每层返回 (楼梯房间列表, 楼梯前缀和, 指示牌数字列表)。"""
    floors = []
    for _ in range(n):
        signs = []
        stairs = []      # 楼梯房间编号，天然升序
        for j in range(m):
            up = next(rooms)  # 该房间是否有楼梯
            signs.append(next(rooms))
            if up:
                stairs.append(j)
        stair_set = set(stairs)
        # pre[j] = 房间 [0, j) 里的楼梯数，下标按房间号（长度 m+1）
        pre = [0, *accumulate(1 if j in stair_set else 0 for j in range(m))]
        floors.append((stairs, pre, signs))
    return floors


def solve() -> None:
    rooms = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(rooms), next(rooms)
    floors = read_floors(rooms, n, m)
    room = next(rooms)  # 底层入口房间编号

    key = 0
    for stairs, pre, signs in floors:
        key += signs[room]  # 密钥累加本层第一个进入房间的指示牌数字
        room = climb_floor(stairs, pre, room, signs[room])
    print(key % MOD)


if __name__ == "__main__":
    solve()

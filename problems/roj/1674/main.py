#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 01:38
# update_at: 2026-10-01 01:38

from collections import deque
from collections.abc import Iterator
import sys

MAX_CHANCE = 2  # 女生共 2 次机会，第二次数到 n 才出局


def survive(n: int, chances: list[int]) -> int:
    """按 chances 里的剩余机会逐个出局，返回最后留下的人（下标从 1 起）。

    每轮连续出局后，报数接力交到下一个未出局的人手上。
    """
    ring = deque(range(len(chances)))  # 存下标，人数最多 20，不用公式跳位
    counter = 0                        # 当前这一棒已经报到的数字
    while len(ring) > 1:
        index = ring.popleft()
        counter += 1
        if counter < n:
            ring.append(index)         # 没数到 n，回到队尾继续
            continue
        chances[index] -= 1            # 数到 n：用掉一次机会
        counter = 0                    # 下一个人从 1 重新报数
        if chances[index] > 0:
            ring.append(index)         # 还有机会，站在队尾等下一轮报数
    return ring[0] + 1


def read_people(tokens: Iterator[str]) -> list[int]:
    """读入 m 与性别序列，换算成每个人的剩余机会：女生 2 次，男生 1 次。"""
    m = int(next(tokens))
    return [MAX_CHANCE if next(tokens) == b'0' else 1 for _ in range(m)]


def solve() -> None:
    tokens = iter(sys.stdin.buffer.read().split())
    chances = read_people(tokens)
    n = int(next(tokens))
    print(survive(n, chances))


if __name__ == "__main__":
    solve()

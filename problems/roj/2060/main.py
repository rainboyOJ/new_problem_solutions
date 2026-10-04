#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 05:45
# update_at: 2026-10-01 05:45

import sys

NEG = -10**9  # 状态不存在时的哨兵：让 max 忽略不可达的转移


def place(
    cur: dict[tuple[int, int], int], length: int, T: int, M: int
) -> dict[tuple[int, int], int]:
    """把一首长度为 length 的歌接进所有状态：丢弃 / 塞进当前 CD / 另开一张 CD。"""
    nxt = dict(cur)  # 丢弃这首歌：状态原样保留
    for (discs, used), songs in cur.items():
        if discs >= 1 and used + length <= T:  # 当前 CD 剩余空位足够
            key = (discs, used + length)
            nxt[key] = max(nxt.get(key, NEG), songs + 1)
        if discs < M and length <= T:  # 单独占用一张新 CD
            key = (discs + 1, length)
            nxt[key] = max(nxt.get(key, NEG), songs + 1)
    return nxt


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, T, M = next(data), next(data), next(data)
    lengths = [next(data) for _ in range(n)]  # 歌曲按创作时间顺序给出

    # 状态 (已开的 CD 数, 最后一张 CD 已用分钟) -> 已选歌曲数；discs = 0 表示还没开过 CD
    state: dict[tuple[int, int], int] = {(0, 0): 0}
    for length in lengths:
        state = place(state, length, T, M)
    print(max(state.values()))


if __name__ == "__main__":
    solve()

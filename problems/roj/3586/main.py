#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47

import sys


def play_round(order: list[int], score: list[int], power: list[int]) -> list[int]:
    """打完一轮并返回新排名：胜者组、负者组各自仍有序，归并即可。"""
    winners: list[int] = []
    losers: list[int] = []
    for k in range(0, len(order), 2):
        a, b = order[k], order[k + 1]
        w, l = (a, b) if power[a] > power[b] else (b, a)
        score[w] += 1  # 胜者加一分
        winners.append(w)
        losers.append(l)

    merged: list[int] = []
    i = j = 0
    while i < len(winners) and j < len(losers):
        a, b = winners[i], losers[j]
        # a 排在 b 前 ⟺ 分数更高，或同分且编号更小
        ahead = score[a] > score[b] or (score[a] == score[b] and a < b)
        if ahead:
            merged.append(a)
            i += 1
        else:
            merged.append(b)
            j += 1
    return merged + (winners[i:] or losers[j:])


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, r, q = next(data), next(data), next(data)
    m = 2 * n
    score = [next(data) for _ in range(m)]
    power = [next(data) for _ in range(m)]

    # 初始排名：总分从高到低，同分编号小的在前
    order = sorted(range(m), key=lambda i: (-score[i], i))
    for _ in range(r):
        order = play_round(order, score, power)

    print(order[q - 1] + 1)  # 选手编号从 1 开始


if __name__ == "__main__":
    solve()

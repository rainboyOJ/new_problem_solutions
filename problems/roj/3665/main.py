#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 14:25
# update_at: 2026-10-02 14:25

import sys

MAX_SCORE = 600  # 题面保证成绩为不超过 600 的非负整数，值域只有 601 档


def cutoff(cnt: list[int], need: int) -> int:
    """即时分数线：按名次从最高分往下累加，第 need 名落在哪个成绩上。"""
    got = 0
    for score in range(MAX_SCORE, -1, -1):
        got += cnt[score]
        if got >= need:
            return score
    return 0  # 不可达：need 不超过已评出的人数，全档累加必然凑满


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    w = next(data)
    cnt = [0] * (MAX_SCORE + 1)  # 每个成绩档的实时人数
    out: list[str] = []

    for p in range(1, n + 1):
        cnt[next(data)] += 1
        need = max(1, p * w // 100)  # 计划获奖人数：全程整数运算，避开浮点误差
        out.append(str(cutoff(cnt, need)))

    print(' '.join(out))


if __name__ == "__main__":
    solve()

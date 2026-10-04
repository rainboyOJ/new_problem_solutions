#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 10:54
# update_at: 2026-10-02 10:54

import sys

# 五种手势：0 剪刀，1 石头，2 布，3 蜥蜴人，4 斯波克
# 胜负关系表：(先手, 后手) 表示先手胜后手，共 5 × 2 = 10 对
BEATS: set[tuple[int, int]] = {
    (0, 2), (0, 3),  # 剪刀胜布、蜥蜴人
    (1, 0), (1, 3),  # 石头胜剪刀、蜥蜴人
    (2, 1), (2, 4),  # 布胜石头、斯波克
    (3, 2), (3, 4),  # 蜥蜴人胜布、斯波克
    (4, 0), (4, 1),  # 斯波克胜剪刀、石头
}


def winner(hand_a: int, hand_b: int) -> int:
    """单轮判胜：甲胜返回 1，乙胜返回 -1，平局返回 0。"""
    if (hand_a, hand_b) in BEATS:
        return 1
    if (hand_b, hand_a) in BEATS:
        return -1
    return 0


def tally(rounds: int, seq_a: list[int], seq_b: list[int]) -> tuple[int, int]:
    """打满 rounds 轮后返回 (甲得分, 乙得分)，出拳按各自周期循环取。"""
    score_a = score_b = 0
    for r in range(rounds):
        result = winner(seq_a[r % len(seq_a)], seq_b[r % len(seq_b)])
        if result == 1:
            score_a += 1
        elif result == -1:
            score_b += 1
    return score_a, score_b


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    rounds = next(data)  # 共进行 N 次猜拳
    len_a = next(data)   # 小 A 出拳周期长度
    len_b = next(data)   # 小 B 出拳周期长度
    seq_a = [next(data) for _ in range(len_a)]
    seq_b = [next(data) for _ in range(len_b)]

    print(*tally(rounds, seq_a, seq_b))


if __name__ == "__main__":
    solve()

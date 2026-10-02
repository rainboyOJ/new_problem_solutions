#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 17:25
# update_at: 2026-10-02 17:25

import sys

FAIL = "failed"         # 淘汰：出现过 D，或 C 累计两次
OFFER = "offer"         # 通过，但没拿到 special offer
SPECIAL = "sp offer"    # 通过且无 D、A 达三个（词间空格与官方评测输出一致）


def judge(score: str) -> str:
    """按四轮评分判定一个人的结果：先判淘汰，再判是否 special offer。"""
    if "D" in score or score.count("C") >= 2:
        return FAIL
    return SPECIAL if score.count("A") >= 3 else OFFER


def solve() -> None:
    data = sys.stdin.read().split()
    T = int(data[0])              # 面试者个数
    scores = data[1:T + 1]        # 每人一行长度为 4 的评分串
    print("\n".join(map(judge, scores)))


if __name__ == "__main__":
    solve()

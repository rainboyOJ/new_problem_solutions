#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 20:30
# update_at: 2026-09-29 20:30

import sys

# 石头/剪子/布 的克制关系：key 能赢 value。
WIN_OVER = {"Rock": "Scissors", "Scissors": "Paper", "Paper": "Rock"}


def judge(a: str, b: str) -> str:
    """判断一局猜拳的胜者。"""
    if a == b:
        return "Tie"
    if WIN_OVER[a] == b:
        return "Player1"
    return "Player2"


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    n = int(next(data))
    out = [judge(next(data).decode(), next(data).decode()) for _ in range(n)]
    print("\n".join(out))


if __name__ == "__main__":
    solve()

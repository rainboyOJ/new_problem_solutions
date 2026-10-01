#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-28 21:30
# update_at: 2026-09-28 21:30

import sys


def nim_xor(gaps: list[int]) -> int:
    """奇数位间隔（从最右棋子数起第 1、3、5……段）的异或和：0 表示先手必败。"""
    xor_sum = 0
    for i in range(len(gaps) - 1, -1, -2):  # 从右往左，隔一个取一个
        xor_sum ^= gaps[i]
    return xor_sum


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    T = next(data)

    for _ in range(T):
        n = next(data)
        pos = sorted(next(data) for _ in range(n))  # 按网格编号从左到右排列

        # gaps[i] = 第 i 个棋子左边可自由移动的空间，最左棋子以 1 号格为左界
        gaps = [pos[0] - 1] + [pos[i] - pos[i - 1] - 1 for i in range(1, n)]

        # 阶梯 Nim：动第 0、2、4……段（从右数奇数段）等价于取石子堆，
        # 动其余段总能被对手镜像回去，所以只看奇数段异或和
        winner = "Georgia will win" if nim_xor(gaps) else "Bob will win"
        out.append(winner)

    print("\n".join(out))


if __name__ == "__main__":
    solve()

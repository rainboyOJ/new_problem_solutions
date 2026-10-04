#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 10:37
# update_at: 2026-10-01 10:42

import sys
from collections import deque

# 牌面 → 点数：A=1、2~9 原值、0 代表 10、J=11、Q=12、K=13（按这张表逐字加一）。
# 键用 bytes，直接匹配 sys.stdin.buffer 切出来的牌面，省一次解码。
VALUE = {name.encode(): value for value, name in enumerate("A234567890JQK", 1)}

PILE_COUNT = 13  # 13 堆，每堆 4 张
LIVES = 4        # 4 张 K = 4 条命
DEATH = 13       # K 的点数；编号 13 的堆既是生命牌堆，也是点数 13 对应的堆


def solve() -> None:
    cards = sys.stdin.buffer.read().split()
    piles: list[deque[int]] = [deque() for _ in range(PILE_COUNT + 1)]
    for i in range(PILE_COUNT):  # 输入顺序即从上到下
        piles[i + 1].extend(VALUE[c] for c in cards[i * 4:i * 4 + 4])

    up = [0] * (PILE_COUNT + 1)  # up[v]：点数 v 已经"翻开并入堆"了多少张
    for _ in range(LIVES):       # 每死一条命就回到第 1 步，重抽生命牌堆顶
        value = piles[DEATH].popleft()    # 第 1 步：抽生命牌堆最上面的一张
        while value != DEATH:             # 抽到 K 则本轮结束，K 被扔掉、不再入堆
            piles[value].appendleft(value)  # 正面朝上压到对应编号堆的最上边
            up[value] += 1
            value = piles[value].pop()      # 再从同一堆最底下抽一张，继续往下走

    print(sum(up[v] == 4 for v in range(1, DEATH)))  # A~Q 中凑齐 4 张正面朝上的点数个数


if __name__ == "__main__":
    solve()

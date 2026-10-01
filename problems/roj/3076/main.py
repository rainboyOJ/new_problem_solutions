#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 14:48
# update_at: 2026-10-01 14:58

import sys

FULL = 0b1111111110  # 数字 1..9 各占一位，第 0 位空着，方便用位运算直接取候选
RING = (10, 9, 8, 7, 6)  # 按到中心的切比雪夫距离分层：中心 10 分，最外圈 6 分


def solve() -> None:
    weight = [RING[max(abs(i // 9 - 4), abs(i % 9 - 4))] for i in range(81)]  # 81 格的分值
    values = list(map(int, sys.stdin.buffer.read().split()))

    rows, cols, boxes = [0] * 9, [0] * 9, [0] * 9  # 第 1..9 位分别是数字 1..9 是否已用
    gain = 0                                       # 已知数字贡献的固定分数
    blanks: list[int] = []                         # 所有空格的一维下标 r*9+c
    for i, value in enumerate(values):
        if value == 0:
            blanks.append(i)
            continue
        bit = 1 << value
        r, c = divmod(i, 9)
        rows[r] |= bit
        cols[c] |= bit
        boxes[r // 3 * 3 + c // 3] |= bit
        gain += value * weight[i]

    # 空格的位置信息按“空格编号”建表，搜索里只搬编号，不再反复做整除取模
    row_of = [i // 9 for i in blanks]
    col_of = [i % 9 for i in blanks]
    box_of = [i // 27 * 3 + i % 9 // 3 for i in blanks]
    w_of = [weight[i] for i in blanks]
    best = -1

    def dfs(score: int, rest: int, alive: tuple[int, ...]) -> None:
        """在未填的空格 alive 上继续搜；score 是当前总分，rest 是这些空格的分值之和。"""
        nonlocal best
        if not alive:                        # 每个空格都填上了，得到完整解
            best = max(best, score)
            return
        cands = [FULL & ~(rows[row_of[i]] | cols[col_of[i]] | boxes[box_of[i]]) for i in alive]
        # 上界：每个空格都填自己候选里的最大数字（bit_length()-1），这样都追不上当前最优就剪掉
        cap = sum((c.bit_length() - 1) * w_of[j] for c, j in zip(cands, alive))
        if score + cap <= best:
            return
        k = min(range(len(alive)), key=lambda t: cands[t].bit_count())  # MRV：候选最少的格子先决策
        bits, pos = cands[k], alive[k]
        rest -= w_of[pos]
        alive = alive[:k] + alive[k + 1:]
        while bits:
            bit = 1 << bits.bit_length() - 1  # 从最大的数字开始试：先拿到高分，界更紧
            bits ^= bit
            rows[row_of[pos]] |= bit
            cols[col_of[pos]] |= bit
            boxes[box_of[pos]] |= bit
            dfs(score + (bit.bit_length() - 1) * w_of[pos], rest, alive)
            rows[row_of[pos]] ^= bit         # 回溯：撤销这个数字
            cols[col_of[pos]] ^= bit
            boxes[box_of[pos]] ^= bit

    dfs(gain, sum(w_of), tuple(range(len(blanks))))
    print(best)


if __name__ == "__main__":
    solve()

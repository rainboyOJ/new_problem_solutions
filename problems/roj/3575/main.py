#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 08:26
# update_at: 2026-10-02 08:46

import sys

WEIGHT = [[10 - max(abs(r - 4), abs(c - 4)) for c in range(9)] for r in range(9)]  # 靶形分值，中心 10 分向外递减
ALL = 0b1111111110  # 候选集合：数字 1..9 的位都为 1


def max_score(grid: list[list[int]]) -> int:
    """返回该数独所有填法中的最高总分；无数独解时返回 -1。"""
    rows, cols, boxes = [0] * 9, [0] * 9, [0] * 9
    empties: list[tuple[int, int, int]] = []  # 空格 (行, 列, 宫)
    base = 0  # 题目给定数字已经拿到的分数

    for r in range(9):
        for c in range(9):
            b = r // 3 * 3 + c // 3
            if v := grid[r][c]:
                bit = 1 << v
                rows[r] |= bit
                cols[c] |= bit
                boxes[b] |= bit
                base += WEIGHT[r][c] * v
            else:
                empties.append((r, c, b))

    best = -1
    n = len(empties)

    def dfs(k: int, score: int) -> None:
        """填第 k..n-1 号空格；同时用各空格的真实候选做上界剪枝。"""
        nonlocal best
        if k == n:
            best = max(best, score)
            return

        # 一轮扫描：既找候选最少的空格，也顺带算出"每个格子都取最大候选数字"的上界
        bound = score
        pick, pick_cand, pick_cnt = -1, 0, 10
        for i in range(k, n):
            r, c, b = empties[i]
            cand = ALL & ~(rows[r] | cols[c] | boxes[b])  # 该空格当前还能填的数字集合
            if not cand:  # 有格子无数字可填，本分支必死
                return
            bound += WEIGHT[empties[i][0]][empties[i][1]] * (cand.bit_length() - 1)
            cnt = cand.bit_count()
            if cnt < pick_cnt:  # 越少候选越优先定下
                pick, pick_cand, pick_cnt = i, cand, cnt
        if bound <= best:  # 乐观估计也追不上当前最优
            return

        empties[k], empties[pick] = empties[pick], empties[k]  # 选中格换到 k，剩下的仍在 k+1..n-1
        r, c, b = empties[k]
        while pick_cand:
            bit = 1 << (pick_cand.bit_length() - 1)  # 从大数字往小试，尽快抬高手头的 best
            pick_cand ^= bit
            v = bit.bit_length() - 1
            rows[r] |= bit
            cols[c] |= bit
            boxes[b] |= bit
            dfs(k + 1, score + WEIGHT[r][c] * v)
            rows[r] ^= bit
            cols[c] ^= bit
            boxes[b] ^= bit

    dfs(0, base)
    return best


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    grid = [[next(data) for _ in range(9)] for _ in range(9)]  # 9 行每行 9 个数
    print(max_score(grid))


if __name__ == "__main__":
    solve()

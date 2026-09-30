#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-03-31 01:00
# update_at: 2026-03-31 01:00

import sys

ALL_DIGITS = 0x3FE  # 1~9 位掩码：1 << 1 到 1 << 9


def get_weight(r: int, c: int) -> int:
    """计算第 r 行第 c 列格子的靶形分值权重（6 到 10 分）。"""
    return 6 + min(r, 8 - r, c, 8 - c)


def box_id(r: int, c: int) -> int:
    """计算第 r 行第 c 列所在的 3x3 小九宫格编号（0 到 8）。"""
    return (r // 3) * 3 + (c // 3)


def search_max_score(grid: list[list[int]]) -> int:
    """回溯搜索数独的所有合法填法，返回最大加权得分；无解返回 -1。"""
    row_mask = [0] * 9  # 每行已填数字集合的位掩码
    col_mask = [0] * 9  # 每列已填数字集合的位掩码
    box_mask = [0] * 9  # 每宫已填数字集合的位掩码

    initial_score = 0
    empties: list[tuple[int, int]] = []

    for r in range(9):
        for c in range(9):
            v = grid[r][c]
            if v:
                b = box_id(r, c)
                row_mask[r] |= 1 << v
                col_mask[c] |= 1 << v
                box_mask[b] |= 1 << v
                initial_score += v * get_weight(r, c)
            else:
                empties.append((r, c))

    max_score = -1

    def dfs(score: int) -> None:
        nonlocal max_score
        best_r, best_c = -1, -1
        min_choices = 10
        best_mask = 0

        # 最少剩余候选数原则（MRV）挑选分支最少的空格
        for r, c in empties:
            if grid[r][c] == 0:
                avail = ALL_DIGITS & ~(row_mask[r] | col_mask[c] | box_mask[box_id(r, c)])
                cnt = avail.bit_count()
                if cnt == 0:  # 存在无解空格，剪枝
                    return
                if cnt < min_choices:
                    min_choices = cnt
                    best_r, best_c = r, c
                    best_mask = avail
                    if cnt == 1:
                        break

        if min_choices == 10:  # 所有空格均已填满
            if score > max_score:
                max_score = score
            return

        r, c = best_r, best_c
        b = box_id(r, c)
        w = get_weight(r, c)
        mask = best_mask

        # 逆序从 9 到 1 尝试（或按位提取）：lsb 提取并回溯
        while mask:
            lsb = mask & -mask
            d = lsb.bit_length() - 1
            mask ^= lsb

            grid[r][c] = d
            row_mask[r] |= lsb
            col_mask[c] |= lsb
            box_mask[b] |= lsb

            dfs(score + d * w)

            grid[r][c] = 0
            row_mask[r] ^= lsb
            col_mask[c] ^= lsb
            box_mask[b] ^= lsb

    dfs(initial_score)
    return max_score


def solve() -> None:
    lines = [line.strip() for line in sys.stdin if line.strip()]
    if not lines:
        return
    grid = [list(map(int, line.split())) for line in lines]
    ans = search_max_score(grid)
    print(ans)


if __name__ == "__main__":
    solve()

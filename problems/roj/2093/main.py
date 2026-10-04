#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-05-22 19:17
# update_at: 2026-05-22 19:17

import sys
from functools import cache

EMPTY = -1  # 棋盘格未填字母哨兵


def count_valid_grids(grid: list[list[int]]) -> int:
    """在当前已填部分限制下，计算合法的 5x5 标准杨表填充方案数。"""

    @cache
    def dfs(a: int, b: int, c: int, d: int, e: int) -> int:
        ch = a + b + c + d + e
        if ch == 25:
            return 1
        return (
            (dfs(a + 1, b, c, d, e) if a < 5 and grid[0][a] in (EMPTY, ch) else 0)
            + (dfs(a, b + 1, c, d, e) if b < a and grid[1][b] in (EMPTY, ch) else 0)
            + (dfs(a, b, c + 1, d, e) if c < b and grid[2][c] in (EMPTY, ch) else 0)
            + (dfs(a, b, c, d + 1, e) if d < c and grid[3][d] in (EMPTY, ch) else 0)
            + (dfs(a, b, c, d, e + 1) if e < d and grid[4][e] in (EMPTY, ch) else 0)
        )

    return dfs(0, 0, 0, 0, 0)


def encode_to_word(rank: int) -> str:
    """将排名 rank（从 1 开始）还原为对应的 25 字符单词。"""
    grid = [[EMPTY] * 5 for _ in range(5)]
    used = [False] * 25
    word: list[str] = []

    for i in range(25):
        r, c = divmod(i, 5)
        for ch in range(25):
            if used[ch]:
                continue
            if (r > 0 and grid[r - 1][c] > ch) or (c > 0 and grid[r][c - 1] > ch):
                continue
            grid[r][c] = ch
            ways = count_valid_grids(grid)
            if ways >= rank:
                used[ch] = True
                word.append(chr(ord("A") + ch))
                break
            rank -= ways
            grid[r][c] = EMPTY

    return "".join(word)


def word_to_encode(word: str) -> int:
    """将合法单词转换为其对应的排名编码（从 1 开始）。"""
    grid = [[EMPTY] * 5 for _ in range(5)]
    used = [False] * 25
    rank = 1

    for i, ch_char in enumerate(word):
        r, c = divmod(i, 5)
        target_ch = ord(ch_char) - ord("A")
        for ch in range(target_ch):
            if used[ch]:
                continue
            if (r > 0 and grid[r - 1][c] > ch) or (c > 0 and grid[r][c - 1] > ch):
                continue
            grid[r][c] = ch
            rank += count_valid_grids(grid)
            grid[r][c] = EMPTY
        grid[r][c] = target_ch
        used[target_ch] = True

    return rank


def solve() -> None:
    tokens = sys.stdin.read().split()
    if not tokens:
        return
    mode = tokens[0]

    if mode == "N":
        rank = int(tokens[1])
        print(encode_to_word(rank))
    else:
        word = tokens[1]
        print(word_to_encode(word))


if __name__ == "__main__":
    solve()

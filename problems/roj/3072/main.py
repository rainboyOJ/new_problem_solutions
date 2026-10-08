#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 21:15
# update_at: 2026-10-08 21:41

import sys
from functools import cache
from heapq import heappop, heappush

type Board = tuple[int, ...]   # 9 个格子按行优先展开，0 表示空格

FACT = (1, 1, 2, 6, 24, 120, 720, 5040, 40320)  # 康托展开用，FACT[i] = i!
SIZE = 362880                                   # 9!，八数码的全部状态数
UNSEEN = -1                                     # dist 里表示该状态还没搜到
TARGET = (1, 2, 3, 4, 5, 6, 7, 8, 0)            # 正确排列
STEPS = ((-1, 0, 'u'), (1, 0, 'd'), (0, -1, 'l'), (0, 1, 'r'))  # 上、下、左、右


def cantor(state: Board) -> int:
    """康托展开：把 9 格排列映射成 [0, 9!) 中的下标。"""
    return sum(
        sum(1 for j in range(i + 1, 9) if state[j] < state[i]) * FACT[8 - i]
        for i in range(9)
    )


@cache
def manhattan(state: Board) -> int:
    """曼哈顿距离启发式：各数字到目标位置的横纵距离之和，可采纳。"""
    return sum(
        abs(i // 3 - (v - 1) // 3) + abs(i % 3 - (v - 1) % 3) for i, v in enumerate(state) if v
    )


def inversions(nums: list[int]) -> int:
    """忽略空格后的逆序对数；它的奇偶性是不变量，奇数时一定无解。"""
    return sum(1 for i in range(len(nums)) for j in range(i + 1, len(nums)) if nums[i] > nums[j])


def search(start: Board) -> list[str]:
    """A* 搜索最短操作序列；无解时返回空列表（调用方已用逆序数排除了无解）。"""
    start_code, target_code = cantor(start), cantor(TARGET)
    if start_code == target_code:
        return []

    dist = [UNSEEN] * SIZE   # dist[code] = 起点到该状态的最短步数
    prev = [0] * SIZE        # prev[code] = 前驱状态的康托编码
    last_op = [''] * SIZE    # last_op[code] = 从前驱走到该状态的那一步
    dist[start_code] = 0

    heap = [(manhattan(start), start_code, start)]
    while heap:
        f, code, state = heappop(heap)
        # 惰性删除：堆里 f 大于"实际步数 + 启发值"的旧记录已经过期
        expired = f > dist[code] + manhattan(state)
        if expired:
            continue
        if code == target_code:
            break

        blank = state.index(0)
        r, c = divmod(blank, 3)
        for dr, dc, ch in STEPS:
            nr, nc = r + dr, c + dc
            if not (0 <= nr < 3 and 0 <= nc < 3):
                continue
            j = nr * 3 + nc
            board = list(state)
            board[blank], board[j] = board[j], board[blank]
            nxt = tuple(board)
            ncode = cantor(nxt)
            nd = dist[code] + 1
            improved = dist[ncode] == UNSEEN or nd < dist[ncode]
            if improved:
                dist[ncode] = nd
                prev[ncode] = code
                last_op[ncode] = ch
                heappush(heap, (nd + manhattan(nxt), ncode, nxt))

    # 从目标态沿前驱倒推，再反转得到正向操作序列
    path: list[str] = []
    code = target_code
    while code != start_code:
        path.append(last_op[code])
        code = prev[code]
    path.reverse()
    return path


def solve() -> None:
    tokens = sys.stdin.buffer.read().decode().split()
    if len(tokens) == 1:
        tokens = list(tokens[0])   # 题面允许紧凑写法 "1234567x8"，与 cin >> char 行为一致
    if len(tokens) != 9:
        return
    start = tuple(0 if t.lower() == 'x' else int(t) for t in tokens)

    nums = [v for v in start if v]
    if inversions(nums) % 2:
        print("unsolvable")
        return
    print(''.join(search(start)))


if __name__ == "__main__":
    solve()

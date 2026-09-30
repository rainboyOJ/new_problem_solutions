#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-04-18 10:00
# update_at: 2026-04-18 10:00

import sys
from collections import deque
from collections.abc import Iterator

# 相邻移动方向：上下左右在 16 位压缩状态下的位偏移与移动对
MOVES: list[tuple[int, int]] = (
    [(r * 4 + c, r * 4 + c + 1) for r in range(4) for c in range(3)]  # 横向相邻 12 对
    + [(r * 4 + c, (r + 1) * 4 + c) for r in range(3) for c in range(4)]  # 纵向相邻 12 对
)


def next_states(state: int) -> Iterator[int]:
    """产出当前状态经一次相邻格子移动（0 与 1 互换）后能达到的所有新状态。"""
    for u, v in MOVES:
        bit_u = (state >> u) & 1
        bit_v = (state >> v) & 1
        if bit_u != bit_v:
            yield state ^ (1 << u) ^ (1 << v)


def min_moves(start: int, target: int) -> int:
    """BFS 搜索从初始玩具状态到达目标状态所需的最少移动步数。"""
    if start == target:
        return 0

    dist: dict[int, int] = {start: 0}
    queue: deque[int] = deque([start])

    while queue:
        curr = queue.popleft()
        step = dist[curr]
        for nxt in next_states(curr):
            if nxt == target:
                return step + 1
            if nxt not in dist:
                dist[nxt] = step + 1
                queue.append(nxt)

    return -1


def parse_board(lines: list[str]) -> int:
    """将 4 行 01 字符串解析并压缩为一个 16 位的二进制整数。"""
    return sum(
        int(ch) << (r * 4 + c)
        for r, row in enumerate(lines)
        for c, ch in enumerate(row)
    )


def solve() -> None:
    tokens = sys.stdin.read().split()
    if not tokens:
        return

    start_lines = tokens[:4]
    target_lines = tokens[4:8]

    start_state = parse_board(start_lines)
    target_state = parse_board(target_lines)

    ans = min_moves(start_state, target_state)
    print(ans)


if __name__ == "__main__":
    solve()

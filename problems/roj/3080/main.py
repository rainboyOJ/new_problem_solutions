#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 15:14
# update_at: 2026-10-01 15:14

import sys
from collections import deque
from collections.abc import Iterator

START, GOAL, OBSTACLE = b"KH*"  # 三个标记的 ASCII 码；bytes 解包出来的就是整数

JUMPS = (  # 马走日的 8 个位移，一行一个家族：先 |dr|=1 的 4 个，再 |dr|=2 的 4 个
    (1, 2), (1, -2), (-1, 2), (-1, -2),
    (2, 1), (2, -1), (-2, 1), (-2, -1),
)


def neighbours(pos: int, board: bytes, C: int, R: int) -> Iterator[int]:
    """产出 pos 一次跳跃能落到的可行下标：越界或踩到障碍的候选直接不产出。"""
    row, col = divmod(pos, C)
    for dr, dc in JUMPS:
        r, c = row + dr, col + dc
        if 0 <= r < R and 0 <= c < C and board[r * C + c] != OBSTACLE:
            yield r * C + c


def bfs(board: bytes, C: int, R: int, start: int) -> int:
    """逐层扩展求最短路，返回首次够到草的层数；题目保证有解，故不会走空。"""
    dist = [-1] * (C * R)  # -1 同时表示"没访问过"和"距离未知"
    dist[start] = 0
    q = deque([start])
    while q:
        pos = q.popleft()
        for nxt in neighbours(pos, board, C, R):
            if dist[nxt] < 0:
                if board[nxt] == GOAL:  # 先进先出，第一次够到就是最少跳跃次数
                    return dist[pos] + 1
                dist[nxt] = dist[pos] + 1
                q.append(nxt)
    return -1


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    C, R = int(next(data)), int(next(data))
    board = b"".join(next(data) for _ in range(R))  # 逐行拼接，下标即 r * C + c

    print(bfs(board, C, R, board.index(START)))


if __name__ == "__main__":
    solve()

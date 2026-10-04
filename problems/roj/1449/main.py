#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# 魔板 Magic Squares 题解
# create_at: 2026-07-05 22:00
# update_at: 2026-07-05 22:00

import sys
from collections import deque

# 三种操作在顺时针序列上的下标重排：s' = tuple(s[i] for i in perm)
PERMS = [
    (7, 6, 5, 4, 3, 2, 1, 0),  # A：交换上下两行，序列整体翻转
    (3, 0, 1, 2, 5, 6, 7, 4),  # B：最右列插入最左列
    (0, 6, 1, 3, 4, 2, 5, 7),  # C：中央 2x2 顺时针旋转
]

START = tuple(range(1, 9))  # 基本状态 1..8


def solve() -> None:
    target = tuple(map(int, sys.stdin.read().split()))  # 目标状态，顺时针序列

    # BFS：按 A、B、C 顺序扩展，首次到达即为字典序最小的最短操作序列
    prev: dict[tuple[int, ...], tuple[tuple[int, ...], str]] = {}
    queue = deque([START])
    while queue:
        state = queue.popleft()
        if state == target:
            break
        for letter, perm in zip("ABC", PERMS):
            nxt = tuple(state[i] for i in perm)
            if nxt not in prev:
                prev[nxt] = (state, letter)
                queue.append(nxt)

    # 回溯还原路径
    path: list[str] = []
    state = target
    while state != START:
        state, letter = prev[state]
        path.append(letter)
    answer = ''.join(reversed(path))

    print(len(answer))
    # 除最后一行外每行 60 个字符
    print('\n'.join(answer[i:i + 60] for i in range(0, len(answer), 60)))


if __name__ == "__main__":
    solve()

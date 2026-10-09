#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-09 08:30
# update_at: 2026-10-09 09:20

import sys
from collections import deque

# 四个方向键的 (dr, dc)：上、下、左、右
DR = (-1, 1, 0, 0)
DC = (0, 0, -1, 1)


def solve() -> None:
    data = sys.stdin.buffer.read().split()
    if not data:
        return
    tok = iter(data)
    r = int(next(tok))
    c = int(next(tok))
    grid = [next(tok) for _ in range(r)]      # 每行是 bytes，比较按字节走，比 str 快
    target = next(tok) + b'*'                 # 题面要求结尾打印换行符，即键盘上的 '*'
    n = len(target)
    total = r * c                             # 格子总数，格子 (i, j) 编码为 i * c + j

    # 跳跃表 jump[p * 4 + d]：从格子 p 按方向 d 跳一次后落到的格子编号。
    # 规则是「跳到该方向上第一个与 grid[p] 字符不同的格子」；若一路相同或出界，
    # 则原地不动（值等于 p）。
    jump = []
    for i in range(r):
        row = grid[i]
        for j in range(c):
            here = row[j]
            for d in range(4):
                a = i + DR[d]
                b = j + DC[d]
                while 0 <= a < r and 0 <= b < c and grid[a][b] == here:
                    a += DR[d]
                    b += DC[d]
                jump.append(a * c + b if 0 <= a < r and 0 <= b < c else i * c + j)

    # max_k[p]：到达格子 p 时曾经达到过的最大已打印字符数。新状态的 k 不超过它时，
    # 之前那个状态用的步数不多、打印得却不少，后缀被包含 ⇒ 当前状态可剪掉。
    max_k = [-1] * total

    # BFS 状态 (p, k, dist)：光标在格子 p、已打印 k 个字符、共按了 dist 次键
    q = deque([(0, 0, 0)])
    max_k[0] = 0

    while q:
        p, k, dist = q.popleft()

        # 按键一：选择键，打印当前字符（需要与待打印字符一致）
        if grid[p // c][p % c] == target[k]:
            nk = k + 1
            if nk == n:
                print(dist + 1)
                return
            if nk > max_k[p]:
                max_k[p] = nk
                q.append((p, nk, dist + 1))

        # 按键二：四个方向键，各跳到该方向上的下一个不同字符
        base = p * 4
        for d in range(4):
            np = jump[base + d]
            if np != p and k > max_k[np]:
                max_k[np] = k
                q.append((np, k, dist + 1))


if __name__ == "__main__":
    solve()

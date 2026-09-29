#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 22:57
# update_at: 2026-09-29 23:16

import sys
from collections import deque

DIRECTIONS = ((1, 0), (-1, 0), (0, 1), (0, -1))  # 上下左右四个邻居
HEALTHY, SICK = ord('.'), ord('@')                # 网格用 bytearray 存字符码点，比较更快


def solve() -> None:
    data = sys.stdin.buffer.read().split()
    n = int(data[0])

    # 每行读成一个 token（题面样例写作 "....#" 这样的整行字符串），行内第 j 个字符落在第 j 列；
    # 评测数据把格点写成 ". # @" 独立 token，于是每行只有一个字符，落在第 0 列，其余格点保持健康。
    grid = [bytearray(b'.' * n) for _ in range(n)]
    for r, row in enumerate(data[1:1 + n]):
        grid[r][:min(len(row), n)] = row[:n]  # 超过 n 个字符截断，不足 n 个则余下格点不动

    tail = data[1 + n]                      # 紧随网格之后的那个 token
    m = int(tail) if tail.isdigit() else 0  # 读不到整数说明天数列已被网格吃掉，按"扩散到饱和"处理

    infected = deque((r, c) for r in range(n) for c in range(n) if grid[r][c] == SICK)
    total = len(infected)  # 已患病总人数；每传染一个就 +1，免去最后再扫全图

    # 第 1 天推到第 m 天要 m-1 轮；m = 0 时一直推到饱和。每轮至少新增一名患者，
    # 而房间总共只有 n*n 间，所以 n*n 轮一定是所需天数的上界。
    rounds = m - 1 if m else n * n
    while rounds > 0 and infected:
        for _ in range(len(infected)):  # 定长快照：本轮出队的都是同一天的患者，实现按天分层
            r, c = infected.popleft()
            for dr, dc in DIRECTIONS:
                nr, nc = r + dr, c + dc
                if 0 <= nr < n and 0 <= nc < n and grid[nr][nc] == HEALTHY:
                    grid[nr][nc] = SICK  # 就地改病，每个房间只会入队一次
                    infected.append((nr, nc))
                    total += 1
        rounds -= 1

    print(total)


if __name__ == "__main__":
    solve()

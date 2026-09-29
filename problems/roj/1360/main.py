#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 07:03
# update_at: 2026-09-30 07:06

import sys
from collections import deque


def fewest_presses(n: int, start: int, target: int, jumps: list[int]) -> int:
    """无权有向图 BFS：返回 start 到 target 的最少按键次数，不可达返回 -1。

    楼层是顶点，第 i 层的「上/下」两个有效按钮是两条代价为 1 的出边，
    所以队列的层号就是按键次数，第一次到达 target 即为最少次数。
    """
    dist = [-1] * (n + 1)  # -1 兼作未访问标记和「不可达」的答案
    dist[start] = 0
    queue = deque([start])
    while queue:
        floor = queue.popleft()
        for nxt in (floor - jumps[floor], floor + jumps[floor]):  # 下 / 上两个按钮
            in_building = 1 <= nxt <= n  # 同时挡掉越界与 K_i = 0 的失效按钮
            if in_building and dist[nxt] < 0:
                dist[nxt] = dist[floor] + 1
                queue.append(nxt)
    return dist[target]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, a, b = next(data), next(data), next(data)
    jumps = [0] + [next(data) for _ in range(n)]  # 1-indexed：jumps[i] 即题面的 K_i

    print(fewest_presses(n, a, b, jumps))


if __name__ == "__main__":
    solve()

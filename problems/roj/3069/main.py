#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 14:23
# update_at: 2026-10-01 14:23

import sys
from collections import deque

SLASH, BACKSLASH = 47, 92  # 字节 b'/' 与 b'\\' 的 ASCII 码，直接和网格字节比
INF = 1 << 30              # 到不了的距离，比 250000 步的上界大得多

# 一条斜边可以看成"从当前格点走到对角的那个格点"：
# (格点位移 di, dj；被穿过的格子相对当前格点的位移 ci, cj；该格原本应有的方向)。
NEIGHBOURS = (
    (1, 1, 0, 0, BACKSLASH),      # 右下：穿过格子 (i, j)，本来就得是 '\'
    (1, -1, 0, -1, SLASH),        # 左下：穿过格子 (i, j-1)，本来就得是 '/'
    (-1, 1, -1, 0, SLASH),        # 右上：穿过格子 (i-1, j)，本来就得是 '/'
    (-1, -1, -1, -1, BACKSLASH),  # 左上：穿过格子 (i-1, j-1)，本来就得是 '\'
)


def min_rotations(rows: list[bytes], R: int, C: int) -> int:
    """从左上角格点走到右下角格点所需的最少旋转次数，不可达返回 INF。

    把每个格点当节点：方向已经对上的斜边权为 0，需要转一次的权为 1，
    于是问题变成 0-1 图上的最短路，用双端队列 BFS 在 O(RC) 内求出。
    """
    W = C + 1                                # 格点按 u = i * W + j 一维编号
    dist = [INF] * ((R + 1) * W)
    dist[0] = 0
    target = R * W + C
    queue = deque([0])

    while queue:
        u = queue.popleft()
        if u == target:
            break                            # 出队时距离已定型，后面不可能更小
        d = dist[u]
        i, j = divmod(u, W)
        for di, dj, ci, cj, want in NEIGHBOURS:
            ni, nj = i + di, j + dj
            if 0 <= ni <= R and 0 <= nj <= C:
                nd = d + (rows[i + ci][j + cj] != want)  # 方向不对就要转这个格子
                v = u + di * W + dj
                if nd < dist[v]:
                    dist[v] = nd
                    if nd > d:
                        queue.append(v)
                    else:
                        queue.appendleft(v)  # 0 权边走队头，双端队列才保持距离有序

    return dist[target]


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    out: list[str] = []
    T = int(next(data))

    for _ in range(T):
        R, C = int(next(data)), int(next(data))
        rows = [next(data) for _ in range(R)]
        answer = min_rotations(rows, R, C)
        out.append("NO SOLUTION" if answer >= INF else str(answer))

    print('\n'.join(out))


if __name__ == "__main__":
    solve()

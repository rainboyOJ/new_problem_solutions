# ROJ 1380 分糖果：从 C 出发的 BFS 最短路 + 吃糖时间
"""n 个小朋友、p 条无权边，C 开始发糖，每秒传一格、每个人收到后 m 秒吃完。
答案 = max(最短路) + m + 1。"""

import sys
from collections import deque


def main() -> None:
    data: list[str] = sys.stdin.buffer.read().split()
    it = iter(data)
    n, p, c = int(next(it)), int(next(it)), int(next(it))
    m = int(next(it))
    # 邻接表
    g: list[list[int]] = [[] for _ in range(n + 1)]
    for _ in range(p):
        x, y = int(next(it)), int(next(it))
        g[x].append(y)
        g[y].append(x)

    # BFS 求 C 到所有人的最短路（每条边耗时 1 秒）
    INF = -1  # 用 -1 表示未访问
    dist: list[int] = [INF] * (n + 1)
    dist[c] = 0
    q = deque([c])
    while q:
        x = q.popleft()
        for y in g[x]:
            if dist[y] < 0:
                dist[y] = dist[x] + 1
                q.append(y)

    # 最晚收到糖的人：走了 max 秒，再花 m 秒吃完，且第一秒已经开始传
    print(max(dist[1:]) + m + 1)


if __name__ == "__main__":
    main()

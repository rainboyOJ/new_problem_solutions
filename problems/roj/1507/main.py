#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 15:06
# update_at: 2026-09-30 15:06

import sys


def has_negative_cycle(n: int, edges: list[tuple[int, int, int]]) -> bool:
    """图里是否存在负环：以超级源点做 n 轮松弛，第 n 轮还能松弛即有负环。

    "回到出发时刻之前"等价于存在总权为负的闭环（闭环必含负环），
    所以只判负环，不必关心起点和具体路径。
    """
    dist = [0] * (n + 1)  # 超级源点到各点初值都为 0：一轮同时覆盖所有连通块
    for _ in range(n):
        relaxed = False
        for u, v, w in edges:
            if dist[u] + w < dist[v]:
                dist[v] = dist[u] + w
                relaxed = True
        if not relaxed:  # 本轮无松弛：距离已稳定，之后不可能再松弛
            return False
    return True  # 第 n 轮仍在松弛 → 存在负环


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    F = next(data)

    for _ in range(F):
        n, m, w = next(data), next(data), next(data)  # 农场规模：地/小路/虫洞
        # 小路无向：来回各记一条正权边；虫洞有向：时间倒流，权取负。
        roads = [(next(data), next(data), next(data)) for _ in range(m)]
        edges = roads + [(e, s, t) for s, e, t in roads]  # 反向边，读入顺序不变
        edges += [(next(data), next(data), -next(data)) for _ in range(w)]
        out.append('YES' if has_negative_cycle(n, edges) else 'NO')

    print('\n'.join(out))


if __name__ == "__main__":
    solve()

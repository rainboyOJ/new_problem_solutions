#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 01:34
# update_at: 2026-10-02 01:42

import sys
from collections import deque

INF = 1 << 30  # 层号哨兵：比任何合法层号都大，表示"这个点还没被 BFS 访问到"


def shortest_augmenting_length(adj: list[list[int]], match_l: list[int],
                               match_r: list[int], dist: list[int]) -> int:
    """给左部点分层，返回最短增广路的边数；一条增广路都没有时返回 INF。

    从每个未匹配左部点出发，沿"未匹配边 → 匹配边"交替走：走到右部点 v 后，
    下一步只能沿 v 的匹配边回到 match_r[v]，所以层号只需记在左部点上。
    BFS 第一次碰到未匹配右部点得到的层数就是最短增广路长度。
    """
    queue = deque()
    for u in range(len(adj)):
        free = match_l[u] < 0          # 未匹配的左部点才是增广路起点
        dist[u] = 0 if free else INF
        if free:
            queue.append(u)
    shortest = INF
    while queue:
        u = queue.popleft()
        if dist[u] >= shortest:        # 同层及更深的点只会给出不更短的路，剪掉
            continue
        for v in adj[u]:
            nxt = match_r[v]
            if nxt < 0:                # 右部点空闲：找到一条增广路
                shortest = dist[u] + 1
            elif dist[nxt] == INF:     # 已匹配右部点：顺着它的匹配边走到左部点 nxt
                dist[nxt] = dist[u] + 1
                queue.append(nxt)
    return shortest


def try_augment(u: int, adj: list[list[int]], match_l: list[int], match_r: list[int],
                dist: list[int], shortest: int) -> bool:
    """从已分层的左部点 u 出发找一条长度恰为 shortest 的增广路，成功就翻转匹配。

    只沿分层方向 dist + 1 往下走，所以递归深度不超过层数（< N），无需放开递归上限。
    """
    for v in adj[u]:
        nxt = match_r[v]
        if nxt < 0:
            grown = dist[u] + 1 == shortest        # 只有最短增广路才在本轮使用
        else:
            grown = dist[nxt] == dist[u] + 1 and try_augment(
                nxt, adj, match_l, match_r, dist, shortest)
        if grown:
            match_l[u], match_r[v] = v, u
            return True
    dist[u] = INF             # 这个点往下到不了自由右部点，本轮放弃它
    return False


def max_matching(adj: list[list[int]], right_size: int) -> int:
    """Hopcroft–Karp：反复"分层 + 沿最短增广路批量增广"，直到不存在增广路。

    每轮把这一层能用的增广路一次用完，所以最多 O(√V) 轮；由增广路定理，
    不存在增广路时的匹配就是最大匹配。
    """
    match_l = [-1] * len(adj)      # 左部点的匹配对象，-1 表示未匹配
    match_r = [-1] * right_size    # 右部点的匹配对象，-1 表示未匹配
    dist = [INF] * len(adj)
    total = 0
    while True:
        shortest = shortest_augmenting_length(adj, match_l, match_r, dist)
        if shortest == INF:
            return total
        total += sum(try_augment(u, adj, match_l, match_r, dist, shortest)
                     for u in range(len(adj)) if match_l[u] < 0)


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []

    for n in data:                 # 终止行只有一个 0，它落在 N 的位置上
        if n == 0:
            break
        m, k = next(data), next(data)

        # 模式 0 是初始状态：用它执行的任务不需要重启，不产生任何约束，
        # 因此只把 a[i] != 0 且 b[i] != 0 的任务建成二分图的边。
        adj: list[list[int]] = [[] for _ in range(n)]
        for _ in range(k):
            _i, a, b = next(data), next(data), next(data)  # 任务编号只作标识，不参与计算
            if a and b:
                adj[a].append(b)

        out.append(str(max_matching(adj, m)))

    print('\n'.join(out))


if __name__ == "__main__":
    solve()

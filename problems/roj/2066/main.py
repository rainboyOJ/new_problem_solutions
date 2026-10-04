#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-05-22 19:17
# update_at: 2026-05-22 19:17

import sys

NO_MATCH = 0  # 牛栏未匹配哨兵编号


def find_path(cow: int, adj: list[list[int]], match: list[int], visited: list[bool]) -> bool:
    """用 DFS 寻找增广路：尝试为奶牛 cow 分配牛栏。"""
    for stall in adj[cow]:
        if visited[stall]:
            continue
        visited[stall] = True
        # 若牛栏未被占用，或占用该牛栏的牛能腾挪到其它牛栏，则匹配成功
        if match[stall] == NO_MATCH or find_path(match[stall], adj, match, visited):
            match[stall] = cow
            return True
    return False


def max_bipartite_matching(n: int, m: int, adj: list[list[int]]) -> int:
    """使用匈牙利算法求解二分图最大匹配数。"""
    match = [NO_MATCH] * (m + 1)
    ans = 0
    for cow in range(1, n + 1):
        visited = [False] * (m + 1)
        if find_path(cow, adj, match, visited):
            ans += 1
    return ans


def solve() -> None:
    tokens = sys.stdin.buffer.read().split()
    if not tokens:
        return
    data = iter(tokens)
    n = int(next(data))
    m = int(next(data))

    adj: list[list[int]] = [[] for _ in range(n + 1)]
    for cow in range(1, n + 1):
        cnt = int(next(data))
        adj[cow] = [int(next(data)) for _ in range(cnt)]

    print(max_bipartite_matching(n, m, adj))


if __name__ == "__main__":
    solve()

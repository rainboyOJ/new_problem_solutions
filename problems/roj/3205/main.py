#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 01:45
# update_at: 2026-10-02 01:52

import sys
from itertools import accumulate, chain

# 马的八个落点：行、列各变一次奇偶，(r + c) 的奇偶必然翻转。
# 所以棋盘天然二染色，同色格互不攻击，攻击边只存在于异色格之间。
STEPS = ((-2, -1), (-2, 1), (-1, -2), (-1, 2), (1, -2), (1, 2), (2, -1), (2, 1))


def build_csr(n: int, m: int, blocked: bytearray) -> tuple[list[int], list[int]]:
    """左部取偶格（(r+c) 为偶），把邻接表压成 CSR：返回 (行偏移 offset, 邻居表 flat)。"""
    neighbours = [
        [
            (r + dr) * m + c + dc
            for dr, dc in STEPS
            if 0 <= r + dr < n and 0 <= c + dc < m and not blocked[(r + dr) * m + c + dc]
        ]
        for r in range(n)
        for c in range(m)
        if not (r + c) & 1 and not blocked[r * m + c]
    ]
    return list(accumulate(map(len, neighbours), initial=0)), list(chain.from_iterable(neighbours))


def max_matching(offset: list[int], flat: list[int], size: int) -> int:
    """匈牙利算法求二分图最大匹配（左部偶格、右部奇格），返回匹配边的条数。

    左部第 k 个点在 CSR 里的行区间是 [offset[k], offset[k+1])。先做一遍贪心拿到
    初始匹配，再只为还没配上的左部点找增广路：贪心不改变正确性和最坏复杂度，
    但能让常见的棋盘数据几乎不需要增广。
    """
    match = [-1] * size  # 右部格 -> 匹配到它的左部格，-1 表示还空着
    seen = [0] * size    # 右部格 -> 最后一次被访问的轮次；轮次互不相同，等价于每轮清空访问标记
    total = 0
    for u in range(len(offset) - 1):
        for v in flat[offset[u]:offset[u + 1]]:
            if match[v] < 0:
                match[v] = u  # 贪心：每个左部点优先抢一个还空着的右部点
                total += 1
                break
    for round_id in range(1, len(offset)):
        u0 = round_id - 1
        already_matched = any(match[v] == u0 for v in flat[offset[u0]:offset[u0 + 1]])
        if already_matched:
            continue  # 贪心阶段已经配上，不用再为它找增广路
        # 显式栈代替递归：帧是 (左部格, 下一个待试的邻居位置, 进入它时经过的右部格)
        stack = [(u0, offset[u0], -1)]
        while stack:
            u, i, via = stack[-1]
            if i >= offset[u + 1]:  # 这个左部点的所有出路都试过了，回溯
                stack.pop()
                continue
            stack[-1] = (u, i + 1, via)
            v = flat[i]
            if seen[v] == round_id:  # 本轮已访问过这个右部格，再走一次没有新信息
                continue
            seen[v] = round_id
            if match[v] < 0:  # 撞上空闲的右部格：找到一条增广路
                match[v] = u
                for j in range(len(stack) - 1, 0, -1):  # 把路上原来的匹配边各后移一位
                    match[stack[j][2]] = stack[j - 1][0]
                total += 1
                stack.clear()
                break
            stack.append((match[v], offset[match[v]], v))  # 该格已被占用，顺着它的匹配边继续走
    return total


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m, T = next(data), next(data), next(data)
    blocked = bytearray(n * m)
    for _ in range(T):
        x, y = next(data), next(data)
        blocked[(x - 1) * m + y - 1] = 1

    offset, flat = build_csr(n, m, blocked)
    free = n * m - blocked.count(1)  # 未被禁止的格子数，也就是二分图的 |V|
    # 最大独立集 = 顶点数 - 最大匹配（König 定理），顶点只数没被禁止的格子
    print(free - max_matching(offset, flat, n * m))


if __name__ == "__main__":
    solve()

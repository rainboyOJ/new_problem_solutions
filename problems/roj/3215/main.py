#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-10-02 02:23

import sys
from collections import deque

SPEED = {"S": 1000, "G": 500, "D": 300, "T": 200, "K": 150}  # 五种车次的速度


def build_graph(lines_txt: list[str]) -> tuple[int, list[list[tuple[int, int]]]]:
    """把每条行车路线建成一条有向边，返回 (点数, 邻接表)。

    连接规则是有向的：前一条路线的末尾车次接到后一条的开头车次，
    所以路线对应"开头车次 → 末尾车次"的有向边，高铁环必须顺着箭头走。
    边上存 a = (n+1)·(2×速度和) + 1，n 是点数；放大加一是为了让
    "权值和 ≥ 0 的环"精确等价于"放大后权值和 > 0 的正环"（见判定函数）。
    """
    node_id: dict[str, int] = {}
    edges: list[tuple[str, str, int]] = []
    for line in lines_txt:
        codes = line.split("-")
        s = sum(SPEED[code[0]] for code in codes)  # 车次速度只看字母，与编号无关
        edges.append((codes[0], codes[-1], s))
        node_id.setdefault(codes[0], len(node_id))
        node_id.setdefault(codes[-1], len(node_id))
    n = len(node_id)
    scale = n + 1  # 环的权值和是整数，放大 n+1 倍后每条边加 1 不会改变 ≥ 0 的判定
    adj: list[list[tuple[int, int]]] = [[] for _ in range(n)]
    for head, tail, s in edges:
        u, v = node_id[head], node_id[tail]
        adj[u].append((v, scale * 2 * s + 1))
    return n, adj


def has_cycle_avg_ge(n: int, adj: list[list[tuple[int, int]]], r: int) -> bool:
    """判断是否存在平均值 ≥ r − 0.5 的高铁环（SPFA 判正环）。

    环 C 满足 avg(C) ≥ r − 0.5 ⟺ Σ(2s−(2r−1)) ≥ 0。记 scale = n+1，由于
    Σ(2s−(2r−1)) 是整数，"≥ 0" ⟺ "scale×它 + |C| > 0"，后者恰好是对
    边权 a−scale·(2r−1) 判严格正环——SPFA 的计数法只能找严格正环，
    这个放大加一的恒等变换把边界情形（平均值恰为 k+0.5）也判对。
    """
    offset = (n + 1) * (2 * r - 1)
    dist = [0] * n          # 虚拟超级源（连向所有点）出发的最长路，初值全 0
    edge_cnt = [0] * n      # 当前最长路用掉的边数，达到 n 说明 predecessor 链成环
    in_queue = bytearray(n)
    queue = deque(range(n))  # 所有点同时入队，等价于一个超级源点
    for u in range(n):
        in_queue[u] = 1
    while queue:
        u = queue.popleft()
        in_queue[u] = 0
        du = dist[u]
        au = adj[u]
        for v, a in au:
            nd = du + a - offset
            if nd > dist[v]:
                dist[v] = nd
                edge_cnt[v] = edge_cnt[u] + 1
                if edge_cnt[v] >= n:  # 链上有 n 条边 ⇒ 前驱链成环 ⇒ 严格正环
                    return True
                if not in_queue[v]:
                    # SLF 优化：比队首大就插队首，正环能让 dist 更快抬升
                    if queue and nd > dist[queue[0]]:
                        queue.appendleft(v)
                    else:
                        queue.append(v)
                    in_queue[v] = 1
    return False


def rounded_best_avg(n: int, adj: list[list[tuple[int, int]]]) -> int:
    """整数二分四舍五入后的答案 r：判定条件是存在平均值 ≥ r − 0.5 的环。"""
    lo, hi = 1, 20001  # 平均值 ≤ 单条路线速度和上限 20000，hi 是取不到的上界
    while lo < hi:
        mid = (lo + hi) // 2
        if has_cycle_avg_ge(n, adj, mid):  # 判"平均值 ≥ mid − 0.5"
            lo = mid + 1
        else:
            hi = mid
    # lo 是第一个判定不成立的 r，最大可行值 = lo − 1；
    # lo 仍为 1 说明 r=1（阈值 0.5）都不成立，图中没有任何环
    return lo - 1 if lo > 1 else -1


def solve() -> None:
    rows = sys.stdin.buffer.read().decode().replace("\r", "").split("\n")
    m = int(rows[0])
    n, adj = build_graph(rows[1 : m + 1])
    print(rounded_best_avg(n, adj))


if __name__ == "__main__":
    solve()

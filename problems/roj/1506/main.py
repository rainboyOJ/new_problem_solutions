#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 15:30
# update_at: 2026-09-30 15:30

import sys
from array import array

INF = 10**15  # 不可达哨兵：真实路径权值和 |w| 合计至多 3×10^10，远小于此


def relax(n: int, edges: list[tuple[int, int, int | float]], is_int: bool) -> list[array]:
    """Karp 递推表 F[j][v]：恰好 j 条边、以 v 结尾的最小权行走（起点任取）。"""
    kind = "q" if is_int else "d"
    rows: list[array] = [array(kind, [0] * n)]  # F[0][v] = 0：空行走权为 0
    prev = rows[0]
    for _ in range(n):
        # 上一行是哨兵时不剪枝：哨兵 + 负权仍落在哨兵带内，永远不会冒充真实值
        cur = [INF] * n
        for u, v, w in edges:
            x = prev[u] + w
            if x < cur[v]:
                cur[v] = x
        prev = array(kind, cur)
        rows.append(prev)
    return rows


def pick_witness(rows: list[array], n: int) -> tuple[int, int]:
    """按 Karp 公式挑出最小平均值的见证对 (v, k)：min_v max_k (F[n][v]-F[k][v])/(n-k)。"""
    fn = rows[n]
    best = [x / n for x in fn]  # k=0 候选：F[0][v]=0，故为 F[n][v]/n
    best_k = [0] * n
    for k in range(1, n):
        row = rows[k]
        step = 1.0 / (n - k)
        for v in range(n):
            q = (fn[v] - row[v]) * step  # 两个候选分数间隔 ≥ 1/(d1·d2)，浮点比较不会误序
            if q > best[v]:
                best[v] = q
                best_k[v] = k
    v0 = min(range(n), key=best.__getitem__)  # 取不到 F[n][v] 的点 best 恒大，不会当选
    return v0, best_k[v0]


def round8(num: int, den: int) -> str:
    """把整数分数 num/den 四舍五入到 8 位小数（0.5 远离零取整，对齐 printf）。"""
    sign = "-" if num < 0 else ""
    scaled = (2 * abs(num) * 10**8 + den) // (2 * den)
    whole, frac = divmod(scaled, 10**8)
    return f"{sign}{whole}.{frac:08d}"


def solve() -> None:
    data = sys.stdin.buffer.read().split()
    it = iter(data)
    n, m = int(next(it)), int(next(it))

    # 权值允许实数（样例 2 的 -2.9）；纯整数输入走精确整数运算，保证 8 位小数不被浮点误差带偏
    edges: list[tuple[int, int, int | float]] = []
    is_int = True
    for _ in range(m):
        u, v = int(next(it)) - 1, int(next(it)) - 1
        token = next(it)
        if b"." in token:
            is_int = False
            w: int | float = float(token)
        else:
            w = int(token)
        edges.append((u, v, w))

    rows = relax(n, edges, is_int)
    v0, k0 = pick_witness(rows, n)
    num = rows[n][v0] - rows[k0][v0]  # 见证分数的分子，整数输入下精确
    den = n - k0
    print(round8(num, den) if is_int else f"{num / den:.8f}")


if __name__ == "__main__":
    solve()

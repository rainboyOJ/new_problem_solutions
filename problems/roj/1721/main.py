#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 18:33
# update_at: 2026-10-07 18:33

import sys
from itertools import accumulate
from operator import itemgetter

INF = 1 << 30  # 不可达标记；真实答案 <= 149 * 5000 = 745000，被它污染过的格只会更大
JUNK = 10 ** 8  # 一格超过它就说明从没被真正走到过，该询问无解输出 -1

# 类型别名（Python 3.12+ 的 type 语句），相当于 C++ 的 using / typedef
type Edge = tuple[int, int, int]  # (u, v, w) 一条有向边
type Table = dict[int, list[list[int]]]  # F[a][v][k]：从 a 走恰好 k 条边到 v 的最小边权和
type StepCap = dict[int, int]  # 起点 a -> 它被问到的最大边数（已夹到 [0, n]）


def build_table(edges: list[Edge], cap: StepCap, n: int) -> Table:
    """按边权升序逐边松弛，算出每个询问起点的 F[a][v][k]，k 上限只取该起点真正会问到的 cap[a]。"""
    F: Table = {a: [[INF] * (cap[a] + 1) for _ in range(n + 1)] for a in cap}
    for a in cap:
        F[a][a][0] = 0  # 走 0 条边：自己到自己，代价 0
    for u, v, w in edges:  # 边已按 w 升序排好，这个处理顺序就是行走时边的使用顺序
        for fa in F.values():
            dst, src = fa[v], fa[u]
            # 整段 k 交给 map / 推导式在 C 层跑：右侧按旧值算完再整体写回，
            # 等价于"所有 k 同时更新"，所以同一次松弛里这条边不会被用上两回。
            dst[1:] = list(map(min, dst[1:], [x + w for x in src[:-1]]))
    return F


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m, q = next(data), next(data), next(data)
    edges: list[Edge] = [(next(data), next(data), next(data)) for _ in range(m)]
    queries: list[Edge] = [(next(data), next(data), next(data)) for _ in range(q)]
    edges.sort(key=itemgetter(2))  # 按 w 升序；题面保证 w 两两不同，排序顺序即行走顺序

    # 边数上限统一夹到 [0, n]：正权下最优解一定是简单路径，长度不超过 n-1；
    # c 没给上界（数据里到 1e9），也可能取 0，负数按不可走处理。
    steps: list[int] = [max(0, min(c, n)) for _, _, c in queries]
    cap: StepCap = {}
    for (a, _, _), step in zip(queries, steps):
        cap[a] = max(cap.get(a, 0), step)

    F = build_table(edges, cap, n)

    # 只有被问到的 (起点, 终点) 行要把"恰好 k 条边"改成"不超过 k 条边"：
    # 累计最小值一次成型，代替再扫一遍 k。
    asked = {(a, b) for a, b, _ in queries}
    best = {pair: list(accumulate(F[pair[0]][pair[1]], min)) for pair in asked}

    ans: list[str] = []
    for (a, b, _), step in zip(queries, steps):
        cost = best[a, b][step]
        ans.append(str(cost) if cost <= JUNK else "-1")
    print("\n".join(ans))


if __name__ == "__main__":
    solve()

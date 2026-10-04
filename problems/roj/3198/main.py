#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 01:50
# update_at: 2026-10-02 01:50

import sys
from collections import deque
from collections.abc import Iterator
from itertools import accumulate

MOD = 10**9 + 7  # 路径条数按大质数取模：入边前段条数 × 出边后段条数恰等于总条数时认定为必经边
INF = 1 << 60    # 最短路哨兵


def topsort(n: int, adj: list[list[tuple[int, int, int]]], indeg: list[int], src: int) -> tuple[list[int], list[int]]:
    """从 src 沿 adj 拓扑 DP：返回各点路径条数（mod MOD）与最短路树入边编号。

    Kahn 队列初始收入所有入度为 0 的点；落在环上（及环下游）的点永远不会出队，
    路径条数保持 0，与题目 std 的行为完全一致。
    """
    cnt = [0] * n
    cnt[src] = 1
    dist = [INF] * n
    dist[src] = 0
    pre = [0] * n  # pre[v]：最短路树上 v 的入边编号，只有从 t 回溯经过的点会被查询
    deg = indeg[:]
    queue = deque(v for v in range(n) if deg[v] == 0)
    while queue:
        x = queue.popleft()
        cx, dx = cnt[x], dist[x]  # 出队时 x 的所有入边都已松弛完，值不会再变
        for y, w, e in adj[x]:
            cnt[y] = (cnt[y] + cx) % MOD
            if dx + w < dist[y]:
                dist[y] = dx + w
                pre[y] = e
            deg[y] -= 1
            if deg[y] == 0:
                queue.append(y)
    return cnt, pre


def solve_case(it: Iterator[int]) -> int:
    """解一组数据：返回 S 到 T 的最小危险程度，无路径返回 -1。"""
    n, m, s, t, q = (next(it), next(it), next(it), next(it), next(it))

    edges = []  # edges[e] = (u, v, w)，边按输入顺序编号
    fwd = [[] for _ in range(n)]  # 正向邻接：(v, w, 边编号)
    radj = [[] for _ in range(n)]  # 反向邻接：(u, w, 边编号)
    indeg_f = [0] * n
    indeg_b = [0] * n
    for e in range(m):
        u, v, w = next(it), next(it), next(it)
        edges.append((u, v, w))
        fwd[u].append((v, w, e))
        radj[v].append((u, w, e))
        indeg_f[v] += 1
        indeg_b[u] += 1
    for lst in fwd:
        lst.reverse()  # std 用头插法建邻接表：遍历顺序 = 输入逆序，原样复刻

    cnt_s, pre = topsort(n, fwd, indeg_f, s)
    if cnt_s[t] == 0:
        return -1
    cnt_t, _ = topsort(n, radj, indeg_b, t)

    # 边 (u,v) 是必经边 ⟺ 前段条数 × 后段条数 = 总条数（同一条边不会先于自己被统计）
    on_bridge = [cnt_s[u] * cnt_t[v] % MOD == cnt_s[t] for u, v, _w in edges]

    path = []  # 最短路树上从 t 回溯到 s 的边，反转成行驶顺序
    x = t
    while x != s:
        e = pre[x]
        path.append(e)
        x = edges[e][0]
    path.reverse()
    if not path:
        return 1 << 30  # S = T 时无路段可步行，题目数据要求按 std 输出 2^30

    seg_w = [edges[e][2] for e in path]  # 依次经过的每段长度
    seg_br = [on_bridge[e] for e in path]  # 依次经过的每段是否必经边
    pref = [0, *accumulate(seg_w)]  # pref[i]：第 i 段末尾在路径上的位置
    danger = [0, *accumulate(w if b else 0 for w, b in zip(seg_w, seg_br))]  # 前 i 段全步行的危险度
    p = len(path)

    dps = [0] * (p + 1)  # dps[i]：前 i 段只用一次车的最小步行危险度
    j = 0
    for i in range(1, p + 1):
        while pref[i] - pref[j] > q:
            j += 1  # 乘车窗口 [pref[i]-q, pref[i]] 的左端压进第 j 段内部
        z = seg_w[i - 1] if seg_br[i - 1] else 0  # 方案一：第 i 段整段步行
        # 方案二：前 j 段步行、第 j+1~i 段乘车；窗口左端的残留 q-(pref[i]-pref[j]) 护住第 j 段尾部
        side = q - (pref[i] - pref[j]) if j > 0 and seg_br[j - 1] else 0
        dps[i] = min(dps[i - 1] + z, danger[j] - side)

    dpt = [0] * (p + 2)  # dpt[i]：第 i~p 段只用一次车的最小步行危险度，dpt[p+1]=0 作哨兵
    j = p
    for i in range(p, 0, -1):
        while pref[j] - pref[i - 1] > q:
            j -= 1  # 乘车窗口 [pref[i-1], pref[i-1]+q] 的右端压进第 j+1 段内部
        z = seg_w[i - 1] if seg_br[i - 1] else 0  # 方案一：第 i 段整段步行
        # 方案二：第 i~j 段乘车、第 j+1~p 段步行；窗口右端的残留护住第 j+1 段头部
        side = q - (pref[j] - pref[i - 1]) if j < p and seg_br[j] else 0
        dpt[i] = min(dpt[i + 1] + z, danger[p] - danger[j] - side)

    return min(dps[i - 1] + dpt[i] for i in range(1, p + 1))


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out = [str(solve_case(data)) for _ in range(next(data))]
    print('\n'.join(out))


if __name__ == "__main__":
    solve()

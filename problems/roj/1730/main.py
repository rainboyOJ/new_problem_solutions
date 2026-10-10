#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 19:03
# update_at: 2026-10-07 19:03

import sys
from collections import deque

INF = 10 ** 9  # 分层 BFS 里"不可达"的层号，比任何真实层号都大
UNMATCHED = -1  # 匹配数组里的"该点未匹配"，左、右部共用同一个哨兵

# 类型别名（Python 3.12+ 的 type 语句），相当于 C++ 的 using / typedef
type Adj = list[list[int]]  # 邻接表：顶点自己编号，表中存邻居编号
type Table = list[bytearray]  # 答案表：每行一个字节串，'0' 表示这条边可用


def max_matching(adj: Adj, n: int, m: int) -> tuple[list[int], list[int]]:
    """Hopcroft-Karp：返回 (左部匹配数组, 右部匹配数组) 表示的一个最大匹配。"""
    match_l = [UNMATCHED] * n
    match_r = [UNMATCHED] * m
    dist = [0] * n  # 分层 BFS 中左部点的层号，只对左部点有意义

    def build_layers() -> bool:
        """按未匹配的左部点重新分层，返回本轮是否还存在增广路。"""
        que = deque(u for u in range(n) if match_l[u] == UNMATCHED)
        for u in range(n):
            dist[u] = 0 if match_l[u] == UNMATCHED else INF
        found = False
        while que:
            u = que.popleft()
            for v in adj[u]:
                w = match_r[v]
                if w == UNMATCHED:
                    found = True  # 走到未匹配的右部点，就有增广路
                elif dist[w] == INF:
                    dist[w] = dist[u] + 1  # 沿匹配边继续往下分层
                    que.append(w)
        return found

    def augment(u: int) -> bool:
        """只在分层图上从 u 找一条增广路并翻转沿途匹配。"""
        for v in adj[u]:
            w = match_r[v]
            # v 未匹配（增广路到头），或 v 的匹配对象恰在下一层且它还能继续增广
            can_extend = w == UNMATCHED or (dist[w] == dist[u] + 1 and augment(w))
            if can_extend:
                match_l[u] = v
                match_r[v] = u
                return True
        dist[u] = INF  # 本轮 u 已确认增广失败，后面不再重复搜索
        return False

    while build_layers():
        for u in range(n):
            if match_l[u] == UNMATCHED:
                augment(u)
    return match_l, match_r


def scc_ids(adj: Adj, total: int) -> list[int]:
    """迭代版 Tarjan，返回每个顶点所属的强连通分量编号。"""
    dfn = [0] * total
    low = [0] * total
    comp = [0] * total
    on_stack = [False] * total
    nxt = [0] * total  # 每个顶点下一次要处理的出弧下标
    stack: list[int] = []  # Tarjan 维护的栈
    call: list[int] = []  # 手工模拟递归用的调用栈
    timer = 0
    count = 0
    for root in range(total):
        if dfn[root]:
            continue
        timer += 1
        dfn[root] = low[root] = timer
        stack.append(root)
        on_stack[root] = True
        call.append(root)
        while call:
            u = call[-1]
            if nxt[u] < len(adj[u]):
                v = adj[u][nxt[u]]
                nxt[u] += 1
                if dfn[v] == 0:
                    timer += 1
                    dfn[v] = low[v] = timer
                    stack.append(v)
                    on_stack[v] = True
                    call.append(v)
                elif on_stack[v]:  # 指向栈内已访问点，用 dfn 更新 low
                    low[u] = min(low[u], dfn[v])
            else:
                call.pop()
                if low[u] == dfn[u]:
                    while True:
                        w = stack.pop()
                        on_stack[w] = False
                        comp[w] = count
                        if w == u:
                            break
                    count += 1
                if call:  # 回溯到父亲，把儿子的 low 传上去
                    parent = call[-1]
                    low[parent] = min(low[parent], low[u])
    return comp


def saturated_edges(adj: Adj, match_l: list[int], match_r: list[int], n: int, m: int) -> Table:
    """已知存在大小为 n 的匹配时，逐条边判定它能否入选：可入选填 '0'，否则保持 '1'。"""
    ans = [bytearray(b'1' * m) for _ in range(n)]
    # 按匹配 M 定向的交错有向图 D：左部点编号 0..n-1，右部点编号 n..n+m-1
    total = n + m
    dag: Adj = [[] for _ in range(total)]
    for u in range(n):
        for v in adj[u]:
            if match_l[u] == v:
                dag[u].append(n + v)  # 匹配边：左 -> 右
            else:
                dag[n + v].append(u)  # 非匹配边：右 -> 左
    comp = scc_ids(dag, total)
    # 从所有未被 M 匹配的右部点出发，标出 D 上可达的顶点
    reachable = bytearray(total)
    que = deque()
    for v in range(m):
        if match_r[v] == UNMATCHED:
            reachable[n + v] = 1
            que.append(n + v)
    while que:
        x = que.popleft()
        for y in dag[x]:
            if not reachable[y]:
                reachable[y] = 1
                que.append(y)
    for u in range(n):
        row = ans[u]
        for v in adj[u]:
            in_cycle = comp[u] == comp[n + v]  # 条件 (a)：这条边落在一条交错环上
            via_free = reachable[n + v] == 1  # 条件 (b)：交错路前缀可翻转到这条边
            if match_l[u] == v or in_cycle or via_free:
                row[v] = 48  # 48 == ord('0')，属于某个大小为 n 的匹配
    return ans


def edge_table(adj: Adj, n: int, m: int) -> Table:
    """整题的答案表：无解（左部无法全匹配）时全填 '1'，否则交给逐边判定。"""
    match_l, match_r = max_matching(adj, n, m)
    has_full = all(x != UNMATCHED for x in match_l)  # 左部全被匹配才存在大小为 n 的匹配
    if not has_full:
        return [bytearray(b'1' * m) for _ in range(n)]
    return saturated_edges(adj, match_l, match_r, n, m)


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    n = int(next(data))
    m = int(next(data))  # 题面保证 n <= m，算法本身不需要这个条件
    rows = [next(data).decode() for _ in range(n)]
    adj = [[j for j, ch in enumerate(row) if ch == '1'] for row in rows]

    ans = edge_table(adj, n, m)
    sys.stdout.write('\n'.join(row.decode() for row in ans) + '\n')


if __name__ == "__main__":
    solve()

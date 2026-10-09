#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-09 08:30
# update_at: 2026-10-09 08:48

import sys
from collections.abc import Iterator

type AdjList = tuple[list[int], list[int], list[int]]  # 链式前向星三元组 (head, to_edge, nxt)


def partner(x: int) -> int:
    """代表 x 的同党伙伴：奇数 2i-1 配偶数 2i，偶数 2i 配奇数 2i-1。"""
    return x + 1 if x % 2 else x - 1


def build_graph(n: int, m: int, data: Iterator[int]) -> AdjList:
    """读入 m 个厌恶对并建 2-SAT 蕴含图，返回链式前向星的 (head, to_edge, nxt)。

    厌恶对 (u, v) 表示 u、v 不能同时入选；由于每党恰选 1 人，「不选 v」等价于
    「选 v 的同党伙伴 partner(v)」，于是有两条蕴含边 u -> partner(v)、v -> partner(u)。
    u == v 时边为 u -> partner(u)，正好表达「u 不能入选」，无需特判。
    """
    head = [0] * (2 * n + 1)     # head[u] 是 u 的第一条出边编号
    to_edge = [0] * (2 * m + 1)  # to_edge[e] 是第 e 条边的终点
    nxt = [0] * (2 * m + 1)      # nxt[e] 是同起点的下一条边编号
    edge_cnt = 0
    for _ in range(m):
        u, v = next(data), next(data)
        for start, end in ((u, partner(v)), (v, partner(u))):
            edge_cnt += 1
            to_edge[edge_cnt] = end
            nxt[edge_cnt] = head[start]
            head[start] = edge_cnt
    return head, to_edge, nxt


def tarjan_scc(size: int, head: list[int], to_edge: list[int],
               nxt: list[int]) -> list[int]:
    """迭代版 Tarjan 求强连通分量，返回每个结点（1..size-1）的 SCC 编号。

    编号按结点完成顺序递增，恰好是缩点 DAG 拓扑序的**逆序**。
    写成显式栈是因为数据里最长蕴含链达 16000 层（spo8/spo12 实测 15999），
    递归会爆栈，而 Python 默认递归上限只有 1000。
    """
    dfn = [0] * size        # Tarjan 时间戳，0 表示还没访问过
    low = [0] * size        # 所在 SCC 能回溯到的最小 dfn
    scc = [0] * size        # 结点所属的 SCC 编号
    in_st = [False] * size  # 结点当前是否还在 SCC 栈里
    edge_ptr = [0] * size   # 每个结点扫描到哪条出边（对应递归里的 for 游标）
    timer = scc_cnt = 0
    st: list[int] = []       # SCC 栈
    call_st: list[int] = []  # 手工调用栈，模拟递归的调用链

    for root in range(1, size):
        if dfn[root]:
            continue
        timer += 1
        dfn[root] = low[root] = timer
        st.append(root)
        in_st[root] = True
        edge_ptr[root] = head[root]
        call_st.append(root)

        while call_st:
            u = call_st[-1]
            e = edge_ptr[u]

            if e:  # 还有出边没扫完，继续深入
                edge_ptr[u] = nxt[e]
                v = to_edge[e]
                if not dfn[v]:
                    timer += 1
                    dfn[v] = low[v] = timer
                    st.append(v)
                    in_st[v] = True
                    edge_ptr[v] = head[v]
                    call_st.append(v)
                elif in_st[v] and dfn[v] < low[u]:
                    low[u] = dfn[v]  # 回边指向栈内结点，用它更新追溯值
            else:  # 出边扫完，回溯
                if low[u] == dfn[u]:
                    scc_cnt += 1
                    while True:
                        v = st.pop()
                        in_st[v] = False
                        scc[v] = scc_cnt
                        if v == u:
                            break
                call_st.pop()
                if call_st and low[u] < low[call_st[-1]]:
                    low[call_st[-1]] = low[u]

    return scc


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data, None)  # 缺输入保护：一个 token 都没有就直接返回
    if n is None:
        return
    m = next(data, 0)

    head, to_edge, nxt = build_graph(n, m, data)
    scc = tarjan_scc(2 * n + 1, head, to_edge, nxt)

    # 同党两名代表落在同一个 SCC ⇒ 选一个必然推出另一个，与「每党恰 1 人」矛盾。
    if any(scc[2 * i - 1] == scc[2 * i] for i in range(1, n + 1)):
        print("NIE")
        return

    # SCC 编号越小越靠近缩点 DAG 的汇点，选它不会推出矛盾；
    # 按党派递增输出，天然满足题面的升序要求。
    committee = [2 * i - 1 if scc[2 * i - 1] < scc[2 * i] else 2 * i
                 for i in range(1, n + 1)]
    if committee:
        print('\n'.join(map(str, committee)))


if __name__ == '__main__':
    solve()

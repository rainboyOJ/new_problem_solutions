"""P1262 [POI 1996 R3] 间谍网络

建模：间谍是点，A 掌握 B 的证据是从 A 到 B 的有向边，「控制」就是沿边可达。
买下某人后他的整条下游免费到手，所以真正要决策的只是「从哪些点进入」。
互相可达的一批人（强连通分量）里买最便宜的即可，缩点后得到 DAG；
DAG 中每个点都能上溯到某个入度为 0 的分量，那些分量无人能揭发、只能直接收买，
所以答案 = 每个入度为 0 的分量内最便宜的可收买价之和。

强连通分量用 rbook 的 Tarjan 模板（book/code/graph/scc.py）。
模板的 dfs 是显式栈写法：n 最大 3000，超过 Python 默认递归上限 1000，
直接递归会 RuntimeError，这里沿用模板的迭代实现，不加 setrecursionlimit。
"""

import sys
from collections import deque

INF = 10 ** 9  # 贿赂价上限 20000，INF 不会与任何真实价格相撞


class LinkList:
    """链式前向星，与 linklist.py 同结构：Tarjan 模板的 e.h / e[i].next 都由它提供。"""

    def __init__(self) -> None:
        self.edge_cnt = 0
        self.ev: list[int] = []  # 第 i 条边的终点
        self.enext: list[int] = []  # 第 i 条边的下一条出边编号
        self.h: list[int] = []  # h[u] = u 的第一条出边编号，-1 表示没有

    def reset(self, n: int) -> None:
        self.edge_cnt = 0
        self.ev = []
        self.enext = []
        self.h = [-1] * (n + 1)

    def add(self, u: int, v: int) -> None:
        self.ev.append(v)
        self.enext.append(self.h[u])
        self.h[u] = self.edge_cnt
        self.edge_cnt += 1


def tarjan(n: int, graph: LinkList) -> tuple[list[int], int]:
    """求强连通分量，返回 (scc_id, scc_cnt)；scc_id 从 1 开始。

    与 book/code/graph/scc.py 的迭代实现一致：栈帧记录 (节点, 下一条待处理的出边编号)，
    回溯时把子节点的 low 并回父节点，dfn == low 时弹出整个分量。
    """
    dfn = [0] * (n + 1)
    low = [0] * (n + 1)
    scc_id = [0] * (n + 1)
    in_stack = [False] * (n + 1)
    st: list[int] = []
    scc_cnt = 0
    timer = 0

    for start in range(1, n + 1):
        if dfn[start]:
            continue
        timer += 1
        dfn[start] = low[start] = timer
        st.append(start)
        in_stack[start] = True
        call: list[tuple[int, int]] = [(start, graph.h[start])]

        while call:
            u, i = call[-1]
            advanced = False
            while i != -1:
                v = graph.ev[i]
                i = graph.enext[i]
                if dfn[v] == 0:
                    call[-1] = (u, i)
                    timer += 1
                    dfn[v] = low[v] = timer
                    st.append(v)
                    in_stack[v] = True
                    call.append((v, graph.h[v]))
                    advanced = True
                    break
                if in_stack[v]:
                    # 返祖边：只能回到栈中的点，用 dfn[v] 更新 low[u]
                    low[u] = min(low[u], dfn[v])
            if advanced:
                continue

            call.pop()
            if low[u] == dfn[u]:
                scc_cnt += 1
                while True:
                    v = st.pop()
                    in_stack[v] = False
                    scc_id[v] = scc_cnt
                    if v == u:
                        break
            if call:
                # 递归返回后 low[父] = min(low[父], low[子])
                pu = call[-1][0]
                low[pu] = min(low[pu], low[u])

    return scc_id, scc_cnt


def solve(n: int, cost: list[int], graph: LinkList) -> tuple[str, int]:
    scc_id, scc_cnt = tarjan(n, graph)

    # 分量内最便宜的可收买价
    min_cost = [INF] * (scc_cnt + 1)
    for v in range(1, n + 1):
        c = scc_id[v]
        min_cost[c] = min(min_cost[c], cost[v])

    # 缩点后 DAG 的入度：环内的边不算，否则环上分量的入度都被自己凑成非 0
    indeg = [0] * (scc_cnt + 1)
    for u in range(1, n + 1):
        i = graph.h[u]
        while i != -1:
            v = graph.ev[i]
            if scc_id[u] != scc_id[v]:
                indeg[scc_id[v]] += 1
            i = graph.enext[i]

    # 买下所有可收买者能控制的范围：买得越多只会更广，全买就是最大可达集
    reach = [False] * (n + 1)
    q: deque[int] = deque()
    for v in range(1, n + 1):
        if cost[v] < INF:
            reach[v] = True
            q.append(v)
    while q:
        u = q.popleft()
        i = graph.h[u]
        while i != -1:
            v = graph.ev[i]
            if not reach[v]:
                reach[v] = True
                q.append(v)
            i = graph.enext[i]

    # 注意：要找「所有不可达点里编号最小的」，不是「坏分量里编号最小的」，
    # 因为坏分量的下游同样失控，而那些点的编号可能更小。
    for v in range(1, n + 1):
        if not reach[v]:
            return ("NO", v)

    total = 0
    for c in range(1, scc_cnt + 1):
        if indeg[c] == 0:
            total += min_cost[c]
    return ("YES", total)


def main() -> None:
    data = sys.stdin.buffer.read().split()
    pos = 0
    n = int(data[pos]); pos += 1
    p = int(data[pos]); pos += 1

    cost = [INF] * (n + 1)
    for _ in range(p):
        v = int(data[pos]); pos += 1
        c = int(data[pos]); pos += 1
        cost[v] = c

    graph = LinkList()
    graph.reset(n)
    r = int(data[pos]); pos += 1
    for _ in range(r):
        u = int(data[pos]); pos += 1
        v = int(data[pos]); pos += 1
        graph.add(u, v)

    verdict, value = solve(n, cost, graph)
    sys.stdout.write(f"{verdict}\n{value}\n")


if __name__ == "__main__":
    main()

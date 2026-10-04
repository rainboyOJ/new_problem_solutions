#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 15:44
# update_at: 2026-09-30 15:44

import sys

INF = 10**9  # 分量代价初值：尚未发现可收买成员


def scc(n: int, g: list[list[int]]) -> list[int]:
    """Tarjan 强连通分量（迭代版）：返回 comp[v]，同一分量内的点互相可达。"""
    num = [0] * (n + 1)        # DFS 编号，0 表示未访问
    low = [0] * (n + 1)        # 子树里的点能回到的最小编号
    on_st = [False] * (n + 1)  # 是否在栈上（仍是当前分量的候选）
    st: list[int] = []
    comp = [-1] * (n + 1)
    frame: list[tuple[int, int]] = []  # 显式栈：(点, 下一条待走的边)，替代递归
    seq = 0      # 全局 DFS 时钟
    comp_id = 0  # 已确定的分量编号

    for root in range(1, n + 1):
        if num[root]:
            continue
        seq += 1
        num[root] = low[root] = seq
        st.append(root)
        on_st[root] = True
        frame.append((root, 0))
        while frame:
            v, ei = frame[-1]
            if ei < len(g[v]):  # 还有边没走
                frame[-1] = (v, ei + 1)
                w = g[v][ei]
                if not num[w]:  # 树边：深入
                    seq += 1
                    num[w] = low[w] = seq
                    st.append(w)
                    on_st[w] = True
                    frame.append((w, 0))
                elif on_st[w]:  # 回边：v 能经 w 回到更早的点
                    low[v] = min(low[v], num[w])
            else:  # v 的边走完，弹栈定根
                frame.pop()
                if low[v] == num[v]:  # 没有出路指回外面 → 整个栈顶段是一个分量
                    while (w := st.pop()):  # 弹到 v 为止（点编号 ≥ 1，0 不会入栈）
                        on_st[w] = False
                        comp[w] = comp_id
                        if w == v:
                            break
                    comp_id += 1
    return comp


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)            # 间谍总数
    p = next(data)            # 可收买人数
    bribe = {next(data): next(data) for _ in range(p)}  # 编号 -> 收买金额
    r = next(data)            # 证据条数
    edges = [(next(data), next(data)) for _ in range(r)]  # (A, B)：A 掌握 B 的证据

    g: list[list[int]] = [[] for _ in range(n + 1)]
    for a, b in edges:
        g[a].append(b)        # 逮捕 A 即控制 B → 有向边 A -> B

    comp = scc(n, g)
    k = max(comp[1:]) + 1                # 强连通分量个数
    head = [n + 1] * k                   # 每个分量里最小的间谍编号
    for v in range(1, n + 1):
        cv = comp[v]
        head[cv] = min(head[cv], v)
    cost = [INF] * k                     # 分量内可收买成员的最低金额
    for spy, money in bribe.items():
        cv = comp[spy]
        cost[cv] = min(cost[cv], money)

    cond: list[list[int]] = [[] for _ in range(k)]  # 缩点后的 DAG
    indeg = [0] * k
    for a, b in edges:
        ca, cb = comp[a], comp[b]
        if ca != cb:
            cond[ca].append(cb)
            indeg[cb] += 1

    # 从每个可收买分量出发做可达性标记：能被控制的分量
    ctrl = [False] * k
    stack = [c for c in range(k) if cost[c] < INF]
    for c in stack:
        ctrl[c] = True
    while stack:
        c = stack.pop()
        for nb in cond[c]:
            if not ctrl[nb]:
                ctrl[nb] = True
                stack.append(nb)

    # 入度 0 的分量没有任何外界能到达，必须自己收买；买下它们即可覆盖全图
    source = [c for c in range(k) if indeg[c] == 0]
    lost = [c for c in range(k) if not ctrl[c]]  # 任何收买方案都控制不到的分量

    if lost:
        out = ['NO', str(min(head[c] for c in lost))]
    else:
        out = ['YES', str(sum(cost[c] for c in source))]
    print('\n'.join(out))


if __name__ == "__main__":
    solve()

#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 16:10
# update_at: 2026-09-30 16:10

import sys


def max_pieces(adj: list[list[int]]) -> tuple[int, int]:
    """迭代版 Tarjan：返回（原图连通块数，删去单点后其所在连通块最多裂成的块数）。"""
    n = len(adj)
    dfn = [-1] * n        # DFS 进入时刻，-1 表示未访问
    low = [0] * n         # 子树经回边能到达的最小 dfn
    split = [0] * n       # u 的孩子里 low[child] >= dfn[u] 的个数
    clock = 0
    comps = 0             # 原图连通块数
    best = 0              # 所有顶点中"删去后裂成的块数"的最大值
    dfs: list[list[int]] = []   # 栈帧：[顶点, 父顶点, 下一条待查邻边位置]，迭代代替递归

    for root in range(n):
        if dfn[root] >= 0:
            continue
        comps += 1
        dfn[root] = low[root] = clock
        clock += 1
        dfs.append([root, -1, 0])
        while dfs:
            u, par, i = dfs[-1]
            if i < len(adj[u]):
                dfs[-1][2] = i + 1
                v = adj[u][i]
                if dfn[v] < 0:                      # 树边：向下展开
                    dfn[v] = low[v] = clock
                    clock += 1
                    dfs.append([v, u, 0])
                elif v != par and dfn[v] < dfn[u]:  # 回边：对称两边只取编号小的一端
                    low[u] = min(low[u], dfn[v])
            else:                                   # u 的邻边走完：向父回传 low 并结算
                dfs.pop()
                if par >= 0:
                    low[par] = min(low[par], low[u])
                    if low[u] >= dfn[par]:          # u 的子树绕不开 par，par 是割点
                        split[par] += 1
                # 非根删点后 = 各闭合子树 + 父方向那一大块；根只有各子树
                best = max(best, split[u] + (par >= 0))
    return comps, best


def solve() -> None:
    # 逐行惰性切分：整份输入有 7+MB，一次性 read().split() 会把峰值内存推近 128MB 限制
    lines = (ln.split() for ln in sys.stdin.buffer if ln.strip())
    out: list[str] = []

    for first in lines:                    # 每组第一行 "P C"，以 0 0 结束
        p_cnt, edge_cnt = int(first[0]), int(first[1])
        if p_cnt == 0:
            break
        adj: list[list[int]] = [[] for _ in range(p_cnt)]
        for _ in range(edge_cnt):          # 保证无重边，直接双向建表
            a, b = map(int, next(lines))
            adj[a].append(b)
            adj[b].append(a)
        comps, best = max_pieces(adj)
        out.append(str(comps - 1 + best))  # 删点后总数 = 其余连通块 + 其所在块的裂块数

    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    solve()

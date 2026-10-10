#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 17:18
# update_at: 2026-10-07 17:18

import sys

NEG = -(1 << 62)  # 配对 DP 里的"不存在"哨兵，比任何合法权值都小


def build_tree(keys: list[int]) -> tuple[list[int], list[int], list[int]]:
    """按键序列建 Trie（退格 8 表示回父结点），返回 (父结点, 深度, 子树大小)。

    集合 S 恰好是这棵 Trie 的结点集：光标在串尾，走一步就是一个孩子，
    退格就是回父结点。字符键用 父结点*256 + ASCII 编码，同一个 (结点, 字符) 只会开一个点。
    """
    parent, depth, size = [-1], [0], [1]  # 结点 0 = 空串 = 根
    child: dict[int, int] = {}
    cur = 0
    for k in keys:
        if k == 8:
            cur = parent[cur] if cur else 0
        else:
            key = cur * 256 + k
            nxt = child.get(key, -1)
            if nxt < 0:  # 这个字符还没出现过，现场开点
                nxt = len(parent)
                child[key] = nxt
                parent.append(cur)
                depth.append(depth[cur] + 1)
                size.append(1)
            cur = nxt
    for v in range(len(parent) - 1, 0, -1):  # 结点编号即拓扑序，父结点编号一定更小
        size[parent[v]] += size[v]
    return parent, depth, size


def day_stat(parent: list[int], depth: list[int], size: list[int]) -> tuple[int, int, int, int, list[int]]:
    """算一天的统计量：返回 (结点数, 两两距离和 W, min D, max D, 每点到全集合的距离和 D)。"""
    n = len(parent)
    # 每条边 (parent[v], v) 被两侧点的每一对跨过：一侧 size[v] 个点，另一侧 n - size[v] 个
    W = sum(size[v] * (n - size[v]) for v in range(1, n))
    D = [sum(depth)] + [0] * (n - 1)  # 根（空串）到所有点的距离和 = 所有点的深度和
    for v in range(1, n):  # 换根：从父结点走进子树，子树内的点都近 1，其余点都远 1
        D[v] = D[parent[v]] + n - 2 * size[v]
    return n, W, min(D), max(D), D


def best_pair(parent: list[int], depth: list[int], D: list[int], coef_a: int, coef_c: int) -> int:
    """在 B 上求 max[nA*D[x] + nC*D[y] + L*d(x,y)]，L = nA*nC（第 3 天最大值的那一项）。

    用 d(x,y) = depth[x] + depth[y] - 2*depth(lca) 拆开，改成对每个结点 v 只统计
    "lca 恰好是 v"的配对：倒序扫编号，孩子子树先并入 v 的候选（孩子编号一定更大）。
    """
    n = len(parent)
    L = coef_a * coef_c
    F = [coef_a * D[v] + L * depth[v] for v in range(n)]  # x 取 v 时的权值
    G = [coef_c * D[v] + L * depth[v] for v in range(n)]  # y 取 v 时的权值
    cross = [F[v] + G[v] for v in range(n)]               # lca = v 的候选答案（先放 x = y = v）
    best0, best1 = F[:], G[:]                             # 子树内 max F / max G，初始含 v 自身
    ans = NEG
    for v in range(n - 1, -1, -1):
        ans = max(ans, cross[v] - 2 * L * depth[v])  # 扣掉 lca 以上多算的两段深度
        p = parent[v]
        if p >= 0:  # 把孩子子树并入父结点：父结点已并入的部分与 v 的子树一定不相交
            cross[p] = max(cross[p], best0[p] + best1[v], best1[p] + best0[v])
            best0[p] = max(best0[p], best0[v])
            best1[p] = max(best1[p], best1[v])
    return ans


def solve() -> None:
    # 一天恰好一行，空行表示该天只按过退格（集合只有空串），所以不能过滤空行；
    # 退格 8 与字符含义不同、必须按行分组，这也是这里按行读入而不是 next() 顺序消费的原因
    raw = sys.stdin.buffer.read().split(b'\n')
    days = [(raw[i] if i < len(raw) else b'') for i in range(3)]
    keys = [[int(x) for x in ln.split()] for ln in days]
    info = [day_stat(*build_tree(k)) for k in keys]
    (nA, WA, dAmin, dAmax, DA), (nB, WB, dBmin, dBmax, DB), (nC, WC, dCmin, dCmax, DC) = info
    parB, depB, _ = build_tree(keys[1])

    # 第 1 天：A 内部两两距离之和
    day1 = WA

    # 第 2 天：A×B 的对距离为 d(P,A0)+1+d(B0,Q)，展开后 A0 的系数是 nB，B0 的系数是 nA
    day2min = WA + WB + nA * nB + nB * dAmin + nA * dBmin
    day2max = WA + WB + nA * nB + nB * dAmax + nA * dBmax

    # 第 3 天：A×C 的对多走一趟 B0→B1，故 A0 系数 nB+nC、C0 系数 nA+nB，B0/B1 分别带 nA/nC
    base = WA + WB + WC + nA * nB + nB * nC + 2 * nA * nC
    day3min = base + (nB + nC) * dAmin + (nA + nB) * dCmin + (nA + nC) * dBmin
    day3max = base + (nB + nC) * dAmax + (nA + nB) * dCmax + best_pair(parB, depB, DB, nA, nC)

    print(f"{day1} {day1}")
    print(f"{day2min} {day2max}")
    print(f"{day3min} {day3max}")


if __name__ == "__main__":
    solve()

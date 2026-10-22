#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-21 09:10
# update_at: 2026-10-21 09:10
#
# main.py：CF1120D Power Tree，与 main.cpp 同一算法。
#
# 建模：叶子按 DFS 序编号 1..m，点 v 的子树叶子是一段连续区间 [lo_v, hi_v]。
#   「给 v 的子树叶子整体 +x」 等价于一维差分数组 d[0..m] 上的两次点修改：
#       d[lo_v - 1] += x ,  d[hi_v] -= x
#   于是每个点 v 对应新图 m+1 个点（编号 0..m）上的一条边 (lo_v-1, hi_v)，边权 c_v。
#   第一问 = 该图的最小生成树权值；第二问 = 属于某棵 MST 的边所对应的点。
# DFS 用显式栈（n 可达 2e5，Python 递归必爆），邻接表用 CSR 数组压内存。

import sys
from array import array


def main() -> None:
    tokens = sys.stdin.buffer.read().split()
    it = iter(tokens)
    n = int(next(it))

    # cost[v]：买下点 v 的花费。用 array('q') 存，避免 20 万个 int 对象
    cost = array("q", bytes(8 * (n + 1)))
    for v in range(1, n + 1):
        cost[v] = int(next(it))

    # ---------- CSR 邻接表：head/next 两条数组，比 list-of-list 省一半以上内存 ----------
    eu = array("i", bytes(4 * (n - 1)))
    ev = array("i", bytes(4 * (n - 1)))
    deg = array("i", bytes(4 * (n + 1)))
    for i in range(n - 1):
        a = int(next(it))
        b = int(next(it))
        eu[i] = a
        ev[i] = b
        deg[a] += 1
        deg[b] += 1
    del tokens, it  # 立刻释放 60 万个 bytes 对象，峰值内存能降一大截

    start = array("i", bytes(4 * (n + 2)))
    for v in range(1, n + 2):
        start[v] = start[v - 1] + deg[v - 1]
    pos = array("i", start)          # 每条边在 CSR 里的写入位置
    to = array("i", bytes(4 * 2 * (n - 1)))
    for i in range(n - 1):
        a, b = eu[i], ev[i]
        to[pos[a]] = b
        pos[a] += 1
        to[pos[b]] = a
        pos[b] += 1
    del eu, ev, deg, pos

    # ---------- 1. 显式栈求 DFS 前序，同时记录父亲 ----------
    # 弹栈时把儿子全部压栈：「最晚压入的最先展开」，所以得到的仍是合法 DFS 前序，
    # 每棵子树在其中连续，叶子也按 DFS 序出现。
    parent = array("i", bytes(4 * (n + 1)))
    visited = bytearray(n + 1)
    order = array("i")
    stack = [1]
    visited[1] = 1
    while stack:
        u = stack.pop()
        order.append(u)
        for k in range(start[u], start[u + 1]):
            v = to[k]
            if not visited[v]:
                visited[v] = 1
                parent[v] = u
                stack.append(v)
    del stack, visited, start, to

    # ---------- 2. 叶子按 DFS 序编号 1..m ----------
    # 叶子 = 非根、度数为 1 的点（题面定义）
    INF = n + 1
    lo = array("i", [INF]) * (n + 1)   # 子树内最小叶子编号
    hi = array("i", [-1]) * (n + 1)    # 子树内最大叶子编号
    # 用「谁有儿子」标记来判叶子：没有儿子且不是根 <=> 度数为 1 的非根点
    m = 0
    has_child = bytearray(n + 1)
    for u in order:
        p = parent[u]
        if p:
            has_child[p] = 1
    for u in order:
        if u != 1 and not has_child[u]:
            m += 1
            lo[u] = m
            hi[u] = m
    del has_child

    # 逆 DFS 序回溯，把儿子的区间并给父亲，O(n)
    for i in range(n - 1, -1, -1):
        u = order[i]
        p = parent[u]
        if p:
            if lo[u] < lo[p]:
                lo[p] = lo[u]
            if hi[u] > hi[p]:
                hi[p] = hi[u]

    # ---------- 3. 新图有 m+1 个点（0..m），点 v 对应边 (lo[v]-1, hi[v]) ----------
    # 按权值排序点编号即可代表按边权排序；Python 排序稳定，同权边自然聚在相邻位置。
    order_v = sorted(range(1, n + 1), key=cost.__getitem__)

    # ---------- 4. 按权值分组的 Kruskal，同时得出两问 ----------
    dsu = list(range(m + 1))
    size = [1] * (m + 1)

    def find(x: int) -> int:
        # 迭代路径压缩，避免递归深度问题
        root = x
        while dsu[root] != root:
            root = dsu[root]
        while dsu[x] != root:
            dsu[x], x = root, dsu[x]
        return root

    total = 0       # 第一问：MST 总权值
    answer = []     # 第二问：出现在某棵 MST 里的边对应的点

    i = 0
    while i < n:
        w = cost[order_v[i]]
        j = i
        while j < n and cost[order_v[j]] == w:
            j += 1

        # (a) 此时并查集恰好是「只用权值 < w 的边」的连通状态（基线）：
        #     两端在基线里不连通 <=> 这条边属于某棵 MST
        for k in range(i, j):
            v = order_v[k]
            if find(lo[v] - 1) != find(hi[v]):
                answer.append(v)
        # (b) 再统一合并整组，保证组内同权边不会影响彼此的判定
        for k in range(i, j):
            v = order_v[k]
            ru, rv = find(lo[v] - 1), find(hi[v])
            if ru != rv:
                if size[ru] < size[rv]:
                    ru, rv = rv, ru
                dsu[rv] = ru
                size[ru] += size[rv]
                total += w
        i = j

    answer.sort()
    out = ["%d %d" % (total, len(answer)), " ".join(map(str, answer))]
    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    main()

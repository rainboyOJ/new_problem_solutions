#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 15:55
# update_at: 2026-09-30 15:55

import sys
from array import array

NEG = -(1 << 60)  # 不可达哨兵；金额非负，用它区分"还没走到过"


def tarjan_scc(n: int, head: array, nxt: array, to: array) -> tuple[array, int]:
    """迭代式 Tarjan 求强连通分量，返回 (comp, 分量个数)。

    分量在"子树全部处理完"时才弹出并编号，所以后继分量一定先拿到小编号：
    对跨分量的边 u -> v 恒有 comp[u] > comp[v]。也就是说 comp 的降序就是拓扑序，
    DP 时从 ncomp-1 往 0 扫即可，无需再排序。
    用人工栈模拟递归，避免 50 万点把 Python 递归深度打爆。

    `cur` 是 head 的副本，函数会把它当"每个点下一条待处理边"的游标改掉，
    调用方的 head 保持原样，后面缩点 DP 还要用完整的邻接表。
    """
    cur = array('i', head)                      # 游标副本，避免破坏调用方的 head
    dfn = array('i', [-1]) * n                  # 访问时间戳，-1 表示还没访问
    low = array('i', [0]) * n                   # 子树经回边能触到的最小 dfn
    comp = array('i', [-1]) * n
    on = bytearray(n)                           # 是否还在 Tarjan 的 SCC 栈里
    scc: list[int] = []                         # 待判定的 SCC 栈
    work: list[int] = []                        # 人工递归栈：存待处理的节点
    timer = 0
    cnt = 0

    for root in range(n):
        if dfn[root] >= 0:
            continue
        dfn[root] = low[root] = timer
        timer += 1
        scc.append(root)
        on[root] = 1
        work.append(root)

        while work:
            v = work[-1]
            e = cur[v]                          # 取 v 下一条还没处理的出边

            if e == -1:                         # 出边处理完，可以收尾
                work.pop()
                if low[v] == dfn[v]:            # v 是所在 SCC 的根，弹出整个分量
                    while True:
                        u = scc.pop()
                        on[u] = 0
                        comp[u] = cnt
                        if u == v:
                            break
                    cnt += 1
                if work and low[v] < low[work[-1]]:
                    low[work[-1]] = low[v]      # 子树 low 回传给父亲
                continue

            cur[v] = nxt[e]                     # 这条边走过了，下次从下一条继续
            u = to[e]
            if dfn[u] < 0:                      # 树边：新节点入栈
                dfn[u] = low[u] = timer
                timer += 1
                scc.append(u)
                on[u] = 1
                work.append(u)
            elif on[u] and dfn[u] < low[v]:     # 回边/横叉边：只有仍在栈里的才更新 low
                low[v] = dfn[u]

    return comp, cnt


def solve() -> None:
    data = sys.stdin.buffer.read().split()
    n = int(data[0])
    m = int(data[1])

    # 链式前向星：head[v] 是 v 的第一条出边，nxt[e] 是同起点的下一条边。
    # 用 array('i') 而非 list：50 万点 50 万边下 list 的指针开销会顶到内存上限。
    head = array('i', [-1]) * n
    nxt = array('i', [0]) * m
    to = array('i', [0]) * m
    p = 2
    for e in range(m):
        a = int(data[p]) - 1
        b = int(data[p + 1]) - 1
        p += 2
        to[e] = b
        nxt[e] = head[a]
        head[a] = e

    money = array('i', [0]) * n                 # 题面的每台 ATM 金额，非负
    for v in range(n):
        money[v] = int(data[p])
        p += 1

    start = int(data[p]) - 1                    # 市中心 S
    bar_cnt = int(data[p + 1])                  # 酒吧数目 P
    p += 2
    bar = bytearray(n)
    for _ in range(bar_cnt):
        bar[int(data[p]) - 1] = 1
        p += 1

    comp, ncomp = tarjan_scc(n, head, nxt, to)

    # 缩点：分量内任意两点互达，走到一个点就能把整个分量的钱扫空，故按分量求和。
    pool = array('q', [0]) * ncomp
    has_bar = bytearray(ncomp)
    for v in range(n):
        c = comp[v]
        pool[c] += money[v]
        if bar[v]:
            has_bar[c] = 1

    # 把节点按分量分桶（计数排序），这样能按分量编号顺序遍历"分量内的点"。
    # comp 降序 = 拓扑序，一趟倒序扫描即可完成 DAG 上的最长路（松弛只向编号更小处走）。
    bucket_start = array('i', [0]) * (ncomp + 1)
    for v in range(n):
        bucket_start[comp[v] + 1] += 1
    for c in range(ncomp):
        bucket_start[c + 1] += bucket_start[c]
    fill = array('i', bucket_start[:ncomp])     # 每个桶当前的写入位置
    node_of = array('i', [0]) * n
    for v in range(n):
        c = comp[v]
        node_of[fill[c]] = v
        fill[c] += 1

    # dp[c] = 从 S 出发走到分量 c 时能抢到的最大金额（含 c 自己的钱）。
    dp = array('q', [NEG]) * ncomp
    dp[comp[start]] = pool[comp[start]]
    best = NEG
    for c in range(ncomp - 1, -1, -1):          # 分量编号降序 = 缩点 DAG 的拓扑序
        if dp[c] == NEG:                        # 这个分量从 S 根本走不到，跳过
            continue
        if has_bar[c] and dp[c] > best:         # 任意酒吧都能收尾，随时刷新答案
            best = dp[c]
        for i in range(bucket_start[c], bucket_start[c + 1]):
            e = head[node_of[i]]
            while e != -1:
                u = comp[to[e]]
                if u != c and dp[c] + pool[u] > dp[u]:   # 只沿跨分量的边松弛
                    dp[u] = dp[c] + pool[u]
                e = nxt[e]

    sys.stdout.write(str(best) + '\n')


if __name__ == "__main__":
    solve()

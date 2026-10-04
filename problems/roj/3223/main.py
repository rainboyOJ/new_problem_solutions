#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 03:05
# update_at: 2026-10-02 03:05

import sys


def scc_ids(size: int, graph: list[list[int]]) -> list[int]:
    """Tarjan 迭代版：返回每个点的强连通分量编号（编号本身无意义，只用来判「是否相等」）。"""
    order = [0] * size          # 0 = 还没访问过，其它值是访问时间戳
    low = [0] * size            # low[v]：v 的子树能回溯到的最早时间戳
    on_stack = bytearray(size)  # 是否仍在 Tarjan 栈里
    comp = [-1] * size
    stack: list[int] = []
    clock = 0                   # 时间戳计数器
    count = 0                   # 已收拢的分量数

    for root in range(size):
        if order[root]:
            continue
        work = [(root, 0)]      # (当前点, 下一条待检查的邻接边下标)，代替递归调用的显式栈
        while work:
            v, edge_at = work[-1]
            if not order[v]:    # 首次进入 v：打时间戳，压入 Tarjan 栈
                clock += 1
                order[v] = low[v] = clock
                stack.append(v)
                on_stack[v] = 1
            descended = False
            for i in range(edge_at, len(graph[v])):
                w = graph[v][i]
                if not order[w]:            # 树边：先深入 w，回来再继续扫
                    work[-1] = (v, i + 1)
                    work.append((w, 0))
                    descended = True
                    break
                if on_stack[w]:             # 回边/横叉边：用 w 的时间戳收缩 low
                    low[v] = min(low[v], order[w])
            if descended:
                continue
            if low[v] == order[v]:          # v 是所在分量的根，把整个分量弹出
                while True:
                    w = stack.pop()
                    on_stack[w] = 0
                    comp[w] = count
                    if w == v:
                        break
                count += 1
            work.pop()
            if work:                        # 回到父节点，孩子的 low 能向上传播
                low[work[-1][0]] = min(low[work[-1][0]], low[v])

    return comp


def solve() -> None:
    data = sys.stdin.buffer.read().split()
    pos = 0
    n = int(data[pos]); pos += 1

    liked: list[list[int]] = []
    for _ in range(n):
        k = int(data[pos]); pos += 1
        liked.append([int(x) - 1 for x in data[pos:pos + k]])  # 姑娘编号统一转成 0 起
        pos += k

    init_match = [int(x) - 1 for x in data[pos:pos + n]]  # 初步配对：第 i 个王子的对象
    taken_by = [0] * n                                    # 逆映射：该姑娘由哪个王子占着
    for boy, girl in enumerate(init_match):
        taken_by[girl] = boy

    # 建有向图：非匹配边 王子→姑娘，匹配边 姑娘→王子。
    # 这样图里的有向环恰好是「关于初配的交替环」：沿环翻转匹配关系，就得到另一个完美匹配。
    graph: list[list[int]] = [[] for _ in range(2 * n)]
    for boy, girls in enumerate(liked):
        graph[boy] = [n + g for g in girls if g != init_match[boy]]
    for girl, boy in enumerate(taken_by):
        graph[n + girl] = [boy]

    comp = scc_ids(2 * n, graph)

    out: list[str] = []
    for boy in range(n):
        # 非匹配边可行 ⟺ 两端同属一个 SCC（能绕成交替环）；
        # 匹配边本身就是初配，永远可行，无需任何条件。
        girls = sorted(g for g in liked[boy] if g == init_match[boy] or comp[boy] == comp[n + g])
        out.append(' '.join(map(str, [len(girls)] + [g + 1 for g in girls])))

    sys.stdout.write('\n'.join(out) + '\n')


if __name__ == "__main__":
    solve()

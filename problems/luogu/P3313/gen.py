#!/usr/bin/env python3
"""P3313 数据生成器（cyaron）：随机树 / 链 / 菊花 / 完全二叉树上的 CC、CW、QS、QM 混合操作。

用法：
    python3 gen.py                # 小数据随机树（n <= 30，q <= 100），给 brute.cpp 对拍
    python3 gen.py chain          # 小数据链
    python3 gen.py star           # 小数据菊花
    python3 gen.py big            # 全规模随机树，n = q = 10^5
    python3 gen.py big-chain      # 全规模链
    python3 gen.py big-balanced   # 全规模完全二叉树（HLD 拆段最多的形状）
    python3 gen.py big-cc         # 全规模、全是 CC（压动态节点池）
    python3 gen.py big-query      # 全规模、全是 QS / QM（压查询时间）

全规模时可用环境变量 P3313_N / P3313_Q / P3313_C 覆盖城市数、事件数与宗教数。
题面保证每个 QS / QM 的两端宗教相同，生成器按当前宗教维护城市集合来满足它。
"""
import os
import sys

from cyaron import IO, Graph, randint

BIG = 100000


def build_edges(kind, n):
    """按形状返回 n 个点的树边；随机形状用 cyaron 的 Graph.tree。"""
    if kind == "chain":
        graph = Graph.chain(n)
    elif kind == "star":
        graph = Graph.flower(n)
    elif kind == "balanced":
        graph = Graph.binary_tree(n)
    else:
        graph = Graph.tree(n, chain=0.3, flower=0.2)
    return [(edge.start, edge.end) for edge in graph.iterate_edges()]


def main():
    mode = sys.argv[1] if len(sys.argv) > 1 else str(randint(0, 2))
    name = ["random", "chain", "star"][int(mode)] if mode.isdigit() else mode
    big = name.startswith("big")

    if big:
        n = int(os.environ.get("P3313_N", BIG))
        q = int(os.environ.get("P3313_Q", BIG))
        color_limit = int(os.environ.get("P3313_C", BIG))
        kind = name[4:] or "random"
        if kind in ("cc", "query"):
            kind = "random"
    else:
        n = randint(1, 30)
        q = randint(1, 100)
        color_limit = min(10, n)
        kind = name

    io = IO(input_file=sys.stdout, disable_output=True)

    # 大数据留一半城市挤在少数宗教里，让每棵宗教树既有大的也有小的。
    color = []
    weight = []
    for i in range(1, n + 1):
        if big and i % 2 == 0:
            color.append(randint(1, 5))
        else:
            color.append(randint(1, color_limit))
        weight.append(randint(1, 10000))
    color.insert(0, 0)   # 下标从 1 开始，与题目编号对应
    weight.insert(0, 0)

    io.input_writeln(n, q)
    for i in range(1, n + 1):
        io.input_writeln(weight[i], color[i])
    for u, v in build_edges(kind, n):
        io.input_writeln(u, v)

    # members[c] 存当前宗教为 c 的城市，at[x] 记 x 在 members[color[x]] 里的位置，
    # 这样改宗教时用「与末尾交换再弹出」做到 O(1) 维护，查询就能直接取同宗教的另一个城市。
    members = [[] for _ in range(color_limit + 1)]
    at = [0] * (n + 1)
    for x in range(1, n + 1):
        members[color[x]].append(x)
        at[x] = len(members[color[x]]) - 1

    def same_color_city(x):
        pool = members[color[x]]
        return pool[randint(0, len(pool) - 1)]

    for _ in range(q):
        if big:
            if name == "big-cc":
                op = "CC"
            elif name == "big-query":
                op = "QS" if randint(0, 1) == 0 else "QM"
            else:
                roll = randint(1, 100)
                if roll <= 20:
                    op = "CC"
                elif roll <= 40:
                    op = "CW"
                else:
                    op = "QS" if randint(0, 1) == 0 else "QM"
        else:
            roll = randint(1, 4)
            op = ("CC", "CW", "QS", "QM")[roll - 1]

        x = randint(1, n)
        if op == "CC":
            old = color[x]
            new = randint(1, color_limit)
            pool = members[old]
            last = pool[-1]
            pool[at[x]] = last
            at[last] = at[x]
            pool.pop()
            color[x] = new
            members[new].append(x)
            at[x] = len(members[new]) - 1
            io.input_writeln("CC", x, new)
        elif op == "CW":
            weight[x] = randint(1, 10000)
            io.input_writeln("CW", x, weight[x])
        else:
            io.input_writeln(op, x, same_color_city(x))


if __name__ == "__main__":
    main()

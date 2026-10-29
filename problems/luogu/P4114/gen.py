#!/usr/bin/env python3
"""
P4114 Qtree1 数据生成器
使用 cyaron 生成随机树 + 边权 + 操作序列
"""
import sys
from cyaron import IO, Graph, randint

def main():
    if len(sys.argv) > 1:
        # 固定 seed 用于复现
        import random
        random.seed(int(sys.argv[1]))

    # n 范围：小规模便于对拍
    n = randint(2, 200)
    io = IO(input_file=sys.stdout, disable_output=True)

    io.input_writeln(n)

    # 生成随机树（chain + flower 混合）
    tree = Graph.tree(n, chain=0.3, flower=0.2)
    edges = []
    for e in tree.iterate_edges():
        w = randint(1, 100000)
        edges.append((e.start, e.end, w))
        io.input_writeln(e.start, e.end, w)

    # 操作数
    q = randint(1, 500)
    for _ in range(q):
        if randint(0, 3) == 0:
            # CHANGE
            x = randint(1, n-1)  # 边编号 1..n-1
            t = randint(1, 100000)
            io.input_writeln("CHANGE", x, t)
        else:
            # QUERY
            a = randint(1, n)
            b = randint(1, n)
            io.input_writeln("QUERY", a, b)

    io.input_writeln("DONE")


if __name__ == "__main__":
    main()

#!/usr/bin/env python3
"""生成 P4408 的小数据：随机树 + 随机边权（含 0），规模适合三点枚举暴力。

无参数运行，数据直接写 stdout，供 duipai.py --gen 调用。形状与规模用环境变量控制，
方便在不改脚本的前提下覆盖链、星、退化等多种结构：

    P4408_SHAPE=random|chain|star|broom   树的形状（默认 random）
    P4408_MAXN=<int>                      节点数上限（默认 9，暴力可承受）
    P4408_ZERO=1                          所有边权取 0，覆盖 0 权退化

手动运行示例：

    P4408_SHAPE=star P4408_MAXN=8 python3 gen.py
"""

import os
import sys

from cyaron import Graph, IO, randint


def build_tree(n, shape):
    """按形状返回 cyaron 的树对象。"""
    if shape == "chain":
        return Graph.chain(n)
    if shape == "star":
        # cyaron 0.7.0 没有 Graph.star，用 father_gen 把父节点固定成 1 造星形
        return Graph.tree(n, father_gen=lambda cur: 1)
    if shape == "broom":
        # 主干较长并挂若干叶子，制造多个偏心分支
        return Graph.tree(n, chain=0.6, flower=0.4)
    return Graph.tree(n, chain=0.3, flower=0.2)


def main():
    shape = os.environ.get("P4408_SHAPE", "random")
    if shape not in ("random", "chain", "star", "broom"):
        raise SystemExit(f"unknown P4408_SHAPE: {shape}")
    max_n = int(os.environ.get("P4408_MAXN", "9"))
    all_zero = os.environ.get("P4408_ZERO") == "1"

    io = IO(input_file=sys.stdout, disable_output=True)

    n = randint(3, max_n)
    io.input_writeln(n, n - 1)

    tree = build_tree(n, shape)
    for edge in tree.iterate_edges():
        if all_zero:
            weight = 0
        else:
            # 保留一定概率的 0 权边，覆盖"未访问标记不能用 0"这个坑
            weight = 0 if randint(1, 5) == 1 else randint(0, 10)
        io.input_writeln(edge.start, edge.end, weight)


if __name__ == "__main__":
    main()

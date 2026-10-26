#!/usr/bin/env python3
"""生成 P5588 对拍数据：小规模随机树 + 随机颜色。

覆盖的结构与颜色分布:
  - 形状: 随机树 / 链 / 菊花 / 完全二叉树(caterpillar 也偶尔出现)
  - 同色点个数: 很少(1~3) / 中等 / 全同色, 覆盖"不共线判 0"与"共线相乘"两类

用法:
  python3 gen.py            # 随机一组
  python3 gen.py 2000       # 指定 n (上限受暴力 brute.cpp 限制, 一般 <= 3000)
调用方可传 sys.argv[1] 指定 n; 默认随机取小规模, 便于和暴力对拍。
"""
import sys
import random

try:
    from cyaron import IO, Graph, randint
except ImportError:  # cyaron 不可用时退化为标准库, 保证脚本总能跑
    IO = None


def build_edges(n, shape):
    """按形状返回 n-1 条边。"""
    edges = []
    if shape == "chain":
        for i in range(2, n + 1):
            edges.append((i, i - 1))
    elif shape == "star":
        for i in range(2, n + 1):
            edges.append((i, 1))
    elif shape == "binary":
        for i in range(2, n + 1):
            edges.append((i, i // 2))
    elif shape == "caterpillar":
        # 一半节点做脊柱, 其余挂到脊柱上, 深度与分支都不极端
        spine = max(2, n // 2)
        for i in range(2, spine + 1):
            edges.append((i, i - 1))
        for i in range(spine + 1, n + 1):
            edges.append((i, random.randint(1, spine)))
    else:  # random: 每个点挂到前面某个点上
        for i in range(2, n + 1):
            edges.append((i, random.randint(1, i - 1)))
    random.shuffle(edges)
    result = []
    for u, v in edges:
        if random.random() < 0.5:
            u, v = v, u
        result.append((u, v))
    return result


def main():
    if len(sys.argv) > 1:
        n = int(sys.argv[1])
    else:
        n = randint(1, 30) if IO else random.randint(1, 30)

    shape = random.choice(["random", "random", "chain", "star", "binary", "caterpillar"])
    mode = random.choice(["few", "some", "all"])

    # 颜色值必须满足 1 <= w_i <= n, 所以上界取 min(..., n)。
    if mode == "few":
        color_kind = random.randint(1, min(3, n))
    elif mode == "all":
        color_kind = 1
    else:
        color_kind = n
    color_kind = max(1, min(color_kind, n))
    colors = [random.randint(1, color_kind) for _ in range(n)]

    edges = build_edges(n, shape)

    if IO is not None:
        io = IO(input_file=sys.stdout, disable_output=True)
        io.input_writeln(n)
        io.input_writeln(colors)
        for u, v in edges:
            io.input_writeln(u, v)
    else:
        print(n)
        print(*colors)
        for u, v in edges:
            print(u, v)


if __name__ == "__main__":
    main()

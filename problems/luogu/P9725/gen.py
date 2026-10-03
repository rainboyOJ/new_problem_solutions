#!/usr/bin/env python3
"""P9725 随机数据生成器：随机树。

设计要点：
  * 固定随机种子，保证可复现；
  * 覆盖小规模（暴力可枚举）、边界（n=2、n=3、菊花图 -> 答案 -1）和
    “一个点挂着大量同父叶子”（考验 max(ceil(L/2), 最大叶子组) 里后者）等结构；
  * 菊花图只在小 n 时生成，否则暴力要枚举全部加边方案，跑不动。
"""
import random
import sys


def random_tree(n, shape):
    """生成一棵 n 个点的树，返回边列表（1-indexed）。"""
    edges = []
    if shape == "path":
        for v in range(2, n + 1):
            edges.append((v - 1, v))
    elif shape == "star":
        for v in range(2, n + 1):
            edges.append((1, v))
    elif shape == "binary":
        for v in range(2, n + 1):
            edges.append((v // 2, v))
    elif shape == "broom":
        # 一条链，末端的点再挂一串叶子
        half = max(1, n // 2)
        for v in range(2, half + 1):
            edges.append((v - 1, v))
        for v in range(half + 1, n + 1):
            edges.append((half, v))
    elif shape == "twin":
        # 短主干 + 某个主干点外挂大量同父叶子
        trunk = max(2, min(n - 1, random.randint(1, max(1, n // 3))))
        for v in range(2, trunk + 1):
            edges.append((v - 1, v))
        center = random.randint(1, trunk)
        for v in range(trunk + 1, n + 1):
            edges.append((center, v))
    else:
        for v in range(2, n + 1):
            edges.append((random.randint(1, v - 1), v))
    return edges


def relabel(edges, n):
    """随机重编号，避免答案依赖点的编号顺序。"""
    perm = list(range(1, n + 1))
    random.shuffle(perm)
    return [(perm[u - 1], perm[v - 1]) for u, v in edges]


def main():
    # 默认种子固定，保证复现；传入 argv[1] 可以换一批数据用于多轮对拍。
    seed = int(sys.argv[1]) if len(sys.argv) > 1 else 20221002
    random.seed(seed)
    tests = []

    # ---- 极小规模：含 n=2、n=3、菊花图（无解边界）----
    tests.append((2, random_tree(2, "random")))
    tests.append((3, random_tree(3, "random")))
    tests.append((4, random_tree(4, "star")))
    tests.append((5, random_tree(5, "star")))
    tests.append((6, random_tree(6, "star")))
    tests.append((4, random_tree(4, "path")))
    tests.append((5, random_tree(5, "random")))
    tests.append((6, random_tree(6, "twin")))

    # ---- 小规模随机：各种结构混合 ----
    shapes = ["random", "random", "path", "binary", "broom", "twin"]
    for _ in range(4):
        n = random.randint(5, 6)
        tests.append((n, random_tree(n, random.choice(shapes))))

    # ---- 稍大规模：不生成菊花图，否则暴力枚举量爆炸 ----
    for _ in range(4):
        n = random.randint(7, 9)
        tests.append((n, random_tree(n, random.choice(shapes))))

    out = [str(len(tests))]
    for n, edges in tests:
        edges = relabel(edges, n)
        out.append(str(n))
        for u, v in edges:
            out.append(f"{u} {v}")
    print("\n".join(out))


if __name__ == "__main__":
    main()

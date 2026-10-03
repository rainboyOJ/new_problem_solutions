#!/usr/bin/env python3
# gen.py：为 P9233 颜色平衡树生成随机数据，输出到 stdout。
# 用法：
#   python3 gen.py <seed>     # 固定种子，同一 seed 一定生成同一份数据（可复现）
#   python3 gen.py            # 不传 seed 时随机取种子，并把 seed 打到 stderr，便于回放
# 覆盖情形：n = 1 的边界、链、随机树、菊花形（1 号点是唯一父亲），
# 以及“颜色数很少”这种容易命中颜色平衡子树的数据。
import os
import random
import sys


def build_random_tree(rng, n):
    """每个点 i 从 1..i-1 中选父亲，保证 F_i < i。"""
    fa = [0] * (n + 1)
    for i in range(2, n + 1):
        fa[i] = rng.randint(1, i - 1)
    return fa


def build_chain(rng, n):
    fa = [0] * (n + 1)
    for i in range(2, n + 1):
        fa[i] = i - 1
    return fa


def build_star(rng, n):
    fa = [0] * (n + 1)
    for i in range(2, n + 1):
        fa[i] = 1
    return fa


def build_shallow(rng, n):
    """父亲尽量小，得到又矮又宽的树，重儿子/轻儿子分布更极端。"""
    fa = [0] * (n + 1)
    for i in range(2, n + 1):
        fa[i] = rng.randint(max(1, i - 3), i - 1)
    return fa


def one_case(rng):
    shape = rng.randint(0, 3)
    if shape == 0:
        n = 1
    elif shape == 1:
        n = rng.randint(2, 12)          # 小数据，便于暴露细节错误
    elif shape == 2:
        n = rng.randint(13, 200)        # 中等数据
    else:
        n = rng.randint(201, 1500)      # 较大数据，验证 O(n^2) 暴力与 O(n log n) 正解一致

    if shape == 0:
        fa = [0, 0]
    elif shape == 1 and rng.randint(0, 3) == 0:
        fa = build_chain(rng, n)
    elif shape == 1 and rng.randint(0, 3) == 0:
        fa = build_star(rng, n)
    elif rng.randint(0, 4) == 0:
        fa = build_shallow(rng, n)
    else:
        fa = build_random_tree(rng, n)

    # 颜色范围：多数情况下很小，这样才容易构造出颜色平衡的子树。
    if rng.randint(0, 4) == 0:
        color_max = rng.randint(1, 4)                  # 只有 1~4 种颜色
    elif rng.randint(0, 3) == 0:
        color_max = rng.randint(1, n)                  # 颜色数和结点数同阶
    else:
        color_max = min(n, rng.randint(1, max(1, n // 2) + 1))

    out = [str(n)]
    for i in range(1, n + 1):
        out.append("%d %d" % (rng.randint(1, color_max), fa[i]))
    return "\n".join(out)


def main():
    if len(sys.argv) > 1:
        seed = int(sys.argv[1])
    elif "DUPAI_SEED" in os.environ:
        seed = int(os.environ["DUPAI_SEED"])
    else:
        seed = random.randrange(1, 10 ** 9)
    sys.stderr.write("# seed=%d\n" % seed)  # 记录种子，任何一份数据都能用 python3 gen.py <seed> 复现
    rng = random.Random(seed)
    sys.stdout.write(one_case(rng) + "\n")


if __name__ == "__main__":
    main()

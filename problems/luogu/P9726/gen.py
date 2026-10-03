#!/usr/bin/env python3
"""P9726 [EC Final 2022] Magic 的随机数据生成器。

用法：
    python3 gen.py [seed]

输出到 stdout，第一行 n，接下来 n 行每行 l_i r_i。

可复现：seed 省略时用固定默认值 DEFAULT_SEED，同一 seed 一定生成同一份数据；
对拍时可以用 `python3 gen.py $i` 逐个换 seed。

数据规模：gen.py 主要服务于对拍，所以 n 控制在 9 以内（brute.cpp 要枚举 n! 种
执行顺序，n=9 已是上限）。为了让各种结构都被覆盖，生成器会随机挑选下面这些形状：

    random   随机配对所有 2n 个端点（最一般的情况）
    dense    所有区间两两“交错”，二分图是稠密图
    nested   区间层层包含，二分图没有边
    adjacent (1,2),(3,4),... 端点两两相邻
    shift    l_i = i+1，r_i 取随机值，形成交错链
    half     一半宽区间包住一半窄区间

为了保证合法，所有画法最后都会检查：2n 个端点互不相同、l_i < r_i 且都在 [1, 2n] 内。
"""
import os
import random
import sys

DEFAULT_SEED = 20221002
MAXN = 9  # brute.cpp 枚举 n! 的上限


def pairing_random(rng, n):
    """把 1..2n 随机配对成 n 个区间。"""
    pos = list(range(1, 2 * n + 1))
    rng.shuffle(pos)
    ivs = []
    for i in range(n):
        a, b = pos[2 * i], pos[2 * i + 1]
        if a > b:
            a, b = b, a
        ivs.append((a, b))
    return ivs


def pairing_dense(rng, n):
    """l_i = i+1, r_i = n+i+1：任意两区间都满足 l_i<l_j<r_i<r_j，二分图为完全二分图。"""
    return [(i + 1, n + i + 1) for i in range(n)]


def pairing_nested(rng, n):
    """区间一个套一个，两两不交错，二分图没有边。"""
    return [(i + 1, 2 * n - i) for i in range(n)]


def pairing_adjacent(rng, n):
    """端点两两相邻：(1,2),(3,4),..."""
    return [(2 * i + 1, 2 * i + 2) for i in range(n)]


def pairing_shift(rng, n):
    """l_i = i+1，r_i 随机取一个更大的值；靠重试保证端点互不相同。"""
    for _ in range(200):
        rset = rng.sample(range(n + 1, 2 * n + 1), n)
        ivs = [(i + 1, rset[i]) for i in range(n)]
        ends = [x for iv in ivs for x in iv]
        if len(set(ends)) == 2 * n:
            return ivs
    return pairing_random(rng, n)


def pairing_half(rng, n):
    """前一半是宽区间，后一半是随机配对；用来混合稠密与稀疏两种结构。"""
    half = n // 2
    if half == 0:
        return pairing_random(rng, n)
    # 宽区间共用点会冲突，这里用前 2*half 个端点做随机配对，其余做稠密
    rest = pairing_random(rng, n - half)
    shift = 2 * half
    ivs = [(l + shift, r + shift) for l, r in rest]
    ivs = pairing_dense(rng, half) + ivs
    return ivs


GENERATORS = [
    pairing_random,
    pairing_dense,
    pairing_nested,
    pairing_adjacent,
    pairing_shift,
    pairing_half,
]


def valid(n, ivs):
    """检查这一组数据是否满足题面约束。"""
    if len(ivs) != n:
        return False
    ends = []
    for l, r in ivs:
        if not (1 <= l < r <= 2 * n):
            return False
        ends.append(l)
        ends.append(r)
    return len(set(ends)) == 2 * n


def make_case(rng):
    """随机挑一个形状和一个规模，直到产出一组合法数据。"""
    for _ in range(300):
        shape = rng.choice(GENERATORS)
        n = rng.randint(1, MAXN)
        ivs = shape(rng, n)
        if valid(n, ivs):
            # 打乱区间编号：保证答案不依赖输入顺序
            perm = list(range(n))
            rng.shuffle(perm)
            ivs = [ivs[p] for p in perm]
            return n, ivs
    # 兜底：一定合法的随机配对
    n = rng.randint(1, MAXN)
    return n, pairing_random(rng, n)


def main():
    if len(sys.argv) > 1:
        seed = int(sys.argv[1])
    elif "DUPAI_SEED" in os.environ:
        seed = int(os.environ["DUPAI_SEED"])
    else:
        seed = DEFAULT_SEED
    rng = random.Random(seed)

    n, ivs = make_case(rng)
    assert valid(n, ivs), "生成器必须输出合法数据"

    out = [str(n)]
    for l, r in ivs:
        out.append(f"{l} {r}")
    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    main()

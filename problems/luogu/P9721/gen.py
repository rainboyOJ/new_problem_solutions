#!/usr/bin/env python3
"""P9721 [EC Final 2022] Inversion 的随机数据生成器。

这是一道交互题：评测时程序只会读到 n，真正的排列 p 是隐藏的。
为了能在本地对拍，gen.py 输出的是「本地约定」的数据：

    第一行: n
    第二行: p_1 p_2 ... p_n   （即隐藏的排列本身，本地用它来扮演交互器）

brute.cpp / main.cpp 都按这个约定读取。真实提交时
main.cpp 检测到 stdin 是普通文件才进入这种本地模式。

可复现：传第一个命令行参数 <seed>，或设置环境变量 DUPAI_SEED=<整数>，
同一 seed 一定生成同一份数据；两者都不给时随手取一个种子并把 seed 打到
stderr，便于回放（这也能让 verify.sh 的 8 次调用拿到不同的数据）。

覆盖的情形：
  0. n = 1 的最小边界、n = 2 的两个排列
  1. 极小规模（n <= 10），方便肉眼核对
  2. 小规模（n <= 60），随机排列
  3. 中等规模（n <= 400），随机排列
  4. 大规模（n 接近 2000）——直接把二分插入的询问次数顶到 40000 上限附近
  5. 结构化排列：递增、递减、几乎有序、锯齿，专打二分的边界分支
"""
import os
import random
import sys

MAXN = 2000  # 题面给出的 n 上界


def perm_random(rng, n):
    """随机排列。"""
    p = list(range(1, n + 1))
    rng.shuffle(p)
    return p


def perm_increasing(n):
    """递增：每次插入都在最右端，二分始终往右走。"""
    return list(range(1, n + 1))


def perm_decreasing(n):
    """递减：每次插入都在最左端，二分始终往左走。"""
    return list(range(n, 0, -1))


def perm_almost_sorted(rng, n):
    """几乎有序：在递增的基础上做少量随机交换，二分路径接近最坏。"""
    p = list(range(1, n + 1))
    swaps = max(1, n // 30)
    for _ in range(swaps):
        i = rng.randrange(n)
        j = rng.randrange(n)
        p[i], p[j] = p[j], p[i]
    return p


def perm_zigzag(n):
    """锯齿：小值和大值交替出现，插入点来回跳。"""
    p = []
    lo, hi = 1, n
    while lo <= hi:
        p.append(lo)
        lo += 1
        if lo <= hi:
            p.append(hi)
            hi -= 1
    return p


def case_tiny(rng):
    """极小规模，含 n=1 和 n=2 这两个必须单独确认的边界。"""
    n = rng.randint(1, 10)
    if n == 1:
        return 1, [1]
    if n == 2 and rng.random() < 0.5:
        return 2, [2, 1]
    kind = rng.random()
    if kind < 0.3:
        return n, perm_increasing(n)
    if kind < 0.6:
        return n, perm_decreasing(n)
    return n, perm_random(rng, n)


def case_small(rng):
    n = rng.randint(2, 60)
    kind = rng.random()
    if kind < 0.2:
        return n, perm_increasing(n)
    if kind < 0.4:
        return n, perm_decreasing(n)
    if kind < 0.6:
        return n, perm_zigzag(n)
    return n, perm_random(rng, n)


def case_medium(rng):
    n = rng.randint(61, 400)
    kind = rng.random()
    if kind < 0.2:
        return n, perm_almost_sorted(rng, n)
    if kind < 0.4:
        return n, perm_zigzag(n)
    return n, perm_random(rng, n)


def case_large(rng):
    """n 接近上界：检验询问次数严格不超过 4*10^4，同时压测 O(n^2) 的维护量。"""
    n = rng.randint(MAXN - 200, MAXN)
    kind = rng.random()
    if kind < 0.25:
        return n, perm_increasing(n)
    if kind < 0.5:
        return n, perm_decreasing(n)
    if kind < 0.7:
        return n, perm_almost_sorted(rng, n)
    return n, perm_random(rng, n)


def case_extreme(rng):
    """固定把 n 顶到 2000，配合最坏排列，专门验算询问次数上限。"""
    n = MAXN
    kind = rng.random()
    if kind < 0.4:
        return n, perm_decreasing(n)
    if kind < 0.8:
        return n, perm_increasing(n)
    return n, perm_almost_sorted(rng, n)


CASES = [
    (case_tiny, 0.18),
    (case_small, 0.30),
    (case_medium, 0.24),
    (case_large, 0.18),
    (case_extreme, 0.10),
]


def main():
    if len(sys.argv) > 1:
        seed = int(sys.argv[1])
    elif "DUPAI_SEED" in os.environ:
        seed = int(os.environ["DUPAI_SEED"])
    else:
        seed = random.randrange(1, 10 ** 9)
        sys.stderr.write("# seed=%d\n" % seed)  # 记录种子，任何一份数据都能用 python3 gen.py <seed> 复现

    rng = random.Random(seed)

    pick = rng.random()
    acc = 0.0
    chosen = CASES[-1][0]
    for func, weight in CASES:
        acc += weight
        if pick < acc:
            chosen = func
            break

    n, p = chosen(rng)
    assert len(p) == n and sorted(p) == list(range(1, n + 1)), "生成器必须输出合法排列"

    out = [str(n), " ".join(str(x) for x in p)]
    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    main()

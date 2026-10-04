#!/usr/bin/env python3
"""P9716 [EC Final 2022] Coloring 的随机数据生成器。

输出格式（与题面一致）：
    第一行 n s
    第二行 n 个 w_i
    第三行 n 个 p_i
    第四行 n 个 a_i  （1 <= a_i <= n, a_i != i）

约束：n <= 5000，|w_i| <= 1e9，0 <= p_i <= 1e9。
因为要对拍 brute.cpp（状态压缩 Dijkstra，共 2^n 个状态），
所以这里把 n 限制在 12 以内，同时尽量覆盖各种结构：

  - 纯环（环长 2 / 3 / 更长）
  - 基环树（环 + 挂上去的子树，子树深度 >= 2）
  - s 在环上 / s 不在环上，两种分支都要出现
  - 功能图（多个连通块，有的块与 s 完全无关）
  - 极端权值：w_i 取 +-1e9，p_i 取 0 或 1e9
"""

import os
import random


def build(n, mode, rng):
    """返回 0 下标的 a 数组，保证 a[i] != i。"""
    a = [-1] * n

    if mode == "pure_cycle":
        # 整张图就是一个环
        for i in range(n):
            a[i] = (i + 1) % n
        return a

    if mode == "two_cycle":
        # 一个 2-环，其余点依次挂上去（形成深层树）
        a[0], a[1] = 1, 0
        for i in range(2, n):
            a[i] = rng.randrange(i)      # 挂在 0..i-1 上，保证链越来越深
        return a

    if mode == "cycle_tree":
        # 长度 2..n 的环 + 深度 >= 2 的挂树
        L = rng.randint(2, max(2, n))
        L = min(L, n)
        for i in range(L):
            a[i] = (i + 1) % L
        for i in range(L, n):
            a[i] = rng.randrange(i)      # 挂到已经出现的点，形成多层子树
        return a

    if mode == "deep_tree":
        # 一条从 0 出发的长链，末端接一个 2-环（s 大概率在链上）
        a[0] = n - 1                     # 0 -> n-1
        a[n - 1] = n - 2                 # n-1 -> n-2
        a[n - 2] = n - 1                 # 末端 2-环
        for i in range(1, n - 2):
            a[i] = i - 1                 # i -> i-1，串成链
        return a

    if mode == "forest":
        # 多个连通块，块内是环或基环树
        perm = list(range(n))
        rng.shuffle(perm)
        cut = 0
        while cut < n:
            remain = n - cut
            size = rng.randint(2, remain) if remain >= 2 else 1
            members = perm[cut:cut + size]
            cut += size
            if size == 1:
                # 单点块：指向块外随便一个点（稍后统一修补自环）
                a[members[0]] = rng.randrange(n)
            else:
                for pos in range(size):
                    a[members[pos]] = members[(pos + 1) % size]
        return a

    # random：完全随机的功能图
    for i in range(n):
        x = rng.randrange(n - 1)
        a[i] = x + 1 if x >= i else x    # 在 0..n-1 去掉 i 后随机取一个
    return a


def on_cycle(a, v):
    x = a[v]
    for _ in range(len(a) + 2):
        if x == v:
            return True
        x = a[x]
    return False


def main():
    seed_text = os.environ.get("DUPAI_SEED")
    rng = random.Random(None if seed_text is None else int(seed_text))

    n = rng.randint(2, 12)
    mode = rng.choice(
        ["pure_cycle", "two_cycle", "cycle_tree", "deep_tree", "forest", "random"]
    )
    a = build(n, mode, rng)

    # 兜底修补：不允许自环（n >= 2 时总能修好）
    for i in range(n):
        if not (0 <= a[i] < n) or a[i] == i:
            a[i] = (i + 1) % n

    # s 的选取：让 s 在环上 / 不在环上两种分支都出现
    roll = rng.random()
    if roll < 0.45:
        s = rng.randrange(n)                       # 随机，大概率在环上
    else:
        off = [v for v in range(n) if not on_cycle(a, v)]
        pool = off if off else list(range(n))
        s = rng.choice(pool)
    s += 1                                          # 转回 1 下标

    # 经常出现极端值，方便测溢出与负权
    if rng.random() < 0.5:
        w = [rng.choice([-10**9, 10**9, 0, rng.randint(-30, 30)]) for _ in range(n)]
        p = [rng.choice([0, 10**9, 0, rng.randint(0, 8)]) for _ in range(n)]
    else:
        w = [rng.randint(-30, 30) for _ in range(n)]
        p = [rng.randint(0, 8) for _ in range(n)]

    print(n, s)
    print(*w)
    print(*p)
    print(*[x + 1 for x in a])          # a 内部用 0 下标，输出转回 1 下标


if __name__ == "__main__":
    main()

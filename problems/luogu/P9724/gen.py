#!/usr/bin/env python3
"""P9724 [EC Final 2022] Chase Game 随机数据生成器。

生成一张连通无向简单图（先随机生成树保证连通，再补若干条不重复的边），
再随机附上 k 和 d。规模控制在 n <= 60，方便暴力 brute.cpp 对拍。
"""
import random
import sys


def gen(seed=None):
    if seed is not None:
        random.seed(seed)
    else:
        random.seed()

    n = random.randint(2, 60)

    # 用随机树保证连通：点 v 连向 [1, v-1] 中的随机一个点。
    edges = set()
    for v in range(2, n + 1):
        u = random.randint(1, v - 1)
        edges.add((u, v))

    # 随机补边：数量与 n 同阶，控制图不会太稠密。
    extra = random.randint(0, n)
    for _ in range(extra):
        a = random.randint(1, n)
        b = random.randint(1, n)
        if a == b:
            continue
        if a > b:
            a, b = b, a
        edges.add((a, b))

    edges = list(edges)
    k = random.randint(1, n)
    # d 覆盖小范围（常触发传送）和大范围（长距离判伤害）两种情况。
    if random.random() < 0.5:
        d = random.randint(1, 6)
    else:
        d = random.randint(1, 2 * n)

    out = ["%d %d %d %d" % (n, len(edges), k, d)]
    for a, b in edges:
        if random.random() < 0.5:
            a, b = b, a
        out.append("%d %d" % (a, b))
    return "\n".join(out) + "\n"


def main():
    seed = None
    if len(sys.argv) > 1:
        seed = int(sys.argv[1])
    sys.stdout.write(gen(seed))


if __name__ == "__main__":
    main()

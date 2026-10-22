#!/usr/bin/env python3
# 随机生成小数据：n 座城市、m 条道路（可能有重边、边权可为 0），q 个询问。
# 覆盖情形：连通图、多连通块（询问跨块答案为 -1）、m = 0、同对点重边、w = 0。
import random


def main():
    random.seed()
    n = random.randint(1, 30)

    all_edges = []
    for i in range(1, n + 1):
        for j in range(i + 1, n + 1):
            all_edges.append((i, j))
    random.shuffle(all_edges)

    # 约 1/3 的数据故意只取较少的边，让图散成多个连通块，制造跨块询问
    max_m = min(len(all_edges), 80)
    if random.random() < 0.3:
        m = random.randint(0, max(0, max_m // 2))
    else:
        m = random.randint(0, max_m)

    # (u, v, w)：先记下每条边的随机权值
    edges = [(u, v, random.randint(0, 1000)) for (u, v) in all_edges[:m]]

    # 一定概率补重边：同一对点再连一条权值不同的路（题面允许）
    if n >= 2 and random.random() < 0.4:
        for _ in range(random.randint(1, 3)):
            u = random.randint(1, n)
            v = random.randint(1, n)
            if u != v:
                edges.append((u, v, random.randint(0, 1000)))

    q = random.randint(1, 50)

    print(n, len(edges))
    for u, v, w in edges:
        print(u, v, w)
    print(q)
    for _ in range(q):
        x = random.randint(1, n)
        y = random.randint(1, n)
        while n > 1 and y == x:
            y = random.randint(1, n)
        print(x, y)


if __name__ == "__main__":
    main()

#!/usr/bin/env python3
# 随机生成小数据。题面保证：t_0 <= t_1 <= ... <= t_{N-1}，且询问的 t 也不下降，
# 所以这里必须把两部分都排序，否则生成的数据不符合题面、对拍结果没有意义。
import random


def main():
    random.seed()

    n = random.randint(2, 12)
    max_edges = n * (n - 1) // 2
    m = random.randint(1, min(max_edges, 20))

    # 题面保证重建时间非降
    times = sorted(random.randint(0, 10) for _ in range(n))

    # 先连成一棵树保证连通，再随机补边；用字典自然去重
    edges = {}
    for i in range(1, n):
        fa = random.randint(0, i - 1)
        key = (min(i, fa), max(i, fa))
        edges[key] = random.randint(1, 20)

    while len(edges) < m:
        u = random.randint(0, n - 1)
        v = random.randint(0, n - 1)
        if u == v:
            continue
        key = (min(u, v), max(u, v))
        if key in edges:
            continue
        edges[key] = random.randint(1, 20)

    q = random.randint(1, 20)

    print(n, len(edges))
    print(" ".join(map(str, times)))
    for (u, v), w in edges.items():
        print(u, v, w)
    print(q)

    # 题面保证询问时间也不下降
    query_days = sorted(random.randint(0, 10) for _ in range(q))
    for day in query_days:
        x = random.randint(0, n - 1)
        y = random.randint(0, n - 1)
        print(x, y, day)


if __name__ == "__main__":
    main()

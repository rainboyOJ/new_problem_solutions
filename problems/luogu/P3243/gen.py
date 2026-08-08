#!/usr/bin/env python3
import random


def gen_case():
    n = random.randint(2, 8)
    edges = []

    # 先随机生成一个 DAG。
    perm = list(range(1, n + 1))
    random.shuffle(perm)
    for i in range(n):
        for j in range(i + 1, n):
            if random.randint(0, 99) < 30:
                edges.append((perm[i], perm[j]))
                if random.randint(0, 99) < 20:
                    edges.append((perm[i], perm[j]))  # 允许重边

    # 一部分数据强行造环，测试 Impossible! 分支。
    if random.randint(0, 99) < 25:
        if n >= 3:
            edges.extend([(1, 2), (2, 3), (3, 1)])
        else:
            edges.extend([(1, 2), (2, 1)])

    return n, edges


def main():
    random.seed()
    T = random.randint(1, 3)
    print(T)
    for _ in range(T):
        n, edges = gen_case()
        print(n, len(edges))
        for u, v in edges:
            print(u, v)


if __name__ == "__main__":
    main()

#!/usr/bin/env python3
# 随机生成小数据：n 个变量、m 条 x_c - x_c' <= y 约束。
# 一半数据随机给边（容易产生负环），一半数据先随机一组"真解"再反推边（保证有解）。
import random


def main():
    random.seed()
    n = random.randint(2, 4)
    if random.random() < 0.5:
        # 随机边：可能因负环无解
        m = random.randint(1, 6)
        edges = []
        for _ in range(m):
            c = random.randint(1, n)
            c2 = random.randint(1, n)
            while c2 == c:
                c2 = random.randint(1, n)
            edges.append((c, c2, random.randint(-3, 3)))
    else:
        # 先取一组真解 x，再让边的权值不小于 x_c - x_c'
        x = [0] + [random.randint(-5, 5) for _ in range(n)]
        m = random.randint(1, 6)
        edges = []
        for _ in range(m):
            c = random.randint(1, n)
            c2 = random.randint(1, n)
            while c2 == c:
                c2 = random.randint(1, n)
            edges.append((c, c2, x[c] - x[c2] + random.randint(0, 3)))

    print(n, m)
    for c, c2, y in edges:
        print(c, c2, y)


if __name__ == "__main__":
    main()

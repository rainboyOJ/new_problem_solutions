#!/usr/bin/env python3
"""生成 P3038 小数据：随机树（n<=30）+ 随机路径加 / 边查询操作，规模适合暴力对拍。"""
import random

random.seed()


def main():
    n = random.randint(2, 30)
    m = random.randint(1, 50)
    print(n, m)

    # 随机生成一棵树：节点 i（i>=2）的父亲是 1..i-1 中的随机一个。
    parent = [0] * (n + 1)
    for i in range(2, n + 1):
        parent[i] = random.randint(1, i - 1)

    order = list(range(2, n + 1))
    random.shuffle(order)  # 打乱边顺序，检验程序不依赖输入边顺序
    for i in order:
        print(i, parent[i])

    for _ in range(m):
        if random.randint(0, 1) == 0:
            # P：两个随机节点（允许相同，路径长度为 0）
            u = random.randint(1, n)
            v = random.randint(1, n)
            print("P", u, v)
        else:
            # Q：随机选一条真实存在的边 (x, parent[x])
            x = random.randint(2, n)
            print("Q", x, parent[x])


if __name__ == "__main__":
    main()

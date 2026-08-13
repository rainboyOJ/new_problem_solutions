#!/usr/bin/env python3
"""生成 P3384 小数据：随机树（n <= 30）加四种操作，规模适合暴力对拍。

输出格式与题面一致：
第一行 n m r p；第二行 n 个点权；接下来 n-1 行边；接下来 m 行操作。
点权与 z 都是非负小整数，p 取小模数，保证能测到取模路径。
"""
import random

random.seed()


def main():
    n = random.randint(1, 30)
    m = random.randint(1, 50)
    r = random.randint(1, n)
    # p 取小模数，p=1 是边界：任何数对 1 取模都是 0。
    p = random.choice([1, 2, 3, 5, 7, 13, 24, 97, 1000])

    print(n, m, r, p)
    print(*[random.randint(0, 100) for _ in range(n)])

    # 随机生成一棵树：第 i 个节点随机接在 1..i-1 某个节点下面。
    for i in range(2, n + 1):
        father = random.randint(1, i - 1)
        print(father, i)

    for _ in range(m):
        op = random.randint(1, 4)
        if op == 1:  # 路径加
            x = random.randint(1, n)
            y = random.randint(1, n)
            z = random.randint(0, 100)
            print(1, x, y, z)
        elif op == 2:  # 路径和
            x = random.randint(1, n)
            y = random.randint(1, n)
            print(2, x, y)
        elif op == 3:  # 子树加
            x = random.randint(1, n)
            z = random.randint(0, 100)
            print(3, x, z)
        else:  # 子树和
            x = random.randint(1, n)
            print(4, x)


if __name__ == "__main__":
    main()

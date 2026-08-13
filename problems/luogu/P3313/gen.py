#!/usr/bin/env python3
"""生成 P3313 小数据：n<=30 个城市、宗教数<=10，m 次 CC/CW/QS/QM 操作，规模适合暴力对拍。

保证每个 QS/QM 的起点与终点宗教相同（与题面数据保证一致）。
"""
import random

random.seed()


def main():
    n = random.randint(1, 30)
    m = random.randint(1, 100)
    cnum = random.randint(1, 10)
    print(n, m)

    col = []
    for _ in range(n):
        c = random.randint(1, cnum)
        w = random.randint(1, 10000)
        col.append(c)
        print(w, c)

    for i in range(1, n):  # 第 i+1 号城市连到前面某个城市，保证是一棵树
        u = i + 1
        v = random.randint(1, i)
        print(u, v)

    for _ in range(m):
        op = random.choice(["CC", "CW", "QS", "QM"])
        if op == "CC":
            x = random.randint(1, n)
            c = random.randint(1, cnum)
            col[x - 1] = c
            print(op, x, c)
        elif op == "CW":
            x = random.randint(1, n)
            w = random.randint(1, 10000)
            print(op, x, w)
        else:
            x = random.randint(1, n)
            same = [i for i in range(1, n + 1) if col[i - 1] == col[x - 1]]
            y = random.choice(same)
            print(op, x, y)


if __name__ == "__main__":
    main()

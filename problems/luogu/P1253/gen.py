#!/usr/bin/env python3
"""生成 P1253 小数据：n 个数，m 个区间赋值 / 区间加 / 区间最大值查询操作，规模适合暴力对拍。"""
import random

random.seed()


def main():
    n = random.randint(1, 30)
    m = random.randint(1, 100)
    print(n, m)
    print(" ".join(str(random.randint(-100, 100)) for _ in range(n)))
    for _ in range(m):
        op = random.randint(1, 3)
        l = random.randint(1, n)
        r = random.randint(1, n)
        if l > r:
            l, r = r, l
        if op == 3:
            print(op, l, r)
        else:
            print(op, l, r, random.randint(-100, 100))


if __name__ == "__main__":
    main()

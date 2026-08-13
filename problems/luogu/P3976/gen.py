#!/usr/bin/env python3
"""生成 P3976 小数据：随机树 n <= 30，m 次随机 (a, b, v) 操作，规模适合暴力对拍。"""
import random

random.seed()


def main():
    n = random.randint(1, 30)
    print(n)
    print(" ".join(str(random.randint(1, 100)) for _ in range(n)))
    for i in range(2, n + 1):
        parent = random.randint(1, i - 1)
        print(parent, i)
    m = random.randint(1, 20)
    print(m)
    for _ in range(m):
        a = random.randint(1, n)
        b = random.randint(1, n)
        v = random.randint(0, 100)
        print(a, b, v)


if __name__ == "__main__":
    main()

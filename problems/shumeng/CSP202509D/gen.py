#!/usr/bin/env python3
"""生成树上路径 mex 的小规模数据。"""

import random


def main():
    random.seed()
    n = random.randint(1, 20)
    m = random.randint(1, 30)
    permutation = list(range(n))
    random.shuffle(permutation)
    print(n, m)
    print(*permutation)
    for i in range(2, n + 1):
        print(i, random.randint(1, i - 1))
    for _ in range(m):
        print(random.randint(1, n), random.randint(1, n))


if __name__ == "__main__":
    main()

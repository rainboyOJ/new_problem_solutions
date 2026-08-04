#!/usr/bin/env python3
"""AcWing 1015 摘花生 的随机小数据生成器（配合 brute.cpp 对拍，行列保持很小）。"""

import random


def main():
    random.seed()
    t = random.randint(1, 5)
    print(t)
    for _ in range(t):
        r = random.randint(1, 6)
        c = random.randint(1, 6)
        print(r, c)
        for _ in range(r):
            print(" ".join(str(random.randint(0, 20)) for _ in range(c)))


if __name__ == "__main__":
    main()

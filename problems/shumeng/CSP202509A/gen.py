#!/usr/bin/env python3
"""生成蒙特卡洛圆内点计数的小规模数据。"""

import random


def main():
    random.seed()
    n = random.randint(1, 50)
    a = random.randint(1, 20)
    print(n, a)
    for _ in range(n):
        print(f"{random.uniform(-a, a):.2f} {random.uniform(-a, a):.2f}")


if __name__ == "__main__":
    main()

#!/usr/bin/env python3
"""生成正态分布查表定位的小规模数据。"""

import random


def main():
    random.seed()
    k = random.randint(1, 10)
    print(k)
    for _ in range(k):
        sigma = random.choice([1, 2, 4, 5, 10, 20, 25, 50, 100])
        mu = random.randint(0, 1000 - 1)
        n = random.randint(mu, 1000)
        print(mu, sigma, n)


if __name__ == "__main__":
    main()

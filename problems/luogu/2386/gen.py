#!/usr/bin/env python3
import random


def main():
    random.seed()
    t = random.randint(1, 5)
    print(t)
    for _ in range(t):
        # 保持小数据：暴力要枚举 (m+1)^n 种方案。
        m = random.randint(1, 7)
        n = random.randint(1, 6)
        print(m, n)


if __name__ == "__main__":
    main()

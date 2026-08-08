#!/usr/bin/env python3
import random


def main():
    random.seed()

    # 生成给 brute.cpp 验证的小数据。
    n = random.randint(1, 10)
    f = random.randint(1, 8)

    print(n, f)
    for _ in range(n):
        print(random.randint(1, 20))


if __name__ == "__main__":
    main()

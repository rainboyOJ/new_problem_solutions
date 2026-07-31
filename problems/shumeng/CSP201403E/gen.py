#!/usr/bin/env python3
import os
import random


def main():
    seed = os.environ.get("DUPAI_SEED")
    random.seed(None if seed is None else int(seed))

    # 暴力程序用于对拍，控制在很小的数据范围内。
    n = random.randint(1, 8)
    print(n)
    for _ in range(n):
        print(*[random.randint(1, 5) for _ in range(4)])


if __name__ == "__main__":
    main()

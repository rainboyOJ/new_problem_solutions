#!/usr/bin/env python3
"""生成 CSP 水印检测的小规模数据。"""

import random


def main():
    random.seed()
    n = random.randint(9, 15)
    limit = random.choice([16, 32, 256])
    print(n, limit)
    for _ in range(n):
        print(*[random.randint(0, limit - 1) for _ in range(n)])


if __name__ == "__main__":
    main()

#!/usr/bin/env python3
"""生成集体锻炼的小规模随机数据。"""

import random


def main():
    random.seed()
    n = random.randint(1, 20)
    print(n)
    print(*[random.randint(1, 100) for _ in range(n)])


if __name__ == "__main__":
    main()

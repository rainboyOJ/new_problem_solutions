#!/usr/bin/env python3
"""生成机器人饲养指南的小规模数据。"""

import random


def main():
    random.seed()
    n = random.randint(1, 20)
    m = random.randint(1, min(6, n))
    print(n, m)
    print(*[random.randint(0, 30) for _ in range(m)])


if __name__ == "__main__":
    main()

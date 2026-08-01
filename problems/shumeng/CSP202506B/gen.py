#!/usr/bin/env python3
"""生成机器人跳跃的小规模数据。"""

import random


def main():
    random.seed()
    n = random.randint(1, 20)
    k = random.randint(1, 20)
    print(n, k)
    print(random.randint(1, n), random.randint(1, n))


if __name__ == "__main__":
    main()

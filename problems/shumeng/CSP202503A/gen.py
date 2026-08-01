#!/usr/bin/env python3
"""生成数值积分的小规模随机数据。"""

import random


def main():
    random.seed()
    l = random.randint(0, 20)
    r = random.randint(l + 2, 40)
    if (r - l) % 2 == 1:
        r += 1
    print(random.randint(-20, 20), random.randint(-20, 20), l, r)


if __name__ == "__main__":
    main()

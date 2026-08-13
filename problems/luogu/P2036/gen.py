#!/usr/bin/env python3
"""生成 P2036 小数据：n<=10，每种配料的酸度 s 与苦度 b 取小值。

s/b 取值范围 1..6：即使全部 10 种配料都选，总酸度 <= 6^10 < 1e9，
满足题面"全部使用产生的总酸度和总苦度小于 1e9"的约束。
"""
import random

random.seed()


def main():
    n = random.randint(1, 10)
    print(n)
    for _ in range(n):
        s = random.randint(1, 6)
        b = random.randint(1, 6)
        print(s, b)


if __name__ == "__main__":
    main()

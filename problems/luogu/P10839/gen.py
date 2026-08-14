#!/usr/bin/env python3
# gen.py：为 P10839 生成随机小数据。
import random


def main():
    random.seed()
    # 数据范围：1 <= a, b, c <= 10，1 <= d <= 1000
    a = random.randint(1, 10)
    b = random.randint(1, 10)
    c = random.randint(1, 10)
    d = random.randint(1, 1000)
    print(a, b, c, d)


if __name__ == "__main__":
    main()

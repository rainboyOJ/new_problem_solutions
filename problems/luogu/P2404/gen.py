#!/usr/bin/env python3
"""生成 P2404 小数据：单个自然数 n，范围取题面 2 <= n <= 8。"""
import random

random.seed()


def main():
    n = random.randint(2, 8)
    print(n)


if __name__ == "__main__":
    main()

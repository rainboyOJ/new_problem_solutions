#!/usr/bin/env python3
"""随机数据生成器：美元汇率"""
import random
import sys

def main():
    random.seed()
    n = random.randint(1, 10)  # 小数据方便对拍
    print(n)
    for _ in range(n):
        print(random.randint(1, 1000))

if __name__ == "__main__":
    main()

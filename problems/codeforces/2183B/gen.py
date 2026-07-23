#!/usr/bin/env python3
# gen.py: 随机生成小数据，用于对拍
import random
import sys

def main():
    n = random.randint(2, 12)
    k = random.randint(2, n)
    a = [random.randint(0, n) for _ in range(n)]
    print(1)
    print(n, k)
    print(' '.join(map(str, a)))

if __name__ == "__main__":
    main()

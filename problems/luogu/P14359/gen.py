#!/usr/bin/env python3
"""随机数据生成器：P14359 [CSP-J 2025] 异或和

用法: python3 gen.py [n] [k] [max_val]
  默认 n=10, k=随机, max_val=255
  输出格式: 第一行 n k, 第二行 n 个整数
"""
import random
import sys


def main():
    n = int(sys.argv[1]) if len(sys.argv) > 1 else 10
    k = int(sys.argv[2]) if len(sys.argv) > 2 else random.randint(0, 255)
    max_val = int(sys.argv[3]) if len(sys.argv) > 3 else 255

    a = [random.randint(0, max_val) for _ in range(n)]
    print(n, k)
    print(' '.join(map(str, a)))


if __name__ == "__main__":
    main()

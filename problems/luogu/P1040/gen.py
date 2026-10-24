#!/usr/bin/env python3
import random

def main():
    n = random.randint(1, 8)
    # 节点权值：小于 100 的正整数
    scores = [random.randint(1, 99) for _ in range(n)]
    print(n)
    print(*(scores))

if __name__ == '__main__':
    main()

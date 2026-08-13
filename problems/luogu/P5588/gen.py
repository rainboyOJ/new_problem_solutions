#!/usr/bin/env python3
"""生成 P5588 小数据：n <= 30 的随机树与随机颜色，规模适合暴力对拍。"""
import random

random.seed()


def main():
    n = random.randint(1, 30)
    print(n)
    print(*[random.randint(1, n) for _ in range(n)])
    # 随机树：节点 i 随机连到 [1, i-1] 中的一个节点，保证是一棵树。
    for i in range(2, n + 1):
        print(i, random.randint(1, i - 1))


if __name__ == "__main__":
    main()

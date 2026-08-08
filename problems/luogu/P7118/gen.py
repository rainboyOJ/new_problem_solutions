#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 9)
    print(n)

    for i in range(1, n + 1):
        left = 0
        right = 0
        if 2 * i <= n:
            left = 2 * i
        if 2 * i + 1 <= n:
            right = 2 * i + 1

        # 随机删边，保持输入仍是一棵从 1 出发可达的二叉树。
        if left != 0 and random.randint(0, 1) == 0:
            left = 0
        if right != 0 and random.randint(0, 1) == 0:
            right = 0

        print(left, right)


if __name__ == "__main__":
    main()

#!/usr/bin/env python3
# 随机生成一棵随机树（n <= 15，配合 O(n^2) 的暴力对拍）。
# 树的结构：第 v 个点向 1..v-1 中随机一个点连边，得到一棵随机有根树。
import random


def main():
    random.seed()
    t = random.randint(1, 3)
    print(t)
    for _ in range(t):
        n = random.randint(1, 15)
        print(n)
        for v in range(2, n + 1):
            u = random.randint(1, v - 1)
            print(u, v)


if __name__ == "__main__":
    main()

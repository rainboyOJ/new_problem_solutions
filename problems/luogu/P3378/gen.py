#!/usr/bin/env python3
"""P3378 【模板】堆：生成小规模操作序列，供对拍使用。

保证操作序列合法：只有堆非空时才可能出现「查询最小值」和「删除最小值」。
"""
import random
import sys


def main():
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))
    else:
        random.seed()

    n = random.randint(1, 30)
    print(n)

    size = 0  # 当前堆里的元素个数，保证查询/删除时堆不为空
    for _ in range(n):
        if size == 0:
            op = 1
        else:
            op = random.choice([1, 1, 2, 3])

        if op == 1:
            # 混入重复值与边界值，覆盖可重堆的常见情形
            x = random.choice([1, 1, 2, 3, 7, 10, random.randint(1, 1000), 10 ** 9])
            print(1, x)
            size += 1
        else:
            print(op)
            if op == 3:
                size -= 1


if __name__ == "__main__":
    main()

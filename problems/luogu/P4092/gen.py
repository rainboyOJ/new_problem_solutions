#!/usr/bin/env python3
"""生成 P4092 小数据：随机有根树（n<=30），标记/查询操作，规模适合暴力对拍。"""
import random

random.seed()


def main():
    n = random.randint(1, 30)
    m = random.randint(1, 50)
    print(n, m)
    # 每个点 v(>=2) 随机选一个编号更小的点当父亲，保证根为 1 且边是父 -> 子。
    for v in range(2, n + 1):
        u = random.randint(1, v - 1)
        print(u, v)
    for _ in range(m):
        opt = 'C' if random.randint(0, 1) == 0 else 'Q'
        u = random.randint(1, n)
        print(opt, u)


if __name__ == "__main__":
    main()

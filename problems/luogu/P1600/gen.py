#!/usr/bin/env python3
"""生成 P1600 小数据：随机树 n<=20、玩家数<=15，规模适合暴力模拟对拍。"""
import random

random.seed()


def main():
    n = random.randint(2, 20)
    m = random.randint(1, 15)
    print(n, m)

    # 随机树：第 i 个点随机连到前面任意一个点上。
    for i in range(2, n + 1):
        p = random.randint(1, i - 1)
        print(i, p)

    # 每个点的观察时刻 w[u] 在 [0, n] 内。
    print(*[random.randint(0, n) for _ in range(n)])

    # m 个玩家的起点和终点。
    for _ in range(m):
        print(random.randint(1, n), random.randint(1, n))


if __name__ == "__main__":
    main()

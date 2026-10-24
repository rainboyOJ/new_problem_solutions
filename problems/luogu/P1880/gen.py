#!/usr/bin/env python3
"""P1880 数据生成器：环形石子合并。

覆盖：n=1 最小规模、全零、大值、以及常规随机。
"""
import random
import sys


def main() -> None:
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))

    mode = random.randint(0, 9)
    if mode == 0:
        n = 1
    elif mode == 1:
        n = 2
    else:
        # 暴力解是指数级且带状态记忆，控制在 n <= 8 保证 brute 可跑
        n = random.randint(1, 8)

    if mode == 2:
        arr = [0] * n
    elif mode == 3:
        arr = [20] * n
    elif mode in (4, 5):
        arr = [random.randint(0, 3) for _ in range(n)]
    else:
        arr = [random.randint(0, 20) for _ in range(n)]

    print(n)
    print(*arr)


if __name__ == "__main__":
    main()
